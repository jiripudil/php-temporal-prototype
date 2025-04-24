#ifndef TEMPORAL_PERIOD_H
#define TEMPORAL_PERIOD_H

#include <php.h>
#include "local_date/local_date.h"

typedef struct _temporal_period_t {
	zend_long years;
	zend_long months;
	zend_long days;
} temporal_period_t;

#ifdef __cplusplus
extern "C" {
#endif

temporal_period_t *temporal_period_zero();
temporal_period_t *temporal_period_of(zend_long years, zend_long months, zend_long days);
temporal_period_t *temporal_period_between(temporal_local_date_t *start, temporal_local_date_t *end_exclusive);
temporal_period_t *temporal_period_clone(const temporal_period_t *period);
temporal_period_t *temporal_period_negated(const temporal_period_t *period);

temporal_period_t *temporal_period_plus(const temporal_period_t *a, const temporal_period_t *b);
temporal_period_t *temporal_period_minus(const temporal_period_t *a, const temporal_period_t *b);

temporal_period_t *temporal_period_parse_iso(const char *input);
zend_string *temporal_period_format_iso(const temporal_period_t *period);

void temporal_period_free(temporal_period_t *period);

#ifdef __cplusplus
}
#endif

#endif // TEMPORAL_PERIOD_H
