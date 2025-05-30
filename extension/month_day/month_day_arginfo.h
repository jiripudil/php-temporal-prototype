/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 6b46dd73148df07f9cf37799d5d022332ae048d0 */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Temporal_MonthDay___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_MonthDay_of, 0, 2, Temporal\\MonthDay, 0)
	ZEND_ARG_TYPE_INFO(0, month, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, day, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_MonthDay_now, 0, 1, Temporal\\MonthDay, 0)
	ZEND_ARG_OBJ_INFO(0, timeZone, Temporal\\TimeZone, 0)
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, clock, Temporal\\Clock, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_MonthDay_fromISOString, 0, 1, Temporal\\MonthDay, 0)
	ZEND_ARG_TYPE_INFO(0, text, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_MonthDay_getMonth, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_MonthDay_withMonth, 0, 1, Temporal\\MonthDay, 0)
	ZEND_ARG_TYPE_INFO(0, month, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_MonthDay_getDayOfMonth arginfo_class_Temporal_MonthDay_getMonth

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_MonthDay_withDayOfMonth, 0, 1, Temporal\\MonthDay, 0)
	ZEND_ARG_TYPE_INFO(0, day, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_MonthDay_existsInYear, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, year, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_MonthDay_atYear, 0, 1, Temporal\\LocalDate, 0)
	ZEND_ARG_TYPE_INFO(0, year, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_MonthDay_compareTo, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, other, Temporal\\MonthDay, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_MonthDay_isEqualTo, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, other, Temporal\\MonthDay, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_MonthDay_isBefore arginfo_class_Temporal_MonthDay_isEqualTo

#define arginfo_class_Temporal_MonthDay_isBeforeOrEqualTo arginfo_class_Temporal_MonthDay_isEqualTo

#define arginfo_class_Temporal_MonthDay_isAfter arginfo_class_Temporal_MonthDay_isEqualTo

#define arginfo_class_Temporal_MonthDay_isAfterOrEqualTo arginfo_class_Temporal_MonthDay_isEqualTo

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_MonthDay_toISOString, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_MonthDay_jsonSerialize arginfo_class_Temporal_MonthDay_toISOString

#define arginfo_class_Temporal_MonthDay___toString arginfo_class_Temporal_MonthDay_toISOString

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_MonthDay___serialize, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_MonthDay___unserialize, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_METHOD(Temporal_MonthDay, __construct);
ZEND_METHOD(Temporal_MonthDay, of);
ZEND_METHOD(Temporal_MonthDay, now);
ZEND_METHOD(Temporal_MonthDay, fromISOString);
ZEND_METHOD(Temporal_MonthDay, getMonth);
ZEND_METHOD(Temporal_MonthDay, withMonth);
ZEND_METHOD(Temporal_MonthDay, getDayOfMonth);
ZEND_METHOD(Temporal_MonthDay, withDayOfMonth);
ZEND_METHOD(Temporal_MonthDay, existsInYear);
ZEND_METHOD(Temporal_MonthDay, atYear);
ZEND_METHOD(Temporal_MonthDay, compareTo);
ZEND_METHOD(Temporal_MonthDay, isEqualTo);
ZEND_METHOD(Temporal_MonthDay, isBefore);
ZEND_METHOD(Temporal_MonthDay, isBeforeOrEqualTo);
ZEND_METHOD(Temporal_MonthDay, isAfter);
ZEND_METHOD(Temporal_MonthDay, isAfterOrEqualTo);
ZEND_METHOD(Temporal_MonthDay, toISOString);
ZEND_METHOD(Temporal_MonthDay, jsonSerialize);
ZEND_METHOD(Temporal_MonthDay, __toString);
ZEND_METHOD(Temporal_MonthDay, __serialize);
ZEND_METHOD(Temporal_MonthDay, __unserialize);

static const zend_function_entry class_Temporal_MonthDay_methods[] = {
	ZEND_ME(Temporal_MonthDay, __construct, arginfo_class_Temporal_MonthDay___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(Temporal_MonthDay, of, arginfo_class_Temporal_MonthDay_of, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_MonthDay, now, arginfo_class_Temporal_MonthDay_now, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_MonthDay, fromISOString, arginfo_class_Temporal_MonthDay_fromISOString, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_MonthDay, getMonth, arginfo_class_Temporal_MonthDay_getMonth, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_MonthDay, withMonth, arginfo_class_Temporal_MonthDay_withMonth, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_MonthDay, getDayOfMonth, arginfo_class_Temporal_MonthDay_getDayOfMonth, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_MonthDay, withDayOfMonth, arginfo_class_Temporal_MonthDay_withDayOfMonth, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_MonthDay, existsInYear, arginfo_class_Temporal_MonthDay_existsInYear, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_MonthDay, atYear, arginfo_class_Temporal_MonthDay_atYear, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_MonthDay, compareTo, arginfo_class_Temporal_MonthDay_compareTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_MonthDay, isEqualTo, arginfo_class_Temporal_MonthDay_isEqualTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_MonthDay, isBefore, arginfo_class_Temporal_MonthDay_isBefore, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_MonthDay, isBeforeOrEqualTo, arginfo_class_Temporal_MonthDay_isBeforeOrEqualTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_MonthDay, isAfter, arginfo_class_Temporal_MonthDay_isAfter, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_MonthDay, isAfterOrEqualTo, arginfo_class_Temporal_MonthDay_isAfterOrEqualTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_MonthDay, toISOString, arginfo_class_Temporal_MonthDay_toISOString, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_MonthDay, jsonSerialize, arginfo_class_Temporal_MonthDay_jsonSerialize, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_MonthDay, __toString, arginfo_class_Temporal_MonthDay___toString, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_MonthDay, __serialize, arginfo_class_Temporal_MonthDay___serialize, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_MonthDay, __unserialize, arginfo_class_Temporal_MonthDay___unserialize, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_Temporal_MonthDay(zend_class_entry *class_entry_JsonSerializable, zend_class_entry *class_entry_Stringable)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Temporal", "MonthDay", class_Temporal_MonthDay_methods);
#if (PHP_VERSION_ID >= 80400)
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);
#else
	class_entry = zend_register_internal_class_ex(&ce, NULL);
	class_entry->ce_flags |= ZEND_ACC_FINAL;
#endif
	zend_class_implements(class_entry, 2, class_entry_JsonSerializable, class_entry_Stringable);

	return class_entry;
}
