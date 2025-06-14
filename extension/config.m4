dnl config.m4 for extension temporal

PHP_ARG_ENABLE(
    [temporal],
    [whether to enable temporal extension],
    [AS_HELP_STRING([--enable-temporal], [Enable temporal extension])]
)

AH_TEMPLATE([PCRE2_CODE_UNIT_WIDTH], [Number of bits in non-UTF mode for PCRE library.])

if test "$PHP_TEMPORAL" != "no"; then
    PHP_SETUP_ICU([TEMPORAL_SHARED_LIBADD])
    PHP_SUBST([TEMPORAL_SHARED_LIBADD])

    PKG_CHECK_MODULES([PCRE2], [libpcre2-8 >= 10.30])

    PHP_EVAL_INCLINE([$PCRE2_CFLAGS])
    PHP_EVAL_LIBLINE([$PCRE2_LIBS])
    AC_DEFINE([PCRE2_CODE_UNIT_WIDTH], [8])

    TEMPORAL_COMMON_FLAGS="$ICU_CFLAGS -D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1"

    PHP_NEW_EXTENSION(
        [temporal],
        m4_normalize([
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
            format/format_style/format_style.c
            format/format_style/format_style_ce.c
            format/formatter_ce.c
            format/formatter_handlers.c
            format/formatter_obj.c
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
            time_zone/time_zone_ce.c
            time_zone/time_zone_handlers.c
            time_zone/time_zone_obj.c
            utils/parse_iso_result.c
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
        ]),
        [$ext_shared],,
        [$TEMPORAL_COMMON_FLAGS],
        [cxx]
    )

    PHP_TEMPORAL_CXX_SOURCES="format/formatter.cpp \
        time_zone/time_zone.cpp \
        utils/unicode_string.cpp"

    PHP_REQUIRE_CXX()

    AC_MSG_CHECKING([if temporal requires -std=c++17])
    AS_IF([$PKG_CONFIG icu-uc --atleast-version=74],[
        AC_MSG_RESULT([yes])
        PHP_CXX_COMPILE_STDCXX([17], [mandatory], [PHP_TEMPORAL_STDCXX])
    ],[
        AC_MSG_RESULT([no])
        PHP_CXX_COMPILE_STDCXX([11], [mandatory], [PHP_TEMPORAL_STDCXX])
    ])

    PHP_TEMPORAL_CXX_FLAGS="$TEMPORAL_COMMON_FLAGS $PHP_TEMPORAL_STDCXX $ICU_CXXFLAGS"

    AS_VAR_IF([ext_shared], [no],
        [PHP_ADD_SOURCES([$ext_dir],
            [$PHP_TEMPORAL_CXX_SOURCES],
            [$PHP_TEMPORAL_CXX_FLAGS]
        )],
        [PHP_ADD_SOURCES_X([$ext_dir],
            [$PHP_TEMPORAL_CXX_SOURCES],
            [$PHP_TEMPORAL_CXX_FLAGS],
            [shared_objects_temporal],
            [yes]
        )]
    )

    PHP_ADD_BUILD_DIR([
        $ext_builddir/clock
        $ext_builddir/clock/fixed
        $ext_builddir/clock/system
        $ext_builddir/duration
        $ext_builddir/exception
        $ext_builddir/format
        $ext_builddir/format/format_style
        $ext_builddir/instant
        $ext_builddir/local_date
        $ext_builddir/local_date_time
        $ext_builddir/local_time
        $ext_builddir/month_day
        $ext_builddir/period
        $ext_builddir/time_zone
        $ext_builddir/time_zone/offset
        $ext_builddir/time_zone/region
        $ext_builddir/utils
        $ext_builddir/year_month
        $ext_builddir/year_week
        $ext_builddir/zoned_date_time
    ])

    PHP_ADD_EXTENSION_DEP(temporal, spl)
    PHP_ADD_EXTENSION_DEP(temporal, date)
    PHP_ADD_EXTENSION_DEP(temporal, json)

    PHP_INSTALL_HEADERS([ext/temporal], [php_temporal.h])
fi
