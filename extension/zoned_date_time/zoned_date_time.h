#ifndef TEMPORAL_ZONED_DATE_TIME_H
#define TEMPORAL_ZONED_DATE_TIME_H

#include <php.h>
#include <unicode/udat.h>
#include "instant/instant.h"
#include "local_date_time/local_date_time.h"
#include "time_zone/offset/time_zone_offset.h"
#include "time_zone/time_zone.h"
#include "utils/parse_iso_result.h"

typedef struct _temporal_zoned_date_time_t {
	temporal_local_date_time_t *date_time;
	temporal_instant_t *instant;
	temporal_time_zone_offset_t *zone_offset;
	temporal_time_zone_t *zone;
} temporal_zoned_date_time_t;

#ifdef __cplusplus
extern "C" {
#endif

temporal_zoned_date_time_t *temporal_zoned_date_time_of(temporal_local_date_time_t *date_time, temporal_time_zone_t *zone);
temporal_zoned_date_time_t *temporal_zoned_date_time_of_instant(temporal_instant_t *instant, temporal_time_zone_t *zone);
temporal_zoned_date_time_t *temporal_zoned_date_time_now(temporal_time_zone_t *zone, zend_object *clock);

int temporal_zoned_date_time_compare(temporal_zoned_date_time_t *a, temporal_zoned_date_time_t *b);
temporal_zoned_date_time_t *temporal_zoned_date_time_clone(temporal_zoned_date_time_t *zoned_date_time);

temporal_parse_iso_result_t *temporal_zoned_date_time_parse_iso(const char *input);
zend_string *temporal_zoned_date_time_format_iso(temporal_zoned_date_time_t *date_time);
zend_string *temporal_zoned_date_time_format(temporal_zoned_date_time_t *date_time, UDateFormat *fmt);

void temporal_zoned_date_time_free(temporal_zoned_date_time_t *zoned_date_time);

#ifdef __cplusplus
}
#endif

#endif // TEMPORAL_ZONED_DATE_TIME_H
