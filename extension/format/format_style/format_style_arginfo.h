/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: d0786f9b6fcd9e0f4f7b0f8df25e23ae1be5483b */

static zend_class_entry *register_class_Temporal_Format_FormatStyle(void)
{
	zend_class_entry *class_entry = zend_register_internal_enum("Temporal\\Format\\FormatStyle", IS_UNDEF, NULL);

	zend_enum_add_case_cstr(class_entry, "FULL", NULL);

	zend_enum_add_case_cstr(class_entry, "LONG", NULL);

	zend_enum_add_case_cstr(class_entry, "MEDIUM", NULL);

	zend_enum_add_case_cstr(class_entry, "SHORT", NULL);

	return class_entry;
}
