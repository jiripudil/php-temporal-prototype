#include "fixed_clock_ce.h"
#include <php.h>
#include "fixed_clock_arginfo.h"
#include "clock/clock_ce.h"
#include "instant/instant_ce.h"

ZEND_METHOD(Temporal_Clock_FixedClock, __construct) {
	zval *instant;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(instant, php_temporal_instant_ce)
	ZEND_PARSE_PARAMETERS_END();

	zend_update_property(Z_OBJCE_P(getThis()), Z_OBJ_P(getThis()), ZEND_STRL("instant"), instant);
}

ZEND_METHOD(Temporal_Clock_FixedClock, getTime) {
	ZEND_PARSE_PARAMETERS_NONE();

	RETURN_ZVAL(zend_read_property(Z_OBJCE_P(getThis()), Z_OBJ_P(getThis()), ZEND_STRL("instant"), false, NULL), true, false);
}

ZEND_METHOD(Temporal_Clock_FixedClock, setTime) {
	zval *instant;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(instant, php_temporal_instant_ce)
	ZEND_PARSE_PARAMETERS_END();

	zend_update_property(Z_OBJCE_P(getThis()), Z_OBJ_P(getThis()), ZEND_STRL("instant"), instant);
}

zend_class_entry *php_temporal_clock_fixed_ce;

void php_temporal_register_clock_fixed_ce() {
	php_temporal_clock_fixed_ce = register_class_Temporal_Clock_FixedClock(php_temporal_clock_ce);
}
