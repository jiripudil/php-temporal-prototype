/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 5d4c5ce88495e7c3a73720c106a014bf76cfbb66 */

static zend_class_entry *register_class_Temporal_TemporalException(zend_class_entry *class_entry_Exception)
{
	zend_class_entry ce, *class_entry;

	INIT_NS_CLASS_ENTRY(ce, "Temporal", "TemporalException", NULL);
#if (PHP_VERSION_ID >= 80400)
	class_entry = zend_register_internal_class_with_flags(&ce, class_entry_Exception, ZEND_ACC_FINAL);
#else
	class_entry = zend_register_internal_class_ex(&ce, class_entry_Exception);
	class_entry->ce_flags |= ZEND_ACC_FINAL;
#endif

	return class_entry;
}
