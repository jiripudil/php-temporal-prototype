#include "formatter_handlers.h"
#include <php.h>
#include <unicode/udat.h>
#include "formatter.h"
#include "formatter_obj.h"

zend_object_handlers php_temporal_formatter_handlers;

static zend_object *php_temporal_formatter_clone_object(zend_object *object) {
	php_temporal_formatter_t *obj = php_temporal_formatter_from_object(object);
	return php_temporal_formatter_create_object_clone(obj);
}

static void php_temporal_formatter_free_object(zend_object *object) {
	php_temporal_formatter_t *obj = php_temporal_formatter_from_object(object);
	temporal_formatter_free(obj->fmt);
	zend_object_std_dtor(&obj->std);
}

void php_temporal_register_formatter_handlers() {
	memcpy(&php_temporal_formatter_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	php_temporal_formatter_handlers.offset = XtOffsetOf(php_temporal_formatter_t, std);
	php_temporal_formatter_handlers.clone_obj = php_temporal_formatter_clone_object;
	php_temporal_formatter_handlers.free_obj = php_temporal_formatter_free_object;
}
