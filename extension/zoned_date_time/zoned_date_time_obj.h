#ifndef TEMPORAL_ZONED_DATE_TIME_OBJ_H
#define TEMPORAL_ZONED_DATE_TIME_OBJ_H

#include <php.h>
#include "zoned_date_time.h"

typedef struct _php_temporal_zoned_date_time_t {
	temporal_zoned_date_time_t *zoned_date_time;
	zend_object std;
} php_temporal_zoned_date_time_t;

static php_temporal_zoned_date_time_t *php_temporal_zoned_date_time_from_object(zend_object *obj) {
	return (php_temporal_zoned_date_time_t *)((char*)(obj) - XtOffsetOf(php_temporal_zoned_date_time_t, std));
}

#define PHP_TEMPORAL_ZONED_DATE_TIME_INTERNAL(p) (p->zoned_date_time)
#define Z_TEMPORAL_ZONED_DATE_TIME_P(z) (php_temporal_zoned_date_time_from_object(Z_OBJ_P(z)))
#define Z_TEMPORAL_ZONED_DATE_TIME(z) (php_temporal_zoned_date_time_from_object(Z_OBJ(z)))
#define Z_TEMPORAL_ZONED_DATE_TIME_INTERNAL_P(z) PHP_TEMPORAL_ZONED_DATE_TIME_INTERNAL(Z_TEMPORAL_ZONED_DATE_TIME_P(z))
#define Z_TEMPORAL_ZONED_DATE_TIME_INTERNAL(z) PHP_TEMPORAL_ZONED_DATE_TIME_INTERNAL(Z_TEMPORAL_ZONED_DATE_TIME(z))
#define Z_OBJ_IS_TEMPORAL_ZONED_DATE_TIME_P(z) (Z_OBJCE_P(z) == php_temporal_zoned_date_time_ce)
#define Z_IS_TEMPORAL_ZONED_DATE_TIME_P(z) (Z_TYPE_P(z) == IS_OBJECT && Z_OBJ_IS_TEMPORAL_ZONED_DATE_TIME_P(z)
#define ZVAL_TEMPORAL_ZONED_DATE_TIME(z, zoned_date_time) ZVAL_OBJ(z, php_temporal_zoned_date_time_create_object_ex(zoned_date_time))
#define THIS_TEMPORAL_ZONED_DATE_TIME() Z_TEMPORAL_ZONED_DATE_TIME_P(getThis())
#define THIS_TEMPORAL_ZONED_DATE_TIME_INTERNAL() Z_TEMPORAL_ZONED_DATE_TIME_INTERNAL_P(getThis())

#define RETURN_TEMPORAL_ZONED_DATE_TIME(zoned_date_time)                                    \
	do {                                                                                    \
		php_temporal_zoned_date_time_t *_zoned_date_time = zoned_date_time;                 \
		if (_zoned_date_time) {                                                             \
			ZVAL_TEMPORAL_ZONED_DATE_TIME(return_value, _zoned_date_time->zoned_date_time); \
		} else {                                                                            \
			ZVAL_NULL(return_value);                                                        \
		}                                                                                   \
		return;                                                                             \
	} while(0)

zend_object *php_temporal_zoned_date_time_create_object(zend_class_entry *ce);
zend_object *php_temporal_zoned_date_time_create_object_ex(temporal_zoned_date_time_t *zoned_date_time);
zend_object *php_temporal_zoned_date_time_create_object_clone(temporal_zoned_date_time_t *zoned_date_time);

#endif // TEMPORAL_ZONED_DATE_TIME_OBJ_H
