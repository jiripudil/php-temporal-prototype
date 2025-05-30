/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 84ceec1f5448fc8971ed9f25ccd01c81c574d7d0 */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Temporal_ZonedDateTime___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_of, 0, 2, Temporal\\ZonedDateTime, 0)
	ZEND_ARG_OBJ_INFO(0, dateTime, Temporal\\LocalDateTime, 0)
	ZEND_ARG_OBJ_INFO(0, timeZone, Temporal\\TimeZone, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_ofInstant, 0, 2, Temporal\\ZonedDateTime, 0)
	ZEND_ARG_OBJ_INFO(0, instant, Temporal\\Instant, 0)
	ZEND_ARG_OBJ_INFO(0, timeZone, Temporal\\TimeZone, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_now, 0, 1, Temporal\\ZonedDateTime, 0)
	ZEND_ARG_OBJ_INFO(0, timeZone, Temporal\\TimeZone, 0)
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, clock, Temporal\\Clock, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_fromISOString, 0, 1, Temporal\\ZonedDateTime, 0)
	ZEND_ARG_TYPE_INFO(0, text, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_getDateTime, 0, 0, Temporal\\LocalDateTime, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_getDate, 0, 0, Temporal\\LocalDate, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_withDate, 0, 1, Temporal\\ZonedDateTime, 0)
	ZEND_ARG_OBJ_INFO(0, date, Temporal\\LocalDate, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_ZonedDateTime_getYear, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_withYear, 0, 1, Temporal\\ZonedDateTime, 0)
	ZEND_ARG_TYPE_INFO(0, year, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_ZonedDateTime_getMonth arginfo_class_Temporal_ZonedDateTime_getYear

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_withMonth, 0, 1, Temporal\\ZonedDateTime, 0)
	ZEND_ARG_TYPE_INFO(0, month, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_getYearMonth, 0, 0, Temporal\\YearMonth, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_ZonedDateTime_getWeek arginfo_class_Temporal_ZonedDateTime_getYear

#define arginfo_class_Temporal_ZonedDateTime_getYearOfWeek arginfo_class_Temporal_ZonedDateTime_getYear

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_getYearWeek, 0, 0, Temporal\\YearWeek, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_ZonedDateTime_getDayOfMonth arginfo_class_Temporal_ZonedDateTime_getYear

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_withDayOfMonth, 0, 1, Temporal\\ZonedDateTime, 0)
	ZEND_ARG_TYPE_INFO(0, dayOfMonth, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_getMonthDay, 0, 0, Temporal\\MonthDay, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_ZonedDateTime_getDayOfYear arginfo_class_Temporal_ZonedDateTime_getYear

#define arginfo_class_Temporal_ZonedDateTime_getDayOfWeek arginfo_class_Temporal_ZonedDateTime_getYear

#define arginfo_class_Temporal_ZonedDateTime_getDaysInMonth arginfo_class_Temporal_ZonedDateTime_getYear

#define arginfo_class_Temporal_ZonedDateTime_getDaysInYear arginfo_class_Temporal_ZonedDateTime_getYear

#define arginfo_class_Temporal_ZonedDateTime_getWeeksInYear arginfo_class_Temporal_ZonedDateTime_getYear

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_ZonedDateTime_isLeapYear, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_getTime, 0, 0, Temporal\\LocalTime, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_withTime, 0, 1, Temporal\\ZonedDateTime, 0)
	ZEND_ARG_OBJ_INFO(0, time, Temporal\\LocalTime, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_ZonedDateTime_getHour arginfo_class_Temporal_ZonedDateTime_getYear

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_withHour, 0, 1, Temporal\\ZonedDateTime, 0)
	ZEND_ARG_TYPE_INFO(0, hour, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_ZonedDateTime_getMinute arginfo_class_Temporal_ZonedDateTime_getYear

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_withMinute, 0, 1, Temporal\\ZonedDateTime, 0)
	ZEND_ARG_TYPE_INFO(0, minute, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_ZonedDateTime_getSecond arginfo_class_Temporal_ZonedDateTime_getYear

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_withSecond, 0, 1, Temporal\\ZonedDateTime, 0)
	ZEND_ARG_TYPE_INFO(0, second, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_ZonedDateTime_getNano arginfo_class_Temporal_ZonedDateTime_getYear

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_withNano, 0, 1, Temporal\\ZonedDateTime, 0)
	ZEND_ARG_TYPE_INFO(0, nano, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_getInstant, 0, 0, Temporal\\Instant, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_getTimeZone, 0, 0, Temporal\\TimeZone, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_getTimeZoneOffset, 0, 0, Temporal\\TimeZoneOffset, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_withTimeZoneSameLocal, 0, 1, Temporal\\ZonedDateTime, 0)
	ZEND_ARG_OBJ_INFO(0, timeZone, Temporal\\TimeZone, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_ZonedDateTime_withTimeZoneSameInstant arginfo_class_Temporal_ZonedDateTime_withTimeZoneSameLocal

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_withFixedOffsetTimeZone, 0, 0, Temporal\\ZonedDateTime, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_plusPeriod, 0, 1, Temporal\\ZonedDateTime, 0)
	ZEND_ARG_OBJ_INFO(0, period, Temporal\\Period, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_plusYears, 0, 1, Temporal\\ZonedDateTime, 0)
	ZEND_ARG_TYPE_INFO(0, years, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_plusMonths, 0, 1, Temporal\\ZonedDateTime, 0)
	ZEND_ARG_TYPE_INFO(0, months, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_plusWeeks, 0, 1, Temporal\\ZonedDateTime, 0)
	ZEND_ARG_TYPE_INFO(0, weeks, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_plusDays, 0, 1, Temporal\\ZonedDateTime, 0)
	ZEND_ARG_TYPE_INFO(0, days, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_ZonedDateTime_minusPeriod arginfo_class_Temporal_ZonedDateTime_plusPeriod

#define arginfo_class_Temporal_ZonedDateTime_minusYears arginfo_class_Temporal_ZonedDateTime_plusYears

#define arginfo_class_Temporal_ZonedDateTime_minusMonths arginfo_class_Temporal_ZonedDateTime_plusMonths

#define arginfo_class_Temporal_ZonedDateTime_minusWeeks arginfo_class_Temporal_ZonedDateTime_plusWeeks

#define arginfo_class_Temporal_ZonedDateTime_minusDays arginfo_class_Temporal_ZonedDateTime_plusDays

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_plusDuration, 0, 1, Temporal\\ZonedDateTime, 0)
	ZEND_ARG_OBJ_INFO(0, duration, Temporal\\Duration, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_plusHours, 0, 1, Temporal\\ZonedDateTime, 0)
	ZEND_ARG_TYPE_INFO(0, hours, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_plusMinutes, 0, 1, Temporal\\ZonedDateTime, 0)
	ZEND_ARG_TYPE_INFO(0, minutes, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_plusSeconds, 0, 1, Temporal\\ZonedDateTime, 0)
	ZEND_ARG_TYPE_INFO(0, seconds, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_plusNanos, 0, 1, Temporal\\ZonedDateTime, 0)
	ZEND_ARG_TYPE_INFO(0, nanos, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_ZonedDateTime_minusDuration arginfo_class_Temporal_ZonedDateTime_plusDuration

#define arginfo_class_Temporal_ZonedDateTime_minusHours arginfo_class_Temporal_ZonedDateTime_plusHours

#define arginfo_class_Temporal_ZonedDateTime_minusMinutes arginfo_class_Temporal_ZonedDateTime_plusMinutes

#define arginfo_class_Temporal_ZonedDateTime_minusSeconds arginfo_class_Temporal_ZonedDateTime_plusSeconds

#define arginfo_class_Temporal_ZonedDateTime_minusNanos arginfo_class_Temporal_ZonedDateTime_plusNanos

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_ZonedDateTime_compareTo, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, other, Temporal\\ZonedDateTime, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_ZonedDateTime_isEqualTo, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, other, Temporal\\ZonedDateTime, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_ZonedDateTime_isBefore arginfo_class_Temporal_ZonedDateTime_isEqualTo

#define arginfo_class_Temporal_ZonedDateTime_isBeforeOrEqualTo arginfo_class_Temporal_ZonedDateTime_isEqualTo

#define arginfo_class_Temporal_ZonedDateTime_isAfter arginfo_class_Temporal_ZonedDateTime_isEqualTo

#define arginfo_class_Temporal_ZonedDateTime_isAfterOrEqualTo arginfo_class_Temporal_ZonedDateTime_isEqualTo

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_toDateTime, 0, 0, DateTimeImmutable, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_ZonedDateTime_fromDateTime, 0, 1, Temporal\\ZonedDateTime, 0)
	ZEND_ARG_OBJ_INFO(0, dateTime, DateTimeInterface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_ZonedDateTime_toISOString, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_ZonedDateTime_format, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, localizedPattern, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, locale, IS_STRING, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_ZonedDateTime_formatWith, 0, 1, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO(0, formatter, Temporal\\Format\\DateTimeFormatter, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_ZonedDateTime_jsonSerialize arginfo_class_Temporal_ZonedDateTime_toISOString

#define arginfo_class_Temporal_ZonedDateTime___toString arginfo_class_Temporal_ZonedDateTime_toISOString

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_ZonedDateTime___serialize, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_ZonedDateTime___unserialize, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_METHOD(Temporal_ZonedDateTime, __construct);
ZEND_METHOD(Temporal_ZonedDateTime, of);
ZEND_METHOD(Temporal_ZonedDateTime, ofInstant);
ZEND_METHOD(Temporal_ZonedDateTime, now);
ZEND_METHOD(Temporal_ZonedDateTime, fromISOString);
ZEND_METHOD(Temporal_ZonedDateTime, getDateTime);
ZEND_METHOD(Temporal_ZonedDateTime, getDate);
ZEND_METHOD(Temporal_ZonedDateTime, withDate);
ZEND_METHOD(Temporal_ZonedDateTime, getYear);
ZEND_METHOD(Temporal_ZonedDateTime, withYear);
ZEND_METHOD(Temporal_ZonedDateTime, getMonth);
ZEND_METHOD(Temporal_ZonedDateTime, withMonth);
ZEND_METHOD(Temporal_ZonedDateTime, getYearMonth);
ZEND_METHOD(Temporal_ZonedDateTime, getWeek);
ZEND_METHOD(Temporal_ZonedDateTime, getYearOfWeek);
ZEND_METHOD(Temporal_ZonedDateTime, getYearWeek);
ZEND_METHOD(Temporal_ZonedDateTime, getDayOfMonth);
ZEND_METHOD(Temporal_ZonedDateTime, withDayOfMonth);
ZEND_METHOD(Temporal_ZonedDateTime, getMonthDay);
ZEND_METHOD(Temporal_ZonedDateTime, getDayOfYear);
ZEND_METHOD(Temporal_ZonedDateTime, getDayOfWeek);
ZEND_METHOD(Temporal_ZonedDateTime, getDaysInMonth);
ZEND_METHOD(Temporal_ZonedDateTime, getDaysInYear);
ZEND_METHOD(Temporal_ZonedDateTime, getWeeksInYear);
ZEND_METHOD(Temporal_ZonedDateTime, isLeapYear);
ZEND_METHOD(Temporal_ZonedDateTime, getTime);
ZEND_METHOD(Temporal_ZonedDateTime, withTime);
ZEND_METHOD(Temporal_ZonedDateTime, getHour);
ZEND_METHOD(Temporal_ZonedDateTime, withHour);
ZEND_METHOD(Temporal_ZonedDateTime, getMinute);
ZEND_METHOD(Temporal_ZonedDateTime, withMinute);
ZEND_METHOD(Temporal_ZonedDateTime, getSecond);
ZEND_METHOD(Temporal_ZonedDateTime, withSecond);
ZEND_METHOD(Temporal_ZonedDateTime, getNano);
ZEND_METHOD(Temporal_ZonedDateTime, withNano);
ZEND_METHOD(Temporal_ZonedDateTime, getInstant);
ZEND_METHOD(Temporal_ZonedDateTime, getTimeZone);
ZEND_METHOD(Temporal_ZonedDateTime, getTimeZoneOffset);
ZEND_METHOD(Temporal_ZonedDateTime, withTimeZoneSameLocal);
ZEND_METHOD(Temporal_ZonedDateTime, withTimeZoneSameInstant);
ZEND_METHOD(Temporal_ZonedDateTime, withFixedOffsetTimeZone);
ZEND_METHOD(Temporal_ZonedDateTime, plusPeriod);
ZEND_METHOD(Temporal_ZonedDateTime, plusYears);
ZEND_METHOD(Temporal_ZonedDateTime, plusMonths);
ZEND_METHOD(Temporal_ZonedDateTime, plusWeeks);
ZEND_METHOD(Temporal_ZonedDateTime, plusDays);
ZEND_METHOD(Temporal_ZonedDateTime, minusPeriod);
ZEND_METHOD(Temporal_ZonedDateTime, minusYears);
ZEND_METHOD(Temporal_ZonedDateTime, minusMonths);
ZEND_METHOD(Temporal_ZonedDateTime, minusWeeks);
ZEND_METHOD(Temporal_ZonedDateTime, minusDays);
ZEND_METHOD(Temporal_ZonedDateTime, plusDuration);
ZEND_METHOD(Temporal_ZonedDateTime, plusHours);
ZEND_METHOD(Temporal_ZonedDateTime, plusMinutes);
ZEND_METHOD(Temporal_ZonedDateTime, plusSeconds);
ZEND_METHOD(Temporal_ZonedDateTime, plusNanos);
ZEND_METHOD(Temporal_ZonedDateTime, minusDuration);
ZEND_METHOD(Temporal_ZonedDateTime, minusHours);
ZEND_METHOD(Temporal_ZonedDateTime, minusMinutes);
ZEND_METHOD(Temporal_ZonedDateTime, minusSeconds);
ZEND_METHOD(Temporal_ZonedDateTime, minusNanos);
ZEND_METHOD(Temporal_ZonedDateTime, compareTo);
ZEND_METHOD(Temporal_ZonedDateTime, isEqualTo);
ZEND_METHOD(Temporal_ZonedDateTime, isBefore);
ZEND_METHOD(Temporal_ZonedDateTime, isBeforeOrEqualTo);
ZEND_METHOD(Temporal_ZonedDateTime, isAfter);
ZEND_METHOD(Temporal_ZonedDateTime, isAfterOrEqualTo);
ZEND_METHOD(Temporal_ZonedDateTime, toDateTime);
ZEND_METHOD(Temporal_ZonedDateTime, fromDateTime);
ZEND_METHOD(Temporal_ZonedDateTime, toISOString);
ZEND_METHOD(Temporal_ZonedDateTime, format);
ZEND_METHOD(Temporal_ZonedDateTime, formatWith);
ZEND_METHOD(Temporal_ZonedDateTime, jsonSerialize);
ZEND_METHOD(Temporal_ZonedDateTime, __toString);
ZEND_METHOD(Temporal_ZonedDateTime, __serialize);
ZEND_METHOD(Temporal_ZonedDateTime, __unserialize);

static const zend_function_entry class_Temporal_ZonedDateTime_methods[] = {
	ZEND_ME(Temporal_ZonedDateTime, __construct, arginfo_class_Temporal_ZonedDateTime___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(Temporal_ZonedDateTime, of, arginfo_class_Temporal_ZonedDateTime_of, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_ZonedDateTime, ofInstant, arginfo_class_Temporal_ZonedDateTime_ofInstant, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_ZonedDateTime, now, arginfo_class_Temporal_ZonedDateTime_now, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_ZonedDateTime, fromISOString, arginfo_class_Temporal_ZonedDateTime_fromISOString, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_ZonedDateTime, getDateTime, arginfo_class_Temporal_ZonedDateTime_getDateTime, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, getDate, arginfo_class_Temporal_ZonedDateTime_getDate, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, withDate, arginfo_class_Temporal_ZonedDateTime_withDate, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, getYear, arginfo_class_Temporal_ZonedDateTime_getYear, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, withYear, arginfo_class_Temporal_ZonedDateTime_withYear, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, getMonth, arginfo_class_Temporal_ZonedDateTime_getMonth, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, withMonth, arginfo_class_Temporal_ZonedDateTime_withMonth, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, getYearMonth, arginfo_class_Temporal_ZonedDateTime_getYearMonth, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, getWeek, arginfo_class_Temporal_ZonedDateTime_getWeek, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, getYearOfWeek, arginfo_class_Temporal_ZonedDateTime_getYearOfWeek, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, getYearWeek, arginfo_class_Temporal_ZonedDateTime_getYearWeek, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, getDayOfMonth, arginfo_class_Temporal_ZonedDateTime_getDayOfMonth, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, withDayOfMonth, arginfo_class_Temporal_ZonedDateTime_withDayOfMonth, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, getMonthDay, arginfo_class_Temporal_ZonedDateTime_getMonthDay, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, getDayOfYear, arginfo_class_Temporal_ZonedDateTime_getDayOfYear, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, getDayOfWeek, arginfo_class_Temporal_ZonedDateTime_getDayOfWeek, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, getDaysInMonth, arginfo_class_Temporal_ZonedDateTime_getDaysInMonth, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, getDaysInYear, arginfo_class_Temporal_ZonedDateTime_getDaysInYear, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, getWeeksInYear, arginfo_class_Temporal_ZonedDateTime_getWeeksInYear, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, isLeapYear, arginfo_class_Temporal_ZonedDateTime_isLeapYear, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, getTime, arginfo_class_Temporal_ZonedDateTime_getTime, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, withTime, arginfo_class_Temporal_ZonedDateTime_withTime, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, getHour, arginfo_class_Temporal_ZonedDateTime_getHour, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, withHour, arginfo_class_Temporal_ZonedDateTime_withHour, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, getMinute, arginfo_class_Temporal_ZonedDateTime_getMinute, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, withMinute, arginfo_class_Temporal_ZonedDateTime_withMinute, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, getSecond, arginfo_class_Temporal_ZonedDateTime_getSecond, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, withSecond, arginfo_class_Temporal_ZonedDateTime_withSecond, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, getNano, arginfo_class_Temporal_ZonedDateTime_getNano, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, withNano, arginfo_class_Temporal_ZonedDateTime_withNano, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, getInstant, arginfo_class_Temporal_ZonedDateTime_getInstant, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, getTimeZone, arginfo_class_Temporal_ZonedDateTime_getTimeZone, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, getTimeZoneOffset, arginfo_class_Temporal_ZonedDateTime_getTimeZoneOffset, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, withTimeZoneSameLocal, arginfo_class_Temporal_ZonedDateTime_withTimeZoneSameLocal, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, withTimeZoneSameInstant, arginfo_class_Temporal_ZonedDateTime_withTimeZoneSameInstant, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, withFixedOffsetTimeZone, arginfo_class_Temporal_ZonedDateTime_withFixedOffsetTimeZone, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, plusPeriod, arginfo_class_Temporal_ZonedDateTime_plusPeriod, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, plusYears, arginfo_class_Temporal_ZonedDateTime_plusYears, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, plusMonths, arginfo_class_Temporal_ZonedDateTime_plusMonths, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, plusWeeks, arginfo_class_Temporal_ZonedDateTime_plusWeeks, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, plusDays, arginfo_class_Temporal_ZonedDateTime_plusDays, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, minusPeriod, arginfo_class_Temporal_ZonedDateTime_minusPeriod, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, minusYears, arginfo_class_Temporal_ZonedDateTime_minusYears, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, minusMonths, arginfo_class_Temporal_ZonedDateTime_minusMonths, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, minusWeeks, arginfo_class_Temporal_ZonedDateTime_minusWeeks, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, minusDays, arginfo_class_Temporal_ZonedDateTime_minusDays, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, plusDuration, arginfo_class_Temporal_ZonedDateTime_plusDuration, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, plusHours, arginfo_class_Temporal_ZonedDateTime_plusHours, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, plusMinutes, arginfo_class_Temporal_ZonedDateTime_plusMinutes, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, plusSeconds, arginfo_class_Temporal_ZonedDateTime_plusSeconds, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, plusNanos, arginfo_class_Temporal_ZonedDateTime_plusNanos, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, minusDuration, arginfo_class_Temporal_ZonedDateTime_minusDuration, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, minusHours, arginfo_class_Temporal_ZonedDateTime_minusHours, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, minusMinutes, arginfo_class_Temporal_ZonedDateTime_minusMinutes, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, minusSeconds, arginfo_class_Temporal_ZonedDateTime_minusSeconds, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, minusNanos, arginfo_class_Temporal_ZonedDateTime_minusNanos, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, compareTo, arginfo_class_Temporal_ZonedDateTime_compareTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, isEqualTo, arginfo_class_Temporal_ZonedDateTime_isEqualTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, isBefore, arginfo_class_Temporal_ZonedDateTime_isBefore, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, isBeforeOrEqualTo, arginfo_class_Temporal_ZonedDateTime_isBeforeOrEqualTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, isAfter, arginfo_class_Temporal_ZonedDateTime_isAfter, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, isAfterOrEqualTo, arginfo_class_Temporal_ZonedDateTime_isAfterOrEqualTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, toDateTime, arginfo_class_Temporal_ZonedDateTime_toDateTime, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, fromDateTime, arginfo_class_Temporal_ZonedDateTime_fromDateTime, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_ZonedDateTime, toISOString, arginfo_class_Temporal_ZonedDateTime_toISOString, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, format, arginfo_class_Temporal_ZonedDateTime_format, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, formatWith, arginfo_class_Temporal_ZonedDateTime_formatWith, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, jsonSerialize, arginfo_class_Temporal_ZonedDateTime_jsonSerialize, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, __toString, arginfo_class_Temporal_ZonedDateTime___toString, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, __serialize, arginfo_class_Temporal_ZonedDateTime___serialize, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_ZonedDateTime, __unserialize, arginfo_class_Temporal_ZonedDateTime___unserialize, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_Temporal_ZonedDateTime(zend_class_entry *class_entry_JsonSerializable, zend_class_entry *class_entry_Stringable)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Temporal", "ZonedDateTime", class_Temporal_ZonedDateTime_methods);
#if (PHP_VERSION_ID >= 80400)
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);
#else
	class_entry = zend_register_internal_class_ex(&ce, NULL);
	class_entry->ce_flags |= ZEND_ACC_FINAL;
#endif
	zend_class_implements(class_entry, 2, class_entry_JsonSerializable, class_entry_Stringable);

	return class_entry;
}
