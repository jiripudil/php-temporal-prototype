<?php

declare(strict_types=1);

namespace Temporal;

use JsonSerializable;
use Stringable;
use function abs;
use function min;

final class YearWeek implements JsonSerializable, Stringable
{
	private function __construct(
		private readonly int $year,
		private readonly int $week,
	) {}

	public static function of(int $year, int $week): self
	{
		if ($year < -999_999 || $year > 999_999) {
			throw TemporalException::valueOutOfRange('year', $year, -999_999, 999_999);
		}

		$weeksInYear = Helpers::getWeeksInYear($year);
		if ($week < 1 || $week > $weeksInYear) {
			throw TemporalException::valueOutOfRange('week', $week, 1, $weeksInYear);
		}

		return new self($year, $week);
	}

	public static function now(TimeZone $timeZone, Clock|null $clock = null): self
	{
		return ZonedDateTime::now($timeZone, $clock)->getYearWeek();
	}

	public static function fromISOString(string $text): self
	{
		$pattern = '/^(-?\d{4})-W(\d{2})()$/';

		if (preg_match($pattern, $text, $matches) !== 1) {
			throw TemporalException::failedToParseInput();
		}

		[, $year, $week] = $matches;

		$year = (int) $year;
		$week = (int) $week;

		try {
			return self::of($year, $week);
		} catch (TemporalException $e) {
			throw TemporalException::failedToParseInput($e);
		}
	}

	public function getYear(): int
	{
		return $this->year;
	}

	public function withYear(int $year): self
	{
		if ($year < -999_999 || $year > 999_999) {
			throw TemporalException::valueOutOfRange('year', $year, -999_999, 999_999);
		}

		$week = min($this->week, Helpers::getWeeksInYear($year));

		return new self($year, $week);
	}

	public function plusYears(int $years): self
	{
		return $this->withYear($this->year + $years);
	}

	public function minusYears(int $years): self
	{
		return $this->withYear($this->year - $years);
	}

	public function getWeek(): int
	{
		return $this->week;
	}

	public function withWeek(int $week): self
	{
		$weeksInYear = Helpers::getWeeksInYear($this->year);
		if ($week < 1 || $week > $weeksInYear) {
			throw TemporalException::valueOutOfRange('week', $week, 1, $weeksInYear);
		}

		return new self($this->year, $week);
	}

	public function plusWeeks(int $weeks): self
	{
		return $this
			->getFirstDay()
			->plusWeeks($weeks)
			->getYearWeek();
	}

	public function minusWeeks(int $weeks): self
	{
		return $this->plusWeeks(-$weeks);
	}

	public function getDaysInYear(): int
	{
		return Helpers::getDaysInYear($this->year);
	}

	public function getWeeksInYear(): int
	{
		return Helpers::getWeeksInYear($this->year);
	}

	public function isLeapYear(): bool
	{
		return Helpers::isLeapYear($this->year);
	}

	public function atDay(int $dayOfWeek): LocalDate
	{
		$correction = LocalDate::of($this->year, 1, 4)->getDayOfWeek() + 3;
		$dayOfYear = $this->week * 7 + $dayOfWeek - $correction;
		$maxDaysOfYear = Helpers::getDaysInYear($this->year);

		if ($dayOfYear > $maxDaysOfYear) {
			return LocalDate::ofDayOfYear($this->year + 1, $dayOfYear - $maxDaysOfYear);
		}

		if ($dayOfYear > 0) {
			return LocalDate::ofDayOfYear($this->year, $dayOfYear);
		}

		$daysOfPreviousYear = Helpers::getDaysInYear($this->year - 1);
		return LocalDate::ofDayOfYear($this->year - 1, $daysOfPreviousYear + $dayOfYear);
	}

	public function getFirstDay(): LocalDate
	{
		return $this->atDay(1);
	}

	public function getLastDay(): LocalDate
	{
		return $this->atDay(7);
	}

	public function compareTo(self $other): int
	{
		$cmp = $this->year <=> $other->year;
		if ($cmp !== 0) {
			return $cmp;
		}

		return $this->week <=> $other->week;
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

	public function toISOString(): string
	{
		$result = sprintf('%04d-W%02d', abs($this->year), $this->week);
		if ($this->year >= 0) {
			return $result;
		}

		return '-' . $result;
	}

	public function jsonSerialize(): string
	{
		return $this->toISOString();
	}

	public function __toString(): string
	{
		return $this->toISOString();
	}

	public function __serialize(): array
	{
		return [
			'year' => $this->year,
			'week' => $this->week,
		];
	}

	public function __unserialize(array $data): void
	{
		$this->year = $data['year'];
		$this->week = $data['week'];
	}
}
