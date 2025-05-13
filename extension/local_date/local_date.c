#include "local_date.h"
#include <pcre2.h>
#include <php.h>
#include <zend_smart_str.h>
#include <unicode/udat.h>
#include "duration/duration.h"
#include "exception/exception_obj.h"
#include "format/formatter.h"
#include "utils/compare.h"
#include "utils/iso_calendar.h"

temporal_local_date_t *temporal_local_date_of(zend_long year, zend_long month, zend_long day) {
	temporal_local_date_t *local_date = ecalloc(1, sizeof(temporal_local_date_t));

	local_date->year = year;
	local_date->month = month;
	local_date->day = day;

	return local_date;
}

temporal_local_date_t *temporal_local_date_of_day_of_year(zend_long year, zend_long day_of_year) {
	zend_long month_of_year = ((day_of_year - 1) / 31) + 1;
	zend_long month_end = first_day_of_year(year, month_of_year) + days_in_month(year, month_of_year) - 1;

	if (day_of_year > month_end) {
		month_of_year++;
	}

	zend_long day_of_month = day_of_year - first_day_of_year(year, month_of_year) + 1;

	return temporal_local_date_of(year, month_of_year, day_of_month);
}

temporal_local_date_t *temporal_local_date_of_epoch_day(zend_long epoch_day) {
	zend_long zero_day = epoch_day + DAYS_0000_TO_1970;
	zero_day -= 60; // adjust to 0000-03-01 so leap day is at the end of a four-year cycle

	zend_long adjust = 0;
	if (zero_day < 0) {
		// adjust negative years to positive for calculation
		zend_long adjust_cycles = ((zero_day + 1) / DAYS_PER_CYCLE) - 1;
		adjust = adjust_cycles * 400;
		zero_day += -adjust_cycles * DAYS_PER_CYCLE;
	}

	zend_long year_est = ((400 * zero_day) + 591) / DAYS_PER_CYCLE;
	zend_long doy_est = zero_day - (365 * year_est + (year_est / 4) - (year_est / 100) + (year_est / 400));
	if (doy_est < 0) {
		year_est--;
		doy_est = zero_day - (365 * year_est + (year_est / 4) - (year_est / 100) + (year_est / 400));
	}

	year_est += adjust; // reset any negative year
	zend_long march_doy_0 = doy_est;

	// convert march-based value back to january-based
	zend_long march_month_0 = (march_doy_0 * 5 + 2) / 153;
	zend_long month = march_month_0 + 3;
	if (month > 12) {
		month -= 12;
	}

	zend_long dom = march_doy_0 - ((march_month_0 * 306 + 5) / 10) + 1;
	if (march_doy_0 >= 306) {
		year_est++;
	}

	return temporal_local_date_of(year_est, month, dom);
}

zend_long temporal_local_date_to_epoch_day(temporal_local_date_t *local_date) {
	zend_long y = local_date->year;
	zend_long m = local_date->month;

	zend_long total = 365 * y;

	if (y >= 0) {
		total += ((y + 3) / 4) - ((y + 99) / 100) + ((y + 399) / 400);
	} else {
		total -= (y / -4) - (y / -100) + (y / -400);
	}

	total += (367 * m - 362) / 12;
	total += local_date->day - 1;

	if (m > 2) {
		total--;
		if (!is_leap_year(local_date->year)) {
			total--;
		}
	}

	return total - DAYS_0000_TO_1970;
}

zend_long temporal_local_date_day_of_year(temporal_local_date_t *local_date) {
	return first_day_of_year(local_date->year, local_date->month) + local_date->day - 1;
}

zend_long temporal_local_date_day_of_week(temporal_local_date_t *local_date) {
	zend_long year = local_date->year;
	zend_long month = local_date->month;
	zend_long day = local_date->day;

	if (month < 3) {
		month += 12;
		year--;
	}

	zend_long k = ((year % 100) + 100) % 100;
	zend_long j = year / 100;

	zend_long h = (((day + (13 * (month + 1)) / 5) + k + (k / 4) + (j / 4) - (2 * j) % 7) + 7) % 7;
	return ((((h + 5) % 7) + 7) % 7) + 1;
}

int temporal_local_date_compare(temporal_local_date_t *a, temporal_local_date_t *b) {
	TEMPORAL_COMPARE_FUNCTION(year, a->year, b->year)
	TEMPORAL_COMPARE_FUNCTION(month, a->month, b->month)
	TEMPORAL_COMPARE_FUNCTION(day, a->day, b->day)
	return 0;
}

temporal_local_date_t *temporal_local_date_clone(temporal_local_date_t *local_date) {
	return temporal_local_date_of(local_date->year, local_date->month, local_date->day);
}

temporal_local_date_t *temporal_local_date_plus_years(temporal_local_date_t *local_date, zend_long years) {
	zend_long year = local_date->year + years;
	zend_long month = local_date->month;
	zend_long day = local_date->day;
	zend_long max_day = days_in_month(year, local_date->month);
	if (day > max_day) {
		day = max_day;
	}

	return temporal_local_date_of(year, month, day);
}

temporal_local_date_t *temporal_local_date_plus_months(temporal_local_date_t *local_date, zend_long months) {
	zend_long month = local_date->month + months - 1;

	zend_long year_diff = month / 12;
	if (month < 0 && (year_diff * 12 != month)) {
		year_diff--;
	}

	month = (((month % 12) + 12) % 12) + 1;
	zend_long year = local_date->year + year_diff;

	zend_long day = local_date->day;
	zend_long max_day = days_in_month(year, month);
	if (day > max_day) {
		day = max_day;
	}

	return temporal_local_date_of(year, month, day);
}

temporal_local_date_t *temporal_local_date_plus_days(temporal_local_date_t *local_date, zend_long days) {
	return temporal_local_date_of_epoch_day(temporal_local_date_to_epoch_day(local_date) + days);
}

temporal_local_date_t *temporal_local_date_parse_iso(const char *input) {
	PCRE2_SPTR pattern = "^(-?[0-9]{4})-([0-9]{2})-([0-9]{2})()$";
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

	zend_long year = 0;
	zend_long month = 1;
	zend_long day = 1;

	char year_str[ovector[3] - ovector[2] + 1];
	strncpy(year_str, input + ovector[2], ovector[3] - ovector[2]);
	year_str[ovector[3] - ovector[2]] = '\0';
	year = strtol(year_str, NULL, 10);
	if (year < -999999 || year > 999999) {
		pcre2_match_data_free(match_data);
		pcre2_code_free(re);
		return NULL;
	}

	char month_str[ovector[5] - ovector[4] + 1];
	strncpy(month_str, input + ovector[4], ovector[5] - ovector[4]);
	month_str[ovector[5] - ovector[4]] = '\0';
	month = strtol(month_str, NULL, 10);
	if (month < 1 || month > 12) {
		pcre2_match_data_free(match_data);
		pcre2_code_free(re);
		return NULL;
	}

	char day_str[ovector[7] - ovector[6] + 1];
	strncpy(day_str, input + ovector[6], ovector[7] - ovector[6]);
	day_str[ovector[7] - ovector[6]] = '\0';
	day = strtol(day_str, NULL, 10);
	zend_long max_day = days_in_month(year, month);
	if (day < 1 || day > max_day) {
		pcre2_match_data_free(match_data);
		pcre2_code_free(re);
		return NULL;
	}

	temporal_local_date_t *local_date = temporal_local_date_of(year, month, day);

	pcre2_match_data_free(match_data);
	pcre2_code_free(re);
	return local_date;
}

zend_string *temporal_local_date_format_iso(temporal_local_date_t *local_date) {
	smart_str buf = {0};

	if (local_date->year < 0) {
		smart_str_appendc(&buf, '-');
	}

	char year_str[6];
	snprintf(year_str, sizeof(year_str), "%04lld", labs(local_date->year));
	smart_str_appends(&buf, year_str);
	smart_str_appendc(&buf, '-');

	char month_str[4];
	snprintf(month_str, sizeof(month_str), "%02lld", local_date->month);
	smart_str_appends(&buf, month_str);
	smart_str_appendc(&buf, '-');

	char day_str[4];
	snprintf(day_str, sizeof(day_str), "%02lld", local_date->day);
	smart_str_appends(&buf, day_str);

	return smart_str_extract(&buf);
}

zend_string *temporal_local_date_format(temporal_local_date_t *local_date, UDateFormat *fmt) {
	if (!temporal_formatter_is_valid_pattern(fmt, TEMPORAL_FORMATTER_FIELD_MASK_DATE)) {
		php_temporal_throw_exception("Failed to format a Temporal value.", 0);
		return NULL;
	}

	UDate timestamp = (UDate) temporal_local_date_to_epoch_day(local_date) * (UDate) SECONDS_PER_DAY * 1000;

	zend_string *result = temporal_formatter_format(fmt, timestamp, NULL);
	if (result == NULL) {
		php_temporal_throw_exception("Failed to format a Temporal value.", 0);
		return NULL;
	}

	return result;
}

void temporal_local_date_free(temporal_local_date_t *local_date) {
	efree(local_date);
}
