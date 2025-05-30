<?php

/**
 * @generate-class-entries
 * @generate-legacy-arginfo 80100
 */

namespace Temporal
{
	final class ZonedDateTime implements \JsonSerializable, \Stringable
	{
		private function __construct() {}
		public static function of(LocalDateTime $dateTime, TimeZone $timeZone): ZonedDateTime {}
		public static function ofInstant(Instant $instant, TimeZone $timeZone): ZonedDateTime {}
		public static function now(TimeZone $timeZone, Clock|null $clock = null): ZonedDateTime {}
		public static function fromISOString(string $text): ZonedDateTime {}
		public function getDateTime(): LocalDateTime {}
		public function getDate(): LocalDate {}
		public function withDate(LocalDate $date): ZonedDateTime {}
		public function getYear(): int {}
		public function withYear(int $year): ZonedDateTime {}
		public function getMonth(): int {}
		public function withMonth(int $month): ZonedDateTime {}
		public function getYearMonth(): YearMonth {}
		public function getWeek(): int {}
		public function getYearOfWeek(): int {}
		public function getYearWeek(): YearWeek {}
		public function getDayOfMonth(): int {}
		public function withDayOfMonth(int $dayOfMonth): ZonedDateTime {}
		public function getMonthDay(): MonthDay {}
		public function getDayOfYear(): int {}
		public function getDayOfWeek(): int {}
		public function getDaysInMonth(): int {}
		public function getDaysInYear(): int {}
		public function getWeeksInYear(): int {}
		public function isLeapYear(): bool {}
		public function getTime(): LocalTime {}
		public function withTime(LocalTime $time): ZonedDateTime {}
		public function getHour(): int {}
		public function withHour(int $hour): ZonedDateTime {}
		public function getMinute(): int {}
		public function withMinute(int $minute): ZonedDateTime {}
		public function getSecond(): int {}
		public function withSecond(int $second): ZonedDateTime {}
		public function getNano(): int {}
		public function withNano(int $nano): ZonedDateTime {}
		public function getInstant(): Instant {}
		public function getTimeZone(): TimeZone {}
		public function getTimeZoneOffset(): TimeZoneOffset {}
		public function withTimeZoneSameLocal(TimeZone $timeZone): ZonedDateTime {}
		public function withTimeZoneSameInstant(TimeZone $timeZone): ZonedDateTime {}
		public function withFixedOffsetTimeZone(): ZonedDateTime {}
		public function plusPeriod(Period $period): ZonedDateTime {}
		public function plusYears(int $years): ZonedDateTime {}
		public function plusMonths(int $months): ZonedDateTime {}
		public function plusWeeks(int $weeks): ZonedDateTime {}
		public function plusDays(int $days): ZonedDateTime {}
		public function minusPeriod(Period $period): ZonedDateTime {}
		public function minusYears(int $years): ZonedDateTime {}
		public function minusMonths(int $months): ZonedDateTime {}
		public function minusWeeks(int $weeks): ZonedDateTime {}
		public function minusDays(int $days): ZonedDateTime {}
		public function plusDuration(Duration $duration): ZonedDateTime {}
		public function plusHours(int $hours): ZonedDateTime {}
		public function plusMinutes(int $minutes): ZonedDateTime {}
		public function plusSeconds(int $seconds): ZonedDateTime {}
		public function plusNanos(int $nanos): ZonedDateTime {}
		public function minusDuration(Duration $duration): ZonedDateTime {}
		public function minusHours(int $hours): ZonedDateTime {}
		public function minusMinutes(int $minutes): ZonedDateTime {}
		public function minusSeconds(int $seconds): ZonedDateTime {}
		public function minusNanos(int $nanos): ZonedDateTime {}
		public function compareTo(ZonedDateTime $other): int {}
		public function isEqualTo(ZonedDateTime $other): bool {}
		public function isBefore(ZonedDateTime $other): bool {}
		public function isBeforeOrEqualTo(ZonedDateTime $other): bool {}
		public function isAfter(ZonedDateTime $other): bool {}
		public function isAfterOrEqualTo(ZonedDateTime $other): bool {}
		public function toDateTime(): \DateTimeImmutable {}
		public static function fromDateTime(\DateTimeInterface $dateTime): ZonedDateTime {}
		public function toISOString(): string {}
		public function format(string $localizedPattern, string|null $locale = null): string {}
		public function formatWith(Format\DateTimeFormatter $formatter): string {}
		public function jsonSerialize(): string {}
		public function __toString(): string {}
		public function __serialize(): array {}
		public function __unserialize(array $data): void {}
	}
}
