<?php

declare(strict_types=1);

namespace Temporal\Tests;

use PHPUnit\Framework\Attributes\DataProvider;
use PHPUnit\Framework\Attributes\TestWith;
use Temporal\Clock\FixedClock;
use Temporal\Exception\ParsingException;
use Temporal\Exception\ValueOutOfRangeException;
use Temporal\Instant;
use Temporal\TimeZoneOffset;
use Temporal\YearWeek;

final class YearWeekTest extends TemporalTestCase
{
	public function testOf(): void
	{
		$yearWeek = YearWeek::of(2025, 4);
		self::assertYearWeek($yearWeek, 2025, 4);
	}

	#[TestWith([PHP_INT_MAX, 1])]
	#[TestWith([2025, 0])]
	#[TestWith([2025, 53])]
	public function testInvalidOf(int $year, int $month): void
	{
		$this->expectException(ValueOutOfRangeException::class);
		YearWeek::of($year, $month);
	}

	public function testNow(): void
	{
		$clock = new FixedClock(Instant::epoch());

		$yearWeek = YearWeek::now(TimeZoneOffset::utc(), $clock);
		self::assertYearWeek($yearWeek, 1970, 1);

		$yearWeek = YearWeek::now(TimeZoneOffset::of(-1), $clock);
		self::assertYearWeek($yearWeek, 1970, 1);
	}

	public static function provideFromIsoStringData(): iterable
	{
		yield ['1970-W01', 1970, 1];
		yield ['-0001-W52', -1, 52];
	}

	#[DataProvider('provideFromIsoStringData')]
	public function testFromIsoString(string $text, int $expectedYear, int $expectedWeek): void
	{
		$yearWeek = YearWeek::fromIsoString($text);
		self::assertYearWeek($yearWeek, $expectedYear, $expectedWeek);
	}

	public static function provideInvalidFromIsoStringData(): iterable
	{
		yield [''];
		yield ['70-W52'];
		yield ['-70-W52'];
		yield ['1970-42'];
		yield ['--1970-W42'];
	}

	#[DataProvider('provideInvalidFromIsoStringData')]
	public function testInvalidFromIsoString(string $text): void
	{
		$this->expectException(ParsingException::class);
		YearWeek::fromIsoString($text);
	}

	public function testAtDay(): void
	{
		$yearWeek = YearWeek::of(1970, 1);

		$firstDay = $yearWeek->atDay(1);
		self::assertLocalDate($firstDay, 1969, 12, 29);

		$lastDay = $yearWeek->atDay(7);
		self::assertLocalDate($lastDay, 1970, 1, 4);
	}

	public static function provideComparisonData(): iterable
	{
		yield [YearWeek::of(1970, 1), YearWeek::of(1970, 1), 0];
		yield [YearWeek::of(1970, 1), YearWeek::of(1971, 1), -1];
		yield [YearWeek::of(1971, 1), YearWeek::of(1970, 1), 1];
		yield [YearWeek::of(1970, 1), YearWeek::of(1970, 2), -1];
		yield [YearWeek::of(1970, 2), YearWeek::of(1970, 1), 1];
	}

	#[DataProvider('provideComparisonData')]
	public function testComparison(YearWeek $a, YearWeek $b, int $expectedResult): void
	{
		self::assertSame($expectedResult, $a->compareTo($b));
		self::assertSame(-$expectedResult, $b->compareTo($a));

		self::assertSame($expectedResult === 0, $a->isEqualTo($b));
		self::assertSame($expectedResult < 0, $a->isBefore($b));
		self::assertSame($expectedResult <= 0, $a->isBeforeOrEqualTo($b));
		self::assertSame($expectedResult > 0, $a->isAfter($b));
		self::assertSame($expectedResult >= 0, $a->isAfterOrEqualTo($b));
	}

	public static function provideToIsoStringData(): iterable
	{
		yield [YearWeek::of(-1, 1), '-0001-W01'];
		yield [YearWeek::of(1970, 1), '1970-W01'];
	}

	#[DataProvider('provideToIsoStringData')]
	public function testToIsoString(YearWeek $yearWeek, string $expectedResult): void
	{
		self::assertSame($expectedResult, $yearWeek->toIsoString());
	}

	public function testSerialization(): void
	{
		$yearWeek = YearWeek::of(1970, 1);

		$serialized = serialize($yearWeek);
		$unserialized = unserialize($serialized);

		self::assertTrue($yearWeek->isEqualTo($unserialized));
	}
}
