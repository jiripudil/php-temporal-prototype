#include "period_handlers.h"
#include <php.h>
#include <zend_smart_str.h>
#include "period.h"
#include "period_obj.h"

zend_object_handlers php_temporal_period_handlers;

static zend_object *php_temporal_period_clone_object(zend_object *object) {
	php_temporal_period_t *period = php_temporal_period_from_object(object);
	return php_temporal_period_create_object_clone(period->period);
}

static void php_temporal_period_free_object(zend_object *object) {
	php_temporal_period_t *period = php_temporal_period_from_object(object);
	temporal_period_free(period->period);
	zend_object_std_dtor(&period->std);
}

static zend_result php_temporal_period_cast_object(zend_object *object, zval *return_value, int type) {
	php_temporal_period_t *period = php_temporal_period_from_object(object);

	switch (type) {
		case IS_STRING:
			ZVAL_STR(return_value, temporal_period_format_iso(period->period));
			return SUCCESS;

		case _IS_BOOL:
			ZVAL_TRUE(return_value); // objects are always truthy
			return SUCCESS;

		default:
			return FAILURE;
	}
}

static HashTable *php_temporal_period_get_debug_info(zend_object *object, int *is_temp) {
	temporal_period_t *period = php_temporal_period_from_object(object)->period;

	HashTable *debug_info;
	ALLOC_HASHTABLE(debug_info);
	zend_hash_init(debug_info, 2, NULL, ZVAL_PTR_DTOR, 0);

	zval tmp;

	ZVAL_LONG(&tmp, period->years);
	zend_hash_str_update(debug_info, ZEND_STRL("years"), &tmp);

	ZVAL_LONG(&tmp, period->months);
	zend_hash_str_update(debug_info, ZEND_STRL("months"), &tmp);

	ZVAL_LONG(&tmp, period->days);
	zend_hash_str_update(debug_info, ZEND_STRL("days"), &tmp);

	*is_temp = 1;

	return debug_info;
}

void php_temporal_register_period_handlers() {
	memcpy(&php_temporal_period_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));

	php_temporal_period_handlers.offset = XtOffsetOf(php_temporal_period_t, std);
	php_temporal_period_handlers.clone_obj = php_temporal_period_clone_object;
	php_temporal_period_handlers.free_obj = php_temporal_period_free_object;
	php_temporal_period_handlers.cast_object = php_temporal_period_cast_object;
	php_temporal_period_handlers.get_debug_info = php_temporal_period_get_debug_info;
}
