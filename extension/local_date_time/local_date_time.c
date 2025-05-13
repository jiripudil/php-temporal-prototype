#include "local_date_time.h"
#include <pcre2.h>
#include <php.h>
#include <unicode/udat.h>
#include <zend_smart_str.h>
#include "duration/duration.h"
#include "exception/exception_obj.h"
#include "format/formatter.h"
#include "local_date/local_date.h"
#include "local_time/local_time.h"
#include "utils/iso_calendar.h"

temporal_local_date_time_t *temporal_local_date_time_of(zend_long year, zend_long month, zend_long day, zend_long hour, zend_long minute, zend_long second, zend_long nano) {
	temporal_local_date_t *date = temporal_local_date_of(year, month, day);
	temporal_local_time_t *time = temporal_local_time_of(hour, minute, second, nano);
	return temporal_local_date_time_of_date_time(date, time);
}

temporal_local_date_time_t *temporal_local_date_time_of_date_time(temporal_local_date_t *date, temporal_local_time_t *time) {
	temporal_local_date_time_t *date_time = ecalloc(1, sizeof(temporal_local_date_time_t));

	date_time->date = date;
	date_time->time = time;

	return date_time;
}

int temporal_local_date_time_compare(temporal_local_date_time_t *a, temporal_local_date_time_t *b) {
	int cmp = temporal_local_date_compare(a->date, b->date);
	if (cmp == 0) {
		cmp = temporal_local_time_compare(a->time, b->time);
	}

	return cmp;
}

temporal_local_date_time_t *temporal_local_date_time_clone(temporal_local_date_time_t *local_date_time) {
	return temporal_local_date_time_of_date_time(
		temporal_local_date_clone(local_date_time->date),
		temporal_local_time_clone(local_date_time->time)
	);
}

temporal_local_date_time_t *temporal_local_date_time_plus_duration(temporal_local_date_time_t *local_date_time, temporal_duration_t *duration) {
	zend_long seconds = temporal_local_time_seconds_of_day(local_date_time->time) + duration->seconds;
	zend_long days = seconds / SECONDS_PER_DAY;
	if (seconds < 0 && (days * SECONDS_PER_DAY) != seconds) {
		days--;
	}

	temporal_local_date_t *date = temporal_local_date_plus_days(local_date_time->date, days);
	temporal_local_time_t *time = temporal_local_time_plus(local_date_time->time, duration);
	return temporal_local_date_time_of_date_time(date, time);
}

temporal_local_date_time_t *temporal_local_date_time_parse_iso(const char *input) {
	PCRE2_SPTR pattern = "^(-?[0-9]{4})-([0-9]{2})-([0-9]{2})T([0-9]{2}):([0-9]{2})(?::([0-9]{2})(?:\\.([0-9]{1,9}))?)?()$";
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

	char day_str[ovector[7] - ovector[6] + 1];
	strncpy(day_str, input + ovector[6], ovector[7] - ovector[6]);
	day_str[ovector[7] - ovector[6]] = '\0';
	zend_long day = strtol(day_str, NULL, 10);
	zend_long max_day = days_in_month(year, month);
	if (day < 1 || day > max_day) {
		pcre2_match_data_free(match_data);
		pcre2_code_free(re);
		return NULL;
	}

	char hour_str[ovector[9] - ovector[8] + 1];
	strncpy(hour_str, input + ovector[8], ovector[9] - ovector[8]);
	hour_str[ovector[9] - ovector[8]] = '\0';
	zend_long hour = strtol(hour_str, NULL, 10);
	if (hour < 0 || hour > 23) {
		pcre2_match_data_free(match_data);
		pcre2_code_free(re);
		return NULL;
	}

	char minute_str[ovector[11] - ovector[10] + 1];
	strncpy(minute_str, input + ovector[10], ovector[11] - ovector[10]);
	minute_str[ovector[11] - ovector[10]] = '\0';
	zend_long minute = strtol(minute_str, NULL, 10);
	if (minute < 0 || minute > 59) {
		pcre2_match_data_free(match_data);
		pcre2_code_free(re);
		return NULL;
	}

	zend_long second = 0;
	if (ovector[12] != PCRE2_UNSET) {
		char second_str[ovector[13] - ovector[12] + 1];
		strncpy(second_str, input + ovector[12], ovector[13] - ovector[12]);
		second_str[ovector[13] - ovector[12]] = '\0';
		second = strtol(second_str, NULL, 10);
		if (second < 0 || second > 59) {
			pcre2_match_data_free(match_data);
			pcre2_code_free(re);
			return NULL;
		}
	}

	zend_long nano = 0;
	if (ovector[14] != PCRE2_UNSET) {
		char nano_str[ovector[15] - ovector[14] + 1];
		strncpy(nano_str, input + ovector[14], ovector[15] - ovector[14]);
		nano_str[ovector[15] - ovector[14]] = '\0';
		nano = strtol(nano_str, NULL, 10) * (long) pow(10, 9 - (double) (ovector[15] - ovector[14]));
		if (nano < 0 || nano > 999999999) {
			pcre2_match_data_free(match_data);
			pcre2_code_free(re);
			return NULL;
		}
	}

	temporal_local_date_t *local_date = temporal_local_date_of(year, month, day);
	temporal_local_time_t *local_time = temporal_local_time_of(hour, minute, second, nano);
	temporal_local_date_time_t *local_date_time = temporal_local_date_time_of_date_time(local_date, local_time);

	pcre2_match_data_free(match_data);
	pcre2_code_free(re);
	return local_date_time;
}

zend_string *temporal_local_date_time_format_iso(temporal_local_date_time_t *local_date_time) {
	smart_str buf = {0};

	zend_string *date = temporal_local_date_format_iso(local_date_time->date);
	smart_str_appends(&buf, ZSTR_VAL(date));
	zend_string_release_ex(date, false);

	smart_str_appendc(&buf, 'T');

	zend_string *time = temporal_local_time_format_iso(local_date_time->time);
	smart_str_appends(&buf, ZSTR_VAL(time));
	zend_string_release_ex(time, false);

	return smart_str_extract(&buf);
}

zend_string *temporal_local_date_time_format(temporal_local_date_time_t *local_date_time, UDateFormat *fmt) {
	if (!temporal_formatter_is_valid_pattern(fmt, TEMPORAL_FORMATTER_FIELD_MASK_DATE | TEMPORAL_FORMATTER_FIELD_MASK_TIME)) {
		php_temporal_throw_exception("Failed to format a Temporal value.", 0);
		return NULL;
	}

	UDate timestamp = ((UDate) temporal_local_date_to_epoch_day(local_date_time->date) * (UDate) SECONDS_PER_DAY * 1000)
		+ ((UDate) temporal_local_time_seconds_of_day(local_date_time->time) * 1000) + ((UDate) local_date_time->time->nano / 1000);

	zend_string *result = temporal_formatter_format(fmt, timestamp, NULL);
	if (result == NULL) {
		php_temporal_throw_exception("Failed to format a Temporal value.", 0);
		return NULL;
	}

	return result;
}

void temporal_local_date_time_free(temporal_local_date_time_t *local_date_time) {
	temporal_local_date_free(local_date_time->date);
	temporal_local_time_free(local_date_time->time);
	efree(local_date_time);
}
