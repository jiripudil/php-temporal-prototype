/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 681d2dce1f42d8570cdeb30a13315e89ce04e30b */

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Clock_getTime, 0, 0, Temporal\\Instant, 0)
ZEND_END_ARG_INFO()


static const zend_function_entry class_Temporal_Clock_methods[] = {
	ZEND_RAW_FENTRY("getTime", NULL, arginfo_class_Temporal_Clock_getTime, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT, NULL, NULL)
	ZEND_FE_END
};

static zend_class_entry *register_class_Temporal_Clock(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Temporal", "Clock", class_Temporal_Clock_methods);
	class_entry = zend_register_internal_interface(&ce);

	return class_entry;
}
