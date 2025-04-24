#include "formatter_ce.h"
#include <php.h>
#include <unicode/udat.h>
#include "exception/exception_obj.h"
#include "format_style/format_style.h"
#include "format_style/format_style_ce.h"
#include "formatter.h"
#include "formatter_arginfo.h"
#include "formatter_handlers.h"
#include "formatter_obj.h"
#include "local_date/local_date_ce.h"
#include "local_date/local_date_obj.h"
#include "local_date_time/local_date_time_ce.h"
#include "local_date_time/local_date_time_obj.h"
#include "local_time/local_time_ce.h"
#include "local_time/local_time_obj.h"
#include "zoned_date_time/zoned_date_time_ce.h"
#include "zoned_date_time/zoned_date_time_obj.h"

ZEND_METHOD(Temporal_Format_DateTimeFormatter, __construct) {
	// private
}

ZEND_METHOD(Temporal_Format_DateTimeFormatter, ofPattern) {
	zend_string *pattern, *locale = NULL;

	ZEND_PARSE_PARAMETERS_START(1, 2)
	Z_PARAM_STR(pattern)
	Z_PARAM_OPTIONAL
	Z_PARAM_STR(locale)
	ZEND_PARSE_PARAMETERS_END();

	UErrorCode status = U_ZERO_ERROR;
	UDateFormat *formatter = temporal_formatter_of_pattern(ZSTR_VAL(pattern), locale ? ZSTR_VAL(locale) : NULL, &status);
	if (U_FAILURE(status)) {
		php_temporal_throw_exception("Failed to create DateTimeFormatter.", 0);
		RETURN_THROWS();
	}

	zend_object *object = php_temporal_formatter_create_object_ex(formatter);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Format_DateTimeFormatter, ofLocalizedPattern) {
	zend_string *skeleton, *locale = NULL;

	ZEND_PARSE_PARAMETERS_START(1, 2)
	Z_PARAM_STR(skeleton)
	Z_PARAM_OPTIONAL
	Z_PARAM_STR(locale)
	ZEND_PARSE_PARAMETERS_END();

	UErrorCode status = U_ZERO_ERROR;
	UDateFormat *formatter = temporal_formatter_of_localized_pattern(ZSTR_VAL(skeleton), locale ? ZSTR_VAL(locale) : NULL, &status);
	if (U_FAILURE(status)) {
		php_temporal_throw_exception("Failed to create DateTimeFormatter.", 0);
		RETURN_THROWS();
	}

	zend_object *object = php_temporal_formatter_create_object_ex(formatter);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Format_DateTimeFormatter, ofDate) {
	zend_object *style;
	zend_string *locale = NULL;

	ZEND_PARSE_PARAMETERS_START(1, 2)
	Z_PARAM_OBJ_OF_CLASS(style, php_temporal_format_style_ce)
	Z_PARAM_OPTIONAL
	Z_PARAM_STR(locale)
	ZEND_PARSE_PARAMETERS_END();

	UDateFormat *formatter = temporal_formatter_of_date(icu_format_style_from_format_style(style), locale ? ZSTR_VAL(locale) : NULL);
	zend_object *object = php_temporal_formatter_create_object_ex(formatter);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Format_DateTimeFormatter, ofTime) {
	zend_object *style;
	zend_string *locale = NULL;

	ZEND_PARSE_PARAMETERS_START(1, 2)
	Z_PARAM_OBJ_OF_CLASS(style, php_temporal_format_style_ce)
	Z_PARAM_OPTIONAL
	Z_PARAM_STR(locale)
	ZEND_PARSE_PARAMETERS_END();

	UDateFormat *formatter = temporal_formatter_of_time(icu_format_style_from_format_style(style), locale ? ZSTR_VAL(locale) : NULL);
	zend_object *object = php_temporal_formatter_create_object_ex(formatter);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Format_DateTimeFormatter, ofDateTime) {
	zend_object *date_style, *time_style;
	zend_string *locale = NULL;

	ZEND_PARSE_PARAMETERS_START(2, 3)
	Z_PARAM_OBJ_OF_CLASS(date_style, php_temporal_format_style_ce)
	Z_PARAM_OBJ_OF_CLASS(time_style, php_temporal_format_style_ce)
	Z_PARAM_OPTIONAL
	Z_PARAM_STR(locale)
	ZEND_PARSE_PARAMETERS_END();

	UDateFormat *formatter = temporal_formatter_of_date_time(icu_format_style_from_format_style(date_style), icu_format_style_from_format_style(time_style), locale ? ZSTR_VAL(locale) : NULL);
	zend_object *object = php_temporal_formatter_create_object_ex(formatter);
	RETURN_OBJ(object);
}

ZEND_METHOD(Temporal_Format_DateTimeFormatter, formatLocalTime) {
	zval *local_time;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(local_time, php_temporal_local_time_ce)
	ZEND_PARSE_PARAMETERS_END();

	UDateFormat *formatter = THIS_TEMPORAL_FORMATTER_INTERNAL();

	zend_string *result = temporal_local_time_format(Z_TEMPORAL_LOCAL_TIME_INTERNAL_P(local_time), formatter);

	if (result == NULL) {
		RETURN_THROWS();
	}

	RETURN_STR(result);
}

ZEND_METHOD(Temporal_Format_DateTimeFormatter, formatLocalDate) {
	zval *local_date;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(local_date, php_temporal_local_date_ce)
	ZEND_PARSE_PARAMETERS_END();

	UDateFormat *formatter = THIS_TEMPORAL_FORMATTER_INTERNAL();

	zend_string *result = temporal_local_date_format(Z_TEMPORAL_LOCAL_DATE_INTERNAL_P(local_date), formatter);

	if (result == NULL) {
		RETURN_THROWS();
	}

	RETURN_STR(result);
}

ZEND_METHOD(Temporal_Format_DateTimeFormatter, formatLocalDateTime) {
	zval *local_date_time;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(local_date_time, php_temporal_local_date_time_ce)
	ZEND_PARSE_PARAMETERS_END();

	UDateFormat *formatter = THIS_TEMPORAL_FORMATTER_INTERNAL();

	zend_string *result = temporal_local_date_time_format(Z_TEMPORAL_LOCAL_DATE_TIME_INTERNAL_P(local_date_time), formatter);

	if (result == NULL) {
		RETURN_THROWS();
	}

	RETURN_STR(result);
}

ZEND_METHOD(Temporal_Format_DateTimeFormatter, formatZonedDateTime) {
	zval *zoned_date_time;

	ZEND_PARSE_PARAMETERS_START(1, 1)
	Z_PARAM_OBJECT_OF_CLASS(zoned_date_time, php_temporal_zoned_date_time_ce)
	ZEND_PARSE_PARAMETERS_END();

	UDateFormat *formatter = THIS_TEMPORAL_FORMATTER_INTERNAL();

	zend_string *result = temporal_zoned_date_time_format(Z_TEMPORAL_ZONED_DATE_TIME_INTERNAL_P(zoned_date_time), formatter);

	if (result == NULL) {
		RETURN_THROWS();
	}

	RETURN_STR(result);
}

zend_class_entry *php_temporal_formatter_ce;

void php_temporal_register_formatter_ce() {
	php_temporal_formatter_ce = register_class_Temporal_Format_DateTimeFormatter();
	php_temporal_formatter_ce->ce_flags |= ZEND_ACC_NOT_SERIALIZABLE;
	php_temporal_formatter_ce->create_object = php_temporal_formatter_create_object;

	php_temporal_register_formatter_handlers();
}
