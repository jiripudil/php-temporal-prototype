#include "year_week.h"
#include <pcre2.h>
#include <php.h>
#include <zend_smart_str.h>
#include "local_date/local_date.h"
#include "local_date/local_date_obj.h"
#include "utils/compare.h"
#include "utils/iso_calendar.h"

temporal_year_week_t *temporal_year_week_of(zend_long year, zend_long week) {
	temporal_year_week_t *year_week = ecalloc(1, sizeof(temporal_year_week_t));

	year_week->year = year;
	year_week->week = week;

	return year_week;
}

temporal_year_week_t *temporal_year_week_of_date(temporal_local_date_t *local_date) {
	zend_long year = local_date->year;
	zend_long week = (temporal_local_date_day_of_year(local_date) - temporal_local_date_day_of_week(local_date) + 10) / 7;

	if (week == 0) {
		year--;
		week = weeks_in_year(year);
	} else if (week == 53 && weeks_in_year(year) != 53) {
		year++;
		week = 1;
	}

	return temporal_year_week_of(year, week);
}

int temporal_year_week_compare(temporal_year_week_t *a, temporal_year_week_t *b) {
	TEMPORAL_COMPARE_FUNCTION(year, a->year, b->year)
	TEMPORAL_COMPARE_FUNCTION(week, a->week, b->week)
	return 0;
}

temporal_year_week_t *temporal_year_week_plus_weeks(temporal_year_week_t *year_week, zend_long weeks) {
	temporal_local_date_t *first_day = temporal_year_week_at_day(year_week, 1);
	temporal_local_date_t *result = temporal_local_date_plus_days(first_day, weeks * 7);
	return temporal_year_week_of_date(result);
}

temporal_year_week_t *temporal_year_week_clone(temporal_year_week_t *year_week) {
	return temporal_year_week_of(year_week->year, year_week->week);
}

temporal_local_date_t *temporal_year_week_at_day(temporal_year_week_t *year_week, zend_long day_of_week) {
	temporal_local_date_t *correction_date = temporal_local_date_of(year_week->year, 1, 4);
	zend_long correction = temporal_local_date_day_of_week(correction_date) + 3;
	temporal_local_date_free(correction_date);

	zend_long day_of_year = year_week->week * 7 + day_of_week - correction;
	zend_long max_days_of_year = days_in_year(year_week->year);

	if (day_of_year > max_days_of_year) {
		return temporal_local_date_of_day_of_year(year_week->year + 1, day_of_year - max_days_of_year);
	}

	if (day_of_year > 0) {
		return temporal_local_date_of_day_of_year(year_week->year, day_of_year);
	}

	zend_long days_of_previous_year = days_in_year(year_week->year - 1);
	return temporal_local_date_of_day_of_year(year_week->year - 1, days_of_previous_year + day_of_year);
}

temporal_year_week_t *temporal_year_week_parse_iso(const char *input) {
	PCRE2_SPTR pattern = "^(-?[0-9]{4})-W([0-9]{2})()$";
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

	char week_str[ovector[5] - ovector[4] + 1];
	strncpy(week_str, input + ovector[4], ovector[5] - ovector[4]);
	week_str[ovector[5] - ovector[4]] = '\0';
	zend_long week = strtol(week_str, NULL, 10);
	zend_long max_weeks = weeks_in_year(year);
	if (week < 1 || week > max_weeks) {
		pcre2_match_data_free(match_data);
		pcre2_code_free(re);
		return NULL;
	}

	temporal_year_week_t *year_week = temporal_year_week_of(year, week);

	pcre2_match_data_free(match_data);
	pcre2_code_free(re);
	return year_week;
}

zend_string *temporal_year_week_format_iso(temporal_year_week_t *year_week) {
	smart_str buf = {0};

	if (year_week->year < 0) {
		smart_str_appendc(&buf, '-');
	}

	char week_str[6];
	snprintf(week_str, sizeof(week_str), "%04llu", labs(year_week->year));
	smart_str_appends(&buf, week_str);
	smart_str_appendc(&buf, '-');

	smart_str_appendc(&buf, 'W');

	char day_str[4];
	snprintf(day_str, sizeof(day_str), "%02lld", year_week->week);
	smart_str_appends(&buf, day_str);

	return smart_str_extract(&buf);
}

void temporal_year_week_free(temporal_year_week_t *year_week) {
	efree(year_week);
}
