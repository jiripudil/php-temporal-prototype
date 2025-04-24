/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 4edc3657629e7dbd6d3be873f795b4761c0d5bcc */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Temporal_TimeZoneRegion___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_TimeZoneRegion_of, 0, 1, Temporal\\TimeZoneRegion, 0)
	ZEND_ARG_TYPE_INFO(0, id, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_TimeZoneRegion_fromISOString, 0, 1, Temporal\\TimeZoneRegion, 0)
	ZEND_ARG_TYPE_INFO(0, text, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_TimeZoneRegion_getId, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_TimeZoneRegion_getOffset, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, instant, Temporal\\Instant, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_TimeZoneRegion_toDateTimeZone, 0, 0, DateTimeZone, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_TimeZoneRegion___serialize, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_TimeZoneRegion___unserialize, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_METHOD(Temporal_TimeZoneRegion, __construct);
ZEND_METHOD(Temporal_TimeZoneRegion, of);
ZEND_METHOD(Temporal_TimeZoneRegion, fromISOString);
ZEND_METHOD(Temporal_TimeZoneRegion, getId);
ZEND_METHOD(Temporal_TimeZoneRegion, getOffset);
ZEND_METHOD(Temporal_TimeZoneRegion, toDateTimeZone);
ZEND_METHOD(Temporal_TimeZoneRegion, __serialize);
ZEND_METHOD(Temporal_TimeZoneRegion, __unserialize);

static const zend_function_entry class_Temporal_TimeZoneRegion_methods[] = {
	ZEND_ME(Temporal_TimeZoneRegion, __construct, arginfo_class_Temporal_TimeZoneRegion___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(Temporal_TimeZoneRegion, of, arginfo_class_Temporal_TimeZoneRegion_of, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_TimeZoneRegion, fromISOString, arginfo_class_Temporal_TimeZoneRegion_fromISOString, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_TimeZoneRegion, getId, arginfo_class_Temporal_TimeZoneRegion_getId, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_TimeZoneRegion, getOffset, arginfo_class_Temporal_TimeZoneRegion_getOffset, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_TimeZoneRegion, toDateTimeZone, arginfo_class_Temporal_TimeZoneRegion_toDateTimeZone, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_TimeZoneRegion, __serialize, arginfo_class_Temporal_TimeZoneRegion___serialize, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_TimeZoneRegion, __unserialize, arginfo_class_Temporal_TimeZoneRegion___unserialize, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_Temporal_TimeZoneRegion(zend_class_entry *class_entry_Temporal_TimeZone)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Temporal", "TimeZoneRegion", class_Temporal_TimeZoneRegion_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, class_entry_Temporal_TimeZone, ZEND_ACC_FINAL);

	return class_entry;
}
