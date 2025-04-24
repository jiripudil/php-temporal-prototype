#include "time_zone_region.h"
#include <php.h>

temporal_time_zone_region_t *temporal_time_zone_region_of(const char *id) {
	temporal_time_zone_region_t *region = ecalloc(1, sizeof(temporal_time_zone_region_t));
	region->id = zend_string_init(id, strlen(id), 0);
	return region;
}

temporal_time_zone_region_t *temporal_time_zone_region_clone(temporal_time_zone_region_t *region) {
	return temporal_time_zone_region_of(zend_string_copy(region->id)->val);
}

void temporal_time_zone_region_free(temporal_time_zone_region_t *region) {
	zend_string_release(region->id);
	efree(region);
}
