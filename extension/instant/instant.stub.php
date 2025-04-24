<?php

/** @generate-class-entries */

namespace Temporal
{
	final class Instant implements \JsonSerializable, \Stringable
	{
		private function __construct() {}
		public static function of(int $epochSecond, int $nanoAdjustment = 0): Instant {}
		public static function now(Clock|null $clock = null): Instant {}
		public static function epoch(): Instant {}
		public static function min(): Instant {}
		public static function max(): Instant {}
		public function getEpochSecond(): int {}
		public function getNano(): int {}
		public function withEpochSecond(int $epochSecond): Instant {}
		public function withNano(int $nano): Instant {}
		public function plus(Duration $duration): Instant {}
		public function plusSeconds(int $seconds): Instant {}
		public function plusMinutes(int $minutes): Instant {}
		public function plusHours(int $hours): Instant {}
		public function plusDays(int $days): Instant {}
		public function minus(Duration $duration): Instant {}
		public function minusSeconds(int $seconds): Instant {}
		public function minusMinutes(int $minutes): Instant {}
		public function minusHours(int $seconds): Instant {}
		public function minusDays(int $days): Instant {}
		public function compareTo(Instant $other): int {}
		public function isEqualTo(Instant $other): bool {}
		public function isBefore(Instant $other): bool {}
		public function isBeforeOrEqualTo(Instant $other): bool {}
		public function isAfter(Instant $other): bool {}
		public function isAfterOrEqualTo(Instant $other): bool {}
		public function atTimeZone(TimeZone $timeZone): ZonedDateTime {}
		public function toDecimal(): string {}
		public function toISOString(): string {}
		public function jsonSerialize(): string {}
		public function __toString(): string {}
		public function __serialize(): array {}
		public function __unserialize(array $data): void {}
	}
}
