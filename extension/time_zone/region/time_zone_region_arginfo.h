/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: d97b852dd605d9747753e8cfa9ef6945c1839ef6 */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Temporal_TimeZoneRegion___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_TimeZoneRegion_of, 0, 1, Temporal\\TimeZoneRegion, 0)
	ZEND_ARG_TYPE_INFO(0, id, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_TimeZoneRegion_fromIsoString, 0, 1, Temporal\\TimeZoneRegion, 0)
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
ZEND_METHOD(Temporal_TimeZoneRegion, fromIsoString);
ZEND_METHOD(Temporal_TimeZoneRegion, getId);
ZEND_METHOD(Temporal_TimeZoneRegion, getOffset);
ZEND_METHOD(Temporal_TimeZoneRegion, toDateTimeZone);
ZEND_METHOD(Temporal_TimeZoneRegion, __serialize);
ZEND_METHOD(Temporal_TimeZoneRegion, __unserialize);

static const zend_function_entry class_Temporal_TimeZoneRegion_methods[] = {
	ZEND_ME(Temporal_TimeZoneRegion, __construct, arginfo_class_Temporal_TimeZoneRegion___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(Temporal_TimeZoneRegion, of, arginfo_class_Temporal_TimeZoneRegion_of, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_TimeZoneRegion, fromIsoString, arginfo_class_Temporal_TimeZoneRegion_fromIsoString, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
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
#if (PHP_VERSION_ID >= 80400)
	class_entry = zend_register_internal_class_with_flags(&ce, class_entry_Temporal_TimeZone, ZEND_ACC_FINAL);
#else
	class_entry = zend_register_internal_class_ex(&ce, class_entry_Temporal_TimeZone);
	class_entry->ce_flags |= ZEND_ACC_FINAL;
#endif

	return class_entry;
}
