#include "time_zone_obj.h"
#include <ext/standard/php_var.h>
#include <php.h>
#include <zend_exceptions.h>
#include <zend_smart_str.h>
#include "exception/exception_obj.h"
#include "time_zone.h"
#include "time_zone/offset/time_zone_offset.h"
#include "time_zone/offset/time_zone_offset_ce.h"
#include "time_zone/region/time_zone_region_ce.h"
#include "time_zone_handlers.h"

zend_object *php_temporal_time_zone_create_object_ex(temporal_time_zone_t *time_zone) {
	zend_class_entry *ce = IS_TEMPORAL_TIME_ZONE_OFFSET(time_zone) ? php_temporal_time_zone_offset_ce : php_temporal_time_zone_region_ce;

	php_temporal_time_zone_t *object = zend_object_alloc(sizeof(php_temporal_time_zone_t), ce);

	zend_object_std_init(&object->std, ce);
	object_properties_init(&object->std, ce);

	object->std.handlers = &php_temporal_time_zone_handlers;
	object->time_zone = time_zone;

	return &object->std;
}

zend_object *php_temporal_time_zone_create_object(zend_class_entry *ce) {
	if (ce != php_temporal_time_zone_region_ce && ce != php_temporal_time_zone_offset_ce) {
		php_temporal_throw_exception("Temporal\\TimeZone cannot be subclassed.", 0);
	}

	php_temporal_time_zone_t *object = zend_object_alloc(sizeof(php_temporal_time_zone_t), ce);

	zend_object_std_init(&object->std, ce);
	object_properties_init(&object->std, ce);

	object->std.handlers = &php_temporal_time_zone_handlers;
	object->time_zone = temporal_time_zone_of_offset(temporal_time_zone_offset_utc());

	return &object->std;
}

zend_object *php_temporal_time_zone_create_object_clone(temporal_time_zone_t *time_zone) {
	return php_temporal_time_zone_create_object_ex(temporal_time_zone_clone(time_zone));
}
