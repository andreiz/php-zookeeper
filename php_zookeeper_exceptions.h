#ifndef PHP_ZOOKEEPER_EXCEPTIONS
#define PHP_ZOOKEEPER_EXCEPTIONS

#include <Zend/zend_exceptions.h>

zend_class_entry *zk_base_exception;
zend_class_entry *zk_optimeout_exception;
zend_class_entry *zk_connection_exception;
zend_class_entry *zk_marshalling_exception;
zend_class_entry *zk_auth_exception;
zend_class_entry *zk_session_exception;

#endif  /* PHP_ZOOKEEPER_EXCEPTIONS */
