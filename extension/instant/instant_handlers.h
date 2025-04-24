#ifndef TEMPORAL_INSTANT_HANDLERS_H
#define TEMPORAL_INSTANT_HANDLERS_H

#include <php.h>

extern zend_object_handlers php_temporal_instant_handlers;

void php_temporal_register_instant_handlers();

#endif // TEMPORAL_INSTANT_HANDLERS_H
