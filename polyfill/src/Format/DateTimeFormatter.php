<?php

declare(strict_types=1);

namespace Temporal\Format;

use IntlDateFormatter;
use IntlDatePatternGenerator;
use IntlTimeZone;
use Temporal\Exception\FormattingException;
use Temporal\LocalDate;
use Temporal\LocalDateTime;
use Temporal\LocalTime;
use Temporal\ZonedDateTime;

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
			throw FormattingException::failedToGeneratePattern($localizedPattern, $locale);
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
			throw FormattingException::invalidPattern($value);
		}

		PatternValidator::validatePattern($pattern, $value);

		$formatted = $formatter->format($value->toDateTime());
		if ($formatted === false) {
			throw FormattingException::failedToFormatValue($value, $formatter->getErrorMessage());
		}

		return $formatted;
	}
}
