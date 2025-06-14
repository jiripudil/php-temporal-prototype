#include "time_zone_offset.h"
#include <pcre2.h>
#include <php.h>
#include <zend_smart_str.h>
#include "duration/duration.h"
#include "local_time/local_time.h"

temporal_time_zone_offset_t *temporal_time_zone_offset_utc() {
	return temporal_time_zone_offset_of_total_seconds(0);
}

temporal_time_zone_offset_t *temporal_time_zone_offset_of(zend_long hours, zend_long minutes, zend_long seconds) {
	zend_long total_seconds = hours * SECONDS_PER_HOUR + minutes * SECONDS_PER_MINUTE + seconds;
	return temporal_time_zone_offset_of_total_seconds(total_seconds);
}

temporal_time_zone_offset_t *temporal_time_zone_offset_of_total_seconds(zend_long total_seconds) {
	temporal_time_zone_offset_t *offset = ecalloc(1, sizeof(temporal_time_zone_offset_t));
	offset->total_seconds = total_seconds;
	return offset;
}

temporal_time_zone_offset_t *temporal_time_zone_offset_clone(temporal_time_zone_offset_t *offset) {
	return temporal_time_zone_offset_of_total_seconds(offset->total_seconds);
}

temporal_parse_iso_result_t *temporal_time_zone_offset_parse_iso(const char *id) {
	if (strlen(id) == 1 && (id[0] == 'Z' || id[0] == 'z')) {
		return temporal_parse_iso_result_create();
	}

	PCRE2_SPTR pattern = "^([+\\-])([0-9]{2}):([0-9]{2})(?::([0-9]{2}))?()$";
	PCRE2_SPTR input = (PCRE2_SPTR) id;
	PCRE2_SIZE input_length = strlen(id);

	int errornumber;
	PCRE2_SIZE erroroffset;

	pcre2_code *re = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, PCRE2_CASELESS, &errornumber, &erroroffset, NULL);
	if (re == NULL) {
		return NULL;
	}

	pcre2_match_data *match_data = pcre2_match_data_create_from_pattern(re, NULL);
	int rc = pcre2_match(re, input, input_length, 0, 0, match_data, NULL);
	if (rc < 0) {
		pcre2_match_data_free(match_data);
		pcre2_code_free(re);
		return NULL;
	}

	PCRE2_SIZE *ovector = pcre2_get_ovector_pointer(match_data);

	temporal_parse_iso_result_t *result = temporal_parse_iso_result_create();

	int sign = id[ovector[2]] == '-' ? -1 : 1;

	char hours_str[ovector[5] - ovector[4] + 1];
	strncpy(hours_str, id + ovector[4], ovector[5] - ovector[4]);
	hours_str[ovector[5] - ovector[4]] = '\0';
	result->tz_offset_hour = sign * strtol(hours_str, NULL, 10);

	char minutes_str[ovector[7] - ovector[6] + 1];
	strncpy(minutes_str, id + ovector[6], ovector[7] - ovector[6]);
	minutes_str[ovector[7] - ovector[6]] = '\0';
	result->tz_offset_minute = sign * strtol(minutes_str, NULL, 10);

	result->tz_offset_second = 0;
	if (ovector[8] != PCRE2_UNSET) {
		char seconds_str[ovector[9] - ovector[8] + 1];
		strncpy(seconds_str, id + ovector[8], ovector[9] - ovector[8]);
		seconds_str[ovector[9] - ovector[8]] = '\0';
		result->tz_offset_second = sign * strtol(seconds_str, NULL, 10);
	}

	pcre2_match_data_free(match_data);
	pcre2_code_free(re);
	return result;
}

zend_string *temporal_time_zone_offset_id(temporal_time_zone_offset_t *offset) {
	zend_long total_seconds = offset->total_seconds;
	smart_str buf = {0};

	if (total_seconds == 0) {
		smart_str_appendc(&buf, 'Z');
		return smart_str_extract(&buf);
	}

	if (total_seconds > 0) {
		smart_str_appendc(&buf, '+');
	} else {
		smart_str_appendc(&buf, '-');
	}

	temporal_local_time_t *local_time = temporal_local_time_of_seconds_of_day(labs(total_seconds), 0);
	zend_string *formatted_time = temporal_local_time_format_iso(local_time);

	smart_str_append(&buf, formatted_time);

	temporal_local_time_free(local_time);
	zend_string_release_ex(formatted_time, false);

	return smart_str_extract(&buf);
}

void temporal_time_zone_offset_free(temporal_time_zone_offset_t *offset) {
	efree(offset);
}
