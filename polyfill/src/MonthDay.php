<?php

declare(strict_types=1);

namespace Temporal;

use JsonSerializable;
use Stringable;

final class MonthDay implements JsonSerializable, Stringable
{
	private function __construct() {}

	public static function of(int $month, int $day): self {}

	public static function now(TimeZone $timeZone, Clock|null $clock = null): self {}

	public static function parse(string $text): self {}

	public function getMonth(): int {}

	public function withMonth(int $month): self {}

	public function getDayOfMonth(): int {}

	public function withDayOfMonth(int $day): self {}

	public function getDaysInMonth(): int {}

	public function existsInYear(int $year): bool {}

	public function atYear(int $year): LocalDate {}

	public function compareTo(self $other): int {}

	public function isEqualTo(self $other): bool {}

	public function isBefore(self $other): bool {}

	public function isBeforeOrEqualTo(self $other): bool {}

	public function isAfter(self $other): bool {}

	public function isAfterOrEqualTo(self $other): bool {}

	public function toISOString(): string {}

	public function jsonSerialize(): string {}

	public function __toString(): string {}
}
