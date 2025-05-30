<?php

declare(strict_types=1);

namespace Temporal\Tests;

use PHPUnit\Framework\Attributes\DataProvider;
use PHPUnit\Framework\Attributes\TestWith;
use Temporal\Clock\FixedClock;
use Temporal\Instant;
use Temporal\MonthDay;
use Temporal\TemporalException;
use Temporal\TimeZoneOffset;

final class MonthDayTest extends TemporalTestCase
{
	public function testOf(): void
	{
		$monthDay = MonthDay::of(12, 12);
		self::assertMonthDay($monthDay, 12, 12);
	}

	#[TestWith([0, 1])]
	#[TestWith([1, 0])]
	#[TestWith([16, 0])]
	#[TestWith([12, 40])]
	#[TestWith([2, 30])]
	public function testInvalidOf(int $month, int $day): void
	{
		$this->expectException(TemporalException::class);
		MonthDay::of($month, $day);
	}

	public function testNow(): void
	{
		$clock = new FixedClock(Instant::epoch());

		$monthDay = MonthDay::now(TimeZoneOffset::utc(), $clock);
		self::assertMonthDay($monthDay, 1, 1);

		$monthDay = MonthDay::now(TimeZoneOffset::of(-1), $clock);
		self::assertMonthDay($monthDay, 12, 31);
	}

	public static function provideFromIsoStringData(): iterable
	{
		yield ['--01-01', 1, 1];
		yield ['--12-31', 12, 31];
	}

	#[DataProvider('provideFromIsoStringData')]
	public function testFromIsoString(string $text, int $expectedMonth, int $expectedDay): void
	{
		$monthDay = MonthDay::fromIsoString($text);
		self::assertMonthDay($monthDay, $expectedMonth, $expectedDay);
	}

	public static function provideInvalidFromIsoStringData(): iterable
	{
		yield [''];
		yield ['--'];
		yield ['01-01'];
		yield ['12-1'];
		yield ['1-31'];
	}

	#[DataProvider('provideInvalidFromIsoStringData')]
	public function testInvalidFromIsoString(string $text): void
	{
		$this->expectException(TemporalException::class);
		$this->expectExceptionMessage('Failed to parse given input into a Temporal value.');

		MonthDay::fromIsoString($text);
	}

	public function testExistsInYear(): void
	{
		self::assertTrue(MonthDay::of(2, 29)->existsInYear(2024));
		self::assertFalse(MonthDay::of(2, 29)->existsInYear(2025));
	}

	public static function provideComparisonData(): iterable
	{
		yield [MonthDay::of(1, 1), MonthDay::of(1, 1), 0];
		yield [MonthDay::of(1, 1), MonthDay::of(1, 2), -1];
		yield [MonthDay::of(1, 2), MonthDay::of(1, 1), 1];
		yield [MonthDay::of(1, 2), MonthDay::of(2, 1), -1];
		yield [MonthDay::of(2, 1), MonthDay::of(1, 2), 1];
	}

	#[DataProvider('provideComparisonData')]
	public function testComparison(MonthDay $a, MonthDay $b, int $expectedResult): void
	{
		self::assertSame($expectedResult, $a->compareTo($b));;
		self::assertSame(-$expectedResult, $b->compareTo($a));;

		self::assertSame($expectedResult === 0, $a->isEqualTo($b));
		self::assertSame($expectedResult < 0, $a->isBefore($b));
		self::assertSame($expectedResult <= 0, $a->isBeforeOrEqualTo($b));
		self::assertSame($expectedResult > 0, $a->isAfter($b));
		self::assertSame($expectedResult >= 0, $a->isAfterOrEqualTo($b));
	}

	public static function provideToIsoStringData(): iterable
	{
		yield [MonthDay::of(1, 1), '--01-01'];
		yield [MonthDay::of(2, 29), '--02-29'];
		yield [MonthDay::of(12, 31), '--12-31'];
	}

	#[DataProvider('provideToIsoStringData')]
	public function testToIsoString(MonthDay $monthDay, string $expectedResult): void
	{
		self::assertSame($expectedResult, $monthDay->toIsoString());
	}

	public function testSerialization(): void
	{
		$monthDay = MonthDay::of(1, 31);

		$serialized = serialize($monthDay);
		$unserialized = unserialize($serialized);

		self::assertTrue($monthDay->isEqualTo($unserialized));
	}
}
