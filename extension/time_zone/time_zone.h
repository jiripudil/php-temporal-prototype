#ifndef TEMPORAL_TIME_ZONE_H
#define TEMPORAL_TIME_ZONE_H

#include <php.h>
#include "instant/instant.h"
#include "local_date_time/local_date_time.h"
#include "time_zone/offset/time_zone_offset.h"
#include "time_zone/region/time_zone_region.h"
#include "utils/parse_iso_result.h"

#define TEMPORAL_TIME_ZONE_TYPE_OFFSET 1
#define IS_TEMPORAL_TIME_ZONE_OFFSET(tz) (tz->type == TEMPORAL_TIME_ZONE_TYPE_OFFSET)

#define TEMPORAL_TIME_ZONE_TYPE_REGION 2
#define IS_TEMPORAL_TIME_ZONE_REGION(tz) (tz->type == TEMPORAL_TIME_ZONE_TYPE_REGION)

typedef void* UTimeZone; // opaque type for icu4c's C++ TimeZone class

typedef struct _temporal_time_zone_t {
	int type;
	UTimeZone *time_zone;
	union {
		temporal_time_zone_offset_t *offset;
		temporal_time_zone_region_t *region;
	};
} temporal_time_zone_t;

#ifdef __cplusplus
extern "C" {
#endif

temporal_time_zone_t *temporal_time_zone_of_offset(temporal_time_zone_offset_t *offset);
temporal_time_zone_t *temporal_time_zone_of_region(temporal_time_zone_region_t *region);

temporal_time_zone_t *temporal_time_zone_clone(temporal_time_zone_t *time_zone);

temporal_parse_iso_result_t *temporal_time_zone_parse_iso(const char *input);
zend_string *temporal_time_zone_get_id(temporal_time_zone_t *tz);
zend_long temporal_time_zone_get_offset(temporal_time_zone_t *tz, temporal_instant_t *instant);

temporal_local_date_time_t *temporal_time_zone_instant_to_local_date_time(temporal_time_zone_t *tz, temporal_instant_t *instant);
temporal_instant_t *temporal_time_zone_local_date_time_to_instant(temporal_time_zone_t *tz, temporal_local_date_time_t *local_date_time);

void temporal_time_zone_free(temporal_time_zone_t *tz);

#ifdef __cplusplus
}
#endif

#endif // TEMPORAL_TIME_ZONE_H
