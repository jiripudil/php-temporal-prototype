#include "clock_ce.h"
#include <php.h>
#include "clock_arginfo.h"

zend_class_entry *php_temporal_clock_ce;

void php_temporal_register_clock_ce() { php_temporal_clock_ce = register_class_Temporal_Clock(); }
