#ifndef TEMPORAL_CLOCK_OBJ_H
#define TEMPORAL_CLOCK_OBJ_H

#include <php.h>
#include "instant/instant.h"

temporal_instant_t *temporal_clock_get_time(zend_object *clock);

#endif // TEMPORAL_CLOCK_OBJ_H
