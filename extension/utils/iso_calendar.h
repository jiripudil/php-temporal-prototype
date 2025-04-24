#ifndef TEMPORAL_UTILS_ISO_CALENDAR_H
#define TEMPORAL_UTILS_ISO_CALENDAR_H

#include <php.h>
#include "local_date/local_date.h"

static bool is_leap_year(zend_long year) {
	return ((year & 3) == 0) && ((year % 100) != 0 || (year % 400 == 0));
}

static zend_long days_in_year(zend_long year) {
	return is_leap_year(year) ? 366 : 365;
}

static zend_long weeks_in_year(zend_long year) {
	temporal_local_date_t *first_january = temporal_local_date_of(year, 1, 1);
	zend_long first_january_day_of_week = temporal_local_date_day_of_week(first_january);
	temporal_local_date_free(first_january);

	bool has_53_weeks = first_january_day_of_week == 4 || (first_january_day_of_week == 3 && is_leap_year(year));
	return has_53_weeks ? 53 : 52;
}

static zend_long days_in_month(zend_long year, zend_long month) {
	switch (month) {
		case 2:
			return is_leap_year(year) ? 29 : 28;
		case 4:
		case 6:
		case 9:
		case 11:
			return 30;
		default:
			return 31;
	}
}

static zend_long max_days_in_month(zend_long month) {
	switch (month) {
		case 2:
			return 29;
		case 4:
		case 6:
		case 9:
		case 11:
			return 30;
		default:
			return 31;
	}
}

static zend_long first_day_of_year(zend_long year, zend_long month) {
	zend_long leap = is_leap_year(year) ? 1 : 0;
	switch (month) {
		case 1: return 1;
		case 2: return 32;
		case 3: return 60 + leap;
		case 4: return 91 + leap;
		case 5: return 121 + leap;
		case 6: return 152 + leap;
		case 7: return 182 + leap;
		case 8: return 213 + leap;
		case 9: return 244 + leap;
		case 10: return 274 + leap;
		case 11: return 305 + leap;
		default: return 335 + leap;
	}
}

#endif // TEMPORAL_UTILS_ISO_CALENDAR_H
