<?php

declare(strict_types=1);

namespace Temporal;

use DateTimeImmutable;
use DateTimeInterface;
use JsonSerializable;
use Stringable;
use Temporal\Format\DateTimeFormatter;

final class LocalDate implements JsonSerializable, Stringable
{
	private function __construct() {}

	public static function of(int $year, int $month, int $day): self {}

	public static function ofDayOfYear(int $year, int $dayOfYear): self {}

	public static function ofEpochDay(int $epochDay): self {}

	public static function now(TimeZone $timeZone, Clock|null $clock = null): self {}

	public static function parse(string $text): self {}

	public static function min(): self {}

	public static function max(): self {}

	public function getYear(): int {}

	public function withYear(int $year): self {}

	public function getMonth(): int {}

	public function withMonth(int $month): self {}

	public function getYearMonth(): YearMonth {}

	public function getWeek(): int {}

	public function getYearOfWeek(): int {}

	public function getYearWeek(): YearWeek {}

	public function getDayOfMonth(): int {}

	public function withDayOfMonth(int $dayOfMonth): self {}

	public function getMonthDay(): MonthDay {}

	public function withMonthDay(MonthDay $monthDay): self {}

	public function getDayOfYear(): int {}

	public function withDayOfYear(int $dayOfYear): self {}

	public function getDayOfWeek(): int {}

	public function getDaysInMonth(): int {}

	public function getDaysInYear(): int {}

	public function getWeeksInYear(): int {}

	public function isLeapYear(): bool {}

	public function toEpochDay(): int {}

	public function plus(Period $period): self {}

	public function plusYears(int $years): self {}

	public function plusMonths(int $months): self {}

	public function plusWeeks(int $weeks): self {}

	public function plusDays(int $days): self {}

	public function minus(Period $period): self {}

	public function minusYears(int $years): self {}

	public function minusMonths(int $months): self {}

	public function minusWeeks(int $weeks): self {}

	public function minusDays(int $days): self {}

	public function until(self $endExclusive): Period {}

	public function daysUntil(self $endExclusive): int {}

	public function compareTo(self $other): int {}

	public function isEqualTo(self $other): bool {}

	public function isBefore(self $other): bool {}

	public function isBeforeOrEqualTo(self $other): bool {}

	public function isAfter(self $other): bool {}

	public function isAfterOrEqualTo(self $other): bool {}

	public function toDateTime(): DateTimeImmutable {}

	public static function fromDateTime(DateTimeInterface $dateTime): self {}

	public function toISOString(): string {}

	public function format(string $localizedPattern, string|null $locale = null): string {}

	public function formatWith(DateTimeFormatter $formatter): string {}

	public function jsonSerialize(): string {}

	public function __toString(): string {}
}
