#ifndef TEMPORAL_UTILS_UNICODE_STRING_H
#define TEMPORAL_UTILS_UNICODE_STRING_H

#include <php.h>
#include <unicode/unistr.h>
#include <unicode/ustring.h>

using icu::UnicodeString;

int u_stringFromChar(UnicodeString &ret, const char *str, size_t str_len, UErrorCode *status);
zend_string *u_charFromString(const UnicodeString &from, UErrorCode *status);

#endif // TEMPORAL_UTILS_UNICODE_STRING_H
