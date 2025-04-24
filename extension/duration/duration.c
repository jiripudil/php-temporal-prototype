#include "duration.h"
#include <ext/pcre/php_pcre.h>
#include <php.h>
#include <zend_smart_str.h>
#include "utils/compare.h"
#include "utils/remove_trailing_zeroes.h"

temporal_duration_t *temporal_duration_zero() {
	return temporal_duration_of(0, 0);
}

temporal_duration_t *temporal_duration_of(zend_long seconds, zend_long nano_adjustment) {
	temporal_duration_t *duration = ecalloc(1, sizeof(temporal_duration_t));

	zend_long nanos = nano_adjustment % NANOS_PER_SECOND;
	seconds += (nano_adjustment - nanos) / NANOS_PER_SECOND;

	if (nanos < 0) {
		nanos += NANOS_PER_SECOND;
		seconds--;
	}

	duration->seconds = seconds;
	duration->nanos = nanos;
	return duration;
}

temporal_duration_t *temporal_duration_clone(const temporal_duration_t *duration) {
	return temporal_duration_of(duration->seconds, duration->nanos);
}

temporal_duration_t *temporal_duration_negated(const temporal_duration_t *duration) {
	temporal_duration_t *negated = temporal_duration_clone(duration);
	negated->seconds *= -1;

	if (negated->nanos != 0) {
		negated->nanos = NANOS_PER_SECOND - negated->nanos;
		negated->seconds--;
	}

	return negated;
}

int temporal_duration_compare(const temporal_duration_t *a, const temporal_duration_t *b) {
	TEMPORAL_COMPARE_FUNCTION(seconds, a->seconds, b->seconds)
	TEMPORAL_COMPARE_FUNCTION(nanos, a->nanos, b->nanos)
	return 0;
}

temporal_duration_t *temporal_duration_plus(const temporal_duration_t *a, const temporal_duration_t *b) {
	return temporal_duration_of(
		a->seconds + b->seconds,
		a->nanos + b->nanos
	);
}

temporal_duration_t *temporal_duration_minus(const temporal_duration_t *a, const temporal_duration_t *b) {
	return temporal_duration_of(
		a->seconds - b->seconds,
		a->nanos - b->nanos
	);
}

temporal_duration_t *temporal_duration_parse_iso(const char *input) {
	PCRE2_SPTR pattern = "^([+\\-]?)P(?:([+\\-]?[0-9]+)D)?(?:T(?:([+\\-]?[0-9]+)H)?(?:([+\\-]?[0-9]+)M)?(?:([+\\-]?[0-9]+)(?:\\.([0-9]{1,9}))?S)?)?()$";
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

	zend_long days = 0;
	zend_long hours = 0;
	zend_long minutes = 0;
	zend_long seconds = 0;
	zend_long nanos = 0;
	int sign = 1;

	if (ovector[2] != PCRE2_UNSET) {
		sign = input[ovector[2]] == '-' ? -1 : 1;
	}

	if (ovector[4] == PCRE2_UNSET && ovector[6] == PCRE2_UNSET && ovector[8] == PCRE2_UNSET && ovector[10] == PCRE2_UNSET) {
		pcre2_match_data_free(match_data);
		pcre2_code_free(re);
		return NULL;
	}

	if (ovector[4] != PCRE2_UNSET) {
		char days_str[ovector[5] - ovector[4] + 1];
		strncpy(days_str, input + ovector[4], ovector[5] - ovector[4]);
		days_str[ovector[5] - ovector[4]] = '\0';
		days = strtol(days_str, NULL, 10);
	}

	if (ovector[6] != PCRE2_UNSET) {
		char hours_str[ovector[7] - ovector[6] + 1];
		strncpy(hours_str, input + ovector[6], ovector[7] - ovector[6]);
		hours_str[ovector[7] - ovector[6]] = '\0';
		hours = strtol(hours_str, NULL, 10);
	}

	if (ovector[8] != PCRE2_UNSET) {
		char minutes_str[ovector[9] - ovector[8] + 1];
		strncpy(minutes_str, input + ovector[8], ovector[9] - ovector[8]);
		minutes_str[ovector[9] - ovector[8]] = '\0';
		minutes = strtol(minutes_str, NULL, 10);
	}

	if (ovector[10] != PCRE2_UNSET) {
		char seconds_str[ovector[11] - ovector[10] + 1];
		strncpy(seconds_str, input + ovector[10], ovector[11] - ovector[10]);
		seconds_str[ovector[11] - ovector[10]] = '\0';
		seconds = strtol(seconds_str, NULL, 10);
	}

	if (ovector[12] != PCRE2_UNSET) {
		char nanos_str[ovector[13] - ovector[12] + 1];
		strncpy(nanos_str, input + ovector[12], ovector[13] - ovector[12]);
		nanos_str[ovector[13] - ovector[12]] = '\0';
		nanos = sign * strtol(nanos_str, NULL, 10) * (long) pow(10, 9 - (ovector[13] - ovector[12]));
	}

	if (seconds < 0) {
		nanos = -nanos;
	}

	seconds = sign * days * SECONDS_PER_DAY
		+ sign * hours * SECONDS_PER_HOUR
		+ sign * minutes * SECONDS_PER_MINUTE
		+ sign * seconds;

	temporal_duration_t *duration = temporal_duration_of(seconds, nanos);

	pcre2_match_data_free(match_data);
	pcre2_code_free(re);
	return duration;
}

zend_string *temporal_duration_format_iso(const temporal_duration_t *duration) {
	smart_str buf = {0};
	smart_str_appends(&buf, "PT");

	zend_long seconds = duration->seconds;
	zend_long nanos = duration->nanos;

	if (seconds == 0 && nanos == 0) {
		smart_str_appends(&buf, "0S");
		return smart_str_extract(&buf);
	}

	int negative = seconds < 0;

	if (negative && nanos != 0) {
		seconds++;
		nanos = NANOS_PER_SECOND - nanos;
	}

	zend_long hours = seconds / SECONDS_PER_HOUR;
	zend_long minutes = (seconds % SECONDS_PER_HOUR) / SECONDS_PER_MINUTE;
	seconds = seconds % SECONDS_PER_MINUTE;

	if (hours != 0) {
		smart_str_append_long(&buf, hours);
		smart_str_appendc(&buf, 'H');
	}

	if (minutes != 0) {
		smart_str_append_long(&buf, minutes);
		smart_str_appendc(&buf, 'M');
	}

	if (seconds == 0 && nanos == 0) {
		return smart_str_extract(&buf);
	}

	if (seconds == 0 && negative) {
		smart_str_appends(&buf, "-0");
	} else {
		smart_str_append_long(&buf, seconds);
	}

	if (nanos != 0) {
		char nanos_str[11];
		snprintf(nanos_str, sizeof(nanos_str), "%09lld", nanos);
		remove_trailing_zeroes(nanos_str);

		smart_str_appendc(&buf, '.');
		smart_str_appends(&buf, nanos_str);
	}

	smart_str_appendc(&buf, 'S');
	return smart_str_extract(&buf);
}

void temporal_duration_free(temporal_duration_t *duration) {
	efree(duration);
}
