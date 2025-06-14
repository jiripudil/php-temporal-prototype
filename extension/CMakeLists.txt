cmake_minimum_required(VERSION 3.10)
project(php_temporal)

set(CMAKE_CXX_STANDARD 17)

# locate php include directory
execute_process(
    COMMAND php-config --include-dir
    OUTPUT_VARIABLE PHP_SOURCE
)
string(REGEX REPLACE "\n$" "" PHP_SOURCE "${PHP_SOURCE}")

# add PHP include directories
include_directories(${PHP_SOURCE})
include_directories(${PHP_SOURCE}/main)
include_directories(${PHP_SOURCE}/Zend)
include_directories(${PHP_SOURCE}/TSRM)

find_package(PkgConfig)

pkg_check_modules(ICU REQUIRED icu-uc>=50.1 icu-io icu-i18n)
pkg_get_variable(ICU_INCLUDE_DIR icu-uc includedir)
include_directories(${ICU_INCLUDE_DIR})

pkg_check_modules(PCRE2 REQUIRED libpcre2-8>=10.30)
pkg_get_variable(PCRE2_INCLUDE_DIR libpcre2-8 includedir)
include_directories(${PCRE2_INCLUDE_DIR})

include_directories(${PROJECT_SOURCE_DIR})

set(SOURCE_FILES
        php_temporal.h
        temporal.c

        clock/fixed/fixed_clock_ce.c
        clock/system/system_clock.c
        clock/system/system_clock_ce.c
        clock/clock_ce.c
        clock/clock_obj.c

        duration/duration.c
        duration/duration_ce.c
        duration/duration_handlers.c
        duration/duration_obj.c

        exception/exception_ce.c
        exception/exception_obj.c

        format/formatter.cpp
        format/formatter_ce.c
        format/formatter_handlers.c
        format/formatter_obj.c
        format/format_style/format_style.c
        format/format_style/format_style_ce.c

        instant/instant.c
        instant/instant_ce.c
        instant/instant_handlers.c
        instant/instant_obj.c

        local_date/local_date.c
        local_date/local_date_ce.c
        local_date/local_date_handlers.c
        local_date/local_date_obj.c

        local_date_time/local_date_time.c
        local_date_time/local_date_time_ce.c
        local_date_time/local_date_time_handlers.c
        local_date_time/local_date_time_obj.c

        local_time/local_time.c
        local_time/local_time_ce.c
        local_time/local_time_handlers.c
        local_time/local_time_obj.c

        month_day/month_day.c
        month_day/month_day_ce.c
        month_day/month_day_handlers.c
        month_day/month_day_obj.c

        period/period.c
        period/period_ce.c
        period/period_handlers.c
        period/period_obj.c

        time_zone/offset/time_zone_offset.c
        time_zone/offset/time_zone_offset_ce.c
        time_zone/region/time_zone_region.c
        time_zone/region/time_zone_region_ce.c
        time_zone/time_zone.cpp
        time_zone/time_zone_ce.c
        time_zone/time_zone_handlers.c
        time_zone/time_zone_obj.c

        utils/parse_iso_result.c
        utils/unicode_string.cpp

        year_month/year_month.c
        year_month/year_month_ce.c
        year_month/year_month_handlers.c
        year_month/year_month_obj.c

        year_week/year_week.c
        year_week/year_week_ce.c
        year_week/year_week_handlers.c
        year_week/year_week_obj.c

        zoned_date_time/zoned_date_time.c
        zoned_date_time/zoned_date_time_ce.c
        zoned_date_time/zoned_date_time_handlers.c
        zoned_date_time/zoned_date_time_obj.c
)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/config.h")
    add_definitions(-DHAVE_CONFIG_H)
    set(SOURCE_FILES "${SOURCE_FILES};config.h")
endif()

add_custom_target(configure
    COMMAND phpize && ./configure
    DEPENDS ${SOURCE_FILES}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_custom_target(make
    COMMAND make && make install
    DEPENDS ${SOURCE_FILES}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_dependencies(make configure)

add_library(___ EXCLUDE_FROM_ALL ${SOURCE_FILES})
