#ifndef TEMPORAL_EXCEPTION_CE_H
#define TEMPORAL_EXCEPTION_CE_H

#include <php.h>

extern zend_class_entry *php_temporal_exception_ce;

extern zend_class_entry *php_temporal_exception_date_time_conversion_ce;
extern zend_class_entry *php_temporal_exception_formatting_ce;
extern zend_class_entry *php_temporal_exception_parsing_ce;
extern zend_class_entry *php_temporal_exception_value_out_of_range_ce;
extern zend_class_entry *php_temporal_exception_unknown_time_zone_ce;

void php_temporal_register_exception_ce();

#endif // TEMPORAL_EXCEPTION_CE_H
