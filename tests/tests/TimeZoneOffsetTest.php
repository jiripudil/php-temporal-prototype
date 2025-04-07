<?php

declare(strict_types=1);

namespace Temporal\Tests;

use DateTimeImmutable;
use PHPUnit\Framework\Attributes\DataProvider;
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

	public function testUtc(): void
	{
		$utc = TimeZoneOffset::utc();

		self::assertTimeZoneOffset($utc, 0);
		self::assertSame('Z', $utc->getId());
	}

	public static function provideParseData(): iterable
	{
		yield ['Z', 0];
		yield ['+01:00', 3600];
		yield ['-01:00', -3600];
		yield ['-01:45', -6300];
		yield ['-01:17:42', -4662];;
	}

	#[DataProvider('provideParseData')]
	public function testParse(string $text, int $expectedTotalSeconds): void
	{
		$timeZone = TimeZoneOffset::parse($text);
		self::assertTimeZoneOffset($timeZone, $expectedTotalSeconds);
	}

	public static function provideInvalidParseData(): iterable
	{
		yield [''];
		yield ['+01'];
		yield ['01:00'];
		yield ['+1:00'];
		yield ['+01:1'];
	}

	#[DataProvider('provideInvalidParseData')]
	public function testInvalidParse(string $text): void
	{
		$this->expectException(TemporalException::class);
		$this->expectExceptionMessage('Failed to parse given input into a Temporal value.');

		TimeZoneOffset::parse($text);
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
}
