<?php

/**
 * @generate-class-entries
 * @generate-legacy-arginfo 80100
 */

namespace Temporal
{
	abstract class TimeZone implements \JsonSerializable, \Stringable
	{
		public static function fromIsoString(string $text): TimeZone {}
		public static function utc(): TimeZone {}
		abstract public function getId(): string {}
		abstract public function getOffset(Instant $instant): int {}
		public function isEqualTo(TimeZone $other): bool {}
		abstract public function toDateTimeZone(): \DateTimeZone {}
		public static function fromDateTimeZone(\DateTimeZone $zone): TimeZone {}
		public function jsonSerialize(): string {}
		public function __toString(): string {}
	}
}
