#include "time_zone_ce.h"
#include <ext/date/php_date.h>
#include <ext/json/php_json.h>
#include <php.h>
#include <zend_interfaces.h>
#include "exception/exception_obj.h"
#include "time_zone/offset/time_zone_offset.h"
#include "time_zone.h"
#include "time_zone_arginfo.h"
#include "time_zone_handlers.h"
#include "time_zone_obj.h"

ZEND_METHOD(Temporal_TimeZone, fromISOString) {
	zend_string *input;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_STR(input)
	ZEND_PARSE_PARAMETERS_END();

	const char *input_s = ZSTR_VAL(input);

	temporal_time_zone_t *time_zone = temporal_time_zone_parse_iso(input_s);
	if (time_zone == NULL) {
		php_temporal_throw_exception("Failed to parse given input into a Temporal value.", 0);
		RETURN_THROWS();
	}

	zend_object *object = php_temporal_time_zone_create_object_ex(time_zone);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_TimeZone, utc) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_time_zone_offset_t *utc = temporal_time_zone_offset_utc();
	temporal_time_zone_t *time_zone = temporal_time_zone_of_offset(utc);
	zend_object *object = php_temporal_time_zone_create_object_ex(time_zone);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_TimeZone, isEqualTo) {
	zval *other;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(other, php_temporal_time_zone_ce)
	ZEND_PARSE_PARAMETERS_END();

	zend_string *this_id = temporal_time_zone_get_id(THIS_TEMPORAL_TIME_ZONE_INTERNAL());
	zend_string *other_id = temporal_time_zone_get_id(Z_TEMPORAL_TIME_ZONE_INTERNAL_P(other));

	bool result = zend_string_equal_content(this_id, other_id);

	zend_string_release(this_id);
	zend_string_release(other_id);

	RETURN_BOOL(result);
}

ZEND_METHOD(Temporal_TimeZone, fromDateTimeZone) {
	zval *dtz;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(dtz, php_date_get_timezone_ce())
	ZEND_PARSE_PARAMETERS_END();

	php_timezone_obj *tz_obj = Z_PHPTIMEZONE_P(dtz);

	if (!tz_obj->initialized) {
		php_temporal_throw_exception("DateTimeZone object is uninitialized.", 0);
		RETURN_THROWS();
	}

	temporal_time_zone_t *time_zone;

	if (tz_obj->type == TIMELIB_ZONETYPE_OFFSET) {
		temporal_time_zone_offset_t *offset = temporal_time_zone_offset_of_total_seconds(tz_obj->tzi.utc_offset);
		time_zone = temporal_time_zone_of_offset(offset);

	} else if (tz_obj->type == TIMELIB_ZONETYPE_ID) {
		temporal_time_zone_region_t *region = temporal_time_zone_region_of(tz_obj->tzi.tz->name);
		time_zone = temporal_time_zone_of_region(region);

	// tz_obj->type == TIMELIB_ZONETYPE_ABBR
	} else if (strlen(tz_obj->tzi.z.abbr) == 1 && (tz_obj->tzi.z.abbr[0] == 'Z' || tz_obj->tzi.z.abbr[0] == 'z')) {
		temporal_time_zone_offset_t *offset = temporal_time_zone_offset_utc();
		time_zone = temporal_time_zone_of_offset(offset);

	} else {
		temporal_time_zone_region_t *region = temporal_time_zone_region_of(tz_obj->tzi.z.abbr);
		time_zone = temporal_time_zone_of_region(region);
	}

	if (time_zone == NULL) {
		php_temporal_throw_exception("Unrecognized DateTimeZone.", 0);
		RETURN_THROWS();
	}

	zend_object *object = php_temporal_time_zone_create_object_ex(time_zone);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_TimeZone, jsonSerialize) {
	zend_string *id = temporal_time_zone_get_id(THIS_TEMPORAL_TIME_ZONE_INTERNAL());
	RETURN_STR(id);
}

ZEND_METHOD(Temporal_TimeZone, __toString) {
	zend_string *id = temporal_time_zone_get_id(THIS_TEMPORAL_TIME_ZONE_INTERNAL());
	RETURN_STR(id);
}

zend_class_entry *php_temporal_time_zone_ce;

void php_temporal_register_time_zone_ce() {
	php_temporal_time_zone_ce = register_class_Temporal_TimeZone(php_json_serializable_ce, zend_ce_stringable);
	php_temporal_time_zone_ce->create_object = php_temporal_time_zone_create_object;

	php_temporal_register_time_zone_handlers();
}
