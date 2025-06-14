<?php

declare(strict_types=1);

namespace Temporal\Exception;

use ReflectionClass;
use Temporal\LocalDate;
use Temporal\LocalDateTime;
use Temporal\LocalTime;
use Temporal\TemporalException;
use Temporal\ZonedDateTime;
use function sprintf;

final class FormattingException extends TemporalException
{
	/**
	 * @internal
	 */
	public static function failedToGeneratePattern(string $localizedPattern, string|null $locale): self
	{
		$locale = $locale !== null ? sprintf('locale "%s"', $locale) : 'default locale';
		return new self(sprintf('Failed to generate pattern from "%s" for %s', $localizedPattern, $locale));
	}

	/**
	 * @internal
	 */
	public static function invalidPattern(LocalDate|LocalTime|LocalDateTime|ZonedDateTime $value): self
	{
		$shortName = (new ReflectionClass($value))->getShortName();
		return new self(sprintf('Failed to format a %s: the formatting pattern is not valid for given value', $shortName));
	}

	/**
	 * @internal
	 */
	public static function failedToFormatValue(LocalDate|LocalTime|LocalDateTime|ZonedDateTime $value, string $errorMessage): self
	{
		$shortName = (new ReflectionClass($value))->getShortName();
		return new self(sprintf('Failed to format a %s: %s', $shortName, $errorMessage));
	}
}
