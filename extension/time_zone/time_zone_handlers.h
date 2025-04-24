#ifndef TEMPORAL_TIME_ZONE_HANDLERS_H
#define TEMPORAL_TIME_ZONE_HANDLERS_H

#include <php.h>

extern zend_object_handlers php_temporal_time_zone_handlers;

void php_temporal_register_time_zone_handlers();

#endif // TEMPORAL_TIME_ZONE_HANDLERS_H
