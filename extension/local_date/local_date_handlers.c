#include "local_date_handlers.h"
#include <php.h>
#include <zend_smart_str.h>
#include "local_date.h"
#include "local_date_obj.h"

zend_object_handlers php_temporal_local_date_handlers;

static zend_object *php_temporal_local_date_clone_object(zend_object *object) {
	php_temporal_local_date_t *local_date = php_temporal_local_date_from_object(object);
	return php_temporal_local_date_create_object_clone(local_date->local_date);
}

static void php_temporal_local_date_free_object(zend_object *object) {
	php_temporal_local_date_t *local_date = php_temporal_local_date_from_object(object);
	temporal_local_date_free(local_date->local_date);
	zend_object_std_dtor(&local_date->std);
}

static zend_result php_temporal_local_date_cast_object(zend_object *object, zval *return_value, int type) {
	php_temporal_local_date_t *local_date = php_temporal_local_date_from_object(object);

	switch (type) {
		case IS_STRING:
			ZVAL_STR(return_value, temporal_local_date_format_iso(local_date->local_date));
			return SUCCESS;

		case _IS_BOOL:
			ZVAL_TRUE(return_value); // objects are always truthy
			return SUCCESS;

		default:
			return FAILURE;
	}
}

static HashTable *php_temporal_local_date_get_debug_info(zend_object *object, int *is_temp) {
	temporal_local_date_t *local_date = php_temporal_local_date_from_object(object)->local_date;

	HashTable *debug_info;
	ALLOC_HASHTABLE(debug_info);
	zend_hash_init(debug_info, 2, NULL, ZVAL_PTR_DTOR, 0);

	zval tmp;

	ZVAL_LONG(&tmp, local_date->year);
	zend_hash_str_update(debug_info, ZEND_STRL("year"), &tmp);

	ZVAL_LONG(&tmp, local_date->month);
	zend_hash_str_update(debug_info, ZEND_STRL("month"), &tmp);

	ZVAL_LONG(&tmp, local_date->day);
	zend_hash_str_update(debug_info, ZEND_STRL("day"), &tmp);

	*is_temp = 1;

	return debug_info;
}

void php_temporal_register_local_date_handlers() {
	memcpy(&php_temporal_local_date_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	php_temporal_local_date_handlers.offset = XtOffsetOf(php_temporal_local_date_t, std);
	php_temporal_local_date_handlers.clone_obj = php_temporal_local_date_clone_object;
	php_temporal_local_date_handlers.free_obj = php_temporal_local_date_free_object;
	php_temporal_local_date_handlers.cast_object = php_temporal_local_date_cast_object;
	php_temporal_local_date_handlers.get_debug_info = php_temporal_local_date_get_debug_info;
}
