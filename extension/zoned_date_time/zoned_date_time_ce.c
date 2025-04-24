#include "zoned_date_time_ce.h"
#include <ext/date/php_date.h>
#include <ext/json/php_json.h>
#include <php.h>
#include <unicode/udat.h>
#include <zend_interfaces.h>
#include <zend_smart_str.h>
#include "clock/clock_ce.h"
#include "duration/duration.h"
#include "duration/duration_ce.h"
#include "duration/duration_obj.h"
#include "exception/exception_obj.h"
#include "format/formatter.h"
#include "format/formatter_ce.h"
#include "format/formatter_obj.h"
#include "instant/instant_ce.h"
#include "instant/instant_obj.h"
#include "local_date/local_date_ce.h"
#include "local_date/local_date_obj.h"
#include "local_date_time/local_date_time_ce.h"
#include "local_date_time/local_date_time_obj.h"
#include "local_time/local_time_ce.h"
#include "local_time/local_time_obj.h"
#include "month_day/month_day.h"
#include "month_day/month_day_obj.h"
#include "period/period.h"
#include "period/period_ce.h"
#include "period/period_obj.h"
#include "time_zone/time_zone.h"
#include "time_zone/time_zone_ce.h"
#include "time_zone/time_zone_obj.h"
#include "utils/check_range.h"
#include "utils/iso_calendar.h"
#include "year_month/year_month.h"
#include "year_month/year_month_obj.h"
#include "year_week/year_week.h"
#include "year_week/year_week_obj.h"
#include "zoned_date_time.h"
#include "zoned_date_time_arginfo.h"
#include "zoned_date_time_handlers.h"
#include "zoned_date_time_obj.h"

ZEND_METHOD(Temporal_ZonedDateTime, __construct) {
	// private
}

ZEND_METHOD(Temporal_ZonedDateTime, of) {
	zval *date_time, *time_zone;

	ZEND_PARSE_PARAMETERS_START(2, 2)
	Z_PARAM_OBJECT_OF_CLASS(date_time, php_temporal_local_date_time_ce)
	Z_PARAM_OBJECT_OF_CLASS(time_zone, php_temporal_time_zone_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of(
		Z_TEMPORAL_LOCAL_DATE_TIME_INTERNAL_P(date_time),
		Z_TEMPORAL_TIME_ZONE_INTERNAL_P(time_zone)
	);

	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, ofInstant) {
	zval *instant, *time_zone;

	ZEND_PARSE_PARAMETERS_START(2, 2)
	Z_PARAM_OBJECT_OF_CLASS(instant, php_temporal_instant_ce)
	Z_PARAM_OBJECT_OF_CLASS(time_zone, php_temporal_time_zone_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of_instant(
		Z_TEMPORAL_INSTANT_INTERNAL_P(instant),
		Z_TEMPORAL_TIME_ZONE_INTERNAL_P(time_zone)
	);

	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, now) {
	zval *time_zone;
	zend_object *clock = NULL;

	ZEND_PARSE_PARAMETERS_START(1, 2)
	Z_PARAM_OBJECT_OF_CLASS(time_zone, php_temporal_time_zone_ce)
	Z_PARAM_OPTIONAL
	Z_PARAM_OBJ_OF_CLASS_OR_NULL(clock, php_temporal_clock_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_now(Z_TEMPORAL_TIME_ZONE_INTERNAL_P(time_zone), clock);
	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, fromISOString) {
	zend_string *input;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_STR(input)
	ZEND_PARSE_PARAMETERS_END();

	const char *input_s = ZSTR_VAL(input);

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_parse_iso(input_s);
	if (zoned_date_time == NULL) {
		php_temporal_throw_exception("Failed to parse given input into a Temporal value.", 0);
		RETURN_THROWS();
	}

	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, getDateTime) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_date_time_t *local_date_time = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time;
	zend_object *object = php_temporal_local_date_time_create_object_ex(local_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, getDate) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_date_t *local_date = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->date;
	zend_object *object = php_temporal_local_date_create_object_ex(local_date);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, withDate) {
	zval *date;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(date, php_temporal_local_date_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_time_t *date_time = temporal_local_date_time_of_date_time(
		Z_TEMPORAL_LOCAL_DATE_INTERNAL_P(date),
		temporal_local_time_clone(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->time)
	);

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of(date_time, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone);
	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, getYear) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_date_t *local_date = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->date;
	RETURN_LONG(local_date->year);
}

ZEND_METHOD(Temporal_ZonedDateTime, withYear) {
	zend_long year;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(year)
	ZEND_PARSE_PARAMETERS_END();

	TEMPORAL_CHECK_VALUE_RANGE("year", year, -999999, 999999);

	temporal_local_date_t *local_date = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->date;

	zend_long day = local_date->day;
	zend_long max_day = days_in_month(year, local_date->month);
	if (day > max_day) {
		day = max_day;
	}

	temporal_local_date_time_t *date_time = temporal_local_date_time_of_date_time(
		temporal_local_date_of(year, local_date->month, day),
		temporal_local_time_clone(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->time)
	);

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of(date_time, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone);
	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, getMonth) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_date_t *local_date = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->date;
	RETURN_LONG(local_date->month);
}

ZEND_METHOD(Temporal_ZonedDateTime, withMonth) {
	zend_long month;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(month)
	ZEND_PARSE_PARAMETERS_END();

	TEMPORAL_CHECK_VALUE_RANGE("month", month, 1, 12);

	temporal_local_date_t *local_date = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->date;

	zend_long day = local_date->day;
	zend_long max_day = days_in_month(local_date->year, month);
	if (day > max_day) {
		day = max_day;
	}

	temporal_local_date_time_t *date_time = temporal_local_date_time_of_date_time(
		temporal_local_date_of(local_date->year, month, day),
		temporal_local_time_clone(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->time)
	);

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of(date_time, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone);
	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, getYearMonth) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_date_t *local_date = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->date;
	temporal_year_month_t *year_month = temporal_year_month_of(local_date->year, local_date->month);
	zend_object *object = php_temporal_year_month_create_object_ex(year_month);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, getWeek) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_date_t *local_date = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->date;
	temporal_year_week_t *year_week = temporal_year_week_of_date(local_date);
	zend_long week = year_week->week;
	temporal_year_week_free(year_week);

	RETURN_LONG(week);
}

ZEND_METHOD(Temporal_ZonedDateTime, getYearOfWeek) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_date_t *local_date = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->date;
	temporal_year_week_t *year_week = temporal_year_week_of_date(local_date);
	zend_long year = year_week->year;
	temporal_year_week_free(year_week);

	RETURN_LONG(year);
}

ZEND_METHOD(Temporal_ZonedDateTime, getYearWeek) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_date_t *local_date = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->date;
	temporal_year_week_t *year_week = temporal_year_week_of_date(local_date);
	zend_object *object = php_temporal_year_week_create_object_ex(year_week);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, getDayOfMonth) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_date_t *local_date = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->date;
	RETURN_LONG(local_date->day);
}

ZEND_METHOD(Temporal_ZonedDateTime, withDayOfMonth) {
	zend_long day;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(day)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *local_date = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->date;

	zend_long max_day = days_in_month(local_date->year, local_date->month);
	TEMPORAL_CHECK_VALUE_RANGE("day", day, 1, max_day);

	temporal_local_date_time_t *date_time = temporal_local_date_time_of_date_time(
		temporal_local_date_of(local_date->year, local_date->month, day),
		temporal_local_time_clone(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->time)
	);

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of(date_time, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone);
	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, getMonthDay) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_date_t *local_date = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->date;
	temporal_month_day_t *month_day = temporal_month_day_of(local_date->month, local_date->day);
	zend_object *object = php_temporal_month_day_create_object_ex(month_day);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, getDayOfYear) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_date_t *local_date = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->date;
	zend_long day_of_year = temporal_local_date_day_of_year(local_date);
	RETURN_LONG(day_of_year);
}

ZEND_METHOD(Temporal_ZonedDateTime, getDayOfWeek) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_date_t *local_date = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->date;
	zend_long day_of_year = temporal_local_date_day_of_week(local_date);
	RETURN_LONG(day_of_year);
}

ZEND_METHOD(Temporal_ZonedDateTime, getDaysInMonth) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_date_t *local_date = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->date;
	zend_long days = days_in_month(local_date->year, local_date->month);
	RETURN_LONG(days);
}

ZEND_METHOD(Temporal_ZonedDateTime, getDaysInYear) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_date_t *local_date = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->date;
	zend_long days = days_in_year(local_date->year);
	RETURN_LONG(days);
}

ZEND_METHOD(Temporal_ZonedDateTime, getWeeksInYear) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_date_t *local_date = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->date;
	zend_long weeks = weeks_in_year(local_date->year);
	RETURN_LONG(weeks);
}

ZEND_METHOD(Temporal_ZonedDateTime, isLeapYear) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_date_t *local_date = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->date;
	bool result = is_leap_year(local_date->year);
	RETURN_BOOL(result);
}

ZEND_METHOD(Temporal_ZonedDateTime, getTime) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_time_t *local_time = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->time;
	zend_object *object = php_temporal_local_time_create_object_ex(local_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, withTime) {
	zval *time;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(time, php_temporal_local_time_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_time_t *date_time = temporal_local_date_time_of_date_time(
		temporal_local_date_clone(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->date),
		Z_TEMPORAL_LOCAL_TIME_INTERNAL_P(time)
	);

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of(date_time, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone);
	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, getHour) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_time_t *local_time = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->time;
	RETURN_LONG(local_time->hour);
}

ZEND_METHOD(Temporal_ZonedDateTime, withHour) {
	zend_long hour;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(hour)
	ZEND_PARSE_PARAMETERS_END();

	TEMPORAL_CHECK_VALUE_RANGE("hour", hour, 0, HOURS_PER_DAY - 1);

	temporal_local_time_t *time = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->time;

	temporal_local_date_time_t *date_time = temporal_local_date_time_of_date_time(
		temporal_local_date_clone(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->date),
		temporal_local_time_of(hour, time->minute, time->second, time->nano)
	);

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of(date_time, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone);
	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, getMinute) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_time_t *local_time = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->time;
	RETURN_LONG(local_time->minute);
}

ZEND_METHOD(Temporal_ZonedDateTime, withMinute) {
	zend_long minute;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(minute)
	ZEND_PARSE_PARAMETERS_END();

	TEMPORAL_CHECK_VALUE_RANGE("minute", minute, 0, MINUTES_PER_HOUR - 1);

	temporal_local_time_t *time = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->time;

	temporal_local_date_time_t *date_time = temporal_local_date_time_of_date_time(
		temporal_local_date_clone(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->date),
		temporal_local_time_of(time->hour, minute, time->second, time->nano)
	);

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of(date_time, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone);
	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, getSecond) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_time_t *local_time = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->time;
	RETURN_LONG(local_time->second);
}

ZEND_METHOD(Temporal_ZonedDateTime, withSecond) {
	zend_long second;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(second)
	ZEND_PARSE_PARAMETERS_END();

	TEMPORAL_CHECK_VALUE_RANGE("second", second, 0, SECONDS_PER_MINUTE - 1);

	temporal_local_time_t *time = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->time;

	temporal_local_date_time_t *date_time = temporal_local_date_time_of_date_time(
		temporal_local_date_clone(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->date),
		temporal_local_time_of(time->hour, time->minute, second, time->nano)
	);

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of(date_time, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone);
	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, getNano) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_time_t *local_time = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->time;
	RETURN_LONG(local_time->nano);
}

ZEND_METHOD(Temporal_ZonedDateTime, withNano) {
	zend_long nano;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(nano)
	ZEND_PARSE_PARAMETERS_END();

	TEMPORAL_CHECK_VALUE_RANGE("nano", nano, 0, NANOS_PER_SECOND - 1);

	temporal_local_time_t *time = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->time;

	temporal_local_date_time_t *date_time = temporal_local_date_time_of_date_time(
		temporal_local_date_clone(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->date),
		temporal_local_time_of(time->hour, time->minute, time->second, nano)
	);

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of(date_time, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone);
	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, getInstant) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_instant_t *instant = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->instant;
	zend_object *object = php_temporal_instant_create_object_clone(instant);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, getTimeZone) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_time_zone_t *time_zone = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone;
	zend_object *time_zone_object = php_temporal_time_zone_create_object_clone(time_zone);
	RETURN_OBJ(time_zone_object);
}

ZEND_METHOD(Temporal_ZonedDateTime, getTimeZoneOffset) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_time_zone_t *time_zone = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone;
	if (IS_TEMPORAL_TIME_ZONE_OFFSET(time_zone)) {
		zend_object *time_zone_object = php_temporal_time_zone_create_object_clone(time_zone);
		RETURN_OBJ(time_zone_object);
	}

	temporal_time_zone_t *time_zone_offset = temporal_time_zone_of_offset(temporal_time_zone_offset_clone(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone_offset));
	zend_object *time_zone_object = php_temporal_time_zone_create_object_ex(time_zone_offset);
	RETURN_OBJ(time_zone_object);
}

ZEND_METHOD(Temporal_ZonedDateTime, withTimeZoneSameLocal) {
	zval *time_zone;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(time_zone, php_temporal_time_zone_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of(
		temporal_local_date_time_clone(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time),
		Z_TEMPORAL_TIME_ZONE_INTERNAL_P(time_zone)
	);

	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, withTimeZoneSameInstant) {
	zval *time_zone;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(time_zone, php_temporal_time_zone_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of_instant(
		temporal_instant_clone(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->instant),
		Z_TEMPORAL_TIME_ZONE_INTERNAL_P(time_zone)
	);

	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, withFixedOffsetTimeZone) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_time_zone_t *time_zone = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone;

	if (IS_TEMPORAL_TIME_ZONE_OFFSET(time_zone)) {
		return_value = getThis();
	}

	temporal_time_zone_t *offset_time_zone = temporal_time_zone_of_offset(temporal_time_zone_offset_clone(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone_offset));

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of(
		temporal_local_date_time_clone(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time),
		offset_time_zone
	);

	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, plusPeriod) {
	zval *period;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(period, php_temporal_period_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *y = temporal_local_date_plus_years(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->date, Z_TEMPORAL_PERIOD_INTERNAL_P(period)->years);
	temporal_local_date_t *m = temporal_local_date_plus_months(y, Z_TEMPORAL_PERIOD_INTERNAL_P(period)->months);
	temporal_local_date_t *date = temporal_local_date_plus_days(m, Z_TEMPORAL_PERIOD_INTERNAL_P(period)->days);

	temporal_local_date_free(y);
	temporal_local_date_free(m);

	temporal_local_date_time_t *local_date_time = temporal_local_date_time_of_date_time(date, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->time);
	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of(local_date_time, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone);
	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, plusYears) {
	zend_long years;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(years)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *date = temporal_local_date_plus_years(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->date, years);
	temporal_local_date_time_t *local_date_time = temporal_local_date_time_of_date_time(date, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->time);
	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of(local_date_time, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone);
	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, plusMonths) {
	zend_long months;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(months)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *date = temporal_local_date_plus_months(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->date, months);
	temporal_local_date_time_t *local_date_time = temporal_local_date_time_of_date_time(date, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->time);
	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of(local_date_time, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone);
	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, plusWeeks) {
	zend_long weeks;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(weeks)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *date = temporal_local_date_plus_days(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->date, weeks * 7);
	temporal_local_date_time_t *local_date_time = temporal_local_date_time_of_date_time(date, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->time);
	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of(local_date_time, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone);
	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, plusDays) {
	zend_long days;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(days)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *date = temporal_local_date_plus_days(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->date, days);
	temporal_local_date_time_t *local_date_time = temporal_local_date_time_of_date_time(date, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->time);
	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of(local_date_time, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone);
	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, minusPeriod) {
	zval *period;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(period, php_temporal_period_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *y = temporal_local_date_plus_years(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->date, Z_TEMPORAL_PERIOD_INTERNAL_P(period)->years * -1);
	temporal_local_date_t *m = temporal_local_date_plus_months(y, Z_TEMPORAL_PERIOD_INTERNAL_P(period)->months * -1);
	temporal_local_date_t *date = temporal_local_date_plus_days(m, Z_TEMPORAL_PERIOD_INTERNAL_P(period)->days * -1);

	temporal_local_date_free(y);
	temporal_local_date_free(m);

	temporal_local_date_time_t *local_date_time = temporal_local_date_time_of_date_time(date, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->time);
	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of(local_date_time, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone);
	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, minusYears) {
	zend_long years;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(years)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *date = temporal_local_date_plus_years(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->date, -years);
	temporal_local_date_time_t *local_date_time = temporal_local_date_time_of_date_time(date, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->time);
	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of(local_date_time, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone);
	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, minusMonths) {
	zend_long months;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(months)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *date = temporal_local_date_plus_months(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->date, -months);
	temporal_local_date_time_t *local_date_time = temporal_local_date_time_of_date_time(date, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->time);
	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of(local_date_time, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone);
	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, minusWeeks) {
	zend_long weeks;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(weeks)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *date = temporal_local_date_plus_days(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->date, -weeks * 7);
	temporal_local_date_time_t *local_date_time = temporal_local_date_time_of_date_time(date, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->time);
	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of(local_date_time, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone);
	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, minusDays) {
	zend_long days;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(days)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *date = temporal_local_date_plus_days(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->date, -days);
	temporal_local_date_time_t *local_date_time = temporal_local_date_time_of_date_time(date, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->date_time->time);
	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of(local_date_time, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone);
	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, plusDuration) {
	zval *duration;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(duration, php_temporal_duration_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_instant_t *instant = temporal_instant_plus(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->instant, Z_TEMPORAL_DURATION_INTERNAL_P(duration));
	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of_instant(instant, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone);
	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, plusHours) {
	zend_long hours;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(hours)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(hours * SECONDS_PER_HOUR, 0);
	temporal_instant_t *instant = temporal_instant_plus(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->instant, duration);
	temporal_duration_free(duration);

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of_instant(instant, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone);
	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, plusMinutes) {
	zend_long minutes;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(minutes)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(minutes * SECONDS_PER_MINUTE, 0);
	temporal_instant_t *instant = temporal_instant_plus(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->instant, duration);
	temporal_duration_free(duration);

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of_instant(instant, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone);
	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, plusSeconds) {
	zend_long seconds;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(seconds)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(seconds, 0);
	temporal_instant_t *instant = temporal_instant_plus(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->instant, duration);
	temporal_duration_free(duration);

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of_instant(instant, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone);
	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, plusNanos) {
	zend_long nanos;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(nanos)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(0, nanos);
	temporal_instant_t *instant = temporal_instant_plus(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->instant, duration);
	temporal_duration_free(duration);

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of_instant(instant, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone);
	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, minusDuration) {
	zval *duration;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(duration, php_temporal_duration_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_instant_t *instant = temporal_instant_minus(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->instant, Z_TEMPORAL_DURATION_INTERNAL_P(duration));
	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of_instant(instant, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone);
	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, minusHours) {
	zend_long hours;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(hours)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(hours * SECONDS_PER_HOUR, 0);
	temporal_instant_t *instant = temporal_instant_minus(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->instant, duration);
	temporal_duration_free(duration);

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of_instant(instant, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone);
	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, minusMinutes) {
	zend_long minutes;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(minutes)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(minutes * SECONDS_PER_MINUTE, 0);
	temporal_instant_t *instant = temporal_instant_minus(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->instant, duration);
	temporal_duration_free(duration);

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of_instant(instant, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone);
	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, minusSeconds) {
	zend_long seconds;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(seconds)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(seconds, 0);
	temporal_instant_t *instant = temporal_instant_minus(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->instant, duration);
	temporal_duration_free(duration);

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of_instant(instant, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone);
	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, minusNanos) {
	zend_long nanos;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(nanos)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(0, nanos);
	temporal_instant_t *instant = temporal_instant_minus(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->instant, duration);
	temporal_duration_free(duration);

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of_instant(instant, THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL()->zone);
	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

#define TEMPORAL_ZONED_DATE_TIME_COMPARE                                                              \
	zend_object *other;                                                                               \
	ZEND_PARSE_PARAMETERS_START(1, 1)                                                                 \
	Z_PARAM_OBJ_OF_CLASS(other, php_temporal_zoned_date_time_ce)                                      \
	ZEND_PARSE_PARAMETERS_END();                                                                      \
	temporal_zoned_date_time_t *a = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL();                         \
	temporal_zoned_date_time_t *b = php_temporal_zoned_date_time_from_object(other)->zoned_date_time; \
	int result = temporal_zoned_date_time_compare(a, b);

ZEND_METHOD(Temporal_ZonedDateTime, compareTo) {
	TEMPORAL_ZONED_DATE_TIME_COMPARE
	RETURN_LONG(result);
}

ZEND_METHOD(Temporal_ZonedDateTime, isEqualTo) {
	TEMPORAL_ZONED_DATE_TIME_COMPARE
	RETURN_BOOL(result == 0);
}

ZEND_METHOD(Temporal_ZonedDateTime, isBefore) {
	TEMPORAL_ZONED_DATE_TIME_COMPARE
	RETURN_BOOL(result < 0);
}

ZEND_METHOD(Temporal_ZonedDateTime, isBeforeOrEqualTo) {
	TEMPORAL_ZONED_DATE_TIME_COMPARE
	RETURN_BOOL(result <= 0);
}

ZEND_METHOD(Temporal_ZonedDateTime, isAfter) {
	TEMPORAL_ZONED_DATE_TIME_COMPARE
	RETURN_BOOL(result > 0);
}

ZEND_METHOD(Temporal_ZonedDateTime, isAfterOrEqualTo) {
	TEMPORAL_ZONED_DATE_TIME_COMPARE
	RETURN_BOOL(result >= 0);
}

ZEND_METHOD(Temporal_ZonedDateTime, toDateTime) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_zoned_date_time_t *zoned_date_time = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL();

	smart_str buf_f = {0};
	smart_str_appends(&buf_f, "Y-m-d\\TH:i");

	smart_str buf_t = {0};

	char year_str[7];
	snprintf(year_str, sizeof(year_str), "%04lld", zoned_date_time->date_time->date->year);
	smart_str_appends(&buf_t, year_str);
	smart_str_appendc(&buf_t, '-');

	char month_str[4];
	snprintf(month_str, sizeof(month_str), "%02lld", zoned_date_time->date_time->date->month);
	smart_str_appends(&buf_t, month_str);
	smart_str_appendc(&buf_t, '-');

	char day_str[4];
	snprintf(day_str, sizeof(day_str), "%02lld", zoned_date_time->date_time->date->day);
	smart_str_appends(&buf_t, day_str);
	smart_str_appendc(&buf_t, 'T');

	char hour_str[4];
	snprintf(hour_str, sizeof(hour_str), "%02lld", zoned_date_time->date_time->time->hour);
	smart_str_appends(&buf_t, hour_str);
	smart_str_appendc(&buf_t, ':');

	char minute_str[4];
	snprintf(minute_str, sizeof(minute_str), "%02lld", zoned_date_time->date_time->time->minute);
	smart_str_appends(&buf_t, minute_str);

	if (zoned_date_time->date_time->time->second != 0 || zoned_date_time->date_time->time->nano != 0) {
		smart_str_appends(&buf_f, ":s");

		smart_str_appendc(&buf_t, ':');
		char second_str[4];
		snprintf(second_str, sizeof(second_str), "%02lld", zoned_date_time->date_time->time->second);
		smart_str_appends(&buf_t, second_str);

		if (zoned_date_time->date_time->time->nano != 0) {
			smart_str_appends(&buf_f, ".u");

			smart_str_appendc(&buf_t, '.');
			char micro_str[8];
			snprintf(micro_str, sizeof(micro_str), "%06lld", zoned_date_time->date_time->time->nano / 1000);
			smart_str_appends(&buf_t, micro_str);
		}
	}

	zend_string *tz_id;
	zval date_time_zone;

	if (IS_TEMPORAL_TIME_ZONE_OFFSET(zoned_date_time->zone)) {
		object_init_ex(&date_time_zone, php_date_get_timezone_ce());
		php_timezone_obj *tz_obj = Z_PHPTIMEZONE_P(&date_time_zone);

		tz_obj->initialized = 1;
		tz_obj->type = TIMELIB_ZONETYPE_OFFSET;
		tz_obj->tzi.utc_offset = zoned_date_time->zone->offset->total_seconds;

		smart_str_appends(&buf_f, " p");
		tz_id = temporal_time_zone_offset_id(zoned_date_time->zone->offset);

	} else {
		zval z_id;
		ZVAL_STR_COPY(&z_id, zoned_date_time->zone->region->id);

		object_init_with_constructor(&date_time_zone, php_date_get_timezone_ce(), 1, &z_id, NULL);

		smart_str_appends(&buf_f, " e");
		tz_id = zend_string_copy(zoned_date_time->zone->region->id);
	}

	smart_str_appendc(&buf_t, ' ');
	smart_str_append(&buf_t, tz_id);

	zend_string_release(tz_id);

	zend_string *format = smart_str_extract(&buf_f);
	zend_string *value = smart_str_extract(&buf_t);

	php_date_instantiate(php_date_get_immutable_ce(), return_value);
	if (!php_date_initialize(Z_PHPDATE_P(return_value), ZSTR_VAL(value), ZSTR_LEN(value), ZSTR_VAL(format), &date_time_zone, PHP_DATE_INIT_FORMAT)) {
		zend_string_release_ex(format, 0);
		zend_string_release_ex(value, 0);

		php_temporal_throw_exception("Failed to convert LocalDateTime into DateTimeImmutable.", 0);
		RETURN_THROWS();
	}

	zend_string_release_ex(format, 0);
	zend_string_release_ex(value, 0);
}

ZEND_METHOD(Temporal_ZonedDateTime, fromDateTime) {
	zval *date;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(date, php_date_get_interface_ce())
	ZEND_PARSE_PARAMETERS_END();

	php_date_obj *date_obj = Z_PHPDATE_P(date);

	temporal_local_date_time_t *local_date_time = temporal_local_date_time_of(date_obj->time->y, date_obj->time->m, date_obj->time->d, date_obj->time->h, date_obj->time->i, date_obj->time->s, date_obj->time->us * 1000);

	temporal_time_zone_t *time_zone;
	if (date_obj->time->zone_type == TIMELIB_ZONETYPE_OFFSET) {
		temporal_time_zone_offset_t *offset = temporal_time_zone_offset_of_total_seconds(date_obj->time->z);
		time_zone = temporal_time_zone_of_offset(offset);

	} else if (date_obj->time->zone_type == TIMELIB_ZONETYPE_ID) {
		temporal_time_zone_region_t *region = temporal_time_zone_region_of(date_obj->time->tz_info->name);
		time_zone = temporal_time_zone_of_region(region);

	} else { // tz_obj->type == TIMELIB_ZONETYPE_ABBR
		temporal_time_zone_region_t *region = temporal_time_zone_region_of(date_obj->time->tz_abbr);
		time_zone = temporal_time_zone_of_region(region);
	}

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of(local_date_time, time_zone);
	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_ZonedDateTime, toISOString) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_string *str = temporal_zoned_date_time_format_iso(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL());
	RETURN_STR(str);
}

ZEND_METHOD(Temporal_ZonedDateTime, format) {
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

	zend_string *formatted = temporal_zoned_date_time_format(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL(), formatter);

	if (formatted == NULL) {
		RETURN_THROWS();
	}

	RETURN_STR(formatted);
}

ZEND_METHOD(Temporal_ZonedDateTime, formatWith) {
	zval *formatter;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(formatter, php_temporal_formatter_ce)
	ZEND_PARSE_PARAMETERS_END();

	zend_string *formatted = temporal_zoned_date_time_format(
		THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL(),
		Z_TEMPORAL_FORMATTER_INTERNAL_P(formatter)
	);

	if (formatted == NULL) {
		RETURN_THROWS();
	}

	RETURN_STR(formatted);
}

ZEND_METHOD(Temporal_ZonedDateTime, jsonSerialize) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_string *str = temporal_zoned_date_time_format_iso(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL());
	RETURN_STR(str);
}

ZEND_METHOD(Temporal_ZonedDateTime, __toString) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_string *str = temporal_zoned_date_time_format_iso(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL());
	RETURN_STR(str);
}

ZEND_METHOD(Temporal_ZonedDateTime, __serialize) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_zoned_date_time_t *zoned_date_time = THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL();

	array_init(return_value);
	HashTable *ht = Z_ARRVAL_P(return_value);

	zval tmp;

	ZVAL_LONG(&tmp, zoned_date_time->date_time->date->year);
	zend_hash_str_update(ht, "year", strlen("year"), &tmp);

	ZVAL_LONG(&tmp, zoned_date_time->date_time->date->month);
	zend_hash_str_update(ht, "month", strlen("month"), &tmp);

	ZVAL_LONG(&tmp, zoned_date_time->date_time->date->day);
	zend_hash_str_update(ht, "day", strlen("day"), &tmp);

	ZVAL_LONG(&tmp, zoned_date_time->date_time->time->hour);
	zend_hash_str_update(ht, "hour", strlen("hour"), &tmp);

	ZVAL_LONG(&tmp, zoned_date_time->date_time->time->minute);
	zend_hash_str_update(ht, "minute", strlen("minute"), &tmp);

	ZVAL_LONG(&tmp, zoned_date_time->date_time->time->second);
	zend_hash_str_update(ht, "second", strlen("second"), &tmp);

	ZVAL_LONG(&tmp, zoned_date_time->date_time->time->nano);
	zend_hash_str_update(ht, "nano", strlen("nano"), &tmp);

	ZVAL_STR(&tmp, temporal_time_zone_get_id(zoned_date_time->zone));
	zend_hash_str_update(ht, "timeZone", strlen("timeZone"), &tmp);
}

ZEND_METHOD(Temporal_ZonedDateTime, __unserialize) {
	HashTable *ht;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_ARRAY_HT(ht)
	ZEND_PARSE_PARAMETERS_END();

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

	zval *zone_id = zend_hash_str_find(ht, "timeZone", strlen("timeZone"));
	if (zone_id == NULL || Z_TYPE_P(zone_id) != IS_STRING) {
		php_temporal_throw_exception("Failed to unserialize Temporal value from data.", 0);
		RETURN_THROWS();
	}

	temporal_zoned_date_time_free(THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL());

	temporal_local_date_time_t *local_date_time = temporal_local_date_time_of(Z_LVAL_P(year), Z_LVAL_P(month), Z_LVAL_P(day), Z_LVAL_P(hour), Z_LVAL_P(minute), Z_LVAL_P(second), Z_LVAL_P(nano));
	temporal_time_zone_t *time_zone = temporal_time_zone_parse_iso(Z_STRVAL_P(zone_id));
	THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL() = temporal_zoned_date_time_of(local_date_time, time_zone);
}

zend_class_entry *php_temporal_zoned_date_time_ce;

void php_temporal_register_zoned_date_time_ce() {
	php_temporal_zoned_date_time_ce = register_class_Temporal_ZonedDateTime(php_json_serializable_ce, zend_ce_stringable);
	php_temporal_zoned_date_time_ce->create_object = php_temporal_zoned_date_time_create_object;

	php_temporal_register_zoned_date_time_handlers();
}
