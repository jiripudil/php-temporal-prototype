<?php

declare(strict_types=1);

namespace Temporal\Tests;

use PHPUnit\Framework\Attributes\CoversClass;
use PHPUnit\Framework\Attributes\DataProvider;
use PHPUnit\Framework\Attributes\TestWith;
use Temporal\Clock\FixedClock;
use Temporal\Duration;
use Temporal\Instant;
use function serialize;
use function unserialize;
use const PHP_INT_MAX;
use const PHP_INT_MIN;

#[CoversClass(Instant::class)]
final class InstantTest extends TemporalTestCase
{
	#[TestWith([3, 1, 3, 1])]
	#[TestWith([4, -999_999_999, 3, 1])]
	#[TestWith([2, 1_000_000_001, 3, 1])]
	public function testOf(int $seconds, int $nanoAdjustment, int $expectedEpochSecond, int $expectedNanos): void
	{
		$instant = Instant::of($seconds, $nanoAdjustment);

		self::assertInstant($instant, $expectedEpochSecond, $expectedNanos);
	}

	public function testNow(): void
	{
		$clock = new FixedClock(Instant::of(1_800_000_000, 999_999_999));
		$now = Instant::now($clock);

		self::assertInstant($now, 1_800_000_000, 999_999_999);
	}

	public function testEpoch(): void
	{
		$epoch = Instant::epoch();

		self::assertInstant($epoch, 0, 0);
	}

	public function testMin(): void
	{
		$min = Instant::min();

		self::assertInstant($min, PHP_INT_MIN, 0);
	}

	public function testMax(): void
	{
		$max = Instant::max();

		self::assertInstant($max, PHP_INT_MAX, 999_999_999);
	}

	public static function providePlusData(): iterable
	{
		yield [Instant::epoch(), Duration::ofSeconds(1), 1, 0];
		yield [Instant::epoch(), Duration::ofSeconds(0, 1), 0, 1];
		yield [Instant::epoch(), Duration::ofMinutes(1), 60, 0];
		yield [Instant::epoch(), Duration::ofHours(1), 3600, 0];
		yield [Instant::epoch(), Duration::ofDays(1), 86400, 0];
	}

	#[DataProvider('providePlusData')]
	public function testPlus(Instant $instant, Duration $duration, int $expectedEpochSecond, int $expectedNanos): void
	{
		self::assertInstant($instant->plus($duration), $expectedEpochSecond, $expectedNanos);
	}

	public static function provideMinusData(): iterable
	{
		yield [Instant::epoch(), Duration::ofSeconds(1), -1, 0];
		yield [Instant::epoch(), Duration::ofSeconds(0, 1), -1, 999_999_999];
		yield [Instant::epoch(), Duration::ofMinutes(1), -60, 0];
		yield [Instant::epoch(), Duration::ofHours(1), -3600, 0];
		yield [Instant::epoch(), Duration::ofDays(1), -86400, 0];
	}

	#[DataProvider('provideMinusData')]
	public function testMinus(Instant $instant, Duration $duration, int $expectedEpochSecond, int $expectedNanos): void
	{
		self::assertInstant($instant->minus($duration), $expectedEpochSecond, $expectedNanos);
	}

	public static function provideComparisonData(): iterable
	{
		yield [Instant::of(1, 1), Instant::of(1, 1), 0];
		yield [Instant::of(1, 1), Instant::of(2, 1), -1];
		yield [Instant::of(2, 1), Instant::of(1, 1), 1];
		yield [Instant::of(1, 1), Instant::of(1, 2), -1];
		yield [Instant::of(1, 2), Instant::of(1, 1), 1];
	}

	#[DataProvider('provideComparisonData')]
	public function testComparison(Instant $a, Instant $b, int $expectedResult): void
	{
		self::assertSame($expectedResult, $a->compareTo($b));
		self::assertSame(-$expectedResult, $b->compareTo($a));

		self::assertSame($expectedResult === 0, $a->isEqualTo($b));
		self::assertSame($expectedResult < 0, $a->isBefore($b));
		self::assertSame($expectedResult <= 0, $a->isBeforeOrEqualTo($b));
		self::assertSame($expectedResult > 0, $a->isAfter($b));
		self::assertSame($expectedResult >= 0, $a->isAfterOrEqualTo($b));
	}

	public static function provideToDecimalData(): iterable
	{
		yield [Instant::epoch(), '0'];
		yield [Instant::of(1, 1), '1.000000001'];
		yield [Instant::of(1, 100_000_000), '1.1'];
		yield [Instant::of(1, 499_000), '1.000499'];
		yield [Instant::of(1, 999_999_999), '1.999999999'];
	}

	#[DataProvider('provideToDecimalData')]
	public function testToDecimal(Instant $instant, string $expectedDecimal): void
	{
		self::assertSame($expectedDecimal, $instant->toDecimal());
	}

	#[TestWith([0, 0, '1970-01-01T00:00Z'])]
	#[TestWith([1, 1, '1970-01-01T00:00:01.000000001Z'])]
	public function testToISOString(int $seconds, int $nanoAdjustment, string $expectedISOString): void
	{
		$instant = Instant::of($seconds, $nanoAdjustment);
		self::assertSame($expectedISOString, $instant->toISOString());
	}

	public function testSerialization(): void
	{
		$instant = Instant::of(1, 499_000);

		$serialized = serialize($instant);
		$unserialized = unserialize($serialized);

		self::assertTrue($instant->isEqualTo($unserialized));
	}
}
