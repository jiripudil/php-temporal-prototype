<?php

/**
 * @generate-class-entries
 * @generate-legacy-arginfo 80100
 */

namespace Temporal
{
	final class MonthDay implements \JsonSerializable, \Stringable
	{
		private function __construct() {}
		public static function of(int $month, int $day): MonthDay {}
		public static function now(TimeZone $timeZone, Clock|null $clock = null): MonthDay {}
		public static function fromIsoString(string $text): MonthDay {}
		public function getMonth(): int {}
		public function withMonth(int $month): MonthDay {}
		public function getDayOfMonth(): int {}
		public function withDayOfMonth(int $day): MonthDay {}
		public function existsInYear(int $year): bool {}
		public function atYear(int $year): LocalDate {}
		public function compareTo(MonthDay $other): int {}
		public function isEqualTo(MonthDay $other): bool {}
		public function isBefore(MonthDay $other): bool {}
		public function isBeforeOrEqualTo(MonthDay $other): bool {}
		public function isAfter(MonthDay $other): bool {}
		public function isAfterOrEqualTo(MonthDay $other): bool {}
		public function toIsoString(): string {}
		public function jsonSerialize(): string {}
		public function __toString(): string {}
		public function __serialize(): array {}
		public function __unserialize(array $data): void {}
	}
}
