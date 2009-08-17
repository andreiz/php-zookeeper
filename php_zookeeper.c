/*
  +----------------------------------------------------------------------+
  | Copyright (c) 2009 The PHP Group                                     |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.0 of the PHP license,       |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_0.txt.                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Authors: Andrei Zmievski <andrei@php.net>                            |
  +----------------------------------------------------------------------+
*/

/* $ Id: $ */

/* TODO
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#ifdef ZTS
#include "TSRM.h"
#endif

#include <php_ini.h>
#include <SAPI.h>
#include <ext/standard/info.h>
#include <zend_extensions.h>
#include <ext/standard/php_smart_str.h>

#include "php_zookeeper.h"

/****************************************
  Helper macros
****************************************/
#define ZK_METHOD_INIT_VARS                \
    zval*             object  = getThis(); \
    php_zk_t*         i_obj   = NULL;      \

#define ZK_METHOD_FETCH_OBJECT                                                 \
    i_obj = (php_zk_t *) zend_object_store_get_object( object TSRMLS_CC );   \
	if (!i_obj->zk) {	\
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Zookeeper constructor was not called");	\
		return;	\
	} \

/****************************************
  Structures and definitions
****************************************/
typedef struct {
	zend_object   zo;
	zhandle_t    *zk;
} php_zk_t;

static zend_class_entry *zookeeper_ce = NULL;

#if (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION < 3)
const zend_fcall_info empty_fcall_info = { 0, NULL, NULL, NULL, NULL, 0, NULL, NULL, 0 };
#undef ZEND_BEGIN_ARG_INFO_EX
#define ZEND_BEGIN_ARG_INFO_EX(name, pass_rest_by_reference, return_reference, required_num_args)   \
    static zend_arg_info name[] = {                                                                       \
        { NULL, 0, NULL, 0, 0, 0, pass_rest_by_reference, return_reference, required_num_args },
#endif

ZEND_DECLARE_MODULE_GLOBALS(php_zookeeper)

#ifdef COMPILE_DL_ZOOKEEPER
ZEND_GET_MODULE(zookeeper)
#endif

/****************************************
  Forward declarations
****************************************/

/****************************************
  Method implementations
****************************************/

/****************************************
  Internal support code
****************************************/

/* {{{ constructor/destructor */
static void php_zk_destroy(php_zk_t *i_obj TSRMLS_DC)
{
	if (i_obj->zk) {
		/* TODO */
	}

	efree(i_obj);
}

static void php_zk_free_storage(php_zk_t *i_obj TSRMLS_DC)
{
	zend_object_std_dtor(&i_obj->zo TSRMLS_CC);
	php_zk_destroy(i_obj TSRMLS_CC);
}

zend_object_value php_zk_new(zend_class_entry *ce TSRMLS_DC)
{
    zend_object_value retval;
    php_zk_t *i_obj;
    zval *tmp;

    i_obj = ecalloc(1, sizeof(*i_obj));
	zend_object_std_init( &i_obj->zo, ce TSRMLS_CC );
    zend_hash_copy(i_obj->zo.properties, &ce->default_properties, (copy_ctor_func_t) zval_add_ref, (void *) &tmp, sizeof(zval *));

    retval.handle = zend_objects_store_put(i_obj, (zend_objects_store_dtor_t)zend_objects_destroy_object, (zend_objects_free_object_storage_t)php_zk_free_storage, NULL TSRMLS_CC);
    retval.handlers = zend_get_std_object_handlers();

    return retval;
}
/* }}} */

/* {{{ internal API functions */

/* }}} */

/* {{{ methods arginfo */

/* }}} */

/* {{{ zookeeper_class_methods */
#define ZK_ME(name, args) PHP_ME(Zookeeper, name, args, ZEND_ACC_PUBLIC)
static zend_function_entry zookeeper_class_methods[] = {
    { NULL, NULL, NULL }
};
#undef ZK_ME
/* }}} */

/* {{{ zookeeper_module_entry
 */

zend_module_entry zookeeper_module_entry = {
#if ZEND_MODULE_API_NO >= 20050922
    STANDARD_MODULE_HEADER_EX,
	NULL,
	NULL,
#else
    STANDARD_MODULE_HEADER,
#endif
	"zookeeper",
	NULL,
	PHP_MINIT(zookeeper),
	PHP_MSHUTDOWN(zookeeper),
	NULL,
	NULL,
	PHP_MINFO(zookeeper),
	PHP_ZOOKEEPER_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

/* {{{ php_zk_register_constants */
static void php_zk_register_constants(INIT_FUNC_ARGS)
{
	#define REGISTER_ZK_CLASS_CONST_LONG(name, value) zend_declare_class_constant_long(php_zk_get_ce() , ZEND_STRS( #name ) - 1, value TSRMLS_CC)


	#undef REGISTER_ZK_CLASS_CONST_LONG
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(zookeeper)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "Zookeeper", zookeeper_class_methods);
	zookeeper_ce = zend_register_internal_class(&ce TSRMLS_CC);
	zookeeper_ce->create_object = php_zk_new;

	php_zk_register_constants(INIT_FUNC_ARGS_PASSTHRU);

#ifdef ZTS
	ts_allocate_id(&php_zookeeper_globals_id, sizeof(zend_php_zookeeper_globals),
				   (ts_allocate_ctor) php_zk_init_globals, (ts_allocate_dtor) php_zk_destroy_globals);
#else
	php_zk_init_globals(&php_zookeeper_globals TSRMLS_CC);
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION */
PHP_MSHUTDOWN_FUNCTION(zookeeper)
{
#ifdef ZTS
    ts_free_id(php_zookeeper_globals_id);
#else
    php_zk_destroy_globals(&php_zookeeper_globals TSRMLS_CC);
#endif

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(zookeeper)
{
	php_info_print_table_start();

	php_info_print_table_header(2, "zookeeper support", "enabled");
	php_info_print_table_row(2, "Version", PHP_ZOOKEEPER_VERSION);
	/*
	 * TODO
	 * php_info_print_table_row(2, "libzookeeper version", zookeeper_lib_version());
	 */

	php_info_print_table_end();
}
/* }}} */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim: noet sw=4 ts=4 fdm=marker:
 */
