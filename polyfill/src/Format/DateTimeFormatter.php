<?php

declare(strict_types=1);

namespace Temporal\Format;

use IntlDateFormatter;
use IntlDatePatternGenerator;
use IntlTimeZone;
use Temporal\LocalDate;
use Temporal\LocalDateTime;
use Temporal\LocalTime;
use Temporal\TemporalException;
use Temporal\ZonedDateTime;
use function sprintf;

final class DateTimeFormatter
{
	private function __construct(
		private readonly IntlDateFormatter $formatter,
	) {}

	public static function ofPattern(string $pattern, string|null $locale = null): self
	{
		$formatter = new IntlDateFormatter(
			$locale,
			IntlDateFormatter::NONE,
			IntlDateFormatter::NONE,
			timezone: IntlTimeZone::createTimeZone('UTC'),
			pattern: $pattern,
		);

		return new self($formatter);
	}

	public static function ofLocalizedPattern(string $localizedPattern, string|null $locale = null): self
	{
		$pattern = (new IntlDatePatternGenerator($locale))->getBestPattern($localizedPattern);
		if ($pattern === false) {
			throw new TemporalException(sprintf('Failed to generate pattern from "%s" for locale "%s"', $localizedPattern, $locale));
		}

		return self::ofPattern($pattern, $locale);
	}

	public static function ofDate(FormatStyle $dateStyle, string|null $locale = null): self
	{
		$formatter = new IntlDateFormatter(
			$locale,
			$dateStyle->toIntlConstant(),
			IntlDateFormatter::NONE,
			timezone: IntlTimeZone::createTimeZone('UTC'),
		);

		return new self($formatter);
	}

	public static function ofTime(FormatStyle $timeStyle, string|null $locale = null): self
	{
		$formatter = new IntlDateFormatter(
			$locale,
			IntlDateFormatter::NONE,
			$timeStyle->toIntlConstant(),
			timezone: IntlTimeZone::createTimeZone('UTC'),
		);

		return new self($formatter);
	}

	public static function ofDateTime(FormatStyle $dateStyle, FormatStyle $timeStyle, string|null $locale = null): self
	{
		$formatter = new IntlDateFormatter(
			$locale,
			$dateStyle->toIntlConstant(),
			$timeStyle->toIntlConstant(),
			timezone: IntlTimeZone::createTimeZone('UTC'),
		);

		return new self($formatter);
	}

	public function formatLocalTime(LocalTime $value): string
	{
		return $this->format($value);
	}

	public function formatLocalDate(LocalDate $value): string
	{
		return $this->format($value);
	}

	public function formatLocalDateTime(LocalDateTime $value): string
	{
		return $this->format($value);
	}

	public function formatZonedDateTime(ZonedDateTime $value): string
	{
		return $this->format($value);
	}

	private function format(LocalDate|LocalTime|LocalDateTime|ZonedDateTime $value): string
	{
		$formatter = clone $this->formatter;

		if ($value instanceof ZonedDateTime) {
			$formatter->setTimeZone($value->getTimeZone()->toDateTimeZone());
		}

		$pattern = $formatter->getPattern();
		if ($pattern === false) {
			throw TemporalException::failedToFormatValue();
		}

		PatternValidator::validatePattern($pattern, $value);

		$formatted = $formatter->format($value->toDateTime());
		if ($formatted === false) {
			throw TemporalException::failedToFormatValue();
		}

		return $formatted;
	}
}
