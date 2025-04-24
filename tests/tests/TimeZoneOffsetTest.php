<?php

declare(strict_types=1);

namespace Temporal\Tests;

use DateTimeImmutable;
use PHPUnit\Framework\Attributes\DataProvider;
use PHPUnit\Framework\Attributes\TestWith;
use Temporal\Instant;
use Temporal\TemporalException;
use Temporal\TimeZoneOffset;

final class TimeZoneOffsetTest extends TemporalTestCase
{
	public static function provideOfData(): iterable
	{
		yield [0, 0, 0, 0];
		yield [0, 1, 0, 60];
		yield [1, 0, 0, 3600];
		yield [-1, 0, 0, -3600];
		yield [5, 30, 0, 19800];
		yield [5, 30, 30, 19830];
	}

	#[DataProvider('provideOfData')]
	public function testOf(int $hours, int $minutes, int $seconds, int $expectedTotalSeconds): void
	{
		$timeZone = TimeZoneOffset::of($hours, $minutes, $seconds);
		self::assertTimeZoneOffset($timeZone, $expectedTotalSeconds);
	}

	public static function provideInvalidOfData(): iterable
	{
		yield [24, 0, 0];
		yield [0, 60, 0];
		yield [0, 0, -60];
		yield [1, -30, 0];
	}

	#[DataProvider('provideInvalidOfData')]
	public function testInvalidOf(int $hours, int $minutes, int $seconds): void
	{
		$this->expectException(TemporalException::class);
		TimeZoneOffset::of($hours, $minutes, $seconds);
	}

	#[TestWith([0])]
	#[TestWith([-3600])]
	#[TestWith([3600])]
	public function testOfTotalSeconds(int $totalSeconds): void
	{
		$timeZone = TimeZoneOffset::ofTotalSeconds($totalSeconds);
		self::assertTimeZoneOffset($timeZone, $totalSeconds);;
	}

	#[TestWith([-68000])]
	#[TestWith([68000])]
	public function testInvalidOfTotalSeconds(int $totalSeconds): void
	{
		$this->expectException(TemporalException::class);
		TimeZoneOffset::ofTotalSeconds($totalSeconds);
	}

	public function testUtc(): void
	{
		$utc = TimeZoneOffset::utc();

		self::assertTimeZoneOffset($utc, 0);
		self::assertSame('Z', $utc->getId());
	}

	public static function provideFromISOStringData(): iterable
	{
		yield ['Z', 0];
		yield ['+01:00', 3600];
		yield ['-01:00', -3600];
		yield ['-01:45', -6300];
		yield ['-01:17:42', -4662];;
	}

	#[DataProvider('provideFromISOStringData')]
	public function testFromISOString(string $text, int $expectedTotalSeconds): void
	{
		$timeZone = TimeZoneOffset::fromISOString($text);
		self::assertTimeZoneOffset($timeZone, $expectedTotalSeconds);
	}

	public static function provideInvalidFromISOStringData(): iterable
	{
		yield [''];
		yield ['+01'];
		yield ['01:00'];
		yield ['+1:00'];
		yield ['+01:1'];
	}

	#[DataProvider('provideInvalidFromISOStringData')]
	public function testInvalidFromISOString(string $text): void
	{
		$this->expectException(TemporalException::class);
		$this->expectExceptionMessage('Failed to parse given input into a Temporal value.');

		TimeZoneOffset::fromISOString($text);
	}

	public function testGetOffset(): void
	{
		$instant = Instant::of(1_800_000_000);
		$timeZone = TimeZoneOffset::ofTotalSeconds(-18_000);

		self::assertSame(-18_000, $timeZone->getOffset($instant));
	}

	public static function provideToDateTimeZoneData(): iterable
	{
		yield [-1, '-00:00:01'];
		yield [3600, '+01:00'];
		yield [-3630, '-01:00:30'];
		yield [-18_000, '-05:00'];
	}

	#[DataProvider('provideToDateTimeZoneData')]
	public function testToDateTimeZone(int $totalSeconds, string $expectedName): void
	{
		$timeZone = TimeZoneOffset::ofTotalSeconds($totalSeconds);
		$dateTimeZone = $timeZone->toDateTimeZone();

		self::assertSame($expectedName, $dateTimeZone->getName());
		self::assertSame($totalSeconds, $dateTimeZone->getOffset(new DateTimeImmutable()));
	}

	public function testSerialization(): void
	{
		$zone = TimeZoneOffset::of(1, 30);

		$serialized = serialize($zone);
		$unserialized = unserialize($serialized);

		self::assertTrue($zone->isEqualTo($unserialized));
	}
}
