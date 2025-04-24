#include "formatter.h"
#include <unicode/datefmt.h>
#include <unicode/schriter.h>
#include <unicode/smpdtfmt.h>
#include <unicode/timezone.h>
#include <unicode/udat.h>
#include <unicode/unistr.h>
#include "utils/unicode_string.h"

using icu::DateFormat;
using icu::DateTimePatternGenerator;
using icu::Locale;
using icu::SimpleDateFormat;
using icu::StringCharacterIterator;
using icu::TimeZone;
using icu::UnicodeString;

extern "C" {
	UDateFormat *temporal_formatter_of_pattern(const char *pattern, const char *locale, UErrorCode *status) {
		UnicodeString u_pattern{};
		u_stringFromChar(u_pattern, pattern, strlen(pattern), status);

		const auto u_locale = Locale::createFromName(locale);
		return reinterpret_cast<UDateFormat *>(new SimpleDateFormat(u_pattern, u_locale, *status));
	}

	UDateFormat *temporal_formatter_of_localized_pattern(const char *skeleton, const char *locale, UErrorCode *status) {
		UnicodeString u_skeleton{};
		u_stringFromChar(u_skeleton, skeleton, strlen(skeleton), status);

		const auto u_locale = Locale::createFromName(locale);
		return reinterpret_cast<UDateFormat *>(SimpleDateFormat::createInstanceForSkeleton(u_skeleton, u_locale, *status));
	}

	UDateFormat *temporal_formatter_of_date(UDateFormatStyle style, const char *locale) {
		auto u_locale = Locale::createFromName(locale);
		return reinterpret_cast<UDateFormat *>(SimpleDateFormat::createDateInstance(static_cast<DateFormat::EStyle>(style), u_locale));
	}

	UDateFormat *temporal_formatter_of_time(UDateFormatStyle style, const char *locale) {
		auto u_locale = Locale::createFromName(locale);
		return reinterpret_cast<UDateFormat *>(SimpleDateFormat::createTimeInstance(static_cast<DateFormat::EStyle>(style), u_locale));
	}

	UDateFormat *temporal_formatter_of_date_time(UDateFormatStyle date_style, UDateFormatStyle time_style, const char *locale) {
		auto u_locale = Locale::createFromName(locale);
		return reinterpret_cast<UDateFormat *>(SimpleDateFormat::createDateTimeInstance(static_cast<DateFormat::EStyle>(date_style), static_cast<DateFormat::EStyle>(time_style), u_locale));
	}

	bool temporal_formatter_is_valid_pattern(UDateFormat *fmt, int field_mask) {
		const auto df = reinterpret_cast<SimpleDateFormat *>(fmt);

		UnicodeString pattern{};
		df->toPattern(pattern);

		bool escaped = false;

		StringCharacterIterator iterator(pattern);
		while (iterator.hasNext()) {
			auto code = iterator.next32();

			if (code == '\'') {
				escaped = !escaped;
				continue;
			}

			if (escaped) {
				continue;
			}

			// only a-z and A-Z are reserved for pattern fields
			if (code < 'A' || code > 'z' || (code < 'a' && code > 'Z')) {
				continue;
			}

			switch (code) {
				case 'G':
				case 'y':
				case 'Y':
				case 'u':
				case 'U':
				case 'r':
				case 'Q':
				case 'q':
				case 'M':
				case 'L':
				case 'l':
				case 'w':
				case 'W':
				case 'd':
				case 'D':
				case 'F':
				case 'g':
				case 'E':
				case 'e':
				case 'c':
					if ((field_mask & TEMPORAL_FORMATTER_FIELD_MASK_DATE) == 0) {
						return false;
					}
					break;

				case 'a':
				case 'b':
				case 'B':
				case 'h':
				case 'H':
				case 'K':
				case 'k':
				case 'm':
				case 's':
				case 'S':
				case 'A':
					if ((field_mask & TEMPORAL_FORMATTER_FIELD_MASK_TIME) == 0) {
						return false;
					}
					break;

				case 'z':
				case 'Z':
				case 'O':
				case 'v':
				case 'V':
				case 'X':
				case 'x':
					if ((field_mask & TEMPORAL_FORMATTER_FIELD_MASK_TIMEZONE) == 0) {
						return false;
					}
					break;

				default:
					return false;
			}
		}

		return true;
	}

	zend_string *temporal_formatter_format(UDateFormat *fmt, UDate timestamp, UTimeZone *tz) {
		const auto df = reinterpret_cast<SimpleDateFormat *>(fmt);
		auto *time_zone = reinterpret_cast<TimeZone *>(tz);

		if (time_zone == nullptr) {
			time_zone = TimeZone::createTimeZone(UnicodeString("UTC", 3, US_INV));
		} else {
			time_zone = time_zone->clone();
		}

		df->adoptTimeZone(time_zone);

		UnicodeString result{};
		df->format(timestamp, result);

		UErrorCode status = U_ZERO_ERROR;
		zend_string *result_zend_string = u_charFromString(result, &status);
		if (U_FAILURE(status)) {
			return nullptr;
		}

		return result_zend_string;
	}

	void temporal_formatter_free(UDateFormat *fmt) {
		delete reinterpret_cast<SimpleDateFormat *>(fmt);
	}
}
