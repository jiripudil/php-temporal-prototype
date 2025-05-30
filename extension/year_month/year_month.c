#include "year_month.h"
#include <pcre2.h>
#include <php.h>
#include <zend_smart_str.h>
#include "utils/compare.h"

temporal_year_month_t *temporal_year_month_of(zend_long year, zend_long month) {
	temporal_year_month_t *year_month = ecalloc(1, sizeof(temporal_year_month_t));

	year_month->year = year;
	year_month->month = month;

	return year_month;
}

int temporal_year_month_compare(temporal_year_month_t *a, temporal_year_month_t *b) {
	TEMPORAL_COMPARE_FUNCTION(year, a->year, b->year)
	TEMPORAL_COMPARE_FUNCTION(month, a->month, b->month)
	return 0;
}

temporal_year_month_t *temporal_year_month_plus_months(temporal_year_month_t *year_month, zend_long months) {
	zend_long month = year_month->month + months - 1;
	zend_long year_diff = month / 12;

	month = (((month % 12) + 12) % 12) + 1;
	zend_long year = year_month->year + year_diff;

	return temporal_year_month_of(year, month);
}

temporal_year_month_t *temporal_year_month_clone(temporal_year_month_t *year_month) {
	return temporal_year_month_of(year_month->year, year_month->month);
}

temporal_year_month_t *temporal_year_month_parse_iso(const char *input) {
	PCRE2_SPTR pattern = "^(-?[0-9]{4})-([0-9]{2})()$";
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

	if (ovector[2] == PCRE2_UNSET && ovector[4] == PCRE2_UNSET) {
		pcre2_match_data_free(match_data);
		pcre2_code_free(re);
		return NULL;
	}

	char year_str[ovector[3] - ovector[2] + 1];
	strncpy(year_str, input + ovector[2], ovector[3] - ovector[2]);
	year_str[ovector[3] - ovector[2]] = '\0';
	zend_long year = strtol(year_str, NULL, 10);
	if (year < -999999 || year > 999999) {
		pcre2_match_data_free(match_data);
		pcre2_code_free(re);
		return NULL;
	}

	char month_str[ovector[5] - ovector[4] + 1];
	strncpy(month_str, input + ovector[4], ovector[5] - ovector[4]);
	month_str[ovector[5] - ovector[4]] = '\0';
	zend_long month = strtol(month_str, NULL, 10);
	if (month < 1 || month > 12) {
		pcre2_match_data_free(match_data);
		pcre2_code_free(re);
		return NULL;
	}

	temporal_year_month_t *year_month = temporal_year_month_of(year, month);

	pcre2_match_data_free(match_data);
	pcre2_code_free(re);
	return year_month;
}

zend_string *temporal_year_month_format_iso(temporal_year_month_t *year_month) {
	smart_str buf = {0};

	if (year_month->year < 0) {
		smart_str_appendc(&buf, '-');
	}

	char month_str[6];
	snprintf(month_str, sizeof(month_str), "%04llu", labs(year_month->year));
	smart_str_appends(&buf, month_str);
	smart_str_appendc(&buf, '-');

	char day_str[4];
	snprintf(day_str, sizeof(day_str), "%02lld", year_month->month);
	smart_str_appends(&buf, day_str);

	return smart_str_extract(&buf);
}

void temporal_year_month_free(temporal_year_month_t *year_month) {
	efree(year_month);
}
