#ifndef TEMPORAL_INSTANT_H
#define TEMPORAL_INSTANT_H

#include <php.h>
#include "../duration/duration.h"

typedef struct _temporal_instant_t {
	zend_long epoch_second;
	zend_long nano;
} temporal_instant_t;

#ifdef __cplusplus
extern "C" {
#endif

temporal_instant_t *temporal_instant_epoch();
temporal_instant_t *temporal_instant_of(zend_long epoch_second, zend_long nano_adjustment);

int temporal_instant_compare(temporal_instant_t *a, temporal_instant_t *b);
temporal_instant_t *temporal_instant_clone(temporal_instant_t *instant);
temporal_instant_t *temporal_instant_plus(temporal_instant_t *instant, temporal_duration_t *duration);
temporal_instant_t *temporal_instant_minus(temporal_instant_t *instant, temporal_duration_t *duration);

zend_string *temporal_instant_format_iso(const temporal_instant_t *instant);

void temporal_instant_free(temporal_instant_t *instant);

#ifdef __cplusplus
}
#endif

#endif // TEMPORAL_INSTANT_H
