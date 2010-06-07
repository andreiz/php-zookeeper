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

#ifdef HAVE_ZOOKEEPER_SESSION

#ifndef _PHP_ZOOKEEPER_SESSION_H_
# define _PHP_ZOOKEEPER_SESSION_H_

#include "zoo_lock.h"

/* {{{ typedef struct _php_zookeeper_session
*/
typedef struct _php_zookeeper_session {
	/* Connection to zookeeper */
	zhandle_t *zk;
	
	/* Lock for the session */
	zkr_lock_mutex_t lock;
	
	/* Whether the session is locked */
	zend_bool is_locked;
	
	/* Current session path */
	char path[512];
} php_zookeeper_session;
/* }}} */

#endif /* _PHP_ZOOKEEPER_SESSION_H_ */

#endif /* HAVE_ZOOKEEPER_SESSION */