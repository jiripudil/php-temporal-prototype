#include "system_clock_ce.h"
#include <php.h>
#include <zend_exceptions.h>
#include "clock/clock_ce.h"
#include "clock/system/system_clock.h"
#include "exception/exception_obj.h"
#include "instant/instant.h"
#include "instant/instant_obj.h"
#include "system_clock_arginfo.h"

ZEND_METHOD(Temporal_Clock_SystemClock, getTime) {
	ZEND_PARSE_PARAMETERS_NONE();

	temporal_instant_t *instant = temporal_clock_system_get_time();
	if (instant == NULL) {
		php_temporal_throw_exception("Unable to get current system time.", 0);
		RETURN_THROWS();
	}

	zend_object *object = php_temporal_instant_create_object_ex(instant);
	RETURN_OBJ(object);
}

zend_class_entry *php_temporal_clock_system_ce;

void php_temporal_register_clock_system_ce() {
	php_temporal_clock_system_ce = register_class_Temporal_Clock_SystemClock(php_temporal_clock_ce);
}
