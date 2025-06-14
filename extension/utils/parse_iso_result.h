#ifndef TEMPORAL_UTILS_PARSE_ISO_RESULT_H
#define TEMPORAL_UTILS_PARSE_ISO_RESULT_H

#include <php.h>
#include <zend_long.h>
#include <zend_string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TEMPORAL_CHECK_PARSE_ISO_VALUE_RANGE(input, result, name, value, min, max)   \
	if (value < min || value > max) {                                                \
		php_temporal_throw_parsing_value_out_of_range(input, name, value, min, max); \
		temporal_parse_iso_result_free(result);                                      \
		RETURN_THROWS();                                                             \
	}

typedef struct _temporal_parse_iso_result_t {
	zend_long year;
	zend_long month;
	zend_long week;
	zend_long day;
	zend_long hour;
	zend_long minute;
	zend_long second;
	zend_long nano;
	zend_long tz_offset_hour;
	zend_long tz_offset_minute;
	zend_long tz_offset_second;
	zend_string *tz_identifier;
} temporal_parse_iso_result_t;

temporal_parse_iso_result_t *temporal_parse_iso_result_create();
void temporal_parse_iso_result_free(temporal_parse_iso_result_t *result);

#ifdef __cplusplus
}
#endif

#endif // TEMPORAL_UTILS_PARSE_ISO_RESULT_H
