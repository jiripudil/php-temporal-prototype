/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 6960fa9f06c4a6c9671c6e024675f7936f075786 */

static zend_class_entry *register_class_Temporal_TemporalException(zend_class_entry *class_entry_Exception)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Temporal", "TemporalException", NULL);
#if (PHP_VERSION_ID >= 80400)
	class_entry = zend_register_internal_class_with_flags(&ce, class_entry_Exception, 0);
#else
	class_entry = zend_register_internal_class_ex(&ce, class_entry_Exception);
#endif

	return class_entry;
}

static zend_class_entry *register_class_Temporal_Exception_DateTimeConversionException(zend_class_entry *class_entry_Temporal_TemporalException)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Temporal\\Exception", "DateTimeConversionException", NULL);
#if (PHP_VERSION_ID >= 80400)
	class_entry = zend_register_internal_class_with_flags(&ce, class_entry_Temporal_TemporalException, ZEND_ACC_FINAL);
#else
	class_entry = zend_register_internal_class_ex(&ce, class_entry_Temporal_TemporalException);
	class_entry->ce_flags |= ZEND_ACC_FINAL;
#endif

	return class_entry;
}

static zend_class_entry *register_class_Temporal_Exception_FormattingException(zend_class_entry *class_entry_Temporal_TemporalException)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Temporal\\Exception", "FormattingException", NULL);
#if (PHP_VERSION_ID >= 80400)
	class_entry = zend_register_internal_class_with_flags(&ce, class_entry_Temporal_TemporalException, ZEND_ACC_FINAL);
#else
	class_entry = zend_register_internal_class_ex(&ce, class_entry_Temporal_TemporalException);
	class_entry->ce_flags |= ZEND_ACC_FINAL;
#endif

	return class_entry;
}

static zend_class_entry *register_class_Temporal_Exception_ParsingException(zend_class_entry *class_entry_Temporal_TemporalException)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Temporal\\Exception", "ParsingException", NULL);
#if (PHP_VERSION_ID >= 80400)
	class_entry = zend_register_internal_class_with_flags(&ce, class_entry_Temporal_TemporalException, ZEND_ACC_FINAL);
#else
	class_entry = zend_register_internal_class_ex(&ce, class_entry_Temporal_TemporalException);
	class_entry->ce_flags |= ZEND_ACC_FINAL;
#endif

	return class_entry;
}

static zend_class_entry *register_class_Temporal_Exception_ValueOutOfRangeException(zend_class_entry *class_entry_Temporal_TemporalException)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Temporal\\Exception", "ValueOutOfRangeException", NULL);
#if (PHP_VERSION_ID >= 80400)
	class_entry = zend_register_internal_class_with_flags(&ce, class_entry_Temporal_TemporalException, ZEND_ACC_FINAL);
#else
	class_entry = zend_register_internal_class_ex(&ce, class_entry_Temporal_TemporalException);
	class_entry->ce_flags |= ZEND_ACC_FINAL;
#endif

	return class_entry;
}

static zend_class_entry *register_class_Temporal_Exception_UnknownTimeZoneException(zend_class_entry *class_entry_Temporal_TemporalException)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Temporal\\Exception", "UnknownTimeZoneException", NULL);
#if (PHP_VERSION_ID >= 80400)
	class_entry = zend_register_internal_class_with_flags(&ce, class_entry_Temporal_TemporalException, ZEND_ACC_FINAL);
#else
	class_entry = zend_register_internal_class_ex(&ce, class_entry_Temporal_TemporalException);
	class_entry->ce_flags |= ZEND_ACC_FINAL;
#endif

	return class_entry;
}
