#ifndef TEMPORAL_TIME_ZONE_OFFSET_H
#define TEMPORAL_TIME_ZONE_OFFSET_H

#include <php.h>

typedef struct _temporal_time_zone_offset_t {
	zend_long total_seconds;
} temporal_time_zone_offset_t;

#ifdef __cplusplus
extern "C" {
#endif

temporal_time_zone_offset_t *temporal_time_zone_offset_utc();
temporal_time_zone_offset_t *temporal_time_zone_offset_of(zend_long hours, zend_long minutes, zend_long seconds);
temporal_time_zone_offset_t *temporal_time_zone_offset_of_total_seconds(zend_long total_seconds);

temporal_time_zone_offset_t *temporal_time_zone_offset_clone(temporal_time_zone_offset_t *offset);

temporal_time_zone_offset_t *temporal_time_zone_offset_parse_iso(const char *id);
zend_string *temporal_time_zone_offset_id(temporal_time_zone_offset_t *offset);

void temporal_time_zone_offset_free(temporal_time_zone_offset_t *offset);

#ifdef __cplusplus
}
#endif

#endif // TEMPORAL_TIME_ZONE_OFFSET_H
