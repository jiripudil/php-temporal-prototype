<?php

/** @generate-class-entries */

namespace Temporal
{
	final class TimeZoneOffset extends TimeZone
	{
		private function __construct() {}
		public static function of(int $hours, int $minutes = 0, int $seconds = 0): TimeZoneOffset {}
		public static function ofTotalSeconds(int $totalSeconds): TimeZoneOffset {}
		public static function fromISOString(string $text): TimeZoneOffset {}
		public static function utc(): TimeZoneOffset {}
		public function getTotalSeconds(): int {}
		public function getId(): string {}
		public function getOffset(Instant $instant): int {}
		public function toDateTimeZone(): \DateTimeZone {}
		public function __serialize(): array {}
		public function __unserialize(array $data): void {}
	}
}
