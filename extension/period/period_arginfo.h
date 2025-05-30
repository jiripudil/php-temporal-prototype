/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 496401d32f9d21e14b7aa2fc1666ac437896447c */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_Temporal_Period___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Period_of, 0, 3, Temporal\\Period, 0)
	ZEND_ARG_TYPE_INFO(0, years, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, months, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, days, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Period_ofYears, 0, 1, Temporal\\Period, 0)
	ZEND_ARG_TYPE_INFO(0, years, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Period_ofMonths, 0, 1, Temporal\\Period, 0)
	ZEND_ARG_TYPE_INFO(0, months, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Period_ofWeeks, 0, 1, Temporal\\Period, 0)
	ZEND_ARG_TYPE_INFO(0, weeks, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Period_ofDays, 0, 1, Temporal\\Period, 0)
	ZEND_ARG_TYPE_INFO(0, days, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Period_zero, 0, 0, Temporal\\Period, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Period_between, 0, 2, Temporal\\Period, 0)
	ZEND_ARG_OBJ_INFO(0, start, Temporal\\LocalDate, 0)
	ZEND_ARG_OBJ_INFO(0, endExclusive, Temporal\\LocalDate, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_class_Temporal_Period_fromIsoString, 0, 1, Temporal\\Period, 0)
	ZEND_ARG_TYPE_INFO(0, text, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_Period_getYears, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_Period_withYears arginfo_class_Temporal_Period_ofYears

#define arginfo_class_Temporal_Period_plusYears arginfo_class_Temporal_Period_ofYears

#define arginfo_class_Temporal_Period_minusYears arginfo_class_Temporal_Period_ofYears

#define arginfo_class_Temporal_Period_getMonths arginfo_class_Temporal_Period_getYears

#define arginfo_class_Temporal_Period_withMonths arginfo_class_Temporal_Period_ofMonths

#define arginfo_class_Temporal_Period_plusMonths arginfo_class_Temporal_Period_ofMonths

#define arginfo_class_Temporal_Period_minusMonths arginfo_class_Temporal_Period_ofMonths

#define arginfo_class_Temporal_Period_getDays arginfo_class_Temporal_Period_getYears

#define arginfo_class_Temporal_Period_withDays arginfo_class_Temporal_Period_ofDays

#define arginfo_class_Temporal_Period_plusDays arginfo_class_Temporal_Period_ofDays

#define arginfo_class_Temporal_Period_minusDays arginfo_class_Temporal_Period_ofDays

#define arginfo_class_Temporal_Period_negated arginfo_class_Temporal_Period_zero

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_Period_isZero, 0, 0, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_Period_isEqualTo, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, other, Temporal\\Period, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_Period_toIsoString, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_Temporal_Period_jsonSerialize arginfo_class_Temporal_Period_toIsoString

#define arginfo_class_Temporal_Period___toString arginfo_class_Temporal_Period_toIsoString

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_Period___serialize, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_Temporal_Period___unserialize, 0, 1, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(0, data, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_METHOD(Temporal_Period, __construct);
ZEND_METHOD(Temporal_Period, of);
ZEND_METHOD(Temporal_Period, ofYears);
ZEND_METHOD(Temporal_Period, ofMonths);
ZEND_METHOD(Temporal_Period, ofWeeks);
ZEND_METHOD(Temporal_Period, ofDays);
ZEND_METHOD(Temporal_Period, zero);
ZEND_METHOD(Temporal_Period, between);
ZEND_METHOD(Temporal_Period, fromIsoString);
ZEND_METHOD(Temporal_Period, getYears);
ZEND_METHOD(Temporal_Period, withYears);
ZEND_METHOD(Temporal_Period, plusYears);
ZEND_METHOD(Temporal_Period, minusYears);
ZEND_METHOD(Temporal_Period, getMonths);
ZEND_METHOD(Temporal_Period, withMonths);
ZEND_METHOD(Temporal_Period, plusMonths);
ZEND_METHOD(Temporal_Period, minusMonths);
ZEND_METHOD(Temporal_Period, getDays);
ZEND_METHOD(Temporal_Period, withDays);
ZEND_METHOD(Temporal_Period, plusDays);
ZEND_METHOD(Temporal_Period, minusDays);
ZEND_METHOD(Temporal_Period, negated);
ZEND_METHOD(Temporal_Period, isZero);
ZEND_METHOD(Temporal_Period, isEqualTo);
ZEND_METHOD(Temporal_Period, toIsoString);
ZEND_METHOD(Temporal_Period, jsonSerialize);
ZEND_METHOD(Temporal_Period, __toString);
ZEND_METHOD(Temporal_Period, __serialize);
ZEND_METHOD(Temporal_Period, __unserialize);

static const zend_function_entry class_Temporal_Period_methods[] = {
	ZEND_ME(Temporal_Period, __construct, arginfo_class_Temporal_Period___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(Temporal_Period, of, arginfo_class_Temporal_Period_of, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_Period, ofYears, arginfo_class_Temporal_Period_ofYears, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_Period, ofMonths, arginfo_class_Temporal_Period_ofMonths, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_Period, ofWeeks, arginfo_class_Temporal_Period_ofWeeks, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_Period, ofDays, arginfo_class_Temporal_Period_ofDays, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_Period, zero, arginfo_class_Temporal_Period_zero, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_Period, between, arginfo_class_Temporal_Period_between, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_Period, fromIsoString, arginfo_class_Temporal_Period_fromIsoString, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_ME(Temporal_Period, getYears, arginfo_class_Temporal_Period_getYears, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Period, withYears, arginfo_class_Temporal_Period_withYears, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Period, plusYears, arginfo_class_Temporal_Period_plusYears, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Period, minusYears, arginfo_class_Temporal_Period_minusYears, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Period, getMonths, arginfo_class_Temporal_Period_getMonths, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Period, withMonths, arginfo_class_Temporal_Period_withMonths, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Period, plusMonths, arginfo_class_Temporal_Period_plusMonths, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Period, minusMonths, arginfo_class_Temporal_Period_minusMonths, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Period, getDays, arginfo_class_Temporal_Period_getDays, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Period, withDays, arginfo_class_Temporal_Period_withDays, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Period, plusDays, arginfo_class_Temporal_Period_plusDays, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Period, minusDays, arginfo_class_Temporal_Period_minusDays, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Period, negated, arginfo_class_Temporal_Period_negated, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Period, isZero, arginfo_class_Temporal_Period_isZero, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Period, isEqualTo, arginfo_class_Temporal_Period_isEqualTo, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Period, toIsoString, arginfo_class_Temporal_Period_toIsoString, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Period, jsonSerialize, arginfo_class_Temporal_Period_jsonSerialize, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Period, __toString, arginfo_class_Temporal_Period___toString, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Period, __serialize, arginfo_class_Temporal_Period___serialize, ZEND_ACC_PUBLIC)
	ZEND_ME(Temporal_Period, __unserialize, arginfo_class_Temporal_Period___unserialize, ZEND_ACC_PUBLIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_Temporal_Period(zend_class_entry *class_entry_JsonSerializable, zend_class_entry *class_entry_Stringable)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Temporal", "Period", class_Temporal_Period_methods);
#if (PHP_VERSION_ID >= 80400)
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);
#else
	class_entry = zend_register_internal_class_ex(&ce, NULL);
	class_entry->ce_flags |= ZEND_ACC_FINAL;
#endif
	zend_class_implements(class_entry, 2, class_entry_JsonSerializable, class_entry_Stringable);

	return class_entry;
}
