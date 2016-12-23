
#ifdef ZEND_ENGINE_3
typedef size_t strsize_t;
#define php5to7_add_assoc_string_ex add_assoc_string_ex
#define php5to7_add_next_index_string add_next_index_string
#define php5to7_register_internal_class_ex(class, parent) zend_register_internal_class_ex(class, parent)
#define PHP5TO7_ZVAL_STRING(z, s) ZVAL_STRING(z, s)
#define PHP5TO7_RETVAL_STRING(s) RETVAL_STRING(s)
#define PHP5TO7_RETVAL_STRINGL(s, l) RETVAL_STRINGL(s, l)
#define PHP5TO7_STRS(s) ZEND_STRL(s)

#define Z_ZK_P(zv) php_zk_fetch_object(Z_OBJ_P((zv)))
#else
typedef int strsize_t;
#define php5to7_add_assoc_string_ex(...) add_assoc_string_ex(__VA_ARGS__, 1)
#define php5to7_add_next_index_string(...) add_next_index_string(__VA_ARGS__, 1)
#define php5to7_register_internal_class_ex(class, parent) zend_register_internal_class_ex(class, parent, NULL TSRMLS_CC)
#define PHP5TO7_ZVAL_STRING(z, s) ZVAL_STRING(z, s, 1)
#define PHP5TO7_RETVAL_STRING(s) RETVAL_STRING(s, 1)
#define PHP5TO7_RETVAL_STRINGL(s, l) RETVAL_STRINGL(s, l, 1)
#define PHP5TO7_STRS(s) ZEND_STRS(s)

#define Z_ZK_P(zv) zend_object_store_get_object(zv TSRMLS_CC)
#endif
