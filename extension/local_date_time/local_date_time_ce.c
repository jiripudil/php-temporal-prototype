#include "local_date_time_ce.h"
#include <ext/date/php_date.h>
#include <ext/json/php_json.h>
#include <php.h>
#include <zoned_date_time/zoned_date_time_obj.h>
#include <unicode/udat.h>
#include <zend_interfaces.h>
#include <zend_smart_str.h>

#include "local_date_time.h"
#include "local_date_time_arginfo.h"
#include "local_date_time_handlers.h"
#include "local_date_time_obj.h"
#include "clock/clock_ce.h"
#include "duration/duration.h"
#include "duration/duration_ce.h"
#include "duration/duration_obj.h"
#include "exception/exception_obj.h"
#include "format/formatter.h"
#include "format/formatter_ce.h"
#include "format/formatter_obj.h"
#include "local_date/local_date_ce.h"
#include "local_date/local_date_obj.h"
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

ZEND_METHOD(Temporal_LocalDateTime, __construct) {
	// private
}

ZEND_METHOD(Temporal_LocalDateTime, of) {
	zend_long year, month, day, hour = 0, minute = 0, second = 0, nano = 0;

	ZEND_PARSE_PARAMETERS_START(3, 7)
	Z_PARAM_LONG(year)
	Z_PARAM_LONG(month)
	Z_PARAM_LONG(day)
	Z_PARAM_OPTIONAL
	Z_PARAM_LONG(hour)
	Z_PARAM_LONG(minute)
	Z_PARAM_LONG(second)
	Z_PARAM_LONG(nano)
	ZEND_PARSE_PARAMETERS_END();

	TEMPORAL_CHECK_VALUE_RANGE("year", year, -999999, 999999);
	TEMPORAL_CHECK_VALUE_RANGE("month", month, 1, 12);

	zend_long max_day = days_in_month(year, month);
	TEMPORAL_CHECK_VALUE_RANGE("day", day, 1, max_day);

	TEMPORAL_CHECK_VALUE_RANGE("hour", hour, 0, HOURS_PER_DAY - 1);
	TEMPORAL_CHECK_VALUE_RANGE("minute", minute, 0, MINUTES_PER_HOUR - 1);
	TEMPORAL_CHECK_VALUE_RANGE("second", second, 0, SECONDS_PER_MINUTE - 1);
	TEMPORAL_CHECK_VALUE_RANGE("nano", nano, 0, NANOS_PER_SECOND - 1);

	temporal_local_date_time_t *date_time = temporal_local_date_time_of(year, month, day, hour, minute, second, nano);
	zend_object *object = php_temporal_local_date_time_create_object_ex(date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, ofDateTime) {
	zval *date, *time;

	ZEND_PARSE_PARAMETERS_START(2, 2)
	Z_PARAM_OBJECT_OF_CLASS(date, php_temporal_local_date_ce)
	Z_PARAM_OBJECT_OF_CLASS(time, php_temporal_local_time_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_time_t *date_time = temporal_local_date_time_of_date_time(
		temporal_local_date_clone(Z_TEMPORAL_LOCAL_DATE_INTERNAL_P(date)),
		temporal_local_time_clone(Z_TEMPORAL_LOCAL_TIME_INTERNAL_P(time))
	);

	zend_object *object = php_temporal_local_date_time_create_object_ex(date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, now) {
	zval *time_zone;
	zend_object *clock = NULL;

	ZEND_PARSE_PARAMETERS_START(1, 2)
	Z_PARAM_OBJECT_OF_CLASS(time_zone, php_temporal_time_zone_ce)
	Z_PARAM_OPTIONAL
	Z_PARAM_OBJ_OF_CLASS_OR_NULL(clock, php_temporal_clock_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_now(temporal_time_zone_clone(Z_TEMPORAL_TIME_ZONE_INTERNAL_P(time_zone)), clock);
	temporal_local_date_time_t *local_date_time = temporal_local_date_time_clone(zoned_date_time->date_time);

	temporal_zoned_date_time_free(zoned_date_time);

	zend_object *object = php_temporal_local_date_time_create_object_ex(local_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, fromISOString) {
	zend_string *input;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_STR(input)
	ZEND_PARSE_PARAMETERS_END();

	const char *input_s = ZSTR_VAL(input);

	temporal_local_date_time_t *local_date_time = temporal_local_date_time_parse_iso(input_s);
	if (local_date_time == NULL) {
		php_temporal_throw_exception("Failed to parse given input into a Temporal value.", 0);
		RETURN_THROWS();
	}

	zend_object *object = php_temporal_local_date_time_create_object_ex(local_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, min) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_date_time_t *local_date_time = temporal_local_date_time_of(-999999, 1, 1, 0, 0, 0, 0);
	zend_object *object = php_temporal_local_date_time_create_object_ex(local_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, max) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_date_time_t *local_date_time = temporal_local_date_time_of(999999, 12, 31, 23, 59, 59, 999999999);
	zend_object *object = php_temporal_local_date_time_create_object_ex(local_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, getDate) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_date_t *date = temporal_local_date_clone(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date);
	zend_object *object = php_temporal_local_date_create_object_ex(date);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, withDate) {
	zval *date;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(date, php_temporal_local_date_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_time_t *copy = temporal_local_date_time_of_date_time(
		temporal_local_date_clone(Z_TEMPORAL_LOCAL_DATE_INTERNAL_P(date)),
		temporal_local_time_clone(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->time)
	);

	zend_object *object = php_temporal_local_date_time_create_object_ex(copy);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, getYear) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_long result = THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date->year;
	RETURN_LONG(result);
}

ZEND_METHOD(Temporal_LocalDateTime, withYear) {
	zend_long year;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(year)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *date = THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date;

	TEMPORAL_CHECK_VALUE_RANGE("year", year, -999999, 999999);

	zend_long day = date->day;
	zend_long max_day = days_in_month(year, date->month);
	if (day > max_day) {
		day = max_day;
	}

	temporal_local_date_time_t *copy = temporal_local_date_time_of_date_time(
		temporal_local_date_of(year, date->month, day),
		temporal_local_time_clone(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->time)
	);

	zend_object *object = php_temporal_local_date_time_create_object_ex(copy);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, getMonth) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_long result = THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date->month;
	RETURN_LONG(result);
}

ZEND_METHOD(Temporal_LocalDateTime, withMonth) {
	zend_long month;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(month)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *date = THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date;

	TEMPORAL_CHECK_VALUE_RANGE("month", month, 1, 12);

	zend_long day = date->day;
	zend_long max_day = days_in_month(date->year, month);
	if (day > max_day) {
		day = max_day;
	}

	temporal_local_date_time_t *copy = temporal_local_date_time_of_date_time(
		temporal_local_date_of(date->year, month, day),
		temporal_local_time_clone(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->time)
	);

	zend_object *object = php_temporal_local_date_time_create_object_ex(copy);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, getYearMonth) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_year_month_t *year_month = temporal_year_month_of(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date->year, THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date->month);
	zend_object *object = php_temporal_year_month_create_object_ex(year_month);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, getWeek) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_year_week_t *year_week = temporal_year_week_of_date(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date);
	zend_long week = year_week->week;
	temporal_year_week_free(year_week);

	RETURN_LONG(week);
}

ZEND_METHOD(Temporal_LocalDateTime, getYearOfWeek) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_year_week_t *year_week = temporal_year_week_of_date(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date);
	zend_long year = year_week->year;
	temporal_year_week_free(year_week);

	RETURN_LONG(year);
}

ZEND_METHOD(Temporal_LocalDateTime, getYearWeek) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_year_week_t *year_week = temporal_year_week_of_date(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date);
	zend_object *object = php_temporal_year_week_create_object_ex(year_week);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, getDayOfMonth) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_long result = THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date->day;
	RETURN_LONG(result);
}

ZEND_METHOD(Temporal_LocalDateTime, withDayOfMonth) {
	zend_long day;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(day)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *date = THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date;

	zend_long max_day = days_in_month(date->year, date->month);
	TEMPORAL_CHECK_VALUE_RANGE("day", day, 1, max_day);

	temporal_local_date_time_t *copy = temporal_local_date_time_of_date_time(
		temporal_local_date_of(date->year, date->month, day),
		temporal_local_time_clone(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->time)
	);

	zend_object *object = php_temporal_local_date_time_create_object_ex(copy);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, getMonthDay) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_month_day_t *month_day = temporal_month_day_of(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date->month, THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date->day);
	zend_object *object = php_temporal_month_day_create_object_ex(month_day);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, getDayOfYear) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long day_of_year = temporal_local_date_day_of_year(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date);
	RETURN_LONG(day_of_year);
}

ZEND_METHOD(Temporal_LocalDateTime, getDayOfWeek) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long day_of_week = temporal_local_date_day_of_week(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date);
	RETURN_LONG(day_of_week);
}

ZEND_METHOD(Temporal_LocalDateTime, getDaysInMonth) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long days = days_in_month(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date->year, THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date->month);
	RETURN_LONG(days);
}

ZEND_METHOD(Temporal_LocalDateTime, getDaysInYear) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long days = days_in_year(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date->year);
	RETURN_LONG(days);
}

ZEND_METHOD(Temporal_LocalDateTime, getWeeksInYear) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long weeks = weeks_in_year(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date->year);
	RETURN_LONG(weeks);
}

ZEND_METHOD(Temporal_LocalDateTime, isLeapYear) {
	ZEND_PARSE_PARAMETERS_NONE();
	bool result = is_leap_year(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date->year);
	RETURN_LONG(result);
}

ZEND_METHOD(Temporal_LocalDateTime, getTime) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_time_t *time = temporal_local_time_clone(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->time);
	zend_object *object = php_temporal_local_time_create_object_ex(time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, withTime) {
	zval *time;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(time, php_temporal_local_time_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_time_t *copy = temporal_local_date_time_of_date_time(
		temporal_local_date_clone(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date),
		temporal_local_time_clone(Z_TEMPORAL_LOCAL_TIME_INTERNAL_P(time))
	);

	zend_object *object = php_temporal_local_date_time_create_object_ex(copy);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, getHour) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_long result = THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->time->hour;
	RETURN_LONG(result);
}

ZEND_METHOD(Temporal_LocalDateTime, withHour) {
	zend_long hour;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(hour)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_time_t *time = THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->time;

	TEMPORAL_CHECK_VALUE_RANGE("hour", hour, 0, HOURS_PER_DAY - 1);

	temporal_local_date_time_t *copy = temporal_local_date_time_of_date_time(
		temporal_local_date_clone(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date),
		temporal_local_time_of(hour, time->minute, time->second, time->nano)
	);

	zend_object *object = php_temporal_local_date_time_create_object_ex(copy);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, getMinute) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_long result = THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->time->minute;
	RETURN_LONG(result);
}

ZEND_METHOD(Temporal_LocalDateTime, withMinute) {
	zend_long minute;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(minute)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_time_t *time = THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->time;

	TEMPORAL_CHECK_VALUE_RANGE("minute", minute, 0, MINUTES_PER_HOUR - 1);

	temporal_local_date_time_t *copy = temporal_local_date_time_of_date_time(
		temporal_local_date_clone(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date),
		temporal_local_time_of(time->hour, minute, time->second, time->nano)
	);

	zend_object *object = php_temporal_local_date_time_create_object_ex(copy);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, getSecond) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_long result = THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->time->second;
	RETURN_LONG(result);
}

ZEND_METHOD(Temporal_LocalDateTime, withSecond) {
	zend_long second;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(second)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_time_t *time = THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->time;

	TEMPORAL_CHECK_VALUE_RANGE("second", second, 0, SECONDS_PER_MINUTE - 1);

	temporal_local_date_time_t *copy = temporal_local_date_time_of_date_time(
		temporal_local_date_clone(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date),
		temporal_local_time_of(time->hour, time->minute, second, time->nano)
	);

	zend_object *object = php_temporal_local_date_time_create_object_ex(copy);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, getNano) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_long result = THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->time->nano;
	RETURN_LONG(result);
}

ZEND_METHOD(Temporal_LocalDateTime, withNano) {
	zend_long nano;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(nano)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_time_t *time = THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->time;

	TEMPORAL_CHECK_VALUE_RANGE("nano", nano, 0, NANOS_PER_SECOND - 1);

	temporal_local_date_time_t *copy = temporal_local_date_time_of_date_time(
		temporal_local_date_clone(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date),
		temporal_local_time_of(time->hour, time->minute, time->second, nano)
	);

	zend_object *object = php_temporal_local_date_time_create_object_ex(copy);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, plusPeriod) {
	zval *period;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(period, php_temporal_period_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *y = temporal_local_date_plus_years(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date, Z_TEMPORAL_PERIOD_INTERNAL_P(period)->years);
	temporal_local_date_t *m = temporal_local_date_plus_months(y, Z_TEMPORAL_PERIOD_INTERNAL_P(period)->months);
	temporal_local_date_t *date = temporal_local_date_plus_days(m, Z_TEMPORAL_PERIOD_INTERNAL_P(period)->days);

	temporal_local_date_free(y);
	temporal_local_date_free(m);

	temporal_local_date_time_t *copy = temporal_local_date_time_of_date_time(date, temporal_local_time_clone(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->time));
	zend_object *object = php_temporal_local_date_time_create_object_ex(copy);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, plusYears) {
	zend_long years;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(years)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *date = temporal_local_date_plus_years(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date, years);
	temporal_local_date_time_t *copy = temporal_local_date_time_of_date_time(date, temporal_local_time_clone(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->time));
	zend_object *object = php_temporal_local_date_time_create_object_ex(copy);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, plusMonths) {
	zend_long months;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(months)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *date = temporal_local_date_plus_months(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date, months);
	temporal_local_date_time_t *copy = temporal_local_date_time_of_date_time(date, temporal_local_time_clone(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->time));
	zend_object *object = php_temporal_local_date_time_create_object_ex(copy);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, plusWeeks) {
	zend_long weeks;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(weeks)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *date = temporal_local_date_plus_days(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date, weeks * 7);
	temporal_local_date_time_t *copy = temporal_local_date_time_of_date_time(date, temporal_local_time_clone(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->time));
	zend_object *object = php_temporal_local_date_time_create_object_ex(copy);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, plusDays) {
	zend_long days;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(days)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *date = temporal_local_date_plus_days(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date, days);
	temporal_local_date_time_t *copy = temporal_local_date_time_of_date_time(date, temporal_local_time_clone(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->time));
	zend_object *object = php_temporal_local_date_time_create_object_ex(copy);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, minusPeriod) {
	zval *period;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(period, php_temporal_period_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *y = temporal_local_date_plus_years(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date, Z_TEMPORAL_PERIOD_INTERNAL_P(period)->years * -1);
	temporal_local_date_t *m = temporal_local_date_plus_months(y, Z_TEMPORAL_PERIOD_INTERNAL_P(period)->months * -1);
	temporal_local_date_t *date = temporal_local_date_plus_days(m, Z_TEMPORAL_PERIOD_INTERNAL_P(period)->days * -1);

	temporal_local_date_free(y);
	temporal_local_date_free(m);

	temporal_local_date_time_t *copy = temporal_local_date_time_of_date_time(date, temporal_local_time_clone(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->time));
	zend_object *object = php_temporal_local_date_time_create_object_ex(copy);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, minusYears) {
	zend_long years;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(years)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *date = temporal_local_date_plus_years(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date, -years);
	temporal_local_date_time_t *copy = temporal_local_date_time_of_date_time(date, temporal_local_time_clone(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->time));
	zend_object *object = php_temporal_local_date_time_create_object_ex(copy);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, minusMonths) {
	zend_long months;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(months)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *date = temporal_local_date_plus_months(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date, -months);
	temporal_local_date_time_t *copy = temporal_local_date_time_of_date_time(date, temporal_local_time_clone(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->time));
	zend_object *object = php_temporal_local_date_time_create_object_ex(copy);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, minusWeeks) {
	zend_long weeks;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(weeks)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *date = temporal_local_date_plus_days(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date, -weeks * 7);
	temporal_local_date_time_t *copy = temporal_local_date_time_of_date_time(date, temporal_local_time_clone(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->time));
	zend_object *object = php_temporal_local_date_time_create_object_ex(copy);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, minusDays) {
	zend_long days;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(days)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *date = temporal_local_date_plus_days(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->date, -days);
	temporal_local_date_time_t *copy = temporal_local_date_time_of_date_time(date, temporal_local_time_clone(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()->time));
	zend_object *object = php_temporal_local_date_time_create_object_ex(copy);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, plusDuration) {
	zval *duration;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(duration, php_temporal_duration_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_time_t *date_time = temporal_local_date_time_plus_duration(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL(), Z_TEMPORAL_DURATION_INTERNAL_P(duration));
	zend_object *object = php_temporal_local_date_time_create_object_ex(date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, plusHours) {
	zend_long hours;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(hours)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(hours * SECONDS_PER_HOUR, 0);
	temporal_local_date_time_t *date_time = temporal_local_date_time_plus_duration(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL(), duration);
	temporal_duration_free(duration);

	zend_object *object = php_temporal_local_date_time_create_object_ex(date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, plusMinutes) {
	zend_long minutes;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(minutes)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(minutes * SECONDS_PER_MINUTE, 0);
	temporal_local_date_time_t *date_time = temporal_local_date_time_plus_duration(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL(), duration);
	temporal_duration_free(duration);

	zend_object *object = php_temporal_local_date_time_create_object_ex(date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, plusSeconds) {
	zend_long seconds;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(seconds)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(seconds, 0);
	temporal_local_date_time_t *date_time = temporal_local_date_time_plus_duration(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL(), duration);
	temporal_duration_free(duration);

	zend_object *object = php_temporal_local_date_time_create_object_ex(date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, plusNanos) {
	zend_long nanos;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(nanos)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(0, nanos);
	temporal_local_date_time_t *date_time = temporal_local_date_time_plus_duration(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL(), duration);
	temporal_duration_free(duration);

	zend_object *object = php_temporal_local_date_time_create_object_ex(date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, minusDuration) {
	zval *duration;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(duration, php_temporal_duration_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *negated = temporal_duration_negated(Z_TEMPORAL_DURATION_INTERNAL_P(duration));
	temporal_local_date_time_t *date_time = temporal_local_date_time_plus_duration(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL(), negated);

	temporal_duration_free(negated);

	zend_object *object = php_temporal_local_date_time_create_object_ex(date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, minusHours) {
	zend_long hours;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(hours)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(-hours * SECONDS_PER_HOUR, 0);
	temporal_local_date_time_t *date_time = temporal_local_date_time_plus_duration(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL(), duration);
	temporal_duration_free(duration);

	zend_object *object = php_temporal_local_date_time_create_object_ex(date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, minusMinutes) {
	zend_long minutes;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(minutes)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(-minutes * SECONDS_PER_MINUTE, 0);
	temporal_local_date_time_t *date_time = temporal_local_date_time_plus_duration(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL(), duration);
	temporal_duration_free(duration);

	zend_object *object = php_temporal_local_date_time_create_object_ex(date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, minusSeconds) {
	zend_long seconds;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(seconds)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(-seconds, 0);
	temporal_local_date_time_t *date_time = temporal_local_date_time_plus_duration(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL(), duration);
	temporal_duration_free(duration);

	zend_object *object = php_temporal_local_date_time_create_object_ex(date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, minusNanos) {
	zend_long nanos;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(nanos)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(0, -nanos);
	temporal_local_date_time_t *date_time = temporal_local_date_time_plus_duration(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL(), duration);
	temporal_duration_free(duration);

	zend_object *object = php_temporal_local_date_time_create_object_ex(date_time);
	RETURN_OBJ(object);
}

#define TEMPORAL_LOCAL_DATE_TIME_COMPARE                                                              \
	zend_object *other;                                                                               \
	ZEND_PARSE_PARAMETERS_START(1, 1)                                                                 \
	Z_PARAM_OBJ_OF_CLASS(other, php_temporal_local_date_time_ce)                                      \
	ZEND_PARSE_PARAMETERS_END();                                                                      \
	temporal_local_date_time_t *a = THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL();                         \
	temporal_local_date_time_t *b = php_temporal_local_date_time_from_object(other)->local_date_time; \
	int result = temporal_local_date_time_compare(a, b);

ZEND_METHOD(Temporal_LocalDateTime, compareTo) {
	TEMPORAL_LOCAL_DATE_TIME_COMPARE
	RETURN_LONG(result);
}

ZEND_METHOD(Temporal_LocalDateTime, isEqualTo) {
	TEMPORAL_LOCAL_DATE_TIME_COMPARE
	RETURN_BOOL(result == 0);
}

ZEND_METHOD(Temporal_LocalDateTime, isBefore) {
	TEMPORAL_LOCAL_DATE_TIME_COMPARE
	RETURN_BOOL(result < 0);
}

ZEND_METHOD(Temporal_LocalDateTime, isBeforeOrEqualTo) {
	TEMPORAL_LOCAL_DATE_TIME_COMPARE
	RETURN_BOOL(result <= 0);
}

ZEND_METHOD(Temporal_LocalDateTime, isAfter) {
	TEMPORAL_LOCAL_DATE_TIME_COMPARE
	RETURN_BOOL(result > 0);
}

ZEND_METHOD(Temporal_LocalDateTime, isAfterOrEqualTo) {
	TEMPORAL_LOCAL_DATE_TIME_COMPARE
	RETURN_BOOL(result >= 0);
}

ZEND_METHOD(Temporal_LocalDateTime, atTimeZone) {
	zval *time_zone;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(time_zone, php_temporal_time_zone_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of(
		temporal_local_date_time_clone(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL()),
		temporal_time_zone_clone(Z_TEMPORAL_TIME_ZONE_INTERNAL_P(time_zone))
	);

	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, toDateTime) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_date_time_t *date_time = THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL();

	smart_str buf_f = {0};
	smart_str_appends(&buf_f, "Y-m-d\\TH:i");

	smart_str buf_t = {0};

	char year_str[7];
	snprintf(year_str, sizeof(year_str), "%04lld", date_time->date->year);
	smart_str_appends(&buf_t, year_str);
	smart_str_appendc(&buf_t, '-');

	char month_str[4];
	snprintf(month_str, sizeof(month_str), "%02lld", date_time->date->month);
	smart_str_appends(&buf_t, month_str);
	smart_str_appendc(&buf_t, '-');

	char day_str[4];
	snprintf(day_str, sizeof(day_str), "%02lld", date_time->date->day);
	smart_str_appends(&buf_t, day_str);
	smart_str_appendc(&buf_t, 'T');

	char hour_str[4];
	snprintf(hour_str, sizeof(hour_str), "%02lld", date_time->time->hour);
	smart_str_appends(&buf_t, hour_str);
	smart_str_appendc(&buf_t, ':');

	char minute_str[4];
	snprintf(minute_str, sizeof(minute_str), "%02lld", date_time->time->minute);
	smart_str_appends(&buf_t, minute_str);

	if (date_time->time->second != 0 || date_time->time->nano != 0) {
		smart_str_appends(&buf_f, ":s");

		smart_str_appendc(&buf_t, ':');
		char second_str[4];
		snprintf(second_str, sizeof(second_str), "%02lld", date_time->time->second);
		smart_str_appends(&buf_t, second_str);

		if (date_time->time->nano != 0) {
			smart_str_appends(&buf_f, ".u");

			smart_str_appendc(&buf_t, '.');
			char micro_str[8];
			snprintf(micro_str, sizeof(micro_str), "%06lld", date_time->time->nano / 1000);
			smart_str_appends(&buf_t, micro_str);
		}

		smart_str_appends(&buf_f, " e");
		smart_str_appends(&buf_t, " UTC");
	}

	zend_string *format = smart_str_extract(&buf_f);
	zend_string *value = smart_str_extract(&buf_t);

	php_date_instantiate(php_date_get_immutable_ce(), return_value);
	if (!php_date_initialize(Z_PHPDATE_P(return_value), ZSTR_VAL(value), ZSTR_LEN(value), ZSTR_VAL(format), NULL, PHP_DATE_INIT_FORMAT)) {
		zend_string_release_ex(format, 0);
		zend_string_release_ex(value, 0);

		php_temporal_throw_exception("Failed to convert LocalDateTime into DateTimeImmutable.", 0);
		RETURN_THROWS();
	}

	zend_string_release_ex(format, 0);
	zend_string_release_ex(value, 0);
}

ZEND_METHOD(Temporal_LocalDateTime, fromDateTime) {
	zval *date;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(date, php_date_get_interface_ce())
	ZEND_PARSE_PARAMETERS_END();

	php_date_obj *date_obj = Z_PHPDATE_P(date);
	temporal_local_date_time_t *local_date_time = temporal_local_date_time_of(date_obj->time->y, date_obj->time->m, date_obj->time->d, date_obj->time->h, date_obj->time->i, date_obj->time->s, date_obj->time->us * 1000);
	zend_object *object = php_temporal_local_date_time_create_object_ex(local_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalDateTime, toISOString) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_string *str = temporal_local_date_time_format_iso(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL());
	RETURN_STR(str);
}

ZEND_METHOD(Temporal_LocalDateTime, format) {
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

	zend_string *formatted = temporal_local_date_time_format(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL(), formatter);

	if (formatted == NULL) {
		RETURN_THROWS();
	}

	RETURN_STR(formatted);
}

ZEND_METHOD(Temporal_LocalDateTime, formatWith) {
	zval *formatter;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(formatter, php_temporal_formatter_ce)
	ZEND_PARSE_PARAMETERS_END();

	zend_string *formatted = temporal_local_date_time_format(
		THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL(),
		Z_TEMPORAL_FORMATTER_INTERNAL_P(formatter)
	);

	if (formatted == NULL) {
		RETURN_THROWS();
	}

	RETURN_STR(formatted);
}

ZEND_METHOD(Temporal_LocalDateTime, jsonSerialize) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_string *str = temporal_local_date_time_format_iso(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL());
	RETURN_STR(str);
}

ZEND_METHOD(Temporal_LocalDateTime, __toString) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_string *str = temporal_local_date_time_format_iso(THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL());
	RETURN_STR(str);
}

ZEND_METHOD(Temporal_LocalDateTime, __serialize) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_date_time_t *local_date_time = THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL();

	array_init(return_value);
	HashTable *ht = Z_ARRVAL_P(return_value);

	zval tmp;

	ZVAL_LONG(&tmp, local_date_time->date->year);
	zend_hash_str_update(ht, "year", strlen("year"), &tmp);

	ZVAL_LONG(&tmp, local_date_time->date->month);
	zend_hash_str_update(ht, "month", strlen("month"), &tmp);

	ZVAL_LONG(&tmp, local_date_time->date->day);
	zend_hash_str_update(ht, "day", strlen("day"), &tmp);

	ZVAL_LONG(&tmp, local_date_time->time->hour);
	zend_hash_str_update(ht, "hour", strlen("hour"), &tmp);

	ZVAL_LONG(&tmp, local_date_time->time->minute);
	zend_hash_str_update(ht, "minute", strlen("minute"), &tmp);

	ZVAL_LONG(&tmp, local_date_time->time->second);
	zend_hash_str_update(ht, "second", strlen("second"), &tmp);

	ZVAL_LONG(&tmp, local_date_time->time->nano);
	zend_hash_str_update(ht, "nano", strlen("nano"), &tmp);
}

ZEND_METHOD(Temporal_LocalDateTime, __unserialize) {
	HashTable *ht;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_ARRAY_HT(ht)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_time_t *local_date_time = THIS_TEMPORAL_LOCAL_DATE_TIME_INTERNAL();

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

	zval *hour = zend_hash_str_find(ht, "hour", strlen("hour"));
	if (hour == NULL || Z_TYPE_P(hour) != IS_LONG) {
		php_temporal_throw_exception("Failed to unserialize Temporal value from data.", 0);
		RETURN_THROWS();
	}

	zval *minute = zend_hash_str_find(ht, "minute", strlen("minute"));
	if (minute == NULL || Z_TYPE_P(minute) != IS_LONG) {
		php_temporal_throw_exception("Failed to unserialize Temporal value from data.", 0);
		RETURN_THROWS();
	}

	zval *second = zend_hash_str_find(ht, "second", strlen("second"));
	if (second == NULL || Z_TYPE_P(second) != IS_LONG) {
		php_temporal_throw_exception("Failed to unserialize Temporal value from data.", 0);
		RETURN_THROWS();
	}

	zval *nano = zend_hash_str_find(ht, "nano", strlen("nano"));
	if (nano == NULL || Z_TYPE_P(nano) != IS_LONG) {
		php_temporal_throw_exception("Failed to unserialize Temporal value from data.", 0);
		RETURN_THROWS();
	}

	local_date_time->date->year = Z_LVAL_P(year);
	local_date_time->date->month = Z_LVAL_P(month);
	local_date_time->date->day = Z_LVAL_P(day);
	local_date_time->time->hour = Z_LVAL_P(hour);
	local_date_time->time->minute = Z_LVAL_P(minute);
	local_date_time->time->second = Z_LVAL_P(second);
	local_date_time->time->nano = Z_LVAL_P(nano);
}

zend_class_entry *php_temporal_local_date_time_ce;

void php_temporal_register_local_date_time_ce() {
	php_temporal_local_date_time_ce = register_class_Temporal_LocalDateTime(php_json_serializable_ce, zend_ce_stringable);
	php_temporal_local_date_time_ce->create_object = php_temporal_local_date_time_create_object;

	php_temporal_register_local_date_time_handlers();
}
