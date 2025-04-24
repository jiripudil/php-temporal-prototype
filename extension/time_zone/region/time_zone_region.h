#ifndef TEMPORAL_TIME_ZONE_REGION_H
#define TEMPORAL_TIME_ZONE_REGION_H

#include <php.h>

typedef struct _temporal_time_zone_region_t {
	zend_string *id;
} temporal_time_zone_region_t;

#ifdef __cplusplus
extern "C" {
#endif

temporal_time_zone_region_t *temporal_time_zone_region_of(const char *id);
temporal_time_zone_region_t *temporal_time_zone_region_clone(temporal_time_zone_region_t *region);
void temporal_time_zone_region_free(temporal_time_zone_region_t *region);

#ifdef __cplusplus
}
#endif

#endif // TEMPORAL_TIME_ZONE_REGION_H
