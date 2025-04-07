<?php

declare(strict_types=1);

namespace Temporal\Tests;

use PHPUnit\Framework\Attributes\DataProvider;
use Temporal\Clock\FixedClock;
use Temporal\Instant;
use Temporal\TemporalException;
use Temporal\TimeZoneOffset;
use Temporal\YearWeek;

final class YearWeekTest extends TemporalTestCase
{
	public function testNow(): void
	{
		$clock = new FixedClock(Instant::epoch());

		$yearWeek = YearWeek::now(TimeZoneOffset::utc(), $clock);
		self::assertYearWeek($yearWeek, 1970, 1);

		$yearWeek = YearWeek::now(TimeZoneOffset::of(-1), $clock);
		self::assertYearWeek($yearWeek, 1970, 1);
	}

	public static function provideParseData(): iterable
	{
		yield ['1970-W01', 1970, 1];
		yield ['-0001-W52', -1, 52];
	}

	#[DataProvider('provideParseData')]
	public function testParse(string $text, int $expectedYear, int $expectedWeek): void
	{
		$yearWeek = YearWeek::parse($text);
		self::assertYearWeek($yearWeek, $expectedYear, $expectedWeek);
	}

	public static function provideInvalidParseData(): iterable
	{
		yield [''];
		yield ['70-W52'];
		yield ['-70-W52'];
		yield ['1970-42'];
		yield ['--1970-W42'];
	}

	#[DataProvider('provideInvalidParseData')]
	public function testInvalidParse(string $text): void
	{
		$this->expectException(TemporalException::class);
		$this->expectExceptionMessage('Failed to parse given input into a Temporal value.');

		YearWeek::parse($text);
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

	public static function provideToISOStringData(): iterable
	{
		yield [YearWeek::of(-1, 1), '-0001-W01'];
		yield [YearWeek::of(1970, 1), '1970-W01'];
	}

	#[DataProvider('provideToISOStringData')]
	public function testToISOString(YearWeek $yearWeek, string $expectedResult): void
	{
		self::assertSame($expectedResult, $yearWeek->toISOString());
	}
}
