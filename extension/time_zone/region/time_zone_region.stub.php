<?php

/**
 * @generate-class-entries
 * @generate-legacy-arginfo 80100
 */

namespace Temporal
{
	final class TimeZoneRegion extends TimeZone
	{
		private function __construct() {}
		public static function of(string $id): TimeZoneRegion {}
		public static function fromISOString(string $text): TimeZoneRegion {}
		public function getId(): string {}
		public function getOffset(Instant $instant): int {}
		public function toDateTimeZone(): \DateTimeZone {}
		public function __serialize(): array {}
		public function __unserialize(array $data): void {}
	}
}
