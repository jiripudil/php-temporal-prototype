#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>
#include <ext/standard/info.h>
#include <unicode/ucal.h>
#include <unicode/uvernum.h>
#include "clock/clock_ce.h"
#include "clock/fixed/fixed_clock_ce.h"
#include "clock/system/system_clock_ce.h"
#include "duration/duration_ce.h"
#include "exception/exception_ce.h"
#include "format/format_style/format_style_ce.h"
#include "format/formatter_ce.h"
#include "instant/instant_ce.h"
#include "local_date/local_date_ce.h"
#include "local_date_time/local_date_time_ce.h"
#include "local_time/local_time_ce.h"
#include "month_day/month_day_ce.h"
#include "period/period_ce.h"
#include "php_temporal.h"
#include "time_zone/time_zone_ce.h"
#include "time_zone/offset/time_zone_offset_ce.h"
#include "time_zone/region/time_zone_region_ce.h"
#include "year_month/year_month_ce.h"
#include "year_week/year_week_ce.h"
#include "zoned_date_time/zoned_date_time_ce.h"

PHP_MINIT_FUNCTION(temporal) {
	php_temporal_register_clock_ce();
	php_temporal_register_clock_fixed_ce();
	php_temporal_register_clock_system_ce();
	php_temporal_register_duration_ce();
	php_temporal_register_exception_ce();
	php_temporal_register_format_style_ce();
	php_temporal_register_formatter_ce();
	php_temporal_register_instant_ce();
	php_temporal_register_local_date_ce();
	php_temporal_register_local_date_time_ce();
	php_temporal_register_local_time_ce();
	php_temporal_register_month_day_ce();
	php_temporal_register_period_ce();
	php_temporal_register_time_zone_ce();
	php_temporal_register_time_zone_region_ce();
	php_temporal_register_time_zone_offset_ce();
	php_temporal_register_year_month_ce();
	php_temporal_register_year_week_ce();
	php_temporal_register_zoned_date_time_ce();

	return SUCCESS;
}

PHP_MINFO_FUNCTION(temporal) {
	UErrorCode status = U_ZERO_ERROR;
	const char *tzdb_version = ucal_getTZDataVersion(&status);
	if (U_FAILURE(status)) {
		tzdb_version = "Unknown";
	}

	php_info_print_table_start();
	php_info_print_table_row(2, "temporal support", "enabled");
	php_info_print_table_row(2, "temporal version", PHP_TEMPORAL_VERSION);
	php_info_print_table_row(2, "ICU version", U_ICU_VERSION);
	php_info_print_table_row(2, "TZDB version", tzdb_version);
	php_info_print_table_end();
}

static const zend_module_dep temporal_module_deps[] = {
	ZEND_MOD_REQUIRED("spl")
	ZEND_MOD_REQUIRED("date")
	ZEND_MOD_REQUIRED("json")
	ZEND_MOD_END
};

zend_module_entry temporal_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	temporal_module_deps,
	PHP_TEMPORAL_EXTNAME,
	NULL,
	PHP_MINIT(temporal),
	NULL,
	NULL,
	NULL,
	PHP_MINFO(temporal),
	PHP_TEMPORAL_VERSION,
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_TEMPORAL
ZEND_GET_MODULE(temporal)
#endif
