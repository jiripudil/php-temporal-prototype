#include "period.h"
#include <pcre2.h>
#include <php.h>
#include <zend_smart_str.h>
#include "local_date/local_date.h"
#include "utils/iso_calendar.h"

temporal_period_t *temporal_period_zero() {
	return temporal_period_of(0, 0, 0);
}

temporal_period_t *temporal_period_of(zend_long years, zend_long months, zend_long days) {
	temporal_period_t *period = ecalloc(1, sizeof(temporal_period_t));

	period->years = years;
	period->months = months;
	period->days = days;

	return period;
}

temporal_period_t *temporal_period_between(temporal_local_date_t *start, temporal_local_date_t *end_exclusive) {
	zend_long a_proleptic_month = start->year * 12 + start->month - 1;
	zend_long b_proleptic_month = end_exclusive->year * 12 + end_exclusive->month - 1;

	zend_long total_months = b_proleptic_month - a_proleptic_month;
	zend_long days = end_exclusive->day - start->day;

	if (total_months > 0 && days < 0) {
		total_months--;
		temporal_local_date_t *calc_date = temporal_local_date_plus_months(start, total_months);
		days = temporal_local_date_to_epoch_day(end_exclusive) - temporal_local_date_to_epoch_day(calc_date);
		temporal_local_date_free(calc_date);
	} else if (total_months < 0 && days > 0) {
		total_months++;
		days -= days_in_month(end_exclusive->year, end_exclusive->month);
	}

	zend_long years = total_months / 12;
	zend_long months = total_months % 12;

	return temporal_period_of(years, months, days);
}

temporal_period_t *temporal_period_clone(const temporal_period_t *period) {
	return temporal_period_of(period->years, period->months, period->days);
}

temporal_period_t *temporal_period_negated(const temporal_period_t *period) {
	return temporal_period_of(-period->years, -period->months, -period->days);
}

temporal_period_t *temporal_period_plus(const temporal_period_t *a, const temporal_period_t *b) {
	return temporal_period_of(
		a->years + b->years,
		a->months + b->months,
		a->days + b->days
	);
}

temporal_period_t *temporal_period_minus(const temporal_period_t *a, const temporal_period_t *b) {
	return temporal_period_of(
		a->years - b->years,
		a->months - b->months,
		a->days - b->days
	);
}

temporal_period_t *temporal_period_parse_iso(const char *input) {
	PCRE2_SPTR pattern = "^([+\\-]?)P(?:([+\\-]?[0-9]+)Y)?(?:([+\\-]?[0-9]+)M)?(?:([+\\-]?[0-9]+)W)?(?:([+\\-]?[0-9]+)D)?()$";
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

	if (ovector[4] == PCRE2_UNSET && ovector[6] == PCRE2_UNSET && ovector[8] == PCRE2_UNSET && ovector[10] == PCRE2_UNSET) {
		return NULL;
	}

	zend_long years = 0;
	zend_long months = 0;
	zend_long weeks = 0;
	zend_long days = 0;
	int sign = 1;

	if (ovector[2] != PCRE2_UNSET) {
		sign = input_string[ovector[2]] == '-' ? -1 : 1;
	}

	if (ovector[4] != PCRE2_UNSET) {
		char years_str[ovector[5] - ovector[4] + 1];
		strncpy(years_str, input + ovector[4], ovector[5] - ovector[4]);
		years_str[ovector[5] - ovector[4]] = '\0';
		years = sign * strtol(years_str, NULL, 10);
	}

	if (ovector[6] != PCRE2_UNSET) {
		char months_str[ovector[7] - ovector[6] + 1];
		strncpy(months_str, input + ovector[6], ovector[7] - ovector[6]);
		months_str[ovector[7] - ovector[6]] = '\0';
		months = sign * strtol(months_str, NULL, 10);
	}

	if (ovector[8] != PCRE2_UNSET) {
		char weeks_str[ovector[9] - ovector[8] + 1];
		strncpy(weeks_str, input + ovector[8], ovector[9] - ovector[8]);
		weeks_str[ovector[9] - ovector[8]] = '\0';
		weeks = sign * strtol(weeks_str, NULL, 10);
	}

	if (ovector[10] != PCRE2_UNSET) {
		char days_str[ovector[11] - ovector[10] + 1];
		strncpy(days_str, input + ovector[10], ovector[11] - ovector[10]);
		days_str[ovector[11] - ovector[10]] = '\0';
		days = sign * strtol(days_str, NULL, 10);
	}

	temporal_period_t *period = temporal_period_of(years, months, weeks * 7 + days);

	pcre2_match_data_free(match_data);
	pcre2_code_free(re);
	return period;
}

zend_string *temporal_period_format_iso(const temporal_period_t *period) {
	smart_str buf = {0};
	smart_str_appendc(&buf, 'P');

	if (period->years == 0 && period->months == 0 && period->days == 0) {
		smart_str_appends(&buf, "0D");
		return smart_str_extract(&buf);
	}

	if (period->years != 0) {
		smart_str_append_long(&buf, period->years);
		smart_str_appendc(&buf, 'Y');
	}

	if (period->months != 0) {
		smart_str_append_long(&buf, period->months);
		smart_str_appendc(&buf, 'M');
	}

	if (period->days != 0) {
		smart_str_append_long(&buf, period->days);
		smart_str_appendc(&buf, 'D');
	}

	return smart_str_extract(&buf);
}

void temporal_period_free(temporal_period_t *period) {
	efree(period);
}
