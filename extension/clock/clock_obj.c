#include "clock_obj.h"
#include <php.h>
#include <zend_interfaces.h>
#include "clock/system/system_clock.h"
#include "instant/instant.h"
#include "instant/instant_obj.h"

temporal_instant_t *temporal_clock_get_time(zend_object *clock) {
	if (clock == NULL) {
		return temporal_clock_system_get_time();
	}

	zval now;

	zend_string *method_name = zend_string_init("getTime", strlen("getTime"), 0);
	zend_call_method_if_exists(clock, method_name, &now, 0, NULL);
	zend_string_release(method_name);

	php_temporal_instant_t *instant_object = php_temporal_instant_from_object(Z_OBJ(now));
	temporal_instant_t *instant = temporal_instant_clone(instant_object->instant);
	zend_objects_destroy_object(Z_OBJ(now));

	return instant;
}
