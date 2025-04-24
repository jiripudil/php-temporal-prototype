/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 2a8c07b6aa05649d79316d0575cf18d974efd440 */

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Clock_SystemClock_getTime, 0, 0, Temporal\\Instant, 0)
ZEND_END_ARG_INFO()

ZEND_METHOD(Temporal_Clock_SystemClock, getTime);

static const zend_function_entry class_Temporal_Clock_SystemClock_methods[] = {
	ZEND_ME(Temporal_Clock_SystemClock, getTime, arginfo_class_Temporal_Clock_SystemClock_getTime, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_Temporal_Clock_SystemClock(zend_class_entry *class_entry_Temporal_Clock)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Temporal\\Clock", "SystemClock", class_Temporal_Clock_SystemClock_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);
	zend_class_implements(class_entry, 1, class_entry_Temporal_Clock);

	return class_entry;
}
