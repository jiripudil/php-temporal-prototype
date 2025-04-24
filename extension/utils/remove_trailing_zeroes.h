#ifndef TEMPORAL_UTILS_REMOVE_TRAILING_ZEROES_H
#define TEMPORAL_UTILS_REMOVE_TRAILING_ZEROES_H

#include <string.h>

static void remove_trailing_zeroes(char *str) {
	int len = strlen(str);

	while (len > 0 && str[len - 1] == '0') {
		len--;
	}

	str[len] = '\0';
}

#endif // TEMPORAL_UTILS_REMOVE_TRAILING_ZEROES_H
