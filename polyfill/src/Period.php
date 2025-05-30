<?php

declare(strict_types=1);

namespace Temporal;

use JsonSerializable;
use Stringable;
use function preg_match;

final class Period implements JsonSerializable, Stringable
{
	private function __construct(
		private readonly int $years,
		private readonly int $months,
		private readonly int $days,
	) {}

	public static function of(int $years, int $months, int $days): self
	{
		return new self($years, $months, $days);
	}

	public static function ofYears(int $years): self
	{
		return new self($years, 0, 0);
	}

	public static function ofMonths(int $months): self
	{
		return new self(0, $months, 0);
	}

	public static function ofWeeks(int $weeks): self
	{
		return new self(0, 0, $weeks * 7);
	}

	public static function ofDays(int $days): self
	{
		return new self(0, 0, $days);
	}

	public static function zero(): self
	{
		/** @var self $zero */
		static $zero = new self(0, 0, 0);
		return $zero;
	}

	public static function between(LocalDate $start, LocalDate $endExclusive): self
	{
		return $start->until($endExclusive);
	}

	public static function fromIsoString(string $text): self
	{
		$pattern = '/^([+\-]?)P(?:([+\-]?[0-9]+)Y)?(?:([+\-]?[0-9]+)M)?(?:([+\-]?[0-9]+)W)?(?:([+\-]?[0-9]+)D)?()$/i';

		if (preg_match($pattern, $text, $matches) !== 1) {
			throw TemporalException::failedToParseInput();
		}

		[, $sign, $years, $months, $weeks, $days] = $matches;

		if ($years === '' && $months === '' && $weeks === '' && $days === '') {
			throw TemporalException::failedToParseInput();
		}

		$years = (int) $years;
		$months = (int) $months;
		$weeks = (int) $weeks;
		$days = (int) $days;

		if ($sign === '-') {
			$years = -$years;
			$months = -$months;
			$weeks = -$weeks;
			$days = -$days;
		}

		return new self($years, $months, $weeks * 7 + $days);
	}

	public function getYears(): int
	{
		return $this->years;
	}

	public function withYears(int $years): self
	{
		return new self($years, $this->months, $this->days);
	}

	public function plusYears(int $years): self
	{
		return $this->withYears($this->years + $years);
	}

	public function minusYears(int $years): self
	{
		return $this->withYears($this->years - $years);
	}

	public function getMonths(): int
	{
		return $this->months;
	}

	public function withMonths(int $months): self
	{
		return new self($this->years, $months, $this->days);
	}

	public function plusMonths(int $months): self
	{
		return $this->withMonths($this->months + $months);
	}

	public function minusMonths(int $months): self
	{
		return $this->withMonths($this->months - $months);
	}

	public function getDays(): int
	{
		return $this->days;
	}

	public function withDays(int $days): self
	{
		return new self($this->years, $this->months, $days);
	}

	public function plusDays(int $days): self
	{
		return $this->withDays($this->days + $days);
	}

	public function minusDays(int $days): self
	{
		return $this->withDays($this->days - $days);
	}

	public function negated(): self
	{
		return new self(
			-$this->years,
			-$this->months,
			-$this->days,
		);
	}

	public function isZero(): bool
	{
		return $this->years === 0
			&& $this->months === 0
			&& $this->days === 0;
	}

	public function isEqualTo(self $other): bool
	{
		return $this->years === $other->years
			&& $this->months === $other->months
			&& $this->days === $other->days;
	}

	public function toIsoString(): string
	{
		if ($this->isZero()) {
			return 'P0D';
		}

		$result = 'P';

		if ($this->years !== 0) {
			$result .= $this->years . 'Y';
		}

		if ($this->months !== 0) {
			$result .= $this->months . 'M';
		}

		if ($this->days !== 0) {
			$result .= $this->days . 'D';
		}

		return $result;
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
			'years' => $this->years,
			'months' => $this->months,
			'days' => $this->days,
		];
	}

	public function __unserialize(array $data): void
	{
		$this->years = $data['years'];
		$this->months = $data['months'];
		$this->days = $data['days'];
	}
}
