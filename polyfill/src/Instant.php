<?php

declare(strict_types=1);

namespace Temporal;

use JsonSerializable;
use Stringable;
use Temporal\Clock\SystemClock;
use function intdiv;
use function rtrim;
use function str_pad;
use const PHP_INT_MAX;
use const PHP_INT_MIN;
use const STR_PAD_LEFT;

final class Instant implements JsonSerializable, Stringable
{
	private function __construct(
		private readonly int $epochSecond,
		private readonly int $nano = 0,
	) {}

	public static function of(int $epochSecond, int $nanoAdjustment = 0): self
	{
		if ($epochSecond === 0 && $nanoAdjustment === 0) {
			return self::epoch();
		}

		$nanos = $nanoAdjustment % Duration::NANOS_PER_SECOND;
		$epochSecond += intdiv($nanoAdjustment - $nanos, Duration::NANOS_PER_SECOND);

		if ($nanos < 0) {
			$nanos += Duration::NANOS_PER_SECOND;
			$epochSecond--;
		}

		return new self($epochSecond, $nanos);
	}

	public static function now(Clock|null $clock = null): self
	{
		return ($clock ?? new SystemClock())->getTime();
	}

	public static function epoch(): self
	{
		/** @var self $epoch */
		static $epoch = new self(0);
		return $epoch;
	}

	public static function min(): self
	{
		/** @var self $min */
		static $min = new self(PHP_INT_MIN, 0);
		return $min;
	}

	public static function max(): self
	{
		/** @var self $max */
		static $max = new self(PHP_INT_MAX, Duration::NANOS_PER_SECOND - 1);
		return $max;
	}

	public function getEpochSecond(): int
	{
		return $this->epochSecond;
	}

	public function getNano(): int
	{
		return $this->nano;
	}

	public function withEpochSecond(int $epochSecond): self
	{
		return new self($epochSecond, $this->nano);
	}

	public function withNano(int $nano): self
	{
		if ($nano < 0 || $nano > Duration::NANOS_PER_SECOND - 1) {
			throw TemporalException::valueOutOfRange('nano', $nano, 0, Duration::NANOS_PER_SECOND - 1);
		}

		return new self($this->epochSecond, $nano);
	}

	public function plus(Duration $duration): self
	{
		$epochSecond = $this->epochSecond + $duration->getSeconds();
		$nano = $this->nano + $duration->getNanos();

		return self::of($epochSecond, $nano);
	}

	public function plusSeconds(int $seconds): self
	{
		return $this->plus(Duration::ofSeconds($seconds));
	}

	public function plusMinutes(int $minutes): self
	{
		return $this->plus(Duration::ofMinutes($minutes));
	}

	public function plusHours(int $hours): self
	{
		return $this->plus(Duration::ofHours($hours));
	}

	public function plusDays(int $days): self
	{
		return $this->plus(Duration::ofDays($days));
	}

	public function minus(Duration $duration): self
	{
		return $this->plus($duration->negated());
	}

	public function minusSeconds(int $seconds): self
	{
		return $this->minus(Duration::ofSeconds($seconds));
	}

	public function minusMinutes(int $minutes): self
	{
		return $this->minus(Duration::ofMinutes($minutes));
	}

	public function minusHours(int $seconds): self
	{
		return $this->minus(Duration::ofHours($seconds));
	}

	public function minusDays(int $days): self
	{
		return $this->minus(Duration::ofDays($days));
	}

	public function compareTo(self $other): int
	{
		$cmp = $this->epochSecond <=> $other->epochSecond;
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

	public function atTimeZone(TimeZone $timeZone): ZonedDateTime
	{
		return ZonedDateTime::ofInstant($this, $timeZone);
	}

	public function toDecimal(): string
	{
		$result = (string) $this->epochSecond;

		if ($this->nano > 0) {
			$result .= '.';
			$result .= rtrim(str_pad((string) $this->nano, 9, '0', STR_PAD_LEFT), '0');
		}

		return $result;
	}

	public function toIsoString(): string
	{
		return $this->atTimeZone(TimeZoneOffset::utc())->toIsoString();
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
			'epochSecond' => $this->epochSecond,
			'nano' => $this->nano,
		];
	}

	public function __unserialize(array $data): void
	{
		$this->epochSecond = $data['epochSecond'];
		$this->nano = $data['nano'];
	}
}
