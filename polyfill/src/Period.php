<?php

declare(strict_types=1);

namespace Temporal;

use JsonSerializable;
use Stringable;

final class Period implements JsonSerializable, Stringable
{
	private function __construct() {}

	public static function of(int $years, int $months, int $days): self {}

	public static function ofYears(int $years): self {}

	public static function ofMonths(int $months): self {}

	public static function ofWeeks(int $weeks): self {}

	public static function ofDays(int $days): self {}

	public static function zero(): self {}

	public static function between(LocalDate $start, LocalDate $endExclusive): self {}

	public static function parse(string $text): self {}

	public function getYears(): int {}

	public function withYears(int $years): self {}

	public function plusYears(int $years): self {}

	public function minusYears(int $years): self {}

	public function getMonths(): int {}

	public function withMonths(int $months): self {}

	public function plusMonths(int $months): self {}

	public function minusMonths(int $months): self {}

	public function getDays(): int {}

	public function withDays(int $days): self {}

	public function plusDays(int $days): self {}

	public function minusDays(int $days): self {}

	public function negated(): self {}

	public function isZero(): bool {}

	public function isEqualTo(self $other): bool {}

	public function toISOString(): string {}

	public function jsonSerialize(): string {}

	public function __toString(): string {}
}
