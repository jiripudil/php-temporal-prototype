#ifndef TEMPORAL_EXCEPTION_OBJ_H
#define TEMPORAL_EXCEPTION_OBJ_H

#include <php.h>

void php_temporal_throw_exception(const char *message, zend_long code);
void php_temporal_throw_date_time_conversion(const char *type);
void php_temporal_throw_formatting_failed_to_generate_pattern(const char *skeleton, const char *locale);
void php_temporal_throw_formatting_invalid_pattern(const char *type);
void php_temporal_throw_formatting_failed_to_format_value(const char *type, const char *error_message);
void php_temporal_throw_parsing_invalid_iso_string(const char *input);
void php_temporal_throw_parsing_value_out_of_range(const char *input, const char *name, zend_long value, zend_long min, zend_long max);
void php_temporal_throw_parsing_unknown_time_zone(const char *input, const char *id);
void php_temporal_throw_parsing(const char *input, const char *error_message);
void php_temporal_throw_unknown_time_zone(const char *id);
void php_temporal_throw_value_out_of_range(const char *name, zend_long value, zend_long min, zend_long max);

#endif // TEMPORAL_EXCEPTION_OBJ_H
