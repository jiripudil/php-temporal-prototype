#ifndef TEMPORAL_DURATION_OBJ_H
#define TEMPORAL_DURATION_OBJ_H

#include <php.h>
#include "duration.h"

typedef struct _php_temporal_duration_t {
	temporal_duration_t *duration;
	zend_object std;
} php_temporal_duration_t;

static php_temporal_duration_t *php_temporal_duration_from_object(zend_object *obj) {
	return (php_temporal_duration_t *)((char*)(obj) - XtOffsetOf(php_temporal_duration_t, std));
}

#define PHP_TEMPORAL_DURATION_INTERNAL(p) (p->duration)
#define Z_TEMPORAL_DURATION_P(z) (php_temporal_duration_from_object(Z_OBJ_P(z)))
#define Z_TEMPORAL_DURATION(z) (php_temporal_duration_from_object(Z_OBJ(z)))
#define Z_TEMPORAL_DURATION_INTERNAL_P(z) PHP_TEMPORAL_DURATION_INTERNAL(Z_TEMPORAL_DURATION_P(z))
#define Z_TEMPORAL_DURATION_INTERNAL(z) PHP_TEMPORAL_DURATION_INTERNAL(Z_TEMPORAL_DURATION(z))
#define Z_OBJ_IS_TEMPORAL_DURATION_P(z) (Z_OBJCE_P(z) == php_temporal_duration_ce)
#define Z_IS_TEMPORAL_DURATION_P(z) (Z_TYPE_P(z) == IS_OBJECT && Z_OBJ_IS_TEMPORAL_DURATION_P(z)
#define ZVAL_TEMPORAL_DURATION(z, duration) ZVAL_OBJ(z, php_temporal_duration_create_object_ex(duration))
#define THIS_TEMPORAL_DURATION() Z_TEMPORAL_DURATION_P(getThis())
#define THIS_TEMPORAL_DURATION_INTERNAL() Z_TEMPORAL_DURATION_INTERNAL_P(getThis())

#define RETURN_TEMPORAL_DURATION(duration)                             \
	do {                                                               \
		php_temporal_duration_t *_duration = duration;                 \
		if (_duration) {                                               \
			ZVAL_TEMPORAL_DURATION(return_value, _duration->duration); \
 		} else {                                                       \
			ZVAL_NULL(return_value);                                   \
		}                                                              \
		return;                                                        \
	} while(0)

zend_object *php_temporal_duration_create_object(zend_class_entry *ce);
zend_object *php_temporal_duration_create_object_ex(temporal_duration_t *duration);
zend_object *php_temporal_duration_create_object_clone(temporal_duration_t *duration);

#endif //TEMPORAL_DURATION_OBJ_H
