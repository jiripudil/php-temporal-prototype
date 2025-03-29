<?php

declare(strict_types=1);

namespace Temporal;

use JsonSerializable;
use Stringable;
use function intdiv;

final class Duration implements JsonSerializable, Stringable
{
	public const NANOS_PER_SECOND = 1_000_000_000;
	public const SECONDS_PER_MINUTE = 60;
	public const SECONDS_PER_HOUR = 3600;
	public const SECONDS_PER_DAY = 86400;
	public const MINUTES_PER_HOUR = 60;
	public const HOURS_PER_DAY = 24;

	private function __construct() {}

	public static function zero(): self {}

	public static function parse(string $value): self {}

	public static function ofSeconds(int $seconds, int $nanoAdjustment = 0): self {}

	public static function ofMinutes(int $minutes): self {}

	public static function ofHours(int $hours): self {}

	public static function ofDays(int $days): self {}

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

	public function plus(self $other): self {}

	public function plusSeconds(int $seconds): self {}

	public function plusMinutes(int $minutes): self {}

	public function plusHours(int $hours): self {}

	public function plusDays(int $days): self {}

	public function minus(self $other): self {}

	public function minusSeconds(int $seconds): self {}

	public function minusMinutes(int $minutes): self {}

	public function minusHours(int $hours): self {}

	public function minusDays(int $days): self {}

	public function negated(): self {}

	public function abs(): self {}

	public function compareTo(self $other): int {}

	public function isEqualTo(self $other): bool {}

	public function isGreaterThan(self $other): bool {}

	public function isGreaterThanOrEqualTo(self $other): bool {}

	public function isLesserThan(self $other): bool {}

	public function isLesserThanOrEqualTo(self $other): bool {}

	public function toISOString(): string {}

	public function jsonSerialize(): string {}

	public function __toString(): string {}
}
