#include "local_date_time_obj.h"
#include <php.h>
#include <zend_exceptions.h>
#include "local_date_time.h"
#include "local_date_time_ce.h"
#include "local_date_time_handlers.h"

zend_object *php_temporal_local_date_time_create_object_ex(temporal_local_date_time_t *local_date_time) {
	php_temporal_local_date_time_t *object = zend_object_alloc(sizeof(php_temporal_local_date_time_t), php_temporal_local_date_time_ce);

	zend_object_std_init(&object->std, php_temporal_local_date_time_ce);
	object_properties_init(&object->std, php_temporal_local_date_time_ce);

	object->std.handlers = &php_temporal_local_date_time_handlers;
	object->local_date_time = local_date_time;

	return &object->std;
}

zend_object *php_temporal_local_date_time_create_object(zend_class_entry *ce) {
	return php_temporal_local_date_time_create_object_ex(temporal_local_date_time_of(0, 1, 1, 0, 0, 0, 0));
}

zend_object *php_temporal_local_date_time_create_object_clone(temporal_local_date_time_t *local_date_time) {
	return php_temporal_local_date_time_create_object_ex(temporal_local_date_time_clone(local_date_time));
}
