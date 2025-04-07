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
use function rtrim;
use function sprintf;
use function str_pad;
use const STR_PAD_LEFT;

final class LocalTime implements JsonSerializable, Stringable
{
	private function __construct(
		private readonly int $hour,
		private readonly int $minute,
		private readonly int $second,
		private readonly int $nano,
	) {}

	public static function of(int $hour, int $minute, int $second = 0, int $nano = 0): self
	{
		if ($hour < 0 || $hour >= Duration::HOURS_PER_DAY) {
			throw TemporalException::valueOutOfRange('hour', $hour, 0, Duration::HOURS_PER_DAY - 1);
		}

		if ($minute < 0 || $minute >= Duration::MINUTES_PER_HOUR) {
			throw TemporalException::valueOutOfRange('minute', $minute, 0, Duration::MINUTES_PER_HOUR - 1);
		}

		if ($second < 0 || $second >= Duration::SECONDS_PER_MINUTE) {
			throw TemporalException::valueOutOfRange('second', $second, 0, Duration::SECONDS_PER_MINUTE - 1);
		}

		if ($nano < 0 || $nano >= Duration::NANOS_PER_SECOND) {
			throw TemporalException::valueOutOfRange('nano', $nano, 0, Duration::NANOS_PER_SECOND - 1);
		}

		return new self($hour, $minute, $second, $nano);
	}

	public static function ofSecondOfDay(int $secondOfDay, int $nano = 0): self
	{
		if ($secondOfDay < 0 || $secondOfDay >= Duration::SECONDS_PER_DAY) {
			throw TemporalException::valueOutOfRange('secondOfDay', $secondOfDay, 0, Duration::SECONDS_PER_DAY - 1);
		}

		if ($nano < 0 || $nano >= Duration::NANOS_PER_SECOND) {
			throw TemporalException::valueOutOfRange('nano', $nano, 0, Duration::NANOS_PER_SECOND - 1);
		}

		$hour = intdiv($secondOfDay, Duration::SECONDS_PER_HOUR);
		$minute = intdiv($secondOfDay % Duration::SECONDS_PER_HOUR, Duration::SECONDS_PER_MINUTE);
		$second = $secondOfDay % Duration::SECONDS_PER_MINUTE;

		return new self($hour, $minute, $second, $nano);
	}

	public static function now(TimeZone $timeZone, Clock|null $clock = null): self
	{
		return ZonedDateTime::now($timeZone, $clock)->getTime();
	}

	public static function parse(string $text): self
	{
		$pattern = '/^(\d{2}):(\d{2})(?::(\d{2})(?:\\.(\d{1,9}))?)?()$/';

		if (preg_match($pattern, $text, $matches) !== 1) {
			throw TemporalException::failedToParseInput();
		}

		[, $hour, $minute, $second, $nano] = $matches;

		$hour = (int) $hour;
		$minute = (int) $minute;
		$second = (int) $second;
		$nano = (int) str_pad($nano, 9, '0');

		try {
			return self::of($hour, $minute, $second, $nano);
		} catch (TemporalException $e) {
			throw TemporalException::failedToParseInput($e);
		}
	}

	public static function midnight(): self
	{
		/** @var self $midnight */
		static $midnight = new self(0, 0, 0, 0);
		return $midnight;
	}

	public static function noon(): self
	{
		/** @var self $noon */
		static $noon = new self(12, 0, 0, 0);
		return $noon;
	}

	public static function min(): self
	{
		return self::midnight();
	}

	public static function max(): self
	{
		/** @var self $max */
		static $max = new self(23, 59, 59, 999_999_999);
		return $max;
	}

	public function getHour(): int
	{
		return $this->hour;
	}

	public function withHour(int $hour): self
	{
		if ($hour < 0 || $hour >= Duration::HOURS_PER_DAY) {
			throw TemporalException::valueOutOfRange('hour', $hour, 0, Duration::HOURS_PER_DAY - 1);
		}

		return new self($hour, $this->minute, $this->second, $this->nano);
	}

	public function getMinute(): int
	{
		return $this->minute;
	}

	public function withMinute(int $minute): self
	{
		if ($minute < 0 || $minute >= Duration::MINUTES_PER_HOUR) {
			throw TemporalException::valueOutOfRange('minute', $minute, 0, Duration::MINUTES_PER_HOUR - 1);
		}

		return new self($this->hour, $minute, $this->second, $this->nano);
	}

	public function getSecond(): int
	{
		return $this->second;
	}

	public function withSecond(int $second): self
	{
		if ($second < 0 || $second >= Duration::SECONDS_PER_MINUTE) {
			throw TemporalException::valueOutOfRange('second', $second, 0, Duration::SECONDS_PER_MINUTE - 1);
		}

		return new self($this->hour, $this->minute, $second, $this->nano);
	}

	public function getNano(): int
	{
		return $this->nano;
	}

	public function withNano(int $nano): self
	{
		if ($nano < 0 || $nano >= Duration::NANOS_PER_SECOND) {
			throw TemporalException::valueOutOfRange('nano', $nano, 0, Duration::NANOS_PER_SECOND - 1);
		}

		return new self($this->hour, $this->minute, $this->second, $nano);
	}

	public function getSecondOfDay(): int
	{
		return $this->hour * Duration::SECONDS_PER_HOUR
			+ $this->minute * Duration::SECONDS_PER_MINUTE
			+ $this->second;
	}

	public function plus(Duration $duration): self
	{
		$second = $this->getSecondOfDay() + $duration->getSeconds();
		$nanoAdjustment = $this->nano + $duration->getNanos();

		$nano = $nanoAdjustment % Duration::NANOS_PER_SECOND;
		$second += intdiv($nanoAdjustment - $nano, Duration::NANOS_PER_SECOND);

		if ($nano < 0) {
			$nano += Duration::NANOS_PER_SECOND;
			$second--;
		}

		$day = intdiv($second, Duration::SECONDS_PER_DAY);
		$second -= $day * Duration::SECONDS_PER_DAY;
		if ($second < 0) {
			$second += Duration::SECONDS_PER_DAY;
		}

		$hour = intdiv($second, Duration::SECONDS_PER_HOUR);
		$second -= $hour * Duration::SECONDS_PER_HOUR;

		$minute = intdiv($second, Duration::SECONDS_PER_MINUTE);
		$second -= $minute * Duration::SECONDS_PER_MINUTE;

		return self::of($hour, $minute, $second, $nano);
	}

	public function plusHours(int $hours): self
	{
		return $this->plus(Duration::ofHours($hours));
	}

	public function plusMinutes(int $minutes): self
	{
		return $this->plus(Duration::ofMinutes($minutes));
	}

	public function plusSeconds(int $seconds): self
	{
		return $this->plus(Duration::ofSeconds($seconds));
	}

	public function plusNanos(int $nanos): self
	{
		return $this->plus(Duration::ofSeconds(0, $nanos));
	}

	public function minus(Duration $duration): self
	{
		return $this->plus($duration->negated());
	}

	public function minusHours(int $hours): self
	{
		return $this->minus(Duration::ofHours($hours));
	}

	public function minusMinutes(int $minutes): self
	{
		return $this->minus(Duration::ofMinutes($minutes));
	}

	public function minusSeconds(int $seconds): self
	{
		return $this->minus(Duration::ofSeconds($seconds));
	}

	public function minusNanos(int $nanos): self
	{
		return $this->minus(Duration::ofSeconds(0, $nanos));
	}

	public function atDate(LocalDate $date): LocalDateTime
	{
		return LocalDateTime::ofDateTime($date, $this);
	}

	public function compareTo(self $other): int
	{
		$cmp = $this->getSecondOfDay() <=> $other->getSecondOfDay();
		if ($cmp !== 0) {
			return $cmp;
		}

		return $this->nano <=> $other->nano;
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

		// round down nano to microseconds
		$nano = 1000 * intdiv($this->nano, 1000);

		if ($this->second !== 0 || $nano !== 0) {
			$format .= ':s';
			if ($nano !== 0) {
				$format .= '.u';
			}
		}

		$dateTime = '0000-01-01T' . $this->withNano($nano);
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
			(int) $dateTime->format('G'),
			(int) $dateTime->format('i'),
			(int) $dateTime->format('s'),
			1000 * (int) $dateTime->format('u'),
		);
	}

	public function toISOString(): string
	{
		$result = sprintf('%02d:%02d', $this->hour, $this->minute);

		if ($this->second === 0 && $this->nano === 0) {
			return $result;
		}

		$result .= sprintf(':%02d', $this->second);

		if ($this->nano !== 0) {
			$result .= '.' . rtrim(str_pad((string) $this->nano, 9, '0', STR_PAD_LEFT), '0');
		}

		return $result;
	}

	public function format(string $localizedPattern, string|null $locale = null): string
	{
		return $this->formatWith(DateTimeFormatter::ofLocalizedPattern($localizedPattern, $locale));
	}

	public function formatWith(DateTimeFormatter $formatter): string
	{
		return $formatter->formatLocalTime($this);
	}

	public function jsonSerialize(): string
	{
		return $this->toISOString();
	}

	public function __toString(): string
	{
		return $this->toISOString();
	}
}
