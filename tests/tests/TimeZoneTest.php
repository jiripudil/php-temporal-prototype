<?php

declare(strict_types=1);

namespace Temporal\Tests;

use DateTimeZone;
use PHPUnit\Framework\Attributes\DataProvider;
use Temporal\TemporalException;
use Temporal\TimeZone;
use Temporal\TimeZoneOffset;
use Temporal\TimeZoneRegion;

final class TimeZoneTest extends TemporalTestCase
{
	public static function provideFromISOStringData(): iterable
	{
		yield ['Z', TimeZoneOffset::class, 'Z'];
		yield ['z', TimeZoneOffset::class, 'Z'];
		yield ['+01:00', TimeZoneOffset::class, '+01:00'];
		yield ['-01:00', TimeZoneOffset::class, '-01:00'];
		yield ['-01:45', TimeZoneOffset::class, '-01:45'];
		yield ['-01:17:42', TimeZoneOffset::class, '-01:17:42'];
		yield ['Europe/Prague', TimeZoneRegion::class, 'Europe/Prague'];
	}

	/**
	 * @param class-string<TimeZone> $expectedClassName
	 */
	#[DataProvider('provideFromISOStringData')]
	public function testFromISOString(string $text, string $expectedClassName, string $expectedId): void
	{
		$timeZone = TimeZone::fromISOString($text);

		self::assertInstanceOf($expectedClassName, $timeZone);
		self::assertSame($expectedId, $timeZone->getId());
	}

	public static function provideInvalidFromISOStringData(): iterable
	{
		yield [''];
		yield ['+'];
		yield ['-'];
		yield ['Europe/Non_Existent_City'];
	}

	#[DataProvider('provideInvalidFromISOStringData')]
	public function testInvalidFromISOString(string $text): void
	{
		$this->expectException(TemporalException::class);
		$this->expectExceptionMessage('Failed to parse given input into a Temporal value.');

		TimeZone::fromISOString($text);
	}

	public function testUtc(): void
	{
		$utc = TimeZone::utc();

		self::assertInstanceOf(TimeZoneOffset::class, $utc);
		self::assertTimeZoneOffset($utc, 0);
	}

	public function testIsEqualTo(): void
	{
		self::assertTrue(TimeZone::utc()->isEqualTo(TimeZoneOffset::ofTotalSeconds(0)));
		self::assertFalse(TimeZone::utc()->isEqualTo(TimeZoneOffset::ofTotalSeconds(3600)));
	}

	public static function provideFromDateTimeZoneData(): iterable
	{
		yield ['Z'];
		yield ['+01:00'];
		yield ['-01:45'];
		yield ['Europe/Prague'];
	}

	#[DataProvider('provideFromDateTimeZoneData')]
	public function testFromDateTimeZone(string $id): void
	{
		$dateTimeZone = new DateTimeZone($id);

		$timeZone = TimeZone::fromDateTimeZone($dateTimeZone);
		self::assertSame($id, $timeZone->getId());
	}
}
