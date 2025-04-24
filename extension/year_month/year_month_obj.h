#ifndef TEMPORAL_YEAR_MONTH_OBJ_H
#define TEMPORAL_YEAR_MONTH_OBJ_H

#include <php.h>
#include "year_month.h"

typedef struct _php_temporal_year_month_t {
	temporal_year_month_t *year_month;
	zend_object std;
} php_temporal_year_month_t;

static php_temporal_year_month_t *php_temporal_year_month_from_object(zend_object *obj) {
	return (php_temporal_year_month_t *)((char*)(obj) - XtOffsetOf(php_temporal_year_month_t, std));
}

#define PHP_TEMPORAL_YEAR_MONTH_INTERNAL(p) (p->year_month)
#define Z_TEMPORAL_YEAR_MONTH_P(z) (php_temporal_year_month_from_object(Z_OBJ_P(z)))
#define Z_TEMPORAL_YEAR_MONTH(z) (php_temporal_year_month_from_object(Z_OBJ(z)))
#define Z_TEMPORAL_YEAR_MONTH_INTERNAL_P(z) PHP_TEMPORAL_YEAR_MONTH_INTERNAL(Z_TEMPORAL_YEAR_MONTH_P(z))
#define Z_TEMPORAL_YEAR_MONTH_INTERNAL(z) PHP_TEMPORAL_YEAR_MONTH_INTERNAL(Z_TEMPORAL_YEAR_MONTH(z))
#define Z_OBJ_IS_TEMPORAL_YEAR_MONTH_P(z) (Z_OBJCE_P(z) == php_temporal_year_month_ce)
#define Z_IS_TEMPORAL_YEAR_MONTH_P(z) (Z_TYPE_P(z) == IS_OBJECT && Z_OBJ_IS_TEMPORAL_YEAR_MONTH_P(z)
#define ZVAL_TEMPORAL_YEAR_MONTH(z, year_month) ZVAL_OBJ(z, php_temporal_year_month_create_object_ex(year_month))
#define THIS_TEMPORAL_YEAR_MONTH() Z_TEMPORAL_YEAR_MONTH_P(getThis())
#define THIS_TEMPORAL_YEAR_MONTH_INTERNAL() Z_TEMPORAL_YEAR_MONTH_INTERNAL_P(getThis())

#define RETURN_TEMPORAL_YEAR_MONTH(year_month)                               \
	do {                                                                     \
		php_temporal_year_month_t *_year_month = year_month;                 \
		if (_year_month) {                                                   \
			ZVAL_TEMPORAL_YEAR_MONTH(return_value, _year_month->year_month); \
		} else {                                                             \
			ZVAL_NULL(return_value);                                         \
		}                                                                    \
		return;                                                              \
	} while(0)

zend_object *php_temporal_year_month_create_object(zend_class_entry *ce);
zend_object *php_temporal_year_month_create_object_ex(temporal_year_month_t *year_month);
zend_object *php_temporal_year_month_create_object_clone(temporal_year_month_t *year_month);

#endif // TEMPORAL_YEAR_MONTH_OBJ_H
