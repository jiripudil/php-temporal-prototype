#include "system_clock.h"
#include "instant/instant.h"

temporal_instant_t *temporal_clock_system_get_time() {
	struct timespec now;
	if (clock_gettime(CLOCK_REALTIME, &now) != 0) {
		return NULL;
	}

	temporal_instant_t *instant = temporal_instant_of(now.tv_sec, now.tv_nsec);
	return instant;
}
