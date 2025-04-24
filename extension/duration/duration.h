#ifndef TEMPORAL_DURATION_H
#define TEMPORAL_DURATION_H

#include <php.h>

static const zend_long NANOS_PER_SECOND = 1000000000;
static const zend_long SECONDS_PER_MINUTE = 60;
static const zend_long SECONDS_PER_HOUR = 3600;
static const zend_long SECONDS_PER_DAY = 86400;
static const zend_long MINUTES_PER_HOUR = 60;
static const zend_long HOURS_PER_DAY = 24;

typedef struct _temporal_duration_t {
	zend_long seconds;
	zend_long nanos;
} temporal_duration_t;

#ifdef __cplusplus
extern "C" {
#endif

temporal_duration_t *temporal_duration_zero();
temporal_duration_t *temporal_duration_of(zend_long seconds, zend_long nano_adjustment);
temporal_duration_t *temporal_duration_clone(const temporal_duration_t *duration);
temporal_duration_t *temporal_duration_negated(const temporal_duration_t *duration);

int temporal_duration_compare(const temporal_duration_t *a, const temporal_duration_t *b);
temporal_duration_t *temporal_duration_plus(const temporal_duration_t *a, const temporal_duration_t *b);
temporal_duration_t *temporal_duration_minus(const temporal_duration_t *a, const temporal_duration_t *b);

temporal_duration_t *temporal_duration_parse_iso(const char *input);
zend_string *temporal_duration_format_iso(const temporal_duration_t *duration);

void temporal_duration_free(temporal_duration_t *duration);

#ifdef __cplusplus
}
#endif

#endif // TEMPORAL_DURATION_H
