#ifndef TEMPORAL_UTILS_COMPARE_H
#define TEMPORAL_UTILS_COMPARE_H

#define TEMPORAL_COMPARE_FUNCTION(NAME, a, b) \
	zend_long cmp_##NAME = a - b; \
	if (cmp_##NAME > 0) return 1; \
	if (cmp_##NAME < 0) return -1;

#endif // TEMPORAL_UTILS_COMPARE_H
