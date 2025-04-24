#include "year_week_ce.h"
#include <ext/date/php_date.h>
#include <ext/json/php_json.h>
#include <php.h>
#include <zend_interfaces.h>
#include <zend_smart_str.h>
#include "year_week.h"
#include "year_week_arginfo.h"
#include "year_week_handlers.h"
#include "year_week_obj.h"
#include "clock/clock_ce.h"
#include "exception/exception_obj.h"
#include "local_date/local_date.h"
#include "local_date/local_date_obj.h"
#include "time_zone/time_zone.h"
#include "time_zone/time_zone_ce.h"
#include "time_zone/time_zone_obj.h"
#include "utils/check_range.h"
#include "utils/iso_calendar.h"
#include "zoned_date_time/zoned_date_time.h"

ZEND_METHOD(Temporal_YearWeek, __construct) {
	// private
}

ZEND_METHOD(Temporal_YearWeek, of) {
	zend_long year, week;

	ZEND_PARSE_PARAMETERS_START(2, 2)
	Z_PARAM_LONG(year)
	Z_PARAM_LONG(week)
	ZEND_PARSE_PARAMETERS_END();

	TEMPORAL_CHECK_VALUE_RANGE("year", year, -999999, 999999);

	zend_long max_week = weeks_in_year(year);
	TEMPORAL_CHECK_VALUE_RANGE("week", week, 1, max_week);

	temporal_year_week_t *year_week = temporal_year_week_of(year, week);
	zend_object *object = php_temporal_year_week_create_object_ex(year_week);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_YearWeek, now) {
	zval *time_zone, *clock = NULL;

	ZEND_PARSE_PARAMETERS_START(1, 2)
	Z_PARAM_OBJECT_OF_CLASS(time_zone, php_temporal_time_zone_ce)
	Z_PARAM_OPTIONAL
	Z_PARAM_OBJECT_OF_CLASS_OR_NULL(clock, php_temporal_clock_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_now(temporal_time_zone_clone(Z_TEMPORAL_TIME_ZONE_INTERNAL_P(time_zone)), Z_OBJ_P(clock));
	temporal_year_week_t *year_week = temporal_year_week_of_date(zoned_date_time->date_time->date);

	temporal_zoned_date_time_free(zoned_date_time);

	zend_object *object = php_temporal_year_week_create_object_ex(year_week);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_YearWeek, fromISOString) {
	zend_string *input;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_STR(input)
	ZEND_PARSE_PARAMETERS_END();

	const char *input_s = ZSTR_VAL(input);

	temporal_year_week_t *year_week = temporal_year_week_parse_iso(input_s);
	if (year_week == NULL) {
		php_temporal_throw_exception("Failed to parse given input into a Temporal value.", 0);
		RETURN_THROWS();
	}

	zend_object *object = php_temporal_year_week_create_object_ex(year_week);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_YearWeek, getYear) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long year = THIS_TEMPORAL_YEAR_WEEK_INTERNAL()->year;
	RETURN_LONG(year);
}

ZEND_METHOD(Temporal_YearWeek, withYear) {
	zend_long year;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(year)
	ZEND_PARSE_PARAMETERS_END();

	TEMPORAL_CHECK_VALUE_RANGE("year", year, -999999, 999999);

	temporal_year_week_t *year_week = temporal_year_week_of(year, THIS_TEMPORAL_YEAR_WEEK_INTERNAL()->week);
	zend_object *object = php_temporal_year_week_create_object_ex(year_week);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_YearWeek, plusYears) {
	zend_long years;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(years)
	ZEND_PARSE_PARAMETERS_END();

	zend_long year = THIS_TEMPORAL_YEAR_WEEK_INTERNAL()->year + years;
	TEMPORAL_CHECK_VALUE_RANGE("year", year, -999999, 999999);

	temporal_year_week_t *year_week = temporal_year_week_of(year, THIS_TEMPORAL_YEAR_WEEK_INTERNAL()->week);
	zend_object *object = php_temporal_year_week_create_object_ex(year_week);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_YearWeek, minusYears) {
	zend_long years;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(years)
	ZEND_PARSE_PARAMETERS_END();

	zend_long year = THIS_TEMPORAL_YEAR_WEEK_INTERNAL()->year - years;
	TEMPORAL_CHECK_VALUE_RANGE("year", year, -999999, 999999);

	temporal_year_week_t *year_week = temporal_year_week_of(year, THIS_TEMPORAL_YEAR_WEEK_INTERNAL()->week);
	zend_object *object = php_temporal_year_week_create_object_ex(year_week);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_YearWeek, getWeek) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long week = THIS_TEMPORAL_YEAR_WEEK_INTERNAL()->week;
	RETURN_LONG(week);
}

ZEND_METHOD(Temporal_YearWeek, withWeek) {
	zend_long week;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(week)
	ZEND_PARSE_PARAMETERS_END();

	zend_long max_week = weeks_in_year(THIS_TEMPORAL_YEAR_WEEK_INTERNAL()->year);
	TEMPORAL_CHECK_VALUE_RANGE("week", week, 1, max_week);

	temporal_year_week_t *year_week = temporal_year_week_of(THIS_TEMPORAL_YEAR_WEEK_INTERNAL()->year, week);
	zend_object *object = php_temporal_year_week_create_object_ex(year_week);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_YearWeek, plusWeeks) {
	zend_long weeks;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(weeks)
	ZEND_PARSE_PARAMETERS_END();

	temporal_year_week_t *year_week = temporal_year_week_plus_weeks(THIS_TEMPORAL_YEAR_WEEK_INTERNAL(), weeks);
	zend_object *object = php_temporal_year_week_create_object_ex(year_week);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_YearWeek, minusWeeks) {
	zend_long weeks;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(weeks)
	ZEND_PARSE_PARAMETERS_END();

	temporal_year_week_t *year_week = temporal_year_week_plus_weeks(THIS_TEMPORAL_YEAR_WEEK_INTERNAL(), -weeks);
	zend_object *object = php_temporal_year_week_create_object_ex(year_week);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_YearWeek, getDaysInYear) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long days = days_in_year(THIS_TEMPORAL_YEAR_WEEK_INTERNAL()->year);
	RETURN_LONG(days);
}

ZEND_METHOD(Temporal_YearWeek, getWeeksInYear) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long weeks = weeks_in_year(THIS_TEMPORAL_YEAR_WEEK_INTERNAL()->year);
	RETURN_LONG(weeks);
}

ZEND_METHOD(Temporal_YearWeek, isLeapYear) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_bool result = is_leap_year(THIS_TEMPORAL_YEAR_WEEK_INTERNAL()->year);
	RETURN_BOOL(result);
}

ZEND_METHOD(Temporal_YearWeek, atDay) {
	zend_long day_of_week;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(day_of_week)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *local_date = temporal_year_week_at_day(THIS_TEMPORAL_YEAR_WEEK_INTERNAL(), day_of_week);
	zend_object *object = php_temporal_local_date_create_object_ex(local_date);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_YearWeek, getFirstDay) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_date_t *local_date = temporal_year_week_at_day(THIS_TEMPORAL_YEAR_WEEK_INTERNAL(), 1);
	zend_object *object = php_temporal_local_date_create_object_ex(local_date);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_YearWeek, getLastDay) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_date_t *local_date = temporal_year_week_at_day(THIS_TEMPORAL_YEAR_WEEK_INTERNAL(), 7);
	zend_object *object = php_temporal_local_date_create_object_ex(local_date);
	RETURN_OBJ(object);
}

#define TEMPORAL_YEAR_WEEK_COMPARE                                                  \
	zend_object *other;                                                             \
	ZEND_PARSE_PARAMETERS_START(1, 1)                                               \
	Z_PARAM_OBJ_OF_CLASS(other, php_temporal_year_week_ce)                          \
	ZEND_PARSE_PARAMETERS_END();                                                    \
	temporal_year_week_t *a = THIS_TEMPORAL_YEAR_WEEK_INTERNAL();                   \
	temporal_year_week_t *b = php_temporal_year_week_from_object(other)->year_week; \
	int result = temporal_year_week_compare(a, b);

ZEND_METHOD(Temporal_YearWeek, compareTo) {
	TEMPORAL_YEAR_WEEK_COMPARE
	RETURN_LONG(result);
}

ZEND_METHOD(Temporal_YearWeek, isEqualTo) {
	TEMPORAL_YEAR_WEEK_COMPARE
	RETURN_BOOL(result == 0);
}

ZEND_METHOD(Temporal_YearWeek, isBefore) {
	TEMPORAL_YEAR_WEEK_COMPARE
	RETURN_BOOL(result < 0);
}

ZEND_METHOD(Temporal_YearWeek, isBeforeOrEqualTo) {
	TEMPORAL_YEAR_WEEK_COMPARE
	RETURN_BOOL(result <= 0);
}

ZEND_METHOD(Temporal_YearWeek, isAfter) {
	TEMPORAL_YEAR_WEEK_COMPARE
	RETURN_BOOL(result > 0);
}

ZEND_METHOD(Temporal_YearWeek, isAfterOrEqualTo) {
	TEMPORAL_YEAR_WEEK_COMPARE
	RETURN_BOOL(result >= 0);
}

ZEND_METHOD(Temporal_YearWeek, toISOString) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_string *str = temporal_year_week_format_iso(THIS_TEMPORAL_YEAR_WEEK_INTERNAL());
	RETURN_STR(str);
}

ZEND_METHOD(Temporal_YearWeek, jsonSerialize) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_string *str = temporal_year_week_format_iso(THIS_TEMPORAL_YEAR_WEEK_INTERNAL());
	RETURN_STR(str);
}

ZEND_METHOD(Temporal_YearWeek, __toString) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_string *str = temporal_year_week_format_iso(THIS_TEMPORAL_YEAR_WEEK_INTERNAL());
	RETURN_STR(str);
}

ZEND_METHOD(Temporal_YearWeek, __serialize) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_year_week_t *year_week = THIS_TEMPORAL_YEAR_WEEK_INTERNAL();

	array_init(return_value);
	HashTable *ht = Z_ARRVAL_P(return_value);

	zval tmp;

	ZVAL_LONG(&tmp, year_week->year);
	zend_hash_str_update(ht, "year", strlen("year"), &tmp);

	ZVAL_LONG(&tmp, year_week->week);
	zend_hash_str_update(ht, "week", strlen("week"), &tmp);
}

ZEND_METHOD(Temporal_YearWeek, __unserialize) {
	HashTable *ht;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_ARRAY_HT(ht)
	ZEND_PARSE_PARAMETERS_END();

	temporal_year_week_t *year_week = THIS_TEMPORAL_YEAR_WEEK_INTERNAL();

	zval *year = zend_hash_str_find(ht, "year", strlen("year"));
	if (year == NULL || Z_TYPE_P(year) != IS_LONG) {
		php_temporal_throw_exception("Failed to unserialize Temporal value from data.", 0);
		RETURN_THROWS();
	}

	zval *week = zend_hash_str_find(ht, "week", strlen("week"));
	if (week == NULL || Z_TYPE_P(week) != IS_LONG) {
		php_temporal_throw_exception("Failed to unserialize Temporal value from data.", 0);
		RETURN_THROWS();
	}

	year_week->year = Z_LVAL_P(year);
	year_week->week = Z_LVAL_P(week);
}

zend_class_entry *php_temporal_year_week_ce;

void php_temporal_register_year_week_ce() {
	php_temporal_year_week_ce = register_class_Temporal_YearWeek(php_json_serializable_ce, zend_ce_stringable);
	php_temporal_year_week_ce->create_object = php_temporal_year_week_create_object;

	php_temporal_register_year_week_handlers();
}
