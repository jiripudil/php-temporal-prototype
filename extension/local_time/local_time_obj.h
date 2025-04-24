#ifndef TEMPORAL_LOCAL_TIME_OBJ_H
#define TEMPORAL_LOCAL_TIME_OBJ_H

#include <php.h>
#include "local_time.h"

typedef struct _php_temporal_local_time_t {
	temporal_local_time_t *local_time;
	zend_object std;
} php_temporal_local_time_t;

static php_temporal_local_time_t *php_temporal_local_time_from_object(zend_object *obj) {
	return (php_temporal_local_time_t *)((char*)(obj) - XtOffsetOf(php_temporal_local_time_t, std));
}

#define PHP_TEMPORAL_LOCAL_TIME_INTERNAL(p) (p->local_time)
#define Z_TEMPORAL_LOCAL_TIME_P(z) (php_temporal_local_time_from_object(Z_OBJ_P(z)))
#define Z_TEMPORAL_LOCAL_TIME(z) (php_temporal_local_time_from_object(Z_OBJ(z)))
#define Z_TEMPORAL_LOCAL_TIME_INTERNAL_P(z) PHP_TEMPORAL_LOCAL_TIME_INTERNAL(Z_TEMPORAL_LOCAL_TIME_P(z))
#define Z_TEMPORAL_LOCAL_TIME_INTERNAL(z) PHP_TEMPORAL_LOCAL_TIME_INTERNAL(Z_TEMPORAL_LOCAL_TIME(z))
#define Z_OBJ_IS_TEMPORAL_LOCAL_TIME_P(z) (Z_OBJCE_P(z) == php_temporal_local_time_ce)
#define Z_IS_TEMPORAL_LOCAL_TIME_P(z) (Z_TYPE_P(z) == IS_OBJECT && Z_OBJ_IS_TEMPORAL_LOCAL_TIME_P(z)
#define ZVAL_TEMPORAL_LOCAL_TIME(z, local_time) ZVAL_OBJ(z, php_temporal_local_time_create_object_ex(local_time))
#define THIS_TEMPORAL_LOCAL_TIME() Z_TEMPORAL_LOCAL_TIME_P(getThis())
#define THIS_TEMPORAL_LOCAL_TIME_INTERNAL() Z_TEMPORAL_LOCAL_TIME_INTERNAL_P(getThis())

#define RETURN_TEMPORAL_LOCAL_TIME(local_time)                               \
	do {                                                                     \
		php_temporal_local_time_t *_local_time = local_time;                 \
		if (_local_time) {                                                   \
			ZVAL_TEMPORAL_LOCAL_TIME(return_value, _local_time->local_time); \
		} else {                                                             \
			ZVAL_NULL(return_value);                                         \
		}                                                                    \
		return;                                                              \
	} while(0)

zend_object *php_temporal_local_time_create_object(zend_class_entry *ce);
zend_object *php_temporal_local_time_create_object_ex(temporal_local_time_t *local_time);
zend_object *php_temporal_local_time_create_object_clone(temporal_local_time_t *local_time);

#endif // TEMPORAL_LOCAL_TIME_OBJ_H
