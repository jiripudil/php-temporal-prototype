#ifndef TEMPORAL_TIME_ZONE_OBJ_H
#define TEMPORAL_TIME_ZONE_OBJ_H

#include <php.h>
#include "time_zone.h"

typedef struct _php_temporal_time_zone_t {
	temporal_time_zone_t *time_zone;
	zend_object std;
} php_temporal_time_zone_t;

static php_temporal_time_zone_t *php_temporal_time_zone_from_object(zend_object *obj) {
	return (php_temporal_time_zone_t *)((char*)(obj) - XtOffsetOf(php_temporal_time_zone_t, std));
}

#define PHP_TEMPORAL_TIME_ZONE_INTERNAL(p) (p->time_zone)
#define Z_TEMPORAL_TIME_ZONE_P(z) (php_temporal_time_zone_from_object(Z_OBJ_P(z)))
#define Z_TEMPORAL_TIME_ZONE(z) (php_temporal_time_zone_from_object(Z_OBJ(z)))
#define Z_TEMPORAL_TIME_ZONE_INTERNAL_P(z) PHP_TEMPORAL_TIME_ZONE_INTERNAL(Z_TEMPORAL_TIME_ZONE_P(z))
#define Z_TEMPORAL_TIME_ZONE_INTERNAL(z) PHP_TEMPORAL_TIME_ZONE_INTERNAL(Z_TEMPORAL_TIME_ZONE(z))
#define Z_OBJ_IS_TEMPORAL_TIME_ZONE_P(z) (Z_OBJCE_P(z) == php_temporal_time_zone_ce)
#define Z_IS_TEMPORAL_TIME_ZONE_P(z) (Z_TYPE_P(z) == IS_OBJECT && Z_OBJ_IS_TEMPORAL_TIME_ZONE_P(z)
#define ZVAL_TEMPORAL_TIME_ZONE(z, time_zone) ZVAL_OBJ(z, php_temporal_time_zone_create_object_ex(time_zone))
#define THIS_TEMPORAL_TIME_ZONE() Z_TEMPORAL_TIME_ZONE_P(getThis())
#define THIS_TEMPORAL_TIME_ZONE_INTERNAL() Z_TEMPORAL_TIME_ZONE_INTERNAL_P(getThis())

zend_object *php_temporal_time_zone_create_object(zend_class_entry *ce);
zend_object *php_temporal_time_zone_create_object_ex(temporal_time_zone_t *time_zone);
zend_object *php_temporal_time_zone_create_object_clone(temporal_time_zone_t *time_zone);

#endif // TEMPORAL_TIME_ZONE_OBJ_H
