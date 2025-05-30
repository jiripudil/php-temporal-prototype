<?php

declare(strict_types=1);

namespace Temporal;

use DateTimeImmutable;
use DateTimeInterface;
use DateTimeZone;
use JsonSerializable;
use Stringable;
use Temporal\Format\DateTimeFormatter;
use function abs;
use function intdiv;
use function min;
use function preg_match;
use function sprintf;

final class LocalDate implements JsonSerializable, Stringable
{
	private const DAYS_PER_CYCLE = 146097;
	private const DAYS_0000_TO_1970 = (self::DAYS_PER_CYCLE * 5) - (30 * 365 + 7);

	private function __construct(
		private readonly int $year,
		private readonly int $month,
		private readonly int $day,
	) {}

	public static function of(int $year, int $month, int $day): self
	{
		if ($year < -999_999 || $year > 999_999) {
			throw TemporalException::valueOutOfRange('year', $year, -999_999, 999_999);
		}

		if ($month < 1 || $month > 12) {
			throw TemporalException::valueOutOfRange('month', $month, 1, 12);
		}

		$daysInMonth = Helpers::getDaysInMonth($year, $month);
		if ($day < 1 || $day > $daysInMonth) {
			throw TemporalException::valueOutOfRange('day', $day, 1, $daysInMonth);
		}

		return new self($year, $month, $day);
	}

	public static function ofDayOfYear(int $year, int $dayOfYear): self
	{
		$daysInYear = Helpers::getDaysInYear($year);
		if ($dayOfYear < 1 || $dayOfYear > $daysInYear) {
			throw TemporalException::valueOutOfRange('dayOfYear', $dayOfYear, 1, $daysInYear);
		}

		$monthOfYear = intdiv($dayOfYear - 1, 31) + 1;
		$monthEnd = Helpers::getFirstDayOfYear($year, $monthOfYear) + Helpers::getDaysInMonth($year, $monthOfYear) - 1;

		if ($dayOfYear > $monthEnd) {
			$monthOfYear++;
		}

		$dayOfMonth = $dayOfYear - Helpers::getFirstDayOfYear($year, $monthOfYear) + 1;

		return self::of($year, $monthOfYear, $dayOfMonth);
	}

	public static function ofEpochDay(int $epochDay): self
	{
		$zeroDay = $epochDay + self::DAYS_0000_TO_1970;
		$zeroDay -= 60; // adjust to 0000-03-01 so leap day is at the end of a four-year cycle
		$adjust = 0;
		if ($zeroDay < 0) {
			// adjust negative years to positive for calculation
			$adjustCycles = intdiv($zeroDay + 1, self::DAYS_PER_CYCLE) - 1;
			$adjust = $adjustCycles * 400;
			$zeroDay += -$adjustCycles * self::DAYS_PER_CYCLE;
		}
		$yearEst = intdiv(400 * $zeroDay + 591, self::DAYS_PER_CYCLE);
		$doyEst = $zeroDay - (365 * $yearEst + intdiv($yearEst, 4) - intdiv($yearEst, 100) + intdiv($yearEst, 400));
		if ($doyEst < 0) {
			// fix estimate
			$yearEst--;
			$doyEst = $zeroDay - (365 * $yearEst + intdiv($yearEst, 4) - intdiv($yearEst, 100) + intdiv($yearEst, 400));
		}
		$yearEst += $adjust; // reset any negative year
		$marchDoy0 = $doyEst;

		// convert march-based value back to january-based
		$marchMonth0 = intdiv($marchDoy0 * 5 + 2, 153);
		$month = $marchMonth0 + 3;
		if ($month > 12) {
			$month -= 12;
		}

		$dom = $marchDoy0 - intdiv($marchMonth0 * 306 + 5, 10) + 1;
		if ($marchDoy0 >= 306) {
			$yearEst++;
		}

		return new self($yearEst, $month, $dom);
	}

	public static function now(TimeZone $timeZone, Clock|null $clock = null): self
	{
		return ZonedDateTime::now($timeZone, $clock)->getDate();
	}

	public static function fromIsoString(string $text): self
	{
		$pattern = '/^(-?\d{4})-(\d{2})-(\d{2})()$/';

		if (preg_match($pattern, $text, $matches) !== 1) {
			throw TemporalException::failedToParseInput();
		}

		[, $year, $month, $day] = $matches;

		$year = (int) $year;
		$month = (int) $month;
		$day = (int) $day;

		try {
			return self::of($year, $month, $day);
		} catch (TemporalException $e) {
			throw TemporalException::failedToParseInput($e);
		}
	}

	public static function min(): self
	{
		/** @var self $min */
		static $min = new self(-999999, 1, 1);
		return $min;
	}

	public static function max(): self
	{
		/** @var self $max */
		static $max = new self(999999, 12, 31);
		return $max;
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

		return new self($year, $this->month, min($this->day, Helpers::getDaysInMonth($year, $this->month)));
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

		return new self($this->year, $month, min($this->day, Helpers::getDaysInMonth($this->year, $month)));
	}

	public function getYearMonth(): YearMonth
	{
		return YearMonth::of($this->year, $this->month);
	}

	public function getWeek(): int
	{
		return $this->getYearWeek()->getWeek();
	}

	public function getYearOfWeek(): int
	{
		return $this->getYearWeek()->getYear();
	}

	public function getYearWeek(): YearWeek
	{
		$year = $this->year;
		$week = intdiv($this->getDayOfYear() - $this->getDayOfWeek() + 10, 7);

		if ($week === 0) {
			$year--;
			$week = Helpers::getWeeksInYear($year);
		} elseif ($week === 53 && Helpers::getWeeksInYear($year) !== 53) {
			$year++;
			$week = 1;
		}

		return YearWeek::of($year, $week);
	}

	public function getDayOfMonth(): int
	{
		return $this->day;
	}

	public function withDayOfMonth(int $dayOfMonth): self
	{
		$daysInMonth = $this->getDaysInMonth();
		if ($dayOfMonth < 1 || $dayOfMonth > $daysInMonth) {
			throw TemporalException::valueOutOfRange('dayOfMonth', $dayOfMonth, 1, $daysInMonth);
		}

		return new self($this->year, $this->month, $dayOfMonth);
	}

	public function getMonthDay(): MonthDay
	{
		return MonthDay::of($this->month, $this->day);
	}

	public function getDayOfYear(): int
	{
		return Helpers::getFirstDayOfYear($this->year, $this->month) + $this->day - 1;
	}

	public function getDayOfWeek(): int
	{
		$modulo = static fn(int $x, int $y): int => (($x % $y) + $y) % $y;

		$year = $this->year;
		$month = $this->month;
		$day = $this->day;

		if ($month < 3) {
			$month += 12;
			$year--;
		}

		$k = $modulo($year, 100);
		$j = intdiv($year, 100);

		$h = $modulo(
			$day + intdiv(13 * ($month + 1), 5) + $k + intdiv($k, 4) + intdiv($j, 4) - (2 * $j),
			7,
		);

		return $modulo($h + 5, 7) + 1;
	}

	public function getDaysInMonth(): int
	{
		return Helpers::getDaysInMonth($this->year, $this->month);
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

	public function toEpochDay(): int
	{
		$y = $this->year;
		$m = $this->month;

		$total = 365 * $y;

		if ($y >= 0) {
			$total += intdiv($y + 3, 4) - intdiv($y + 99, 100) + intdiv($y + 399, 400);
		} else {
			$total -= intdiv($y, -4) - intdiv($y, -100) + intdiv($y, -400);
		}

		$total += intdiv(367 * $m - 362, 12);
		$total += $this->day - 1;

		if ($m > 2) {
			$total--;
			if (!Helpers::isLeapYear($this->year)) {
				$total--;
			}
		}

		return $total - self::DAYS_0000_TO_1970;
	}

	public function plus(Period $period): self
	{
		return $this
			->plusYears($period->getYears())
			->plusMonths($period->getMonths())
			->plusDays($period->getDays());
	}

	public function plusYears(int $years): self
	{
		return $this->withYear($this->year + $years);
	}

	public function plusMonths(int $months): self
	{
		$month = $this->month + $months - 1;

		$yearDiff = intdiv($month, 12);
		if ($month < 0 && ($yearDiff * 12 !== $month)) {
			$yearDiff--;
		}

		$month = ((($month % 12) + 12) % 12) + 1;

		$year = $this->year + $yearDiff;

		$day = min($this->day, Helpers::getDaysInMonth($this->year, $month));

		return new self($year, $month, $day);
	}

	public function plusWeeks(int $weeks): self
	{
		return $this->plusDays($weeks * 7);
	}

	public function plusDays(int $days): self
	{
		return self::ofEpochDay($this->toEpochDay() + $days);
	}

	public function minus(Period $period): self
	{
		return $this->plus($period->negated());
	}

	public function minusYears(int $years): self
	{
		return $this->plusYears(-$years);
	}

	public function minusMonths(int $months): self
	{
		return $this->plusMonths(-$months);
	}

	public function minusWeeks(int $weeks): self
	{
		return $this->plusWeeks(-$weeks);
	}

	public function minusDays(int $days): self
	{
		return $this->plusDays(-$days);
	}

	public function until(self $endExclusive): Period
	{
		$endExclusiveProlepticMonth = $endExclusive->year * 12 + $endExclusive->month - 1;
		$thisProlepticMonth = $this->year * 12 + $this->month - 1;

		$totalMonths = $endExclusiveProlepticMonth - $thisProlepticMonth;
		$days = $endExclusive->day - $this->day;

		if ($totalMonths > 0 && $days < 0) {
			$totalMonths--;
			$calcDate = $this->plusMonths($totalMonths);
			$days = $endExclusive->toEpochDay() - $calcDate->toEpochDay();
		} elseif ($totalMonths < 0 && $days > 0) {
			$totalMonths++;
			$days -= $endExclusive->getDaysInMonth();
		}

		$years = intdiv($totalMonths, 12);
		$months = $totalMonths % 12;

		return Period::of($years, $months, $days);
	}

	public function daysUntil(self $endExclusive): int
	{
		return $endExclusive->toEpochDay() - $this->toEpochDay();
	}

	public function atTime(LocalTime $time): LocalDateTime
	{
		return LocalDateTime::ofDateTime($this, $time);
	}

	public function compareTo(self $other): int
	{
		$cmp = $this->year <=> $other->year;
		if ($cmp !== 0) {
			return $cmp;
		}

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

	public function toDateTime(): DateTimeImmutable
	{
		$format = 'Y-m-d\TH:i:s.u';
		$dateTime = $this . 'T00:00:00.000000';
		$dateTimeZone = new DateTimeZone('UTC');

		$result = DateTimeImmutable::createFromFormat($format, $dateTime, $dateTimeZone);
		if ($result === false) {
			throw TemporalException::failedToConvertToDateTime();
		}

		return $result;
	}

	public static function fromDateTime(DateTimeInterface $dateTime): self
	{
		return new self(
			(int) $dateTime->format('Y'),
			(int) $dateTime->format('n'),
			(int) $dateTime->format('j'),
		);
	}

	public function toIsoString(): string
	{
		$result = sprintf('%04d-%02d-%02d', abs($this->year), $this->month, $this->day);
		if ($this->year >= 0) {
			return $result;
		}

		return '-' . $result;
	}

	public function format(string $localizedPattern, string|null $locale = null): string
	{
		$formatter = DateTimeFormatter::ofLocalizedPattern($localizedPattern, $locale);
		return $this->formatWith($formatter);
	}

	public function formatWith(DateTimeFormatter $formatter): string
	{
		return $formatter->formatLocalDate($this);
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
			'day' => $this->day,
		];
	}

	public function __unserialize(array $data): void
	{
		$this->year = $data['year'];
		$this->month = $data['month'];
		$this->day = $data['day'];
	}
}
