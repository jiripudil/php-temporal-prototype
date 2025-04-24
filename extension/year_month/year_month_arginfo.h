/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 53deb59cbb3913dd6604cc1bf3e2667b8fe419b5 */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Temporal_YearMonth___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_YearMonth_of, 0, 2, Temporal\\YearMonth, 0)
	ZEND_ARG_TYPE_INFO(0, year, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, month, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_YearMonth_now, 0, 1, Temporal\\YearMonth, 0)
	ZEND_ARG_OBJ_INFO(0, timeZone, Temporal\\TimeZone, 0)
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, clock, Temporal\\Clock, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_YearMonth_fromISOString, 0, 1, Temporal\\YearMonth, 0)
	ZEND_ARG_TYPE_INFO(0, text, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_YearMonth_getYear, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_YearMonth_withYear, 0, 1, Temporal\\YearMonth, 0)
	ZEND_ARG_TYPE_INFO(0, year, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_YearMonth_plusYears, 0, 1, Temporal\\YearMonth, 0)
	ZEND_ARG_TYPE_INFO(0, years, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_YearMonth_minusYears arginfo_class_Temporal_YearMonth_plusYears

#define arginfo_class_Temporal_YearMonth_getMonth arginfo_class_Temporal_YearMonth_getYear

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_YearMonth_withMonth, 0, 1, Temporal\\YearMonth, 0)
	ZEND_ARG_TYPE_INFO(0, month, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_YearMonth_plusMonths, 0, 1, Temporal\\YearMonth, 0)
	ZEND_ARG_TYPE_INFO(0, months, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_YearMonth_minusMonths arginfo_class_Temporal_YearMonth_plusMonths

#define arginfo_class_Temporal_YearMonth_getDaysInMonth arginfo_class_Temporal_YearMonth_getYear

#define arginfo_class_Temporal_YearMonth_getDaysInYear arginfo_class_Temporal_YearMonth_getYear

#define arginfo_class_Temporal_YearMonth_getWeeksInYear arginfo_class_Temporal_YearMonth_getYear

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_YearMonth_isLeapYear, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_YearMonth_atDay, 0, 1, Temporal\\LocalDate, 0)
	ZEND_ARG_TYPE_INFO(0, dayOfMonth, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_YearMonth_getFirstDay, 0, 0, Temporal\\LocalDate, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_YearMonth_getLastDay arginfo_class_Temporal_YearMonth_getFirstDay

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_YearMonth_compareTo, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, other, Temporal\\YearMonth, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_YearMonth_isEqualTo, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, other, Temporal\\YearMonth, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_YearMonth_isBefore arginfo_class_Temporal_YearMonth_isEqualTo

#define arginfo_class_Temporal_YearMonth_isBeforeOrEqualTo arginfo_class_Temporal_YearMonth_isEqualTo

#define arginfo_class_Temporal_YearMonth_isAfter arginfo_class_Temporal_YearMonth_isEqualTo

#define arginfo_class_Temporal_YearMonth_isAfterOrEqualTo arginfo_class_Temporal_YearMonth_isEqualTo

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_YearMonth_toISOString, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_YearMonth_jsonSerialize arginfo_class_Temporal_YearMonth_toISOString

#define arginfo_class_Temporal_YearMonth___toString arginfo_class_Temporal_YearMonth_toISOString

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_YearMonth___serialize, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_YearMonth___unserialize, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_METHOD(Temporal_YearMonth, __construct);
ZEND_METHOD(Temporal_YearMonth, of);
ZEND_METHOD(Temporal_YearMonth, now);
ZEND_METHOD(Temporal_YearMonth, fromISOString);
ZEND_METHOD(Temporal_YearMonth, getYear);
ZEND_METHOD(Temporal_YearMonth, withYear);
ZEND_METHOD(Temporal_YearMonth, plusYears);
ZEND_METHOD(Temporal_YearMonth, minusYears);
ZEND_METHOD(Temporal_YearMonth, getMonth);
ZEND_METHOD(Temporal_YearMonth, withMonth);
ZEND_METHOD(Temporal_YearMonth, plusMonths);
ZEND_METHOD(Temporal_YearMonth, minusMonths);
ZEND_METHOD(Temporal_YearMonth, getDaysInMonth);
ZEND_METHOD(Temporal_YearMonth, getDaysInYear);
ZEND_METHOD(Temporal_YearMonth, getWeeksInYear);
ZEND_METHOD(Temporal_YearMonth, isLeapYear);
ZEND_METHOD(Temporal_YearMonth, atDay);
ZEND_METHOD(Temporal_YearMonth, getFirstDay);
ZEND_METHOD(Temporal_YearMonth, getLastDay);
ZEND_METHOD(Temporal_YearMonth, compareTo);
ZEND_METHOD(Temporal_YearMonth, isEqualTo);
ZEND_METHOD(Temporal_YearMonth, isBefore);
ZEND_METHOD(Temporal_YearMonth, isBeforeOrEqualTo);
ZEND_METHOD(Temporal_YearMonth, isAfter);
ZEND_METHOD(Temporal_YearMonth, isAfterOrEqualTo);
ZEND_METHOD(Temporal_YearMonth, toISOString);
ZEND_METHOD(Temporal_YearMonth, jsonSerialize);
ZEND_METHOD(Temporal_YearMonth, __toString);
ZEND_METHOD(Temporal_YearMonth, __serialize);
ZEND_METHOD(Temporal_YearMonth, __unserialize);

static const zend_function_entry class_Temporal_YearMonth_methods[] = {
	ZEND_ME(Temporal_YearMonth, __construct, arginfo_class_Temporal_YearMonth___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(Temporal_YearMonth, of, arginfo_class_Temporal_YearMonth_of, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_YearMonth, now, arginfo_class_Temporal_YearMonth_now, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_YearMonth, fromISOString, arginfo_class_Temporal_YearMonth_fromISOString, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_YearMonth, getYear, arginfo_class_Temporal_YearMonth_getYear, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearMonth, withYear, arginfo_class_Temporal_YearMonth_withYear, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearMonth, plusYears, arginfo_class_Temporal_YearMonth_plusYears, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearMonth, minusYears, arginfo_class_Temporal_YearMonth_minusYears, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearMonth, getMonth, arginfo_class_Temporal_YearMonth_getMonth, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearMonth, withMonth, arginfo_class_Temporal_YearMonth_withMonth, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearMonth, plusMonths, arginfo_class_Temporal_YearMonth_plusMonths, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearMonth, minusMonths, arginfo_class_Temporal_YearMonth_minusMonths, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearMonth, getDaysInMonth, arginfo_class_Temporal_YearMonth_getDaysInMonth, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearMonth, getDaysInYear, arginfo_class_Temporal_YearMonth_getDaysInYear, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearMonth, getWeeksInYear, arginfo_class_Temporal_YearMonth_getWeeksInYear, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearMonth, isLeapYear, arginfo_class_Temporal_YearMonth_isLeapYear, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearMonth, atDay, arginfo_class_Temporal_YearMonth_atDay, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearMonth, getFirstDay, arginfo_class_Temporal_YearMonth_getFirstDay, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearMonth, getLastDay, arginfo_class_Temporal_YearMonth_getLastDay, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearMonth, compareTo, arginfo_class_Temporal_YearMonth_compareTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearMonth, isEqualTo, arginfo_class_Temporal_YearMonth_isEqualTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearMonth, isBefore, arginfo_class_Temporal_YearMonth_isBefore, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearMonth, isBeforeOrEqualTo, arginfo_class_Temporal_YearMonth_isBeforeOrEqualTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearMonth, isAfter, arginfo_class_Temporal_YearMonth_isAfter, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearMonth, isAfterOrEqualTo, arginfo_class_Temporal_YearMonth_isAfterOrEqualTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearMonth, toISOString, arginfo_class_Temporal_YearMonth_toISOString, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearMonth, jsonSerialize, arginfo_class_Temporal_YearMonth_jsonSerialize, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearMonth, __toString, arginfo_class_Temporal_YearMonth___toString, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearMonth, __serialize, arginfo_class_Temporal_YearMonth___serialize, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearMonth, __unserialize, arginfo_class_Temporal_YearMonth___unserialize, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_Temporal_YearMonth(zend_class_entry *class_entry_JsonSerializable, zend_class_entry *class_entry_Stringable)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Temporal", "YearMonth", class_Temporal_YearMonth_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);
	zend_class_implements(class_entry, 2, class_entry_JsonSerializable, class_entry_Stringable);

	return class_entry;
}
