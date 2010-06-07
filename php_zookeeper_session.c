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

#define ZK_SESS_DATA php_zookeeper_session *session = PS_GET_MOD_DATA();

#define PHP_ZK_PARENT_NODE "/php-sessid"

ZEND_DECLARE_MODULE_GLOBALS(php_zookeeper)

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
		status = zoo_create(session->zk, PHP_ZK_PARENT_NODE, 0, 0, &ZOO_OPEN_ACL_UNSAFE, 0, 0, 0);
		
		if (status != ZOK) {
			zookeeper_close(session->zk);
			efree(session);
			php_error_docref(NULL TSRMLS_CC, E_ERROR, "Failed to create parent node for sessions");
		}
	}
	
	session->lock = NULL;
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
	return session;
}
/* }}} */

/* {{{ PS_OPEN_FUNC(zookeeper) 
*/
PS_OPEN_FUNC(zookeeper)
{
	struct Stat stat;
	php_zookeeper_session *session = php_zookeeper_session_get(PS(save_path) TSRMLS_C);
	
	if (!session) {
		PS_SET_MOD_DATA(NULL);
		return FAILURE;
	}
	
	PS_SET_MOD_DATA(session);
	return SUCCESS;
}
/* }}} */

/* {{{ PS_READ_FUNC(zookeeper)
*/
PS_READ_FUNC(zookeeper)
{
	ZK_SESS_DATA;
	int status, path_len, lock_path_len;
	char path[512], *lock_path;
	struct Stat stat;
	
	char *buffer;
	int buffer_len, retry_count = 0;
	
	if (ZK_G(session_lock)) {
		session->lock = emalloc(sizeof(zkr_lock_mutex_t));
		lock_path_len = spprintf(&lock_path, 512, "%s/%s-lock", PHP_ZK_PARENT_NODE, key);
	
		if (zkr_lock_init(session->lock, session->zk, lock_path, &ZOO_OPEN_ACL_UNSAFE) != 0) {
			php_error_docref(NULL TSRMLS_CC, E_ERROR, "Failed to create session mutex");
			return FAILURE;
		}
	
		if (!zkr_lock_lock(session->lock)) {
			php_error_docref(NULL TSRMLS_CC, E_ERROR, "Failed to acquire the lock");
			return FAILURE;
		}
	}
	
	path_len = snprintf(path, 512, "%s/%s", PHP_ZK_PARENT_NODE, key);
	
	retry_count = 0;
	do {
		status = zoo_exists(session->zk, path, 1, &stat);
		retry_count++;
	} while (status == ZCONNECTIONLOSS && retry_count < 3);

	if (status != ZOK) {
		*val    = estrdup("");
		*vallen = 0; 
		return SUCCESS;
	}
	
	*val    = emalloc(stat.dataLength);
	*vallen = stat.dataLength;
	
	retry_count = 0;
	do {
		status = zoo_get(session->zk, path, 0, *val, vallen, &stat);
		retry_count++;
	} while (status == ZCONNECTIONLOSS && retry_count < 3);

	if (status != ZOK) {
		efree(*val);
		*val    = estrdup("");
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
	int status, path_len;
	char path[512];
	struct Stat stat;
	
	path_len = snprintf(path, 512, "%s/%s", PHP_ZK_PARENT_NODE, key);
	status   = zoo_exists(session->zk, path, 1, &stat);
	
	if (status != ZOK) {
		status = zoo_create(session->zk, path, val, vallen, &ZOO_OPEN_ACL_UNSAFE, 0, 0, 0);
	} else {
		status = zoo_set(session->zk, path, val, vallen, -1);
	}
	
	return (status == ZOK) ? SUCCESS : FAILURE;
}
/* }}} */

PS_DESTROY_FUNC(zookeeper)
{
	ZK_SESS_DATA;
	int path_len, status;
	char path[512];
	
	path_len = snprintf(path, 512, "%s/%s", PHP_ZK_PARENT_NODE, key);
	status   = zoo_delete(session->zk, path, -1);

	return (status == ZOK) ? SUCCESS : FAILURE;
}

PS_GC_FUNC(zookeeper)
{
	/* TODO: add garbage collection */
}

PS_CLOSE_FUNC(zookeeper)
{
	ZK_SESS_DATA;
	
	if (ZK_G(session_lock)) {	
		(void) zkr_lock_unlock(session->lock);
		efree(session->lock->path);
	
		zkr_lock_destroy(session->lock);
		efree(session->lock);
	}
	
	PS_SET_MOD_DATA(NULL);
	return SUCCESS;
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim: noet sw=4 ts=4 fdm=marker:
 */
