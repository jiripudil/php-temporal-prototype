#include "instant_obj.h"
#include <php.h>
#include <zend_exceptions.h>
#include "instant.h"
#include "instant_ce.h"
#include "instant_handlers.h"

zend_object *php_temporal_instant_create_object_ex(temporal_instant_t *instant) {
	php_temporal_instant_t *object = zend_object_alloc(sizeof(php_temporal_instant_t), php_temporal_instant_ce);

	zend_object_std_init(&object->std, php_temporal_instant_ce);
	object_properties_init(&object->std, php_temporal_instant_ce);

	object->std.handlers = &php_temporal_instant_handlers;
	object->instant = instant;

	return &object->std;
}

zend_object *php_temporal_instant_create_object(zend_class_entry *ce) {
	return php_temporal_instant_create_object_ex(temporal_instant_epoch());
}

zend_object *php_temporal_instant_create_object_clone(temporal_instant_t *instant) {
	return php_temporal_instant_create_object_ex(temporal_instant_clone(instant));
}
