#ifndef TEMPORAL_UTILS_UCHAR_FROM_ZEND_STRING_H
#define TEMPORAL_UTILS_UCHAR_FROM_ZEND_STRING_H

#include <php.h>
#include <unicode/uchar.h>
#include <unicode/ustring.h>

static void uchar_from_zend_string(zend_string *value, UChar *result, int *result_length, UErrorCode *status) {
	int length_needed;
	u_strFromUTF8(NULL, 0, &length_needed, ZSTR_VAL(value), ZSTR_LEN(value), status);

	if (*status == U_BUFFER_OVERFLOW_ERROR) {
		*status = U_ZERO_ERROR;
		result = (UChar *)emalloc(sizeof(UChar) * length_needed);
		u_strFromUTF8(result, length_needed, NULL, ZSTR_VAL(value), ZSTR_LEN(value), status);
	}

	if (U_FAILURE(*status)) {
		efree(result);
	}
}

#endif // TEMPORAL_UTILS_UCHAR_FROM_ZEND_STRING_H
