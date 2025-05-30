/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: f2734ce829d5902551d80806cc18d9ecb7894af8 */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Temporal_Instant___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Instant_of, 0, 1, Temporal\\Instant, 0)
	ZEND_ARG_TYPE_INFO(0, epochSecond, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, nanoAdjustment, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Instant_now, 0, 0, Temporal\\Instant, 0)
	ZEND_ARG_OBJ_INFO_WITH_DEFAULT_VALUE(0, clock, Temporal\\Clock, 1, "null")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Instant_epoch, 0, 0, Temporal\\Instant, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_Instant_min arginfo_class_Temporal_Instant_epoch

#define arginfo_class_Temporal_Instant_max arginfo_class_Temporal_Instant_epoch

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_Instant_getEpochSecond, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_Instant_getNano arginfo_class_Temporal_Instant_getEpochSecond

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Instant_withEpochSecond, 0, 1, Temporal\\Instant, 0)
	ZEND_ARG_TYPE_INFO(0, epochSecond, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Instant_withNano, 0, 1, Temporal\\Instant, 0)
	ZEND_ARG_TYPE_INFO(0, nano, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Instant_plus, 0, 1, Temporal\\Instant, 0)
	ZEND_ARG_OBJ_INFO(0, duration, Temporal\\Duration, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Instant_plusSeconds, 0, 1, Temporal\\Instant, 0)
	ZEND_ARG_TYPE_INFO(0, seconds, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Instant_plusMinutes, 0, 1, Temporal\\Instant, 0)
	ZEND_ARG_TYPE_INFO(0, minutes, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Instant_plusHours, 0, 1, Temporal\\Instant, 0)
	ZEND_ARG_TYPE_INFO(0, hours, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Instant_plusDays, 0, 1, Temporal\\Instant, 0)
	ZEND_ARG_TYPE_INFO(0, days, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_Instant_minus arginfo_class_Temporal_Instant_plus

#define arginfo_class_Temporal_Instant_minusSeconds arginfo_class_Temporal_Instant_plusSeconds

#define arginfo_class_Temporal_Instant_minusMinutes arginfo_class_Temporal_Instant_plusMinutes

#define arginfo_class_Temporal_Instant_minusHours arginfo_class_Temporal_Instant_plusSeconds

#define arginfo_class_Temporal_Instant_minusDays arginfo_class_Temporal_Instant_plusDays

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_Instant_compareTo, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, other, Temporal\\Instant, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_Instant_isEqualTo, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, other, Temporal\\Instant, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_Instant_isBefore arginfo_class_Temporal_Instant_isEqualTo

#define arginfo_class_Temporal_Instant_isBeforeOrEqualTo arginfo_class_Temporal_Instant_isEqualTo

#define arginfo_class_Temporal_Instant_isAfter arginfo_class_Temporal_Instant_isEqualTo

#define arginfo_class_Temporal_Instant_isAfterOrEqualTo arginfo_class_Temporal_Instant_isEqualTo

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Instant_atTimeZone, 0, 1, Temporal\\ZonedDateTime, 0)
	ZEND_ARG_OBJ_INFO(0, timeZone, Temporal\\TimeZone, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_Instant_toDecimal, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_Instant_toIsoString arginfo_class_Temporal_Instant_toDecimal

#define arginfo_class_Temporal_Instant_jsonSerialize arginfo_class_Temporal_Instant_toDecimal

#define arginfo_class_Temporal_Instant___toString arginfo_class_Temporal_Instant_toDecimal

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_Instant___serialize, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_Instant___unserialize, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_METHOD(Temporal_Instant, __construct);
ZEND_METHOD(Temporal_Instant, of);
ZEND_METHOD(Temporal_Instant, now);
ZEND_METHOD(Temporal_Instant, epoch);
ZEND_METHOD(Temporal_Instant, min);
ZEND_METHOD(Temporal_Instant, max);
ZEND_METHOD(Temporal_Instant, getEpochSecond);
ZEND_METHOD(Temporal_Instant, getNano);
ZEND_METHOD(Temporal_Instant, withEpochSecond);
ZEND_METHOD(Temporal_Instant, withNano);
ZEND_METHOD(Temporal_Instant, plus);
ZEND_METHOD(Temporal_Instant, plusSeconds);
ZEND_METHOD(Temporal_Instant, plusMinutes);
ZEND_METHOD(Temporal_Instant, plusHours);
ZEND_METHOD(Temporal_Instant, plusDays);
ZEND_METHOD(Temporal_Instant, minus);
ZEND_METHOD(Temporal_Instant, minusSeconds);
ZEND_METHOD(Temporal_Instant, minusMinutes);
ZEND_METHOD(Temporal_Instant, minusHours);
ZEND_METHOD(Temporal_Instant, minusDays);
ZEND_METHOD(Temporal_Instant, compareTo);
ZEND_METHOD(Temporal_Instant, isEqualTo);
ZEND_METHOD(Temporal_Instant, isBefore);
ZEND_METHOD(Temporal_Instant, isBeforeOrEqualTo);
ZEND_METHOD(Temporal_Instant, isAfter);
ZEND_METHOD(Temporal_Instant, isAfterOrEqualTo);
ZEND_METHOD(Temporal_Instant, atTimeZone);
ZEND_METHOD(Temporal_Instant, toDecimal);
ZEND_METHOD(Temporal_Instant, toIsoString);
ZEND_METHOD(Temporal_Instant, jsonSerialize);
ZEND_METHOD(Temporal_Instant, __toString);
ZEND_METHOD(Temporal_Instant, __serialize);
ZEND_METHOD(Temporal_Instant, __unserialize);

static const zend_function_entry class_Temporal_Instant_methods[] = {
	ZEND_ME(Temporal_Instant, __construct, arginfo_class_Temporal_Instant___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(Temporal_Instant, of, arginfo_class_Temporal_Instant_of, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_Instant, now, arginfo_class_Temporal_Instant_now, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_Instant, epoch, arginfo_class_Temporal_Instant_epoch, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_Instant, min, arginfo_class_Temporal_Instant_min, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_Instant, max, arginfo_class_Temporal_Instant_max, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_Instant, getEpochSecond, arginfo_class_Temporal_Instant_getEpochSecond, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Instant, getNano, arginfo_class_Temporal_Instant_getNano, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Instant, withEpochSecond, arginfo_class_Temporal_Instant_withEpochSecond, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Instant, withNano, arginfo_class_Temporal_Instant_withNano, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Instant, plus, arginfo_class_Temporal_Instant_plus, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Instant, plusSeconds, arginfo_class_Temporal_Instant_plusSeconds, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Instant, plusMinutes, arginfo_class_Temporal_Instant_plusMinutes, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Instant, plusHours, arginfo_class_Temporal_Instant_plusHours, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Instant, plusDays, arginfo_class_Temporal_Instant_plusDays, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Instant, minus, arginfo_class_Temporal_Instant_minus, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Instant, minusSeconds, arginfo_class_Temporal_Instant_minusSeconds, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Instant, minusMinutes, arginfo_class_Temporal_Instant_minusMinutes, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Instant, minusHours, arginfo_class_Temporal_Instant_minusHours, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Instant, minusDays, arginfo_class_Temporal_Instant_minusDays, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Instant, compareTo, arginfo_class_Temporal_Instant_compareTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Instant, isEqualTo, arginfo_class_Temporal_Instant_isEqualTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Instant, isBefore, arginfo_class_Temporal_Instant_isBefore, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Instant, isBeforeOrEqualTo, arginfo_class_Temporal_Instant_isBeforeOrEqualTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Instant, isAfter, arginfo_class_Temporal_Instant_isAfter, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Instant, isAfterOrEqualTo, arginfo_class_Temporal_Instant_isAfterOrEqualTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Instant, atTimeZone, arginfo_class_Temporal_Instant_atTimeZone, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Instant, toDecimal, arginfo_class_Temporal_Instant_toDecimal, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Instant, toIsoString, arginfo_class_Temporal_Instant_toIsoString, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Instant, jsonSerialize, arginfo_class_Temporal_Instant_jsonSerialize, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Instant, __toString, arginfo_class_Temporal_Instant___toString, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Instant, __serialize, arginfo_class_Temporal_Instant___serialize, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Instant, __unserialize, arginfo_class_Temporal_Instant___unserialize, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_Temporal_Instant(zend_class_entry *class_entry_JsonSerializable, zend_class_entry *class_entry_Stringable)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Temporal", "Instant", class_Temporal_Instant_methods);
#if (PHP_VERSION_ID >= 80400)
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);
#else
	class_entry = zend_register_internal_class_ex(&ce, NULL);
	class_entry->ce_flags |= ZEND_ACC_FINAL;
#endif
	zend_class_implements(class_entry, 2, class_entry_JsonSerializable, class_entry_Stringable);

	return class_entry;
}
