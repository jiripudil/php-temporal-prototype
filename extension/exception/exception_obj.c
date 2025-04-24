#include "exception_obj.h"
#include <zend_exceptions.h>
#include <zend_smart_str.h>
#include "exception_ce.h"

void php_temporal_throw_exception(const char *message, zend_long code) {
	zend_throw_exception(php_temporal_exception_ce, message, code);
}

void php_temporal_throw_value_out_of_range(const char *name, zend_long value, zend_long min, zend_long max) {
	smart_str buf = {0};
	smart_str_appends(&buf, "Value ");
	smart_str_append_long(&buf, value);
	smart_str_appends(&buf, " is out of range for ");
	smart_str_appends(&buf, name);
	smart_str_appends(&buf, ": ");
	smart_str_append_long(&buf, min);
	smart_str_appends(&buf, "..");
	smart_str_append_long(&buf, max);

	zend_string *message = smart_str_extract(&buf);
	php_temporal_throw_exception(ZSTR_VAL(message), 0);
	zend_string_release_ex(message, false);
}
