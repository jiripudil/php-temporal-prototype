<?php

declare(strict_types=1);

namespace Temporal\Exception;

use Temporal\TemporalException;
use function sprintf;

final class ParsingException extends TemporalException
{
	/**
	 * @internal
	 */
	public static function invalidIsoString(string $input): self
	{
		return new self(sprintf('Failed to parse input "%s": invalid ISO 8601 string', $input));
	}

	/**
	 * @internal
	 */
	public static function valueOutOfRange(string $input, ValueOutOfRangeException $exception): self
	{
		return new self(sprintf('Failed to parse input "%s": %s', $input, $exception->getMessage()), previous: $exception);
	}

	/**
	 * @internal
	 */
	public static function unknownTimeZone(string $input, UnknownTimeZoneException $exception): self
	{
		return new self(sprintf('Failed to parse input "%s": %s', $input, $exception->getMessage()), previous: $exception);
	}

	/**
	 * @internal
	 */
	public static function of(string $input, string $errorMessage): self
	{
		return new self(sprintf('Failed to parse input "%s": %s', $input, $errorMessage));
	}
}
