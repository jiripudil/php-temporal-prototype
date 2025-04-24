#ifndef TEMPORAL_EXCEPTION_OBJ_H
#define TEMPORAL_EXCEPTION_OBJ_H

#include <php.h>

void php_temporal_throw_exception(const char *message, zend_long code);
void php_temporal_throw_value_out_of_range(const char *name, zend_long value, zend_long min, zend_long max);

#endif // TEMPORAL_EXCEPTION_OBJ_H
