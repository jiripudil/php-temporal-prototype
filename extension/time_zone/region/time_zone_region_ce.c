#include "time_zone_region_ce.h"
#include <ext/date/php_date.h>
#include <php.h>
#include <zend_exceptions.h>
#include "exception/exception_obj.h"
#include "instant/instant_ce.h"
#include "instant/instant_obj.h"
#include "time_zone/time_zone.h"
#include "time_zone/time_zone_ce.h"
#include "time_zone/time_zone_obj.h"
#include "time_zone_region.h"
#include "time_zone_region_arginfo.h"

ZEND_METHOD(Temporal_TimeZoneRegion, __construct) {
	// private
}

ZEND_METHOD(Temporal_TimeZoneRegion, of) {
	zend_string *input;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_STR(input)
	ZEND_PARSE_PARAMETERS_END();

	const char *input_s = ZSTR_VAL(input);

	temporal_time_zone_region_t *region = temporal_time_zone_region_of(input_s);
	temporal_time_zone_t *time_zone = temporal_time_zone_of_region(region);
	if (time_zone == NULL) {
		temporal_time_zone_region_free(region);
		php_temporal_throw_exception("Unrecognized time zone ID.", 0);
		RETURN_THROWS();
	}

	zend_object *object = php_temporal_time_zone_create_object_ex(time_zone);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_TimeZoneRegion, parse) {
	zend_string *input;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_STR(input)
	ZEND_PARSE_PARAMETERS_END();

	const char *input_s = ZSTR_VAL(input);

	temporal_time_zone_region_t *region = temporal_time_zone_region_of(input_s);
	temporal_time_zone_t *time_zone = temporal_time_zone_of_region(region);
	if (time_zone == NULL) {
		temporal_time_zone_region_free(region);
		php_temporal_throw_exception("Failed to parse given input into a Temporal value.", 0);
		RETURN_THROWS();
	}

	zend_object *object = php_temporal_time_zone_create_object_ex(time_zone);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_TimeZoneRegion, getId) {
	ZEND_PARSE_PARAMETERS_NONE();

	zend_string *id = temporal_time_zone_get_id(THIS_TEMPORAL_TIME_ZONE_INTERNAL());
	RETURN_STR(id);
}

ZEND_METHOD(Temporal_TimeZoneRegion, getOffset) {
	zval *instant;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(instant, php_temporal_instant_ce)
	ZEND_PARSE_PARAMETERS_END();

	zend_long offset = temporal_time_zone_get_offset(THIS_TEMPORAL_TIME_ZONE_INTERNAL(), Z_TEMPORAL_INSTANT_INTERNAL_P(instant));
	RETURN_LONG(offset);
}

ZEND_METHOD(Temporal_TimeZoneRegion, toDateTimeZone) {
	ZEND_PARSE_PARAMETERS_NONE();

	zval z_id;
	ZVAL_STR_COPY(&z_id, THIS_TEMPORAL_TIME_ZONE_INTERNAL()->region->id);

	object_init_with_constructor(return_value, php_date_get_timezone_ce(), 1, &z_id, NULL);
}

ZEND_METHOD(Temporal_TimeZoneRegion, __serialize) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_time_zone_t *time_zone = THIS_TEMPORAL_TIME_ZONE_INTERNAL();

	array_init(return_value);
	HashTable *ht = Z_ARRVAL_P(return_value);

	zval tmp;

	ZVAL_STR_COPY(&tmp, time_zone->region->id);
	zend_hash_str_update(ht, "id", strlen("id"), &tmp);
}

ZEND_METHOD(Temporal_TimeZoneRegion, __unserialize) {
	HashTable *ht;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_ARRAY_HT(ht)
	ZEND_PARSE_PARAMETERS_END();

	zval *id = zend_hash_str_find(ht, "id", strlen("id"));
	if (id == NULL || Z_TYPE_P(id) != IS_STRING) {
		php_temporal_throw_exception("Failed!!! to unserialize Temporal value from data.", 0);
		RETURN_THROWS();
	}

	temporal_time_zone_free(THIS_TEMPORAL_TIME_ZONE_INTERNAL());

	temporal_time_zone_region_t *time_zone_region = temporal_time_zone_region_of(Z_STRVAL_P(id));
	THIS_TEMPORAL_TIME_ZONE_INTERNAL() = temporal_time_zone_of_region(time_zone_region);
}

zend_class_entry *php_temporal_time_zone_region_ce;

void php_temporal_register_time_zone_region_ce() {
	php_temporal_time_zone_region_ce = register_class_Temporal_TimeZoneRegion(php_temporal_time_zone_ce);
}
