<?php

declare(strict_types=1);

namespace Temporal\Tests;

use DateTimeImmutable;
use PHPUnit\Framework\Attributes\DataProvider;
use PHPUnit\Framework\Attributes\TestWith;
use Temporal\Clock\FixedClock;
use Temporal\Duration;
use Temporal\Format\DateTimeFormatter;
use Temporal\Format\FormatStyle;
use Temporal\Instant;
use Temporal\LocalDate;
use Temporal\LocalDateTime;
use Temporal\LocalTime;
use Temporal\Period;
use Temporal\TemporalException;
use Temporal\TimeZoneOffset;

final class LocalDateTimeTest extends TemporalTestCase
{
	public function testOf(): void
	{
		$dateTime = LocalDateTime::of(1970, 1, 1, 12, 30, 59, 123_456_789);
		self::assertLocalDateTime($dateTime, 1970, 1, 1, 12, 30, 59, 123_456_789);
	}

	#[TestWith([PHP_INT_MAX, 1, 1, 0, 0, 0, 0])]
	#[TestWith([2025, 0, 1, 0, 0, 0, 0])]
	#[TestWith([2025, 1, 0, 0, 0, 0, 0])]
	#[TestWith([2025, 16, 1, 0, 0, 0, 0])]
	#[TestWith([2025, 12, 40, 0, 0, 0, 0])]
	#[TestWith([2025, 2, 29, 0, 0, 0, 0])]
	#[TestWith([1970, 1, 1, -1, 0, 0])]
	#[TestWith([1970, 1, 1, 24, 0, 0])]
	#[TestWith([1970, 1, 1, 24, 0, 0])]
	#[TestWith([1970, 1, 1, 12, -1, 0])]
	#[TestWith([1970, 1, 1, 12, 60, 0])]
	#[TestWith([1970, 1, 1, 12, 30, -1])]
	#[TestWith([1970, 1, 1, 12, 30, 60])]
	#[TestWith([1970, 1, 1, 12, 30, 59, -1])]
	#[TestWith([1970, 1, 1, 12, 30, 59, 1_000_000_000])]
	public function testInvalidOf(int $year, int $month, int $day, int $hour, int $minute, int $second, int $nano = 0): void
	{
		$this->expectException(TemporalException::class);
		LocalDateTime::of($year, $month, $day, $hour, $minute, $second, $nano);
	}

	public function testOfDateTime(): void
	{
		$date = LocalDate::of(1970, 1, 1);
		$time = LocalTime::of(12, 30, 59, 123_456_789);

		$dateTime = LocalDateTime::ofDateTime($date, $time);
		self::assertLocalDateTime($dateTime, 1970, 1, 1, 12, 30, 59, 123_456_789);
	}

	public function testNow(): void
	{
		$clock = new FixedClock(Instant::epoch());

		$dateTime = LocalDateTime::now(TimeZoneOffset::utc(), $clock);
		self::assertLocalDateTime($dateTime, 1970, 1, 1, 0, 0);

		$dateTime = LocalDateTime::now(TimeZoneOffset::of(0, -30), $clock);
		self::assertLocalDateTime($dateTime, 1969, 12, 31, 23, 30);

		$dateTime = LocalDateTime::now(TimeZoneOffset::of(1, 45), $clock);
		self::assertLocalDateTime($dateTime, 1970, 1, 1, 1, 45);
	}

	public static function provideParseData(): iterable
	{
		yield ['1970-01-01T00:00', 1970, 1, 1, 0, 0];
		yield ['1970-01-01T12:30', 1970, 1, 1, 12, 30];
		yield ['1970-01-01T12:30:00', 1970, 1, 1, 12, 30];
		yield ['1970-01-01T12:30:00.000000', 1970, 1, 1, 12, 30];
		yield ['1970-01-01T12:30:59', 1970, 1, 1, 12, 30, 59];
		yield ['1970-01-01T12:30:59.000000001', 1970, 1, 1, 12, 30, 59, 1];
	}

	#[DataProvider('provideParseData')]
	public function testParse(string $text, int $expectedYear, int $expectedMonth, int $expectedDay, int $expectedHour, int $expectedMinute, int $expectedSecond = 0, int $expectedNano = 0): void
	{
		$dateTime = LocalDateTime::parse($text);
		self::assertLocalDateTime($dateTime, $expectedYear, $expectedMonth, $expectedDay, $expectedHour, $expectedMinute, $expectedSecond, $expectedNano);
	}

	public function testMin(): void
	{
		$min = LocalDateTime::min();
		self::assertLocalDateTime($min, -999_999, 1, 1, 0, 0);
	}

	public function testMax(): void
	{
		$max = LocalDateTime::max();
		self::assertLocalDateTime($max, 999_999, 12, 31, 23, 59, 59, 999_999_999);
	}

	public static function providePlusPeriodData(): iterable
	{
		yield [LocalDateTime::of(1970, 1, 1, 12, 30), Period::ofDays(1), 1970, 1, 2, 12, 30];
		yield [LocalDateTime::of(1970, 1, 1, 12, 30), Period::ofMonths(1), 1970, 2, 1, 12, 30];
		yield [LocalDateTime::of(1970, 1, 1, 12, 30), Period::ofYears(1), 1971, 1, 1, 12, 30];
	}

	#[DataProvider('providePlusPeriodData')]
	public function testPlusPeriod(LocalDateTime $dateTime, Period $period, int $expectedYear, int $expectedMonth, int $expectedDay, int $expectedHour, int $expectedMinute, int $expectedSecond = 0, int $expectedNano = 0): void
	{
		$result = $dateTime->plusPeriod($period);
		self::assertLocalDateTime($result, $expectedYear, $expectedMonth, $expectedDay, $expectedHour, $expectedMinute, $expectedSecond, $expectedNano);
	}

	public static function provideMinusPeriodData(): iterable
	{
		yield [LocalDateTime::of(1970, 1, 1, 12, 30), Period::ofDays(1), 1969, 12, 31, 12, 30];
		yield [LocalDateTime::of(1970, 1, 1, 12, 30), Period::ofMonths(1), 1969, 12, 1, 12, 30];
		yield [LocalDateTime::of(1970, 1, 1, 12, 30), Period::ofYears(1), 1969, 1, 1, 12, 30];
	}

	#[DataProvider('provideMinusPeriodData')]
	public function testMinusPeriod(LocalDateTime $dateTime, Period $period, int $expectedYear, int $expectedMonth, int $expectedDay, int $expectedHour, int $expectedMinute, int $expectedSecond = 0, int $expectedNano = 0): void
	{
		$result = $dateTime->minusPeriod($period);
		self::assertLocalDateTime($result, $expectedYear, $expectedMonth, $expectedDay, $expectedHour, $expectedMinute, $expectedSecond, $expectedNano);
	}

	public static function providePlusDurationData(): iterable
	{
		yield [LocalDateTime::of(1970, 1, 1, 12, 30), Duration::ofDays(1), 1970, 1, 2, 12, 30];
		yield [LocalDateTime::of(1970, 1, 1, 12, 30), Duration::ofHours(12), 1970, 1, 2, 0, 30];
		yield [LocalDateTime::of(1970, 1, 1, 12, 30), Duration::ofHours(6), 1970, 1, 1, 18, 30];
	}

	#[DataProvider('providePlusDurationData')]
	public function testPlusDuration(LocalDateTime $dateTime, Duration $duration, int $expectedYear, int $expectedMonth, int $expectedDay, int $expectedHour, int $expectedMinute, int $expectedSecond = 0, int $expectedNano = 0): void
	{
		$result = $dateTime->plusDuration($duration);
		self::assertLocalDateTime($result, $expectedYear, $expectedMonth, $expectedDay, $expectedHour, $expectedMinute, $expectedSecond, $expectedNano);
	}

	public static function provideMinusDurationData(): iterable
	{
		yield [LocalDateTime::of(1970, 1, 1, 12, 30), Duration::ofDays(1), 1969, 12, 31, 12, 30];
		yield [LocalDateTime::of(1970, 1, 1, 12, 30), Duration::ofHours(12), 1970, 1, 1, 0, 30];
		yield [LocalDateTime::of(1970, 1, 1, 12, 30), Duration::ofHours(14), 1969, 12, 31, 22, 30];
	}

	#[DataProvider('provideMinusDurationData')]
	public function testMinusDuration(LocalDateTime $dateTime, Duration $duration, int $expectedYear, int $expectedMonth, int $expectedDay, int $expectedHour, int $expectedMinute, int $expectedSecond = 0, int $expectedNano = 0): void
	{
		$result = $dateTime->minusDuration($duration);
		self::assertLocalDateTime($result, $expectedYear, $expectedMonth, $expectedDay, $expectedHour, $expectedMinute, $expectedSecond, $expectedNano);
	}

	public static function provideComparisonData(): iterable
	{
		yield [LocalDateTime::of(1970, 1, 1, 12, 30), LocalDateTime::of(1970, 1, 1, 12, 30), 0];
		yield [LocalDateTime::of(1970, 1, 2, 12, 30), LocalDateTime::of(1970, 1, 1, 12, 30), 1];
		yield [LocalDateTime::of(1970, 1, 1, 12, 30), LocalDateTime::of(1970, 1, 2, 12, 30), -1];
		yield [LocalDateTime::of(1970, 1, 1, 14, 30), LocalDateTime::of(1970, 1, 1, 12, 30), 1];
		yield [LocalDateTime::of(1970, 1, 1, 12, 30), LocalDateTime::of(1970, 1, 1, 14, 30), -1];
	}

	#[DataProvider('provideComparisonData')]
	public function testComparison(LocalDateTime $a, LocalDateTime $b, int $expectedResult): void
	{
		self::assertSame($expectedResult, $a->compareTo($b));
		self::assertSame(-$expectedResult, $b->compareTo($a));

		self::assertSame($expectedResult === 0, $a->isEqualTo($b));
		self::assertSame($expectedResult < 0, $a->isBefore($b));
		self::assertSame($expectedResult <= 0, $a->isBeforeOrEqualTo($b));
		self::assertSame($expectedResult > 0, $a->isAfter($b));
		self::assertSame($expectedResult >= 0, $a->isAfterOrEqualTo($b));
	}

	public function testToDateTime(): void
	{
		$dateTime = LocalDateTime::of(1970, 1, 1, 12, 30, 59, 123_456_789);

		$nativeDateTime = $dateTime->toDateTime();
		self::assertSame('1', $nativeDateTime->format('j'));
		self::assertSame('1', $nativeDateTime->format('n'));
		self::assertSame('1970', $nativeDateTime->format('Y'));
		self::assertSame('12', $nativeDateTime->format('H'));
		self::assertSame('30', $nativeDateTime->format('i'));
		self::assertSame('59', $nativeDateTime->format('s'));
		self::assertSame('123456', $nativeDateTime->format('u'));
	}

	public function testFromDateTime(): void
	{
		$dateTime = LocalDateTime::fromDateTime(new DateTimeImmutable('1970-01-01T12:30:59.123456Z'));
		self::assertLocalDateTime($dateTime, 1970, 1, 1, 12, 30, 59, 123_456_000);

		$dateTime = LocalDateTime::fromDateTime(new DateTimeImmutable('1970-01-01T12:30:59.123456+11:00'));
		self::assertLocalDateTime($dateTime, 1970, 1, 1, 12, 30, 59, 123_456_000);
	}

	public static function provideToISOStringData(): iterable
	{
		yield [LocalDateTime::of(1970, 1, 1, 12, 30), '1970-01-01T12:30'];
		yield [LocalDateTime::of(1970, 1, 1, 12, 30, 59), '1970-01-01T12:30:59'];
		yield [LocalDateTime::of(1970, 1, 1, 12, 30, 59, 1), '1970-01-01T12:30:59.000000001'];
		yield [LocalDateTime::of(1970, 1, 1, 12, 30, 59, 499_000), '1970-01-01T12:30:59.000499'];
		yield [LocalDateTime::of(1970, 1, 1, 12, 30, 59, 999_999_999), '1970-01-01T12:30:59.999999999'];
	}

	#[DataProvider('provideToISOStringData')]
	public function testToISOString(LocalDateTime $dateTime, string $expectedResult): void
	{
		self::assertSame($expectedResult, $dateTime->toISOString());
	}

	public static function provideFormatData(): iterable
	{
		yield [LocalDateTime::of(1970, 1, 31, 14, 30, 59), DateTimeFormatter::ofLocalizedPattern('yyyyMMddjamm', 'en-US'), "01/31/1970, 2:30\u{202F}PM"];
		yield [LocalDateTime::of(1970, 1, 31, 14, 30, 59), DateTimeFormatter::ofLocalizedPattern('yyyyMMddjamm', 'cs-CZ'), '31. 01. 1970 14:30'];
		yield [LocalDateTime::of(1970, 1, 31, 14, 30, 59), DateTimeFormatter::ofPattern('yyyy-MM-dd HH:mm:ss', 'en-US'), '1970-01-31 14:30:59'];
		yield [LocalDateTime::of(1970, 1, 31, 14, 30, 59), DateTimeFormatter::ofPattern('d.M.yy h:mm a', 'en-US'), '31.1.70 2:30 PM'];
		yield [LocalDateTime::of(1970, 1, 31, 14, 30, 59), DateTimeFormatter::ofDateTime(FormatStyle::LONG, FormatStyle::SHORT, 'en-US'), "January 31, 1970 at 2:30\u{202F}PM"];
		yield [LocalDateTime::of(1970, 1, 31, 14, 30, 59), DateTimeFormatter::ofDate(FormatStyle::LONG, 'en-US'), 'January 31, 1970'];
		yield [LocalDateTime::of(1970, 1, 31, 14, 30, 59), DateTimeFormatter::ofTime(FormatStyle::SHORT, 'en-US'), "2:30\u{202F}PM"];
	}

	#[DataProvider('provideFormatData')]
	public function testFormat(LocalDateTime $dateTime, DateTimeFormatter $formatter, string $expectedResult): void
	{
		self::assertSame($expectedResult, $dateTime->formatWith($formatter));
	}

	public static function provideInvalidFormatData(): iterable
	{
		yield [LocalDateTime::of(1970, 1, 1, 12, 30, 59), DateTimeFormatter::ofDateTime(FormatStyle::LONG, FormatStyle::FULL, 'en-US')];
		yield [LocalDateTime::of(1970, 1, 1, 12, 30, 59), DateTimeFormatter::ofTime(FormatStyle::FULL, 'en-US')];
	}

	#[DataProvider('provideInvalidFormatData')]
	public function testInvalidFormat(LocalDateTime $dateTime, DateTimeFormatter $formatter): void
	{
		$this->expectException(TemporalException::class);
		$this->expectExceptionMessage('Failed to format a Temporal value.');

		$dateTime->formatWith($formatter);
	}

	public function testSerialization(): void
	{
		$localDateTime = LocalDateTime::of(1970, 1, 31, 14, 30, 59, 1);

		$serialized = serialize($localDateTime);
		$unserialized = unserialize($serialized);

		self::assertTrue($localDateTime->isEqualTo($unserialized));
	}
}
