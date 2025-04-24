/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: f67a3982fe4bee616f4d32a7f68881c3669929ed */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Temporal_LocalDateTime___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDateTime_of, 0, 3, Temporal\\LocalDateTime, 0)
	ZEND_ARG_TYPE_INFO(0, year, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, month, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, day, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, hour, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, minute, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, second, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, nano, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDateTime_ofDateTime, 0, 2, Temporal\\LocalDateTime, 0)
	ZEND_ARG_OBJ_INFO(0, date, Temporal\\LocalDate, 0)
	ZEND_ARG_OBJ_INFO(0, time, Temporal\\LocalTime, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDateTime_now, 0, 1, Temporal\\LocalDateTime, 0)
	ZEND_ARG_OBJ_INFO(0, timeZone, Temporal\\TimeZone, 0)
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, clock, Temporal\\Clock, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDateTime_parse, 0, 1, Temporal\\LocalDateTime, 0)
	ZEND_ARG_TYPE_INFO(0, text, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDateTime_min, 0, 0, Temporal\\LocalDateTime, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_LocalDateTime_max arginfo_class_Temporal_LocalDateTime_min

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDateTime_getDate, 0, 0, Temporal\\LocalDate, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDateTime_withDate, 0, 1, Temporal\\LocalDateTime, 0)
	ZEND_ARG_OBJ_INFO(0, date, Temporal\\LocalDate, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_LocalDateTime_getYear, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDateTime_withYear, 0, 1, Temporal\\LocalDateTime, 0)
	ZEND_ARG_TYPE_INFO(0, year, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_LocalDateTime_getMonth arginfo_class_Temporal_LocalDateTime_getYear

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDateTime_withMonth, 0, 1, Temporal\\LocalDateTime, 0)
	ZEND_ARG_TYPE_INFO(0, month, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDateTime_getYearMonth, 0, 0, Temporal\\YearMonth, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_LocalDateTime_getWeek arginfo_class_Temporal_LocalDateTime_getYear

#define arginfo_class_Temporal_LocalDateTime_getYearOfWeek arginfo_class_Temporal_LocalDateTime_getYear

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDateTime_getYearWeek, 0, 0, Temporal\\YearWeek, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_LocalDateTime_getDayOfMonth arginfo_class_Temporal_LocalDateTime_getYear

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDateTime_withDayOfMonth, 0, 1, Temporal\\LocalDateTime, 0)
	ZEND_ARG_TYPE_INFO(0, dayOfMonth, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDateTime_getMonthDay, 0, 0, Temporal\\MonthDay, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_LocalDateTime_getDayOfYear arginfo_class_Temporal_LocalDateTime_getYear

#define arginfo_class_Temporal_LocalDateTime_getDayOfWeek arginfo_class_Temporal_LocalDateTime_getYear

#define arginfo_class_Temporal_LocalDateTime_getDaysInMonth arginfo_class_Temporal_LocalDateTime_getYear

#define arginfo_class_Temporal_LocalDateTime_getDaysInYear arginfo_class_Temporal_LocalDateTime_getYear

#define arginfo_class_Temporal_LocalDateTime_getWeeksInYear arginfo_class_Temporal_LocalDateTime_getYear

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_LocalDateTime_isLeapYear, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDateTime_getTime, 0, 0, Temporal\\LocalTime, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDateTime_withTime, 0, 1, Temporal\\LocalDateTime, 0)
	ZEND_ARG_OBJ_INFO(0, time, Temporal\\LocalTime, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_LocalDateTime_getHour arginfo_class_Temporal_LocalDateTime_getYear

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDateTime_withHour, 0, 1, Temporal\\LocalDateTime, 0)
	ZEND_ARG_TYPE_INFO(0, hour, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_LocalDateTime_getMinute arginfo_class_Temporal_LocalDateTime_getYear

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDateTime_withMinute, 0, 1, Temporal\\LocalDateTime, 0)
	ZEND_ARG_TYPE_INFO(0, minute, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_LocalDateTime_getSecond arginfo_class_Temporal_LocalDateTime_getYear

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDateTime_withSecond, 0, 1, Temporal\\LocalDateTime, 0)
	ZEND_ARG_TYPE_INFO(0, second, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_LocalDateTime_getNano arginfo_class_Temporal_LocalDateTime_getYear

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDateTime_withNano, 0, 1, Temporal\\LocalDateTime, 0)
	ZEND_ARG_TYPE_INFO(0, nano, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDateTime_plusPeriod, 0, 1, Temporal\\LocalDateTime, 0)
	ZEND_ARG_OBJ_INFO(0, period, Temporal\\Period, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDateTime_plusYears, 0, 1, Temporal\\LocalDateTime, 0)
	ZEND_ARG_TYPE_INFO(0, years, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDateTime_plusMonths, 0, 1, Temporal\\LocalDateTime, 0)
	ZEND_ARG_TYPE_INFO(0, months, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDateTime_plusWeeks, 0, 1, Temporal\\LocalDateTime, 0)
	ZEND_ARG_TYPE_INFO(0, weeks, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDateTime_plusDays, 0, 1, Temporal\\LocalDateTime, 0)
	ZEND_ARG_TYPE_INFO(0, days, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_LocalDateTime_minusPeriod arginfo_class_Temporal_LocalDateTime_plusPeriod

#define arginfo_class_Temporal_LocalDateTime_minusYears arginfo_class_Temporal_LocalDateTime_plusYears

#define arginfo_class_Temporal_LocalDateTime_minusMonths arginfo_class_Temporal_LocalDateTime_plusMonths

#define arginfo_class_Temporal_LocalDateTime_minusWeeks arginfo_class_Temporal_LocalDateTime_plusWeeks

#define arginfo_class_Temporal_LocalDateTime_minusDays arginfo_class_Temporal_LocalDateTime_plusDays

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDateTime_plusDuration, 0, 1, Temporal\\LocalDateTime, 0)
	ZEND_ARG_OBJ_INFO(0, duration, Temporal\\Duration, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDateTime_plusHours, 0, 1, Temporal\\LocalDateTime, 0)
	ZEND_ARG_TYPE_INFO(0, hours, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDateTime_plusMinutes, 0, 1, Temporal\\LocalDateTime, 0)
	ZEND_ARG_TYPE_INFO(0, minutes, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDateTime_plusSeconds, 0, 1, Temporal\\LocalDateTime, 0)
	ZEND_ARG_TYPE_INFO(0, seconds, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDateTime_plusNanos, 0, 1, Temporal\\LocalDateTime, 0)
	ZEND_ARG_TYPE_INFO(0, nanos, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_LocalDateTime_minusDuration arginfo_class_Temporal_LocalDateTime_plusDuration

#define arginfo_class_Temporal_LocalDateTime_minusHours arginfo_class_Temporal_LocalDateTime_plusHours

#define arginfo_class_Temporal_LocalDateTime_minusMinutes arginfo_class_Temporal_LocalDateTime_plusMinutes

#define arginfo_class_Temporal_LocalDateTime_minusSeconds arginfo_class_Temporal_LocalDateTime_plusSeconds

#define arginfo_class_Temporal_LocalDateTime_minusNanos arginfo_class_Temporal_LocalDateTime_plusNanos

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_LocalDateTime_compareTo, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, other, Temporal\\LocalDateTime, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_LocalDateTime_isEqualTo, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, other, Temporal\\LocalDateTime, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_LocalDateTime_isBefore arginfo_class_Temporal_LocalDateTime_isEqualTo

#define arginfo_class_Temporal_LocalDateTime_isBeforeOrEqualTo arginfo_class_Temporal_LocalDateTime_isEqualTo

#define arginfo_class_Temporal_LocalDateTime_isAfter arginfo_class_Temporal_LocalDateTime_isEqualTo

#define arginfo_class_Temporal_LocalDateTime_isAfterOrEqualTo arginfo_class_Temporal_LocalDateTime_isEqualTo

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDateTime_atTimeZone, 0, 1, Temporal\\ZonedDateTime, 0)
	ZEND_ARG_OBJ_INFO(0, timeZone, Temporal\\TimeZone, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDateTime_toDateTime, 0, 0, DateTimeImmutable, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalDateTime_fromDateTime, 0, 1, Temporal\\LocalDateTime, 0)
	ZEND_ARG_OBJ_INFO(0, dateTime, DateTimeInterface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_LocalDateTime_toISOString, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_LocalDateTime_format, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, localizedPattern, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, locale, IS_STRING, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_LocalDateTime_formatWith, 0, 1, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO(0, formatter, Temporal\\Format\\DateTimeFormatter, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_LocalDateTime_jsonSerialize arginfo_class_Temporal_LocalDateTime_toISOString

#define arginfo_class_Temporal_LocalDateTime___toString arginfo_class_Temporal_LocalDateTime_toISOString

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_LocalDateTime___serialize, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_LocalDateTime___unserialize, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_METHOD(Temporal_LocalDateTime, __construct);
ZEND_METHOD(Temporal_LocalDateTime, of);
ZEND_METHOD(Temporal_LocalDateTime, ofDateTime);
ZEND_METHOD(Temporal_LocalDateTime, now);
ZEND_METHOD(Temporal_LocalDateTime, parse);
ZEND_METHOD(Temporal_LocalDateTime, min);
ZEND_METHOD(Temporal_LocalDateTime, max);
ZEND_METHOD(Temporal_LocalDateTime, getDate);
ZEND_METHOD(Temporal_LocalDateTime, withDate);
ZEND_METHOD(Temporal_LocalDateTime, getYear);
ZEND_METHOD(Temporal_LocalDateTime, withYear);
ZEND_METHOD(Temporal_LocalDateTime, getMonth);
ZEND_METHOD(Temporal_LocalDateTime, withMonth);
ZEND_METHOD(Temporal_LocalDateTime, getYearMonth);
ZEND_METHOD(Temporal_LocalDateTime, getWeek);
ZEND_METHOD(Temporal_LocalDateTime, getYearOfWeek);
ZEND_METHOD(Temporal_LocalDateTime, getYearWeek);
ZEND_METHOD(Temporal_LocalDateTime, getDayOfMonth);
ZEND_METHOD(Temporal_LocalDateTime, withDayOfMonth);
ZEND_METHOD(Temporal_LocalDateTime, getMonthDay);
ZEND_METHOD(Temporal_LocalDateTime, getDayOfYear);
ZEND_METHOD(Temporal_LocalDateTime, getDayOfWeek);
ZEND_METHOD(Temporal_LocalDateTime, getDaysInMonth);
ZEND_METHOD(Temporal_LocalDateTime, getDaysInYear);
ZEND_METHOD(Temporal_LocalDateTime, getWeeksInYear);
ZEND_METHOD(Temporal_LocalDateTime, isLeapYear);
ZEND_METHOD(Temporal_LocalDateTime, getTime);
ZEND_METHOD(Temporal_LocalDateTime, withTime);
ZEND_METHOD(Temporal_LocalDateTime, getHour);
ZEND_METHOD(Temporal_LocalDateTime, withHour);
ZEND_METHOD(Temporal_LocalDateTime, getMinute);
ZEND_METHOD(Temporal_LocalDateTime, withMinute);
ZEND_METHOD(Temporal_LocalDateTime, getSecond);
ZEND_METHOD(Temporal_LocalDateTime, withSecond);
ZEND_METHOD(Temporal_LocalDateTime, getNano);
ZEND_METHOD(Temporal_LocalDateTime, withNano);
ZEND_METHOD(Temporal_LocalDateTime, plusPeriod);
ZEND_METHOD(Temporal_LocalDateTime, plusYears);
ZEND_METHOD(Temporal_LocalDateTime, plusMonths);
ZEND_METHOD(Temporal_LocalDateTime, plusWeeks);
ZEND_METHOD(Temporal_LocalDateTime, plusDays);
ZEND_METHOD(Temporal_LocalDateTime, minusPeriod);
ZEND_METHOD(Temporal_LocalDateTime, minusYears);
ZEND_METHOD(Temporal_LocalDateTime, minusMonths);
ZEND_METHOD(Temporal_LocalDateTime, minusWeeks);
ZEND_METHOD(Temporal_LocalDateTime, minusDays);
ZEND_METHOD(Temporal_LocalDateTime, plusDuration);
ZEND_METHOD(Temporal_LocalDateTime, plusHours);
ZEND_METHOD(Temporal_LocalDateTime, plusMinutes);
ZEND_METHOD(Temporal_LocalDateTime, plusSeconds);
ZEND_METHOD(Temporal_LocalDateTime, plusNanos);
ZEND_METHOD(Temporal_LocalDateTime, minusDuration);
ZEND_METHOD(Temporal_LocalDateTime, minusHours);
ZEND_METHOD(Temporal_LocalDateTime, minusMinutes);
ZEND_METHOD(Temporal_LocalDateTime, minusSeconds);
ZEND_METHOD(Temporal_LocalDateTime, minusNanos);
ZEND_METHOD(Temporal_LocalDateTime, compareTo);
ZEND_METHOD(Temporal_LocalDateTime, isEqualTo);
ZEND_METHOD(Temporal_LocalDateTime, isBefore);
ZEND_METHOD(Temporal_LocalDateTime, isBeforeOrEqualTo);
ZEND_METHOD(Temporal_LocalDateTime, isAfter);
ZEND_METHOD(Temporal_LocalDateTime, isAfterOrEqualTo);
ZEND_METHOD(Temporal_LocalDateTime, atTimeZone);
ZEND_METHOD(Temporal_LocalDateTime, toDateTime);
ZEND_METHOD(Temporal_LocalDateTime, fromDateTime);
ZEND_METHOD(Temporal_LocalDateTime, toISOString);
ZEND_METHOD(Temporal_LocalDateTime, format);
ZEND_METHOD(Temporal_LocalDateTime, formatWith);
ZEND_METHOD(Temporal_LocalDateTime, jsonSerialize);
ZEND_METHOD(Temporal_LocalDateTime, __toString);
ZEND_METHOD(Temporal_LocalDateTime, __serialize);
ZEND_METHOD(Temporal_LocalDateTime, __unserialize);

static const zend_function_entry class_Temporal_LocalDateTime_methods[] = {
	ZEND_ME(Temporal_LocalDateTime, __construct, arginfo_class_Temporal_LocalDateTime___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(Temporal_LocalDateTime, of, arginfo_class_Temporal_LocalDateTime_of, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_LocalDateTime, ofDateTime, arginfo_class_Temporal_LocalDateTime_ofDateTime, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_LocalDateTime, now, arginfo_class_Temporal_LocalDateTime_now, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_LocalDateTime, parse, arginfo_class_Temporal_LocalDateTime_parse, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_LocalDateTime, min, arginfo_class_Temporal_LocalDateTime_min, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_LocalDateTime, max, arginfo_class_Temporal_LocalDateTime_max, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_LocalDateTime, getDate, arginfo_class_Temporal_LocalDateTime_getDate, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, withDate, arginfo_class_Temporal_LocalDateTime_withDate, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, getYear, arginfo_class_Temporal_LocalDateTime_getYear, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, withYear, arginfo_class_Temporal_LocalDateTime_withYear, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, getMonth, arginfo_class_Temporal_LocalDateTime_getMonth, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, withMonth, arginfo_class_Temporal_LocalDateTime_withMonth, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, getYearMonth, arginfo_class_Temporal_LocalDateTime_getYearMonth, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, getWeek, arginfo_class_Temporal_LocalDateTime_getWeek, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, getYearOfWeek, arginfo_class_Temporal_LocalDateTime_getYearOfWeek, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, getYearWeek, arginfo_class_Temporal_LocalDateTime_getYearWeek, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, getDayOfMonth, arginfo_class_Temporal_LocalDateTime_getDayOfMonth, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, withDayOfMonth, arginfo_class_Temporal_LocalDateTime_withDayOfMonth, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, getMonthDay, arginfo_class_Temporal_LocalDateTime_getMonthDay, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, getDayOfYear, arginfo_class_Temporal_LocalDateTime_getDayOfYear, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, getDayOfWeek, arginfo_class_Temporal_LocalDateTime_getDayOfWeek, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, getDaysInMonth, arginfo_class_Temporal_LocalDateTime_getDaysInMonth, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, getDaysInYear, arginfo_class_Temporal_LocalDateTime_getDaysInYear, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, getWeeksInYear, arginfo_class_Temporal_LocalDateTime_getWeeksInYear, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, isLeapYear, arginfo_class_Temporal_LocalDateTime_isLeapYear, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, getTime, arginfo_class_Temporal_LocalDateTime_getTime, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, withTime, arginfo_class_Temporal_LocalDateTime_withTime, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, getHour, arginfo_class_Temporal_LocalDateTime_getHour, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, withHour, arginfo_class_Temporal_LocalDateTime_withHour, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, getMinute, arginfo_class_Temporal_LocalDateTime_getMinute, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, withMinute, arginfo_class_Temporal_LocalDateTime_withMinute, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, getSecond, arginfo_class_Temporal_LocalDateTime_getSecond, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, withSecond, arginfo_class_Temporal_LocalDateTime_withSecond, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, getNano, arginfo_class_Temporal_LocalDateTime_getNano, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, withNano, arginfo_class_Temporal_LocalDateTime_withNano, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, plusPeriod, arginfo_class_Temporal_LocalDateTime_plusPeriod, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, plusYears, arginfo_class_Temporal_LocalDateTime_plusYears, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, plusMonths, arginfo_class_Temporal_LocalDateTime_plusMonths, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, plusWeeks, arginfo_class_Temporal_LocalDateTime_plusWeeks, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, plusDays, arginfo_class_Temporal_LocalDateTime_plusDays, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, minusPeriod, arginfo_class_Temporal_LocalDateTime_minusPeriod, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, minusYears, arginfo_class_Temporal_LocalDateTime_minusYears, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, minusMonths, arginfo_class_Temporal_LocalDateTime_minusMonths, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, minusWeeks, arginfo_class_Temporal_LocalDateTime_minusWeeks, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, minusDays, arginfo_class_Temporal_LocalDateTime_minusDays, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, plusDuration, arginfo_class_Temporal_LocalDateTime_plusDuration, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, plusHours, arginfo_class_Temporal_LocalDateTime_plusHours, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, plusMinutes, arginfo_class_Temporal_LocalDateTime_plusMinutes, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, plusSeconds, arginfo_class_Temporal_LocalDateTime_plusSeconds, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, plusNanos, arginfo_class_Temporal_LocalDateTime_plusNanos, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, minusDuration, arginfo_class_Temporal_LocalDateTime_minusDuration, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, minusHours, arginfo_class_Temporal_LocalDateTime_minusHours, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, minusMinutes, arginfo_class_Temporal_LocalDateTime_minusMinutes, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, minusSeconds, arginfo_class_Temporal_LocalDateTime_minusSeconds, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, minusNanos, arginfo_class_Temporal_LocalDateTime_minusNanos, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, compareTo, arginfo_class_Temporal_LocalDateTime_compareTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, isEqualTo, arginfo_class_Temporal_LocalDateTime_isEqualTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, isBefore, arginfo_class_Temporal_LocalDateTime_isBefore, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, isBeforeOrEqualTo, arginfo_class_Temporal_LocalDateTime_isBeforeOrEqualTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, isAfter, arginfo_class_Temporal_LocalDateTime_isAfter, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, isAfterOrEqualTo, arginfo_class_Temporal_LocalDateTime_isAfterOrEqualTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, atTimeZone, arginfo_class_Temporal_LocalDateTime_atTimeZone, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, toDateTime, arginfo_class_Temporal_LocalDateTime_toDateTime, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, fromDateTime, arginfo_class_Temporal_LocalDateTime_fromDateTime, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_LocalDateTime, toISOString, arginfo_class_Temporal_LocalDateTime_toISOString, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, format, arginfo_class_Temporal_LocalDateTime_format, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, formatWith, arginfo_class_Temporal_LocalDateTime_formatWith, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, jsonSerialize, arginfo_class_Temporal_LocalDateTime_jsonSerialize, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, __toString, arginfo_class_Temporal_LocalDateTime___toString, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, __serialize, arginfo_class_Temporal_LocalDateTime___serialize, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalDateTime, __unserialize, arginfo_class_Temporal_LocalDateTime___unserialize, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_Temporal_LocalDateTime(zend_class_entry *class_entry_JsonSerializable, zend_class_entry *class_entry_Stringable)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Temporal", "LocalDateTime", class_Temporal_LocalDateTime_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);
	zend_class_implements(class_entry, 2, class_entry_JsonSerializable, class_entry_Stringable);

	return class_entry;
}
