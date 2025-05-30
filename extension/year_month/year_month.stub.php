<?php

/**
 * @generate-class-entries
 * @generate-legacy-arginfo 80100
 */

namespace Temporal
{
	final class YearMonth implements \JsonSerializable, \Stringable
	{
		private function __construct() {}
		public static function of(int $year, int $month): YearMonth {}
		public static function now(TimeZone $timeZone, Clock|null $clock = null): YearMonth {}
		public static function fromISOString(string $text): YearMonth {}
		public function getYear(): int {}
		public function withYear(int $year): YearMonth {}
		public function plusYears(int $years): YearMonth {}
		public function minusYears(int $years): YearMonth {}
		public function getMonth(): int {}
		public function withMonth(int $month): YearMonth {}
		public function plusMonths(int $months): YearMonth {}
		public function minusMonths(int $months): YearMonth {}
		public function getDaysInMonth(): int {}
		public function getDaysInYear(): int {}
		public function getWeeksInYear(): int {}
		public function isLeapYear(): bool {}
		public function atDay(int $dayOfMonth): LocalDate {}
		public function getFirstDay(): LocalDate {}
		public function getLastDay(): LocalDate {}
		public function compareTo(YearMonth $other): int {}
		public function isEqualTo(YearMonth $other): bool {}
		public function isBefore(YearMonth $other): bool {}
		public function isBeforeOrEqualTo(YearMonth $other): bool {}
		public function isAfter(YearMonth $other): bool {}
		public function isAfterOrEqualTo(YearMonth $other): bool {}
		public function toISOString(): string {}
		public function jsonSerialize(): string {}
		public function __toString(): string {}
		public function __serialize(): array {}
		public function __unserialize(array $data): void {}
	}
}
