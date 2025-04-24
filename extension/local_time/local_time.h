#ifndef TEMPORAL_LOCAL_TIME_H
#define TEMPORAL_LOCAL_TIME_H

#include <php.h>
#include <unicode/udat.h>
#include "duration/duration.h"

typedef struct _temporal_local_time_t {
	zend_long hour;
	zend_long minute;
	zend_long second;
	zend_long nano;
} temporal_local_time_t;

#ifdef __cplusplus
extern "C" {
#endif

temporal_local_time_t *temporal_local_time_midnight();
temporal_local_time_t *temporal_local_time_of(zend_long hour, zend_long minute, zend_long second, zend_long nano);
temporal_local_time_t *temporal_local_time_of_seconds_of_day(zend_long total_seconds, zend_long nano);

zend_long temporal_local_time_seconds_of_day(temporal_local_time_t *local_time);
int temporal_local_time_compare(temporal_local_time_t *a, temporal_local_time_t *b);
temporal_local_time_t *temporal_local_time_clone(temporal_local_time_t *local_time);
temporal_local_time_t *temporal_local_time_plus(temporal_local_time_t *local_time, temporal_duration_t *duration);
temporal_local_time_t *temporal_local_time_minus(temporal_local_time_t *local_time, temporal_duration_t *duration);

temporal_local_time_t *temporal_local_time_parse_iso(const char *input);
zend_string *temporal_local_time_format_iso(temporal_local_time_t *local_time);
zend_string *temporal_local_time_format(temporal_local_time_t *local_time, UDateFormat *fmt);

void temporal_local_time_free(temporal_local_time_t *local_time);

#ifdef __cplusplus
}
#endif

#endif // TEMPORAL_LOCAL_TIME_H
