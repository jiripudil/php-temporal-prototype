#ifndef TEMPORAL_YEAR_WEEK_H
#define TEMPORAL_YEAR_WEEK_H

#include <php.h>
#include "local_date/local_date.h"

typedef struct _temporal_year_week_t {
	zend_long year;
	zend_long week;
} temporal_year_week_t;

#ifdef __cplusplus
extern "C" {
#endif

temporal_year_week_t *temporal_year_week_of(zend_long year, zend_long week);
temporal_year_week_t *temporal_year_week_of_date(temporal_local_date_t *local_date);

int temporal_year_week_compare(temporal_year_week_t *a, temporal_year_week_t *b);
temporal_year_week_t *temporal_year_week_plus_weeks(temporal_year_week_t *year_week, zend_long weeks);
temporal_year_week_t *temporal_year_week_clone(temporal_year_week_t *year_week);

temporal_local_date_t *temporal_year_week_at_day(temporal_year_week_t *year_week, zend_long day_of_week);

temporal_year_week_t *temporal_year_week_parse_iso(const char *input);
zend_string *temporal_year_week_format_iso(temporal_year_week_t *year_week);

void temporal_year_week_free(temporal_year_week_t *year_week);

#ifdef __cplusplus
}
#endif

#endif // TEMPORAL_YEAR_WEEK_H
