#include "duration_obj.h"
#include <php.h>
#include <zend_exceptions.h>
#include "duration.h"
#include "duration_ce.h"
#include "duration_handlers.h"

zend_object *php_temporal_duration_create_object_ex(temporal_duration_t *duration) {
	php_temporal_duration_t *object = zend_object_alloc(sizeof(php_temporal_duration_t), php_temporal_duration_ce);

	zend_object_std_init(&object->std, php_temporal_duration_ce);
	object_properties_init(&object->std, php_temporal_duration_ce);

	object->std.handlers = &php_temporal_duration_handlers;
	object->duration = duration;

	return &object->std;
}

zend_object *php_temporal_duration_create_object(zend_class_entry *ce) {
	return php_temporal_duration_create_object_ex(temporal_duration_zero());
}

zend_object *php_temporal_duration_create_object_clone(temporal_duration_t *duration) {
	return php_temporal_duration_create_object_ex(temporal_duration_clone(duration));
}
