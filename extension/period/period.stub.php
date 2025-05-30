<?php

/**
 * @generate-class-entries
 * @generate-legacy-arginfo 80100
 */

namespace Temporal
{
	final class Period implements \JsonSerializable, \Stringable
	{
		private function __construct() {}
		public static function of(int $years, int $months, int $days): Period {}
		public static function ofYears(int $years): Period {}
		public static function ofMonths(int $months): Period {}
		public static function ofWeeks(int $weeks): Period {}
		public static function ofDays(int $days): Period {}
		public static function zero(): Period {}
		public static function between(LocalDate $start, LocalDate $endExclusive): Period {}
		public static function fromISOString(string $text): Period {}
		public function getYears(): int {}
		public function withYears(int $years): Period {}
		public function plusYears(int $years): Period {}
		public function minusYears(int $years): Period {}
		public function getMonths(): int {}
		public function withMonths(int $months): Period {}
		public function plusMonths(int $months): Period {}
		public function minusMonths(int $months): Period {}
		public function getDays(): int {}
		public function withDays(int $days): Period {}
		public function plusDays(int $days): Period {}
		public function minusDays(int $days): Period {}
		public function negated(): Period {}
		public function isZero(): bool {}
		public function isEqualTo(Period $other): bool {}
		public function toISOString(): string {}
		public function jsonSerialize(): string {}
		public function __toString(): string {}
		public function __serialize(): array {}
		public function __unserialize(array $data): void {}
	}
}
