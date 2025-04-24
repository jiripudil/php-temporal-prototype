#include "instant_handlers.h"
#include <php.h>
#include <zend_smart_str.h>
#include "instant.h"
#include "instant_obj.h"

zend_object_handlers php_temporal_instant_handlers;

static zend_object *php_temporal_instant_clone_object(zend_object *object) {
	php_temporal_instant_t *instant = php_temporal_instant_from_object(object);
	return php_temporal_instant_create_object_clone(instant->instant);
}

static void php_temporal_instant_free_object(zend_object *object) {
	php_temporal_instant_t *instant = php_temporal_instant_from_object(object);
	temporal_instant_free(instant->instant);
	zend_object_std_dtor(&instant->std);
}

static zend_result php_temporal_instant_cast_object(zend_object *object, zval *return_value, int type) {
	php_temporal_instant_t *instant = php_temporal_instant_from_object(object);

	switch (type) {
		case IS_STRING:
			ZVAL_STR(return_value, temporal_instant_format_iso(instant->instant));
			return SUCCESS;

		case _IS_BOOL:
			ZVAL_TRUE(return_value); // objects are always truthy
			return SUCCESS;

		default:
			return FAILURE;
	}
}

static HashTable *php_temporal_instant_get_debug_info(zend_object *object, int *is_temp) {
	temporal_instant_t *instant = php_temporal_instant_from_object(object)->instant;

	HashTable *debug_info;
	ALLOC_HASHTABLE(debug_info);
	zend_hash_init(debug_info, 2, NULL, ZVAL_PTR_DTOR, 0);

	zval tmp;

	ZVAL_LONG(&tmp, instant->epoch_second);
	zend_hash_str_update(debug_info, ZEND_STRL("epochSecond"), &tmp);

	ZVAL_LONG(&tmp, instant->nano);
	zend_hash_str_update(debug_info, ZEND_STRL("nano"), &tmp);

	*is_temp = 1;

	return debug_info;
}

void php_temporal_register_instant_handlers() {
	memcpy(&php_temporal_instant_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	php_temporal_instant_handlers.offset = XtOffsetOf(php_temporal_instant_t, std);
	php_temporal_instant_handlers.clone_obj = php_temporal_instant_clone_object;
	php_temporal_instant_handlers.free_obj = php_temporal_instant_free_object;
	php_temporal_instant_handlers.cast_object = php_temporal_instant_cast_object;
	php_temporal_instant_handlers.get_debug_info = php_temporal_instant_get_debug_info;
}
