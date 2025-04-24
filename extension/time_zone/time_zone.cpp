#include "time_zone.h"
#include <php.h>
#include <unicode/calendar.h>
#include <unicode/timezone.h>
#include <unicode/unistr.h>
#include "instant/instant.h"
#include "local_date_time/local_date_time.h"
#include "time_zone/offset/time_zone_offset.h"
#include "time_zone/region/time_zone_region.h"
#include "utils/unicode_string.h"

using icu::Calendar;
using icu::TimeZone;
using icu::UnicodeString;

extern "C" {
	temporal_time_zone_t *temporal_time_zone_of_offset(temporal_time_zone_offset_t *offset) {
		if (offset->total_seconds == 0) {
			auto *time_zone = new temporal_time_zone_t();

			time_zone->type = TEMPORAL_TIME_ZONE_TYPE_OFFSET;
			time_zone->offset = offset;
			time_zone->time_zone = reinterpret_cast<UTimeZone *>(TimeZone::createTimeZone(UnicodeString("UTC", 3, US_INV)));
			return time_zone;
		}

		zend_string *id = temporal_time_zone_offset_id(offset);

		UErrorCode status{};
		UnicodeString u_id{};
		u_stringFromChar(u_id, ZSTR_VAL(id), ZSTR_LEN(id), &status);

		zend_string_release(id);

		u_id.insert(0, UnicodeString("GMT", 3, US_INV));

		auto *time_zone = new temporal_time_zone_t;
		time_zone->type = TEMPORAL_TIME_ZONE_TYPE_OFFSET;
		time_zone->offset = offset;
		time_zone->time_zone = reinterpret_cast<UTimeZone *>(TimeZone::createTimeZone(u_id));
		return time_zone;
	}

	temporal_time_zone_t *temporal_time_zone_of_region(temporal_time_zone_region_t *region) {
		const std::string id_s(ZSTR_VAL(region->id));
		if (id_s == "Z" || id_s == "z" || id_s[0] == '+' || id_s[0] == '-') {
			return nullptr;
		}

		UErrorCode status{};
		UnicodeString u_id{};
		u_stringFromChar(u_id, ZSTR_VAL(region->id), ZSTR_LEN(region->id), &status);

		TimeZone *u_time_zone = TimeZone::createTimeZone(u_id);
		if (*u_time_zone == TimeZone::getUnknown()) {
			delete u_time_zone;
			return nullptr;
		}

		auto *time_zone = new temporal_time_zone_t();

		time_zone->type = TEMPORAL_TIME_ZONE_TYPE_REGION;
		time_zone->region = region;
		time_zone->time_zone = reinterpret_cast<UTimeZone *>(u_time_zone);
		return time_zone;
	}

	temporal_time_zone_t *temporal_time_zone_clone(temporal_time_zone_t *time_zone) {
		if (IS_TEMPORAL_TIME_ZONE_OFFSET(time_zone)) {
			return temporal_time_zone_of_offset(temporal_time_zone_offset_clone(time_zone->offset));
		}

		return temporal_time_zone_of_region(temporal_time_zone_region_clone(time_zone->region));
	}

	temporal_time_zone_t *temporal_time_zone_parse_iso(const char *input) {
		if (strlen(input) == 1 && (input[0] == 'Z' || input[0] == 'z')) {
			temporal_time_zone_offset_t *offset = temporal_time_zone_offset_utc();
			return temporal_time_zone_of_offset(offset);
		}

		if (input[0] == '+' || input[0] == '-') {
			temporal_time_zone_offset_t *offset = temporal_time_zone_offset_parse_iso(input);
			if (offset == nullptr) {
				return nullptr;
			}

			return temporal_time_zone_of_offset(offset);
		}

		temporal_time_zone_region_t *region = temporal_time_zone_region_of(input);
		return temporal_time_zone_of_region(region);
	}

	zend_string *temporal_time_zone_get_id(temporal_time_zone_t *tz) {
		if (IS_TEMPORAL_TIME_ZONE_OFFSET(tz)) {
			return temporal_time_zone_offset_id(tz->offset);
		}

		return zend_string_copy(tz->region->id);
	}

	zend_long temporal_time_zone_get_offset(temporal_time_zone_t *tz, temporal_instant_t *instant) {
		if (IS_TEMPORAL_TIME_ZONE_OFFSET(tz)) {
			return tz->offset->total_seconds;
		}

		UDate epoch_millis = static_cast<UDate>(instant->epoch_second) * 1000 + static_cast<UDate>(instant->nano) / 1000000;

		const auto u_time_zone = reinterpret_cast<TimeZone *>(tz->time_zone);

		int32_t raw_offset, dst_offset;
		UErrorCode status{};
		u_time_zone->getOffset(epoch_millis, false, raw_offset, dst_offset, status);

		if (U_FAILURE(status)) {
			return 0; // TODO throw
		}

		return (raw_offset + dst_offset) / 1000;
	}

	temporal_local_date_time_t *temporal_time_zone_instant_to_local_date_time(temporal_time_zone_t *tz, temporal_instant_t *instant) {
		auto *u_time_zone = reinterpret_cast<TimeZone *>(tz->time_zone);

		UErrorCode status = UErrorCode();
		auto calendar = Calendar::createInstance(u_time_zone->clone(), status);
		if (U_FAILURE(status)) {
			return nullptr;
		}

		UDate timestamp = static_cast<UDate>(instant->epoch_second) * 1000 + static_cast<UDate>(instant->nano) / 1000000;
		calendar->setTime(timestamp, status);
		if (U_FAILURE(status)) {
			return nullptr;
		}

		zend_long year = calendar->get(UCAL_YEAR, status);
		zend_long month = calendar->get(UCAL_MONTH, status) + 1;
		zend_long day = calendar->get(UCAL_DATE, status);
		zend_long hour = calendar->get(UCAL_HOUR_OF_DAY, status);
		zend_long minute = calendar->get(UCAL_MINUTE, status);
		zend_long second = calendar->get(UCAL_SECOND, status);

		delete calendar;

		if (U_FAILURE(status)) {
			return nullptr;
		}

		return temporal_local_date_time_of(year, month, day, hour, minute, second, instant->nano);
	}

	temporal_instant_t *temporal_time_zone_local_date_time_to_instant(temporal_time_zone_t *tz, temporal_local_date_time_t *local_date_time) {
		auto u_time_zone = reinterpret_cast<TimeZone *>(tz->time_zone);

		UErrorCode status = UErrorCode();
		auto calendar = Calendar::createInstance(u_time_zone->clone(), status);
		if (U_FAILURE(status)) {
			return nullptr;
		}

		calendar->set(
			local_date_time->date->year,
			local_date_time->date->month - 1,
			local_date_time->date->day,
			local_date_time->time->hour,
			local_date_time->time->minute,
			local_date_time->time->second
		);

		const UDate timestamp = calendar->getTime(status);

		delete calendar;

		if (U_FAILURE(status)) {
			return nullptr;
		}

		return temporal_instant_of(timestamp / 1000, local_date_time->time->nano);
	}

	void temporal_time_zone_free(temporal_time_zone_t *tz) {
		if (IS_TEMPORAL_TIME_ZONE_OFFSET(tz)) {
			temporal_time_zone_offset_free(tz->offset);
		} else {
			temporal_time_zone_region_free(tz->region);
		}

		auto *u_time_zone = reinterpret_cast<TimeZone *>(tz->time_zone);
		delete u_time_zone;

		delete tz;
	}
}
