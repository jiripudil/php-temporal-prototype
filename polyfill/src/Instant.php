<?php

declare(strict_types=1);

namespace Temporal;

use JsonSerializable;
use Stringable;

final class Instant implements JsonSerializable, Stringable
{
	private function __construct() {}

	public static function epoch(): self {}

	public static function of(int $epochSecond, int $nanoAdjustment = 0): self {}

	public static function now(Clock|null $clock = null): self {}

	public static function min(): self {}

	public static function max(): self {}

	public function getEpochSecond(): int {}

	public function getNano(): int {}

	public function withEpochSecond(int $epochSecond): self {}

	public function withNano(int $nano): self {}

	public function plus(Duration $duration): self {}

	public function plusSeconds(int $seconds): self {}

	public function plusMinutes(int $seconds): self {}

	public function plusHours(int $seconds): self {}

	public function plusDays(int $seconds): self {}

	public function minus(Duration $duration): self {}

	public function minusSeconds(int $seconds): self {}

	public function minusMinutes(int $seconds): self {}

	public function minusHours(int $seconds): self {}

	public function minusDays(int $seconds): self {}

	public function compareTo(self $other): int {}

	public function isEqualTo(self $other): bool {}

	public function isBefore(self $other): bool {}

	public function isBeforeOrEqualTo(self $other): bool {}

	public function isAfter(self $other): bool {}

	public function isAfterOrEqualTo(self $other): bool {}

	public function atTimeZone(TimeZone $timeZone): ZonedDateTime {}

	public function toDecimal(): string {}

	public function toISOString(): string {}

	public function jsonSerialize(): string {}

	public function __toString(): string {}
}
