<?php

declare(strict_types=1);

namespace Temporal;

use DateTimeZone;
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
			throw TemporalException::valueOutOfRange('hours', $hours, -18, 18);
		}

		if ($minutes < -59 || $minutes > 59) {
			throw TemporalException::valueOutOfRange('minutes', $minutes, -59, 59);
		}

		if ($seconds < -59 || $seconds > 59) {
			throw TemporalException::valueOutOfRange('seconds', $seconds, -59, 59);
		}

		if (
			($hours > 0 && ($minutes < 0 || $seconds < 0))
			|| ($hours < 0 && ($minutes > 0 || $seconds > 0))
			|| ($minutes > 0 && $seconds < 0)
			|| ($minutes < 0 && $seconds > 0)
		) {
			throw TemporalException::failedToParseInput();
		}

		$totalSeconds = $hours * Duration::SECONDS_PER_HOUR
			+ $minutes * Duration::SECONDS_PER_MINUTE
			+ $seconds;

		if ($totalSeconds < -64800 || $totalSeconds > 64800) {
			throw TemporalException::valueOutOfRange('totalSeconds', $totalSeconds, -64800, 64800);
		}

		return new self($totalSeconds);
	}

	public static function ofTotalSeconds(int $totalSeconds): self
	{
		if ($totalSeconds < -64800 || $totalSeconds > 64800) {
			throw TemporalException::valueOutOfRange('totalSeconds', $totalSeconds, -64800, 64800);
		}

		return new self($totalSeconds);
	}

	public static function utc(): self
	{
		/** @var self $utc */
		static $utc = new self(0);
		return $utc;
	}

	public static function fromISOString(string $text): self
	{
		if ($text === 'Z' || $text === 'z') {
			return self::utc();
		}

		$pattern = '/^([+\-])(\d{2}):(\d{2})(?::(\d{2}))?()$/';

		if (preg_match($pattern, $text, $matches) !== 1) {
			throw TemporalException::failedToParseInput();
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
		} catch (TemporalException $e) {
			throw TemporalException::failedToParseInput($e);
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

	public function __unserialize(array $data): void
	{
		$this->totalSeconds = $data['totalSeconds'];
	}
}
