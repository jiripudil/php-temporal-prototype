<?php

declare(strict_types=1);

namespace Temporal\Tests;

use PHPUnit\Framework\TestCase;
use Temporal\Duration;
use Temporal\Instant;
use Temporal\LocalDate;
use Temporal\LocalDateTime;
use Temporal\LocalTime;
use Temporal\MonthDay;
use Temporal\Period;
use Temporal\TimeZoneOffset;
use Temporal\YearMonth;
use Temporal\YearWeek;
use Temporal\ZonedDateTime;

abstract class TemporalTestCase extends TestCase
{
	protected static function assertDuration(Duration $duration, int $expectedSeconds, int $expectedNanos = 0): void
	{
		self::assertSame($expectedSeconds, $duration->getSeconds());
		self::assertSame($expectedNanos, $duration->getNanos());
	}

	protected static function assertInstant(Instant $instant, int $expectedEpochSecond, int $expectedNanos = 0): void
	{
		self::assertSame($expectedEpochSecond, $instant->getEpochSecond());
		self::assertSame($expectedNanos, $instant->getNano());
	}

	protected static function assertLocalDate(LocalDate $date, int $expectedYear, int $expectedMonth, int $expectedDay): void
	{
		self::assertSame($expectedYear, $date->getYear());
		self::assertSame($expectedMonth, $date->getMonth());
		self::assertSame($expectedDay, $date->getDayOfMonth());
	}

	protected static function assertLocalTime(LocalTime $time, int $expectedHour, int $expectedMinute, int $expectedSecond = 0, int $expectedNano = 0): void
	{
		self::assertSame($expectedHour, $time->getHour());
		self::assertSame($expectedMinute, $time->getMinute());
		self::assertSame($expectedSecond, $time->getSecond());
		self::assertSame($expectedNano, $time->getNano());
	}

	protected static function assertLocalDateTime(LocalDateTime $dateTime, int $expectedYear, int $expectedMonth, int $expectedDay, int $expectedHour, int $expectedMinute, int $expectedSecond = 0, int $expectedNano = 0): void
	{
		self::assertSame($expectedYear, $dateTime->getYear());
		self::assertSame($expectedMonth, $dateTime->getMonth());
		self::assertSame($expectedDay, $dateTime->getDayOfMonth());
		self::assertSame($expectedHour, $dateTime->getHour());
		self::assertSame($expectedMinute, $dateTime->getMinute());
		self::assertSame($expectedSecond, $dateTime->getSecond());
		self::assertSame($expectedNano, $dateTime->getNano());
	}

	protected static function assertMonthDay(MonthDay $monthDay, int $expectedMonth, int $expectedDay): void
	{
		self::assertSame($expectedMonth, $monthDay->getMonth());
		self::assertSame($expectedDay, $monthDay->getDayOfMonth());
	}

	protected static function assertPeriod(Period $period, int $expectedYears, int $expectedMonths, int $expectedDays): void
	{
		self::assertSame($expectedYears, $period->getYears());
		self::assertSame($expectedMonths, $period->getMonths());
		self::assertSame($expectedDays, $period->getDays());
	}

	protected static function assertTimeZoneOffset(TimeZoneOffset $offset, int $expectedTotalSeconds): void
	{
		self::assertSame($expectedTotalSeconds, $offset->getTotalSeconds());
	}

	protected static function assertYearMonth(YearMonth $yearMonth, int $expectedYear, int $expectedMonth): void
	{
		self::assertSame($expectedYear, $yearMonth->getYear());
		self::assertSame($expectedMonth, $yearMonth->getMonth());
	}

	protected static function assertYearWeek(YearWeek $yearWeek, int $expectedYear, int $expectedWeek): void
	{
		self::assertSame($expectedYear, $yearWeek->getYear());
		self::assertSame($expectedWeek, $yearWeek->getWeek());
	}

	protected static function assertZonedDateTime(ZonedDateTime $zonedDateTime, int $expectedYear, int $expectedMonth, int $expectedDay, int $expectedHour, int $expectedMinute, int $expectedSecond = 0, int $expectedNano = 0): void
	{
		self::assertSame($expectedYear, $zonedDateTime->getYear());
		self::assertSame($expectedMonth, $zonedDateTime->getMonth());
		self::assertSame($expectedDay, $zonedDateTime->getDayOfMonth());
		self::assertSame($expectedHour, $zonedDateTime->getHour());
		self::assertSame($expectedMinute, $zonedDateTime->getMinute());
		self::assertSame($expectedSecond, $zonedDateTime->getSecond());
		self::assertSame($expectedNano, $zonedDateTime->getNano());
	}
}
