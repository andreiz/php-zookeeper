#ifndef PHP_ZOOKEEPER_EXCEPTIONS
#define PHP_ZOOKEEPER_EXCEPTIONS

#include <Zend/zend_exceptions.h>

zend_class_entry *zk_base_exception;
zend_class_entry *zk_optimeout_exception;
zend_class_entry *zk_connection_exception;
zend_class_entry *zk_marshalling_exception;
zend_class_entry *zk_auth_exception;
zend_class_entry *zk_session_exception;
zend_class_entry *zk_nonode_exception;

static void php_zk_register_exceptions()
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "ZookeeperException", NULL);
	zk_base_exception = zend_register_internal_class_ex(&ce, zend_exception_get_default(), NULL TSRMLS_CC);

	INIT_CLASS_ENTRY(ce, "ZookeeperOperationTimeoutException", NULL);
	zk_optimeout_exception = zend_register_internal_class_ex(&ce, zk_base_exception, "ZookeeperException");

	INIT_CLASS_ENTRY(ce, "ZookeeperConnectionException", NULL);
	zk_connection_exception = zend_register_internal_class_ex(&ce, zk_base_exception, "ZookeeperException");

	INIT_CLASS_ENTRY(ce, "ZookeeperMarshallingException", NULL);
	zk_marshalling_exception = zend_register_internal_class_ex(&ce, zk_base_exception, "ZookeeperException");

	INIT_CLASS_ENTRY(ce, "ZookeeperAuthenticationException", NULL);
	zk_auth_exception = zend_register_internal_class_ex(&ce, zk_base_exception, "ZookeeperException");

	INIT_CLASS_ENTRY(ce, "ZookeeperSessionException", NULL);
	zk_session_exception = zend_register_internal_class_ex(&ce, zk_base_exception, "ZookeeperException");

	INIT_CLASS_ENTRY(ce, "ZookeeperNoNodeException", NULL);
	zk_nonode_exception = zend_register_internal_class_ex(&ce, zk_base_exception, "ZookeeperException");
}

zend_class_entry * php_zk_get_exception_with_message(zend_class_entry *ce, char *message)
{
	zend_declare_property_string(ce, "message", strlen("message"), message, ZEND_ACC_PUBLIC TSRMLS_CC);
	return ce;
}

static void php_zk_throw_exception(int zk_status)
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

	zend_throw_exception(php_zk_get_exception_with_message(ce, message), NULL, 0 TSRMLS_CC);
	return;
}

#endif  /* PHP_ZOOKEEPER_EXCEPTIONS */
