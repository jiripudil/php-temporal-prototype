#ifndef TEMPORAL_YEAR_WEEK_OBJ_H
#define TEMPORAL_YEAR_WEEK_OBJ_H

#include <php.h>
#include "year_week.h"

typedef struct _php_temporal_year_week_t {
	temporal_year_week_t *year_week;
	zend_object std;
} php_temporal_year_week_t;

static php_temporal_year_week_t *php_temporal_year_week_from_object(zend_object *obj) {
	return (php_temporal_year_week_t *)((char*)(obj) - XtOffsetOf(php_temporal_year_week_t, std));
}

#define PHP_TEMPORAL_YEAR_WEEK_INTERNAL(p) (p->year_week)
#define Z_TEMPORAL_YEAR_WEEK_P(z) (php_temporal_year_week_from_object(Z_OBJ_P(z)))
#define Z_TEMPORAL_YEAR_WEEK(z) (php_temporal_year_week_from_object(Z_OBJ(z)))
#define Z_TEMPORAL_YEAR_WEEK_INTERNAL_P(z) PHP_TEMPORAL_YEAR_WEEK_INTERNAL(Z_TEMPORAL_YEAR_WEEK_P(z))
#define Z_TEMPORAL_YEAR_WEEK_INTERNAL(z) PHP_TEMPORAL_YEAR_WEEK_INTERNAL(Z_TEMPORAL_YEAR_WEEK(z))
#define Z_OBJ_IS_TEMPORAL_YEAR_WEEK_P(z) (Z_OBJCE_P(z) == php_temporal_year_week_ce)
#define Z_IS_TEMPORAL_YEAR_WEEK_P(z) (Z_TYPE_P(z) == IS_OBJECT && Z_OBJ_IS_TEMPORAL_YEAR_WEEK_P(z)
#define ZVAL_TEMPORAL_YEAR_WEEK(z, year_week) ZVAL_OBJ(z, php_temporal_year_week_create_object_ex(year_week))
#define THIS_TEMPORAL_YEAR_WEEK() Z_TEMPORAL_YEAR_WEEK_P(getThis())
#define THIS_TEMPORAL_YEAR_WEEK_INTERNAL() Z_TEMPORAL_YEAR_WEEK_INTERNAL_P(getThis())

#define RETURN_TEMPORAL_YEAR_WEEK(year_week)                              \
	do {                                                                  \
		php_temporal_year_week_t *_year_week = year_week;                 \
		if (_year_week) {                                                 \
			ZVAL_TEMPORAL_YEAR_WEEK(return_value, _year_week->year_week); \
		} else {                                                          \
			ZVAL_NULL(return_value);                                      \
		}                                                                 \
		return;                                                           \
	} while(0)

zend_object *php_temporal_year_week_create_object(zend_class_entry *ce);
zend_object *php_temporal_year_week_create_object_ex(temporal_year_week_t *year_week);
zend_object *php_temporal_year_week_create_object_clone(temporal_year_week_t *year_week);

#endif // TEMPORAL_YEAR_WEEK_OBJ_H
