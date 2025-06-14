<?php

declare(strict_types=1);

namespace Temporal;

use DateTime;
use DateTimeImmutable;
use DateTimeInterface;
use DateTimeZone;
use JsonSerializable;
use Stringable;
use Temporal\Exception\DateTimeConversionException;
use Temporal\Exception\ParsingException;
use Temporal\Exception\UnknownTimeZoneException;
use Temporal\Exception\ValueOutOfRangeException;
use Temporal\Format\DateTimeFormatter;
use function intdiv;
use function preg_match;
use function sprintf;

final class ZonedDateTime implements JsonSerializable, Stringable
{
	private function __construct(
		private readonly LocalDateTime $dateTime,
		private readonly TimeZoneOffset $timeZoneOffset,
		private readonly TimeZone $timeZone,
		private readonly Instant $instant,
	) {}

	public static function of(LocalDateTime $dateTime, TimeZone $timeZone): self
	{
		$dtz = new DateTimeZone($timeZone->getId());
		$dt = new DateTime((string) $dateTime->withNano(0), $dtz);

		$instant = Instant::of($dt->getTimestamp(), $dateTime->getNano());

		if ($timeZone instanceof TimeZoneOffset) {
			$timeZoneOffset = $timeZone;
		} else {
			$timeZoneOffset = TimeZoneOffset::ofTotalSeconds($dt->getOffset());
		}

		// the date-time might not be valid for the given timeZone because of a DST transition
		$dateTime = LocalDateTime::fromIsoString($dt->format('Y-m-d\TH:i:s'))->withNano($dateTime->getNano());

		return new self($dateTime, $timeZoneOffset, $timeZone, $instant);
	}

	public static function ofInstant(Instant $instant, TimeZone $timeZone): self
	{
		$dtz = new DateTimeZone($timeZone->getId());
		$dt = new DateTime('@' . $instant->getEpochSecond(), $dtz);
		$dt->setTimezone($dtz);

		$localDateTime = LocalDateTime::fromIsoString($dt->format('Y-m-d\TH:i:s'));
		$localDateTime = $localDateTime->withNano($instant->getNano());

		if ($timeZone instanceof TimeZoneOffset) {
			$timeZoneOffset = $timeZone;
		} else {
			$timeZoneOffset = TimeZoneOffset::ofTotalSeconds($dt->getOffset());
		}

		return new self($localDateTime, $timeZoneOffset, $timeZone, $instant);
	}

	public static function now(TimeZone $timeZone, Clock|null $clock = null): self
	{
		return self::ofInstant(Instant::now($clock), $timeZone);
	}

	public static function fromIsoString(string $text): self
	{
		$pattern = '/^(-?\d{4})-(\d{2})-(\d{2})T(\d{2}):(\d{2})(?::(\d{2})(?:\.(\d{1,9}))?)?([Zz]|[+-]\d{2}:\d{2}(?::\d{2})?)(?:\[(.+?)])?()$/';

		if (preg_match($pattern, $text, $matches) !== 1) {
			throw ParsingException::invalidIsoString($text);
		}

		[, $year, $month, $day, $hour, $minute, $second, $nano, $offset, $timeZoneId] = $matches;

		$year = (int) $year;
		$month = (int) $month;
		$day = (int) $day;
		$hour = (int) $hour;
		$minute = (int) $minute;
		$second = (int) $second;
		$nano = (int) str_pad($nano, 9, '0');

		try {
			$dateTime = LocalDateTime::of($year, $month, $day, $hour, $minute, $second, $nano);
		} catch (ValueOutOfRangeException $e) {
			throw ParsingException::valueOutOfRange($text, $e);
		}

		$timeZone = TimeZoneOffset::fromIsoString($offset);

		if ($timeZoneId !== '') {
			try {
				$timeZone = TimeZoneRegion::of($timeZoneId);
			} catch (UnknownTimeZoneException $e) {
				throw ParsingException::unknownTimeZone($text, $e);
			}
		}

		return self::of($dateTime, $timeZone);
	}

	public function getDateTime(): LocalDateTime
	{
		return $this->dateTime;
	}

	public function getDate(): LocalDate
	{
		return $this->dateTime->getDate();
	}

	public function withDate(LocalDate $date): self
	{
		return self::of($this->dateTime->withDate($date), $this->timeZone);
	}

	public function getYear(): int
	{
		return $this->dateTime->getYear();
	}

	public function withYear(int $year): self
	{
		return self::of($this->dateTime->withYear($year), $this->timeZone);
	}

	public function getMonth(): int
	{
		return $this->dateTime->getMonth();
	}

	public function withMonth(int $month): self
	{
		return self::of($this->dateTime->withMonth($month), $this->timeZone);
	}

	public function getYearMonth(): YearMonth
	{
		return $this->dateTime->getYearMonth();
	}

	public function getWeek(): int
	{
		return $this->dateTime->getWeek();
	}

	public function getYearOfWeek(): int
	{
		return $this->dateTime->getYearOfWeek();
	}

	public function getYearWeek(): YearWeek
	{
		return $this->dateTime->getYearWeek();
	}

	public function getDayOfMonth(): int
	{
		return $this->dateTime->getDayOfMonth();
	}

	public function withDayOfMonth(int $dayOfMonth): self
	{
		return self::of($this->dateTime->withDayOfMonth($dayOfMonth), $this->timeZone);
	}

	public function getMonthDay(): MonthDay
	{
		return $this->dateTime->getMonthDay();
	}

	public function getDayOfYear(): int
	{
		return $this->dateTime->getDayOfYear();
	}

	public function getDayOfWeek(): int
	{
		return $this->dateTime->getDayOfWeek();
	}

	public function getDaysInMonth(): int
	{
		return $this->dateTime->getDaysInMonth();
	}

	public function getDaysInYear(): int
	{
		return $this->dateTime->getDaysInYear();
	}

	public function getWeeksInYear(): int
	{
		return $this->dateTime->getWeeksInYear();
	}

	public function isLeapYear(): bool
	{
		return $this->dateTime->isLeapYear();
	}

	public function getTime(): LocalTime
	{
		return $this->dateTime->getTime();
	}

	public function withTime(LocalTime $time): self
	{
		return self::of($this->dateTime->withTime($time), $this->timeZone);
	}

	public function getHour(): int
	{
		return $this->dateTime->getHour();
	}

	public function withHour(int $hour): self
	{
		return self::of($this->dateTime->withHour($hour), $this->timeZone);
	}

	public function getMinute(): int
	{
		return $this->dateTime->getMinute();
	}

	public function withMinute(int $minute): self
	{
		return self::of($this->dateTime->withMinute($minute), $this->timeZone);
	}

	public function getSecond(): int
	{
		return $this->dateTime->getSecond();
	}

	public function withSecond(int $second): self
	{
		return self::of($this->dateTime->withSecond($second), $this->timeZone);
	}

	public function getNano(): int
	{
		return $this->dateTime->getNano();
	}

	public function withNano(int $nano): self
	{
		return self::of($this->dateTime->withNano($nano), $this->timeZone);
	}

	public function getInstant(): Instant
	{
		return $this->instant;
	}

	public function getTimeZone(): TimeZone
	{
		return $this->timeZone;
	}

	public function getTimeZoneOffset(): TimeZoneOffset
	{
		return $this->timeZoneOffset;
	}

	public function withTimeZoneSameLocal(TimeZone $timeZone): self
	{
		return self::of($this->dateTime, $timeZone);
	}

	public function withTimeZoneSameInstant(TimeZone $timeZone): self
	{
		return self::ofInstant($this->instant, $timeZone);
	}

	public function withFixedOffsetTimeZone(): self
	{
		return self::of($this->dateTime, $this->timeZoneOffset);
	}

	public function plusPeriod(Period $period): self
	{
		return self::of($this->dateTime->plusPeriod($period), $this->timeZone);
	}

	public function plusYears(int $years): self
	{
		return self::of($this->dateTime->plusYears($years), $this->timeZone);
	}

	public function plusMonths(int $months): self
	{
		return self::of($this->dateTime->plusMonths($months), $this->timeZone);
	}

	public function plusWeeks(int $weeks): self
	{
		return self::of($this->dateTime->plusWeeks($weeks), $this->timeZone);
	}

	public function plusDays(int $days): self
	{
		return self::of($this->dateTime->plusDays($days), $this->timeZone);
	}

	public function minusPeriod(Period $period): self
	{
		return self::of($this->dateTime->minusPeriod($period), $this->timeZone);
	}

	public function minusYears(int $years): self
	{
		return self::of($this->dateTime->minusYears($years), $this->timeZone);
	}

	public function minusMonths(int $months): self
	{
		return self::of($this->dateTime->minusMonths($months), $this->timeZone);
	}

	public function minusWeeks(int $weeks): self
	{
		return self::of($this->dateTime->minusWeeks($weeks), $this->timeZone);
	}

	public function minusDays(int $days): self
	{
		return self::of($this->dateTime->minusDays($days), $this->timeZone);
	}

	public function plusDuration(Duration $duration): self
	{
		return self::ofInstant($this->instant->plus($duration), $this->timeZone);
	}

	public function plusHours(int $hours): self
	{
		return self::ofInstant($this->instant->plusHours($hours), $this->timeZone);
	}

	public function plusMinutes(int $minutes): self
	{
		return self::ofInstant($this->instant->plusMinutes($minutes), $this->timeZone);
	}

	public function plusSeconds(int $seconds): self
	{
		return self::ofInstant($this->instant->plusSeconds($seconds), $this->timeZone);
	}

	public function plusNanos(int $nanos): self
	{
		return self::ofInstant($this->instant->plus(Duration::ofSeconds(0, $nanos)), $this->timeZone);
	}

	public function minusDuration(Duration $duration): self
	{
		return self::ofInstant($this->instant->minus($duration), $this->timeZone);
	}

	public function minusHours(int $hours): self
	{
		return self::ofInstant($this->instant->minusHours($hours), $this->timeZone);
	}

	public function minusMinutes(int $minutes): self
	{
		return self::ofInstant($this->instant->minusMinutes($minutes), $this->timeZone);
	}

	public function minusSeconds(int $seconds): self
	{
		return self::ofInstant($this->instant->minusSeconds($seconds), $this->timeZone);
	}

	public function minusNanos(int $nanos): self
	{
		return self::ofInstant($this->instant->minus(Duration::ofSeconds(0, $nanos)), $this->timeZone);
	}

	public function compareTo(self $other): int
	{
		return $this->instant->compareTo($other->instant);
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
		$format = 'Y-m-d\TH:i';

		// round down to microseconds
		$nano = 1000 * intdiv($this->dateTime->getNano(), 1000);

		$dateTime = (string) $this->dateTime->withNano($nano);
		$dateTimeZone = $this->timeZone->toDateTimeZone();

		if ($this->dateTime->getSecond() !== 0 || $nano !== 0) {
			$format .= ':s';
			if ($nano !== 0) {
				$format .= '.u';
			}
		}

		$format .= 'p';
		$dateTime .= $this->timeZoneOffset->getId();

		$nativeDateTime = DateTimeImmutable::createFromFormat($format, $dateTime);
		if ($nativeDateTime === false) {
			throw DateTimeConversionException::of($this);
		}

		$nativeDateTime = $nativeDateTime->setTimezone($dateTimeZone);

		return $nativeDateTime;
	}

	public static function fromDateTime(DateTimeInterface $dateTime): self
	{
		$localDateTime = LocalDateTime::fromDateTime($dateTime);
		$timeZone = TimeZone::fromDateTimeZone($dateTime->getTimezone());

		if ($timeZone instanceof TimeZoneOffset) {
			$timeZoneOffset = $timeZone;
		} else {
			$timeZoneOffset = TimeZoneOffset::ofTotalSeconds($dateTime->getOffset());
		}

		$instant = Instant::of($dateTime->getTimestamp(), $localDateTime->getNano());

		return new self($localDateTime, $timeZoneOffset, $timeZone, $instant);
	}

	public function toIsoString(): string
	{
		$result = $this->dateTime . $this->timeZoneOffset;

		if ($this->timeZone instanceof TimeZoneRegion) {
			$result .= sprintf('[%s]', $this->timeZone);
		}

		return $result;
	}

	public function format(string $localizedPattern, string|null $locale = null): string
	{
		$formatter = DateTimeFormatter::ofLocalizedPattern($localizedPattern, $locale);
		return $this->formatWith($formatter);
	}

	public function formatWith(DateTimeFormatter $formatter): string
	{
		return $formatter->formatZonedDateTime($this);
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
			'year' => $this->dateTime->getYear(),
			'month' => $this->dateTime->getMonth(),
			'day' => $this->dateTime->getDayOfMonth(),
			'hour' => $this->dateTime->getHour(),
			'minute' => $this->dateTime->getMinute(),
			'second' => $this->dateTime->getSecond(),
			'nano' => $this->dateTime->getNano(),
			'timeZone' => $this->timeZone->getId(),
		];
	}

	/**
	 * @param array{year: int, month: int, day: int, hour: int, minute: int, second: int, nano: int, timeZone: string} $data
	 */
	public function __unserialize(array $data): void
	{
		$year = $data['year'];
		$month = $data['month'];
		$day = $data['day'];
		$hour = $data['hour'];
		$minute = $data['minute'];
		$second = $data['second'];
		$nano = $data['nano'];

		$dateTime = LocalDateTime::of($year, $month, $day, $hour, $minute, $second, $nano);
		$timeZone = TimeZone::fromIsoString($data['timeZone']);
		$zonedDateTime = self::of($dateTime, $timeZone);

		$this->dateTime = $zonedDateTime->dateTime;
		$this->timeZoneOffset = $zonedDateTime->timeZoneOffset;
		$this->timeZone = $zonedDateTime->timeZone;
		$this->instant = $zonedDateTime->instant;
	}
}
