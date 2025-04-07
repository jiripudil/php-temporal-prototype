<?php

declare(strict_types=1);

namespace Temporal\Tests;

use DateTimeImmutable;
use PHPUnit\Framework\Attributes\DataProvider;
use PHPUnit\Framework\Attributes\TestWith;
use Temporal\Clock\FixedClock;
use Temporal\Duration;
use Temporal\Format\DateTimeFormatter;
use Temporal\Format\FormatStyle;
use Temporal\Instant;
use Temporal\LocalTime;
use Temporal\TemporalException;
use Temporal\TimeZoneOffset;

final class LocalTimeTest extends TemporalTestCase
{
	public function testNow(): void
	{
		$clock = new FixedClock(Instant::epoch());

		$time = LocalTime::now(TimeZoneOffset::utc(), $clock);
		self::assertLocalTime($time, 0, 0);

		$time = LocalTime::now(TimeZoneOffset::of(0, -30), $clock);
		self::assertLocalTime($time, 23, 30);

		$time = LocalTime::now(TimeZoneOffset::of(1, 30), $clock);
		self::assertLocalTime($time, 1, 30);
	}

	#[TestWith(['12:30', 12, 30])]
	#[TestWith(['12:30:00', 12, 30])]
	#[TestWith(['12:30:00.000000', 12, 30])]
	#[TestWith(['12:30:59', 12, 30, 59])]
	#[TestWith(['12:30:59.000000001', 12, 30, 59, 1])]
	public function testParse(string $text, int $expectedHour, int $expectedMinute, int $expectedSecond = 0, int $expectedNano = 0): void
	{
		$time = LocalTime::parse($text);
		self::assertLocalTime($time, $expectedHour, $expectedMinute, $expectedSecond, $expectedNano);
	}

	public function testMidnight(): void
	{
		$time = LocalTime::midnight();
		self::assertLocalTime($time, 0, 0);
	}

	public function testNoon(): void
	{
		$time = LocalTime::noon();
		self::assertLocalTime($time, 12, 0);
	}

	public function testMin(): void
	{
		$time = LocalTime::min();
		self::assertLocalTime($time, 0, 0);
	}

	public function testMax(): void
	{
		$time = LocalTime::max();
		self::assertLocalTime($time, 23, 59, 59, 999_999_999);
	}

	public function testOfSecondOfDay(): void
	{
		$time = LocalTime::ofSecondOfDay(1);
		self::assertLocalTime($time, 0, 0, 1);

		$time = LocalTime::ofSecondOfDay(Duration::SECONDS_PER_DAY - 1);
		self::assertLocalTime($time, 23, 59, 59);
	}

	public function testGetSecondOfDay(): void
	{
		$time = LocalTime::of(0, 0, 1);
		self::assertSame(1, $time->getSecondOfDay());

		$time = LocalTime::of(23, 59, 59);
		self::assertSame(Duration::SECONDS_PER_DAY - 1, $time->getSecondOfDay());
	}

	public static function providePlusData(): iterable
	{
		yield [LocalTime::noon(), Duration::ofDays(1), 12, 0];
		yield [LocalTime::noon(), Duration::ofHours(24), 12, 0];
		yield [LocalTime::noon(), Duration::ofHours(12), 0, 0];
		yield [LocalTime::noon(), Duration::ofHours(1), 13, 0];
		yield [LocalTime::noon(), Duration::ofMinutes(1), 12, 1];
		yield [LocalTime::noon(), Duration::ofSeconds(1), 12, 0, 1];
		yield [LocalTime::noon(), Duration::ofSeconds(0, 1), 12, 0, 0, 1];
	}

	#[DataProvider('providePlusData')]
	public function testPlus(LocalTime $time, Duration $duration, int $expectedHour, int $expectedMinute, int $expectedSecond = 0, int $expectedNano = 0): void
	{
		self::assertLocalTime($time->plus($duration), $expectedHour, $expectedMinute, $expectedSecond, $expectedNano);
	}

	public static function provideMinusData(): iterable
	{
		yield [LocalTime::noon(), Duration::ofDays(1), 12, 0];
		yield [LocalTime::noon(), Duration::ofHours(24), 12, 0];
		yield [LocalTime::noon(), Duration::ofHours(12), 0, 0];
		yield [LocalTime::noon(), Duration::ofHours(1), 11, 0];
		yield [LocalTime::noon(), Duration::ofMinutes(1), 11, 59];
		yield [LocalTime::noon(), Duration::ofSeconds(1), 11, 59, 59];
		yield [LocalTime::noon(), Duration::ofSeconds(0, 1), 11, 59, 59, 999_999_999];
	}

	#[DataProvider('provideMinusData')]
	public function testMinus(LocalTime $time, Duration $duration, int $expectedHour, int $expectedMinute, int $expectedSecond = 0, int $expectedNano = 0): void
	{
		self::assertLocalTime($time->minus($duration), $expectedHour, $expectedMinute, $expectedSecond, $expectedNano);
	}

	public static function provideComparisonData(): iterable
	{
		yield [LocalTime::of(1, 1), LocalTime::of(1, 1), 0];
		yield [LocalTime::of(2, 2), LocalTime::of(2, 1), 1];
		yield [LocalTime::of(2, 1), LocalTime::of(2, 2), -1];
		yield [LocalTime::of(1, 2), LocalTime::of(1, 1), 1];
		yield [LocalTime::of(1, 1), LocalTime::of(1, 2), -1];
	}

	#[DataProvider('provideComparisonData')]
	public function testComparison(LocalTime $a, LocalTime $b, int $expectedResult): void
	{
		self::assertSame($expectedResult, $a->compareTo($b));
		self::assertSame(-$expectedResult, $b->compareTo($a));

		self::assertSame($expectedResult === 0, $a->isEqualTo($b));
		self::assertSame($expectedResult < 0, $a->isBefore($b));
		self::assertSame($expectedResult <= 0, $a->isBeforeOrEqualTo($b));
		self::assertSame($expectedResult > 0, $a->isAfter($b));
		self::assertSame($expectedResult >= 0, $a->isAfterOrEqualTo($b));
	}

	public function testToDateTime(): void
	{
		$time = LocalTime::of(12, 30, 59, 123_456_789);

		$dateTime = $time->toDateTime();
		self::assertSame('12', $dateTime->format('H'));
		self::assertSame('30', $dateTime->format('i'));
		self::assertSame('59', $dateTime->format('s'));
		self::assertSame('123456', $dateTime->format('u'));
	}

	public function testFromDateTime(): void
	{
		$time = LocalTime::fromDateTime(new DateTimeImmutable('1970-01-01T12:30:59.123456Z'));
		self::assertLocalTime($time, 12, 30, 59, 123_456_000);

		$time = LocalTime::fromDateTime(new DateTimeImmutable('1970-01-01T12:30:59.123456+11:00'));
		self::assertLocalTime($time, 12, 30, 59, 123_456_000);
	}

	public static function provideToISOStringData(): iterable
	{
		yield [LocalTime::of(12, 30), '12:30'];
		yield [LocalTime::of(12, 30, 59), '12:30:59'];
		yield [LocalTime::of(12, 30, 59, 1), '12:30:59.000000001'];
		yield [LocalTime::of(12, 30, 59, 499_000), '12:30:59.000499'];
		yield [LocalTime::of(12, 30, 59, 999_999_999), '12:30:59.999999999'];
	}

	#[DataProvider('provideToISOStringData')]
	public function testToISOString(LocalTime $time, string $expectedResult): void
	{
		self::assertSame($expectedResult, $time->toISOString());
	}

	public static function provideFormatData(): iterable
	{
		yield [LocalTime::of(14, 30, 59), DateTimeFormatter::ofLocalizedPattern('jamm', 'en-US'), "2:30\u{202F}PM"];
		yield [LocalTime::of(14, 30, 59), DateTimeFormatter::ofLocalizedPattern('jamm', 'cs-CZ'), '14:30'];
		yield [LocalTime::of(14, 30, 59), DateTimeFormatter::ofPattern('HH:mm:ss', 'en-US'), '14:30:59'];
		yield [LocalTime::of(14, 30, 59), DateTimeFormatter::ofPattern('h:mm a', 'en-US'), '2:30 PM'];
		yield [LocalTime::of(14, 30, 59), DateTimeFormatter::ofTime(FormatStyle::SHORT, 'en-US'), "2:30\u{202F}PM"];
	}

	#[DataProvider('provideFormatData')]
	public function testFormat(LocalTime $time, DateTimeFormatter $formatter, string $expectedResult): void
	{
		self::assertSame($expectedResult, $time->formatWith($formatter));
	}

	public static function provideInvalidFormatData(): iterable
	{
		yield [LocalTime::of(14, 30, 59), DateTimeFormatter::ofTime(FormatStyle::FULL, 'en-US')];
		yield [LocalTime::of(14, 30, 59), DateTimeFormatter::ofDate(FormatStyle::FULL, 'en-US')];
		yield [LocalTime::of(14, 30, 59), DateTimeFormatter::ofDateTime(FormatStyle::LONG, FormatStyle::FULL, 'en-US')];
	}

	#[DataProvider('provideInvalidFormatData')]
	public function testInvalidFormat(LocalTime $time, DateTimeFormatter $formatter): void
	{
		$this->expectException(TemporalException::class);
		$this->expectExceptionMessage('Failed to format a Temporal value.');

		$time->formatWith($formatter);
	}
}
