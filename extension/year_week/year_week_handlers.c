#include "year_week_handlers.h"
#include <php.h>
#include <zend_smart_str.h>
#include "year_week.h"
#include "year_week_obj.h"

zend_object_handlers php_temporal_year_week_handlers;

static zend_object *php_temporal_year_week_clone_object(zend_object *object) {
	php_temporal_year_week_t *year_week = php_temporal_year_week_from_object(object);
	return php_temporal_year_week_create_object_clone(year_week->year_week);
}

static void php_temporal_year_week_free_object(zend_object *object) {
	php_temporal_year_week_t *year_week = php_temporal_year_week_from_object(object);
	temporal_year_week_free(year_week->year_week);
	zend_object_std_dtor(&year_week->std);
}

static zend_result php_temporal_year_week_cast_object(zend_object *object, zval *return_value, int type) {
	php_temporal_year_week_t *year_week = php_temporal_year_week_from_object(object);

	switch (type) {
		case IS_STRING:
			ZVAL_STR(return_value, temporal_year_week_format_iso(year_week->year_week));
			return SUCCESS;

		case _IS_BOOL:
			ZVAL_TRUE(return_value); // objects are always truthy
			return SUCCESS;

		default:
			return FAILURE;
	}
}

static HashTable *php_temporal_year_week_get_debug_info(zend_object *object, int *is_temp) {
	temporal_year_week_t *year_week = php_temporal_year_week_from_object(object)->year_week;

	HashTable *debug_info;
	ALLOC_HASHTABLE(debug_info);
	zend_hash_init(debug_info, 2, NULL, ZVAL_PTR_DTOR, 0);

	zval tmp;

	ZVAL_LONG(&tmp, year_week->year);
	zend_hash_str_update(debug_info, ZEND_STRL("year"), &tmp);

	ZVAL_LONG(&tmp, year_week->week);
	zend_hash_str_update(debug_info, ZEND_STRL("week"), &tmp);

	*is_temp = 1;

	return debug_info;
}

void php_temporal_register_year_week_handlers() {
	memcpy(&php_temporal_year_week_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	php_temporal_year_week_handlers.offset = XtOffsetOf(php_temporal_year_week_t, std);
	php_temporal_year_week_handlers.clone_obj = php_temporal_year_week_clone_object;
	php_temporal_year_week_handlers.free_obj = php_temporal_year_week_free_object;
	php_temporal_year_week_handlers.cast_object = php_temporal_year_week_cast_object;
	php_temporal_year_week_handlers.get_debug_info = php_temporal_year_week_get_debug_info;
}
