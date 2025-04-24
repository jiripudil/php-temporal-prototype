<?php

declare(strict_types=1);

namespace Temporal\Tests;

use PHPUnit\Framework\Attributes\DataProvider;
use Temporal\Instant;
use Temporal\TemporalException;
use Temporal\TimeZoneRegion;

final class TimeZoneRegionTest extends TemporalTestCase
{
	public function testOf(): void
	{
		$timeZone = TimeZoneRegion::of('Europe/Prague');
		self::assertSame('Europe/Prague', $timeZone->getId());
	}

	public static function provideInvalidOfData(): iterable
	{
		yield [''];
		yield ['Z'];
		yield ['+01:00'];
		yield ['-01:00'];
		yield ['Europe/Non_Existent_City'];
	}

	#[DataProvider('provideInvalidOfData')]
	public function testInvalidOf(string $text): void
	{
		$this->expectException(TemporalException::class);
		TimeZoneRegion::of($text);
	}

	public static function provideGetOffsetData(): iterable
	{
		yield [TimeZoneRegion::of('Europe/Prague'), Instant::of(1_700_000_000), 3600];
		yield [TimeZoneRegion::of('Europe/London'), Instant::of(1_700_000_000), 0];

		yield [TimeZoneRegion::of('Europe/Prague'), Instant::of(1_750_000_000), 7200];
		yield [TimeZoneRegion::of('Europe/London'), Instant::of(1_750_000_000), 3600];
	}

	#[DataProvider('provideGetOffsetData')]
	public function testGetOffset(TimeZoneRegion $timeZone, Instant $instant, int $expectedOffset): void
	{
		$actualOffset = $timeZone->getOffset($instant);
		self::assertSame($expectedOffset, $actualOffset);
	}

	public function testToDateTimeZone(): void
	{
		$timeZone = TimeZoneRegion::of('Europe/Prague');
		$dateTimeZone = $timeZone->toDateTimeZone();

		self::assertSame('Europe/Prague', $dateTimeZone->getName());
	}

	public function testSerialization(): void
	{
		$zone = TimeZoneRegion::of('Europe/Prague');

		$serialized = serialize($zone);
		$unserialized = unserialize($serialized);

		self::assertTrue($zone->isEqualTo($unserialized));
	}
}
