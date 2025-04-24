#ifndef TEMPORAL_MONTH_DAY_OBJ_H
#define TEMPORAL_MONTH_DAY_OBJ_H

#include <php.h>
#include "month_day.h"

typedef struct _php_temporal_month_day_t {
	temporal_month_day_t *month_day;
	zend_object std;
} php_temporal_month_day_t;

static php_temporal_month_day_t *php_temporal_month_day_from_object(zend_object *obj) {
	return (php_temporal_month_day_t *)((char*)(obj) - XtOffsetOf(php_temporal_month_day_t, std));
}

#define PHP_TEMPORAL_MONTH_DAY_INTERNAL(p) (p->month_day)
#define Z_TEMPORAL_MONTH_DAY_P(z) (php_temporal_month_day_from_object(Z_OBJ_P(z)))
#define Z_TEMPORAL_MONTH_DAY(z) (php_temporal_month_day_from_object(Z_OBJ(z)))
#define Z_TEMPORAL_MONTH_DAY_INTERNAL_P(z) PHP_TEMPORAL_MONTH_DAY_INTERNAL(Z_TEMPORAL_MONTH_DAY_P(z))
#define Z_TEMPORAL_MONTH_DAY_INTERNAL(z) PHP_TEMPORAL_MONTH_DAY_INTERNAL(Z_TEMPORAL_MONTH_DAY(z))
#define Z_OBJ_IS_TEMPORAL_MONTH_DAY_P(z) (Z_OBJCE_P(z) == php_temporal_month_day_ce)
#define Z_IS_TEMPORAL_MONTH_DAY_P(z) (Z_TYPE_P(z) == IS_OBJECT && Z_OBJ_IS_TEMPORAL_MONTH_DAY_P(z)
#define ZVAL_TEMPORAL_MONTH_DAY(z, month_day) ZVAL_OBJ(z, php_temporal_month_day_create_object_ex(month_day))
#define THIS_TEMPORAL_MONTH_DAY() Z_TEMPORAL_MONTH_DAY_P(getThis())
#define THIS_TEMPORAL_MONTH_DAY_INTERNAL() Z_TEMPORAL_MONTH_DAY_INTERNAL_P(getThis())

#define RETURN_TEMPORAL_MONTH_DAY(month_day)                              \
	do {                                                                  \
		php_temporal_month_day_t *_month_day = month_day;                 \
		if (_month_day) {                                                 \
			ZVAL_TEMPORAL_MONTH_DAY(return_value, _month_day->month_day); \
		} else {                                                          \
			ZVAL_NULL(return_value);                                      \
		}                                                                 \
		return;                                                           \
	} while(0)

zend_object *php_temporal_month_day_create_object(zend_class_entry *ce);
zend_object *php_temporal_month_day_create_object_ex(temporal_month_day_t *month_day);
zend_object *php_temporal_month_day_create_object_clone(temporal_month_day_t *month_day);

#endif // TEMPORAL_MONTH_DAY_OBJ_H
