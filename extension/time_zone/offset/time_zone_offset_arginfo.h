/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: d816780eb1d39fb5e08e79e8e847553157bc4cec */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Temporal_TimeZoneOffset___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_TimeZoneOffset_of, 0, 1, Temporal\\TimeZoneOffset, 0)
	ZEND_ARG_TYPE_INFO(0, hours, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, minutes, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, seconds, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_TimeZoneOffset_ofTotalSeconds, 0, 1, Temporal\\TimeZoneOffset, 0)
	ZEND_ARG_TYPE_INFO(0, totalSeconds, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_TimeZoneOffset_fromIsoString, 0, 1, Temporal\\TimeZoneOffset, 0)
	ZEND_ARG_TYPE_INFO(0, text, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_TimeZoneOffset_utc, 0, 0, Temporal\\TimeZoneOffset, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_TimeZoneOffset_getTotalSeconds, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_TimeZoneOffset_getId, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_TimeZoneOffset_getOffset, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, instant, Temporal\\Instant, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_TimeZoneOffset_toDateTimeZone, 0, 0, DateTimeZone, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_TimeZoneOffset___serialize, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_TimeZoneOffset___unserialize, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_METHOD(Temporal_TimeZoneOffset, __construct);
ZEND_METHOD(Temporal_TimeZoneOffset, of);
ZEND_METHOD(Temporal_TimeZoneOffset, ofTotalSeconds);
ZEND_METHOD(Temporal_TimeZoneOffset, fromIsoString);
ZEND_METHOD(Temporal_TimeZoneOffset, utc);
ZEND_METHOD(Temporal_TimeZoneOffset, getTotalSeconds);
ZEND_METHOD(Temporal_TimeZoneOffset, getId);
ZEND_METHOD(Temporal_TimeZoneOffset, getOffset);
ZEND_METHOD(Temporal_TimeZoneOffset, toDateTimeZone);
ZEND_METHOD(Temporal_TimeZoneOffset, __serialize);
ZEND_METHOD(Temporal_TimeZoneOffset, __unserialize);

static const zend_function_entry class_Temporal_TimeZoneOffset_methods[] = {
	ZEND_ME(Temporal_TimeZoneOffset, __construct, arginfo_class_Temporal_TimeZoneOffset___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(Temporal_TimeZoneOffset, of, arginfo_class_Temporal_TimeZoneOffset_of, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_TimeZoneOffset, ofTotalSeconds, arginfo_class_Temporal_TimeZoneOffset_ofTotalSeconds, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_TimeZoneOffset, fromIsoString, arginfo_class_Temporal_TimeZoneOffset_fromIsoString, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_TimeZoneOffset, utc, arginfo_class_Temporal_TimeZoneOffset_utc, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_TimeZoneOffset, getTotalSeconds, arginfo_class_Temporal_TimeZoneOffset_getTotalSeconds, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_TimeZoneOffset, getId, arginfo_class_Temporal_TimeZoneOffset_getId, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_TimeZoneOffset, getOffset, arginfo_class_Temporal_TimeZoneOffset_getOffset, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_TimeZoneOffset, toDateTimeZone, arginfo_class_Temporal_TimeZoneOffset_toDateTimeZone, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_TimeZoneOffset, __serialize, arginfo_class_Temporal_TimeZoneOffset___serialize, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_TimeZoneOffset, __unserialize, arginfo_class_Temporal_TimeZoneOffset___unserialize, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_Temporal_TimeZoneOffset(zend_class_entry *class_entry_Temporal_TimeZone)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Temporal", "TimeZoneOffset", class_Temporal_TimeZoneOffset_methods);
#if (PHP_VERSION_ID >= 80400)
	class_entry = zend_register_internal_class_with_flags(&ce, class_entry_Temporal_TimeZone, ZEND_ACC_FINAL);
#else
	class_entry = zend_register_internal_class_ex(&ce, class_entry_Temporal_TimeZone);
	class_entry->ce_flags |= ZEND_ACC_FINAL;
#endif

	return class_entry;
}
