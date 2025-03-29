<?php

declare(strict_types=1);

namespace Temporal;

use DateTimeImmutable;
use DateTimeInterface;
use JsonSerializable;
use Stringable;
use Temporal\Format\DateTimeFormatter;

final class ZonedDateTime implements JsonSerializable, Stringable
{
	private function __construct() {}

	public static function of(LocalDateTime $dateTime, TimeZone $timeZone): self {}

	public static function ofInstant(Instant $instant, TimeZone $timeZone): self {}

	public static function now(TimeZone $timeZone, Clock|null $clock = null): self {}

	public static function parse(string $text): self {}

	public function getDateTime(): LocalDateTime {}

	public function getDate(): LocalDate {}

	public function withDate(LocalDate $date): self {}

	public function getYear(): int {}

	public function withYear(int $year): self {}

	public function getMonth(): int {}

	public function withMonth(int $month): self {}

	public function getYearMonth(): YearMonth {}

	public function getWeek(): int {}

	public function getYearOfWeek(): int {}

	public function getYearWeek(): YearWeek {}

	public function getDayOfMonth(): int {}

	public function withDayOfMonth(int $dayOfMonth): self {}

	public function getMonthDay(): MonthDay {}

	public function withMonthDay(MonthDay $monthDay): self {}

	public function getDayOfYear(): int {}

	public function withDayOfYear(int $dayOfYear): self {}

	public function getDayOfWeek(): int {}

	public function getDaysInMonth(): int {}

	public function getDaysInYear(): int {}

	public function getWeeksInYear(): int {}

	public function isLeapYear(): bool {}

	public function getTime(): LocalTime {}

	public function withTime(LocalTime $time): self {}

	public function getHour(): int {}

	public function withHour(int $hour): self {}

	public function getMinute(): int {}

	public function withMinute(int $minute): self {}

	public function getSecond(): int {}

	public function withSecond(int $second): self {}

	public function getNano(): int {}

	public function withNano(int $nano): self {}

	public function getInstant(): self {}

	public function getTimeZone(): TimeZone {}

	public function getTimeZoneOffset(): TimeZoneOffset {}

	public function withTimeZoneSameLocal(TimeZone $timeZone): self {}
	
	public function withTimeZoneSameInstant(TimeZone $timeZone): self {}

	public function withFixedOffsetTimeZone(): self {}

	public function plusPeriod(Period $period): self {}

	public function plusYears(int $years): self {}

	public function plusMonths(int $months): self {}

	public function plusWeeks(int $weeks): self {}

	public function plusDays(int $days): self {}

	public function minusPeriod(Period $period): self {}

	public function minusYears(int $years): self {}

	public function minusMonths(int $months): self {}

	public function minusWeeks(int $weeks): self {}

	public function minusDays(int $days): self {}

	public function plusDuration(Duration $duration): self {}

	public function plusHours(int $hours): self {}

	public function plusMinutes(int $minutes): self {}

	public function plusSeconds(int $seconds): self {}

	public function plusNanos(int $nanos): self {}

	public function minusDuration(Duration $duration): self {}

	public function minusHours(int $hours): self {}

	public function minusMinutes(int $minutes): self {}

	public function minusSeconds(int $seconds): self {}

	public function minusNanos(int $nanos): self {}

	public function compareTo(self $other): int {}

	public function isEqualTo(self $other): bool {}

	public function isBefore(self $other): bool {}

	public function isBeforeOrEqualTo(self $other): bool {}

	public function isAfter(self $other): bool {}

	public function isAfterOrEqualTo(self $other): bool {}

	public function toDateTime(): DateTimeImmutable {}

	public static function fromDateTime(DateTimeInterface $dateTime): self {}

	public function toISOString(): string {}

	public function format(string $localizedPattern, string|null $locale = null): string {}

	public function formatWith(DateTimeFormatter $formatter): string {}

	public function jsonSerialize(): string {}

	public function __toString(): string {}
}
