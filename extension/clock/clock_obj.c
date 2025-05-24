#include "clock_obj.h"
#include <php.h>
#include <zend_interfaces.h>
#include "clock/system/system_clock.h"
#include "clock/system/system_clock_ce.h"
#include "instant/instant.h"
#include "instant/instant_obj.h"

temporal_instant_t *temporal_clock_get_time(zend_object *clock) {
	if (clock == NULL || clock->ce == php_temporal_clock_system_ce) {
		return temporal_clock_system_get_time();
	}

	zval now;
	zend_call_method_with_0_params(clock, NULL, NULL, "getTime", &now);

	php_temporal_instant_t *instant_object = php_temporal_instant_from_object(Z_OBJ(now));
	temporal_instant_t *instant = temporal_instant_clone(instant_object->instant);

	zval_ptr_dtor(&now);

	return instant;
}
