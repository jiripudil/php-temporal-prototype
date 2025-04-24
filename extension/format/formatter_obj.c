#include "formatter_obj.h"
#include <php.h>
#include <unicode/udat.h>
#include "formatter_ce.h"
#include "formatter_handlers.h"
#include "exception/exception_obj.h"

zend_object *php_temporal_formatter_create_object(zend_class_entry *ce) {
	return php_temporal_formatter_create_object_ex(NULL);
}

zend_object *php_temporal_formatter_create_object_ex(UDateFormat *fmt) {
	php_temporal_formatter_t *object = zend_object_alloc(sizeof(php_temporal_formatter_t), php_temporal_formatter_ce);

	zend_object_std_init(&object->std, php_temporal_formatter_ce);
	object_properties_init(&object->std, php_temporal_formatter_ce);

	object->std.handlers = &php_temporal_formatter_handlers;
	object->fmt = fmt;

	return &object->std;
}

zend_object *php_temporal_formatter_create_object_clone(php_temporal_formatter_t *formatter) {
	UErrorCode status = U_ZERO_ERROR;
	UDateFormat *copy = udat_clone(formatter->fmt, &status);
	if (U_FAILURE(status)) {
		php_temporal_throw_exception("Failed to clone DateTimeFormatter.", 0);
		return NULL;
	}

	return php_temporal_formatter_create_object_ex(copy);
}
