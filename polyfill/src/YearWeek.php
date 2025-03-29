<?php

declare(strict_types=1);

namespace Temporal;

use JsonSerializable;
use Stringable;

final class YearWeek implements JsonSerializable, Stringable
{
	private function __construct() {}

	public static function of(int $year, int $week): self {}

	public static function now(TimeZone $timeZone, Clock|null $clock = null): self {}

	public static function parse(string $text): self {}

	public function getYear(): int {}

	public function withYear(int $year): self {}

	public function plusYears(int $years): self {}

	public function minusYears(int $years): self {}

	public function getWeek(): int {}

	public function withWeek(int $week): self {}

	public function plusWeeks(int $weeks): self {}

	public function minusWeeks(int $weeks): self {}

	public function getDaysInYear(): int {}

	public function getWeeksInYear(): int {}

	public function isLeapYear(): bool {}

	public function atDay(int $dayOfWeek): LocalDate {}

	public function getFirstDay(): LocalDate {}

	public function getLastDay(): LocalDate {}

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
