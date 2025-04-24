<?php

/** @generate-class-entries */

namespace Temporal
{
	final class LocalTime implements \JsonSerializable, \Stringable
	{
		private function __construct() {}
		public static function of(int $hour, int $minute, int $second = 0, int $nano = 0): LocalTime {}
		public static function ofSecondOfDay(int $secondOfDay, int $nano = 0): LocalTime {}
		public static function now(TimeZone $timeZone, Clock|null $clock = null): LocalTime {}
		public static function parse(string $text): LocalTime {}
		public static function midnight(): LocalTime {}
		public static function noon(): LocalTime {}
		public static function min(): LocalTime {}
		public static function max(): LocalTime {}
		public function getHour(): int {}
		public function withHour(int $hour): LocalTime {}
		public function getMinute(): int {}
		public function withMinute(int $minute): LocalTime {}
		public function getSecond(): int {}
		public function withSecond(int $second): LocalTime {}
		public function getNano(): int {}
		public function withNano(int $nano): LocalTime {}
		public function getSecondOfDay(): int {}
		public function plus(Duration $duration): LocalTime {}
		public function plusHours(int $hours): LocalTime {}
		public function plusMinutes(int $minutes): LocalTime {}
		public function plusSeconds(int $seconds): LocalTime {}
		public function plusNanos(int $nanos): LocalTime {}
		public function minus(Duration $duration): LocalTime {}
		public function minusHours(int $hours): LocalTime {}
		public function minusMinutes(int $minutes): LocalTime {}
		public function minusSeconds(int $seconds): LocalTime {}
		public function minusNanos(int $nanos): LocalTime {}
		public function atDate(LocalDate $date): LocalDateTime {}
		public function compareTo(LocalTime $other): int {}
		public function isEqualTo(LocalTime $other): bool {}
		public function isBefore(LocalTime $other): bool {}
		public function isBeforeOrEqualTo(LocalTime $other): bool {}
		public function isAfter(LocalTime $other): bool {}
		public function isAfterOrEqualTo(LocalTime $other): bool {}
		public function toDateTime(): \DateTimeImmutable {}
		public static function fromDateTime(\DateTimeInterface $dateTime): LocalTime {}
		public function toISOString(): string {}
		public function format(string $localizedPattern, string|null $locale = null): string {}
		public function formatWith(Format\DateTimeFormatter $formatter): string {}
		public function jsonSerialize(): string {}
		public function __toString(): string {}
		public function __serialize(): array {}
		public function __unserialize(array $data): void {}
	}
}
