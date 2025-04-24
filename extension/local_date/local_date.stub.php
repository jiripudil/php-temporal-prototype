<?php

/** @generate-class-entries */

namespace Temporal
{
	final class LocalDate implements \JsonSerializable, \Stringable
	{
		private function __construct() {}
		public static function of(int $year, int $month, int $day): LocalDate {}
		public static function ofDayOfYear(int $year, int $dayOfYear): LocalDate {}
		public static function ofEpochDay(int $epochDay): LocalDate {}
		public static function now(TimeZone $timeZone, Clock|null $clock = null): LocalDate {}
		public static function fromISOString(string $text): LocalDate {}
		public static function min(): LocalDate {}
		public static function max(): LocalDate {}
		public function getYear(): int {}
		public function withYear(int $year): LocalDate {}
		public function getMonth(): int {}
		public function withMonth(int $month): LocalDate {}
		public function getYearMonth(): YearMonth {}
		public function getWeek(): int {}
		public function getYearOfWeek(): int {}
		public function getYearWeek(): YearWeek {}
		public function getDayOfMonth(): int {}
		public function withDayOfMonth(int $dayOfMonth): LocalDate {}
		public function getMonthDay(): MonthDay {}
		public function getDayOfYear(): int {}
		public function getDayOfWeek(): int {}
		public function getDaysInMonth(): int {}
		public function getDaysInYear(): int {}
		public function getWeeksInYear(): int {}
		public function isLeapYear(): bool {}
		public function toEpochDay(): int {}
		public function plus(Period $period): LocalDate {}
		public function plusYears(int $years): LocalDate {}
		public function plusMonths(int $months): LocalDate {}
		public function plusWeeks(int $weeks): LocalDate {}
		public function plusDays(int $days): LocalDate {}
		public function minus(Period $period): LocalDate {}
		public function minusYears(int $years): LocalDate {}
		public function minusMonths(int $months): LocalDate {}
		public function minusWeeks(int $weeks): LocalDate {}
		public function minusDays(int $days): LocalDate {}
		public function until(LocalDate $endExclusive): Period {}
		public function daysUntil(LocalDate $endExclusive): int {}
		public function atTime(LocalTime $time): LocalDateTime {}
		public function compareTo(LocalDate $other): int {}
		public function isEqualTo(LocalDate $other): bool {}
		public function isBefore(LocalDate $other): bool {}
		public function isBeforeOrEqualTo(LocalDate $other): bool {}
		public function isAfter(LocalDate $other): bool {}
		public function isAfterOrEqualTo(LocalDate $other): bool {}
		public function toDateTime(): \DateTimeImmutable {}
		public static function fromDateTime(\DateTimeInterface $dateTime): LocalDate {}
		public function toISOString(): string {}
		public function format(string $localizedPattern, string|null $locale = null): string {}
		public function formatWith(\Temporal\Format\DateTimeFormatter $formatter): string {}
		public function jsonSerialize(): string {}
		public function __toString(): string {}
		public function __serialize(): array {}
		public function __unserialize(array $data): void {}
	}
}
