#ifndef TEMPORAL_FORMATTER_OBJ_H
#define TEMPORAL_FORMATTER_OBJ_H

#include <php.h>
#include <unicode/udat.h>

typedef struct _php_temporal_formatter_t {
	UDateFormat *fmt;
	zend_object std;
} php_temporal_formatter_t;

static php_temporal_formatter_t *php_temporal_formatter_from_object(zend_object *object) {
	return (php_temporal_formatter_t *)((char *) object - XtOffsetOf(php_temporal_formatter_t, std));
}

#define PHP_TEMPORAL_FORMATTER_INTERNAL(p) (p->fmt)
#define Z_TEMPORAL_FORMATTER_P(z) (php_temporal_formatter_from_object(Z_OBJ_P(z)))
#define Z_TEMPORAL_FORMATTER(z) (php_temporal_formatter_from_object(Z_OBJ(z)))
#define Z_TEMPORAL_FORMATTER_INTERNAL_P(z) PHP_TEMPORAL_FORMATTER_INTERNAL(Z_TEMPORAL_FORMATTER_P(z))
#define Z_TEMPORAL_FORMATTER_INTERNAL(z) PHP_TEMPORAL_FORMATTER_INTERNAL(Z_TEMPORAL_FORMATTER(z))
#define THIS_TEMPORAL_FORMATTER() Z_TEMPORAL_FORMATTER_P(getThis())
#define THIS_TEMPORAL_FORMATTER_INTERNAL() Z_TEMPORAL_FORMATTER_INTERNAL_P(getThis())

zend_object *php_temporal_formatter_create_object(zend_class_entry *ce);
zend_object *php_temporal_formatter_create_object_ex(UDateFormat *fmt);
zend_object *php_temporal_formatter_create_object_clone(php_temporal_formatter_t *formatter);

#endif // TEMPORAL_FORMATTER_OBJ_H
