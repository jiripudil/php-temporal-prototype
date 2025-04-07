<?php

declare(strict_types=1);

namespace Temporal;

use JsonSerializable;
use Stringable;
use function intdiv;
use function preg_match;
use function rtrim;
use function str_pad;
use const STR_PAD_LEFT;

final class Duration implements JsonSerializable, Stringable
{
	public const NANOS_PER_SECOND = 1_000_000_000;
	public const SECONDS_PER_MINUTE = 60;
	public const SECONDS_PER_HOUR = 3600;
	public const SECONDS_PER_DAY = 86400;
	public const MINUTES_PER_HOUR = 60;
	public const HOURS_PER_DAY = 24;

	private function __construct(
		private readonly int $seconds,
		private readonly int $nanos = 0,
	) {}

	public static function zero(): self
	{
		/** @var self $zero */
		static $zero = new self(0);
		return $zero;
	}

	public static function parse(string $value): self
	{
		$pattern = '/^([+\-]?)P(?:([+\-]?[0-9]+)D)?(?:T(?:([+\-]?[0-9]+)H)?(?:([+\-]?[0-9]+)M)?(?:([+\-]?[0-9]+)(?:\.([0-9]{1,9}))?S)?)?()$/i';

		if (preg_match($pattern, $value, $matches) !== 1) {
			throw TemporalException::failedToParseInput();
		}

		[, $sign, $days, $hours, $minutes, $seconds, $nanos] = $matches;
		if ($days === '' && $hours === '' && $minutes === '' && $seconds === '') {
			throw TemporalException::failedToParseInput();
		}

		$days = (int) $days;
		$hours = (int) $hours;
		$minutes = (int) $minutes;
		$seconds = (int) $seconds;
		$nanos = (int) str_pad($nanos, 9, '0');

		if ($seconds < 0) {
			$nanos *= -1;
		}

		if ($sign === '-') {
			$days = -$days;
			$hours = -$hours;
			$minutes = -$minutes;
			$seconds = -$seconds;
			$nanos = -$nanos;
		}

		$seconds = $seconds
			+ $days * self::SECONDS_PER_DAY
			+ $hours * self::SECONDS_PER_HOUR
			+ $minutes * self::SECONDS_PER_MINUTE;

		return self::ofSeconds($seconds, $nanos);
	}

	public static function ofSeconds(int $seconds, int $nanoAdjustment = 0): self
	{
		$nanos = $nanoAdjustment % self::NANOS_PER_SECOND;
		$seconds += intdiv($nanoAdjustment - $nanos, self::NANOS_PER_SECOND);

		if ($nanos < 0) {
			$nanos += self::NANOS_PER_SECOND;
			$seconds--;
		}

		return new self($seconds, $nanos);
	}

	public static function ofMinutes(int $minutes): self
	{
		return self::ofSeconds($minutes * self::SECONDS_PER_MINUTE);
	}

	public static function ofHours(int $hours): self
	{
		return self::ofSeconds($hours * self::SECONDS_PER_HOUR);
	}

	public static function ofDays(int $days): self
	{
		return self::ofSeconds($days * self::SECONDS_PER_DAY);
	}

	public static function between(Instant $start, Instant $endExclusive): self
	{
		$seconds = $endExclusive->getEpochSecond() - $start->getEpochSecond();
		$nanos = $endExclusive->getNano() - $start->getNano();

		return self::ofSeconds($seconds, $nanos);
	}

	public function getSeconds(): int
	{
		return $this->seconds;
	}

	public function getNanos(): int
	{
		return $this->nanos;
	}

	public function toDays(): int
	{
		return intdiv($this->seconds, self::SECONDS_PER_DAY);
	}

	public function toDaysPart(): int
	{
		return $this->toDays();
	}

	public function toHours(): int
	{
		return intdiv($this->seconds, self::SECONDS_PER_HOUR);
	}

	public function toHoursPart(): int
	{
		return $this->toHours() % self::HOURS_PER_DAY;
	}

	public function toMinutes(): int
	{
		return intdiv($this->seconds, self::SECONDS_PER_MINUTE);
	}

	public function toMinutesPart(): int
	{
		return $this->toMinutes() % self::MINUTES_PER_HOUR;
	}

	public function toSeconds(): int
	{
		return $this->seconds;
	}

	public function toSecondsPart(): int
	{
		return $this->seconds % self::SECONDS_PER_MINUTE;
	}

	public function isZero(): bool
	{
		return $this->seconds === 0 && $this->nanos === 0;
	}

	public function isPositive(): bool
	{
		return $this->seconds > 0 || ($this->seconds === 0 && $this->nanos > 0);
	}

	public function isPositiveOrZero(): bool
	{
		return $this->seconds >= 0;
	}

	public function isNegative(): bool
	{
		return $this->seconds < 0;
	}

	public function isNegativeOrZero(): bool
	{
		return $this->seconds < 0 || ($this->seconds === 0 && $this->nanos === 0);
	}

	public function plus(self $other): self
	{
		$seconds = $this->seconds + $other->seconds;
		$nanos = $this->nanos + $other->nanos;

		return self::ofSeconds($seconds, $nanos);
	}

	public function plusSeconds(int $seconds): self
	{
		return $this->plus(self::ofSeconds($seconds));
	}

	public function plusMinutes(int $minutes): self
	{
		return $this->plus(self::ofMinutes($minutes));
	}

	public function plusHours(int $hours): self
	{
		return $this->plus(self::ofHours($hours));
	}

	public function plusDays(int $days): self
	{
		return $this->plus(self::ofDays($days));
	}

	public function minus(self $other): self
	{
		return $this->plus($other->negated());
	}

	public function minusSeconds(int $seconds): self
	{
		return $this->minus(self::ofSeconds($seconds));
	}

	public function minusMinutes(int $minutes): self
	{
		return $this->minus(self::ofMinutes($minutes));
	}

	public function minusHours(int $hours): self
	{
		return $this->minus(self::ofHours($hours));
	}

	public function minusDays(int $days): self
	{
		return $this->minus(self::ofDays($days));
	}

	public function negated(): self
	{
		return self::ofSeconds(-$this->seconds, -$this->nanos);
	}

	public function abs(): self
	{
		return $this->isNegative() ? $this->negated() : $this;
	}

	public function compareTo(self $other): int
	{
		$cmp = $this->seconds <=> $other->seconds;
		if ($cmp !== 0) {
			return $cmp;
		}

		return $this->nanos <=> $other->nanos;
	}

	public function isEqualTo(self $other): bool
	{
		return $this->compareTo($other) === 0;
	}

	public function isGreaterThan(self $other): bool
	{
		return $this->compareTo($other) > 0;
	}

	public function isGreaterThanOrEqualTo(self $other): bool
	{
		return $this->compareTo($other) >= 0;
	}

	public function isLesserThan(self $other): bool
	{
		return $this->compareTo($other) < 0;
	}

	public function isLesserThanOrEqualTo(self $other): bool
	{
		return $this->compareTo($other) <= 0;
	}

	public function toISOString(): string
	{
		$seconds = $this->seconds;
		$nanos = $this->nanos;

		if ($seconds === 0 && $nanos === 0) {
			return 'PT0S';
		}

		$negative = $seconds < 0;

		if ($negative && $nanos !== 0) {
			$seconds++;
			$nanos = self::NANOS_PER_SECOND - $nanos;
		}

		$hours = intdiv($seconds, self::SECONDS_PER_HOUR);
		$minutes = intdiv($seconds % self::SECONDS_PER_HOUR, self::SECONDS_PER_MINUTE);
		$seconds = $seconds % self::SECONDS_PER_MINUTE;

		$result = 'PT';

		if ($hours !== 0) {
			$result .= $hours . 'H';
		}

		if ($minutes !== 0) {
			$result .= $minutes . 'M';
		}

		if ($seconds === 0 && $nanos === 0) {
			return $result;
		}

		$result .= ($seconds === 0 && $negative) ? '-0' : $seconds;

		if ($nanos !== 0) {
			$result .= '.' . rtrim(str_pad((string) $nanos, 9, '0', STR_PAD_LEFT), '0');
		}

		return $result . 'S';
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
