#include "format_style_ce.h"
#include <php.h>
#include <zend_enum.h>
#include "format_style_arginfo.h"

zend_class_entry *php_temporal_format_style_ce;

void php_temporal_register_format_style_ce() {
	php_temporal_format_style_ce = register_class_Temporal_Format_FormatStyle();
}
