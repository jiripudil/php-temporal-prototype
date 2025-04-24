#include "month_day_handlers.h"
#include <php.h>
#include <zend_smart_str.h>
#include "month_day.h"
#include "month_day_obj.h"

zend_object_handlers php_temporal_month_day_handlers;

static zend_object *php_temporal_month_day_clone_object(zend_object *object) {
	php_temporal_month_day_t *month_day = php_temporal_month_day_from_object(object);
	return php_temporal_month_day_create_object_clone(month_day->month_day);
}

static void php_temporal_month_day_free_object(zend_object *object) {
	php_temporal_month_day_t *month_day = php_temporal_month_day_from_object(object);
	temporal_month_day_free(month_day->month_day);
	zend_object_std_dtor(&month_day->std);
}

static zend_result php_temporal_month_day_cast_object(zend_object *object, zval *return_value, int type) {
	php_temporal_month_day_t *month_day = php_temporal_month_day_from_object(object);

	switch (type) {
		case IS_STRING:
			ZVAL_STR(return_value, temporal_month_day_format_iso(month_day->month_day));
			return SUCCESS;

		case _IS_BOOL:
			ZVAL_TRUE(return_value); // objects are always truthy
			return SUCCESS;

		default:
			return FAILURE;
	}
}

static HashTable *php_temporal_month_day_get_debug_info(zend_object *object, int *is_temp) {
	temporal_month_day_t *month_day = php_temporal_month_day_from_object(object)->month_day;

	HashTable *debug_info;
	ALLOC_HASHTABLE(debug_info);
	zend_hash_init(debug_info, 2, NULL, ZVAL_PTR_DTOR, 0);

	zval tmp;

	ZVAL_LONG(&tmp, month_day->month);
	zend_hash_str_update(debug_info, ZEND_STRL("month"), &tmp);

	ZVAL_LONG(&tmp, month_day->day);
	zend_hash_str_update(debug_info, ZEND_STRL("day"), &tmp);

	*is_temp = 1;

	return debug_info;
}

void php_temporal_register_month_day_handlers() {
	memcpy(&php_temporal_month_day_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	php_temporal_month_day_handlers.offset = XtOffsetOf(php_temporal_month_day_t, std);
	php_temporal_month_day_handlers.clone_obj = php_temporal_month_day_clone_object;
	php_temporal_month_day_handlers.free_obj = php_temporal_month_day_free_object;
	php_temporal_month_day_handlers.cast_object = php_temporal_month_day_cast_object;
	php_temporal_month_day_handlers.get_debug_info = php_temporal_month_day_get_debug_info;
}
