#ifndef TEMPORAL_YEAR_MONTH_H
#define TEMPORAL_YEAR_MONTH_H

#include <php.h>
#include "utils/parse_iso_result.h"

typedef struct _temporal_year_month_t {
	zend_long year;
	zend_long month;
} temporal_year_month_t;

#ifdef __cplusplus
extern "C" {
#endif

temporal_year_month_t *temporal_year_month_of(zend_long year, zend_long month);

int temporal_year_month_compare(temporal_year_month_t *a, temporal_year_month_t *b);
temporal_year_month_t *temporal_year_month_plus_months(temporal_year_month_t *year_month, zend_long months);
temporal_year_month_t *temporal_year_month_clone(temporal_year_month_t *year_month);

temporal_parse_iso_result_t *temporal_year_month_parse_iso(const char *input);
zend_string *temporal_year_month_format_iso(temporal_year_month_t *year_month);

void temporal_year_month_free(temporal_year_month_t *year_month);

#ifdef __cplusplus
}
#endif

#endif // TEMPORAL_YEAR_MONTH_H
