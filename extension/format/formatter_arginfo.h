/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 4cf283c93f9ac0f2965b16aceff053d381b149fa */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Temporal_Format_DateTimeFormatter___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Format_DateTimeFormatter_ofPattern, 0, 1, Temporal\\Format\\DateTimeFormatter, 0)
	ZEND_ARG_TYPE_INFO(0, pattern, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, locale, IS_STRING, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Format_DateTimeFormatter_ofLocalizedPattern, 0, 1, Temporal\\Format\\DateTimeFormatter, 0)
	ZEND_ARG_TYPE_INFO(0, localizedPattern, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, locale, IS_STRING, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Format_DateTimeFormatter_ofDate, 0, 1, Temporal\\Format\\DateTimeFormatter, 0)
	ZEND_ARG_OBJ_INFO(0, style, Temporal\\Format\\FormatStyle, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, locale, IS_STRING, 1, "null")
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_Format_DateTimeFormatter_ofTime arginfo_class_Temporal_Format_DateTimeFormatter_ofDate

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Format_DateTimeFormatter_ofDateTime, 0, 2, Temporal\\Format\\DateTimeFormatter, 0)
	ZEND_ARG_OBJ_INFO(0, dateStyle, Temporal\\Format\\FormatStyle, 0)
	ZEND_ARG_OBJ_INFO(0, timeStyle, Temporal\\Format\\FormatStyle, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, locale, IS_STRING, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_Format_DateTimeFormatter_formatLocalTime, 0, 1, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO(0, value, Temporal\\LocalTime, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_Format_DateTimeFormatter_formatLocalDate, 0, 1, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO(0, value, Temporal\\LocalDate, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_Format_DateTimeFormatter_formatLocalDateTime, 0, 1, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO(0, value, Temporal\\LocalDateTime, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_Format_DateTimeFormatter_formatZonedDateTime, 0, 1, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO(0, value, Temporal\\ZonedDateTime, 0)
ZEND_END_ARG_INFO()

ZEND_METHOD(Temporal_Format_DateTimeFormatter, __construct);
ZEND_METHOD(Temporal_Format_DateTimeFormatter, ofPattern);
ZEND_METHOD(Temporal_Format_DateTimeFormatter, ofLocalizedPattern);
ZEND_METHOD(Temporal_Format_DateTimeFormatter, ofDate);
ZEND_METHOD(Temporal_Format_DateTimeFormatter, ofTime);
ZEND_METHOD(Temporal_Format_DateTimeFormatter, ofDateTime);
ZEND_METHOD(Temporal_Format_DateTimeFormatter, formatLocalTime);
ZEND_METHOD(Temporal_Format_DateTimeFormatter, formatLocalDate);
ZEND_METHOD(Temporal_Format_DateTimeFormatter, formatLocalDateTime);
ZEND_METHOD(Temporal_Format_DateTimeFormatter, formatZonedDateTime);

static const zend_function_entry class_Temporal_Format_DateTimeFormatter_methods[] = {
	ZEND_ME(Temporal_Format_DateTimeFormatter, __construct, arginfo_class_Temporal_Format_DateTimeFormatter___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(Temporal_Format_DateTimeFormatter, ofPattern, arginfo_class_Temporal_Format_DateTimeFormatter_ofPattern, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_Format_DateTimeFormatter, ofLocalizedPattern, arginfo_class_Temporal_Format_DateTimeFormatter_ofLocalizedPattern, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_Format_DateTimeFormatter, ofDate, arginfo_class_Temporal_Format_DateTimeFormatter_ofDate, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_Format_DateTimeFormatter, ofTime, arginfo_class_Temporal_Format_DateTimeFormatter_ofTime, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_Format_DateTimeFormatter, ofDateTime, arginfo_class_Temporal_Format_DateTimeFormatter_ofDateTime, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_Format_DateTimeFormatter, formatLocalTime, arginfo_class_Temporal_Format_DateTimeFormatter_formatLocalTime, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Format_DateTimeFormatter, formatLocalDate, arginfo_class_Temporal_Format_DateTimeFormatter_formatLocalDate, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Format_DateTimeFormatter, formatLocalDateTime, arginfo_class_Temporal_Format_DateTimeFormatter_formatLocalDateTime, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Format_DateTimeFormatter, formatZonedDateTime, arginfo_class_Temporal_Format_DateTimeFormatter_formatZonedDateTime, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_Temporal_Format_DateTimeFormatter(void)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Temporal\\Format", "DateTimeFormatter", class_Temporal_Format_DateTimeFormatter_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	return class_entry;
}
