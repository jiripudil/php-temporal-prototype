/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 30f99efbf733a3d718789dfbaa7b115208482a2d */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Temporal_LocalTime___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalTime_of, 0, 2, Temporal\\LocalTime, 0)
	ZEND_ARG_TYPE_INFO(0, hour, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, minute, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, second, IS_LONG, 0, "0")
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, nano, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalTime_ofSecondOfDay, 0, 1, Temporal\\LocalTime, 0)
	ZEND_ARG_TYPE_INFO(0, secondOfDay, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, nano, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalTime_now, 0, 1, Temporal\\LocalTime, 0)
	ZEND_ARG_OBJ_INFO(0, timeZone, Temporal\\TimeZone, 0)
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, clock, Temporal\\Clock, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalTime_fromISOString, 0, 1, Temporal\\LocalTime, 0)
	ZEND_ARG_TYPE_INFO(0, text, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalTime_midnight, 0, 0, Temporal\\LocalTime, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_LocalTime_noon arginfo_class_Temporal_LocalTime_midnight

#define arginfo_class_Temporal_LocalTime_min arginfo_class_Temporal_LocalTime_midnight

#define arginfo_class_Temporal_LocalTime_max arginfo_class_Temporal_LocalTime_midnight

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_LocalTime_getHour, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalTime_withHour, 0, 1, Temporal\\LocalTime, 0)
	ZEND_ARG_TYPE_INFO(0, hour, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_LocalTime_getMinute arginfo_class_Temporal_LocalTime_getHour

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalTime_withMinute, 0, 1, Temporal\\LocalTime, 0)
	ZEND_ARG_TYPE_INFO(0, minute, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_LocalTime_getSecond arginfo_class_Temporal_LocalTime_getHour

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalTime_withSecond, 0, 1, Temporal\\LocalTime, 0)
	ZEND_ARG_TYPE_INFO(0, second, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_LocalTime_getNano arginfo_class_Temporal_LocalTime_getHour

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalTime_withNano, 0, 1, Temporal\\LocalTime, 0)
	ZEND_ARG_TYPE_INFO(0, nano, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_LocalTime_getSecondOfDay arginfo_class_Temporal_LocalTime_getHour

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalTime_plus, 0, 1, Temporal\\LocalTime, 0)
	ZEND_ARG_OBJ_INFO(0, duration, Temporal\\Duration, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalTime_plusHours, 0, 1, Temporal\\LocalTime, 0)
	ZEND_ARG_TYPE_INFO(0, hours, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalTime_plusMinutes, 0, 1, Temporal\\LocalTime, 0)
	ZEND_ARG_TYPE_INFO(0, minutes, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalTime_plusSeconds, 0, 1, Temporal\\LocalTime, 0)
	ZEND_ARG_TYPE_INFO(0, seconds, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalTime_plusNanos, 0, 1, Temporal\\LocalTime, 0)
	ZEND_ARG_TYPE_INFO(0, nanos, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_LocalTime_minus arginfo_class_Temporal_LocalTime_plus

#define arginfo_class_Temporal_LocalTime_minusHours arginfo_class_Temporal_LocalTime_plusHours

#define arginfo_class_Temporal_LocalTime_minusMinutes arginfo_class_Temporal_LocalTime_plusMinutes

#define arginfo_class_Temporal_LocalTime_minusSeconds arginfo_class_Temporal_LocalTime_plusSeconds

#define arginfo_class_Temporal_LocalTime_minusNanos arginfo_class_Temporal_LocalTime_plusNanos

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalTime_atDate, 0, 1, Temporal\\LocalDateTime, 0)
	ZEND_ARG_OBJ_INFO(0, date, Temporal\\LocalDate, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_LocalTime_compareTo, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, other, Temporal\\LocalTime, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_LocalTime_isEqualTo, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, other, Temporal\\LocalTime, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_LocalTime_isBefore arginfo_class_Temporal_LocalTime_isEqualTo

#define arginfo_class_Temporal_LocalTime_isBeforeOrEqualTo arginfo_class_Temporal_LocalTime_isEqualTo

#define arginfo_class_Temporal_LocalTime_isAfter arginfo_class_Temporal_LocalTime_isEqualTo

#define arginfo_class_Temporal_LocalTime_isAfterOrEqualTo arginfo_class_Temporal_LocalTime_isEqualTo

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalTime_toDateTime, 0, 0, DateTimeImmutable, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_LocalTime_fromDateTime, 0, 1, Temporal\\LocalTime, 0)
	ZEND_ARG_OBJ_INFO(0, dateTime, DateTimeInterface, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_LocalTime_toISOString, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_LocalTime_format, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, localizedPattern, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, locale, IS_STRING, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_LocalTime_formatWith, 0, 1, IS_STRING, 0)
	ZEND_ARG_OBJ_INFO(0, formatter, Temporal\\Format\\DateTimeFormatter, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_LocalTime_jsonSerialize arginfo_class_Temporal_LocalTime_toISOString

#define arginfo_class_Temporal_LocalTime___toString arginfo_class_Temporal_LocalTime_toISOString

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_LocalTime___serialize, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_LocalTime___unserialize, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_METHOD(Temporal_LocalTime, __construct);
ZEND_METHOD(Temporal_LocalTime, of);
ZEND_METHOD(Temporal_LocalTime, ofSecondOfDay);
ZEND_METHOD(Temporal_LocalTime, now);
ZEND_METHOD(Temporal_LocalTime, fromISOString);
ZEND_METHOD(Temporal_LocalTime, midnight);
ZEND_METHOD(Temporal_LocalTime, noon);
ZEND_METHOD(Temporal_LocalTime, min);
ZEND_METHOD(Temporal_LocalTime, max);
ZEND_METHOD(Temporal_LocalTime, getHour);
ZEND_METHOD(Temporal_LocalTime, withHour);
ZEND_METHOD(Temporal_LocalTime, getMinute);
ZEND_METHOD(Temporal_LocalTime, withMinute);
ZEND_METHOD(Temporal_LocalTime, getSecond);
ZEND_METHOD(Temporal_LocalTime, withSecond);
ZEND_METHOD(Temporal_LocalTime, getNano);
ZEND_METHOD(Temporal_LocalTime, withNano);
ZEND_METHOD(Temporal_LocalTime, getSecondOfDay);
ZEND_METHOD(Temporal_LocalTime, plus);
ZEND_METHOD(Temporal_LocalTime, plusHours);
ZEND_METHOD(Temporal_LocalTime, plusMinutes);
ZEND_METHOD(Temporal_LocalTime, plusSeconds);
ZEND_METHOD(Temporal_LocalTime, plusNanos);
ZEND_METHOD(Temporal_LocalTime, minus);
ZEND_METHOD(Temporal_LocalTime, minusHours);
ZEND_METHOD(Temporal_LocalTime, minusMinutes);
ZEND_METHOD(Temporal_LocalTime, minusSeconds);
ZEND_METHOD(Temporal_LocalTime, minusNanos);
ZEND_METHOD(Temporal_LocalTime, atDate);
ZEND_METHOD(Temporal_LocalTime, compareTo);
ZEND_METHOD(Temporal_LocalTime, isEqualTo);
ZEND_METHOD(Temporal_LocalTime, isBefore);
ZEND_METHOD(Temporal_LocalTime, isBeforeOrEqualTo);
ZEND_METHOD(Temporal_LocalTime, isAfter);
ZEND_METHOD(Temporal_LocalTime, isAfterOrEqualTo);
ZEND_METHOD(Temporal_LocalTime, toDateTime);
ZEND_METHOD(Temporal_LocalTime, fromDateTime);
ZEND_METHOD(Temporal_LocalTime, toISOString);
ZEND_METHOD(Temporal_LocalTime, format);
ZEND_METHOD(Temporal_LocalTime, formatWith);
ZEND_METHOD(Temporal_LocalTime, jsonSerialize);
ZEND_METHOD(Temporal_LocalTime, __toString);
ZEND_METHOD(Temporal_LocalTime, __serialize);
ZEND_METHOD(Temporal_LocalTime, __unserialize);

static const zend_function_entry class_Temporal_LocalTime_methods[] = {
	ZEND_ME(Temporal_LocalTime, __construct, arginfo_class_Temporal_LocalTime___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(Temporal_LocalTime, of, arginfo_class_Temporal_LocalTime_of, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_LocalTime, ofSecondOfDay, arginfo_class_Temporal_LocalTime_ofSecondOfDay, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_LocalTime, now, arginfo_class_Temporal_LocalTime_now, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_LocalTime, fromISOString, arginfo_class_Temporal_LocalTime_fromISOString, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_LocalTime, midnight, arginfo_class_Temporal_LocalTime_midnight, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_LocalTime, noon, arginfo_class_Temporal_LocalTime_noon, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_LocalTime, min, arginfo_class_Temporal_LocalTime_min, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_LocalTime, max, arginfo_class_Temporal_LocalTime_max, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_LocalTime, getHour, arginfo_class_Temporal_LocalTime_getHour, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalTime, withHour, arginfo_class_Temporal_LocalTime_withHour, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalTime, getMinute, arginfo_class_Temporal_LocalTime_getMinute, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalTime, withMinute, arginfo_class_Temporal_LocalTime_withMinute, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalTime, getSecond, arginfo_class_Temporal_LocalTime_getSecond, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalTime, withSecond, arginfo_class_Temporal_LocalTime_withSecond, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalTime, getNano, arginfo_class_Temporal_LocalTime_getNano, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalTime, withNano, arginfo_class_Temporal_LocalTime_withNano, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalTime, getSecondOfDay, arginfo_class_Temporal_LocalTime_getSecondOfDay, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalTime, plus, arginfo_class_Temporal_LocalTime_plus, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalTime, plusHours, arginfo_class_Temporal_LocalTime_plusHours, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalTime, plusMinutes, arginfo_class_Temporal_LocalTime_plusMinutes, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalTime, plusSeconds, arginfo_class_Temporal_LocalTime_plusSeconds, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalTime, plusNanos, arginfo_class_Temporal_LocalTime_plusNanos, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalTime, minus, arginfo_class_Temporal_LocalTime_minus, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalTime, minusHours, arginfo_class_Temporal_LocalTime_minusHours, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalTime, minusMinutes, arginfo_class_Temporal_LocalTime_minusMinutes, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalTime, minusSeconds, arginfo_class_Temporal_LocalTime_minusSeconds, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalTime, minusNanos, arginfo_class_Temporal_LocalTime_minusNanos, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalTime, atDate, arginfo_class_Temporal_LocalTime_atDate, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalTime, compareTo, arginfo_class_Temporal_LocalTime_compareTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalTime, isEqualTo, arginfo_class_Temporal_LocalTime_isEqualTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalTime, isBefore, arginfo_class_Temporal_LocalTime_isBefore, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalTime, isBeforeOrEqualTo, arginfo_class_Temporal_LocalTime_isBeforeOrEqualTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalTime, isAfter, arginfo_class_Temporal_LocalTime_isAfter, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalTime, isAfterOrEqualTo, arginfo_class_Temporal_LocalTime_isAfterOrEqualTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalTime, toDateTime, arginfo_class_Temporal_LocalTime_toDateTime, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalTime, fromDateTime, arginfo_class_Temporal_LocalTime_fromDateTime, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_LocalTime, toISOString, arginfo_class_Temporal_LocalTime_toISOString, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalTime, format, arginfo_class_Temporal_LocalTime_format, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalTime, formatWith, arginfo_class_Temporal_LocalTime_formatWith, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalTime, jsonSerialize, arginfo_class_Temporal_LocalTime_jsonSerialize, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalTime, __toString, arginfo_class_Temporal_LocalTime___toString, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalTime, __serialize, arginfo_class_Temporal_LocalTime___serialize, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_LocalTime, __unserialize, arginfo_class_Temporal_LocalTime___unserialize, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_Temporal_LocalTime(zend_class_entry *class_entry_JsonSerializable, zend_class_entry *class_entry_Stringable)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Temporal", "LocalTime", class_Temporal_LocalTime_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);
	zend_class_implements(class_entry, 2, class_entry_JsonSerializable, class_entry_Stringable);

	return class_entry;
}
