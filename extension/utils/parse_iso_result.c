#include "parse_iso_result.h"
#include <zend_string.h>

temporal_parse_iso_result_t *temporal_parse_iso_result_create() {
	temporal_parse_iso_result_t *result = ecalloc(1, sizeof(temporal_parse_iso_result_t));
	result->year = 0;
	result->month = 0;
	result->day = 0;
	result->hour = 0;
	result->minute = 0;
	result->second = 0;
	result->nano = 0;
	result->tz_offset_hour = 0;
	result->tz_offset_minute = 0;
	result->tz_offset_second = 0;
	result->tz_identifier = NULL;

	return result;
}

void temporal_parse_iso_result_free(temporal_parse_iso_result_t *result) {
	if (result->tz_identifier != NULL) {
		zend_string_release(result->tz_identifier);
	}

	efree(result);
}
