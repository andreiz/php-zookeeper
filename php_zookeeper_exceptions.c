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
  | Authors: Ryan Uber <ru@ryanuber.com>                                 |
  |          Timandes White <timands@gmail.com>                          |
  +----------------------------------------------------------------------+
*/

#include <php.h>

#ifdef ZTS
#include "TSRM.h"
#endif

#include "php5to7.h"
#include "php_zookeeper.h"
#include "php_zookeeper_exceptions.h"

void php_zk_register_exceptions(TSRMLS_D)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "ZookeeperException", NULL);
	zk_base_exception = php5to7_register_internal_class_ex(&ce, zend_exception_get_default(TSRMLS_C));

	INIT_CLASS_ENTRY(ce, "ZookeeperOperationTimeoutException", NULL);
	zk_optimeout_exception = php5to7_register_internal_class_ex(&ce, zk_base_exception);

	INIT_CLASS_ENTRY(ce, "ZookeeperConnectionException", NULL);
	zk_connection_exception = php5to7_register_internal_class_ex(&ce, zk_base_exception);

	INIT_CLASS_ENTRY(ce, "ZookeeperMarshallingException", NULL);
	zk_marshalling_exception = php5to7_register_internal_class_ex(&ce, zk_base_exception);

	INIT_CLASS_ENTRY(ce, "ZookeeperAuthenticationException", NULL);
	zk_auth_exception = php5to7_register_internal_class_ex(&ce, zk_base_exception);

	INIT_CLASS_ENTRY(ce, "ZookeeperSessionException", NULL);
	zk_session_exception = php5to7_register_internal_class_ex(&ce, zk_base_exception);

	INIT_CLASS_ENTRY(ce, "ZookeeperNoNodeException", NULL);
	zk_nonode_exception = php5to7_register_internal_class_ex(&ce, zk_base_exception);
}

zend_class_entry * php_zk_get_exception_with_message(zend_class_entry *ce, char *message TSRMLS_DC)
{
	zend_declare_property_string(ce, "message", strlen("message"), message, ZEND_ACC_PUBLIC TSRMLS_CC);
	return ce;
}

void php_zk_throw_exception(int zk_status TSRMLS_DC)
{
	zend_class_entry *ce;
	char *message = NULL;

	switch(zk_status) {
		case PHPZK_CONNECTION_FAILURE:
			ce = zk_connection_exception;
			message = "Failed to connect to Zookeeper";
			break;
		case PHPZK_CONNECT_NOT_CALLED:
			ce = zk_connection_exception;
			message = "Zookeeper->connect() was not called";
			break;
		case ZCONNECTIONLOSS:
			ce = zk_connection_exception;
			break;
		case ZOPERATIONTIMEOUT:
			ce = zk_optimeout_exception;
			break;
		case ZMARSHALLINGERROR:
			ce = zk_marshalling_exception;
			break;
		case ZNOAUTH:
		case ZAUTHFAILED:
			ce = zk_auth_exception;
			break;
		case ZSESSIONEXPIRED:
		case ZSESSIONMOVED:
			ce = zk_session_exception;
			break;
		case ZNONODE:
			ce = zk_nonode_exception;
			break;
		default:
			ce = zk_base_exception;
			break;
	}

	if (!message) {
		message = (char *)zerror(zk_status);
	}

    zend_throw_exception_ex(ce, zk_status TSRMLS_CC, "%s", message);
	return;
}
