#include "month_day_ce.h"
#include <ext/date/php_date.h>
#include <ext/json/php_json.h>
#include <php.h>
#include <zend_interfaces.h>
#include <zend_smart_str.h>
#include "month_day.h"
#include "month_day_arginfo.h"
#include "month_day_handlers.h"
#include "month_day_obj.h"
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

ZEND_METHOD(Temporal_MonthDay, __construct) {
	// private
}

ZEND_METHOD(Temporal_MonthDay, of) {
	zend_long month, day;

	ZEND_PARSE_PARAMETERS_START(2, 2)
	Z_PARAM_LONG(month)
	Z_PARAM_LONG(day)
	ZEND_PARSE_PARAMETERS_END();

	TEMPORAL_CHECK_VALUE_RANGE("month", month, 1, 12);

	zend_long max_day = max_days_in_month(month);
	TEMPORAL_CHECK_VALUE_RANGE("day", day, 1, max_day);

	temporal_month_day_t *month_day = temporal_month_day_of(month, day);
	zend_object *object = php_temporal_month_day_create_object_ex(month_day);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_MonthDay, now) {
	zval *time_zone, *clock = NULL;

	ZEND_PARSE_PARAMETERS_START(1, 2)
	Z_PARAM_OBJECT_OF_CLASS(time_zone, php_temporal_time_zone_ce)
	Z_PARAM_OPTIONAL
	Z_PARAM_OBJECT_OF_CLASS_OR_NULL(clock, php_temporal_clock_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_now(temporal_time_zone_clone(Z_TEMPORAL_TIME_ZONE_INTERNAL_P(time_zone)), Z_OBJ_P(clock));
	temporal_month_day_t *month_day = temporal_month_day_of(zoned_date_time->date_time->date->month, zoned_date_time->date_time->date->day);

	temporal_zoned_date_time_free(zoned_date_time);

	zend_object *object = php_temporal_month_day_create_object_ex(month_day);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_MonthDay, fromIsoString) {
	zend_string *input;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_STR(input)
	ZEND_PARSE_PARAMETERS_END();

	const char *input_s = ZSTR_VAL(input);

	temporal_parse_iso_result_t *result = temporal_month_day_parse_iso(input_s);
	if (result == NULL) {
		php_temporal_throw_parsing_invalid_iso_string(input_s);
		RETURN_THROWS();
	}

	zend_long max_day = max_days_in_month(result->month);
	TEMPORAL_CHECK_PARSE_ISO_VALUE_RANGE(input_s, result, "month", result->month, 1, 12)
	TEMPORAL_CHECK_PARSE_ISO_VALUE_RANGE(input_s, result, "day", result->day, 1, max_day)

	temporal_month_day_t *month_day = temporal_month_day_of(result->month, result->day);
	temporal_parse_iso_result_free(result);

	zend_object *object = php_temporal_month_day_create_object_ex(month_day);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_MonthDay, getMonth) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long month = THIS_TEMPORAL_MONTH_DAY_INTERNAL()->month;
	RETURN_LONG(month);
}

ZEND_METHOD(Temporal_MonthDay, withMonth) {
	zend_long month;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(month)
	ZEND_PARSE_PARAMETERS_END();

	TEMPORAL_CHECK_VALUE_RANGE("month", month, 1, 12);

	zend_long day = THIS_TEMPORAL_MONTH_DAY_INTERNAL()->day;

	zend_long max_days = max_days_in_month(month);
	if (day > max_days) {
		day = max_days;
	}

	temporal_month_day_t *month_day = temporal_month_day_of(month, day);
	zend_object *object = php_temporal_month_day_create_object_ex(month_day);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_MonthDay, getDayOfMonth) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long day = THIS_TEMPORAL_MONTH_DAY_INTERNAL()->day;
	RETURN_LONG(day);
}

ZEND_METHOD(Temporal_MonthDay, withDayOfMonth) {
	zend_long day;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(day)
	ZEND_PARSE_PARAMETERS_END();

	zend_long max_days = max_days_in_month(THIS_TEMPORAL_MONTH_DAY_INTERNAL()->month);
	TEMPORAL_CHECK_VALUE_RANGE("dayOfMonth", day, 1, max_days);

	temporal_month_day_t *month_day = temporal_month_day_of(THIS_TEMPORAL_MONTH_DAY_INTERNAL()->month, day);
	zend_object *object = php_temporal_month_day_create_object_ex(month_day);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_MonthDay, existsInYear) {
	zend_long year;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(year)
	ZEND_PARSE_PARAMETERS_END();

	temporal_month_day_t *month_day = THIS_TEMPORAL_MONTH_DAY_INTERNAL();
	RETURN_BOOL(month_day->month != 2 || month_day->day != 29 || is_leap_year(year));
}

ZEND_METHOD(Temporal_MonthDay, atYear) {
	zend_long year;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(year)
	ZEND_PARSE_PARAMETERS_END();

	TEMPORAL_CHECK_VALUE_RANGE("year", year, -999999, 999999);

	zend_long month = THIS_TEMPORAL_MONTH_DAY_INTERNAL()->month;
	zend_long day = THIS_TEMPORAL_MONTH_DAY_INTERNAL()->day;
	zend_long max_days = days_in_month(year, month);
	if (day > max_days) {
		day = max_days;
	}

	temporal_local_date_t *local_date = temporal_local_date_of(year, month, day);
	zend_object *object = php_temporal_local_date_create_object_ex(local_date);
	RETURN_OBJ(object);
}

#define TEMPORAL_MONTH_DAY_COMPARE                                                  \
	zend_object *other;                                                             \
	ZEND_PARSE_PARAMETERS_START(1, 1)                                               \
	Z_PARAM_OBJ_OF_CLASS(other, php_temporal_month_day_ce)                          \
	ZEND_PARSE_PARAMETERS_END();                                                    \
	temporal_month_day_t *a = THIS_TEMPORAL_MONTH_DAY_INTERNAL();                   \
	temporal_month_day_t *b = php_temporal_month_day_from_object(other)->month_day; \
	int result = temporal_month_day_compare(a, b);

ZEND_METHOD(Temporal_MonthDay, compareTo) {
	TEMPORAL_MONTH_DAY_COMPARE
	RETURN_LONG(result);
}

ZEND_METHOD(Temporal_MonthDay, isEqualTo) {
	TEMPORAL_MONTH_DAY_COMPARE
	RETURN_BOOL(result == 0);
}

ZEND_METHOD(Temporal_MonthDay, isBefore) {
	TEMPORAL_MONTH_DAY_COMPARE
	RETURN_BOOL(result < 0);
}

ZEND_METHOD(Temporal_MonthDay, isBeforeOrEqualTo) {
	TEMPORAL_MONTH_DAY_COMPARE
	RETURN_BOOL(result <= 0);
}

ZEND_METHOD(Temporal_MonthDay, isAfter) {
	TEMPORAL_MONTH_DAY_COMPARE
	RETURN_BOOL(result > 0);
}

ZEND_METHOD(Temporal_MonthDay, isAfterOrEqualTo) {
	TEMPORAL_MONTH_DAY_COMPARE
	RETURN_BOOL(result >= 0);
}

ZEND_METHOD(Temporal_MonthDay, toIsoString) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_string *str = temporal_month_day_format_iso(THIS_TEMPORAL_MONTH_DAY_INTERNAL());
	RETURN_STR(str);
}

ZEND_METHOD(Temporal_MonthDay, jsonSerialize) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_string *str = temporal_month_day_format_iso(THIS_TEMPORAL_MONTH_DAY_INTERNAL());
	RETURN_STR(str);
}

ZEND_METHOD(Temporal_MonthDay, __toString) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_string *str = temporal_month_day_format_iso(THIS_TEMPORAL_MONTH_DAY_INTERNAL());
	RETURN_STR(str);
}

ZEND_METHOD(Temporal_MonthDay, __serialize) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_month_day_t *month_day = THIS_TEMPORAL_MONTH_DAY_INTERNAL();

	array_init(return_value);
	HashTable *ht = Z_ARRVAL_P(return_value);

	zval tmp;

	ZVAL_LONG(&tmp, month_day->month);
	zend_hash_str_update(ht, "month", strlen("month"), &tmp);

	ZVAL_LONG(&tmp, month_day->day);
	zend_hash_str_update(ht, "day", strlen("day"), &tmp);
}

ZEND_METHOD(Temporal_MonthDay, __unserialize) {
	HashTable *ht;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_ARRAY_HT(ht)
	ZEND_PARSE_PARAMETERS_END();

	temporal_month_day_t *month_day = THIS_TEMPORAL_MONTH_DAY_INTERNAL();

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

	month_day->month = Z_LVAL_P(month);
	month_day->day = Z_LVAL_P(day);
}

zend_class_entry *php_temporal_month_day_ce;

void php_temporal_register_month_day_ce() {
	php_temporal_month_day_ce = register_class_Temporal_MonthDay(php_json_serializable_ce, zend_ce_stringable);
	php_temporal_month_day_ce->create_object = php_temporal_month_day_create_object;

	php_temporal_register_month_day_handlers();
}
