/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: b2e780d809be9c0e3cfd55ba1291c40b97c91f56 */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Temporal_Duration___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Duration_zero, 0, 0, Temporal\\Duration, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Duration_fromISOString, 0, 1, Temporal\\Duration, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Duration_ofSeconds, 0, 1, Temporal\\Duration, 0)
	ZEND_ARG_TYPE_INFO(0, seconds, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, nanoAdjustment, IS_LONG, 0, "0")
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Duration_ofMinutes, 0, 1, Temporal\\Duration, 0)
	ZEND_ARG_TYPE_INFO(0, minutes, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Duration_ofHours, 0, 1, Temporal\\Duration, 0)
	ZEND_ARG_TYPE_INFO(0, hours, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Duration_ofDays, 0, 1, Temporal\\Duration, 0)
	ZEND_ARG_TYPE_INFO(0, days, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Duration_between, 0, 2, Temporal\\Duration, 0)
	ZEND_ARG_OBJ_INFO(0, start, Temporal\\Instant, 0)
	ZEND_ARG_OBJ_INFO(0, endExclusive, Temporal\\Instant, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_Duration_getSeconds, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_Duration_getNanos arginfo_class_Temporal_Duration_getSeconds

#define arginfo_class_Temporal_Duration_toDays arginfo_class_Temporal_Duration_getSeconds

#define arginfo_class_Temporal_Duration_toDaysPart arginfo_class_Temporal_Duration_getSeconds

#define arginfo_class_Temporal_Duration_toHours arginfo_class_Temporal_Duration_getSeconds

#define arginfo_class_Temporal_Duration_toHoursPart arginfo_class_Temporal_Duration_getSeconds

#define arginfo_class_Temporal_Duration_toMinutes arginfo_class_Temporal_Duration_getSeconds

#define arginfo_class_Temporal_Duration_toMinutesPart arginfo_class_Temporal_Duration_getSeconds

#define arginfo_class_Temporal_Duration_toSeconds arginfo_class_Temporal_Duration_getSeconds

#define arginfo_class_Temporal_Duration_toSecondsPart arginfo_class_Temporal_Duration_getSeconds

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_Duration_isZero, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_Duration_isPositive arginfo_class_Temporal_Duration_isZero

#define arginfo_class_Temporal_Duration_isPositiveOrZero arginfo_class_Temporal_Duration_isZero

#define arginfo_class_Temporal_Duration_isNegative arginfo_class_Temporal_Duration_isZero

#define arginfo_class_Temporal_Duration_isNegativeOrZero arginfo_class_Temporal_Duration_isZero

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Duration_plus, 0, 1, Temporal\\Duration, 0)
	ZEND_ARG_OBJ_INFO(0, other, Temporal\\Duration, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Duration_plusSeconds, 0, 1, Temporal\\Duration, 0)
	ZEND_ARG_TYPE_INFO(0, seconds, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_Duration_plusMinutes arginfo_class_Temporal_Duration_ofMinutes

#define arginfo_class_Temporal_Duration_plusHours arginfo_class_Temporal_Duration_ofHours

#define arginfo_class_Temporal_Duration_plusDays arginfo_class_Temporal_Duration_ofDays

#define arginfo_class_Temporal_Duration_minus arginfo_class_Temporal_Duration_plus

#define arginfo_class_Temporal_Duration_minusSeconds arginfo_class_Temporal_Duration_plusSeconds

#define arginfo_class_Temporal_Duration_minusMinutes arginfo_class_Temporal_Duration_ofMinutes

#define arginfo_class_Temporal_Duration_minusHours arginfo_class_Temporal_Duration_ofHours

#define arginfo_class_Temporal_Duration_minusDays arginfo_class_Temporal_Duration_ofDays

#define arginfo_class_Temporal_Duration_negated arginfo_class_Temporal_Duration_zero

#define arginfo_class_Temporal_Duration_abs arginfo_class_Temporal_Duration_zero

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_Duration_compareTo, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, other, Temporal\\Duration, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_Duration_isEqualTo, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, other, Temporal\\Duration, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_Duration_isGreaterThan arginfo_class_Temporal_Duration_isEqualTo

#define arginfo_class_Temporal_Duration_isGreaterThanOrEqualTo arginfo_class_Temporal_Duration_isEqualTo

#define arginfo_class_Temporal_Duration_isLesserThan arginfo_class_Temporal_Duration_isEqualTo

#define arginfo_class_Temporal_Duration_isLesserThanOrEqualTo arginfo_class_Temporal_Duration_isEqualTo

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_Duration_toISOString, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_Duration_jsonSerialize arginfo_class_Temporal_Duration_toISOString

#define arginfo_class_Temporal_Duration___toString arginfo_class_Temporal_Duration_toISOString

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_Duration___serialize, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_Duration___unserialize, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_METHOD(Temporal_Duration, __construct);
ZEND_METHOD(Temporal_Duration, zero);
ZEND_METHOD(Temporal_Duration, fromISOString);
ZEND_METHOD(Temporal_Duration, ofSeconds);
ZEND_METHOD(Temporal_Duration, ofMinutes);
ZEND_METHOD(Temporal_Duration, ofHours);
ZEND_METHOD(Temporal_Duration, ofDays);
ZEND_METHOD(Temporal_Duration, between);
ZEND_METHOD(Temporal_Duration, getSeconds);
ZEND_METHOD(Temporal_Duration, getNanos);
ZEND_METHOD(Temporal_Duration, toDays);
ZEND_METHOD(Temporal_Duration, toDaysPart);
ZEND_METHOD(Temporal_Duration, toHours);
ZEND_METHOD(Temporal_Duration, toHoursPart);
ZEND_METHOD(Temporal_Duration, toMinutes);
ZEND_METHOD(Temporal_Duration, toMinutesPart);
ZEND_METHOD(Temporal_Duration, toSeconds);
ZEND_METHOD(Temporal_Duration, toSecondsPart);
ZEND_METHOD(Temporal_Duration, isZero);
ZEND_METHOD(Temporal_Duration, isPositive);
ZEND_METHOD(Temporal_Duration, isPositiveOrZero);
ZEND_METHOD(Temporal_Duration, isNegative);
ZEND_METHOD(Temporal_Duration, isNegativeOrZero);
ZEND_METHOD(Temporal_Duration, plus);
ZEND_METHOD(Temporal_Duration, plusSeconds);
ZEND_METHOD(Temporal_Duration, plusMinutes);
ZEND_METHOD(Temporal_Duration, plusHours);
ZEND_METHOD(Temporal_Duration, plusDays);
ZEND_METHOD(Temporal_Duration, minus);
ZEND_METHOD(Temporal_Duration, minusSeconds);
ZEND_METHOD(Temporal_Duration, minusMinutes);
ZEND_METHOD(Temporal_Duration, minusHours);
ZEND_METHOD(Temporal_Duration, minusDays);
ZEND_METHOD(Temporal_Duration, negated);
ZEND_METHOD(Temporal_Duration, abs);
ZEND_METHOD(Temporal_Duration, compareTo);
ZEND_METHOD(Temporal_Duration, isEqualTo);
ZEND_METHOD(Temporal_Duration, isGreaterThan);
ZEND_METHOD(Temporal_Duration, isGreaterThanOrEqualTo);
ZEND_METHOD(Temporal_Duration, isLesserThan);
ZEND_METHOD(Temporal_Duration, isLesserThanOrEqualTo);
ZEND_METHOD(Temporal_Duration, toISOString);
ZEND_METHOD(Temporal_Duration, jsonSerialize);
ZEND_METHOD(Temporal_Duration, __toString);
ZEND_METHOD(Temporal_Duration, __serialize);
ZEND_METHOD(Temporal_Duration, __unserialize);

static const zend_function_entry class_Temporal_Duration_methods[] = {
	ZEND_ME(Temporal_Duration, __construct, arginfo_class_Temporal_Duration___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(Temporal_Duration, zero, arginfo_class_Temporal_Duration_zero, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_Duration, fromISOString, arginfo_class_Temporal_Duration_fromISOString, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_Duration, ofSeconds, arginfo_class_Temporal_Duration_ofSeconds, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_Duration, ofMinutes, arginfo_class_Temporal_Duration_ofMinutes, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_Duration, ofHours, arginfo_class_Temporal_Duration_ofHours, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_Duration, ofDays, arginfo_class_Temporal_Duration_ofDays, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_Duration, between, arginfo_class_Temporal_Duration_between, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_Duration, getSeconds, arginfo_class_Temporal_Duration_getSeconds, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, getNanos, arginfo_class_Temporal_Duration_getNanos, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, toDays, arginfo_class_Temporal_Duration_toDays, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, toDaysPart, arginfo_class_Temporal_Duration_toDaysPart, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, toHours, arginfo_class_Temporal_Duration_toHours, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, toHoursPart, arginfo_class_Temporal_Duration_toHoursPart, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, toMinutes, arginfo_class_Temporal_Duration_toMinutes, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, toMinutesPart, arginfo_class_Temporal_Duration_toMinutesPart, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, toSeconds, arginfo_class_Temporal_Duration_toSeconds, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, toSecondsPart, arginfo_class_Temporal_Duration_toSecondsPart, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, isZero, arginfo_class_Temporal_Duration_isZero, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, isPositive, arginfo_class_Temporal_Duration_isPositive, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, isPositiveOrZero, arginfo_class_Temporal_Duration_isPositiveOrZero, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, isNegative, arginfo_class_Temporal_Duration_isNegative, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, isNegativeOrZero, arginfo_class_Temporal_Duration_isNegativeOrZero, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, plus, arginfo_class_Temporal_Duration_plus, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, plusSeconds, arginfo_class_Temporal_Duration_plusSeconds, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, plusMinutes, arginfo_class_Temporal_Duration_plusMinutes, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, plusHours, arginfo_class_Temporal_Duration_plusHours, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, plusDays, arginfo_class_Temporal_Duration_plusDays, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, minus, arginfo_class_Temporal_Duration_minus, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, minusSeconds, arginfo_class_Temporal_Duration_minusSeconds, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, minusMinutes, arginfo_class_Temporal_Duration_minusMinutes, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, minusHours, arginfo_class_Temporal_Duration_minusHours, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, minusDays, arginfo_class_Temporal_Duration_minusDays, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, negated, arginfo_class_Temporal_Duration_negated, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, abs, arginfo_class_Temporal_Duration_abs, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, compareTo, arginfo_class_Temporal_Duration_compareTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, isEqualTo, arginfo_class_Temporal_Duration_isEqualTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, isGreaterThan, arginfo_class_Temporal_Duration_isGreaterThan, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, isGreaterThanOrEqualTo, arginfo_class_Temporal_Duration_isGreaterThanOrEqualTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, isLesserThan, arginfo_class_Temporal_Duration_isLesserThan, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, isLesserThanOrEqualTo, arginfo_class_Temporal_Duration_isLesserThanOrEqualTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, toISOString, arginfo_class_Temporal_Duration_toISOString, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, jsonSerialize, arginfo_class_Temporal_Duration_jsonSerialize, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, __toString, arginfo_class_Temporal_Duration___toString, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, __serialize, arginfo_class_Temporal_Duration___serialize, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Duration, __unserialize, arginfo_class_Temporal_Duration___unserialize, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_Temporal_Duration(zend_class_entry *class_entry_JsonSerializable, zend_class_entry *class_entry_Stringable)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Temporal", "Duration", class_Temporal_Duration_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);
	zend_class_implements(class_entry, 2, class_entry_JsonSerializable, class_entry_Stringable);

	zval const_NANOS_PER_SECOND_value;
	ZVAL_LONG(&const_NANOS_PER_SECOND_value, 1000000000);
	zend_string *const_NANOS_PER_SECOND_name = zend_string_init_interned("NANOS_PER_SECOND", sizeof("NANOS_PER_SECOND") - 1, 1);
	zend_declare_typed_class_constant(class_entry, const_NANOS_PER_SECOND_name, &const_NANOS_PER_SECOND_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(const_NANOS_PER_SECOND_name);

	zval const_SECONDS_PER_MINUTE_value;
	ZVAL_LONG(&const_SECONDS_PER_MINUTE_value, 60);
	zend_string *const_SECONDS_PER_MINUTE_name = zend_string_init_interned("SECONDS_PER_MINUTE", sizeof("SECONDS_PER_MINUTE") - 1, 1);
	zend_declare_typed_class_constant(class_entry, const_SECONDS_PER_MINUTE_name, &const_SECONDS_PER_MINUTE_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(const_SECONDS_PER_MINUTE_name);

	zval const_SECONDS_PER_HOUR_value;
	ZVAL_LONG(&const_SECONDS_PER_HOUR_value, 3600);
	zend_string *const_SECONDS_PER_HOUR_name = zend_string_init_interned("SECONDS_PER_HOUR", sizeof("SECONDS_PER_HOUR") - 1, 1);
	zend_declare_typed_class_constant(class_entry, const_SECONDS_PER_HOUR_name, &const_SECONDS_PER_HOUR_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(const_SECONDS_PER_HOUR_name);

	zval const_SECONDS_PER_DAY_value;
	ZVAL_LONG(&const_SECONDS_PER_DAY_value, 86400);
	zend_string *const_SECONDS_PER_DAY_name = zend_string_init_interned("SECONDS_PER_DAY", sizeof("SECONDS_PER_DAY") - 1, 1);
	zend_declare_typed_class_constant(class_entry, const_SECONDS_PER_DAY_name, &const_SECONDS_PER_DAY_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(const_SECONDS_PER_DAY_name);

	zval const_MINUTES_PER_HOUR_value;
	ZVAL_LONG(&const_MINUTES_PER_HOUR_value, 60);
	zend_string *const_MINUTES_PER_HOUR_name = zend_string_init_interned("MINUTES_PER_HOUR", sizeof("MINUTES_PER_HOUR") - 1, 1);
	zend_declare_typed_class_constant(class_entry, const_MINUTES_PER_HOUR_name, &const_MINUTES_PER_HOUR_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(const_MINUTES_PER_HOUR_name);

	zval const_HOURS_PER_DAY_value;
	ZVAL_LONG(&const_HOURS_PER_DAY_value, 24);
	zend_string *const_HOURS_PER_DAY_name = zend_string_init_interned("HOURS_PER_DAY", sizeof("HOURS_PER_DAY") - 1, 1);
	zend_declare_typed_class_constant(class_entry, const_HOURS_PER_DAY_name, &const_HOURS_PER_DAY_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(const_HOURS_PER_DAY_name);

	return class_entry;
}
