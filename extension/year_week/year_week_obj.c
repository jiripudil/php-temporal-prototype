#include "year_week_obj.h"
#include <php.h>
#include <zend_exceptions.h>
#include "year_week.h"
#include "year_week_ce.h"
#include "year_week_handlers.h"

zend_object *php_temporal_year_week_create_object_ex(temporal_year_week_t *year_week) {
	php_temporal_year_week_t *object = zend_object_alloc(sizeof(php_temporal_year_week_t), php_temporal_year_week_ce);

	zend_object_std_init(&object->std, php_temporal_year_week_ce);
	object_properties_init(&object->std, php_temporal_year_week_ce);

	object->std.handlers = &php_temporal_year_week_handlers;
	object->year_week = year_week;

	return &object->std;
}

zend_object *php_temporal_year_week_create_object(zend_class_entry *ce) {
	return php_temporal_year_week_create_object_ex(temporal_year_week_of(0, 1));
}

zend_object *php_temporal_year_week_create_object_clone(temporal_year_week_t *year_week) {
	return php_temporal_year_week_create_object_ex(temporal_year_week_clone(year_week));
}
