#ifndef TEMPORAL_FORMATTER_H
#define TEMPORAL_FORMATTER_H

#include <php.h>
#include <unicode/udat.h>
#include "time_zone/time_zone.h"

#ifdef __cplusplus
extern "C" {
#endif

UDateFormat *temporal_formatter_of_pattern(const char *pattern, const char *locale, UErrorCode *status);
UDateFormat *temporal_formatter_of_localized_pattern(const char *skeleton, const char *locale, UErrorCode *status);
UDateFormat *temporal_formatter_of_date(UDateFormatStyle style, const char *locale);
UDateFormat *temporal_formatter_of_time(UDateFormatStyle style, const char *locale);
UDateFormat *temporal_formatter_of_date_time(UDateFormatStyle date_style, UDateFormatStyle time_style, const char *locale);

#define TEMPORAL_FORMATTER_FIELD_MASK_DATE (1 << 0)
#define TEMPORAL_FORMATTER_FIELD_MASK_TIME (1 << 1)
#define TEMPORAL_FORMATTER_FIELD_MASK_TIMEZONE (1 << 2)
bool temporal_formatter_is_valid_pattern(UDateFormat *fmt, int field_mask);

zend_string *temporal_formatter_format(UDateFormat *fmt, UDate timestamp, UTimeZone *tz);

void temporal_formatter_free(UDateFormat *fmt);

#ifdef __cplusplus
}
#endif

#endif // TEMPORAL_FORMATTER_H
