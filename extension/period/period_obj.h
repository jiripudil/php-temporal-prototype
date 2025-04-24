#ifndef TEMPORAL_PERIOD_OBJ_H
#define TEMPORAL_PERIOD_OBJ_H

#include <php.h>
#include "period.h"

typedef struct _php_temporal_period_t {
	temporal_period_t *period;
	zend_object std;
} php_temporal_period_t;

static php_temporal_period_t *php_temporal_period_from_object(zend_object *obj) {
	return (php_temporal_period_t *)((char*)(obj) - XtOffsetOf(php_temporal_period_t, std));
}

#define PHP_TEMPORAL_PERIOD_INTERNAL(p) (p->period)
#define Z_TEMPORAL_PERIOD_P(z) (php_temporal_period_from_object(Z_OBJ_P(z)))
#define Z_TEMPORAL_PERIOD(z) (php_temporal_period_from_object(Z_OBJ(z)))
#define Z_TEMPORAL_PERIOD_INTERNAL_P(z) PHP_TEMPORAL_PERIOD_INTERNAL(Z_TEMPORAL_PERIOD_P(z))
#define Z_TEMPORAL_PERIOD_INTERNAL(z) PHP_TEMPORAL_PERIOD_INTERNAL(Z_TEMPORAL_PERIOD(z))
#define Z_OBJ_IS_TEMPORAL_PERIOD_P(z) (Z_OBJCE_P(z) == php_temporal_period_ce)
#define Z_IS_TEMPORAL_PERIOD_P(z) (Z_TYPE_P(z) == IS_OBJECT && Z_OBJ_IS_TEMPORAL_PERIOD_P(z)
#define ZVAL_TEMPORAL_PERIOD(z, period) ZVAL_OBJ(z, php_temporal_period_create_object_ex(period))
#define THIS_TEMPORAL_PERIOD() Z_TEMPORAL_PERIOD_P(getThis())
#define THIS_TEMPORAL_PERIOD_INTERNAL() Z_TEMPORAL_PERIOD_INTERNAL_P(getThis())

#define RETURN_TEMPORAL_PERIOD(period)                           \
	do {                                                         \
		php_temporal_period_t *_period = period;                 \
		if (_period) {                                           \
			ZVAL_TEMPORAL_PERIOD(return_value, _period->period); \
 		} else {                                                 \
			ZVAL_NULL(return_value);                             \
		}                                                        \
		return;                                                  \
	} while(0)

zend_object *php_temporal_period_create_object(zend_class_entry *ce);
zend_object *php_temporal_period_create_object_ex(temporal_period_t *period);
zend_object *php_temporal_period_create_object_clone(temporal_period_t *period);

#endif //TEMPORAL_PERIOD_OBJ_H
