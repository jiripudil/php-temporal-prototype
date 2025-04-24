#include "format_style.h"
#include <php.h>
#include <zend_enum.h>
#include <zend_string.h>
#include <unicode/udat.h>

UDateFormatStyle icu_format_style_from_format_style(zend_object *format_style) {
	zval *case_name = zend_enum_fetch_case_name(format_style);
	zend_string *style_name = Z_STR_P(case_name);

	switch (ZSTR_VAL(style_name)[0]) {
		case 'F': return UDAT_FULL;
		case 'L': return UDAT_LONG;
		case 'M': return UDAT_MEDIUM;
		case 'S': return UDAT_SHORT;
		EMPTY_SWITCH_DEFAULT_CASE();
	}
}
