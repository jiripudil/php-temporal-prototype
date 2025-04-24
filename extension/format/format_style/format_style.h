#ifndef TEMPORAL_FORMAT_STYLE_H
#define TEMPORAL_FORMAT_STYLE_H

#include <php.h>
#include <unicode/udat.h>

UDateFormatStyle icu_format_style_from_format_style(zend_object *format_style);

#endif // TEMPORAL_FORMAT_STYLE_H
