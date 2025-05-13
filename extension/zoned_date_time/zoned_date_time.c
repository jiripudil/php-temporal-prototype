#include "zoned_date_time.h"
#include <pcre2.h>
#include <php.h>
#include <zend_smart_str.h>
#include "clock/clock_obj.h"
#include "exception/exception_obj.h"
#include "format/formatter.h"
#include "instant/instant.h"
#include "time_zone/offset/time_zone_offset.h"
#include "time_zone/time_zone.h"
#include "utils/iso_calendar.h"

temporal_zoned_date_time_t *temporal_zoned_date_time_of(temporal_local_date_time_t *date_time, temporal_time_zone_t *zone) {
	temporal_zoned_date_time_t *zoned_date_time = ecalloc(1, sizeof(temporal_zoned_date_time_t));

	zoned_date_time->instant = temporal_time_zone_local_date_time_to_instant(zone, date_time);
	zoned_date_time->zone = zone;

	// the date-time might not be valid for the given timeZone because of a DST transition
	zoned_date_time->date_time = temporal_time_zone_instant_to_local_date_time(zone, zoned_date_time->instant);

	if (IS_TEMPORAL_TIME_ZONE_OFFSET(zone)) {
		zoned_date_time->zone_offset = temporal_time_zone_offset_clone(zone->offset);
	} else {
		zend_long total_seconds = temporal_time_zone_get_offset(zone, zoned_date_time->instant);
		zoned_date_time->zone_offset = temporal_time_zone_offset_of_total_seconds(total_seconds);
	}

	return zoned_date_time;
}

temporal_zoned_date_time_t *temporal_zoned_date_time_of_instant(temporal_instant_t *instant, temporal_time_zone_t *zone) {
	temporal_zoned_date_time_t *zoned_date_time = ecalloc(1, sizeof(temporal_zoned_date_time_t));

	zoned_date_time->date_time = temporal_time_zone_instant_to_local_date_time(zone, instant);
	zoned_date_time->instant = instant;
	zoned_date_time->zone = zone;

	if (IS_TEMPORAL_TIME_ZONE_OFFSET(zone)) {
		zoned_date_time->zone_offset = temporal_time_zone_offset_clone(zone->offset);
	} else {
		zend_long total_seconds = temporal_time_zone_get_offset(zone, instant);
		zoned_date_time->zone_offset = temporal_time_zone_offset_of_total_seconds(total_seconds);
	}

	return zoned_date_time;
}

temporal_zoned_date_time_t *temporal_zoned_date_time_now(temporal_time_zone_t *zone, zend_object *clock) {
	temporal_instant_t *instant = temporal_clock_get_time(clock);
	return temporal_zoned_date_time_of_instant(instant, zone);
}

int temporal_zoned_date_time_compare(temporal_zoned_date_time_t *a, temporal_zoned_date_time_t *b) {
	return temporal_instant_compare(a->instant, b->instant);
}

temporal_zoned_date_time_t *temporal_zoned_date_time_clone(temporal_zoned_date_time_t *zoned_date_time) {
	return temporal_zoned_date_time_of_instant(
		temporal_instant_clone(zoned_date_time->instant),
		temporal_time_zone_clone(zoned_date_time->zone)
	);
}

temporal_zoned_date_time_t *temporal_zoned_date_time_parse_iso(const char *input) {
	PCRE2_SPTR pattern = "^(-?[0-9]{4})-([0-9]{2})-([0-9]{2})T([0-9]{2}):([0-9]{2})(?::([0-9]{2})(?:\\.([0-9]{1,9}))?)?([Zz]|[+\\-][0-9]{2}:[0-9]{2}(?::[0-9]{2})?)(?:\\[(.+)])?()$";
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
	zend_long month = 0;
	zend_long day = 0;
	zend_long hour = 0;
	zend_long minute = 0;
	zend_long second = 0;
	zend_long nano = 0;

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

	char hour_str[ovector[9] - ovector[8] + 1];
	strncpy(hour_str, input + ovector[8], ovector[9] - ovector[8]);
	hour_str[ovector[9] - ovector[8]] = '\0';
	hour = strtol(hour_str, NULL, 10);
	if (hour < 0 || hour > 23) {
		pcre2_match_data_free(match_data);
		pcre2_code_free(re);
		return NULL;
	}

	char minute_str[ovector[11] - ovector[10] + 1];
	strncpy(minute_str, input + ovector[10], ovector[11] - ovector[10]);
	minute_str[ovector[11] - ovector[10]] = '\0';
	minute = strtol(minute_str, NULL, 10);
	if (minute < 0 || minute > 59) {
		pcre2_match_data_free(match_data);
		pcre2_code_free(re);
		return NULL;
	}

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

	temporal_time_zone_t *time_zone = NULL;

	if (ovector[18] != PCRE2_UNSET) {
		char time_zone_id_str[ovector[19] - ovector[18] + 1];
		strncpy(time_zone_id_str, input + ovector[18], ovector[19] - ovector[18]);
		time_zone_id_str[ovector[19] - ovector[18]] = '\0';

		time_zone = temporal_time_zone_of_region(temporal_time_zone_region_of(time_zone_id_str));

	} else {
		char time_zone_offset_str[ovector[17] - ovector[16] + 1];
		strncpy(time_zone_offset_str, input + ovector[16], ovector[17] - ovector[16]);
		time_zone_offset_str[ovector[17] - ovector[16]] = '\0';

		temporal_time_zone_offset_t *offset = temporal_time_zone_offset_parse_iso(time_zone_offset_str);
		if (offset != NULL) {
			time_zone = temporal_time_zone_of_offset(offset);
		}
	}

	if (time_zone == NULL) {
		pcre2_match_data_free(match_data);
		pcre2_code_free(re);
		return NULL;
	}

	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of(local_date_time, time_zone);

	pcre2_match_data_free(match_data);
	pcre2_code_free(re);
	return zoned_date_time;
}

zend_string *temporal_zoned_date_time_format_iso(temporal_zoned_date_time_t *date_time) {
	smart_str buf = {0};

	zend_string *local = temporal_local_date_time_format_iso(date_time->date_time);
	smart_str_appends(&buf, ZSTR_VAL(local));
	zend_string_release(local);

	zend_string *offset = temporal_time_zone_offset_id(date_time->zone_offset);
	smart_str_appends(&buf, ZSTR_VAL(offset));
	zend_string_release(offset);

	if (IS_TEMPORAL_TIME_ZONE_OFFSET(date_time->zone)) {
		return smart_str_extract(&buf);
	}

	zend_string *id = temporal_time_zone_get_id(date_time->zone);

	smart_str_appendc(&buf, '[');
	smart_str_appends(&buf, ZSTR_VAL(id));
	smart_str_appendc(&buf, ']');

	zend_string_release(id);

	return smart_str_extract(&buf);
}

zend_string *temporal_zoned_date_time_format(temporal_zoned_date_time_t *date_time, UDateFormat *fmt) {
	if (!temporal_formatter_is_valid_pattern(fmt, TEMPORAL_FORMATTER_FIELD_MASK_DATE | TEMPORAL_FORMATTER_FIELD_MASK_TIME | TEMPORAL_FORMATTER_FIELD_MASK_TIMEZONE)) {
		php_temporal_throw_exception("Failed to format a Temporal value.", 0);
		return NULL;
	}

	UDate timestamp = (UDate) date_time->instant->epoch_second * 1000 + (UDate) date_time->instant->nano / 1000000;

	zend_string *result = temporal_formatter_format(fmt, timestamp, date_time->zone->time_zone);
	if (result == NULL) {
		php_temporal_throw_exception("Failed to format a Temporal value.", 0);
		return NULL;
	}

	return result;
}

void temporal_zoned_date_time_free(temporal_zoned_date_time_t *zoned_date_time) {
	temporal_local_date_time_free(zoned_date_time->date_time);
	temporal_instant_free(zoned_date_time->instant);
	temporal_time_zone_offset_free(zoned_date_time->zone_offset);
	temporal_time_zone_free(zoned_date_time->zone);
	efree(zoned_date_time);
}
