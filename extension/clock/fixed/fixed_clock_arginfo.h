/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 74ff72659291c920078731297c7dbd95f6791223 */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Temporal_Clock_FixedClock___construct, 0, 0, 1)
	ZEND_ARG_OBJ_INFO(0, instant, Temporal\\Instant, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Clock_FixedClock_getTime, 0, 0, Temporal\\Instant, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_Clock_FixedClock_setTime, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, instant, Temporal\\Instant, 0)
ZEND_END_ARG_INFO()

ZEND_METHOD(Temporal_Clock_FixedClock, __construct);
ZEND_METHOD(Temporal_Clock_FixedClock, getTime);
ZEND_METHOD(Temporal_Clock_FixedClock, setTime);

static const zend_function_entry class_Temporal_Clock_FixedClock_methods[] = {
	ZEND_ME(Temporal_Clock_FixedClock, __construct, arginfo_class_Temporal_Clock_FixedClock___construct, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Clock_FixedClock, getTime, arginfo_class_Temporal_Clock_FixedClock_getTime, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Clock_FixedClock, setTime, arginfo_class_Temporal_Clock_FixedClock_setTime, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_Temporal_Clock_FixedClock(zend_class_entry *class_entry_Temporal_Clock)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Temporal\\Clock", "FixedClock", class_Temporal_Clock_FixedClock_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);
	zend_class_implements(class_entry, 1, class_entry_Temporal_Clock);

	zval property_instant_default_value;
	ZVAL_UNDEF(&property_instant_default_value);
	zend_string *property_instant_name = zend_string_init("instant", sizeof("instant") - 1, 1);
	zend_string *property_instant_class_Temporal_Instant = zend_string_init("Temporal\\Instant", sizeof("Temporal\\Instant")-1, 1);
	zend_declare_typed_property(class_entry, property_instant_name, &property_instant_default_value, ZEND_ACC_PRIVATE, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_instant_class_Temporal_Instant, 0, 0));
	zend_string_release(property_instant_name);

	return class_entry;
}
