<?php

declare(strict_types=1);

namespace Temporal\Tests;

use PHPUnit\Framework\Attributes\DataProvider;
use PHPUnit\Framework\Attributes\TestWith;
use Temporal\Clock\FixedClock;
use Temporal\Instant;
use Temporal\TemporalException;
use Temporal\TimeZoneOffset;
use Temporal\YearMonth;

final class YearMonthTest extends TemporalTestCase
{
	public function testOf(): void
	{
		$yearMonth = YearMonth::of(2025, 4);
		self::assertYearMonth($yearMonth, 2025, 4);
	}

	#[TestWith([PHP_INT_MAX, 1])]
	#[TestWith([2025, 0])]
	#[TestWith([2025, 16])]
	public function testInvalidOf(int $year, int $month): void
	{
		$this->expectException(TemporalException::class);
		YearMonth::of($year, $month);
	}

	public function testNow(): void
	{
		$clock = new FixedClock(Instant::epoch());

		$yearMonth = YearMonth::now(TimeZoneOffset::utc(), $clock);
		self::assertYearMonth($yearMonth, 1970, 1);

		$yearMonth = YearMonth::now(TimeZoneOffset::of(-1), $clock);
		self::assertYearMonth($yearMonth, 1969, 12);
	}

	public static function provideParseData(): iterable
	{
		yield ['-0001-12', -1, 12];
		yield ['1970-01', 1970, 1];
	}

	#[DataProvider('provideParseData')]
	public function testParse(string $text, int $expectedYear, int $expectedMonth): void
	{
		$yearMonth = YearMonth::parse($text);
		self::assertYearMonth($yearMonth, $expectedYear, $expectedMonth);
	}

	public static function provideInvalidParseData(): iterable
	{
		yield [''];
		yield ['--1970-12'];
		yield ['70-12'];
		yield ['-70-12'];
	}

	#[DataProvider('provideInvalidParseData')]
	public function testInvalidParse(string $text): void
	{
		$this->expectException(TemporalException::class);
		$this->expectExceptionMessage('Failed to parse given input into a Temporal value.');

		YearMonth::parse($text);
	}

	public function testPlusMinusMonths(): void
	{
		$yearMonth = YearMonth::of(2024, 2);

		$yearMonth = $yearMonth->plusMonths(11);
		self::assertYearMonth($yearMonth, 2025, 1);

		$yearMonth = $yearMonth->minusMonths(13);
		self::assertYearMonth($yearMonth, 2024, 12);
	}

	public function testGetDaysInMonth(): void
	{
		$yearMonth = YearMonth::of(2024, 2);
		self::assertSame(29, $yearMonth->getDaysInMonth());

		$yearMonth = YearMonth::of(2025, 2);
		self::assertSame(28, $yearMonth->getDaysInMonth());
	}

	public static function provideComparisonData(): iterable
	{
		yield [YearMonth::of(1970, 1), YearMonth::of(1970, 1), 0];
		yield [YearMonth::of(1970, 1), YearMonth::of(1971, 1), -1];
		yield [YearMonth::of(1971, 1), YearMonth::of(1970, 1), 1];
		yield [YearMonth::of(1970, 1), YearMonth::of(1970, 2), -1];
		yield [YearMonth::of(1970, 2), YearMonth::of(1970, 1), 1];
	}

	#[DataProvider('provideComparisonData')]
	public function testComparison(YearMonth $a, YearMonth $b, int $expectedResult): void
	{
		self::assertSame($expectedResult, $a->compareTo($b));
		self::assertSame(-$expectedResult, $b->compareTo($a));

		self::assertSame($expectedResult === 0, $a->isEqualTo($b));
		self::assertSame($expectedResult < 0, $a->isBefore($b));
		self::assertSame($expectedResult <= 0, $a->isBeforeOrEqualTo($b));
		self::assertSame($expectedResult > 0, $a->isAfter($b));
		self::assertSame($expectedResult >= 0, $a->isAfterOrEqualTo($b));
	}

	public static function provideToISOStringData(): iterable
	{
		yield [YearMonth::of(-1, 1), '-0001-01'];
		yield [YearMonth::of(1970, 1), '1970-01'];
	}

	#[DataProvider('provideToISOStringData')]
	public function testToISOString(YearMonth $yearMonth, string $expectedResult): void
	{
		self::assertSame($expectedResult, $yearMonth->toISOString());
	}

	public function testSerialization(): void
	{
		$yearMonth = YearMonth::of(1970, 1);

		$serialized = serialize($yearMonth);
		$unserialized = unserialize($serialized);

		self::assertTrue($yearMonth->isEqualTo($unserialized));
	}
}
