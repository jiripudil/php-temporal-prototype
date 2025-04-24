#include "instant.h"
#include <php.h>
#include "duration/duration.h"
#include "time_zone/offset/time_zone_offset.h"
#include "time_zone/time_zone.h"
#include "utils/compare.h"
#include "zoned_date_time/zoned_date_time.h"

temporal_instant_t *temporal_instant_epoch() {
	return temporal_instant_of(0, 0);
}

temporal_instant_t *temporal_instant_of(zend_long epoch_second, zend_long nano_adjustment) {
	temporal_instant_t *instant = ecalloc(1, sizeof(temporal_instant_t));

	zend_long nanos = nano_adjustment % NANOS_PER_SECOND;
	epoch_second += (nano_adjustment - nanos) / NANOS_PER_SECOND;

	if (nanos < 0) {
		nanos += NANOS_PER_SECOND;
		epoch_second--;
	}

	instant->epoch_second = epoch_second;
	instant->nano = nanos;
	return instant;
}

int temporal_instant_compare(temporal_instant_t *a, temporal_instant_t *b) {
	TEMPORAL_COMPARE_FUNCTION(epoch_second, a->epoch_second, b->epoch_second)
	TEMPORAL_COMPARE_FUNCTION(nano, a->nano, b->nano)
	return 0;
}

temporal_instant_t *temporal_instant_clone(temporal_instant_t *instant) {
	return temporal_instant_of(instant->epoch_second, instant->nano);
}

temporal_instant_t *temporal_instant_plus(temporal_instant_t *instant, temporal_duration_t *duration) {
	return temporal_instant_of(
		instant->epoch_second + duration->seconds,
		instant->nano + duration->nanos
	);
}

temporal_instant_t *temporal_instant_minus(temporal_instant_t *instant, temporal_duration_t *duration) {
	return temporal_instant_of(
		instant->epoch_second - duration->seconds,
		instant->nano - duration->nanos
	);
}

zend_string *temporal_instant_format_iso(const temporal_instant_t *instant) {
	temporal_time_zone_t *utc = temporal_time_zone_of_offset(temporal_time_zone_offset_utc());
	temporal_local_date_time_t *utc_date_time = temporal_time_zone_instant_to_local_date_time(utc, (temporal_instant_t *) instant);
	temporal_zoned_date_time_t *zoned_date_time = temporal_zoned_date_time_of(utc_date_time, utc);

	zend_string *result = temporal_zoned_date_time_format_iso(zoned_date_time);

	temporal_local_date_time_free(utc_date_time);
	temporal_zoned_date_time_free(zoned_date_time);

	return result;
}

void temporal_instant_free(temporal_instant_t *instant) {
	efree(instant);
}
