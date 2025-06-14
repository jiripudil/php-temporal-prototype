#ifndef TEMPORAL_MONTH_DAY_H
#define TEMPORAL_MONTH_DAY_H

#include <php.h>
#include "utils/parse_iso_result.h"

typedef struct _temporal_month_day_t {
	zend_long month;
	zend_long day;
} temporal_month_day_t;

#ifdef __cplusplus
extern "C" {
#endif

temporal_month_day_t *temporal_month_day_of(zend_long month, zend_long day);

int temporal_month_day_compare(temporal_month_day_t *a, temporal_month_day_t *b);
temporal_month_day_t *temporal_month_day_clone(temporal_month_day_t *month_day);

temporal_parse_iso_result_t *temporal_month_day_parse_iso(const char *input);
zend_string *temporal_month_day_format_iso(temporal_month_day_t *month_day);

void temporal_month_day_free(temporal_month_day_t *month_day);

#ifdef __cplusplus
}
#endif

#endif // TEMPORAL_MONTH_DAY_H
