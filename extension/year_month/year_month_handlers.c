#include "year_month_handlers.h"
#include <php.h>
#include <zend_smart_str.h>
#include "year_month.h"
#include "year_month_obj.h"

zend_object_handlers php_temporal_year_month_handlers;

static zend_object *php_temporal_year_month_clone_object(zend_object *object) {
	php_temporal_year_month_t *year_month = php_temporal_year_month_from_object(object);
	return php_temporal_year_month_create_object_clone(year_month->year_month);
}

static void php_temporal_year_month_free_object(zend_object *object) {
	php_temporal_year_month_t *year_month = php_temporal_year_month_from_object(object);
	temporal_year_month_free(year_month->year_month);
	zend_object_std_dtor(&year_month->std);
}

static zend_result php_temporal_year_month_cast_object(zend_object *object, zval *return_value, int type) {
	php_temporal_year_month_t *year_month = php_temporal_year_month_from_object(object);

	switch (type) {
		case IS_STRING:
			ZVAL_STR(return_value, temporal_year_month_format_iso(year_month->year_month));
			return SUCCESS;

		case _IS_BOOL:
			ZVAL_TRUE(return_value); // objects are always truthy
			return SUCCESS;

		default:
			return FAILURE;
	}
}

static HashTable *php_temporal_year_month_get_debug_info(zend_object *object, int *is_temp) {
	temporal_year_month_t *year_month = php_temporal_year_month_from_object(object)->year_month;

	HashTable *debug_info;
	ALLOC_HASHTABLE(debug_info);
	zend_hash_init(debug_info, 2, NULL, ZVAL_PTR_DTOR, 0);

	zval tmp;

	ZVAL_LONG(&tmp, year_month->year);
	zend_hash_str_update(debug_info, ZEND_STRL("year"), &tmp);

	ZVAL_LONG(&tmp, year_month->month);
	zend_hash_str_update(debug_info, ZEND_STRL("month"), &tmp);

	*is_temp = 1;

	return debug_info;
}

void php_temporal_register_year_month_handlers() {
	memcpy(&php_temporal_year_month_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	php_temporal_year_month_handlers.offset = XtOffsetOf(php_temporal_year_month_t, std);
	php_temporal_year_month_handlers.clone_obj = php_temporal_year_month_clone_object;
	php_temporal_year_month_handlers.free_obj = php_temporal_year_month_free_object;
	php_temporal_year_month_handlers.cast_object = php_temporal_year_month_cast_object;
	php_temporal_year_month_handlers.get_debug_info = php_temporal_year_month_get_debug_info;
}
