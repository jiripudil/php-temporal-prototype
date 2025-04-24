#ifndef TEMPORAL_PERIOD_HANDLERS_H
#define TEMPORAL_PERIOD_HANDLERS_H

#include <php.h>

extern zend_object_handlers php_temporal_period_handlers;

void php_temporal_register_period_handlers();

#endif // TEMPORAL_PERIOD_HANDLERS_H
