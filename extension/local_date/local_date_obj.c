#include "local_date_obj.h"
#include <php.h>
#include <zend_exceptions.h>
#include "local_date.h"
#include "local_date_ce.h"
#include "local_date_handlers.h"

zend_object *php_temporal_local_date_create_object_ex(temporal_local_date_t *local_date) {
	php_temporal_local_date_t *object = zend_object_alloc(sizeof(php_temporal_local_date_t), php_temporal_local_date_ce);

	zend_object_std_init(&object->std, php_temporal_local_date_ce);
	object_properties_init(&object->std, php_temporal_local_date_ce);

	object->std.handlers = &php_temporal_local_date_handlers;
	object->local_date = local_date;

	return &object->std;
}

zend_object *php_temporal_local_date_create_object(zend_class_entry *ce) {
	return php_temporal_local_date_create_object_ex(temporal_local_date_of(0, 1, 1));
}

zend_object *php_temporal_local_date_create_object_clone(temporal_local_date_t *local_date) {
	return php_temporal_local_date_create_object_ex(temporal_local_date_clone(local_date));
}
