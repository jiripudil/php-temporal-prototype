#ifndef TEMPORAL_LOCAL_DATE_H
#define TEMPORAL_LOCAL_DATE_H

#include <php.h>
#include <unicode/udat.h>
#include "utils/parse_iso_result.h"

#define DAYS_PER_CYCLE 146097
#define DAYS_0000_TO_1970 ((DAYS_PER_CYCLE * 5) - (30 * 365 + 7))

typedef struct _temporal_local_date_t {
	zend_long year;
	zend_long month;
	zend_long day;
} temporal_local_date_t;

#ifdef __cplusplus
extern "C" {
#endif

temporal_local_date_t *temporal_local_date_of(zend_long year, zend_long month, zend_long day);
temporal_local_date_t *temporal_local_date_of_day_of_year(zend_long year, zend_long day_of_year);
temporal_local_date_t *temporal_local_date_of_epoch_day(zend_long epoch_day);

zend_long temporal_local_date_to_epoch_day(temporal_local_date_t *local_date);
zend_long temporal_local_date_day_of_year(temporal_local_date_t *local_date);
zend_long temporal_local_date_day_of_week(temporal_local_date_t *local_date);

int temporal_local_date_compare(temporal_local_date_t *a, temporal_local_date_t *b);
temporal_local_date_t *temporal_local_date_clone(temporal_local_date_t *local_date);
temporal_local_date_t *temporal_local_date_plus_years(temporal_local_date_t *local_date, zend_long years);
temporal_local_date_t *temporal_local_date_plus_months(temporal_local_date_t *local_date, zend_long months);
temporal_local_date_t *temporal_local_date_plus_days(temporal_local_date_t *local_date, zend_long days);

temporal_parse_iso_result_t *temporal_local_date_parse_iso(const char *input);
zend_string *temporal_local_date_format_iso(temporal_local_date_t *local_date);
zend_string *temporal_local_date_format(temporal_local_date_t *local_date, UDateFormat *fmt);

void temporal_local_date_free(temporal_local_date_t *local_date);

#ifdef __cplusplus
}
#endif

#endif // TEMPORAL_LOCAL_DATE_H
