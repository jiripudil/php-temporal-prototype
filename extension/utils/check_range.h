#ifndef TEMPORAL_UTILS_CHECK_VALUE_RANGE_H
#define TEMPORAL_UTILS_CHECK_VALUE_RANGE_H

#define TEMPORAL_CHECK_VALUE_RANGE(name, value, min, max)                                                              \
	if (value < min || value > max) {                                                                                  \
		php_temporal_throw_value_out_of_range(name, value, min, max);                                                  \
		RETURN_THROWS();                                                                                               \
	}

#endif // TEMPORAL_UTILS_CHECK_VALUE_RANGE_H
