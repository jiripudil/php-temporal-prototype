<?php

declare(strict_types=1);

namespace Temporal;

use JsonSerializable;
use Stringable;
use function min;
use function preg_match;

final class MonthDay implements JsonSerializable, Stringable
{
	private function __construct(
		private readonly int $month,
		private readonly int $day,
	) {}

	public static function of(int $month, int $day): self
	{
		if ($month < 1 || $month > 12) {
			throw TemporalException::valueOutOfRange('month', $month, 1, 12);
		}

		$daysInMonth = Helpers::getMaxDaysInMonth($month);
		if ($day < 1 || $day > $daysInMonth) {
			throw TemporalException::valueOutOfRange('day', $day, 1, $daysInMonth);
		}

		return new self($month, $day);
	}

	public static function now(TimeZone $timeZone, Clock|null $clock = null): self
	{
		return ZonedDateTime::now($timeZone, $clock)->getMonthDay();
	}

	public static function fromIsoString(string $text): self
	{
		$pattern = '/^--(\d{2})-(\d{2})()$/';

		if (preg_match($pattern, $text, $matches) !== 1) {
			throw TemporalException::failedToParseInput();
		}

		[, $month, $day] = $matches;

		$month = (int) $month;
		$day = (int) $day;

		try {
			return self::of($month, $day);
		} catch (TemporalException $e) {
			throw TemporalException::failedToParseInput($e);
		}
	}

	public function getMonth(): int
	{
		return $this->month;
	}

	public function withMonth(int $month): self
	{
		if ($month < 1 || $month > 12) {
			throw TemporalException::valueOutOfRange('month', $month, 1, 12);
		}

		$day = min(
			$this->day,
			Helpers::getMaxDaysInMonth($month),
		);

		return new self($month, $day);
	}

	public function getDayOfMonth(): int
	{
		return $this->day;
	}

	public function withDayOfMonth(int $day): self
	{
		$daysInMonth = Helpers::getMaxDaysInMonth($this->month);

		if ($day < 1 || $day > $daysInMonth) {
			throw TemporalException::valueOutOfRange('day', $day, 1, $daysInMonth);
		}

		return new self($this->month, $day);
	}

	public function existsInYear(int $year): bool
	{
		return $this->month !== 2
			|| $this->day !== 29
			|| Helpers::isLeapYear($year);
	}

	public function atYear(int $year): LocalDate
	{
		return LocalDate::of($year, $this->month, $this->existsInYear($year) ? $this->day : 28);
	}

	public function compareTo(self $other): int
	{
		$cmp = $this->month <=> $other->month;
		if ($cmp !== 0) {
			return $cmp;
		}

		return $this->day <=> $other->day;
	}

	public function isEqualTo(self $other): bool
	{
		return $this->compareTo($other) === 0;
	}

	public function isBefore(self $other): bool
	{
		return $this->compareTo($other) < 0;
	}

	public function isBeforeOrEqualTo(self $other): bool
	{
		return $this->compareTo($other) <= 0;
	}

	public function isAfter(self $other): bool
	{
		return $this->compareTo($other) > 0;
	}

	public function isAfterOrEqualTo(self $other): bool
	{
		return $this->compareTo($other) >= 0;
	}

	public function toIsoString(): string
	{
		return sprintf('--%02d-%02d', $this->month, $this->day);
	}

	public function jsonSerialize(): string
	{
		return $this->toIsoString();
	}

	public function __toString(): string
	{
		return $this->toIsoString();
	}

	public function __serialize(): array
	{
		return [
			'month' => $this->month,
			'day' => $this->day,
		];
	}

	public function __unserialize(array $data): void
	{
		$this->month = $data['month'];
		$this->day = $data['day'];
	}
}
