#include "exception_obj.h"
#include <zend_exceptions.h>
#include <zend_smart_str.h>
#include "exception_ce.h"

void php_temporal_throw_exception(const char *message, zend_long code) {
	zend_throw_exception(php_temporal_exception_ce, message, code);
}

void php_temporal_throw_date_time_conversion(const char *type) {
	smart_str buf = {0};
	smart_str_appends(&buf, "Failed to convert a ");
	smart_str_appends(&buf, type);
	smart_str_appends(&buf, " to DateTime");

	zend_string *message = smart_str_extract(&buf);
	zend_throw_exception(php_temporal_exception_date_time_conversion_ce, ZSTR_VAL(message), 0);
	zend_string_release_ex(message, false);
}

void php_temporal_throw_formatting_failed_to_generate_pattern(const char *skeleton, const char *locale) {
	smart_str buf = {0};
	smart_str_appends(&buf, "Failed to generate pattern from \"");
	smart_str_appends(&buf, skeleton);
	smart_str_appends(&buf, "\" for ");

	if (locale == NULL) {
		smart_str_appends(&buf, "default locale");
	} else {
		smart_str_appends(&buf, "locale \"");
		smart_str_appends(&buf, locale);
		smart_str_appendc(&buf, '"');
	}

	zend_string *message = smart_str_extract(&buf);
	zend_throw_exception(php_temporal_exception_formatting_ce, ZSTR_VAL(message), 0);
	zend_string_release_ex(message, false);
}

void php_temporal_throw_formatting_invalid_pattern(const char *type) {
	smart_str buf = {0};
	smart_str_appends(&buf, "Failed to format a ");
	smart_str_appends(&buf, type);
	smart_str_appends(&buf, ": the formatting pattern is not valid for given value");

	zend_string *message = smart_str_extract(&buf);
	zend_throw_exception(php_temporal_exception_formatting_ce, ZSTR_VAL(message), 0);
	zend_string_release_ex(message, false);
}

void php_temporal_throw_formatting_failed_to_format_value(const char *type, const char *error_message) {
	smart_str buf = {0};
	smart_str_appends(&buf, "Failed to format a ");
	smart_str_appends(&buf, type);
	smart_str_appends(&buf, ": ");
	smart_str_appends(&buf, error_message);

	zend_string *message = smart_str_extract(&buf);
	zend_throw_exception(php_temporal_exception_formatting_ce, ZSTR_VAL(message), 0);
	zend_string_release_ex(message, false);
}

void php_temporal_throw_parsing_invalid_iso_string(const char *input) {
	smart_str buf = {0};
	smart_str_appends(&buf, "Failed to parse input \"");
	smart_str_appends(&buf, input);
	smart_str_appends(&buf, "\": invalid ISO 8601 string");

	zend_string *message = smart_str_extract(&buf);
	zend_throw_exception(php_temporal_exception_parsing_ce, ZSTR_VAL(message), 0);
	zend_string_release_ex(message, false);
}

void php_temporal_throw_parsing_value_out_of_range(const char *input, const char *name, zend_long value, zend_long min, zend_long max) {
	php_temporal_throw_value_out_of_range(name, value, min, max);
	zend_exception_save();

	smart_str buf = {0};
	smart_str_appends(&buf, "Failed to parse input \"");
	smart_str_appends(&buf, input);
	smart_str_appends(&buf, "\": Value ");
	smart_str_append_long(&buf, value);
	smart_str_appends(&buf, " is out of range for $");
	smart_str_appends(&buf, name);
	smart_str_appends(&buf, ": ");
	smart_str_append_long(&buf, min);
	smart_str_appends(&buf, "..");
	smart_str_append_long(&buf, max);

	zend_string *message = smart_str_extract(&buf);
	zend_throw_exception(php_temporal_exception_parsing_ce, ZSTR_VAL(message), 0);
	zend_string_release_ex(message, false);

	zend_exception_restore();
}

void php_temporal_throw_parsing_unknown_time_zone(const char *input, const char *id) {
	php_temporal_throw_unknown_time_zone(id);
	zend_exception_save();

	smart_str buf = {0};
	smart_str_appends(&buf, "Failed to parse input \"");
	smart_str_appends(&buf, input);
	smart_str_appends(&buf, "\": Unrecognized time zone identifier \"");
	smart_str_appends(&buf, id);
	smart_str_appendc(&buf, '"');

	zend_string *message = smart_str_extract(&buf);
	zend_throw_exception(php_temporal_exception_parsing_ce, ZSTR_VAL(message), 0);
	zend_string_release_ex(message, false);

	zend_exception_restore();
}

void php_temporal_throw_parsing(const char *input, const char *error_message) {
	smart_str buf = {0};
	smart_str_appends(&buf, "Failed to parse input \"");
	smart_str_appends(&buf, input);
	smart_str_appends(&buf, "\": ");
	smart_str_appends(&buf, error_message);

	zend_string *message = smart_str_extract(&buf);
	zend_throw_exception(php_temporal_exception_parsing_ce, ZSTR_VAL(message), 0);
	zend_string_release_ex(message, false);
}

void php_temporal_throw_unknown_time_zone(const char *id) {
	smart_str buf = {0};
	smart_str_appends(&buf, "Unrecognized time zone identifier \"");
	smart_str_appends(&buf, id);
	smart_str_appendc(&buf, '"');

	zend_string *message = smart_str_extract(&buf);
	zend_throw_exception(php_temporal_exception_unknown_time_zone_ce, ZSTR_VAL(message), 0);
	zend_string_release_ex(message, false);
}

void php_temporal_throw_value_out_of_range(const char *name, zend_long value, zend_long min, zend_long max) {
	smart_str buf = {0};
	smart_str_appends(&buf, "Value ");
	smart_str_append_long(&buf, value);
	smart_str_appends(&buf, " is out of range for $");
	smart_str_appends(&buf, name);
	smart_str_appends(&buf, ": ");
	smart_str_append_long(&buf, min);
	smart_str_appends(&buf, "..");
	smart_str_append_long(&buf, max);

	zend_string *message = smart_str_extract(&buf);
	zend_throw_exception(php_temporal_exception_value_out_of_range_ce, ZSTR_VAL(message), 0);
	zend_string_release_ex(message, false);
}
