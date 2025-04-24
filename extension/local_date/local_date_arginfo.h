/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 1429d7905294ed784fe6f00ab70a1f450f6e8228 */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Temporal_LocalDate___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDate_of, 0, 3, Temporal\\LocalDate, 0)
	ZEND_ARG_TYPE_INFO(0, year, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, month, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, day, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDate_ofDayOfYear, 0, 2, Temporal\\LocalDate, 0)
	ZEND_ARG_TYPE_INFO(0, year, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, dayOfYear, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDate_ofEpochDay, 0, 1, Temporal\\LocalDate, 0)
	ZEND_ARG_TYPE_INFO(0, epochDay, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDate_now, 0, 1, Temporal\\LocalDate, 0)
	ZEND_ARG_OBJ_INFO(0, timeZone, Temporal\\TimeZone, 0)
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, clock, Temporal\\Clock, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDate_fromISOString, 0, 1, Temporal\\LocalDate, 0)
	ZEND_ARG_TYPE_INFO(0, text, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDate_min, 0, 0, Temporal\\LocalDate, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_LocalDate_max arginfo_class_Temporal_LocalDate_min

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_LocalDate_getYear, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDate_withYear, 0, 1, Temporal\\LocalDate, 0)
	ZEND_ARG_TYPE_INFO(0, year, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_LocalDate_getMonth arginfo_class_Temporal_LocalDate_getYear

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDate_withMonth, 0, 1, Temporal\\LocalDate, 0)
	ZEND_ARG_TYPE_INFO(0, month, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDate_getYearMonth, 0, 0, Temporal\\YearMonth, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_LocalDate_getWeek arginfo_class_Temporal_LocalDate_getYear

#define arginfo_class_Temporal_LocalDate_getYearOfWeek arginfo_class_Temporal_LocalDate_getYear

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDate_getYearWeek, 0, 0, Temporal\\YearWeek, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_LocalDate_getDayOfMonth arginfo_class_Temporal_LocalDate_getYear

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDate_withDayOfMonth, 0, 1, Temporal\\LocalDate, 0)
	ZEND_ARG_TYPE_INFO(0, dayOfMonth, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDate_getMonthDay, 0, 0, Temporal\\MonthDay, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_LocalDate_getDayOfYear arginfo_class_Temporal_LocalDate_getYear

#define arginfo_class_Temporal_LocalDate_getDayOfWeek arginfo_class_Temporal_LocalDate_getYear

#define arginfo_class_Temporal_LocalDate_getDaysInMonth arginfo_class_Temporal_LocalDate_getYear

#define arginfo_class_Temporal_LocalDate_getDaysInYear arginfo_class_Temporal_LocalDate_getYear

#define arginfo_class_Temporal_LocalDate_getWeeksInYear arginfo_class_Temporal_LocalDate_getYear

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_LocalDate_isLeapYear, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_LocalDate_toEpochDay arginfo_class_Temporal_LocalDate_getYear

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDate_plus, 0, 1, Temporal\\LocalDate, 0)
	ZEND_ARG_OBJ_INFO(0, period, Temporal\\Period, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDate_plusYears, 0, 1, Temporal\\LocalDate, 0)
	ZEND_ARG_TYPE_INFO(0, years, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDate_plusMonths, 0, 1, Temporal\\LocalDate, 0)
	ZEND_ARG_TYPE_INFO(0, months, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDate_plusWeeks, 0, 1, Temporal\\LocalDate, 0)
	ZEND_ARG_TYPE_INFO(0, weeks, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDate_plusDays, 0, 1, Temporal\\LocalDate, 0)
	ZEND_ARG_TYPE_INFO(0, days, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_LocalDate_minus arginfo_class_Temporal_LocalDate_plus

#define arginfo_class_Temporal_LocalDate_minusYears arginfo_class_Temporal_LocalDate_plusYears

#define arginfo_class_Temporal_LocalDate_minusMonths arginfo_class_Temporal_LocalDate_plusMonths

#define arginfo_class_Temporal_LocalDate_minusWeeks arginfo_class_Temporal_LocalDate_plusWeeks

#define arginfo_class_Temporal_LocalDate_minusDays arginfo_class_Temporal_LocalDate_plusDays

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDate_until, 0, 1, Temporal\\Period, 0)
	ZEND_ARG_OBJ_INFO(0, endExclusive, Temporal\\LocalDate, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_LocalDate_daysUntil, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, endExclusive, Temporal\\LocalDate, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDate_atTime, 0, 1, Temporal\\LocalDateTime, 0)
	ZEND_ARG_OBJ_INFO(0, time, Temporal\\LocalTime, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_LocalDate_compareTo, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, other, Temporal\\LocalDate, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_LocalDate_isEqualTo, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, other, Temporal\\LocalDate, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_LocalDate_isBefore arginfo_class_Temporal_LocalDate_isEqualTo

#define arginfo_class_Temporal_LocalDate_isBeforeOrEqualTo arginfo_class_Temporal_LocalDate_isEqualTo

#define arginfo_class_Temporal_LocalDate_isAfter arginfo_class_Temporal_LocalDate_isEqualTo

#define arginfo_class_Temporal_LocalDate_isAfterOrEqualTo arginfo_class_Temporal_LocalDate_isEqualTo

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDate_toDateTime, 0, 0, DateTimeImmutable, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDate_fromDateTime, 0, 1, Temporal\\LocalDate, 0)
	ZEND_ARG_OBJ_INFO(0, dateTime, DateTimeInterface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_LocalDate_toISOString, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_LocalDate_format, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, localizedPattern, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, locale, IS_STRING, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_LocalDate_formatWith, 0, 1, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO(0, formatter, Temporal\\Format\\DateTimeFormatter, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_LocalDate_jsonSerialize arginfo_class_Temporal_LocalDate_toISOString

#define arginfo_class_Temporal_LocalDate___toString arginfo_class_Temporal_LocalDate_toISOString

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_LocalDate___serialize, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_LocalDate___unserialize, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_METHOD(Temporal_LocalDate, __construct);
ZEND_METHOD(Temporal_LocalDate, of);
ZEND_METHOD(Temporal_LocalDate, ofDayOfYear);
ZEND_METHOD(Temporal_LocalDate, ofEpochDay);
ZEND_METHOD(Temporal_LocalDate, now);
ZEND_METHOD(Temporal_LocalDate, fromISOString);
ZEND_METHOD(Temporal_LocalDate, min);
ZEND_METHOD(Temporal_LocalDate, max);
ZEND_METHOD(Temporal_LocalDate, getYear);
ZEND_METHOD(Temporal_LocalDate, withYear);
ZEND_METHOD(Temporal_LocalDate, getMonth);
ZEND_METHOD(Temporal_LocalDate, withMonth);
ZEND_METHOD(Temporal_LocalDate, getYearMonth);
ZEND_METHOD(Temporal_LocalDate, getWeek);
ZEND_METHOD(Temporal_LocalDate, getYearOfWeek);
ZEND_METHOD(Temporal_LocalDate, getYearWeek);
ZEND_METHOD(Temporal_LocalDate, getDayOfMonth);
ZEND_METHOD(Temporal_LocalDate, withDayOfMonth);
ZEND_METHOD(Temporal_LocalDate, getMonthDay);
ZEND_METHOD(Temporal_LocalDate, getDayOfYear);
ZEND_METHOD(Temporal_LocalDate, getDayOfWeek);
ZEND_METHOD(Temporal_LocalDate, getDaysInMonth);
ZEND_METHOD(Temporal_LocalDate, getDaysInYear);
ZEND_METHOD(Temporal_LocalDate, getWeeksInYear);
ZEND_METHOD(Temporal_LocalDate, isLeapYear);
ZEND_METHOD(Temporal_LocalDate, toEpochDay);
ZEND_METHOD(Temporal_LocalDate, plus);
ZEND_METHOD(Temporal_LocalDate, plusYears);
ZEND_METHOD(Temporal_LocalDate, plusMonths);
ZEND_METHOD(Temporal_LocalDate, plusWeeks);
ZEND_METHOD(Temporal_LocalDate, plusDays);
ZEND_METHOD(Temporal_LocalDate, minus);
ZEND_METHOD(Temporal_LocalDate, minusYears);
ZEND_METHOD(Temporal_LocalDate, minusMonths);
ZEND_METHOD(Temporal_LocalDate, minusWeeks);
ZEND_METHOD(Temporal_LocalDate, minusDays);
ZEND_METHOD(Temporal_LocalDate, until);
ZEND_METHOD(Temporal_LocalDate, daysUntil);
ZEND_METHOD(Temporal_LocalDate, atTime);
ZEND_METHOD(Temporal_LocalDate, compareTo);
ZEND_METHOD(Temporal_LocalDate, isEqualTo);
ZEND_METHOD(Temporal_LocalDate, isBefore);
ZEND_METHOD(Temporal_LocalDate, isBeforeOrEqualTo);
ZEND_METHOD(Temporal_LocalDate, isAfter);
ZEND_METHOD(Temporal_LocalDate, isAfterOrEqualTo);
ZEND_METHOD(Temporal_LocalDate, toDateTime);
ZEND_METHOD(Temporal_LocalDate, fromDateTime);
ZEND_METHOD(Temporal_LocalDate, toISOString);
ZEND_METHOD(Temporal_LocalDate, format);
ZEND_METHOD(Temporal_LocalDate, formatWith);
ZEND_METHOD(Temporal_LocalDate, jsonSerialize);
ZEND_METHOD(Temporal_LocalDate, __toString);
ZEND_METHOD(Temporal_LocalDate, __serialize);
ZEND_METHOD(Temporal_LocalDate, __unserialize);

static const zend_function_entry class_Temporal_LocalDate_methods[] = {
	ZEND_ME(Temporal_LocalDate, __construct, arginfo_class_Temporal_LocalDate___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(Temporal_LocalDate, of, arginfo_class_Temporal_LocalDate_of, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_LocalDate, ofDayOfYear, arginfo_class_Temporal_LocalDate_ofDayOfYear, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_LocalDate, ofEpochDay, arginfo_class_Temporal_LocalDate_ofEpochDay, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_LocalDate, now, arginfo_class_Temporal_LocalDate_now, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_LocalDate, fromISOString, arginfo_class_Temporal_LocalDate_fromISOString, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_LocalDate, min, arginfo_class_Temporal_LocalDate_min, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_LocalDate, max, arginfo_class_Temporal_LocalDate_max, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_LocalDate, getYear, arginfo_class_Temporal_LocalDate_getYear, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, withYear, arginfo_class_Temporal_LocalDate_withYear, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, getMonth, arginfo_class_Temporal_LocalDate_getMonth, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, withMonth, arginfo_class_Temporal_LocalDate_withMonth, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, getYearMonth, arginfo_class_Temporal_LocalDate_getYearMonth, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, getWeek, arginfo_class_Temporal_LocalDate_getWeek, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, getYearOfWeek, arginfo_class_Temporal_LocalDate_getYearOfWeek, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, getYearWeek, arginfo_class_Temporal_LocalDate_getYearWeek, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, getDayOfMonth, arginfo_class_Temporal_LocalDate_getDayOfMonth, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, withDayOfMonth, arginfo_class_Temporal_LocalDate_withDayOfMonth, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, getMonthDay, arginfo_class_Temporal_LocalDate_getMonthDay, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, getDayOfYear, arginfo_class_Temporal_LocalDate_getDayOfYear, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, getDayOfWeek, arginfo_class_Temporal_LocalDate_getDayOfWeek, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, getDaysInMonth, arginfo_class_Temporal_LocalDate_getDaysInMonth, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, getDaysInYear, arginfo_class_Temporal_LocalDate_getDaysInYear, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, getWeeksInYear, arginfo_class_Temporal_LocalDate_getWeeksInYear, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, isLeapYear, arginfo_class_Temporal_LocalDate_isLeapYear, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, toEpochDay, arginfo_class_Temporal_LocalDate_toEpochDay, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, plus, arginfo_class_Temporal_LocalDate_plus, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, plusYears, arginfo_class_Temporal_LocalDate_plusYears, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, plusMonths, arginfo_class_Temporal_LocalDate_plusMonths, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, plusWeeks, arginfo_class_Temporal_LocalDate_plusWeeks, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, plusDays, arginfo_class_Temporal_LocalDate_plusDays, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, minus, arginfo_class_Temporal_LocalDate_minus, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, minusYears, arginfo_class_Temporal_LocalDate_minusYears, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, minusMonths, arginfo_class_Temporal_LocalDate_minusMonths, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, minusWeeks, arginfo_class_Temporal_LocalDate_minusWeeks, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, minusDays, arginfo_class_Temporal_LocalDate_minusDays, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, until, arginfo_class_Temporal_LocalDate_until, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, daysUntil, arginfo_class_Temporal_LocalDate_daysUntil, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, atTime, arginfo_class_Temporal_LocalDate_atTime, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, compareTo, arginfo_class_Temporal_LocalDate_compareTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, isEqualTo, arginfo_class_Temporal_LocalDate_isEqualTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, isBefore, arginfo_class_Temporal_LocalDate_isBefore, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, isBeforeOrEqualTo, arginfo_class_Temporal_LocalDate_isBeforeOrEqualTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, isAfter, arginfo_class_Temporal_LocalDate_isAfter, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, isAfterOrEqualTo, arginfo_class_Temporal_LocalDate_isAfterOrEqualTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, toDateTime, arginfo_class_Temporal_LocalDate_toDateTime, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, fromDateTime, arginfo_class_Temporal_LocalDate_fromDateTime, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_LocalDate, toISOString, arginfo_class_Temporal_LocalDate_toISOString, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, format, arginfo_class_Temporal_LocalDate_format, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, formatWith, arginfo_class_Temporal_LocalDate_formatWith, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, jsonSerialize, arginfo_class_Temporal_LocalDate_jsonSerialize, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, __toString, arginfo_class_Temporal_LocalDate___toString, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, __serialize, arginfo_class_Temporal_LocalDate___serialize, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDate, __unserialize, arginfo_class_Temporal_LocalDate___unserialize, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_Temporal_LocalDate(zend_class_entry *class_entry_JsonSerializable, zend_class_entry *class_entry_Stringable)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Temporal", "LocalDate", class_Temporal_LocalDate_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);
	zend_class_implements(class_entry, 2, class_entry_JsonSerializable, class_entry_Stringable);

	return class_entry;
}
