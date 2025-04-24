#include "local_date_ce.h"
#include <ext/date/php_date.h>
#include <ext/json/php_json.h>
#include <php.h>
#include <unicode/udat.h>
#include <zend_interfaces.h>
#include <zend_smart_str.h>
#include "local_date.h"
#include "local_date_arginfo.h"
#include "local_date_handlers.h"
#include "local_date_obj.h"
#include "clock/clock_ce.h"
#include "exception/exception_obj.h"
#include "format/formatter.h"
#include "format/formatter_ce.h"
#include "format/formatter_obj.h"
#include "local_date_time/local_date_time.h"
#include "local_date_time/local_date_time_obj.h"
#include "local_time/local_time.h"
#include "local_time/local_time_ce.h"
#include "local_time/local_time_obj.h"
#include "month_day/month_day.h"
#include "month_day/month_day_obj.h"
#include "period/period.h"
#include "period/period_ce.h"
#include "period/period_obj.h"
#include "time_zone/time_zone_ce.h"
#include "time_zone/time_zone_obj.h"
#include "utils/check_range.h"
#include "utils/iso_calendar.h"
#include "year_month/year_month.h"
#include "year_month/year_month_obj.h"
#include "year_week/year_week.h"
#include "year_week/year_week_obj.h"
#include "zoned_date_time/zoned_date_time.h"

ZEND_METHOD(Temporal_LocalDate, __construct) {
	// private
}

ZEND_METHOD(Temporal_LocalDate, of) {
	zend_long year, month, day;

	ZEND_PARSE_PARAMETERS_START(3, 3)
	Z_PARAM_LONG(year)
	Z_PARAM_LONG(month)
	Z_PARAM_LONG(day)
	ZEND_PARSE_PARAMETERS_END();

	TEMPORAL_CHECK_VALUE_RANGE("year", year, -999999, 999999);
	TEMPORAL_CHECK_VALUE_RANGE("month", month, 1, 12);

	zend_long max_day = days_in_month(year, month);
	TEMPORAL_CHECK_VALUE_RANGE("day", day, 1, max_day);

	temporal_local_date_t *local_date = temporal_local_date_of(year, month, day);
	zend_object *object = php_temporal_local_date_create_object_ex(local_date);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDate, ofDayOfYear) {
	zend_long year, day_of_year;

	ZEND_PARSE_PARAMETERS_START(2, 2)
	Z_PARAM_LONG(year)
	Z_PARAM_LONG(day_of_year)
	ZEND_PARSE_PARAMETERS_END();

	TEMPORAL_CHECK_VALUE_RANGE("year", year, -999999, 999999);

	zend_long max_day = days_in_year(year);
	TEMPORAL_CHECK_VALUE_RANGE("dayOfYear", day_of_year, 1, max_day);

	temporal_local_date_t *local_date = temporal_local_date_of_day_of_year(year, day_of_year);
	zend_object *object = php_temporal_local_date_create_object_ex(local_date);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDate, ofEpochDay) {
	zend_long epoch_day;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(epoch_day)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *local_date = temporal_local_date_of_epoch_day(epoch_day);
	zend_object *object = php_temporal_local_date_create_object_ex(local_date);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDate, now) {
	zval *time_zone;
	zend_object *clock = NULL;

	ZEND_PARSE_PARAMETERS_START(1, 2)
	Z_PARAM_OBJECT_OF_CLASS(time_zone, php_temporal_time_zone_ce)
	Z_PARAM_OPTIONAL
	Z_PARAM_OBJ_OF_CLASS_OR_NULL(clock, php_temporal_clock_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_now(Z_TEMPORAL_TIME_ZONE_INTERNAL_P(time_zone), clock);
	temporal_local_date_t *local_date = temporal_local_date_clone(zoned_date_time->date_time->date);

	temporal_zoned_date_time_free(zoned_date_time);

	zend_object *object = php_temporal_local_date_create_object_ex(local_date);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDate, parse) {
	zend_string *input;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_STR(input)
	ZEND_PARSE_PARAMETERS_END();

	const char *input_s = ZSTR_VAL(input);

	temporal_local_date_t *local_date = temporal_local_date_parse_iso(input_s);
	if (local_date == NULL) {
		php_temporal_throw_exception("Failed to parse given input into a Temporal value.", 0);
		RETURN_THROWS();
	}

	zend_object *object = php_temporal_local_date_create_object_ex(local_date);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDate, min) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_date_t *local_date = temporal_local_date_of(-999999, 1, 1);
	zend_object *object = php_temporal_local_date_create_object_ex(local_date);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDate, max) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_date_t *local_date = temporal_local_date_of(999999, 12, 31);
	zend_object *object = php_temporal_local_date_create_object_ex(local_date);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDate, getYear) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long year = THIS_TEMPORAL_LOCAL_DATE_INTERNAL()->year;
	RETURN_LONG(year);
}

ZEND_METHOD(Temporal_LocalDate, withYear) {
	zend_long year;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(year)
	ZEND_PARSE_PARAMETERS_END();

	TEMPORAL_CHECK_VALUE_RANGE("year", year, -999999, 999999);

	temporal_local_date_t *local_date = temporal_local_date_of(year, THIS_TEMPORAL_LOCAL_DATE_INTERNAL()->month, THIS_TEMPORAL_LOCAL_DATE_INTERNAL()->day);
	zend_object *object = php_temporal_local_date_create_object_ex(local_date);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDate, getMonth) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long month = THIS_TEMPORAL_LOCAL_DATE_INTERNAL()->month;
	RETURN_LONG(month);
}

ZEND_METHOD(Temporal_LocalDate, withMonth) {
	zend_long month;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(month)
	ZEND_PARSE_PARAMETERS_END();

	TEMPORAL_CHECK_VALUE_RANGE("month", month, 1, 12);

	zend_long day = THIS_TEMPORAL_LOCAL_DATE_INTERNAL()->day;
	zend_long max_day = days_in_month(THIS_TEMPORAL_LOCAL_DATE_INTERNAL()->year, month);
	if (day > max_day) {
		day = max_day;
	}

	temporal_local_date_t *local_date = temporal_local_date_of(THIS_TEMPORAL_LOCAL_DATE_INTERNAL()->year, month, day);
	zend_object *object = php_temporal_local_date_create_object_ex(local_date);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDate, getYearMonth) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_year_month_t *year_month = temporal_year_month_of(THIS_TEMPORAL_LOCAL_DATE_INTERNAL()->year, THIS_TEMPORAL_LOCAL_DATE_INTERNAL()->month);
	zend_object *object = php_temporal_year_month_create_object_ex(year_month);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDate, getWeek) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_year_week_t *year_week = temporal_year_week_of_date(THIS_TEMPORAL_LOCAL_DATE_INTERNAL());
	zend_long week = year_week->week;
	temporal_year_week_free(year_week);

	RETURN_LONG(week);
}

ZEND_METHOD(Temporal_LocalDate, getYearOfWeek) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_year_week_t *year_week = temporal_year_week_of_date(THIS_TEMPORAL_LOCAL_DATE_INTERNAL());
	zend_long year = year_week->year;
	temporal_year_week_free(year_week);

	RETURN_LONG(year);
}

ZEND_METHOD(Temporal_LocalDate, getYearWeek) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_year_week_t *year_week = temporal_year_week_of_date(THIS_TEMPORAL_LOCAL_DATE_INTERNAL());
	zend_object *object = php_temporal_year_week_create_object_ex(year_week);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDate, getDayOfMonth) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long day = THIS_TEMPORAL_LOCAL_DATE_INTERNAL()->day;
	RETURN_LONG(day);
}

ZEND_METHOD(Temporal_LocalDate, withDayOfMonth) {
	zend_long day;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(day)
	ZEND_PARSE_PARAMETERS_END();

	zend_long max_day = days_in_month(THIS_TEMPORAL_LOCAL_DATE_INTERNAL()->year, THIS_TEMPORAL_LOCAL_DATE_INTERNAL()->month);
	TEMPORAL_CHECK_VALUE_RANGE("dayOfMonth", day, 1, max_day);

	temporal_local_date_t *local_date = temporal_local_date_of(THIS_TEMPORAL_LOCAL_DATE_INTERNAL()->year, THIS_TEMPORAL_LOCAL_DATE_INTERNAL()->month, day);
	zend_object *object = php_temporal_local_date_create_object_ex(local_date);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDate, getMonthDay) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_month_day_t *month_day = temporal_month_day_of(THIS_TEMPORAL_LOCAL_DATE_INTERNAL()->month, THIS_TEMPORAL_LOCAL_DATE_INTERNAL()->day);
	zend_object *object = php_temporal_month_day_create_object_ex(month_day);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDate, getDayOfYear) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long day_of_year = temporal_local_date_day_of_year(THIS_TEMPORAL_LOCAL_DATE_INTERNAL());
	RETURN_LONG(day_of_year);
}

ZEND_METHOD(Temporal_LocalDate, getDayOfWeek) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long day_of_week = temporal_local_date_day_of_week(THIS_TEMPORAL_LOCAL_DATE_INTERNAL());
	RETURN_LONG(day_of_week);
}

ZEND_METHOD(Temporal_LocalDate, getDaysInMonth) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long days = days_in_month(THIS_TEMPORAL_LOCAL_DATE_INTERNAL()->year, THIS_TEMPORAL_LOCAL_DATE_INTERNAL()->month);
	RETURN_LONG(days);
}

ZEND_METHOD(Temporal_LocalDate, getDaysInYear) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long days = days_in_year(THIS_TEMPORAL_LOCAL_DATE_INTERNAL()->year);
	RETURN_LONG(days);
}

ZEND_METHOD(Temporal_LocalDate, getWeeksInYear) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long weeks = weeks_in_year(THIS_TEMPORAL_LOCAL_DATE_INTERNAL()->year);
	RETURN_LONG(weeks);
}

ZEND_METHOD(Temporal_LocalDate, isLeapYear) {
	ZEND_PARSE_PARAMETERS_NONE();
	bool result = is_leap_year(THIS_TEMPORAL_LOCAL_DATE_INTERNAL()->year);
	RETURN_BOOL(result);
}

ZEND_METHOD(Temporal_LocalDate, toEpochDay) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long epoch_day = temporal_local_date_to_epoch_day(THIS_TEMPORAL_LOCAL_DATE_INTERNAL());
	RETURN_LONG(epoch_day);
}

ZEND_METHOD(Temporal_LocalDate, plus) {
	zval *period;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(period, php_temporal_period_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *y = temporal_local_date_plus_years(THIS_TEMPORAL_LOCAL_DATE_INTERNAL(), Z_TEMPORAL_PERIOD_INTERNAL_P(period)->years);
	temporal_local_date_t *m = temporal_local_date_plus_months(y, Z_TEMPORAL_PERIOD_INTERNAL_P(period)->months);
	temporal_local_date_t *local_date = temporal_local_date_plus_days(m, Z_TEMPORAL_PERIOD_INTERNAL_P(period)->days);

	temporal_local_date_free(y);
	temporal_local_date_free(m);

	zend_object *object = php_temporal_local_date_create_object_ex(local_date);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDate, plusYears) {
	zend_long years;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(years)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *local_date = temporal_local_date_plus_years(THIS_TEMPORAL_LOCAL_DATE_INTERNAL(), years);
	zend_object *object = php_temporal_local_date_create_object_ex(local_date);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDate, plusMonths) {
	zend_long months;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(months)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *local_date = temporal_local_date_plus_months(THIS_TEMPORAL_LOCAL_DATE_INTERNAL(), months);
	zend_object *object = php_temporal_local_date_create_object_ex(local_date);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDate, plusWeeks) {
	zend_long weeks;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(weeks)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *local_date = temporal_local_date_plus_days(THIS_TEMPORAL_LOCAL_DATE_INTERNAL(), weeks * 7);
	zend_object *object = php_temporal_local_date_create_object_ex(local_date);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDate, plusDays) {
	zend_long days;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(days)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *local_date = temporal_local_date_plus_days(THIS_TEMPORAL_LOCAL_DATE_INTERNAL(), days);
	zend_object *object = php_temporal_local_date_create_object_ex(local_date);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDate, minus) {
	zval *period;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(period, php_temporal_period_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *y = temporal_local_date_plus_years(THIS_TEMPORAL_LOCAL_DATE_INTERNAL(), Z_TEMPORAL_PERIOD_INTERNAL_P(period)->years * -1);
	temporal_local_date_t *m = temporal_local_date_plus_months(y, Z_TEMPORAL_PERIOD_INTERNAL_P(period)->months * -1);
	temporal_local_date_t *local_date = temporal_local_date_plus_days(m, Z_TEMPORAL_PERIOD_INTERNAL_P(period)->days * -1);

	temporal_local_date_free(y);
	temporal_local_date_free(m);

	zend_object *object = php_temporal_local_date_create_object_ex(local_date);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDate, minusYears) {
	zend_long years;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(years)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *local_date = temporal_local_date_plus_years(THIS_TEMPORAL_LOCAL_DATE_INTERNAL(), -years);
	zend_object *object = php_temporal_local_date_create_object_ex(local_date);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDate, minusMonths) {
	zend_long months;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(months)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *local_date = temporal_local_date_plus_months(THIS_TEMPORAL_LOCAL_DATE_INTERNAL(), -months);
	zend_object *object = php_temporal_local_date_create_object_ex(local_date);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDate, minusWeeks) {
	zend_long weeks;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(weeks)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *local_date = temporal_local_date_plus_days(THIS_TEMPORAL_LOCAL_DATE_INTERNAL(), -weeks * 7);
	zend_object *object = php_temporal_local_date_create_object_ex(local_date);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDate, minusDays) {
	zend_long days;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(days)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *local_date = temporal_local_date_plus_days(THIS_TEMPORAL_LOCAL_DATE_INTERNAL(), -days);
	zend_object *object = php_temporal_local_date_create_object_ex(local_date);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDate, until) {
	zend_object *other;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJ_OF_CLASS(other, php_temporal_local_date_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *start = THIS_TEMPORAL_LOCAL_DATE_INTERNAL();
	temporal_local_date_t *end_exclusive = php_temporal_local_date_from_object(other)->local_date;

	temporal_period_t *period = temporal_period_between(start, end_exclusive);
	zend_object *object = php_temporal_period_create_object_ex(period);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDate, daysUntil) {
	zend_object *other;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJ_OF_CLASS(other, php_temporal_local_date_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *a = THIS_TEMPORAL_LOCAL_DATE_INTERNAL();
	temporal_local_date_t *b = php_temporal_local_date_from_object(other)->local_date;

	zend_long result = temporal_local_date_to_epoch_day(b) - temporal_local_date_to_epoch_day(a);
	RETURN_LONG(result);
}

ZEND_METHOD(Temporal_LocalDate, atTime) {
	zval *time;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(time, php_temporal_local_time_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *local_date = THIS_TEMPORAL_LOCAL_DATE_INTERNAL();
	temporal_local_time_t *local_time = temporal_local_time_clone(Z_TEMPORAL_LOCAL_TIME_INTERNAL_P(time));

	temporal_local_date_time_t *date_time = temporal_local_date_time_of_date_time(local_date, local_time);
	zend_object *object = php_temporal_local_date_time_create_object_ex(date_time);
	RETURN_OBJ(object);
}

#define TEMPORAL_LOCAL_DATE_COMPARE                                                    \
	zend_object *other;                                                                \
	ZEND_PARSE_PARAMETERS_START(1, 1)                                                  \
	Z_PARAM_OBJ_OF_CLASS(other, php_temporal_local_date_ce)                            \
	ZEND_PARSE_PARAMETERS_END();                                                       \
	temporal_local_date_t *a = THIS_TEMPORAL_LOCAL_DATE_INTERNAL();                    \
	temporal_local_date_t *b = php_temporal_local_date_from_object(other)->local_date; \
	int result = temporal_local_date_compare(a, b);

ZEND_METHOD(Temporal_LocalDate, compareTo) {
	TEMPORAL_LOCAL_DATE_COMPARE
	RETURN_LONG(result);
}

ZEND_METHOD(Temporal_LocalDate, isEqualTo) {
	TEMPORAL_LOCAL_DATE_COMPARE
	RETURN_BOOL(result == 0);
}

ZEND_METHOD(Temporal_LocalDate, isBefore) {
	TEMPORAL_LOCAL_DATE_COMPARE
	RETURN_BOOL(result < 0);
}

ZEND_METHOD(Temporal_LocalDate, isBeforeOrEqualTo) {
	TEMPORAL_LOCAL_DATE_COMPARE
	RETURN_BOOL(result <= 0);
}

ZEND_METHOD(Temporal_LocalDate, isAfter) {
	TEMPORAL_LOCAL_DATE_COMPARE
	RETURN_BOOL(result > 0);
}

ZEND_METHOD(Temporal_LocalDate, isAfterOrEqualTo) {
	TEMPORAL_LOCAL_DATE_COMPARE
	RETURN_BOOL(result >= 0);
}

ZEND_METHOD(Temporal_LocalDate, toDateTime) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_date_t *local_date = THIS_TEMPORAL_LOCAL_DATE_INTERNAL();

	smart_str buf_f = {0};
	smart_str_appends(&buf_f, "Y-m-d\\TH:i:s.u");

	smart_str buf_t = {0};

	char year_str[7];
	snprintf(year_str, sizeof(year_str), "%04lld", local_date->year);
	smart_str_appends(&buf_t, year_str);
	smart_str_appendc(&buf_t, '-');

	char month_str[7];
	snprintf(month_str, sizeof(month_str), "%02lld", local_date->month);
	smart_str_appends(&buf_t, month_str);
	smart_str_appendc(&buf_t, '-');

	char day_str[7];
	snprintf(day_str, sizeof(day_str), "%02lld", local_date->day);
	smart_str_appends(&buf_t, day_str);

	smart_str_appends(&buf_f, " e");
	smart_str_appends(&buf_t, "T00:00:00.000000 UTC");

	zend_string *format = smart_str_extract(&buf_f);
	zend_string *value = smart_str_extract(&buf_t);

	php_date_instantiate(php_date_get_immutable_ce(), return_value);
	if (!php_date_initialize(Z_PHPDATE_P(return_value), ZSTR_VAL(value), ZSTR_LEN(value), ZSTR_VAL(format), NULL, PHP_DATE_INIT_FORMAT)) {
		zend_string_release_ex(format, 0);
		zend_string_release_ex(value, 0);

		php_temporal_throw_exception("Failed to convert LocalDate into DateTimeImmutable.", 0);
		RETURN_THROWS();
	}

	zend_string_release_ex(format, 0);
	zend_string_release_ex(value, 0);
}

ZEND_METHOD(Temporal_LocalDate, fromDateTime) {
	zval *date;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(date, php_date_get_interface_ce())
	ZEND_PARSE_PARAMETERS_END();

	php_date_obj *date_obj = Z_PHPDATE_P(date);
	temporal_local_date_t *local_date = temporal_local_date_of(date_obj->time->y, date_obj->time->m, date_obj->time->d);
	zend_object *object = php_temporal_local_date_create_object_ex(local_date);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDate, toISOString) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_string *str = temporal_local_date_format_iso(THIS_TEMPORAL_LOCAL_DATE_INTERNAL());
	RETURN_STR(str);
}

ZEND_METHOD(Temporal_LocalDate, format) {
	zend_string *pattern, *locale = NULL;

	ZEND_PARSE_PARAMETERS_START(1, 2)
	Z_PARAM_STR(pattern)
	Z_PARAM_OPTIONAL
	Z_PARAM_STR_OR_NULL(locale)
	ZEND_PARSE_PARAMETERS_END();

	UErrorCode status = U_ZERO_ERROR;
	UDateFormat *formatter = temporal_formatter_of_localized_pattern(ZSTR_VAL(pattern), locale != NULL ? ZSTR_VAL(locale) : NULL, &status);
	if (U_FAILURE(status)) {
		php_temporal_throw_exception("Failed to format a Temporal value.", 0);
		RETURN_THROWS();
	}

	zend_string *formatted = temporal_local_date_format(THIS_TEMPORAL_LOCAL_DATE_INTERNAL(), formatter);

	if (formatted == NULL) {
		RETURN_THROWS();
	}

	RETURN_STR(formatted);
}

ZEND_METHOD(Temporal_LocalDate, formatWith) {
	zval *formatter;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(formatter, php_temporal_formatter_ce)
	ZEND_PARSE_PARAMETERS_END();

	zend_string *formatted = temporal_local_date_format(
		THIS_TEMPORAL_LOCAL_DATE_INTERNAL(),
		Z_TEMPORAL_FORMATTER_INTERNAL_P(formatter)
	);

	if (formatted == NULL) {
		RETURN_THROWS();
	}

	RETURN_STR(formatted);
}

ZEND_METHOD(Temporal_LocalDate, jsonSerialize) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_string *str = temporal_local_date_format_iso(THIS_TEMPORAL_LOCAL_DATE_INTERNAL());
	RETURN_STR(str);
}

ZEND_METHOD(Temporal_LocalDate, __toString) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_string *str = temporal_local_date_format_iso(THIS_TEMPORAL_LOCAL_DATE_INTERNAL());
	RETURN_STR(str);
}

ZEND_METHOD(Temporal_LocalDate, __serialize) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_date_t *local_date = THIS_TEMPORAL_LOCAL_DATE_INTERNAL();

	array_init(return_value);
	HashTable *ht = Z_ARRVAL_P(return_value);

	zval tmp;

	ZVAL_LONG(&tmp, local_date->year);
	zend_hash_str_update(ht, "year", strlen("year"), &tmp);

	ZVAL_LONG(&tmp, local_date->month);
	zend_hash_str_update(ht, "month", strlen("month"), &tmp);

	ZVAL_LONG(&tmp, local_date->day);
	zend_hash_str_update(ht, "day", strlen("day"), &tmp);
}

ZEND_METHOD(Temporal_LocalDate, __unserialize) {
	HashTable *ht;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_ARRAY_HT(ht)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *local_date = THIS_TEMPORAL_LOCAL_DATE_INTERNAL();

	zval *year = zend_hash_str_find(ht, "year", strlen("year"));
	if (year == NULL || Z_TYPE_P(year) != IS_LONG) {
		php_temporal_throw_exception("Failed to unserialize Temporal value from data.", 0);
		RETURN_THROWS();
	}

	zval *month = zend_hash_str_find(ht, "month", strlen("month"));
	if (month == NULL || Z_TYPE_P(month) != IS_LONG) {
		php_temporal_throw_exception("Failed to unserialize Temporal value from data.", 0);
		RETURN_THROWS();
	}

	zval *day = zend_hash_str_find(ht, "day", strlen("day"));
	if (day == NULL || Z_TYPE_P(day) != IS_LONG) {
		php_temporal_throw_exception("Failed to unserialize Temporal value from data.", 0);
		RETURN_THROWS();
	}

	local_date->year = Z_LVAL_P(year);
	local_date->month = Z_LVAL_P(month);
	local_date->day = Z_LVAL_P(day);
}

zend_class_entry *php_temporal_local_date_ce;

void php_temporal_register_local_date_ce() {
	php_temporal_local_date_ce = register_class_Temporal_LocalDate(php_json_serializable_ce, zend_ce_stringable);
	php_temporal_local_date_ce->create_object = php_temporal_local_date_create_object;

	php_temporal_register_local_date_handlers();
}
