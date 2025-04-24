#ifndef TEMPORAL_INSTANT_OBJ_H
#define TEMPORAL_INSTANT_OBJ_H

#include <php.h>
#include "instant.h"

typedef struct _php_temporal_instant_t {
	temporal_instant_t *instant;
	zend_object std;
} php_temporal_instant_t;

static php_temporal_instant_t *php_temporal_instant_from_object(zend_object *obj) {
	return (php_temporal_instant_t *)((char*)(obj) - XtOffsetOf(php_temporal_instant_t, std));
}

#define PHP_TEMPORAL_INSTANT_INTERNAL(p) (p->instant)
#define Z_TEMPORAL_INSTANT_P(z) (php_temporal_instant_from_object(Z_OBJ_P(z)))
#define Z_TEMPORAL_INSTANT(z) (php_temporal_instant_from_object(Z_OBJ(z)))
#define Z_TEMPORAL_INSTANT_INTERNAL_P(z) PHP_TEMPORAL_INSTANT_INTERNAL(Z_TEMPORAL_INSTANT_P(z))
#define Z_TEMPORAL_INSTANT_INTERNAL(z) PHP_TEMPORAL_INSTANT_INTERNAL(Z_TEMPORAL_INSTANT(z))
#define Z_OBJ_IS_TEMPORAL_INSTANT_P(z) (Z_OBJCE_P(z) == php_temporal_instant_ce)
#define Z_IS_TEMPORAL_INSTANT_P(z) (Z_TYPE_P(z) == IS_OBJECT && Z_OBJ_IS_TEMPORAL_INSTANT_P(z)
#define ZVAL_TEMPORAL_INSTANT(z, instant) ZVAL_OBJ(z, php_temporal_instant_create_object_ex(instant))
#define THIS_TEMPORAL_INSTANT() Z_TEMPORAL_INSTANT_P(getThis())
#define THIS_TEMPORAL_INSTANT_INTERNAL() Z_TEMPORAL_INSTANT_INTERNAL_P(getThis())

#define RETURN_TEMPORAL_INSTANT(instant)                            \
	do {                                                            \
		php_temporal_instant_t *_instant = instant;                 \
		if (_instant) {                                             \
			ZVAL_TEMPORAL_INSTANT(return_value, _instant->instant); \
 		} else {                                                    \
			ZVAL_NULL(return_value);                                \
		}                                                           \
		return;                                                     \
	} while(0)

zend_object *php_temporal_instant_create_object(zend_class_entry *ce);
zend_object *php_temporal_instant_create_object_ex(temporal_instant_t *instant);
zend_object *php_temporal_instant_create_object_clone(temporal_instant_t *instant);

#endif //TEMPORAL_INSTANT_OBJ_H
