#include "year_month_ce.h"
#include <ext/date/php_date.h>
#include <ext/json/php_json.h>
#include <php.h>
#include <zend_interfaces.h>
#include <zend_smart_str.h>
#include "year_month.h"
#include "year_month_arginfo.h"
#include "year_month_handlers.h"
#include "year_month_obj.h"
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

ZEND_METHOD(Temporal_YearMonth, __construct) {
	// private
}

ZEND_METHOD(Temporal_YearMonth, of) {
	zend_long year, month;

	ZEND_PARSE_PARAMETERS_START(2, 2)
	Z_PARAM_LONG(year)
	Z_PARAM_LONG(month)
	ZEND_PARSE_PARAMETERS_END();

	TEMPORAL_CHECK_VALUE_RANGE("year", year, -999999, 999999);
	TEMPORAL_CHECK_VALUE_RANGE("month", month, 1, 12);

	temporal_year_month_t *year_month = temporal_year_month_of(year, month);
	zend_object *object = php_temporal_year_month_create_object_ex(year_month);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_YearMonth, now) {
	zval *time_zone, *clock = NULL;

	ZEND_PARSE_PARAMETERS_START(1, 2)
	Z_PARAM_OBJECT_OF_CLASS(time_zone, php_temporal_time_zone_ce)
	Z_PARAM_OPTIONAL
	Z_PARAM_OBJECT_OF_CLASS_OR_NULL(clock, php_temporal_clock_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_now(Z_TEMPORAL_TIME_ZONE_INTERNAL_P(time_zone), Z_OBJ_P(clock));
	temporal_year_month_t *year_month = temporal_year_month_of(zoned_date_time->date_time->date->year, zoned_date_time->date_time->date->month);

	temporal_zoned_date_time_free(zoned_date_time);

	zend_object *object = php_temporal_year_month_create_object_ex(year_month);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_YearMonth, parse) {
	zend_string *input;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_STR(input)
	ZEND_PARSE_PARAMETERS_END();

	const char *input_s = ZSTR_VAL(input);

	temporal_year_month_t *year_month = temporal_year_month_parse_iso(input_s);
	if (year_month == NULL) {
		php_temporal_throw_exception("Failed to parse given input into a Temporal value.", 0);
		RETURN_THROWS();
	}

	zend_object *object = php_temporal_year_month_create_object_ex(year_month);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_YearMonth, getYear) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long year = THIS_TEMPORAL_YEAR_MONTH_INTERNAL()->year;
	RETURN_LONG(year);
}

ZEND_METHOD(Temporal_YearMonth, withYear) {
	zend_long year;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(year)
	ZEND_PARSE_PARAMETERS_END();

	TEMPORAL_CHECK_VALUE_RANGE("year", year, -999999, 999999);

	temporal_year_month_t *year_month = temporal_year_month_of(year, THIS_TEMPORAL_YEAR_MONTH_INTERNAL()->month);
	zend_object *object = php_temporal_year_month_create_object_ex(year_month);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_YearMonth, plusYears) {
	zend_long years;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(years)
	ZEND_PARSE_PARAMETERS_END();

	zend_long year = THIS_TEMPORAL_YEAR_MONTH_INTERNAL()->year + years;
	TEMPORAL_CHECK_VALUE_RANGE("year", year, -999999, 999999);

	temporal_year_month_t *year_month = temporal_year_month_of(year, THIS_TEMPORAL_YEAR_MONTH_INTERNAL()->month);
	zend_object *object = php_temporal_year_month_create_object_ex(year_month);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_YearMonth, minusYears) {
	zend_long years;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(years)
	ZEND_PARSE_PARAMETERS_END();

	zend_long year = THIS_TEMPORAL_YEAR_MONTH_INTERNAL()->year - years;
	TEMPORAL_CHECK_VALUE_RANGE("year", year, -999999, 999999);

	temporal_year_month_t *year_month = temporal_year_month_of(year, THIS_TEMPORAL_YEAR_MONTH_INTERNAL()->month);
	zend_object *object = php_temporal_year_month_create_object_ex(year_month);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_YearMonth, getMonth) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long month = THIS_TEMPORAL_YEAR_MONTH_INTERNAL()->month;
	RETURN_LONG(month);
}

ZEND_METHOD(Temporal_YearMonth, withMonth) {
	zend_long month;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(month)
	ZEND_PARSE_PARAMETERS_END();

	TEMPORAL_CHECK_VALUE_RANGE("month", month, 1, 12);

	temporal_year_month_t *year_month = temporal_year_month_of(THIS_TEMPORAL_YEAR_MONTH_INTERNAL()->year, month);
	zend_object *object = php_temporal_year_month_create_object_ex(year_month);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_YearMonth, plusMonths) {
	zend_long months;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(months)
	ZEND_PARSE_PARAMETERS_END();

	temporal_year_month_t *year_month = temporal_year_month_plus_months(THIS_TEMPORAL_YEAR_MONTH_INTERNAL(), months);
	zend_object *object = php_temporal_year_month_create_object_ex(year_month);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_YearMonth, minusMonths) {
	zend_long months;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(months)
	ZEND_PARSE_PARAMETERS_END();

	temporal_year_month_t *year_month = temporal_year_month_plus_months(THIS_TEMPORAL_YEAR_MONTH_INTERNAL(), -months);
	zend_object *object = php_temporal_year_month_create_object_ex(year_month);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_YearMonth, getDaysInMonth) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long days = days_in_month(THIS_TEMPORAL_YEAR_MONTH_INTERNAL()->year, THIS_TEMPORAL_YEAR_MONTH_INTERNAL()->month);
	RETURN_LONG(days);
}

ZEND_METHOD(Temporal_YearMonth, getDaysInYear) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long days = days_in_year(THIS_TEMPORAL_YEAR_MONTH_INTERNAL()->year);
	RETURN_LONG(days);
}

ZEND_METHOD(Temporal_YearMonth, getWeeksInYear) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long weeks = weeks_in_year(THIS_TEMPORAL_YEAR_MONTH_INTERNAL()->year);
	RETURN_LONG(weeks);
}

ZEND_METHOD(Temporal_YearMonth, isLeapYear) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_bool result = is_leap_year(THIS_TEMPORAL_YEAR_MONTH_INTERNAL()->year);
	RETURN_BOOL(result);
}

ZEND_METHOD(Temporal_YearMonth, atDay) {
	zend_long day_of_month;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(day_of_month)
	ZEND_PARSE_PARAMETERS_END();

	zend_long max_day = days_in_month(THIS_TEMPORAL_YEAR_MONTH_INTERNAL()->year, THIS_TEMPORAL_YEAR_MONTH_INTERNAL()->month);
	TEMPORAL_CHECK_VALUE_RANGE("dayOfMonth", day_of_month, -999999, max_day);

	temporal_local_date_t *local_date = temporal_local_date_of(THIS_TEMPORAL_YEAR_MONTH_INTERNAL()->year, THIS_TEMPORAL_YEAR_MONTH_INTERNAL()->month, day_of_month);
	zend_object *object = php_temporal_local_date_create_object_ex(local_date);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_YearMonth, getFirstDay) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_date_t *local_date = temporal_local_date_of(THIS_TEMPORAL_YEAR_MONTH_INTERNAL()->year, THIS_TEMPORAL_YEAR_MONTH_INTERNAL()->month, 1);
	zend_object *object = php_temporal_local_date_create_object_ex(local_date);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_YearMonth, getLastDay) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_long last_day = days_in_month(THIS_TEMPORAL_YEAR_MONTH_INTERNAL()->year, THIS_TEMPORAL_YEAR_MONTH_INTERNAL()->month);

	temporal_local_date_t *local_date = temporal_local_date_of(THIS_TEMPORAL_YEAR_MONTH_INTERNAL()->year, THIS_TEMPORAL_YEAR_MONTH_INTERNAL()->month, last_day);
	zend_object *object = php_temporal_local_date_create_object_ex(local_date);
	RETURN_OBJ(object);
}

#define TEMPORAL_YEAR_MONTH_COMPARE                                                    \
	zend_object *other;                                                                \
	ZEND_PARSE_PARAMETERS_START(1, 1)                                                  \
	Z_PARAM_OBJ_OF_CLASS(other, php_temporal_year_month_ce)                            \
	ZEND_PARSE_PARAMETERS_END();                                                       \
	temporal_year_month_t *a = THIS_TEMPORAL_YEAR_MONTH_INTERNAL();                    \
	temporal_year_month_t *b = php_temporal_year_month_from_object(other)->year_month; \
	int result = temporal_year_month_compare(a, b);

ZEND_METHOD(Temporal_YearMonth, compareTo) {
	TEMPORAL_YEAR_MONTH_COMPARE
	RETURN_LONG(result);
}

ZEND_METHOD(Temporal_YearMonth, isEqualTo) {
	TEMPORAL_YEAR_MONTH_COMPARE
	RETURN_BOOL(result == 0);
}

ZEND_METHOD(Temporal_YearMonth, isBefore) {
	TEMPORAL_YEAR_MONTH_COMPARE
	RETURN_BOOL(result < 0);
}

ZEND_METHOD(Temporal_YearMonth, isBeforeOrEqualTo) {
	TEMPORAL_YEAR_MONTH_COMPARE
	RETURN_BOOL(result <= 0);
}

ZEND_METHOD(Temporal_YearMonth, isAfter) {
	TEMPORAL_YEAR_MONTH_COMPARE
	RETURN_BOOL(result > 0);
}

ZEND_METHOD(Temporal_YearMonth, isAfterOrEqualTo) {
	TEMPORAL_YEAR_MONTH_COMPARE
	RETURN_BOOL(result >= 0);
}

ZEND_METHOD(Temporal_YearMonth, toISOString) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_string *str = temporal_year_month_format_iso(THIS_TEMPORAL_YEAR_MONTH_INTERNAL());
	RETURN_STR(str);
}

ZEND_METHOD(Temporal_YearMonth, jsonSerialize) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_string *str = temporal_year_month_format_iso(THIS_TEMPORAL_YEAR_MONTH_INTERNAL());
	RETURN_STR(str);
}

ZEND_METHOD(Temporal_YearMonth, __toString) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_string *str = temporal_year_month_format_iso(THIS_TEMPORAL_YEAR_MONTH_INTERNAL());
	RETURN_STR(str);
}

ZEND_METHOD(Temporal_YearMonth, __serialize) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_year_month_t *year_month = THIS_TEMPORAL_YEAR_MONTH_INTERNAL();

	array_init(return_value);
	HashTable *ht = Z_ARRVAL_P(return_value);

	zval tmp;

	ZVAL_LONG(&tmp, year_month->year);
	zend_hash_str_update(ht, "year", strlen("year"), &tmp);

	ZVAL_LONG(&tmp, year_month->month);
	zend_hash_str_update(ht, "month", strlen("month"), &tmp);
}

ZEND_METHOD(Temporal_YearMonth, __unserialize) {
	HashTable *ht;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_ARRAY_HT(ht)
	ZEND_PARSE_PARAMETERS_END();

	temporal_year_month_t *year_month = THIS_TEMPORAL_YEAR_MONTH_INTERNAL();

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

	year_month->year = Z_LVAL_P(year);
	year_month->month = Z_LVAL_P(month);
}

zend_class_entry *php_temporal_year_month_ce;

void php_temporal_register_year_month_ce() {
	php_temporal_year_month_ce = register_class_Temporal_YearMonth(php_json_serializable_ce, zend_ce_stringable);
	php_temporal_year_month_ce->create_object = php_temporal_year_month_create_object;

	php_temporal_register_year_month_handlers();
}
