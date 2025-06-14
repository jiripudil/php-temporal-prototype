<?php

declare(strict_types=1);

namespace Temporal;

use DateTimeZone;
use Temporal\Exception\ParsingException;
use Temporal\Exception\ValueOutOfRangeException;
use function abs;
use function preg_match;

final class TimeZoneOffset extends TimeZone
{
	private function __construct(
		private readonly int $totalSeconds,
	) {}

	public static function of(int $hours, int $minutes = 0, int $seconds = 0): self
	{
		if ($hours < -18 || $hours > 18) {
			throw ValueOutOfRangeException::of('hours', $hours, -18, 18);
		}

		if ($minutes < -59 || $minutes > 59) {
			throw ValueOutOfRangeException::of('minutes', $minutes, -59, 59);
		}

		if ($seconds < -59 || $seconds > 59) {
			throw ValueOutOfRangeException::of('seconds', $seconds, -59, 59);
		}

		if (
			($hours > 0 && ($minutes < 0 || $seconds < 0))
			|| ($hours < 0 && ($minutes > 0 || $seconds > 0))
			|| ($minutes > 0 && $seconds < 0)
			|| ($minutes < 0 && $seconds > 0)
		) {
			throw new TemporalException('Invalid input for TimeZoneOffset: all values must have the same sign.');
		}

		$totalSeconds = $hours * Duration::SECONDS_PER_HOUR
			+ $minutes * Duration::SECONDS_PER_MINUTE
			+ $seconds;

		if ($totalSeconds < -64800 || $totalSeconds > 64800) {
			throw ValueOutOfRangeException::of('totalSeconds', $totalSeconds, -64800, 64800);
		}

		return new self($totalSeconds);
	}

	public static function ofTotalSeconds(int $totalSeconds): self
	{
		if ($totalSeconds < -64800 || $totalSeconds > 64800) {
			throw ValueOutOfRangeException::of('totalSeconds', $totalSeconds, -64800, 64800);
		}

		return new self($totalSeconds);
	}

	public static function utc(): self
	{
		/** @var self $utc */
		static $utc = new self(0);
		return $utc;
	}

	public static function fromIsoString(string $text): self
	{
		if ($text === 'Z' || $text === 'z') {
			return self::utc();
		}

		$pattern = '/^([+\-])(\d{2}):(\d{2})(?::(\d{2}))?()$/';

		if (preg_match($pattern, $text, $matches) !== 1) {
			throw ParsingException::invalidIsoString($text);
		}

		[, $sign, $hours, $minutes, $seconds] = $matches;

		$hours = (int) $hours;
		$minutes = (int) $minutes;
		$seconds = (int) $seconds;

		if ($sign === '-') {
			$hours = -$hours;
			$minutes = -$minutes;
			$seconds = -$seconds;
		}

		try {
			return self::of($hours, $minutes, $seconds);
		} catch (ValueOutOfRangeException $e) {
			throw ParsingException::valueOutOfRange($text, $e);
		}
	}

	public function getTotalSeconds(): int
	{
		return $this->totalSeconds;
	}

	public function getId(): string
	{
		if ($this->totalSeconds > 0) {
			return '+' . LocalTime::ofSecondOfDay($this->totalSeconds);
		}

		if ($this->totalSeconds < 0) {
			return '-' . LocalTime::ofSecondOfDay(abs($this->totalSeconds));
		}

		return 'Z';
	}

	public function getOffset(Instant $instant): int
	{
		return $this->totalSeconds;
	}

	public function toDateTimeZone(): DateTimeZone
	{
		return new DateTimeZone($this->getId());
	}

	public function __serialize(): array
	{
		return [
			'totalSeconds' => $this->totalSeconds,
		];
	}

	/**
	 * @param array{totalSeconds: int} $data
	 */
	public function __unserialize(array $data): void
	{
		$this->totalSeconds = $data['totalSeconds'];
	}
}
