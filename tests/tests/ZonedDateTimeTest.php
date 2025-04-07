<?php

declare(strict_types=1);

namespace Temporal\Tests;

use DateTimeImmutable;
use DateTimeZone;
use PHPUnit\Framework\Attributes\DataProvider;
use Temporal\Clock\FixedClock;
use Temporal\Duration;
use Temporal\Format\DateTimeFormatter;
use Temporal\Format\FormatStyle;
use Temporal\Instant;
use Temporal\LocalDateTime;
use Temporal\Period;
use Temporal\TemporalException;
use Temporal\TimeZone;
use Temporal\TimeZoneOffset;
use Temporal\TimeZoneRegion;
use Temporal\ZonedDateTime;

final class ZonedDateTimeTest extends TemporalTestCase
{
	public static function provideOfData(): iterable
	{
		yield [LocalDateTime::of(2025, 3, 30, 2), TimeZoneRegion::of('Europe/Prague'), 2025, 3, 30, 3, 0, 0, 0, 7200, 'Europe/Prague'];
		yield [LocalDateTime::of(2025, 3, 30, 2), TimeZoneOffset::of(1), 2025, 3, 30, 2, 0, 0, 0, 3600, '+01:00'];
		yield [LocalDateTime::of(2025, 3, 30, 2), TimeZoneOffset::of(2), 2025, 3, 30, 2, 0, 0, 0, 7200, '+02:00'];
	}

	#[DataProvider('provideOfData')]
	public function testOf(LocalDateTime $dateTime, TimeZone $timeZone, int $expectedYear, int $expectedMonth, int $expectedDay, int $expectedHour, int $expectedMinute, int $expectedSecond, int $expectedNano, int $expectedTimeZoneOffset, string $expectedTimeZoneId): void
	{
		$zonedDateTime = ZonedDateTime::of($dateTime, $timeZone);
		self::assertZonedDateTime($zonedDateTime, $expectedYear, $expectedMonth, $expectedDay, $expectedHour, $expectedMinute, $expectedSecond, $expectedNano);
		self::assertTimeZoneOffset($zonedDateTime->getTimeZoneOffset(), $expectedTimeZoneOffset);
		self::assertSame($expectedTimeZoneId, $zonedDateTime->getTimeZone()->getId());
	}

	public static function provideOfInstantData(): iterable
	{
		yield [Instant::of(1_743_296_400), TimeZoneRegion::of('Europe/Prague'), 2025, 3, 30, 3, 0, 0, 0, 7200, 'Europe/Prague'];
		yield [Instant::of(1_743_296_400), TimeZoneOffset::of(1), 2025, 3, 30, 2, 0, 0, 0, 3600, '+01:00'];
		yield [Instant::of(1_743_296_400), TimeZoneOffset::of(2), 2025, 3, 30, 3, 0, 0, 0, 7200, '+02:00'];
	}

	#[DataProvider('provideOfInstantData')]
	public function testOfInstant(Instant $instant, TimeZone $timeZone, int $expectedYear, int $expectedMonth, int $expectedDay, int $expectedHour, int $expectedMinute, int $expectedSecond, int $expectedNano, int $expectedTimeZoneOffset, string $expectedTimeZoneId): void
	{
		$zonedDateTime = ZonedDateTime::ofInstant($instant, $timeZone);
		self::assertZonedDateTime($zonedDateTime, $expectedYear, $expectedMonth, $expectedDay, $expectedHour, $expectedMinute, $expectedSecond, $expectedNano);
		self::assertTimeZoneOffset($zonedDateTime->getTimeZoneOffset(), $expectedTimeZoneOffset);
		self::assertSame($expectedTimeZoneId, $zonedDateTime->getTimeZone()->getId());
	}

	public function testNow(): void
	{
		$clock = new FixedClock(Instant::epoch());

		$zonedDateTime = ZonedDateTime::now(TimeZoneOffset::utc(), $clock);
		self::assertZonedDateTime($zonedDateTime, 1970, 1, 1, 0, 0);
		self::assertTimeZoneOffset($zonedDateTime->getTimeZoneOffset(), 0);

		$zonedDateTime = ZonedDateTime::now(TimeZoneOffset::of(1, 30), $clock);
		self::assertZonedDateTime($zonedDateTime, 1970, 1, 1, 1, 30);
		self::assertTimeZoneOffset($zonedDateTime->getTimeZoneOffset(), 5400);
	}

	public static function provideParseData(): iterable
	{
		yield ['2025-03-30T03:00:00+02:00[Europe/Prague]', 2025, 3, 30, 3, 0, 0, 0, 'Europe/Prague', 7200];
		yield ['2025-03-30T03:00:00+01:00', 2025, 3, 30, 3, 0, 0, 0, '+01:00', 3600];
		yield ['2025-03-30T03:00:00+02:00', 2025, 3, 30, 3, 0, 0, 0, '+02:00', 7200];
		yield ['2025-03-30T03:00:00Z', 2025, 3, 30, 3, 0, 0, 0, 'Z', 0];
	}

	#[DataProvider('provideParseData')]
	public function testParse(string $text, int $expectedYear, int $expectedMonth, int $expectedDay, int $expectedHour, int $expectedMinute, int $expectedSecond, int $expectedNano, string $expectedTimeZoneId, int $expectedTimeZoneOffset): void
	{
		$zonedDateTime = ZonedDateTime::parse($text);

		self::assertZonedDateTime($zonedDateTime, $expectedYear, $expectedMonth, $expectedDay, $expectedHour, $expectedMinute, $expectedSecond, $expectedNano);
		self::assertTimeZoneOffset($zonedDateTime->getTimeZoneOffset(), $expectedTimeZoneOffset);
		self::assertSame($expectedTimeZoneId, $zonedDateTime->getTimeZone()->getId());
	}

	public static function provideInvalidParseData(): iterable
	{
		yield [''];
		yield ['2025-03-30T03:00'];
		yield ['2025-03-30T03:00-2'];
		yield ['2025-03-30T03:00+22:00'];
		yield ['2025-03-30T03:00+12:00[Europe/Non_Existent_City]'];
	}

	#[DataProvider('provideInvalidParseData')]
	public function testInvalidParse(string $text): void
	{
		$this->expectException(TemporalException::class);
		$this->expectExceptionMessage('Failed to parse given input into a Temporal value.');

		ZonedDateTime::parse($text);
	}

	public function testWithTimeZoneSameLocal(): void
	{
		$zonedDateTime = ZonedDateTime::of(LocalDateTime::of(2025, 3, 30, 3), TimeZoneOffset::of(1));
		self::assertTimeZoneOffset($zonedDateTime->getTimeZoneOffset(), 3600);

		$sameLocal = $zonedDateTime->withTimeZoneSameLocal(TimeZoneOffset::of(2));
		self::assertZonedDateTime($sameLocal, 2025, 3, 30, 3, 0);
		self::assertTimeZoneOffset($sameLocal->getTimeZoneOffset(), 7200);
	}

	public function testWithTimeZoneSameInstant(): void
	{
		$zonedDateTime = ZonedDateTime::of(LocalDateTime::of(2025, 3, 30, 3), TimeZoneOffset::of(1));
		self::assertTimeZoneOffset($zonedDateTime->getTimeZoneOffset(), 3600);

		$sameLocal = $zonedDateTime->withTimeZoneSameInstant(TimeZoneOffset::of(2));
		self::assertZonedDateTime($sameLocal, 2025, 3, 30, 4, 0);
		self::assertTimeZoneOffset($sameLocal->getTimeZoneOffset(), 7200);
	}

	public function testWithFixedOffsetTimeZone(): void
	{
		$zonedDateTime = ZonedDateTime::of(LocalDateTime::of(2025, 3, 30, 3), TimeZoneRegion::of('Europe/Prague'));
		self::assertInstanceOf(TimeZoneRegion::class, $zonedDateTime->getTimeZone());

		$offsetDateTime = $zonedDateTime->withFixedOffsetTimeZone();
		self::assertInstanceOf(TimeZoneOffset::class, $offsetDateTime->getTimeZone());
		self::assertTimeZoneOffset($offsetDateTime->getTimeZoneOffset(), 7200);
	}

	public static function providePlusPeriodData(): iterable
	{
		yield [
			ZonedDateTime::of(LocalDateTime::of(2025, 3, 30, 1), TimeZoneRegion::of('Europe/Prague')),
			Period::ofDays(1),
			2025, 3, 31, 1, 0, 0, 0, 7200, 'Europe/Prague',
		];

		yield [
			ZonedDateTime::of(LocalDateTime::of(2025, 3, 30, 1), TimeZoneRegion::of('Europe/Prague')),
			Period::ofMonths(1),
			2025, 4, 30, 1, 0, 0, 0, 7200, 'Europe/Prague',
		];

		yield [
			ZonedDateTime::of(LocalDateTime::of(2025, 3, 30, 1), TimeZoneRegion::of('Europe/Prague')),
			Period::ofYears(1),
			2026, 3, 30, 1, 0, 0, 0, 7200, 'Europe/Prague',
		];
	}

	#[DataProvider('providePlusPeriodData')]
	public function testPlusPeriod(ZonedDateTime $zonedDateTime, Period $period, int $expectedYear, int $expectedMonth, int $expectedDay, int $expectedHour, int $expectedMinute, int $expectedSecond, int $expectedNano, int $expectedTimeZoneOffset, string $expectedTimeZoneId): void
	{
		$result = $zonedDateTime->plusPeriod($period);

		self::assertZonedDateTime($result, $expectedYear, $expectedMonth, $expectedDay, $expectedHour, $expectedMinute, $expectedSecond, $expectedNano);
		self::assertTimeZoneOffset($result->getTimeZoneOffset(), $expectedTimeZoneOffset);
		self::assertSame($expectedTimeZoneId, $result->getTimeZone()->getId());
	}

	public static function provideMinusPeriodData(): iterable
	{
		yield [
			ZonedDateTime::of(LocalDateTime::of(2025, 3, 31, 1), TimeZoneRegion::of('Europe/Prague')),
			Period::ofDays(1),
			2025, 3, 30, 1, 0, 0, 0, 3600, 'Europe/Prague',
		];

		yield [
			ZonedDateTime::of(LocalDateTime::of(2025, 3, 31, 1), TimeZoneRegion::of('Europe/Prague')),
			Period::ofMonths(1),
			2025, 2, 28, 1, 0, 0, 0, 3600, 'Europe/Prague',
		];

		yield [
			ZonedDateTime::of(LocalDateTime::of(2025, 3, 31, 1), TimeZoneRegion::of('Europe/Prague')),
			Period::ofYears(1),
			2024, 3, 31, 1, 0, 0, 0, 3600, 'Europe/Prague',
		];
	}

	#[DataProvider('provideMinusPeriodData')]
	public function testMinusPeriod(ZonedDateTime $zonedDateTime, Period $period, int $expectedYear, int $expectedMonth, int $expectedDay, int $expectedHour, int $expectedMinute, int $expectedSecond, int $expectedNano, int $expectedTimeZoneOffset, string $expectedTimeZoneId): void
	{
		$result = $zonedDateTime->minusPeriod($period);

		self::assertZonedDateTime($result, $expectedYear, $expectedMonth, $expectedDay, $expectedHour, $expectedMinute, $expectedSecond, $expectedNano);
		self::assertTimeZoneOffset($result->getTimeZoneOffset(), $expectedTimeZoneOffset);
		self::assertSame($expectedTimeZoneId, $result->getTimeZone()->getId());
	}

	public static function providePlusDurationData(): iterable
	{
		yield [
			ZonedDateTime::of(LocalDateTime::of(2025, 3, 30, 1), TimeZoneRegion::of('Europe/Prague')),
			Duration::ofHours(1),
			2025, 3, 30, 3, 0, 0, 0, 7200, 'Europe/Prague',
		];
	}

	#[DataProvider('providePlusDurationData')]
	public function testPlusDuration(ZonedDateTime $zonedDateTime, Duration $duration, int $expectedYear, int $expectedMonth, int $expectedDay, int $expectedHour, int $expectedMinute, int $expectedSecond, int $expectedNano, int $expectedTimeZoneOffset, string $expectedTimeZoneId): void
	{
		$result = $zonedDateTime->plusDuration($duration);

		self::assertZonedDateTime($result, $expectedYear, $expectedMonth, $expectedDay, $expectedHour, $expectedMinute, $expectedSecond, $expectedNano);
		self::assertTimeZoneOffset($result->getTimeZoneOffset(), $expectedTimeZoneOffset);
		self::assertSame($expectedTimeZoneId, $result->getTimeZone()->getId());
	}

	public static function provideMinusDurationData(): iterable
	{
		yield [
			ZonedDateTime::of(LocalDateTime::of(2025, 3, 30, 1), TimeZoneRegion::of('Europe/Prague')),
			Duration::ofHours(1),
			2025, 3, 30, 0, 0, 0, 0, 3600, 'Europe/Prague',
		];
	}

	#[DataProvider('provideMinusDurationData')]
	public function testMinusDuration(ZonedDateTime $zonedDateTime, Duration $duration, int $expectedYear, int $expectedMonth, int $expectedDay, int $expectedHour, int $expectedMinute, int $expectedSecond, int $expectedNano, int $expectedTimeZoneOffset, string $expectedTimeZoneId): void
	{
		$result = $zonedDateTime->minusDuration($duration);

		self::assertZonedDateTime($result, $expectedYear, $expectedMonth, $expectedDay, $expectedHour, $expectedMinute, $expectedSecond, $expectedNano);
		self::assertTimeZoneOffset($result->getTimeZoneOffset(), $expectedTimeZoneOffset);
		self::assertSame($expectedTimeZoneId, $result->getTimeZone()->getId());
	}

	public static function provideComparisonData(): iterable
	{
		yield [
			ZonedDateTime::of(LocalDateTime::of(1970, 1, 1, 12, 30), TimeZoneOffset::utc()),
			ZonedDateTime::of(LocalDateTime::of(1970, 1, 1, 12, 30), TimeZoneOffset::utc()),
			0,
		];

		yield [
			ZonedDateTime::of(LocalDateTime::of(1970, 1, 2, 12, 30), TimeZoneOffset::utc()),
			ZonedDateTime::of(LocalDateTime::of(1970, 1, 1, 12, 30), TimeZoneOffset::utc()),
			1,
		];

		yield [
			ZonedDateTime::of(LocalDateTime::of(1970, 1, 1, 12, 30), TimeZoneOffset::utc()),
			ZonedDateTime::of(LocalDateTime::of(1970, 1, 2, 12, 30), TimeZoneOffset::utc()),
			-1,
		];

		yield [
			ZonedDateTime::of(LocalDateTime::of(1970, 1, 1, 14, 30), TimeZoneOffset::utc()),
			ZonedDateTime::of(LocalDateTime::of(1970, 1, 1, 12, 30), TimeZoneOffset::utc()),
			1,
		];

		yield [
			ZonedDateTime::of(LocalDateTime::of(1970, 1, 1, 12, 30), TimeZoneOffset::utc()),
			ZonedDateTime::of(LocalDateTime::of(1970, 1, 1, 14, 30), TimeZoneOffset::utc()),
			-1,
		];
	}

	#[DataProvider('provideComparisonData')]
	public function testComparison(ZonedDateTime $a, ZonedDateTime $b, int $expectedResult): void
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
		$zonedDateTime = ZonedDateTime::of(LocalDateTime::of(2025, 3, 30, 3), TimeZoneRegion::of('Europe/Prague'));

		$dateTime = $zonedDateTime->toDateTime();
		self::assertSame('30', $dateTime->format('j'));
		self::assertSame('3', $dateTime->format('n'));
		self::assertSame('2025', $dateTime->format('Y'));
		self::assertSame('03', $dateTime->format('H'));
		self::assertSame('00', $dateTime->format('i'));
		self::assertSame('00', $dateTime->format('s'));
		self::assertSame('000000', $dateTime->format('u'));

		self::assertSame('Europe/Prague', $dateTime->getTimezone()->getName());
		self::assertSame(7200, $dateTime->getOffset());
	}

	public function testFromDateTime(): void
	{
		$dateTime = new DateTimeImmutable('2025-03-30T03:00:00', new DateTimeZone('Europe/Prague'));

		$zonedDateTime = ZonedDateTime::fromDateTime($dateTime);
		self::assertZonedDateTime($zonedDateTime, 2025, 3, 30, 3, 0);
		self::assertTimeZoneOffset($zonedDateTime->getTimeZoneOffset(), 7200);
		self::assertSame('Europe/Prague', $zonedDateTime->getTimeZone()->getId());
	}

	public static function provideToISOStringData(): iterable
	{
		yield [ZonedDateTime::of(LocalDateTime::of(2025, 3, 30, 3), TimeZoneRegion::of('Europe/Prague')), '2025-03-30T03:00+02:00[Europe/Prague]'];
		yield [ZonedDateTime::of(LocalDateTime::of(2025, 3, 30, 3), TimeZoneOffset::of(2)), '2025-03-30T03:00+02:00'];
		yield [ZonedDateTime::of(LocalDateTime::of(2025, 3, 30, 3), TimeZoneOffset::of(1)), '2025-03-30T03:00+01:00'];
		yield [ZonedDateTime::of(LocalDateTime::of(2025, 3, 30, 3), TimeZoneOffset::utc()), '2025-03-30T03:00Z'];
	}

	#[DataProvider('provideToISOStringData')]
	public function testToISOString(ZonedDateTime $zonedDateTime, string $expectedResult): void
	{
		self::assertSame($expectedResult, $zonedDateTime->toISOString());
	}

	public static function provideFormatData(): iterable
	{
		yield [ZonedDateTime::of(LocalDateTime::of(2025, 3, 30, 3), TimeZoneRegion::of('Europe/Prague')), DateTimeFormatter::ofLocalizedPattern('zzyyyyMMddjamm', 'en-US'), "03/30/2025, 3:00\u{202F}AM GMT+2"];
		yield [ZonedDateTime::of(LocalDateTime::of(2025, 3, 30, 3), TimeZoneRegion::of('Europe/Prague')), DateTimeFormatter::ofLocalizedPattern('zzyyyyMMddjamm', 'cs-CZ'), "30. 03. 2025 3:00 SELČ"];
		yield [ZonedDateTime::of(LocalDateTime::of(2025, 3, 30, 3), TimeZoneRegion::of('Europe/Prague')), DateTimeFormatter::ofPattern('yyyy-MM-dd HH:mm:ss zzz', 'en-US'), "2025-03-30 03:00:00 GMT+2"];
		yield [ZonedDateTime::of(LocalDateTime::of(2025, 3, 30, 3), TimeZoneRegion::of('Europe/Prague')), DateTimeFormatter::ofDateTime(FormatStyle::FULL, FormatStyle::FULL, 'en-US'), "Sunday, March 30, 2025 at 3:00:00\u{202F}AM Central European Summer Time"];
	}

	#[DataProvider('provideFormatData')]
	public function testFormat(ZonedDateTime $zonedDateTime, DateTimeFormatter $formatter, string $expectedResult): void
	{
		self::assertSame($expectedResult, $zonedDateTime->formatWith($formatter));
	}
}
