#include "exception_ce.h"
#include <zend_exceptions.h>
#include "exception_arginfo.h"

zend_class_entry *php_temporal_exception_ce;

void php_temporal_register_exception_ce() {
	php_temporal_exception_ce = register_class_Temporal_TemporalException(zend_ce_exception);
}
