<?php

declare(strict_types=1);

namespace Temporal;

use DateTimeImmutable;
use DateTimeInterface;
use DateTimeZone;
use JsonSerializable;
use Stringable;
use Temporal\Format\DateTimeFormatter;
use function intdiv;
use function preg_match;
use function sprintf;
use function str_pad;

final class LocalDateTime implements JsonSerializable, Stringable
{
	private function __construct(
		private readonly LocalDate $date,
		private readonly LocalTime $time,
	) {}

	public static function of(int $year, int $month, int $day, int $hour = 0, int $minute = 0, int $second = 0, int $nano = 0): self
	{
		return new self(
			LocalDate::of($year, $month, $day),
			LocalTime::of($hour, $minute, $second, $nano),
		);
	}

	public static function ofDateTime(LocalDate $date, LocalTime $time): self
	{
		return new self($date, $time);
	}

	public static function now(TimeZone $timeZone, Clock|null $clock = null): self
	{
		return ZonedDateTime::now($timeZone, $clock)->getDateTime();
	}

	public static function fromIsoString(string $text): self
	{
		$pattern = '/^(-?\d{4})-(\d{2})-(\d{2})T(\d{2}):(\d{2})(?::(\d{2})(?:\\.(\d{1,9}))?)?()$/';

		if (preg_match($pattern, $text, $matches) !== 1) {
			throw TemporalException::failedToParseInput();
		}

		[, $year, $month, $day, $hour, $minute, $second, $nano] = $matches;

		$year = (int) $year;
		$month = (int) $month;
		$day = (int) $day;
		$hour = (int) $hour;
		$minute = (int) $minute;
		$second = (int) $second;
		$nano = (int) str_pad($nano, 9, '0');

		try {
			return self::of($year, $month, $day, $hour, $minute, $second, $nano);
		} catch (TemporalException $e) {
			throw TemporalException::failedToParseInput($e);
		}
	}

	public static function min(): self
	{
		return new self(LocalDate::min(), LocalTime::min());
	}

	public static function max(): self
	{
		return new self(LocalDate::max(), LocalTime::max());
	}

	public function getDate(): LocalDate
	{
		return $this->date;
	}

	public function withDate(LocalDate $date): self
	{
		return new self($date, $this->time);
	}

	public function getYear(): int
	{
		return $this->date->getYear();
	}

	public function withYear(int $year): self
	{
		return new self($this->date->withYear($year), $this->time);
	}

	public function getMonth(): int
	{
		return $this->date->getMonth();
	}

	public function withMonth(int $month): self
	{
		return new self($this->date->withMonth($month), $this->time);
	}

	public function getYearMonth(): YearMonth
	{
		return $this->date->getYearMonth();
	}

	public function getWeek(): int
	{
		return $this->date->getWeek();
	}

	public function getYearOfWeek(): int
	{
		return $this->date->getYearOfWeek();
	}

	public function getYearWeek(): YearWeek
	{
		return $this->date->getYearWeek();
	}

	public function getDayOfMonth(): int
	{
		return $this->date->getDayOfMonth();
	}

	public function withDayOfMonth(int $dayOfMonth): self
	{
		return new self($this->date->withDayOfMonth($dayOfMonth), $this->time);
	}

	public function getMonthDay(): MonthDay
	{
		return $this->date->getMonthDay();
	}

	public function getDayOfYear(): int
	{
		return $this->date->getDayOfYear();
	}

	public function getDayOfWeek(): int
	{
		return $this->date->getDayOfWeek();
	}

	public function getDaysInMonth(): int
	{
		return $this->date->getDaysInMonth();
	}

	public function getDaysInYear(): int
	{
		return $this->date->getDaysInYear();
	}

	public function getWeeksInYear(): int
	{
		return $this->date->getWeeksInYear();
	}

	public function isLeapYear(): bool
	{
		return $this->date->isLeapYear();
	}

	public function getTime(): LocalTime
	{
		return $this->time;
	}

	public function withTime(LocalTime $time): self
	{
		return new self($this->date, $time);
	}

	public function getHour(): int
	{
		return $this->time->getHour();
	}

	public function withHour(int $hour): self
	{
		return new self($this->date, $this->time->withHour($hour));
	}

	public function getMinute(): int
	{
		return $this->time->getMinute();
	}

	public function withMinute(int $minute): self
	{
		return new self($this->date, $this->time->withMinute($minute));
	}

	public function getSecond(): int
	{
		return $this->time->getSecond();
	}

	public function withSecond(int $second): self
	{
		return new self($this->date, $this->time->withSecond($second));
	}

	public function getNano(): int
	{
		return $this->time->getNano();
	}

	public function withNano(int $nano): self
	{
		return new self($this->date, $this->time->withNano($nano));
	}

	public function plusPeriod(Period $period): self
	{
		return new self($this->date->plus($period), $this->time);
	}

	public function plusYears(int $years): self
	{
		return new self($this->date->plusYears($years), $this->time);
	}

	public function plusMonths(int $months): self
	{
		return new self($this->date->plusMonths($months), $this->time);
	}

	public function plusWeeks(int $weeks): self
	{
		return new self($this->date->plusWeeks($weeks), $this->time);
	}

	public function plusDays(int $days): self
	{
		return new self($this->date->plusDays($days), $this->time);
	}

	public function minusPeriod(Period $period): self
	{
		return new self($this->date->minus($period), $this->time);
	}

	public function minusYears(int $years): self
	{
		return new self($this->date->minusYears($years), $this->time);
	}

	public function minusMonths(int $months): self
	{
		return new self($this->date->minusMonths($months), $this->time);
	}

	public function minusWeeks(int $weeks): self
	{
		return new self($this->date->minusWeeks($weeks), $this->time);
	}

	public function minusDays(int $days): self
	{
		return new self($this->date->minusDays($days), $this->time);
	}

	public function plusDuration(Duration $duration): self
	{
		$seconds = $this->time->getSecondOfDay() + $duration->getSeconds();
		$days = intdiv($seconds, Duration::SECONDS_PER_DAY);
		if ($seconds < 0 && ($days * Duration::SECONDS_PER_DAY) !== $seconds) {
			$days--;
		}

		return new self($this->date->plusDays($days), $this->time->plus($duration));
	}

	public function plusHours(int $hours): self
	{
		return $this->plusDuration(Duration::ofHours($hours));
	}

	public function plusMinutes(int $minutes): self
	{
		return $this->plusDuration(Duration::ofMinutes($minutes));
	}

	public function plusSeconds(int $seconds): self
	{
		return $this->plusDuration(Duration::ofSeconds($seconds));
	}

	public function plusNanos(int $nanos): self
	{
		return $this->plusDuration(Duration::ofSeconds(0, $nanos));
	}

	public function minusDuration(Duration $duration): self
	{
		return $this->plusDuration($duration->negated());
	}

	public function minusHours(int $hours): self
	{
		return $this->minusDuration(Duration::ofHours($hours));
	}

	public function minusMinutes(int $minutes): self
	{
		return $this->minusDuration(Duration::ofMinutes($minutes));
	}

	public function minusSeconds(int $seconds): self
	{
		return $this->minusDuration(Duration::ofSeconds($seconds));
	}

	public function minusNanos(int $nanos): self
	{
		return $this->minusDuration(Duration::ofSeconds(0, $nanos));
	}

	public function compareTo(self $other): int
	{
		$cmp = $this->date->compareTo($other->date);
		if ($cmp !== 0) {
			return $cmp;
		}

		return $this->time->compareTo($other->time);
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

	public function atTimeZone(TimeZone $timeZone): ZonedDateTime
	{
		return ZonedDateTime::of($this, $timeZone);
	}

	public function toDateTime(): DateTimeImmutable
	{
		$format = 'Y-m-d\TH:i';

		// round down nano to microsecond
		$nano = 1000 * intdiv($this->time->getNano(), 1000);

		if ($this->time->getSecond() !== 0 || $nano !== 0) {
			$format .= ':s';
			if ($nano !== 0) {
				$format .= '.u';
			}
		}

		$dateTime = $this->date . 'T' . $this->time->withNano($nano);
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
			LocalDate::fromDateTime($dateTime),
			LocalTime::fromDateTime($dateTime),
		);
	}

	public function toIsoString(): string
	{
		return sprintf('%sT%s', $this->date->toIsoString(), $this->time->toIsoString());
	}

	public function format(string $localizedPattern, string|null $locale = null): string
	{
		$formatter = DateTimeFormatter::ofLocalizedPattern($localizedPattern, $locale);
		return $this->formatWith($formatter);
	}

	public function formatWith(DateTimeFormatter $formatter): string
	{
		return $formatter->formatLocalDateTime($this);
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
			'year' => $this->getYear(),
			'month' => $this->getMonth(),
			'day' => $this->getDayOfMonth(),
			'hour' => $this->getHour(),
			'minute' => $this->getMinute(),
			'second' => $this->getSecond(),
			'nano' => $this->getNano(),
		];
	}

	public function __unserialize(array $data): void
	{
		$year = $data['year'];
		$month = $data['month'];
		$day = $data['day'];
		$this->date = LocalDate::of($year, $month, $day);

		$hour = $data['hour'];
		$minute = $data['minute'];
		$second = $data['second'];
		$nano = $data['nano'];
		$this->time = LocalTime::of($hour, $minute, $second, $nano);
	}
}
