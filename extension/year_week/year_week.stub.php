<?php

/** @generate-class-entries */

namespace Temporal
{
	final class YearWeek implements \JsonSerializable, \Stringable
	{
		private function __construct() {}
		public static function of(int $year, int $month): YearWeek {}
		public static function now(TimeZone $timeZone, Clock|null $clock = null): YearWeek {}
		public static function fromISOString(string $text): YearWeek {}
		public function getYear(): int {}
		public function withYear(int $year): YearWeek {}
		public function plusYears(int $years): YearWeek {}
		public function minusYears(int $years): YearWeek {}
		public function getWeek(): int {}
		public function withWeek(int $week): YearWeek {}
		public function plusWeeks(int $weeks): YearWeek {}
		public function minusWeeks(int $weeks): YearWeek {}
		public function getDaysInYear(): int {}
		public function getWeeksInYear(): int {}
		public function isLeapYear(): bool {}
		public function atDay(int $dayOfWeek): LocalDate {}
		public function getFirstDay(): LocalDate {}
		public function getLastDay(): LocalDate {}
		public function compareTo(YearWeek $other): int {}
		public function isEqualTo(YearWeek $other): bool {}
		public function isBefore(YearWeek $other): bool {}
		public function isBeforeOrEqualTo(YearWeek $other): bool {}
		public function isAfter(YearWeek $other): bool {}
		public function isAfterOrEqualTo(YearWeek $other): bool {}
		public function toISOString(): string {}
		public function jsonSerialize(): string {}
		public function __toString(): string {}
		public function __serialize(): array {}
		public function __unserialize(array $data): void {}
	}
}
