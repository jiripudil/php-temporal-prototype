<?php

declare(strict_types=1);

namespace Temporal;

use JsonSerializable;
use Stringable;
use function abs;
use function preg_match;
use function sprintf;

final class YearMonth implements JsonSerializable, Stringable
{
	private function __construct(
		private readonly int $year,
		private readonly int $month,
	) {}

	public static function of(int $year, int $month): self
	{
		if ($year < -999_999 || $year > 999_999) {
			throw TemporalException::valueOutOfRange('year', $year, -999_999, 999_999);
		}

		if ($month < 1 || $month > 12) {
			throw TemporalException::valueOutOfRange('month', $month, 1, 12);
		}

		return new self($year, $month);
	}

	public static function now(TimeZone $timeZone, Clock|null $clock = null): self
	{
		return ZonedDateTime::now($timeZone, $clock)->getYearMonth();
	}

	public static function fromIsoString(string $text): self
	{
		$pattern = '/^(-?\d{4})-(\d{2})()$/';

		if (preg_match($pattern, $text, $matches) !== 1) {
			throw TemporalException::failedToParseInput();
		}

		[, $year, $month] = $matches;

		$year = (int) $year;
		$month = (int) $month;

		try {
			return self::of($year, $month);
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

		return new self($year, $this->month);
	}

	public function plusYears(int $years): self
	{
		return $this->withYear($this->year + $years);
	}

	public function minusYears(int $years): self
	{
		return $this->withYear($this->year - $years);
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

		return new self($this->year, $month);
	}

	public function plusMonths(int $months): self
	{
		$month = $this->month + $months - 1;

		$yearDiff = intdiv($month, 12);
		$month = ((($month % 12) + 12) % 12) + 1;

		$year = $this->year + $yearDiff;

		return new self($year, $month);
	}

	public function minusMonths(int $months): self
	{
		return $this->plusMonths(-$months);
	}

	public function getDaysInMonth(): int
	{
		return match ($this->month) {
			2 => Helpers::isLeapYear($this->year) ? 29 : 28,
			4, 6, 9, 11 => 30,
			default => 31,
		};
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

	public function atDay(int $dayOfMonth): LocalDate
	{
		$daysInMonth = $this->getDaysInMonth();
		if ($dayOfMonth < 1 || $dayOfMonth > $daysInMonth) {
			throw TemporalException::valueOutOfRange('dayOfMonth', $dayOfMonth, 1, $daysInMonth);
		}

		return LocalDate::of($this->year, $this->month, $dayOfMonth);
	}

	public function getFirstDay(): LocalDate
	{
		return $this->atDay(1);
	}

	public function getLastDay(): LocalDate
	{
		return $this->atDay($this->getDaysInMonth());
	}

	public function compareTo(self $other): int
	{
		$cmp = $this->year <=> $other->year;
		if ($cmp !== 0) {
			return $cmp;
		}

		return $this->month <=> $other->month;
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
		$result = sprintf('%04d-%02d', abs($this->year), $this->month);
		if ($this->year >= 0) {
			return $result;
		}

		return '-' . $result;
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
			'year' => $this->year,
			'month' => $this->month,
		];
	}

	/**
	 * @param array{year: int, month: int} $data
	 */
	public function __unserialize(array $data): void
	{
		$this->year = $data['year'];
		$this->month = $data['month'];
	}
}
