#include "year_month_obj.h"
#include <php.h>
#include <zend_exceptions.h>
#include "year_month.h"
#include "year_month_ce.h"
#include "year_month_handlers.h"

zend_object *php_temporal_year_month_create_object_ex(temporal_year_month_t *year_month) {
	php_temporal_year_month_t *object = zend_object_alloc(sizeof(php_temporal_year_month_t), php_temporal_year_month_ce);

	zend_object_std_init(&object->std, php_temporal_year_month_ce);
	object_properties_init(&object->std, php_temporal_year_month_ce);

	object->std.handlers = &php_temporal_year_month_handlers;
	object->year_month = year_month;

	return &object->std;
}

zend_object *php_temporal_year_month_create_object(zend_class_entry *ce) {
	return php_temporal_year_month_create_object_ex(temporal_year_month_of(0, 1));
}

zend_object *php_temporal_year_month_create_object_clone(temporal_year_month_t *year_month) {
	return php_temporal_year_month_create_object_ex(temporal_year_month_clone(year_month));
}
