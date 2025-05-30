<?php

declare(strict_types=1);

namespace Temporal\Tests;

use PHPUnit\Framework\Attributes\DataProvider;
use Temporal\Duration;
use Temporal\Instant;
use Temporal\TemporalException;
use function serialize;
use function unserialize;

final class DurationTest extends TemporalTestCase
{
	public function testZero(): void
	{
		$zero = Duration::zero();
		self::assertDuration($zero, 0);
	}

	public static function provideOfSecondsData(): iterable
	{
		yield [3, 1, 3, 1];
		yield [4, -999_999_999, 3, 1];
		yield [2, 1_000_000_001, 3, 1];
		yield [-3, 1, -3, 1];
		yield [-4, 1_000_000_001, -3, 1];
		yield [-2, -999_999_999, -3, 1];
	}

	#[DataProvider('provideOfSecondsData')]
	public function testOfSeconds(int $seconds, int $nanoAdjustment, int $expectedSeconds, int $expectedNanos): void
	{
		$duration = Duration::ofSeconds($seconds, $nanoAdjustment);
		self::assertDuration($duration, $expectedSeconds, $expectedNanos);
	}

	public function testOfMinutes(): void
	{
		$duration = Duration::ofMinutes(-1);
		self::assertDuration($duration, -60);

		$duration = Duration::ofMinutes(0);
		self::assertDuration($duration, 0);

		$duration = Duration::ofMinutes(1);
		self::assertDuration($duration, 60);
	}

	public function testOfHours(): void
	{
		$duration = Duration::ofHours(-1);
		self::assertDuration($duration, -3600);

		$duration = Duration::ofHours(0);
		self::assertDuration($duration, 0);

		$duration = Duration::ofHours(1);
		self::assertDuration($duration, 3600);
	}

	public function testOfDays(): void
	{
		$duration = Duration::ofDays(-1);
		self::assertDuration($duration, -86400);

		$duration = Duration::ofDays(0);
		self::assertDuration($duration, 0);

		$duration = Duration::ofDays(1);
		self::assertDuration($duration, 86400);
	}

	public function testBetween(): void
	{
		$a = Instant::of(0, 500_000_000);
		$b = Instant::of(3);

		$duration = Duration::between($a, $b);
		self::assertDuration($duration, 2, 500_000_000);
	}

	public static function provideFromIsoStringData(): iterable
	{
		yield ['PT0S', 0, 0];
		yield ['PT-0S', 0, 0];
		yield ['-PT0S', 0, 0];
		yield ['-PT-0S', 0, 0];

		yield ['PT1S', 1, 0];
		yield ['PT1.5S', 1, 500_000_000];
		yield ['PT1.000000001S', 1, 1];

		yield ['P1D', 86400, 0];
		yield ['PT24H', 86400, 0];
		yield ['PT1440M', 86400, 0];
		yield ['PT86400S', 86400, 0];
		yield ['PT86400.0S', 86400, 0];

		yield ['P1DT1H', 90000, 0];
		yield ['P1DT1H1M', 90060, 0];
		yield ['P1DT1H1M1S', 90061, 0];
		yield ['P1DT1H1M1.1S', 90061, 100_000_000];
	}

	#[DataProvider('provideFromIsoStringData')]
	public function testFromIsoString(string $text, int $expectedSeconds, int $expectedNanos): void
	{
		$duration = Duration::fromIsoString($text);
		self::assertDuration($duration, $expectedSeconds, $expectedNanos);
	}

	public static function provideInvalidFromIsoStringData(): iterable
	{
		yield [''];
		yield ['P'];
		yield ['-P'];
		yield ['PD'];
		yield ['-PD'];
		yield ['P-D'];
		yield ['-PT'];
	}

	#[DataProvider('provideInvalidFromIsoStringData')]
	public function testInvalidFromIsoString(string $text): void
	{
		$this->expectException(TemporalException::class);
		$this->expectExceptionMessage('Failed to parse given input into a Temporal value.');

		Duration::fromIsoString($text);
	}

	public function testGetters(): void
	{
		$duration = Duration::ofSeconds(123_456, 2);

		self::assertSame(1, $duration->toDays());
		self::assertSame(1, $duration->toDaysPart());

		self::assertSame(34, $duration->toHours());
		self::assertSame(10, $duration->toHoursPart());

		self::assertSame(2057, $duration->toMinutes());
		self::assertSame(17, $duration->toMinutesPart());

		self::assertSame(123_456, $duration->toSeconds());
		self::assertSame(36, $duration->toSecondsPart());
	}

	public static function provideComparisonToZeroData(): iterable
	{
		yield [Duration::zero(), 0];
		yield [Duration::ofSeconds(1), 1];
		yield [Duration::ofSeconds(-1), -1];
		yield [Duration::ofSeconds(-1, 500_000), -1];
		yield [Duration::ofSeconds(1, 500_000), 1];
		yield [Duration::ofSeconds(1, -500_000), 1];
		yield [Duration::ofSeconds(1, -1_000_000_000), 0];
	}

	#[DataProvider('provideComparisonToZeroData')]
	public function testComparisonToZero(Duration $duration, int $expectedResult): void
	{
		self::assertSame($expectedResult === 0, $duration->isZero());
		self::assertSame($expectedResult > 0, $duration->isPositive());
		self::assertSame($expectedResult >= 0, $duration->isPositiveOrZero());
		self::assertSame($expectedResult < 0, $duration->isNegative());
		self::assertSame($expectedResult <= 0, $duration->isNegativeOrZero());
	}

	public static function providePlusData(): iterable
	{
		yield [Duration::zero(), Duration::ofSeconds(1), 1, 0];
		yield [Duration::ofSeconds(0, 600_000_000), Duration::ofSeconds(1, 600_000_000), 2, 200_000_000];
	}

	#[DataProvider('providePlusData')]
	public function testPlus(Duration $duration, Duration $other, int $expectedSeconds, int $expectedNanos): void
	{
		self::assertDuration($duration->plus($other), $expectedSeconds, $expectedNanos);
	}

	public static function provideMinusData(): iterable
	{
		yield [Duration::zero(), Duration::ofSeconds(1), -1, 0];
		yield [Duration::ofSeconds(0, 600_000_000), Duration::ofSeconds(1, 600_000_000), -1, 0];
	}

	#[DataProvider('provideMinusData')]
	public function testMinus(Duration $duration, Duration $other, int $expectedSeconds, int $expectedNanos): void
	{
		self::assertDuration($duration->minus($other), $expectedSeconds, $expectedNanos);
	}

	public function testNegated(): void
	{
		$duration = Duration::ofSeconds(1, 600_000_000);
		$negated = $duration->negated();

		self::assertDuration($negated, -2, 400_000_000);
	}

	public function testAbs(): void
	{
		$duration = Duration::ofSeconds(-42_000);
		$abs = $duration->abs();

		self::assertDuration($abs, 42_000);
	}

	public static function provideComparisonData(): iterable
	{
		yield [Duration::ofSeconds(1), Duration::ofSeconds(1), 0];
		yield [Duration::ofSeconds(1), Duration::ofSeconds(2), -1];
		yield [Duration::ofSeconds(2), Duration::ofSeconds(1), 1];
	}

	#[DataProvider('provideComparisonData')]
	public function testComparison(Duration $a, Duration $b, int $expectedResult): void
	{
		self::assertSame($expectedResult, $a->compareTo($b));
		self::assertSame(-$expectedResult, $b->compareTo($a));

		self::assertSame($expectedResult === 0, $a->isEqualTo($b));
		self::assertSame($expectedResult < 0, $a->isLesserThan($b));
		self::assertSame($expectedResult <= 0, $a->isLesserThanOrEqualTo($b));
		self::assertSame($expectedResult > 0, $a->isGreaterThan($b));
		self::assertSame($expectedResult >= 0, $a->isGreaterThanOrEqualTo($b));
	}

	public static function provideToIsoStringData(): iterable
	{
		yield [Duration::zero(), 'PT0S'];

		yield [Duration::ofSeconds(1), 'PT1S'];
		yield [Duration::ofSeconds(-1), 'PT-1S'];
		yield [Duration::ofSeconds(1, 500_000_000), 'PT1.5S'];
		yield [Duration::ofSeconds(1, 1), 'PT1.000000001S'];
		yield [Duration::ofSeconds(-2, 500_000_000), 'PT-1.5S'];
		yield [Duration::ofSeconds(-1, 1), 'PT-0.999999999S'];

		yield [Duration::ofSeconds(123_456), 'PT34H17M36S'];
		yield [Duration::ofSeconds(-123_456), 'PT-34H-17M-36S'];
	}

	#[DataProvider('provideToIsoStringData')]
	public function testToIsoString(Duration $duration, string $expectedResult): void
	{
		self::assertSame($expectedResult, $duration->toIsoString());
	}

	public function testSerialization(): void
	{
		$duration = Duration::ofDays(1)->plusHours(1)->plusMinutes(1)->plusSeconds(1);

		$serialized = serialize($duration);
		$unserialized = unserialize($serialized);

		self::assertTrue($duration->isEqualTo($unserialized));
	}
}
