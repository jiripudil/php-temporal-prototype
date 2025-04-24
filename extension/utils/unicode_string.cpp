#include <php.h>
#include <unicode/unistr.h>
#include <unicode/ustring.h>

using icu::UnicodeString;

int u_stringFromChar(UnicodeString &ret, const char *str, size_t str_len, UErrorCode *status) {
	int32_t capacity = (int32_t) str_len + 1;

	UChar *utf16 = ret.getBuffer(capacity);
	int32_t utf16_len = 0;
	*status = U_ZERO_ERROR;
	u_strFromUTF8WithSub(utf16, ret.getCapacity(), &utf16_len, str, str_len, U_SENTINEL, NULL, status);
	ret.releaseBuffer(utf16_len);
	if (U_FAILURE(*status)) {
		ret.setToBogus();
		return 0;
	}

	return 1;
}

zend_string *u_charFromString(const UnicodeString &from, UErrorCode *status) {
	zend_string *u8res;

	if (from.isBogus()) {
		return NULL;
	}

	int32_t capacity = from.length() * 3;

	if (from.isEmpty()) {
		return ZSTR_EMPTY_ALLOC();
	}

	u8res = zend_string_alloc(capacity, 0);

	const UChar *utf16buf = from.getBuffer();
	int32_t actual_len;
	u_strToUTF8WithSub(ZSTR_VAL(u8res), capacity, &actual_len, utf16buf, from.length(), U_SENTINEL, NULL, status);
	if (U_FAILURE(*status)) {
		zend_string_release(u8res);
		return NULL;
	}

	u8res = zend_string_truncate(u8res, actual_len, 0);

	return u8res;
}
