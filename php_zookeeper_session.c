/*
  +----------------------------------------------------------------------+
  | Copyright (c) 2010 The PHP Group                                     |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt.                                 |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Authors: Andrei Zmievski <andrei@php.net>                            |
  |          Mikko Koppanen <mkoppanen@php.net>                          |
  +----------------------------------------------------------------------+
*/

#include "php_zookeeper.h"
#include "php_zookeeper_private.h"
#include "php_zookeeper_session.h"
#include "SAPI.h"

#ifdef HAVE_ZOOKEEPER_SESSION

#define ZK_SESS_DATA php_zookeeper_session *session = PS_GET_MOD_DATA();

#define PHP_ZK_PARENT_NODE "/php-sessid"

#define PHP_ZK_SESS_DEFAULT_LOCK_WAIT 150000

#define PHP_ZK_SESS_LOCK_EXPIRATION 30

ps_module ps_mod_zookeeper = {
	PS_MOD(zookeeper)
};

/* {{{ static php_zookeeper_session *php_zookeeper_session_init(char *save_path TSRMLS_DC)
	Initialize the session
*/
static php_zookeeper_session *php_zookeeper_session_init(char *save_path TSRMLS_DC)
{
	struct Stat stat;

	int status, recv_timeout = ZK_G(recv_timeout);
	php_zookeeper_session *session;

	session     = pecalloc(1, sizeof(php_zookeeper_session), 1);
	session->zk = zookeeper_init(save_path, NULL, recv_timeout, 0, NULL, 0);

	if (!session->zk) {
		efree(session);
		return NULL;
	}

	/* Create parent node if it does not exist */
	if (zoo_exists(session->zk, PHP_ZK_PARENT_NODE, 1, &stat) == ZNONODE) {
		int retry_count = 3;
		do {
			status = zoo_create(session->zk, PHP_ZK_PARENT_NODE, 0, 0, &ZOO_OPEN_ACL_UNSAFE, 0, 0, 0);
			retry_count++;
		} while (status == ZCONNECTIONLOSS && retry_count--);

		if (status != ZOK) {
			zookeeper_close(session->zk);
			efree(session);
			php_error_docref(NULL TSRMLS_CC, E_ERROR, "Failed to create parent node for sessions");
		}
	}
	return session;
}
/* }}} */

/* {{{ static php_zookeeper_session *php_zookeeper_session_get(char *save_path TSRMLS_DC)
	Get a connection. If connection does not exist in persistent list allocates a new one
*/
static php_zookeeper_session *php_zookeeper_session_get(char *save_path TSRMLS_DC)
{
	php_zookeeper_session *session;

	char *plist_key;
	int plist_key_len;
	zend_rsrc_list_entry le, *le_p = NULL;

	plist_key_len  = spprintf(&plist_key, 0, "zk-conn:[%s]", save_path);
	plist_key_len += 1;

	if (zend_hash_find(&EG(persistent_list), plist_key, plist_key_len, (void *)&le_p) == SUCCESS) {
		if (le_p->type == php_zookeeper_get_connection_le()) {
			efree(plist_key);
			return (php_zookeeper_session *) le_p->ptr;
		}
	}

	session = php_zookeeper_session_init(save_path TSRMLS_CC);
	le.type = php_zookeeper_get_connection_le();
	le.ptr  = session;

	if (zend_hash_update(&EG(persistent_list), (char *)plist_key, plist_key_len, (void *)&le, sizeof(le), NULL) == FAILURE) {
		php_error_docref(NULL TSRMLS_CC, E_ERROR, "Could not register persistent entry for the zk handle");
	}

	efree(plist_key);
	session->is_locked = 0;
	return session;
}
/* }}} */

/* {{{ PS_OPEN_FUNC(zookeeper)
*/
PS_OPEN_FUNC(zookeeper)
{
	php_zookeeper_session *session = php_zookeeper_session_get(PS(save_path) TSRMLS_CC);

	if (!session) {
		PS_SET_MOD_DATA(NULL);
		return FAILURE;
	}
	PS_SET_MOD_DATA(session);
	return SUCCESS;
}
/* }}} */

/* {{{ static int php_zookeeper_sess_lock(php_zookeeper_session *session, const char *key TSRMLS_DC)
	Locking functionality. Adapted algo from memcached extension
*/
static zend_bool php_zookeeper_sess_lock(php_zookeeper_session *session, const char *key TSRMLS_DC)
{
	char *lock_path;
	int lock_path_len;
	long attempts, lock_maxwait;
	long lock_wait = ZK_G(sess_lock_wait);
	time_t expiration;

	/* lock_path if freed when the lock is freed */
	lock_path_len = spprintf(&lock_path, 512 + 5, "%s/%s-lock", PHP_ZK_PARENT_NODE, key);

	if (zkr_lock_init(&(session->lock), session->zk, lock_path, &ZOO_OPEN_ACL_UNSAFE) != 0) {
		efree(lock_path);
		return 0;
	}

	/* set max timeout for session_start = max_execution_time.  (c) Andrei Darashenka, Richter & Poweleit GmbH */
	lock_maxwait = zend_ini_long(ZEND_STRS("max_execution_time"), 0);
	if (lock_maxwait <= 0) {
		lock_maxwait = PHP_ZK_SESS_LOCK_EXPIRATION;
	}
	if (lock_wait == 0) {
		lock_wait = PHP_ZK_SESS_DEFAULT_LOCK_WAIT;
	}
	expiration = SG(global_request_time) + lock_maxwait + 1;
	attempts   = lock_maxwait * 1000000 / lock_wait;

	do {
		if (zkr_lock_lock(&(session->lock))) {
			session->is_locked = 1;
			return 1;
		}
		if (lock_wait > 0) {
			usleep(lock_wait);
		}
	} while(--attempts > 0);

	return 0;
}

/* {{{ PS_READ_FUNC(zookeeper)
*/
PS_READ_FUNC(zookeeper)
{
	ZK_SESS_DATA;
	int status, path_len;
	struct Stat stat;
	int retry_count;
	int64_t expiration_time;

	if (ZK_G(session_lock)) {
		if (!php_zookeeper_sess_lock(session, key TSRMLS_CC)) {
			php_error_docref(NULL TSRMLS_CC, E_ERROR, "Failed to create session mutex");
			return FAILURE;
		}
	}

	path_len = snprintf(session->path, 512, "%s/%s", PHP_ZK_PARENT_NODE, key);

	retry_count = 3;
	do {
		status = zoo_exists(session->zk, session->path, 1, &stat);
		retry_count++;
	} while (status == ZCONNECTIONLOSS && retry_count--);

	if (status != ZOK) {
		*val    = NULL;
		*vallen = 0;
		return FAILURE;
	}

	expiration_time = (int64_t) (SG(global_request_time) - PS(gc_maxlifetime)) * 1000;

	/* The session has expired */
	if (stat.mtime < expiration_time) {
		retry_count = 3;
		do {
			status = zoo_delete(session->zk, session->path, -1);
			retry_count++;
		} while (status == ZCONNECTIONLOSS && retry_count--);

		*val    = NULL;
		*vallen = 0;
		return FAILURE;
	}

	*val    = emalloc(stat.dataLength);
	*vallen = stat.dataLength;

	retry_count = 3;
	do {
		status = zoo_get(session->zk, session->path, 0, *val, vallen, &stat);
		retry_count++;
	} while (status == ZCONNECTIONLOSS && retry_count--);

	if (status != ZOK) {
		efree(*val);
		*val    = NULL;
		*vallen = 0;
		return FAILURE;
	}
	return SUCCESS;
}
/* }}} */

/* {{{ PS_WRITE_FUNC(zookeeper)
*/
PS_WRITE_FUNC(zookeeper)
{
	ZK_SESS_DATA;
	int status, retry_count;
	struct Stat stat;

	retry_count = 3;
	do {
		status = zoo_exists(session->zk, session->path, 1, &stat);
		retry_count++;
	} while (status == ZCONNECTIONLOSS && retry_count--);

	retry_count = 3;
	do {
		if (status != ZOK) {
			status = zoo_create(session->zk, session->path, val, vallen, &ZOO_OPEN_ACL_UNSAFE, 0, 0, 0);
		} else {
			status = zoo_set(session->zk, session->path, val, vallen, -1);
		}
		retry_count++;
	} while (status == ZCONNECTIONLOSS && retry_count--);

	return (status == ZOK) ? SUCCESS : FAILURE;
}
/* }}} */

PS_DESTROY_FUNC(zookeeper)
{
	ZK_SESS_DATA;
	int status, retry_count;

	retry_count = 3;
	do {
		status = zoo_delete(session->zk, session->path, -1);
		retry_count++;
	} while (status == ZCONNECTIONLOSS && retry_count--);

	return (status == ZOK) ? SUCCESS : FAILURE;
}

PS_GC_FUNC(zookeeper)
{
	struct Stat stat;
	struct String_vector nodes;
	int i, status;
	int64_t expiration_time;
	ZK_SESS_DATA;

	expiration_time = (int64_t) (SG(global_request_time) - PS(gc_maxlifetime)) * 1000;
	status          = zoo_get_children(session->zk, PHP_ZK_PARENT_NODE, 0, &nodes);

	if (status == ZOK) {
		for (i = 0; i < nodes.count; i++) {
			char path[512];
			int path_len;

			path_len = snprintf(path, 512, "%s/%s", PHP_ZK_PARENT_NODE, nodes.data[i]);

			if (zoo_exists(session->zk, path, 1, &stat) == ZOK) {
				/* TODO: should lock here? */
				if (stat.mtime < expiration_time) {
					(void) zoo_delete(session->zk, path, -1);
				}
			}
		}
	}
	return SUCCESS;
}

static void php_zk_sync_completion(int rc, const char *value, const void *data) {}

PS_CLOSE_FUNC(zookeeper)
{
	ZK_SESS_DATA;

	if (session->is_locked) {
		(void) zkr_lock_unlock(&(session->lock));
		efree(session->lock.path);

		zkr_lock_destroy(&(session->lock));
		session->is_locked = 0;
	}

	/* TODO: is this needed? */
	// zoo_async(session->zk, session->path, php_zk_sync_completion, (const void *) session);
	PS_SET_MOD_DATA(NULL);
	return SUCCESS;
}

#endif /* HAVE_ZOOKEEPER_SESSION */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim: noet sw=4 ts=4 fdm=marker:
 */
