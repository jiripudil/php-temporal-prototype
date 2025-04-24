#include "local_time_ce.h"
#include <ext/date/php_date.h>
#include <ext/json/php_json.h>
#include <php.h>
#include <unicode/udat.h>
#include <zend_interfaces.h>
#include <zend_smart_str.h>
#include "local_time.h"
#include "local_time_arginfo.h"
#include "local_time_handlers.h"
#include "local_time_obj.h"
#include "clock/clock_ce.h"
#include "duration/duration_ce.h"
#include "duration/duration_obj.h"
#include "exception/exception_obj.h"
#include "format/formatter.h"
#include "format/formatter_ce.h"
#include "format/formatter_obj.h"
#include "local_date/local_date.h"
#include "local_date/local_date_ce.h"
#include "local_date/local_date_obj.h"
#include "local_date_time/local_date_time.h"
#include "local_date_time/local_date_time_obj.h"
#include "time_zone/time_zone.h"
#include "time_zone/time_zone_ce.h"
#include "time_zone/time_zone_obj.h"
#include "utils/check_range.h"
#include "zoned_date_time/zoned_date_time.h"

ZEND_METHOD(Temporal_LocalTime, __construct) {
	// private
}

ZEND_METHOD(Temporal_LocalTime, of) {
	zend_long hour, minute, second = 0, nano = 0;

	ZEND_PARSE_PARAMETERS_START(2, 4)
	Z_PARAM_LONG(hour)
	Z_PARAM_LONG(minute)
	Z_PARAM_OPTIONAL
	Z_PARAM_LONG(second)
	Z_PARAM_LONG(nano)
	ZEND_PARSE_PARAMETERS_END();

	TEMPORAL_CHECK_VALUE_RANGE("hour", hour, 0, HOURS_PER_DAY - 1);
	TEMPORAL_CHECK_VALUE_RANGE("minute", minute, 0, MINUTES_PER_HOUR - 1);
	TEMPORAL_CHECK_VALUE_RANGE("second", second, 0, SECONDS_PER_MINUTE - 1);
	TEMPORAL_CHECK_VALUE_RANGE("nano", nano, 0, NANOS_PER_SECOND - 1);

	temporal_local_time_t *local_time = temporal_local_time_of(hour, minute, second, nano);
	zend_object *object = php_temporal_local_time_create_object_ex(local_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalTime, ofSecondOfDay) {
	zend_long second_of_day, nano = 0;

	ZEND_PARSE_PARAMETERS_START(1, 2)
	Z_PARAM_LONG(second_of_day)
	Z_PARAM_OPTIONAL
	Z_PARAM_LONG(nano)
	ZEND_PARSE_PARAMETERS_END();

	TEMPORAL_CHECK_VALUE_RANGE("secondOfDay", second_of_day, 0, SECONDS_PER_DAY - 1);
	TEMPORAL_CHECK_VALUE_RANGE("nano", nano, 0, NANOS_PER_SECOND - 1);

	temporal_local_time_t *local_time = temporal_local_time_of_seconds_of_day(second_of_day, nano);
	zend_object *object = php_temporal_local_time_create_object_ex(local_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalTime, now) {
	zval *time_zone;
	zend_object *clock = NULL;

	ZEND_PARSE_PARAMETERS_START(1, 2)
	Z_PARAM_OBJECT_OF_CLASS(time_zone, php_temporal_time_zone_ce)
	Z_PARAM_OPTIONAL
	Z_PARAM_OBJ_OF_CLASS_OR_NULL(clock, php_temporal_clock_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_now(temporal_time_zone_clone(Z_TEMPORAL_TIME_ZONE_INTERNAL_P(time_zone)), clock);
	temporal_local_time_t *local_time = temporal_local_time_clone(zoned_date_time->date_time->time);

	temporal_zoned_date_time_free(zoned_date_time);

	zend_object *object = php_temporal_local_time_create_object_ex(local_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalTime, fromISOString) {
	zend_string *input;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_STR(input)
	ZEND_PARSE_PARAMETERS_END();

	const char *input_s = ZSTR_VAL(input);

	temporal_local_time_t *local_time = temporal_local_time_parse_iso(input_s);
	if (local_time == NULL) {
		php_temporal_throw_exception("Failed to parse given input into a Temporal value.", 0);
		RETURN_THROWS();
	}

	zend_object *object = php_temporal_local_time_create_object_ex(local_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalTime, midnight) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_time_t *local_time = temporal_local_time_of(0, 0, 0, 0);
	zend_object *object = php_temporal_local_time_create_object_ex(local_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalTime, noon) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_time_t *local_time = temporal_local_time_of(12, 0, 0, 0);
	zend_object *object = php_temporal_local_time_create_object_ex(local_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalTime, min) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_time_t *local_time = temporal_local_time_of(0, 0, 0, 0);
	zend_object *object = php_temporal_local_time_create_object_ex(local_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalTime, max) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_time_t *local_time = temporal_local_time_of(23, 59, 59, 999999999);
	zend_object *object = php_temporal_local_time_create_object_ex(local_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalTime, getHour) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_long result = THIS_TEMPORAL_LOCAL_TIME_INTERNAL()->hour;
	RETURN_LONG(result);
}

ZEND_METHOD(Temporal_LocalTime, withHour) {
	zend_long hour;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(hour)
	ZEND_PARSE_PARAMETERS_END();

	TEMPORAL_CHECK_VALUE_RANGE("hour", hour, 0, HOURS_PER_DAY - 1);

	temporal_local_time_t *copy = temporal_local_time_clone(THIS_TEMPORAL_LOCAL_TIME_INTERNAL());
	copy->hour = hour;

	zend_object *object = php_temporal_local_time_create_object_ex(copy);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalTime, getMinute) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_long result = THIS_TEMPORAL_LOCAL_TIME_INTERNAL()->minute;
	RETURN_LONG(result);
}

ZEND_METHOD(Temporal_LocalTime, withMinute) {
	zend_long minute;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(minute)
	ZEND_PARSE_PARAMETERS_END();

	TEMPORAL_CHECK_VALUE_RANGE("minute", minute, 0, MINUTES_PER_HOUR - 1);

	temporal_local_time_t *copy = temporal_local_time_clone(THIS_TEMPORAL_LOCAL_TIME_INTERNAL());
	copy->minute = minute;

	zend_object *object = php_temporal_local_time_create_object_ex(copy);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalTime, getSecond) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_long result = THIS_TEMPORAL_LOCAL_TIME_INTERNAL()->second;
	RETURN_LONG(result);
}

ZEND_METHOD(Temporal_LocalTime, withSecond) {
	zend_long second;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(second)
	ZEND_PARSE_PARAMETERS_END();

	TEMPORAL_CHECK_VALUE_RANGE("second", second, 0, SECONDS_PER_MINUTE - 1);

	temporal_local_time_t *copy = temporal_local_time_clone(THIS_TEMPORAL_LOCAL_TIME_INTERNAL());
	copy->second = second;

	zend_object *object = php_temporal_local_time_create_object_ex(copy);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalTime, getNano) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_long result = THIS_TEMPORAL_LOCAL_TIME_INTERNAL()->nano;
	RETURN_LONG(result);
}

ZEND_METHOD(Temporal_LocalTime, withNano) {
	zend_long nano;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(nano)
	ZEND_PARSE_PARAMETERS_END();

	TEMPORAL_CHECK_VALUE_RANGE("nano", nano, 0, NANOS_PER_SECOND - 1);

	temporal_local_time_t *copy = temporal_local_time_clone(THIS_TEMPORAL_LOCAL_TIME_INTERNAL());
	copy->nano = nano;

	zend_object *object = php_temporal_local_time_create_object_ex(copy);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalTime, getSecondOfDay) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_long result = temporal_local_time_seconds_of_day(THIS_TEMPORAL_LOCAL_TIME_INTERNAL());
	RETURN_LONG(result);
}

ZEND_METHOD(Temporal_LocalTime, plus) {
	zval *duration;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(duration, php_temporal_duration_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_time_t *local_time = temporal_local_time_plus(THIS_TEMPORAL_LOCAL_TIME_INTERNAL(), Z_TEMPORAL_DURATION_INTERNAL_P(duration));
	zend_object *object = php_temporal_local_time_create_object_ex(local_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalTime, plusHours) {
	zend_long hours;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(hours)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(hours * SECONDS_PER_HOUR, 0);
	temporal_local_time_t *local_time = temporal_local_time_plus(THIS_TEMPORAL_LOCAL_TIME_INTERNAL(), duration);
	temporal_duration_free(duration);

	zend_object *object = php_temporal_local_time_create_object_ex(local_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalTime, plusMinutes) {
	zend_long minutes;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(minutes)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(minutes * SECONDS_PER_MINUTE, 0);
	temporal_local_time_t *local_time = temporal_local_time_plus(THIS_TEMPORAL_LOCAL_TIME_INTERNAL(), duration);
	temporal_duration_free(duration);

	zend_object *object = php_temporal_local_time_create_object_ex(local_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalTime, plusSeconds) {
	zend_long seconds;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(seconds)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(seconds, 0);
	temporal_local_time_t *local_time = temporal_local_time_plus(THIS_TEMPORAL_LOCAL_TIME_INTERNAL(), duration);
	temporal_duration_free(duration);

	zend_object *object = php_temporal_local_time_create_object_ex(local_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalTime, plusNanos) {
	zend_long nanos;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(nanos)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(0, nanos);
	temporal_local_time_t *local_time = temporal_local_time_plus(THIS_TEMPORAL_LOCAL_TIME_INTERNAL(), duration);
	temporal_duration_free(duration);

	zend_object *object = php_temporal_local_time_create_object_ex(local_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalTime, minus) {
	zval *duration;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(duration, php_temporal_duration_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_time_t *local_time = temporal_local_time_minus(THIS_TEMPORAL_LOCAL_TIME_INTERNAL(), Z_TEMPORAL_DURATION_INTERNAL_P(duration));
	zend_object *object = php_temporal_local_time_create_object_ex(local_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalTime, minusHours) {
	zend_long hours;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(hours)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(hours * SECONDS_PER_HOUR, 0);
	temporal_local_time_t *local_time = temporal_local_time_minus(THIS_TEMPORAL_LOCAL_TIME_INTERNAL(), duration);
	temporal_duration_free(duration);

	zend_object *object = php_temporal_local_time_create_object_ex(local_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalTime, minusMinutes) {
	zend_long minutes;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(minutes)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(minutes * SECONDS_PER_MINUTE, 0);
	temporal_local_time_t *local_time = temporal_local_time_minus(THIS_TEMPORAL_LOCAL_TIME_INTERNAL(), duration);
	temporal_duration_free(duration);

	zend_object *object = php_temporal_local_time_create_object_ex(local_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalTime, minusSeconds) {
	zend_long seconds;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(seconds)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(seconds, 0);
	temporal_local_time_t *local_time = temporal_local_time_minus(THIS_TEMPORAL_LOCAL_TIME_INTERNAL(), duration);
	temporal_duration_free(duration);

	zend_object *object = php_temporal_local_time_create_object_ex(local_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalTime, minusNanos) {
	zend_long nanos;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(nanos)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(0, nanos);
	temporal_local_time_t *local_time = temporal_local_time_minus(THIS_TEMPORAL_LOCAL_TIME_INTERNAL(), duration);
	temporal_duration_free(duration);

	zend_object *object = php_temporal_local_time_create_object_ex(local_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalTime, atDate) {
	zval *date;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(date, php_temporal_local_date_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_date_t *local_date = temporal_local_date_clone(Z_TEMPORAL_LOCAL_DATE_INTERNAL_P(date));
	temporal_local_time_t *local_time = temporal_local_time_clone(THIS_TEMPORAL_LOCAL_TIME_INTERNAL());

	temporal_local_date_time_t *date_time = temporal_local_date_time_of_date_time(local_date, local_time);
	zend_object *object = php_temporal_local_date_time_create_object_ex(date_time);
	RETURN_OBJ(object);
}

#define TEMPORAL_LOCAL_TIME_COMPARE                                                    \
	zend_object *other;                                                                \
	ZEND_PARSE_PARAMETERS_START(1, 1)                                                  \
	Z_PARAM_OBJ_OF_CLASS(other, php_temporal_local_time_ce)                            \
	ZEND_PARSE_PARAMETERS_END();                                                       \
	temporal_local_time_t *a = THIS_TEMPORAL_LOCAL_TIME_INTERNAL();                    \
	temporal_local_time_t *b = php_temporal_local_time_from_object(other)->local_time; \
	int result = temporal_local_time_compare(a, b);

ZEND_METHOD(Temporal_LocalTime, compareTo) {
	TEMPORAL_LOCAL_TIME_COMPARE
	RETURN_LONG(result);
}

ZEND_METHOD(Temporal_LocalTime, isEqualTo) {
	TEMPORAL_LOCAL_TIME_COMPARE
	RETURN_BOOL(result == 0);
}

ZEND_METHOD(Temporal_LocalTime, isBefore) {
	TEMPORAL_LOCAL_TIME_COMPARE
	RETURN_BOOL(result < 0);
}

ZEND_METHOD(Temporal_LocalTime, isBeforeOrEqualTo) {
	TEMPORAL_LOCAL_TIME_COMPARE
	RETURN_BOOL(result <= 0);
}

ZEND_METHOD(Temporal_LocalTime, isAfter) {
	TEMPORAL_LOCAL_TIME_COMPARE
	RETURN_BOOL(result > 0);
}

ZEND_METHOD(Temporal_LocalTime, isAfterOrEqualTo) {
	TEMPORAL_LOCAL_TIME_COMPARE
	RETURN_BOOL(result >= 0);
}

ZEND_METHOD(Temporal_LocalTime, toDateTime) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_time_t *local_time = THIS_TEMPORAL_LOCAL_TIME_INTERNAL();

	smart_str buf_f = {0};
	smart_str_appends(&buf_f, "Y-m-d\\TH:i");

	smart_str buf_t = {0};
	smart_str_appends(&buf_t, "0000-01-01T");

	char hour_str[4];
	snprintf(hour_str, sizeof(hour_str), "%02lld", local_time->hour);
	smart_str_appends(&buf_t, hour_str);
	smart_str_appendc(&buf_t, ':');

	char minute_str[4];
	snprintf(minute_str, sizeof(minute_str), "%02lld", local_time->minute);
	smart_str_appends(&buf_t, minute_str);

	if (local_time->second != 0 || local_time->nano != 0) {
		smart_str_appends(&buf_f, ":s");

		smart_str_appendc(&buf_t, ':');
		char second_str[4];
		snprintf(second_str, sizeof(second_str), "%02lld", local_time->second);
		smart_str_appends(&buf_t, second_str);

		if (local_time->nano != 0) {
			smart_str_appends(&buf_f, ".u");

			smart_str_appendc(&buf_t, '.');
			char micro_str[8];
			snprintf(micro_str, sizeof(micro_str), "%06lld", local_time->nano / 1000);
			smart_str_appends(&buf_t, micro_str);
		}
	}

	smart_str_appends(&buf_f, " e");
	smart_str_appends(&buf_t, " UTC");

	zend_string *format = smart_str_extract(&buf_f);
	zend_string *value = smart_str_extract(&buf_t);

	php_date_instantiate(php_date_get_immutable_ce(), return_value);
	if (!php_date_initialize(Z_PHPDATE_P(return_value), ZSTR_VAL(value), ZSTR_LEN(value), ZSTR_VAL(format), NULL, PHP_DATE_INIT_FORMAT)) {
		zend_string_release_ex(format, 0);
		zend_string_release_ex(value, 0);

		php_temporal_throw_exception("Failed to convert LocalTime into DateTimeImmutable.", 0);
		RETURN_THROWS();
	}

	zend_string_release_ex(format, 0);
	zend_string_release_ex(value, 0);
}

ZEND_METHOD(Temporal_LocalTime, fromDateTime) {
	zval *date;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(date, php_date_get_interface_ce())
	ZEND_PARSE_PARAMETERS_END();

	php_date_obj *date_obj = Z_PHPDATE_P(date);
	temporal_local_time_t *local_time = temporal_local_time_of(date_obj->time->h, date_obj->time->i, date_obj->time->s, date_obj->time->us * 1000);
	zend_object *object = php_temporal_local_time_create_object_ex(local_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_LocalTime, toISOString) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_string *str = temporal_local_time_format_iso(THIS_TEMPORAL_LOCAL_TIME_INTERNAL());
	RETURN_STR(str);
}

ZEND_METHOD(Temporal_LocalTime, format) {
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

	zend_string *formatted = temporal_local_time_format(THIS_TEMPORAL_LOCAL_TIME_INTERNAL(), formatter);

	if (formatted == NULL) {
		RETURN_THROWS();
	}

	RETURN_STR(formatted);
}

ZEND_METHOD(Temporal_LocalTime, formatWith) {
	zval *formatter;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(formatter, php_temporal_formatter_ce)
	ZEND_PARSE_PARAMETERS_END();

	zend_string *formatted = temporal_local_time_format(
		THIS_TEMPORAL_LOCAL_TIME_INTERNAL(),
		Z_TEMPORAL_FORMATTER_INTERNAL_P(formatter)
	);

	if (formatted == NULL) {
		RETURN_THROWS();
	}

	RETURN_STR(formatted);
}

ZEND_METHOD(Temporal_LocalTime, jsonSerialize) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_string *str = temporal_local_time_format_iso(THIS_TEMPORAL_LOCAL_TIME_INTERNAL());
	RETURN_STR(str);
}

ZEND_METHOD(Temporal_LocalTime, __toString) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_string *str = temporal_local_time_format_iso(THIS_TEMPORAL_LOCAL_TIME_INTERNAL());
	RETURN_STR(str);
}

ZEND_METHOD(Temporal_LocalTime, __serialize) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_local_time_t *local_time = THIS_TEMPORAL_LOCAL_TIME_INTERNAL();

	array_init(return_value);
	HashTable *ht = Z_ARRVAL_P(return_value);

	zval tmp;

	ZVAL_LONG(&tmp, local_time->hour);
	zend_hash_str_update(ht, "hour", strlen("hour"), &tmp);

	ZVAL_LONG(&tmp, local_time->minute);
	zend_hash_str_update(ht, "minute", strlen("minute"), &tmp);

	ZVAL_LONG(&tmp, local_time->second);
	zend_hash_str_update(ht, "second", strlen("second"), &tmp);

	ZVAL_LONG(&tmp, local_time->nano);
	zend_hash_str_update(ht, "nano", strlen("nano"), &tmp);
}

ZEND_METHOD(Temporal_LocalTime, __unserialize) {
	HashTable *ht;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_ARRAY_HT(ht)
	ZEND_PARSE_PARAMETERS_END();

	temporal_local_time_t *local_time = THIS_TEMPORAL_LOCAL_TIME_INTERNAL();

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

	local_time->hour = Z_LVAL_P(hour);
	local_time->minute = Z_LVAL_P(minute);
	local_time->second = Z_LVAL_P(second);
	local_time->nano = Z_LVAL_P(nano);
}

zend_class_entry *php_temporal_local_time_ce;

void php_temporal_register_local_time_ce() {
	php_temporal_local_time_ce = register_class_Temporal_LocalTime(php_json_serializable_ce, zend_ce_stringable);
	php_temporal_local_time_ce->create_object = php_temporal_local_time_create_object;

	php_temporal_register_local_time_handlers();
}
