<?php

/** @generate-class-entries */

namespace Temporal
{
	final class Duration implements \JsonSerializable, \Stringable
	{
		public const int NANOS_PER_SECOND = 1_000_000_000;
		public const int SECONDS_PER_MINUTE = 60;
		public const int SECONDS_PER_HOUR = 3600;
		public const int SECONDS_PER_DAY = 86400;
		public const int MINUTES_PER_HOUR = 60;
		public const int HOURS_PER_DAY = 24;
	
		private function __construct() {}
		public static function zero(): Duration {}
		public static function fromISOString(string $value): Duration {}
		public static function ofSeconds(int $seconds, int $nanoAdjustment = 0): Duration {}
		public static function ofMinutes(int $minutes): Duration {}
		public static function ofHours(int $hours): Duration {}
		public static function ofDays(int $days): Duration {}
		public static function between(Instant $start, Instant $endExclusive): Duration {}
		public function getSeconds(): int {}
		public function getNanos(): int {}
		public function toDays(): int {}
		public function toDaysPart(): int {}
		public function toHours(): int {}
		public function toHoursPart(): int {}
		public function toMinutes(): int {}
		public function toMinutesPart(): int {}
		public function toSeconds(): int {}
		public function toSecondsPart(): int {}
		public function isZero(): bool {}
		public function isPositive(): bool {}
		public function isPositiveOrZero(): bool {}
		public function isNegative(): bool {}
		public function isNegativeOrZero(): bool {}
		public function plus(Duration $other): Duration {}
		public function plusSeconds(int $seconds): Duration {}
		public function plusMinutes(int $minutes): Duration {}
		public function plusHours(int $hours): Duration {}
		public function plusDays(int $days): Duration {}
		public function minus(Duration $other): Duration {}
		public function minusSeconds(int $seconds): Duration {}
		public function minusMinutes(int $minutes): Duration {}
		public function minusHours(int $hours): Duration {}
		public function minusDays(int $days): Duration {}
		public function negated(): Duration {}
		public function abs(): Duration {}
		public function compareTo(Duration $other): int {}
		public function isEqualTo(Duration $other): bool {}
		public function isGreaterThan(Duration $other): bool {}
		public function isGreaterThanOrEqualTo(Duration $other): bool {}
		public function isLesserThan(Duration $other): bool {}
		public function isLesserThanOrEqualTo(Duration $other): bool {}
		public function toISOString(): string {}
		public function jsonSerialize(): string {}
		public function __toString(): string {}
		public function __serialize(): array {}
		public function __unserialize(array $data): void {}
	}

}
