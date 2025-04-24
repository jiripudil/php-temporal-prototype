#ifndef TEMPORAL_DURATION_HANDLERS_H
#define TEMPORAL_DURATION_HANDLERS_H

#include <php.h>

extern zend_object_handlers php_temporal_duration_handlers;

void php_temporal_register_duration_handlers();

#endif // TEMPORAL_DURATION_HANDLERS_H
