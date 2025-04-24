#include "duration_handlers.h"
#include <php.h>
#include <zend_smart_str.h>
#include "duration.h"
#include "duration_obj.h"

zend_object_handlers php_temporal_duration_handlers;

static zend_object *php_temporal_duration_clone_object(zend_object *object) {
	php_temporal_duration_t *duration = php_temporal_duration_from_object(object);
	return php_temporal_duration_create_object_clone(duration->duration);
}

static void php_temporal_duration_free_object(zend_object *object) {
	php_temporal_duration_t *duration = php_temporal_duration_from_object(object);
	temporal_duration_free(duration->duration);
	zend_object_std_dtor(&duration->std);
}

static zend_result php_temporal_duration_cast_object(zend_object *object, zval *return_value, int type) {
	php_temporal_duration_t *duration = php_temporal_duration_from_object(object);

	switch (type) {
		case IS_STRING:
			ZVAL_STR(return_value, temporal_duration_format_iso(duration->duration));
			return SUCCESS;

		case _IS_BOOL:
			ZVAL_TRUE(return_value); // objects are always truthy
			return SUCCESS;

		default:
			return FAILURE;
	}
}

static HashTable *php_temporal_duration_get_debug_info(zend_object *object, int *is_temp) {
	temporal_duration_t *duration = php_temporal_duration_from_object(object)->duration;

	HashTable *debug_info;
	ALLOC_HASHTABLE(debug_info);
	zend_hash_init(debug_info, 2, NULL, ZVAL_PTR_DTOR, 0);

	zval tmp;

	ZVAL_LONG(&tmp, duration->seconds);
	zend_hash_str_update(debug_info, ZEND_STRL("seconds"), &tmp);

	ZVAL_LONG(&tmp, duration->nanos);
	zend_hash_str_update(debug_info, ZEND_STRL("nanos"), &tmp);

	*is_temp = 1;

	return debug_info;
}

void php_temporal_register_duration_handlers() {
	memcpy(&php_temporal_duration_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	php_temporal_duration_handlers.offset = XtOffsetOf(php_temporal_duration_t, std);
	php_temporal_duration_handlers.clone_obj = php_temporal_duration_clone_object;
	php_temporal_duration_handlers.free_obj = php_temporal_duration_free_object;
	php_temporal_duration_handlers.cast_object = php_temporal_duration_cast_object;
	php_temporal_duration_handlers.get_debug_info = php_temporal_duration_get_debug_info;
}
