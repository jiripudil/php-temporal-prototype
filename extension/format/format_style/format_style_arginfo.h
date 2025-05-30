/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 9a4a9d98665668a68736baae6d0e6af5899b901f */

static zend_class_entry *register_class_Temporal_Format_FormatStyle(void)
{
	zend_class_entry *class_entry = zend_register_internal_enum("Temporal\\Format\\FormatStyle", IS_UNDEF, NULL);

	zend_enum_add_case_cstr(class_entry, "FULL", NULL);

	zend_enum_add_case_cstr(class_entry, "LONG", NULL);

	zend_enum_add_case_cstr(class_entry, "MEDIUM", NULL);

	zend_enum_add_case_cstr(class_entry, "SHORT", NULL);

	return class_entry;
}
