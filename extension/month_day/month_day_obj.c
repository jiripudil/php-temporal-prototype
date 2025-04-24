#include "month_day_obj.h"
#include <php.h>
#include <zend_exceptions.h>
#include "month_day.h"
#include "month_day_ce.h"
#include "month_day_handlers.h"

zend_object *php_temporal_month_day_create_object_ex(temporal_month_day_t *month_day) {
	php_temporal_month_day_t *object = zend_object_alloc(sizeof(php_temporal_month_day_t), php_temporal_month_day_ce);

	zend_object_std_init(&object->std, php_temporal_month_day_ce);
	object_properties_init(&object->std, php_temporal_month_day_ce);

	object->std.handlers = &php_temporal_month_day_handlers;
	object->month_day = month_day;

	return &object->std;
}

zend_object *php_temporal_month_day_create_object(zend_class_entry *ce) {
	return php_temporal_month_day_create_object_ex(temporal_month_day_of(1, 1));
}

zend_object *php_temporal_month_day_create_object_clone(temporal_month_day_t *month_day) {
	return php_temporal_month_day_create_object_ex(temporal_month_day_clone(month_day));
}
