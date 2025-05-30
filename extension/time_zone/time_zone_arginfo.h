/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 76886f3343f5d96cb606aacda3354880eec69540 */

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_TimeZone_fromISOString, 0, 1, Temporal\\TimeZone, 0)
	ZEND_ARG_TYPE_INFO(0, text, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_TimeZone_utc, 0, 0, Temporal\\TimeZone, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_TimeZone_getId, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_TimeZone_getOffset, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, instant, Temporal\\Instant, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_TimeZone_isEqualTo, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, other, Temporal\\TimeZone, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_TimeZone_toDateTimeZone, 0, 0, DateTimeZone, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_TimeZone_fromDateTimeZone, 0, 1, Temporal\\TimeZone, 0)
	ZEND_ARG_OBJ_INFO(0, zone, DateTimeZone, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_TimeZone_jsonSerialize arginfo_class_Temporal_TimeZone_getId

#define arginfo_class_Temporal_TimeZone___toString arginfo_class_Temporal_TimeZone_getId

ZEND_METHOD(Temporal_TimeZone, fromISOString);
ZEND_METHOD(Temporal_TimeZone, utc);
ZEND_METHOD(Temporal_TimeZone, isEqualTo);
ZEND_METHOD(Temporal_TimeZone, fromDateTimeZone);
ZEND_METHOD(Temporal_TimeZone, jsonSerialize);
ZEND_METHOD(Temporal_TimeZone, __toString);

static const zend_function_entry class_Temporal_TimeZone_methods[] = {
	ZEND_ME(Temporal_TimeZone, fromISOString, arginfo_class_Temporal_TimeZone_fromISOString, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_TimeZone, utc, arginfo_class_Temporal_TimeZone_utc, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
#if (PHP_VERSION_ID >= 80400)
	ZEND_RAW_FENTRY("getId", NULL, arginfo_class_Temporal_TimeZone_getId, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT, NULL, NULL)
#else
	ZEND_RAW_FENTRY("getId", NULL, arginfo_class_Temporal_TimeZone_getId, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
#endif
#if (PHP_VERSION_ID >= 80400)
	ZEND_RAW_FENTRY("getOffset", NULL, arginfo_class_Temporal_TimeZone_getOffset, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT, NULL, NULL)
#else
	ZEND_RAW_FENTRY("getOffset", NULL, arginfo_class_Temporal_TimeZone_getOffset, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
#endif
	ZEND_ME(Temporal_TimeZone, isEqualTo, arginfo_class_Temporal_TimeZone_isEqualTo, ZEND_ACC_PUBLIC)
#if (PHP_VERSION_ID >= 80400)
	ZEND_RAW_FENTRY("toDateTimeZone", NULL, arginfo_class_Temporal_TimeZone_toDateTimeZone, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT, NULL, NULL)
#else
	ZEND_RAW_FENTRY("toDateTimeZone", NULL, arginfo_class_Temporal_TimeZone_toDateTimeZone, ZEND_ACC_PUBLIC|ZEND_ACC_ABSTRACT)
#endif
	ZEND_ME(Temporal_TimeZone, fromDateTimeZone, arginfo_class_Temporal_TimeZone_fromDateTimeZone, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_TimeZone, jsonSerialize, arginfo_class_Temporal_TimeZone_jsonSerialize, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_TimeZone, __toString, arginfo_class_Temporal_TimeZone___toString, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_Temporal_TimeZone(zend_class_entry *class_entry_JsonSerializable, zend_class_entry *class_entry_Stringable)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Temporal", "TimeZone", class_Temporal_TimeZone_methods);
#if (PHP_VERSION_ID >= 80400)
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_ABSTRACT);
#else
	class_entry = zend_register_internal_class_ex(&ce, NULL);
	class_entry->ce_flags |= ZEND_ACC_ABSTRACT;
#endif
	zend_class_implements(class_entry, 2, class_entry_JsonSerializable, class_entry_Stringable);

	return class_entry;
}
