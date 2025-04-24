#include "local_time.h"
#include <ext/pcre/pcre2.h>
#include <php.h>
#include <zend_smart_str.h>
#include <unicode/udat.h>
#include "exception/exception_obj.h"
#include "format/formatter.h"
#include "utils/compare.h"
#include "utils/remove_trailing_zeroes.h"

temporal_local_time_t *temporal_local_time_midnight() {
	return temporal_local_time_of_seconds_of_day(0, 0);
}

temporal_local_time_t *temporal_local_time_of(zend_long hour, zend_long minute, zend_long second, zend_long nano) {
	zend_long seconds_of_day = hour * SECONDS_PER_HOUR + minute * SECONDS_PER_MINUTE + second;
	return temporal_local_time_of_seconds_of_day(seconds_of_day, nano);
}

temporal_local_time_t *temporal_local_time_of_seconds_of_day(zend_long total_seconds, zend_long nano) {
	temporal_local_time_t *local_time = ecalloc(1, sizeof(temporal_local_time_t));

	local_time->hour = total_seconds / SECONDS_PER_HOUR;
	local_time->minute = (total_seconds % SECONDS_PER_HOUR) / SECONDS_PER_MINUTE;
	local_time->second = total_seconds % SECONDS_PER_MINUTE;
	local_time->nano = nano;

	return local_time;
}

zend_long temporal_local_time_seconds_of_day(temporal_local_time_t *local_time) {
	return local_time->hour * SECONDS_PER_HOUR
		+ local_time->minute * SECONDS_PER_MINUTE
		+ local_time->second;
}

int temporal_local_time_compare(temporal_local_time_t *a, temporal_local_time_t *b) {
	TEMPORAL_COMPARE_FUNCTION(hour, a->hour, b->hour)
	TEMPORAL_COMPARE_FUNCTION(minute, a->minute, b->minute)
	TEMPORAL_COMPARE_FUNCTION(second, a->second, b->second)
	TEMPORAL_COMPARE_FUNCTION(nano, a->nano, b->nano)
	return 0;
}

temporal_local_time_t *temporal_local_time_clone(temporal_local_time_t *local_time) {
	return temporal_local_time_of(local_time->hour, local_time->minute, local_time->second, local_time->nano);
}

temporal_local_time_t *temporal_local_time_plus(temporal_local_time_t *local_time, temporal_duration_t *duration) {
	zend_long second = temporal_local_time_seconds_of_day(local_time) + duration->seconds;
	zend_long nano_adjustment = local_time->nano + duration->nanos;

	zend_long nano = nano_adjustment % NANOS_PER_SECOND;
	second += (nano_adjustment - nano) / NANOS_PER_SECOND;
	if (nano < 0) {
		nano += NANOS_PER_SECOND;
		second--;
	}

	zend_long day = second / SECONDS_PER_DAY;
	second -= day * SECONDS_PER_DAY;
	if (second < 0) {
		second += SECONDS_PER_DAY;
	}

	zend_long hour = second / SECONDS_PER_HOUR;
	second -= hour * SECONDS_PER_HOUR;

	zend_long minute = second / SECONDS_PER_MINUTE;
	second -= minute * SECONDS_PER_MINUTE;

	return temporal_local_time_of(hour, minute, second, nano);
}

temporal_local_time_t *temporal_local_time_minus(temporal_local_time_t *local_time, temporal_duration_t *duration) {
	return temporal_local_time_plus(local_time, temporal_duration_negated(duration));
}

temporal_local_time_t *temporal_local_time_parse_iso(const char *input) {
	PCRE2_SPTR pattern = "^([0-9]{2}):([0-9]{2})(?::([0-9]{2})(?:\\.([0-9]{1,9}))?)?()$";
	PCRE2_SPTR input_string = (PCRE2_SPTR) input;
	PCRE2_SIZE input_length = strlen(input);

	int errornumber;
	PCRE2_SIZE erroroffset;

	pcre2_code *re = pcre2_compile(pattern, PCRE2_ZERO_TERMINATED, PCRE2_CASELESS, &errornumber, &erroroffset, NULL);
	if (re == NULL) {
		return NULL;
	}

	pcre2_match_data *match_data = pcre2_match_data_create_from_pattern(re, NULL);
	int rc = pcre2_match(re, input_string, input_length, 0, 0, match_data, NULL);
	if (rc < 0) {
		pcre2_match_data_free(match_data);
		pcre2_code_free(re);
		return NULL;
	}

	PCRE2_SIZE *ovector = pcre2_get_ovector_pointer(match_data);

	zend_long hour = 0;
	zend_long minute = 0;
	zend_long second = 0;
	zend_long nano = 0;

	char hour_str[ovector[3] - ovector[2] + 1];
	strncpy(hour_str, input + ovector[2], ovector[3] - ovector[2]);
	hour_str[ovector[3] - ovector[2]] = '\0';
	hour = strtol(hour_str, NULL, 10);
	if (hour < 0 || hour > 23) {
		pcre2_match_data_free(match_data);
		pcre2_code_free(re);
		return NULL;
	}

	char minute_str[ovector[5] - ovector[4] + 1];
	strncpy(minute_str, input + ovector[4], ovector[5] - ovector[4]);
	minute_str[ovector[5] - ovector[4]] = '\0';
	minute = strtol(minute_str, NULL, 10);
	if (minute < 0 || minute > 59) {
		pcre2_match_data_free(match_data);
		pcre2_code_free(re);
		return NULL;
	}

	if (ovector[6] != PCRE2_UNSET) {
		char second_str[ovector[7] - ovector[6] + 1];
		strncpy(second_str, input + ovector[6], ovector[7] - ovector[6]);
		second_str[ovector[7] - ovector[6]] = '\0';
		second = strtol(second_str, NULL, 10);
		if (second < 0 || second > 59) {
			pcre2_match_data_free(match_data);
			pcre2_code_free(re);
			return NULL;
		}
	}

	if (ovector[8] != PCRE2_UNSET) {
		char nano_str[ovector[9] - ovector[8] + 1];
		strncpy(nano_str, input + ovector[8], ovector[9] - ovector[8]);
		nano_str[ovector[9] - ovector[8]] = '\0';
		nano = strtol(nano_str, NULL, 10) * (long) pow(10, 9 - (double) (ovector[9] - ovector[8]));
		if (nano < 0 || nano > 999999999) {
			pcre2_match_data_free(match_data);
			pcre2_code_free(re);
			return NULL;
		}
	}

	temporal_local_time_t *local_time = temporal_local_time_of(hour, minute, second, nano);

	pcre2_match_data_free(match_data);
	pcre2_code_free(re);
	return local_time;
}

zend_string *temporal_local_time_format_iso(temporal_local_time_t *local_time) {
	smart_str buf = {0};

	char hour_str[4];
	snprintf(hour_str, sizeof(hour_str), "%02lld", local_time->hour);
	smart_str_appends(&buf, hour_str);
	smart_str_appendc(&buf, ':');

	char minute_str[4];
	snprintf(minute_str, sizeof(minute_str), "%02lld", local_time->minute);
	smart_str_appends(&buf, minute_str);

	if (local_time->second != 0 || local_time->nano != 0) {
		smart_str_appendc(&buf, ':');

		char second_str[4];
		snprintf(second_str, sizeof(second_str), "%02lld", local_time->second);
		smart_str_appends(&buf, second_str);

		if (local_time->nano != 0) {
			char nanos_str[11];
			snprintf(nanos_str, sizeof(nanos_str), "%09lld", local_time->nano);
			remove_trailing_zeroes(nanos_str);

			smart_str_appendc(&buf, '.');
			smart_str_appends(&buf, nanos_str);
		}
	}

	return smart_str_extract(&buf);
}

zend_string *temporal_local_time_format(temporal_local_time_t *local_time, UDateFormat *fmt) {
	if (!temporal_formatter_is_valid_pattern(fmt, TEMPORAL_FORMATTER_FIELD_MASK_TIME)) {
		php_temporal_throw_exception("Failed to format a Temporal value.", 0);
		return NULL;
	}

	UDate timestamp = (UDate) temporal_local_time_seconds_of_day(local_time) * 1000 + (UDate) local_time->nano / 1000000;

	zend_string *result = temporal_formatter_format(fmt, timestamp, NULL);
	if (result == NULL) {
		php_temporal_throw_exception("Failed to format a Temporal value.", 0);
		return NULL;
	}

	return result;
}

void temporal_local_time_free(temporal_local_time_t *local_time) {
	efree(local_time);
}
