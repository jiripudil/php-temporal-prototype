#include "time_zone_offset_ce.h"
#include <ext/date/php_date.h>
#include <php.h>
#include <zend_exceptions.h>
#include "exception/exception_obj.h"
#include "instant/instant_ce.h"
#include "instant/instant_obj.h"
#include "time_zone/time_zone.h"
#include "time_zone/time_zone_ce.h"
#include "time_zone/time_zone_obj.h"
#include "utils/check_range.h"
#include "time_zone_offset.h"
#include "time_zone_offset_arginfo.h"

ZEND_METHOD(Temporal_TimeZoneOffset, __construct) {
	// private
}

ZEND_METHOD(Temporal_TimeZoneOffset, of) {
	zend_long hours, minutes = 0, seconds = 0;

	ZEND_PARSE_PARAMETERS_START(1, 3)
	Z_PARAM_LONG(hours)
	Z_PARAM_OPTIONAL
	Z_PARAM_LONG(minutes)
	Z_PARAM_LONG(seconds)
	ZEND_PARSE_PARAMETERS_END();

	TEMPORAL_CHECK_VALUE_RANGE("hours", hours, -18, 18);
	TEMPORAL_CHECK_VALUE_RANGE("minutes", minutes, -MINUTES_PER_HOUR + 1, MINUTES_PER_HOUR - 1);
	TEMPORAL_CHECK_VALUE_RANGE("seconds", seconds, -SECONDS_PER_MINUTE + 1, SECONDS_PER_MINUTE - 1);

	if ((hours > 0 && (minutes < 0 || seconds < 0))
		|| (hours < 0 && (minutes > 0 || seconds > 0))
		|| (minutes > 0 && seconds < 0)
		|| (minutes < 0 && seconds > 0)
	) {
		php_temporal_throw_exception("Failed to parse given input into a Temporal value.", 0);
		RETURN_THROWS();
	}

	temporal_time_zone_offset_t *offset = temporal_time_zone_offset_of(hours, minutes, seconds);
	temporal_time_zone_t *time_zone = temporal_time_zone_of_offset(offset);
	zend_object *object = php_temporal_time_zone_create_object_ex(time_zone);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_TimeZoneOffset, ofTotalSeconds) {
	zend_long total_seconds;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(total_seconds)
	ZEND_PARSE_PARAMETERS_END();

	TEMPORAL_CHECK_VALUE_RANGE("totalSeconds", total_seconds, -64800, 64800);

	temporal_time_zone_offset_t *offset = temporal_time_zone_offset_of_total_seconds(total_seconds);
	temporal_time_zone_t *time_zone = temporal_time_zone_of_offset(offset);
	zend_object *object = php_temporal_time_zone_create_object_ex(time_zone);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_TimeZoneOffset, fromISOString) {
	zend_string *input;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_STR(input)
	ZEND_PARSE_PARAMETERS_END();

	const char *input_s = ZSTR_VAL(input);

	temporal_time_zone_offset_t *offset = temporal_time_zone_offset_parse_iso(input_s);
	if (offset == NULL) {
		php_temporal_throw_exception("Failed to parse given input into a Temporal value.", 0);
		RETURN_THROWS();
	}

	temporal_time_zone_t *time_zone = temporal_time_zone_of_offset(offset);
	zend_object *object = php_temporal_time_zone_create_object_ex(time_zone);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_TimeZoneOffset, utc) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_time_zone_offset_t *offset = temporal_time_zone_offset_utc();
	temporal_time_zone_t *time_zone = temporal_time_zone_of_offset(offset);
	zend_object *object = php_temporal_time_zone_create_object_ex(time_zone);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_TimeZoneOffset, getTotalSeconds) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_long total_seconds = THIS_TEMPORAL_TIME_ZONE_INTERNAL()->offset->total_seconds;
	RETURN_LONG(total_seconds);
}

ZEND_METHOD(Temporal_TimeZoneOffset, getId) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_string *id = temporal_time_zone_offset_id(THIS_TEMPORAL_TIME_ZONE_INTERNAL()->offset);
	RETURN_STR(id);
}

ZEND_METHOD(Temporal_TimeZoneOffset, getOffset) {
	zval *instant;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(instant, php_temporal_instant_ce)
	ZEND_PARSE_PARAMETERS_END();

	zend_long total_seconds = THIS_TEMPORAL_TIME_ZONE_INTERNAL()->offset->total_seconds;
	RETURN_LONG(total_seconds);
}

ZEND_METHOD(Temporal_TimeZoneOffset, toDateTimeZone) {
	ZEND_PARSE_PARAMETERS_NONE();

	object_init_ex(return_value, php_date_get_timezone_ce());
	php_timezone_obj *tz_obj = Z_PHPTIMEZONE_P(return_value);

	tz_obj->initialized = 1;
	tz_obj->type = TIMELIB_ZONETYPE_OFFSET;
	tz_obj->tzi.utc_offset = THIS_TEMPORAL_TIME_ZONE_INTERNAL()->offset->total_seconds;
}

ZEND_METHOD(Temporal_TimeZoneOffset, __serialize) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_time_zone_t *time_zone = THIS_TEMPORAL_TIME_ZONE_INTERNAL();

	array_init(return_value);
	HashTable *ht = Z_ARRVAL_P(return_value);

	zval tmp;

	ZVAL_LONG(&tmp, time_zone->offset->total_seconds);
	zend_hash_str_update(ht, "totalSeconds", strlen("totalSeconds"), &tmp);
}

ZEND_METHOD(Temporal_TimeZoneOffset, __unserialize) {
	HashTable *ht;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_ARRAY_HT(ht)
	ZEND_PARSE_PARAMETERS_END();

	zval *total_seconds = zend_hash_str_find(ht, "totalSeconds", strlen("totalSeconds"));
	if (total_seconds == NULL || Z_TYPE_P(total_seconds) != IS_LONG) {
		php_temporal_throw_exception("Failed to unserialize Temporal value from data.", 0);
		RETURN_THROWS();
	}

	temporal_time_zone_free(THIS_TEMPORAL_TIME_ZONE_INTERNAL());

	temporal_time_zone_offset_t *time_zone_offset = temporal_time_zone_offset_of_total_seconds(Z_LVAL_P(total_seconds));
	THIS_TEMPORAL_TIME_ZONE_INTERNAL() = temporal_time_zone_of_offset(time_zone_offset);
}

zend_class_entry *php_temporal_time_zone_offset_ce;

void php_temporal_register_time_zone_offset_ce() {
	php_temporal_time_zone_offset_ce = register_class_Temporal_TimeZoneOffset(php_temporal_time_zone_ce);
}
