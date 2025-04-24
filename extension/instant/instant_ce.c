#include "instant_ce.h"
#include <ext/json/php_json.h>
#include <php.h>
#include <zend_interfaces.h>
#include <zend_long.h>
#include <zend_smart_str.h>
#include "instant_arginfo.h"
#include "instant_handlers.h"
#include "instant_obj.h"
#include "clock/clock_ce.h"
#include "clock/clock_obj.h"
#include "duration/duration.h"
#include "duration/duration_ce.h"
#include "duration/duration_obj.h"
#include "exception/exception_obj.h"
#include "time_zone/time_zone_ce.h"
#include "time_zone/time_zone_obj.h"
#include "utils/check_range.h"
#include "utils/remove_trailing_zeroes.h"
#include "zoned_date_time/zoned_date_time.h"
#include "zoned_date_time/zoned_date_time_obj.h"

ZEND_METHOD(Temporal_Instant, __construct) {
	// private
}

ZEND_METHOD(Temporal_Instant, of) {
	zend_long epoch_second, nano_adjustment = 0;

	ZEND_PARSE_PARAMETERS_START(1, 2)
	Z_PARAM_LONG(epoch_second)
	Z_PARAM_OPTIONAL
	Z_PARAM_LONG(nano_adjustment)
	ZEND_PARSE_PARAMETERS_END();

	temporal_instant_t *instant = temporal_instant_of(epoch_second, nano_adjustment);
	zend_object *object = php_temporal_instant_create_object_ex(instant);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Instant, now) {
	zend_object *clock = NULL;

	ZEND_PARSE_PARAMETERS_START(0, 1)
	Z_PARAM_OPTIONAL
	Z_PARAM_OBJ_OF_CLASS_OR_NULL(clock, php_temporal_clock_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_instant_t *instant = temporal_clock_get_time(clock);
	zend_object *object = php_temporal_instant_create_object_ex(instant);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Instant, epoch) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_instant_t *instant = temporal_instant_epoch();
	zend_object *object = php_temporal_instant_create_object_ex(instant);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Instant, min) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_instant_t *instant = temporal_instant_of(ZEND_LONG_MIN, 0);
	zend_object *object = php_temporal_instant_create_object_ex(instant);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Instant, max) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_instant_t *instant = temporal_instant_of(ZEND_LONG_MAX, 999999999);
	zend_object *object = php_temporal_instant_create_object_ex(instant);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Instant, getEpochSecond) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_long epoch_second = THIS_TEMPORAL_INSTANT_INTERNAL()->epoch_second;
	RETURN_LONG(epoch_second);
}

ZEND_METHOD(Temporal_Instant, getNano) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_long nano = THIS_TEMPORAL_INSTANT_INTERNAL()->nano;
	RETURN_LONG(nano);
}

ZEND_METHOD(Temporal_Instant, withEpochSecond) {
	zend_long epoch_second;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(epoch_second)
	ZEND_PARSE_PARAMETERS_END();

	temporal_instant_t *copy = temporal_instant_clone(THIS_TEMPORAL_INSTANT_INTERNAL());
	copy->epoch_second = epoch_second;

	zend_object *object = php_temporal_instant_create_object_ex(copy);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Instant, withNano) {
	zend_long nano;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(nano)
	ZEND_PARSE_PARAMETERS_END();

	TEMPORAL_CHECK_VALUE_RANGE("nano", nano, 0, NANOS_PER_SECOND - 1)

	temporal_instant_t *copy = temporal_instant_clone(THIS_TEMPORAL_INSTANT_INTERNAL());
	copy->nano = nano;

	zend_object *object = php_temporal_instant_create_object_ex(copy);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Instant, plus) {
	zval *duration;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(duration, php_temporal_duration_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_instant_t *instant = temporal_instant_plus(THIS_TEMPORAL_INSTANT_INTERNAL(), Z_TEMPORAL_DURATION_INTERNAL_P(duration));
	zend_object *object = php_temporal_instant_create_object_ex(instant);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Instant, plusSeconds) {
	zend_long seconds;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(seconds)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(seconds, 0);
	temporal_instant_t *instant = temporal_instant_plus(THIS_TEMPORAL_INSTANT_INTERNAL(), duration);
	temporal_duration_free(duration);

	zend_object *object = php_temporal_instant_create_object_ex(instant);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Instant, plusMinutes) {
	zend_long minutes;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(minutes)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(minutes * SECONDS_PER_MINUTE, 0);
	temporal_instant_t *instant = temporal_instant_plus(THIS_TEMPORAL_INSTANT_INTERNAL(), duration);
	temporal_duration_free(duration);

	zend_object *object = php_temporal_instant_create_object_ex(instant);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Instant, plusHours) {
	zend_long hours;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(hours)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(hours * SECONDS_PER_HOUR, 0);
	temporal_instant_t *instant = temporal_instant_plus(THIS_TEMPORAL_INSTANT_INTERNAL(), duration);
	temporal_duration_free(duration);

	zend_object *object = php_temporal_instant_create_object_ex(instant);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Instant, plusDays) {
	zend_long days;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(days)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(days * SECONDS_PER_DAY, 0);
	temporal_instant_t *instant = temporal_instant_plus(THIS_TEMPORAL_INSTANT_INTERNAL(), duration);
	temporal_duration_free(duration);

	zend_object *object = php_temporal_instant_create_object_ex(instant);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Instant, minus) {
	zval *duration;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(duration, php_temporal_duration_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_instant_t *instant = temporal_instant_minus(THIS_TEMPORAL_INSTANT_INTERNAL(), Z_TEMPORAL_DURATION_INTERNAL_P(duration));
	zend_object *object = php_temporal_instant_create_object_ex(instant);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Instant, minusSeconds) {
	zend_long seconds;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(seconds)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(seconds, 0);
	temporal_instant_t *instant = temporal_instant_minus(THIS_TEMPORAL_INSTANT_INTERNAL(), duration);
	temporal_duration_free(duration);

	zend_object *object = php_temporal_instant_create_object_ex(instant);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Instant, minusMinutes) {
	zend_long minutes;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(minutes)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(minutes * SECONDS_PER_MINUTE, 0);
	temporal_instant_t *instant = temporal_instant_minus(THIS_TEMPORAL_INSTANT_INTERNAL(), duration);
	temporal_duration_free(duration);

	zend_object *object = php_temporal_instant_create_object_ex(instant);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Instant, minusHours) {
	zend_long hours;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(hours)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(hours * SECONDS_PER_HOUR, 0);
	temporal_instant_t *instant = temporal_instant_minus(THIS_TEMPORAL_INSTANT_INTERNAL(), duration);
	temporal_duration_free(duration);

	zend_object *object = php_temporal_instant_create_object_ex(instant);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Instant, minusDays) {
	zend_long days;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(days)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(days * SECONDS_PER_DAY, 0);
	temporal_instant_t *instant = temporal_instant_minus(THIS_TEMPORAL_INSTANT_INTERNAL(), duration);
	temporal_duration_free(duration);

	zend_object *object = php_temporal_instant_create_object_ex(instant);
	RETURN_OBJ(object);
}

#define TEMPORAL_INSTANT_COMPARE                                              \
	zend_object *other;                                                       \
	ZEND_PARSE_PARAMETERS_START(1, 1)                                         \
	Z_PARAM_OBJ_OF_CLASS(other, php_temporal_instant_ce)                      \
	ZEND_PARSE_PARAMETERS_END();                                              \
	temporal_instant_t *a = THIS_TEMPORAL_INSTANT_INTERNAL();                 \
	temporal_instant_t *b = php_temporal_instant_from_object(other)->instant; \
	int result = temporal_instant_compare(a, b);

ZEND_METHOD(Temporal_Instant, compareTo) {
	TEMPORAL_INSTANT_COMPARE
	RETURN_LONG(result);
}

ZEND_METHOD(Temporal_Instant, isEqualTo) {
	TEMPORAL_INSTANT_COMPARE
	RETURN_BOOL(result == 0);
}

ZEND_METHOD(Temporal_Instant, isBefore) {
	TEMPORAL_INSTANT_COMPARE
	RETURN_BOOL(result < 0);
}

ZEND_METHOD(Temporal_Instant, isBeforeOrEqualTo) {
	TEMPORAL_INSTANT_COMPARE
	RETURN_BOOL(result <= 0);
}

ZEND_METHOD(Temporal_Instant, isAfter) {
	TEMPORAL_INSTANT_COMPARE
	RETURN_BOOL(result > 0);
}

ZEND_METHOD(Temporal_Instant, isAfterOrEqualTo) {
	TEMPORAL_INSTANT_COMPARE
	RETURN_BOOL(result >= 0);
}

ZEND_METHOD(Temporal_Instant, atTimeZone) {
	zval *time_zone;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(time_zone, php_temporal_time_zone_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of_instant(
		temporal_instant_clone(THIS_TEMPORAL_INSTANT_INTERNAL()),
		temporal_time_zone_clone(Z_TEMPORAL_TIME_ZONE_INTERNAL_P(time_zone))
	);

	zend_object *object = php_temporal_zoned_date_time_create_object_ex(zoned_date_time);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Instant, toDecimal) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_instant_t *instant = THIS_TEMPORAL_INSTANT_INTERNAL();

	smart_str buf = {0};
	smart_str_append_long(&buf, instant->epoch_second);
	if (instant->nano != 0) {
		char nano[11];
		snprintf(nano, sizeof(nano), "%09llu", instant->nano);
		remove_trailing_zeroes(nano);

		smart_str_appendc(&buf, '.');
		smart_str_appends(&buf, nano);
	}

	zend_string *str = smart_str_extract(&buf);
	RETURN_STR(str);
}

ZEND_METHOD(Temporal_Instant, toISOString) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_string *str = temporal_instant_format_iso(THIS_TEMPORAL_INSTANT_INTERNAL());
	RETURN_STR(str);
}

ZEND_METHOD(Temporal_Instant, jsonSerialize) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_string *str = temporal_instant_format_iso(THIS_TEMPORAL_INSTANT_INTERNAL());
	RETURN_STR(str);
}

ZEND_METHOD(Temporal_Instant, __toString) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_string *str = temporal_instant_format_iso(THIS_TEMPORAL_INSTANT_INTERNAL());
	RETURN_STR(str);
}

ZEND_METHOD(Temporal_Instant, __serialize) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_instant_t *instant = THIS_TEMPORAL_INSTANT_INTERNAL();

	array_init(return_value);
	HashTable *ht = Z_ARRVAL_P(return_value);

	zval tmp;

	ZVAL_LONG(&tmp, instant->epoch_second);
	zend_hash_str_update(ht, "epochSecond", strlen("epochSecond"), &tmp);

	ZVAL_LONG(&tmp, instant->nano);
	zend_hash_str_update(ht, "nano", strlen("nano"), &tmp);
}

ZEND_METHOD(Temporal_Instant, __unserialize) {
	HashTable *ht;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_ARRAY_HT(ht)
	ZEND_PARSE_PARAMETERS_END();

	temporal_instant_t *instant = THIS_TEMPORAL_INSTANT_INTERNAL();

	zval *epoch_second = zend_hash_str_find(ht, "epochSecond", strlen("epochSecond"));
	if (epoch_second == NULL || Z_TYPE_P(epoch_second) != IS_LONG) {
		php_temporal_throw_exception("Failed to unserialize Temporal value from data.", 0);
		RETURN_THROWS();
	}

	zval *nano = zend_hash_str_find(ht, "nano", strlen("nano"));
	if (nano == NULL || Z_TYPE_P(nano) != IS_LONG) {
		php_temporal_throw_exception("Failed to unserialize Temporal value from data.", 0);
		RETURN_THROWS();
	}

	instant->epoch_second = Z_LVAL_P(epoch_second);
	instant->nano = Z_LVAL_P(nano);
}

zend_class_entry *php_temporal_instant_ce;

void php_temporal_register_instant_ce() {
	php_temporal_instant_ce = register_class_Temporal_Instant(php_json_serializable_ce, zend_ce_stringable);
	php_temporal_instant_ce->create_object = php_temporal_instant_create_object;

	php_temporal_register_instant_handlers();
}
