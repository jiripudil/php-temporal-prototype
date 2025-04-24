#include "local_time_handlers.h"
#include <php.h>
#include <zend_smart_str.h>
#include "local_time.h"
#include "local_time_obj.h"

zend_object_handlers php_temporal_local_time_handlers;

static zend_object *php_temporal_local_time_clone_object(zend_object *object) {
	php_temporal_local_time_t *local_time = php_temporal_local_time_from_object(object);
	return php_temporal_local_time_create_object_clone(local_time->local_time);
}

static void php_temporal_local_time_free_object(zend_object *object) {
	php_temporal_local_time_t *local_time = php_temporal_local_time_from_object(object);
	temporal_local_time_free(local_time->local_time);
	zend_object_std_dtor(&local_time->std);
}

static zend_result php_temporal_local_time_cast_object(zend_object *object, zval *return_value, int type) {
	php_temporal_local_time_t *local_time = php_temporal_local_time_from_object(object);

	switch (type) {
		case IS_STRING:
			ZVAL_STR(return_value, temporal_local_time_format_iso(local_time->local_time));
			return SUCCESS;

		case _IS_BOOL:
			ZVAL_TRUE(return_value); // objects are always truthy
			return SUCCESS;

		default:
			return FAILURE;
	}
}

static HashTable *php_temporal_local_time_get_debug_info(zend_object *object, int *is_temp) {
	temporal_local_time_t *local_time = php_temporal_local_time_from_object(object)->local_time;

	HashTable *debug_info;
	ALLOC_HASHTABLE(debug_info);
	zend_hash_init(debug_info, 2, NULL, ZVAL_PTR_DTOR, 0);

	zval tmp;

	ZVAL_LONG(&tmp, local_time->hour);
	zend_hash_str_update(debug_info, ZEND_STRL("hour"), &tmp);

	ZVAL_LONG(&tmp, local_time->minute);
	zend_hash_str_update(debug_info, ZEND_STRL("minute"), &tmp);

	ZVAL_LONG(&tmp, local_time->second);
	zend_hash_str_update(debug_info, ZEND_STRL("second"), &tmp);

	ZVAL_LONG(&tmp, local_time->nano);
	zend_hash_str_update(debug_info, ZEND_STRL("nano"), &tmp);

	*is_temp = 1;

	return debug_info;
}

void php_temporal_register_local_time_handlers() {
	memcpy(&php_temporal_local_time_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	php_temporal_local_time_handlers.offset = XtOffsetOf(php_temporal_local_time_t, std);
	php_temporal_local_time_handlers.clone_obj = php_temporal_local_time_clone_object;
	php_temporal_local_time_handlers.free_obj = php_temporal_local_time_free_object;
	php_temporal_local_time_handlers.cast_object = php_temporal_local_time_cast_object;
	php_temporal_local_time_handlers.get_debug_info = php_temporal_local_time_get_debug_info;
}
