<?php

declare(strict_types=1);

namespace Temporal\Tests;

use DateTimeImmutable;
use PHPUnit\Framework\Attributes\DataProvider;
use PHPUnit\Framework\Attributes\TestWith;
use Temporal\Clock\FixedClock;
use Temporal\Format\DateTimeFormatter;
use Temporal\Format\FormatStyle;
use Temporal\Instant;
use Temporal\LocalDate;
use Temporal\Period;
use Temporal\TemporalException;
use Temporal\TimeZoneOffset;

final class LocalDateTest extends TemporalTestCase
{
	public function testOf(): void
	{
		$date = LocalDate::of(1970, 1, 1);
		self::assertLocalDate($date, 1970, 1, 1);
	}

	#[TestWith([PHP_INT_MAX, 1, 1])]
	#[TestWith([2025, 0, 1])]
	#[TestWith([2025, 1, 0])]
	#[TestWith([2025, 16, 1])]
	#[TestWith([2025, 12, 40])]
	#[TestWith([2025, 2, 29])]
	public function testInvalidOf(int $year, int $month, int $day): void
	{
		$this->expectException(TemporalException::class);
		LocalDate::of($year, $month, $day);
	}

	public function testNow(): void
	{
		$clock = new FixedClock(Instant::epoch());

		$date = LocalDate::now(TimeZoneOffset::utc(), $clock);
		self::assertLocalDate($date, 1970, 1, 1);

		$date = LocalDate::now(TimeZoneOffset::of(0, -30), $clock);
		self::assertLocalDate($date, 1969, 12, 31);
	}

	public function testFromIsoString(): void
	{
		$date = LocalDate::fromIsoString('1970-01-01');
		self::assertLocalDate($date, 1970, 1, 1);

		$this->expectException(TemporalException::class);
		$this->expectExceptionMessage('Failed to parse given input into a Temporal value.');
		LocalDate::fromIsoString('1970-13-42');
	}

	public function testMin(): void
	{
		$date = LocalDate::min();
		self::assertLocalDate($date, -999_999, 1, 1);
	}

	public function testMax(): void
	{
		$date = LocalDate::max();
		self::assertLocalDate($date, 999_999, 12, 31);
	}

	public function testOfEpochDay(): void
	{
		$date = LocalDate::ofEpochDay(0);
		self::assertLocalDate($date, 1970, 1, 1);

		$date = LocalDate::ofEpochDay(365);
		self::assertLocalDate($date, 1971, 1, 1);

		$date = LocalDate::ofEpochDay(-365);
		self::assertLocalDate($date, 1969, 1, 1);
	}

	public function testToEpochDay(): void
	{
		$date = LocalDate::of(1970, 1, 1);
		self::assertSame(0, $date->toEpochDay());

		$date = LocalDate::of(1971, 1, 1);
		self::assertSame(365, $date->toEpochDay());

		$date = LocalDate::of(1969, 1, 1);
		self::assertSame(-365, $date->toEpochDay());
	}

	public function testOfDayOfYear(): void
	{
		$date = LocalDate::ofDayOfYear(1970, 365);
		self::assertLocalDate($date, 1970, 12, 31);

		$date = LocalDate::ofDayOfYear(1972, 365);
		self::assertLocalDate($date, 1972, 12, 30);

		$date = LocalDate::ofDayOfYear(1972, 366);
		self::assertLocalDate($date, 1972, 12, 31);
	}

	public function testGetDayOfYear(): void
	{
		$date = LocalDate::of(1970, 12, 31);
		self::assertSame(365, $date->getDayOfYear());

		$date = LocalDate::of(1972, 12, 30);
		self::assertSame(365, $date->getDayOfYear());

		$date = LocalDate::of(1972, 12, 31);
		self::assertSame(366, $date->getDayOfYear());
	}

	public function testGetDayOfWeek(): void
	{
		$date = LocalDate::of(1970, 1, 1);
		self::assertSame(4, $date->getDayOfWeek());
	}

	public function testGetYearWeek(): void
	{
		$date = LocalDate::of(1969, 12, 28);
		self::assertSame(52, $date->getWeek());
		self::assertSame(1969, $date->getYearOfWeek());

		$date = LocalDate::of(1969, 12, 31);
		self::assertSame(1, $date->getWeek());
		self::assertSame(1970, $date->getYearOfWeek());

		$date = LocalDate::of(1970, 1, 1);
		self::assertSame(1, $date->getWeek());
		self::assertSame(1970, $date->getYearOfWeek());

		$date = LocalDate::of(1970, 12, 31);
		self::assertSame(53, $date->getWeek());
		self::assertSame(1970, $date->getYearOfWeek());

		$date = LocalDate::of(1971, 1, 1);
		self::assertSame(53, $date->getWeek());
		self::assertSame(1970, $date->getYearOfWeek());
	}

	public static function providePlusData(): iterable
	{
		yield [LocalDate::of(1970, 1, 1), Period::ofDays(1), 1970, 1, 2];
		yield [LocalDate::of(1970, 1, 1), Period::ofWeeks(1), 1970, 1, 8];
		yield [LocalDate::of(1970, 1, 1), Period::ofMonths(1), 1970, 2, 1];
		yield [LocalDate::of(1970, 1, 1), Period::ofMonths(3), 1970, 4, 1];
		yield [LocalDate::of(1970, 1, 1), Period::ofYears(1), 1971, 1, 1];
	}

	#[DataProvider('providePlusData')]
	public function testPlus(LocalDate $date, Period $period, int $expectedYear, int $expectedMonth, int $expectedDay): void
	{
		self::assertLocalDate($date->plus($period), $expectedYear, $expectedMonth, $expectedDay);
	}

	public static function provideMinusData(): iterable
	{
		yield [LocalDate::of(1970, 1, 1), Period::ofDays(1), 1969, 12, 31];
		yield [LocalDate::of(1970, 1, 1), Period::ofWeeks(1), 1969, 12, 25];
		yield [LocalDate::of(1970, 1, 1), Period::ofMonths(1), 1969, 12, 1];
		yield [LocalDate::of(1970, 1, 1), Period::ofMonths(3), 1969, 10, 1];
		yield [LocalDate::of(1970, 1, 1), Period::ofYears(1), 1969, 1, 1];
	}

	#[DataProvider('provideMinusData')]
	public function testMinus(LocalDate $date, Period $period, int $expectedYear, int $expectedMonth, int $expectedDay): void
	{
		self::assertLocalDate($date->minus($period), $expectedYear, $expectedMonth, $expectedDay);
	}

	public function testUntil(): void
	{
		$date = LocalDate::of(1970, 1, 1);
		$until = $date->until(LocalDate::of(1971, 11, 22));

		self::assertSame(1, $until->getYears());
		self::assertSame(10, $until->getMonths());
		self::assertSame(21, $until->getDays());
	}

	public static function provideComparisonData(): iterable
	{
		yield [LocalDate::of(1970, 1, 1), LocalDate::of(1970, 1, 1), 0];
		yield [LocalDate::of(1970, 1, 1), LocalDate::of(1970, 1, 2), -1];
		yield [LocalDate::of(1970, 1, 2), LocalDate::of(1970, 2, 1), -1];
		yield [LocalDate::of(1970, 1, 2), LocalDate::of(1970, 1, 1), 1];
		yield [LocalDate::of(1970, 2, 1), LocalDate::of(1970, 1, 2), 1];
	}

	#[DataProvider('provideComparisonData')]
	public function testComparison(LocalDate $a, LocalDate $b, int $expectedResult): void
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
		$date = LocalDate::of(1970, 12, 31);

		$dateTime = $date->toDateTime();
		self::assertSame('31', $dateTime->format('j'));
		self::assertSame('12', $dateTime->format('n'));
		self::assertSame('1970', $dateTime->format('Y'));
	}

	public function testFromDateTime(): void
	{
		$date = LocalDate::fromDateTime(new DateTimeImmutable('1970-01-01T12:30:59.123456Z'));
		self::assertLocalDate($date, 1970, 1, 1);

		$date = LocalDate::fromDateTime(new DateTimeImmutable('1970-01-01T12:30:59.123456Z+11:00'));
		self::assertLocalDate($date, 1970, 1, 1);
	}

	public static function provideToIsoStringData(): iterable
	{
		yield [LocalDate::of(1970, 1, 1), '1970-01-01'];
		yield [LocalDate::of(-1, 1, 1), '-0001-01-01'];
	}

	#[DataProvider('provideToIsoStringData')]
	public function testToIsoString(LocalDate $date, string $expectedResult): void
	{
		self::assertSame($expectedResult, $date->toIsoString());
	}

	public static function provideFormatData(): iterable
	{
		yield [LocalDate::of(1970, 1, 31), DateTimeFormatter::ofLocalizedPattern('yyyyMMdd', 'en-US'), '01/31/1970'];
		yield [LocalDate::of(1970, 1, 31), DateTimeFormatter::ofLocalizedPattern('yyyyMMdd', 'cs-CZ'), '31. 01. 1970'];
		yield [LocalDate::of(1970, 1, 31), DateTimeFormatter::ofPattern('yyyy-MM-dd', 'en-US'), '1970-01-31'];
		yield [LocalDate::of(1970, 1, 31), DateTimeFormatter::ofPattern('d.M.yy', 'en-US'), '31.1.70'];
		yield [LocalDate::of(1970, 1, 31), DateTimeFormatter::ofDate(FormatStyle::LONG, 'en-US'), 'January 31, 1970'];
		yield [LocalDate::of(1970, 1, 31), DateTimeFormatter::ofDate(FormatStyle::LONG, 'ja-JP'), '1970年1月31日'];
		yield [LocalDate::of(1970, 1, 31), DateTimeFormatter::ofDate(FormatStyle::LONG, 'ar-MA'), '31 يناير 1970'];
		yield [LocalDate::of(1970, 1, 31), DateTimeFormatter::ofDate(FormatStyle::LONG, 'ar-EG'), '٣١ يناير ١٩٧٠'];
	}

	#[DataProvider('provideFormatData')]
	public function testFormat(LocalDate $date, DateTimeFormatter $formatter, string $expectedResult): void
	{
		self::assertSame($expectedResult, $date->formatWith($formatter));
	}

	public static function provideInvalidFormatData(): iterable
	{
		yield [LocalDate::of(1970, 1, 31), DateTimeFormatter::ofTime(FormatStyle::FULL, 'en-US')];
		yield [LocalDate::of(1970, 1, 31), DateTimeFormatter::ofDateTime(FormatStyle::FULL, FormatStyle::FULL, 'en-US')];
	}

	#[DataProvider('provideInvalidFormatData')]
	public function testInvalidFormat(LocalDate $date, DateTimeFormatter $formatter): void
	{
		$this->expectException(TemporalException::class);
		$this->expectExceptionMessage('Failed to format a Temporal value.');

		$date->formatWith($formatter);
	}

	public function testSerialization(): void
	{
		$localDate = LocalDate::of(1970, 1, 31);

		$serialized = serialize($localDate);
		$unserialized = unserialize($serialized);

		self::assertTrue($localDate->isEqualTo($unserialized));
	}
}
