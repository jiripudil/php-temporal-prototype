#include "duration_ce.h"
#include <ext/json/php_json.h>
#include <php.h>
#include <zend_interfaces.h>
#include "duration.h"
#include "duration_arginfo.h"
#include "duration_handlers.h"
#include "duration_obj.h"
#include "exception/exception_obj.h"
#include "instant/instant_ce.h"
#include "instant/instant_obj.h"

ZEND_METHOD(Temporal_Duration, __construct) {
	// private
}

ZEND_METHOD(Temporal_Duration, zero) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_duration_t *duration = temporal_duration_zero();
	zend_object *object = php_temporal_duration_create_object_ex(duration);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Duration, fromISOString) {
	zend_string *input;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_STR(input)
	ZEND_PARSE_PARAMETERS_END();

	const char *input_s = ZSTR_VAL(input);

	temporal_duration_t *duration = temporal_duration_parse_iso(input_s);
	if (duration == NULL) {
		php_temporal_throw_exception("Failed to parse given input into a Temporal value.", 0);
		RETURN_THROWS();
	}

	zend_object *object = php_temporal_duration_create_object_ex(duration);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Duration, ofSeconds) {
	zend_long seconds, nano_adjustment = 0;

	ZEND_PARSE_PARAMETERS_START(1, 2)
	Z_PARAM_LONG(seconds)
	Z_PARAM_OPTIONAL
	Z_PARAM_LONG(nano_adjustment)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(seconds, nano_adjustment);
	zend_object *object = php_temporal_duration_create_object_ex(duration);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Duration, ofMinutes) {
	zend_long minutes;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(minutes)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(minutes * SECONDS_PER_MINUTE, 0);
	zend_object *object = php_temporal_duration_create_object_ex(duration);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Duration, ofHours) {
	zend_long hours;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(hours)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(hours * SECONDS_PER_HOUR, 0);
	zend_object *object = php_temporal_duration_create_object_ex(duration);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Duration, ofDays) {
	zend_long days;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(days)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = temporal_duration_of(days * SECONDS_PER_DAY, 0);
	zend_object *object = php_temporal_duration_create_object_ex(duration);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Duration, between) {
	zval *start, *end_exclusive;

	ZEND_PARSE_PARAMETERS_START(2, 2)
	Z_PARAM_OBJECT_OF_CLASS(start, php_temporal_instant_ce)
	Z_PARAM_OBJECT_OF_CLASS(end_exclusive, php_temporal_instant_ce)
	ZEND_PARSE_PARAMETERS_END();

	zend_long seconds = Z_TEMPORAL_INSTANT_INTERNAL_P(end_exclusive)->epoch_second - Z_TEMPORAL_INSTANT_INTERNAL_P(start)->epoch_second;
	zend_long nano_adjustment = Z_TEMPORAL_INSTANT_INTERNAL_P(end_exclusive)->nano - Z_TEMPORAL_INSTANT_INTERNAL_P(start)->nano;

	temporal_duration_t *duration = temporal_duration_of(seconds, nano_adjustment);
	zend_object *object = php_temporal_duration_create_object_ex(duration);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Duration, getSeconds) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long seconds = THIS_TEMPORAL_DURATION_INTERNAL()->seconds;
	RETURN_LONG(seconds);
}

ZEND_METHOD(Temporal_Duration, getNanos) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long nanos = THIS_TEMPORAL_DURATION_INTERNAL()->nanos;
	RETURN_LONG(nanos);
}

ZEND_METHOD(Temporal_Duration, toDays) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long seconds = THIS_TEMPORAL_DURATION_INTERNAL()->seconds;
	zend_long days = seconds / SECONDS_PER_DAY;
	RETURN_LONG(days);
}

ZEND_METHOD(Temporal_Duration, toDaysPart) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long seconds = THIS_TEMPORAL_DURATION_INTERNAL()->seconds;
	zend_long days = seconds / SECONDS_PER_DAY;
	RETURN_LONG(days);
}

ZEND_METHOD(Temporal_Duration, toHours) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long seconds = THIS_TEMPORAL_DURATION_INTERNAL()->seconds;
	zend_long hours = seconds / SECONDS_PER_HOUR;
	RETURN_LONG(hours);
}

ZEND_METHOD(Temporal_Duration, toHoursPart) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long seconds = THIS_TEMPORAL_DURATION_INTERNAL()->seconds;
	zend_long hours_part = (seconds / SECONDS_PER_HOUR) % HOURS_PER_DAY;
	RETURN_LONG(hours_part);
}

ZEND_METHOD(Temporal_Duration, toMinutes) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long seconds = THIS_TEMPORAL_DURATION_INTERNAL()->seconds;
	zend_long minutes = seconds / SECONDS_PER_MINUTE;
	RETURN_LONG(minutes);
}

ZEND_METHOD(Temporal_Duration, toMinutesPart) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long seconds = THIS_TEMPORAL_DURATION_INTERNAL()->seconds;
	zend_long minutes_part = (seconds / SECONDS_PER_MINUTE) % MINUTES_PER_HOUR;
	RETURN_LONG(minutes_part);
}

ZEND_METHOD(Temporal_Duration, toSeconds) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long seconds = THIS_TEMPORAL_DURATION_INTERNAL()->seconds;
	RETURN_LONG(seconds);
}

ZEND_METHOD(Temporal_Duration, toSecondsPart) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long seconds = THIS_TEMPORAL_DURATION_INTERNAL()->seconds;
	zend_long seconds_part = seconds % SECONDS_PER_MINUTE;
	RETURN_LONG(seconds_part);
}

ZEND_METHOD(Temporal_Duration, isZero) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long seconds = THIS_TEMPORAL_DURATION_INTERNAL()->seconds;
	zend_long nanos = THIS_TEMPORAL_DURATION_INTERNAL()->nanos;
	RETURN_BOOL(seconds == 0 && nanos == 0);
}

ZEND_METHOD(Temporal_Duration, isPositive) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long seconds = THIS_TEMPORAL_DURATION_INTERNAL()->seconds;
	zend_long nanos = THIS_TEMPORAL_DURATION_INTERNAL()->nanos;
	RETURN_BOOL(seconds > 0 || (seconds == 0 && nanos > 0));
}

ZEND_METHOD(Temporal_Duration, isPositiveOrZero) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long seconds = THIS_TEMPORAL_DURATION_INTERNAL()->seconds;
	RETURN_BOOL(seconds >= 0);
}

ZEND_METHOD(Temporal_Duration, isNegative) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long seconds = THIS_TEMPORAL_DURATION_INTERNAL()->seconds;
	RETURN_BOOL(seconds < 0);
}

ZEND_METHOD(Temporal_Duration, isNegativeOrZero) {
	ZEND_PARSE_PARAMETERS_NONE();
	zend_long seconds = THIS_TEMPORAL_DURATION_INTERNAL()->seconds;
	zend_long nanos = THIS_TEMPORAL_DURATION_INTERNAL()->nanos;
	RETURN_BOOL(seconds < 0 || (seconds == 0 && nanos == 0));
}

ZEND_METHOD(Temporal_Duration, plus) {
	zval *other;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(other, php_temporal_duration_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *result = temporal_duration_plus(THIS_TEMPORAL_DURATION_INTERNAL(), Z_TEMPORAL_DURATION_INTERNAL_P(other));
	zend_object *object = php_temporal_duration_create_object_ex(result);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Duration, plusSeconds) {
	zend_long seconds;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(seconds)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *other = temporal_duration_of(seconds, 0);
	temporal_duration_t *result = temporal_duration_plus(THIS_TEMPORAL_DURATION_INTERNAL(), other);
	zend_object *object = php_temporal_duration_create_object_ex(result);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Duration, plusMinutes) {
	zend_long minutes;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(minutes)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *other = temporal_duration_of(minutes * SECONDS_PER_MINUTE, 0);
	temporal_duration_t *result = temporal_duration_plus(THIS_TEMPORAL_DURATION_INTERNAL(), other);
	zend_object *object = php_temporal_duration_create_object_ex(result);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Duration, plusHours) {
	zend_long hours;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(hours)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *other = temporal_duration_of(hours * SECONDS_PER_HOUR, 0);
	temporal_duration_t *result = temporal_duration_plus(THIS_TEMPORAL_DURATION_INTERNAL(), other);
	zend_object *object = php_temporal_duration_create_object_ex(result);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Duration, plusDays) {
	zend_long days;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(days)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *other = temporal_duration_of(days * SECONDS_PER_DAY, 0);
	temporal_duration_t *result = temporal_duration_plus(THIS_TEMPORAL_DURATION_INTERNAL(), other);
	zend_object *object = php_temporal_duration_create_object_ex(result);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Duration, minus) {
	zval *other;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(other, php_temporal_duration_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *result = temporal_duration_minus(THIS_TEMPORAL_DURATION_INTERNAL(), Z_TEMPORAL_DURATION_INTERNAL_P(other));
	zend_object *object = php_temporal_duration_create_object_ex(result);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Duration, minusSeconds) {
	zend_long seconds;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(seconds)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *other = temporal_duration_of(seconds, 0);
	temporal_duration_t *result = temporal_duration_minus(THIS_TEMPORAL_DURATION_INTERNAL(), other);
	zend_object *object = php_temporal_duration_create_object_ex(result);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Duration, minusMinutes) {
	zend_long minutes;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(minutes)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *other = temporal_duration_of(minutes * SECONDS_PER_MINUTE, 0);
	temporal_duration_t *result = temporal_duration_minus(THIS_TEMPORAL_DURATION_INTERNAL(), other);
	zend_object *object = php_temporal_duration_create_object_ex(result);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Duration, minusHours) {
	zend_long hours;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(hours)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *other = temporal_duration_of(hours * SECONDS_PER_HOUR, 0);
	temporal_duration_t *result = temporal_duration_minus(THIS_TEMPORAL_DURATION_INTERNAL(), other);
	zend_object *object = php_temporal_duration_create_object_ex(result);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Duration, minusDays) {
	zend_long days;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(days)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *other = temporal_duration_of(days * SECONDS_PER_DAY, 0);
	temporal_duration_t *result = temporal_duration_minus(THIS_TEMPORAL_DURATION_INTERNAL(), other);
	zend_object *object = php_temporal_duration_create_object_ex(result);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Duration, negated) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_duration_t *negated = temporal_duration_negated(THIS_TEMPORAL_DURATION_INTERNAL());
	zend_object *object = php_temporal_duration_create_object_ex(negated);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Duration, abs) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_duration_t *result = temporal_duration_clone(THIS_TEMPORAL_DURATION_INTERNAL());

	if (result->seconds >= 0) {
		zend_object *object = php_temporal_duration_create_object_ex(result);
		RETURN_OBJ(object);
	}

	result->seconds *= -1;

	if (result->nanos != 0) {
		result->nanos = NANOS_PER_SECOND - result->nanos;
		result->seconds--;
	}

	zend_object *object = php_temporal_duration_create_object_ex(result);
	RETURN_OBJ(object);
}

#define TEMPORAL_DURATION_COMPARE                                                \
	zend_object *other;                                                          \
	ZEND_PARSE_PARAMETERS_START(1, 1)                                            \
	Z_PARAM_OBJ_OF_CLASS(other, php_temporal_duration_ce)                        \
	ZEND_PARSE_PARAMETERS_END();                                                 \
	temporal_duration_t *a = THIS_TEMPORAL_DURATION_INTERNAL();                  \
	temporal_duration_t *b = php_temporal_duration_from_object(other)->duration; \
	int result = temporal_duration_compare(a, b);

ZEND_METHOD(Temporal_Duration, compareTo) {
	TEMPORAL_DURATION_COMPARE
	RETURN_LONG(result);
}

ZEND_METHOD(Temporal_Duration, isEqualTo) {
	TEMPORAL_DURATION_COMPARE
	RETURN_BOOL(result == 0);
}

ZEND_METHOD(Temporal_Duration, isGreaterThan) {
	TEMPORAL_DURATION_COMPARE
	RETURN_BOOL(result > 0);
}

ZEND_METHOD(Temporal_Duration, isGreaterThanOrEqualTo) {
	TEMPORAL_DURATION_COMPARE
	RETURN_BOOL(result >= 0);
}

ZEND_METHOD(Temporal_Duration, isLesserThan) {
	TEMPORAL_DURATION_COMPARE
	RETURN_BOOL(result < 0);
}

ZEND_METHOD(Temporal_Duration, isLesserThanOrEqualTo) {
	TEMPORAL_DURATION_COMPARE
	RETURN_BOOL(result <= 0);
}

ZEND_METHOD(Temporal_Duration, toISOString) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_string *result = temporal_duration_format_iso(THIS_TEMPORAL_DURATION_INTERNAL());
	RETURN_STR(result);
}

ZEND_METHOD(Temporal_Duration, jsonSerialize) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_string *result = temporal_duration_format_iso(THIS_TEMPORAL_DURATION_INTERNAL());
	RETURN_STR(result);
}

ZEND_METHOD(Temporal_Duration, __toString) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_string *result = temporal_duration_format_iso(THIS_TEMPORAL_DURATION_INTERNAL());
	RETURN_STR(result);
}

ZEND_METHOD(Temporal_Duration, __serialize) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_duration_t *duration = THIS_TEMPORAL_DURATION_INTERNAL();

	array_init(return_value);
	HashTable *ht = Z_ARRVAL_P(return_value);

	zval tmp;

	ZVAL_LONG(&tmp, duration->seconds);
	zend_hash_str_update(ht, "seconds", strlen("seconds"), &tmp);

	ZVAL_LONG(&tmp, duration->nanos);
	zend_hash_str_update(ht, "nanos", strlen("nanos"), &tmp);
}

ZEND_METHOD(Temporal_Duration, __unserialize) {
	HashTable *ht;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_ARRAY_HT(ht)
	ZEND_PARSE_PARAMETERS_END();

	temporal_duration_t *duration = THIS_TEMPORAL_DURATION_INTERNAL();

	zval *seconds = zend_hash_str_find(ht, "seconds", strlen("seconds"));
	if (seconds == NULL || Z_TYPE_P(seconds) != IS_LONG) {
		php_temporal_throw_exception("Failed to unserialize Temporal value from data.", 0);
		RETURN_THROWS();
	}

	zval *nanos = zend_hash_str_find(ht, "nanos", strlen("nanos"));
	if (nanos == NULL || Z_TYPE_P(nanos) != IS_LONG) {
		php_temporal_throw_exception("Failed to unserialize Temporal value from data.", 0);
		RETURN_THROWS();
	}

	duration->seconds = Z_LVAL_P(seconds);
	duration->nanos = Z_LVAL_P(nanos);
}

zend_class_entry *php_temporal_duration_ce;

void php_temporal_register_duration_ce() {
	php_temporal_duration_ce = register_class_Temporal_Duration(php_json_serializable_ce, zend_ce_stringable);
	php_temporal_duration_ce->create_object = php_temporal_duration_create_object;

	php_temporal_register_duration_handlers();
}
