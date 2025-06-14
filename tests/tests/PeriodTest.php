<?php

declare(strict_types=1);

namespace Temporal\Tests;

use PHPUnit\Framework\Attributes\DataProvider;
use Temporal\Exception\ParsingException;
use Temporal\LocalDate;
use Temporal\Period;

final class PeriodTest extends TemporalTestCase
{
	public function testZero(): void
	{
		$zero = Period::zero();
		self::assertPeriod($zero, 0, 0, 0);
	}

	public function testOf(): void
	{
		$period = Period::of(1, 1, 1);
		self::assertPeriod($period, 1, 1, 1);
	}

	public function testOfYears(): void
	{
		$period = Period::ofYears(1);
		self::assertPeriod($period, 1, 0, 0);
	}

	public function testOfMonths(): void
	{
		$period = Period::ofMonths(1);
		self::assertPeriod($period, 0, 1, 0);
	}

	public function testOfWeeks(): void
	{
		$period = Period::ofWeeks(1);
		self::assertPeriod($period, 0, 0, 7);
	}

	public function testOfDays(): void
	{
		$period = Period::ofDays(1);
		self::assertPeriod($period, 0, 0, 1);
	}

	public function testBetween(): void
	{
		$a = LocalDate::of(1970, 1, 1);
		$b = LocalDate::of(1972, 11, 22);

		$period = Period::between($a, $b);
		self::assertPeriod($period, 2, 10, 21);
	}

	public static function provideFromIsoStringData(): iterable
	{
		yield ['P1Y2M3D', 1, 2, 3];
		yield ['P1Y-1M', 1, -1, 0];
		yield ['P-1M', 0, -1, 0];
		yield ['-P-1M', 0, 1, 0];
		yield ['-P4W', 0, 0, -28];
	}

	#[DataProvider('provideFromIsoStringData')]
	public function testFromIsoString(string $text, int $expectedYears, int $expectedMonths, int $expectedDays): void
	{
		$period = Period::fromIsoString($text);
		self::assertPeriod($period, $expectedYears, $expectedMonths, $expectedDays);
	}

	public static function provideInvalidFromIsoStringData(): iterable
	{
		yield [''];
		yield ['PT1S'];
		yield ['PY'];
		yield ['P-Y'];
		yield ['-PY'];
	}

	#[DataProvider('provideInvalidFromIsoStringData')]
	public function testInvalidFromIsoString(string $text): void
	{
		$this->expectException(ParsingException::class);
		Period::fromIsoString($text);
	}

	public function testNegated(): void
	{
		$period = Period::of(0, -1, 1);
		$negated = $period->negated();
		self::assertPeriod($negated, 0, 1, -1);
	}

	public function testIsZero(): void
	{
		self::assertTrue(Period::zero()->isZero());
		self::assertTrue(Period::of(0, 0, 0)->isZero());
		self::assertFalse(Period::of(0, 0, -1)->isZero());
		self::assertFalse(Period::of(0, 0, 1)->isZero());
	}

	public static function provideIsEqualToData(): iterable
	{
		yield [Period::zero(), Period::zero(), true];
		yield [Period::of(-1, 0, 1), Period::of(1, 0, -1), false];
	}

	#[DataProvider('provideIsEqualToData')]
	public function testIsEqualTo(Period $a, Period $b, bool $expectedResult): void
	{
		self::assertSame($expectedResult, $a->isEqualTo($b));
		self::assertSame($expectedResult, $b->isEqualTo($a));
	}

	public static function provideToIsoStringData(): iterable
	{
		yield [Period::ofYears(1), 'P1Y'];
		yield [Period::of(1, -10, 21), 'P1Y-10M21D'];
	}

	#[DataProvider('provideToIsoStringData')]
	public function testToIsoString(Period $period, string $expectedResult): void
	{
		self::assertSame($period->toIsoString(), $expectedResult);
	}

	public function testSerialization(): void
	{
		$period = Period::of(1, 1, 1);

		$serialized = serialize($period);
		$unserialized = unserialize($serialized);

		self::assertTrue($period->isEqualTo($unserialized));
	}
}
