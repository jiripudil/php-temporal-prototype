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

final class DateTimeConversionException extends TemporalException
{
	/**
	 * @internal
	 */
	public static function of(LocalDate|LocalTime|LocalDateTime|ZonedDateTime $value): self
	{
		$shortName = (new ReflectionClass($value))->getShortName();
		return new self(sprintf('Failed to convert a %s to DateTime', $shortName));
	}
}
