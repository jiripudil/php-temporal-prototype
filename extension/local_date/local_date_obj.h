#ifndef TEMPORAL_LOCAL_DATE_OBJ_H
#define TEMPORAL_LOCAL_DATE_OBJ_H

#include <php.h>
#include "local_date.h"

typedef struct _php_temporal_local_date_t {
	temporal_local_date_t *local_date;
	zend_object std;
} php_temporal_local_date_t;

static php_temporal_local_date_t *php_temporal_local_date_from_object(zend_object *obj) {
	return (php_temporal_local_date_t *)((char*)(obj) - XtOffsetOf(php_temporal_local_date_t, std));
}

#define PHP_TEMPORAL_LOCAL_DATE_INTERNAL(p) (p->local_date)
#define Z_TEMPORAL_LOCAL_DATE_P(z) (php_temporal_local_date_from_object(Z_OBJ_P(z)))
#define Z_TEMPORAL_LOCAL_DATE(z) (php_temporal_local_date_from_object(Z_OBJ(z)))
#define Z_TEMPORAL_LOCAL_DATE_INTERNAL_P(z) PHP_TEMPORAL_LOCAL_DATE_INTERNAL(Z_TEMPORAL_LOCAL_DATE_P(z))
#define Z_TEMPORAL_LOCAL_DATE_INTERNAL(z) PHP_TEMPORAL_LOCAL_DATE_INTERNAL(Z_TEMPORAL_LOCAL_DATE(z))
#define Z_OBJ_IS_TEMPORAL_LOCAL_DATE_P(z) (Z_OBJCE_P(z) == php_temporal_local_date_ce)
#define Z_IS_TEMPORAL_LOCAL_DATE_P(z) (Z_TYPE_P(z) == IS_OBJECT && Z_OBJ_IS_TEMPORAL_LOCAL_DATE_P(z)
#define ZVAL_TEMPORAL_LOCAL_DATE(z, local_date) ZVAL_OBJ(z, php_temporal_local_date_create_object_ex(local_date))
#define THIS_TEMPORAL_LOCAL_DATE() Z_TEMPORAL_LOCAL_DATE_P(getThis())
#define THIS_TEMPORAL_LOCAL_DATE_INTERNAL() Z_TEMPORAL_LOCAL_DATE_INTERNAL_P(getThis())

#define RETURN_TEMPORAL_LOCAL_DATE(local_date)                               \
	do {                                                                     \
		php_temporal_local_date_t *_local_date = local_date;                 \
		if (_local_date) {                                                   \
			ZVAL_TEMPORAL_LOCAL_DATE(return_value, _local_date->local_date); \
		} else {                                                             \
			ZVAL_NULL(return_value);                                         \
		}                                                                    \
		return;                                                              \
	} while(0)

zend_object *php_temporal_local_date_create_object(zend_class_entry *ce);
zend_object *php_temporal_local_date_create_object_ex(temporal_local_date_t *local_date);
zend_object *php_temporal_local_date_create_object_clone(temporal_local_date_t *local_date);

#endif // TEMPORAL_LOCAL_DATE_OBJ_H
