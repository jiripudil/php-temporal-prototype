/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: d5bdab3871fc4b019281b98feb328cd163c42709 */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Temporal_YearWeek___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_YearWeek_of, 0, 2, Temporal\\YearWeek, 0)
	ZEND_ARG_TYPE_INFO(0, year, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, month, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_YearWeek_now, 0, 1, Temporal\\YearWeek, 0)
	ZEND_ARG_OBJ_INFO(0, timeZone, Temporal\\TimeZone, 0)
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, clock, Temporal\\Clock, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_YearWeek_parse, 0, 1, Temporal\\YearWeek, 0)
	ZEND_ARG_TYPE_INFO(0, text, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_YearWeek_getYear, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_YearWeek_withYear, 0, 1, Temporal\\YearWeek, 0)
	ZEND_ARG_TYPE_INFO(0, year, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_YearWeek_plusYears, 0, 1, Temporal\\YearWeek, 0)
	ZEND_ARG_TYPE_INFO(0, years, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_YearWeek_minusYears arginfo_class_Temporal_YearWeek_plusYears

#define arginfo_class_Temporal_YearWeek_getWeek arginfo_class_Temporal_YearWeek_getYear

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_YearWeek_withWeek, 0, 1, Temporal\\YearWeek, 0)
	ZEND_ARG_TYPE_INFO(0, week, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_YearWeek_plusWeeks, 0, 1, Temporal\\YearWeek, 0)
	ZEND_ARG_TYPE_INFO(0, weeks, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_YearWeek_minusWeeks arginfo_class_Temporal_YearWeek_plusWeeks

#define arginfo_class_Temporal_YearWeek_getDaysInYear arginfo_class_Temporal_YearWeek_getYear

#define arginfo_class_Temporal_YearWeek_getWeeksInYear arginfo_class_Temporal_YearWeek_getYear

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_YearWeek_isLeapYear, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_YearWeek_atDay, 0, 1, Temporal\\LocalDate, 0)
	ZEND_ARG_TYPE_INFO(0, dayOfWeek, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_YearWeek_getFirstDay, 0, 0, Temporal\\LocalDate, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_YearWeek_getLastDay arginfo_class_Temporal_YearWeek_getFirstDay

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_YearWeek_compareTo, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, other, Temporal\\YearWeek, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_YearWeek_isEqualTo, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, other, Temporal\\YearWeek, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_YearWeek_isBefore arginfo_class_Temporal_YearWeek_isEqualTo

#define arginfo_class_Temporal_YearWeek_isBeforeOrEqualTo arginfo_class_Temporal_YearWeek_isEqualTo

#define arginfo_class_Temporal_YearWeek_isAfter arginfo_class_Temporal_YearWeek_isEqualTo

#define arginfo_class_Temporal_YearWeek_isAfterOrEqualTo arginfo_class_Temporal_YearWeek_isEqualTo

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_YearWeek_toISOString, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_YearWeek_jsonSerialize arginfo_class_Temporal_YearWeek_toISOString

#define arginfo_class_Temporal_YearWeek___toString arginfo_class_Temporal_YearWeek_toISOString

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_YearWeek___serialize, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_YearWeek___unserialize, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_METHOD(Temporal_YearWeek, __construct);
ZEND_METHOD(Temporal_YearWeek, of);
ZEND_METHOD(Temporal_YearWeek, now);
ZEND_METHOD(Temporal_YearWeek, parse);
ZEND_METHOD(Temporal_YearWeek, getYear);
ZEND_METHOD(Temporal_YearWeek, withYear);
ZEND_METHOD(Temporal_YearWeek, plusYears);
ZEND_METHOD(Temporal_YearWeek, minusYears);
ZEND_METHOD(Temporal_YearWeek, getWeek);
ZEND_METHOD(Temporal_YearWeek, withWeek);
ZEND_METHOD(Temporal_YearWeek, plusWeeks);
ZEND_METHOD(Temporal_YearWeek, minusWeeks);
ZEND_METHOD(Temporal_YearWeek, getDaysInYear);
ZEND_METHOD(Temporal_YearWeek, getWeeksInYear);
ZEND_METHOD(Temporal_YearWeek, isLeapYear);
ZEND_METHOD(Temporal_YearWeek, atDay);
ZEND_METHOD(Temporal_YearWeek, getFirstDay);
ZEND_METHOD(Temporal_YearWeek, getLastDay);
ZEND_METHOD(Temporal_YearWeek, compareTo);
ZEND_METHOD(Temporal_YearWeek, isEqualTo);
ZEND_METHOD(Temporal_YearWeek, isBefore);
ZEND_METHOD(Temporal_YearWeek, isBeforeOrEqualTo);
ZEND_METHOD(Temporal_YearWeek, isAfter);
ZEND_METHOD(Temporal_YearWeek, isAfterOrEqualTo);
ZEND_METHOD(Temporal_YearWeek, toISOString);
ZEND_METHOD(Temporal_YearWeek, jsonSerialize);
ZEND_METHOD(Temporal_YearWeek, __toString);
ZEND_METHOD(Temporal_YearWeek, __serialize);
ZEND_METHOD(Temporal_YearWeek, __unserialize);

static const zend_function_entry class_Temporal_YearWeek_methods[] = {
	ZEND_ME(Temporal_YearWeek, __construct, arginfo_class_Temporal_YearWeek___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(Temporal_YearWeek, of, arginfo_class_Temporal_YearWeek_of, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_YearWeek, now, arginfo_class_Temporal_YearWeek_now, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_YearWeek, parse, arginfo_class_Temporal_YearWeek_parse, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_YearWeek, getYear, arginfo_class_Temporal_YearWeek_getYear, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearWeek, withYear, arginfo_class_Temporal_YearWeek_withYear, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearWeek, plusYears, arginfo_class_Temporal_YearWeek_plusYears, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearWeek, minusYears, arginfo_class_Temporal_YearWeek_minusYears, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearWeek, getWeek, arginfo_class_Temporal_YearWeek_getWeek, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearWeek, withWeek, arginfo_class_Temporal_YearWeek_withWeek, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearWeek, plusWeeks, arginfo_class_Temporal_YearWeek_plusWeeks, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearWeek, minusWeeks, arginfo_class_Temporal_YearWeek_minusWeeks, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearWeek, getDaysInYear, arginfo_class_Temporal_YearWeek_getDaysInYear, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearWeek, getWeeksInYear, arginfo_class_Temporal_YearWeek_getWeeksInYear, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearWeek, isLeapYear, arginfo_class_Temporal_YearWeek_isLeapYear, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearWeek, atDay, arginfo_class_Temporal_YearWeek_atDay, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearWeek, getFirstDay, arginfo_class_Temporal_YearWeek_getFirstDay, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearWeek, getLastDay, arginfo_class_Temporal_YearWeek_getLastDay, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearWeek, compareTo, arginfo_class_Temporal_YearWeek_compareTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearWeek, isEqualTo, arginfo_class_Temporal_YearWeek_isEqualTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearWeek, isBefore, arginfo_class_Temporal_YearWeek_isBefore, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearWeek, isBeforeOrEqualTo, arginfo_class_Temporal_YearWeek_isBeforeOrEqualTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearWeek, isAfter, arginfo_class_Temporal_YearWeek_isAfter, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearWeek, isAfterOrEqualTo, arginfo_class_Temporal_YearWeek_isAfterOrEqualTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearWeek, toISOString, arginfo_class_Temporal_YearWeek_toISOString, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearWeek, jsonSerialize, arginfo_class_Temporal_YearWeek_jsonSerialize, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearWeek, __toString, arginfo_class_Temporal_YearWeek___toString, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearWeek, __serialize, arginfo_class_Temporal_YearWeek___serialize, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_YearWeek, __unserialize, arginfo_class_Temporal_YearWeek___unserialize, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_Temporal_YearWeek(zend_class_entry *class_entry_JsonSerializable, zend_class_entry *class_entry_Stringable)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Temporal", "YearWeek", class_Temporal_YearWeek_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);
	zend_class_implements(class_entry, 2, class_entry_JsonSerializable, class_entry_Stringable);

	return class_entry;
}
