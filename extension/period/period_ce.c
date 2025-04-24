#include "period_ce.h"
#include <ext/json/php_json.h>
#include <php.h>
#include <zend_interfaces.h>
#include "period.h"
#include "period_arginfo.h"
#include "period_handlers.h"
#include "period_obj.h"
#include "exception/exception_obj.h"
#include "local_date/local_date_ce.h"
#include "local_date/local_date_obj.h"

ZEND_METHOD(Temporal_Period, __construct) {
	// private
}

ZEND_METHOD(Temporal_Period, of) {
	zend_long years, months, days;

	ZEND_PARSE_PARAMETERS_START(3, 3)
	Z_PARAM_LONG(years)
	Z_PARAM_LONG(months)
	Z_PARAM_LONG(days)
	ZEND_PARSE_PARAMETERS_END();

	temporal_period_t *period = temporal_period_of(years, months, days);
	zend_object *object = php_temporal_period_create_object_ex(period);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Period, ofYears) {
	zend_long years;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(years)
	ZEND_PARSE_PARAMETERS_END();

	temporal_period_t *period = temporal_period_of(years, 0, 0);
	zend_object *object = php_temporal_period_create_object_ex(period);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Period, ofMonths) {
	zend_long months;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(months)
	ZEND_PARSE_PARAMETERS_END();

	temporal_period_t *period = temporal_period_of(0, months, 0);
	zend_object *object = php_temporal_period_create_object_ex(period);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Period, ofWeeks) {
	zend_long weeks;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(weeks)
	ZEND_PARSE_PARAMETERS_END();

	temporal_period_t *period = temporal_period_of(0, 0, weeks * 7);
	zend_object *object = php_temporal_period_create_object_ex(period);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Period, ofDays) {
	zend_long days;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(days)
	ZEND_PARSE_PARAMETERS_END();

	temporal_period_t *period = temporal_period_of(0, 0, days);
	zend_object *object = php_temporal_period_create_object_ex(period);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Period, zero) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_period_t *period = temporal_period_zero();
	zend_object *object = php_temporal_period_create_object_ex(period);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Period, between) {
	zend_object *start, *end_exclusive;

	ZEND_PARSE_PARAMETERS_START(2, 2)
	Z_PARAM_OBJ_OF_CLASS(start, php_temporal_local_date_ce)
	Z_PARAM_OBJ_OF_CLASS(end_exclusive, php_temporal_local_date_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_period_t *period = temporal_period_between(
		php_temporal_local_date_from_object(start)->local_date,
		php_temporal_local_date_from_object(end_exclusive)->local_date
	);

	zend_object *object = php_temporal_period_create_object_ex(period);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Period, fromISOString) {
	zend_string *input;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_STR(input)
	ZEND_PARSE_PARAMETERS_END();

	const char *input_s = ZSTR_VAL(input);

	temporal_period_t *period = temporal_period_parse_iso(input_s);
	if (period == NULL) {
		php_temporal_throw_exception("Failed to parse given input into a Temporal value.", 0);
		RETURN_THROWS();
	}

	zend_object *object = php_temporal_period_create_object_ex(period);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Period, getYears) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_period_t *period = THIS_TEMPORAL_PERIOD_INTERNAL();
	RETURN_LONG(period->years);
}

ZEND_METHOD(Temporal_Period, withYears) {
	zend_long years;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(years)
	ZEND_PARSE_PARAMETERS_END();

	temporal_period_t *result = temporal_period_clone(THIS_TEMPORAL_PERIOD_INTERNAL());
	result->years = years;

	zend_object *object = php_temporal_period_create_object_ex(result);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Period, plusYears) {
	zend_long years;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(years)
	ZEND_PARSE_PARAMETERS_END();

	temporal_period_t *result = temporal_period_clone(THIS_TEMPORAL_PERIOD_INTERNAL());
	result->years += years;

	zend_object *object = php_temporal_period_create_object_ex(result);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Period, minusYears) {
	zend_long years;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(years)
	ZEND_PARSE_PARAMETERS_END();

	temporal_period_t *result = temporal_period_clone(THIS_TEMPORAL_PERIOD_INTERNAL());
	result->years -= years;

	zend_object *object = php_temporal_period_create_object_ex(result);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Period, getMonths) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_period_t *period = THIS_TEMPORAL_PERIOD_INTERNAL();
	RETURN_LONG(period->months);
}

ZEND_METHOD(Temporal_Period, withMonths) {
	zend_long months;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(months)
	ZEND_PARSE_PARAMETERS_END();

	temporal_period_t *result = temporal_period_clone(THIS_TEMPORAL_PERIOD_INTERNAL());
	result->months = months;

	zend_object *object = php_temporal_period_create_object_ex(result);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Period, plusMonths) {
	zend_long months;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(months)
	ZEND_PARSE_PARAMETERS_END();

	temporal_period_t *result = temporal_period_clone(THIS_TEMPORAL_PERIOD_INTERNAL());
	result->months += months;

	zend_object *object = php_temporal_period_create_object_ex(result);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Period, minusMonths) {
	zend_long months;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(months)
	ZEND_PARSE_PARAMETERS_END();

	temporal_period_t *result = temporal_period_clone(THIS_TEMPORAL_PERIOD_INTERNAL());
	result->months -= months;

	zend_object *object = php_temporal_period_create_object_ex(result);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Period, getDays) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_period_t *period = THIS_TEMPORAL_PERIOD_INTERNAL();
	RETURN_LONG(period->days);
}

ZEND_METHOD(Temporal_Period, withDays) {
	zend_long days;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(days)
	ZEND_PARSE_PARAMETERS_END();

	temporal_period_t *result = temporal_period_clone(THIS_TEMPORAL_PERIOD_INTERNAL());
	result->days = days;

	zend_object *object = php_temporal_period_create_object_ex(result);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Period, plusDays) {
	zend_long days;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(days)
	ZEND_PARSE_PARAMETERS_END();

	temporal_period_t *result = temporal_period_clone(THIS_TEMPORAL_PERIOD_INTERNAL());
	result->days += days;

	zend_object *object = php_temporal_period_create_object_ex(result);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Period, minusDays) {
	zend_long days;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_LONG(days)
	ZEND_PARSE_PARAMETERS_END();

	temporal_period_t *result = temporal_period_clone(THIS_TEMPORAL_PERIOD_INTERNAL());
	result->days -= days;

	zend_object *object = php_temporal_period_create_object_ex(result);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Period, negated) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_period_t *negated = temporal_period_negated(THIS_TEMPORAL_PERIOD_INTERNAL());
	zend_object *object = php_temporal_period_create_object_ex(negated);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Period, isZero) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_period_t *period = THIS_TEMPORAL_PERIOD_INTERNAL();
	RETURN_BOOL(period->years == 0 && period->months == 0 && period->days == 0);
}

ZEND_METHOD(Temporal_Period, isEqualTo) {
	zend_object *other;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJ_OF_CLASS(other, php_temporal_period_ce)
	ZEND_PARSE_PARAMETERS_END();

	temporal_period_t *period = THIS_TEMPORAL_PERIOD_INTERNAL();
	temporal_period_t *other_period = php_temporal_period_from_object(other)->period;
	RETURN_BOOL(period->years == other_period->years && period->months == other_period->months && period->days == other_period->days);
}

ZEND_METHOD(Temporal_Period, toISOString) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_string *str = temporal_period_format_iso(THIS_TEMPORAL_PERIOD_INTERNAL());
	RETURN_STR(str);
}

ZEND_METHOD(Temporal_Period, jsonSerialize) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_string *str = temporal_period_format_iso(THIS_TEMPORAL_PERIOD_INTERNAL());
	RETURN_STR(str);
}

ZEND_METHOD(Temporal_Period, __toString) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_string *str = temporal_period_format_iso(THIS_TEMPORAL_PERIOD_INTERNAL());
	RETURN_STR(str);
}

ZEND_METHOD(Temporal_Period, __serialize) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_period_t *period = THIS_TEMPORAL_PERIOD_INTERNAL();

	array_init(return_value);
	HashTable *ht = Z_ARRVAL_P(return_value);

	zval tmp;

	ZVAL_LONG(&tmp, period->years);
	zend_hash_str_update(ht, "years", strlen("years"), &tmp);

	ZVAL_LONG(&tmp, period->months);
	zend_hash_str_update(ht, "months", strlen("months"), &tmp);

	ZVAL_LONG(&tmp, period->days);
	zend_hash_str_update(ht, "days", strlen("days"), &tmp);
}

ZEND_METHOD(Temporal_Period, __unserialize) {
	HashTable *ht;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_ARRAY_HT(ht)
	ZEND_PARSE_PARAMETERS_END();

	temporal_period_t *period = THIS_TEMPORAL_PERIOD_INTERNAL();

	zval *years = zend_hash_str_find(ht, "years", strlen("years"));
	if (years == NULL || Z_TYPE_P(years) != IS_LONG) {
		php_temporal_throw_exception("Failed to unserialize Temporal value from data.", 0);
		RETURN_THROWS();
	}

	zval *months = zend_hash_str_find(ht, "months", strlen("months"));
	if (months == NULL || Z_TYPE_P(months) != IS_LONG) {
		php_temporal_throw_exception("Failed to unserialize Temporal value from data.", 0);
		RETURN_THROWS();
	}

	zval *days = zend_hash_str_find(ht, "days", strlen("days"));
	if (days == NULL || Z_TYPE_P(days) != IS_LONG) {
		php_temporal_throw_exception("Failed to unserialize Temporal value from data.", 0);
		RETURN_THROWS();
	}

	period->years = Z_LVAL_P(years);
	period->months = Z_LVAL_P(months);
	period->days = Z_LVAL_P(days);
}

zend_class_entry *php_temporal_period_ce;

void php_temporal_register_period_ce() {
	php_temporal_period_ce = register_class_Temporal_Period(php_json_serializable_ce, zend_ce_stringable);
	php_temporal_period_ce->create_object = php_temporal_period_create_object;

	php_temporal_register_period_handlers();
}
