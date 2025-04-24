<?php

/** @generate-class-entries */

namespace Temporal
{
	final class LocalDateTime implements \JsonSerializable, \Stringable
	{
		private function __construct() {}
		public static function of(int $year, int $month, int $day, int $hour = 0, int $minute = 0, int $second = 0, int $nano = 0): LocalDateTime {}
		public static function ofDateTime(LocalDate $date, LocalTime $time): LocalDateTime {}
		public static function now(TimeZone $timeZone, Clock|null $clock = null): LocalDateTime {}
		public static function parse(string $text): LocalDateTime {}
		public static function min(): LocalDateTime {}
		public static function max(): LocalDateTime {}
		public function getDate(): LocalDate {}
		public function withDate(LocalDate $date): LocalDateTime {}
		public function getYear(): int {}
		public function withYear(int $year): LocalDateTime {}
		public function getMonth(): int {}
		public function withMonth(int $month): LocalDateTime {}
		public function getYearMonth(): YearMonth {}
		public function getWeek(): int {}
		public function getYearOfWeek(): int {}
		public function getYearWeek(): YearWeek {}
		public function getDayOfMonth(): int {}
		public function withDayOfMonth(int $dayOfMonth): LocalDateTime {}
		public function getMonthDay(): MonthDay {}
		public function getDayOfYear(): int {}
		public function getDayOfWeek(): int {}
		public function getDaysInMonth(): int {}
		public function getDaysInYear(): int {}
		public function getWeeksInYear(): int {}
		public function isLeapYear(): bool {}
		public function getTime(): LocalTime {}
		public function withTime(LocalTime $time): LocalDateTime {}
		public function getHour(): int {}
		public function withHour(int $hour): LocalDateTime {}
		public function getMinute(): int {}
		public function withMinute(int $minute): LocalDateTime {}
		public function getSecond(): int {}
		public function withSecond(int $second): LocalDateTime {}
		public function getNano(): int {}
		public function withNano(int $nano): LocalDateTime {}
		public function plusPeriod(Period $period): LocalDateTime {}
		public function plusYears(int $years): LocalDateTime {}
		public function plusMonths(int $months): LocalDateTime {}
		public function plusWeeks(int $weeks): LocalDateTime {}
		public function plusDays(int $days): LocalDateTime {}
		public function minusPeriod(Period $period): LocalDateTime {}
		public function minusYears(int $years): LocalDateTime {}
		public function minusMonths(int $months): LocalDateTime {}
		public function minusWeeks(int $weeks): LocalDateTime {}
		public function minusDays(int $days): LocalDateTime {}
		public function plusDuration(Duration $duration): LocalDateTime {}
		public function plusHours(int $hours): LocalDateTime {}
		public function plusMinutes(int $minutes): LocalDateTime {}
		public function plusSeconds(int $seconds): LocalDateTime {}
		public function plusNanos(int $nanos): LocalDateTime {}
		public function minusDuration(Duration $duration): LocalDateTime {}
		public function minusHours(int $hours): LocalDateTime {}
		public function minusMinutes(int $minutes): LocalDateTime {}
		public function minusSeconds(int $seconds): LocalDateTime {}
		public function minusNanos(int $nanos): LocalDateTime {}
		public function compareTo(LocalDateTime $other): int {}
		public function isEqualTo(LocalDateTime $other): bool {}
		public function isBefore(LocalDateTime $other): bool {}
		public function isBeforeOrEqualTo(LocalDateTime $other): bool {}
		public function isAfter(LocalDateTime $other): bool {}
		public function isAfterOrEqualTo(LocalDateTime $other): bool {}
		public function atTimeZone(TimeZone $timeZone): ZonedDateTime {}
		public function toDateTime(): \DateTimeImmutable {}
		public static function fromDateTime(\DateTimeInterface $dateTime): LocalDateTime {}
		public function toISOString(): string {}
		public function format(string $localizedPattern, string|null $locale = null): string {}
		public function formatWith(\Temporal\Format\DateTimeFormatter $formatter): string {}
		public function jsonSerialize(): string {}
		public function __toString(): string {}
		public function __serialize(): array {}
		public function __unserialize(array $data): void {}
	}
}
