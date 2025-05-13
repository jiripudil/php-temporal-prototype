#include "month_day.h"
#include <pcre2.h>
#include <php.h>
#include <zend_smart_str.h>
#include "utils/compare.h"
#include "utils/iso_calendar.h"

temporal_month_day_t *temporal_month_day_of(zend_long month, zend_long day) {
	temporal_month_day_t *month_day = ecalloc(1, sizeof(temporal_month_day_t));

	month_day->month = month;
	month_day->day = day;

	return month_day;
}

int temporal_month_day_compare(temporal_month_day_t *a, temporal_month_day_t *b) {
	TEMPORAL_COMPARE_FUNCTION(month, a->month, b->month)
	TEMPORAL_COMPARE_FUNCTION(day, a->day, b->day)
	return 0;
}

temporal_month_day_t *temporal_month_day_clone(temporal_month_day_t *month_day) {
	return temporal_month_day_of(month_day->month, month_day->day);
}

temporal_month_day_t *temporal_month_day_parse_iso(const char *input) {
	PCRE2_SPTR pattern = "^--([0-9]{2})-([0-9]{2})()$";
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

	zend_long month = 1;
	zend_long day = 1;

	if (ovector[2] == PCRE2_UNSET && ovector[4] == PCRE2_UNSET) {
		pcre2_match_data_free(match_data);
		pcre2_code_free(re);
		return NULL;
	}

	char month_str[ovector[3] - ovector[2] + 1];
	strncpy(month_str, input + ovector[2], ovector[3] - ovector[2]);
	month_str[ovector[3] - ovector[2]] = '\0';
	month = strtol(month_str, NULL, 10);
	if (month < 1 || month > 12) {
		pcre2_match_data_free(match_data);
		pcre2_code_free(re);
		return NULL;
	}

	char day_str[ovector[5] - ovector[4] + 1];
	strncpy(day_str, input + ovector[4], ovector[5] - ovector[4]);
	day_str[ovector[5] - ovector[4]] = '\0';
	day = strtol(day_str, NULL, 10);
	zend_long max_day = max_days_in_month(month);
	if (day < 1 || day > max_day) {
		pcre2_match_data_free(match_data);
		pcre2_code_free(re);
		return NULL;
	}

	temporal_month_day_t *month_day = temporal_month_day_of(month, day);

	pcre2_match_data_free(match_data);
	pcre2_code_free(re);
	return month_day;
}

zend_string *temporal_month_day_format_iso(temporal_month_day_t *month_day) {
	smart_str buf = {0};
	smart_str_appends(&buf, "--");

	char month_str[4];
	snprintf(month_str, sizeof(month_str), "%02lld", month_day->month);
	smart_str_appends(&buf, month_str);
	smart_str_appendc(&buf, '-');

	char day_str[4];
	snprintf(day_str, sizeof(day_str), "%02lld", month_day->day);
	smart_str_appends(&buf, day_str);

	return smart_str_extract(&buf);
}

void temporal_month_day_free(temporal_month_day_t *month_day) {
	efree(month_day);
}
