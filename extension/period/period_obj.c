#include "period_obj.h"
#include <php.h>
#include <zend_exceptions.h>
#include "period.h"
#include "period_ce.h"
#include "period_handlers.h"

zend_object *php_temporal_period_create_object_ex(temporal_period_t *period) {
	php_temporal_period_t *object = zend_object_alloc(sizeof(php_temporal_period_t), php_temporal_period_ce);

	zend_object_std_init(&object->std, php_temporal_period_ce);
	object_properties_init(&object->std, php_temporal_period_ce);

	object->std.handlers = &php_temporal_period_handlers;
	object->period = period;

	return &object->std;
}

zend_object *php_temporal_period_create_object(zend_class_entry *ce) {
	return php_temporal_period_create_object_ex(temporal_period_zero());
}

zend_object *php_temporal_period_create_object_clone(temporal_period_t *period) {
	return php_temporal_period_create_object_ex(temporal_period_clone(period));
}
