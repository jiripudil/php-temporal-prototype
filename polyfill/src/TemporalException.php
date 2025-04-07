<?php

declare(strict_types=1);

namespace Temporal;

use Exception;
use function sprintf;

final class TemporalException extends Exception
{
	public static function valueOutOfRange(string $name, int $value, int $min, int $max): self
	{
		return new self(sprintf('Value %d is out of range for $%s: %d..%d', $value, $name, $min, $max));
	}

	public static function failedToParseInput(TemporalException|null $previous = null): self
	{
		return new self('Failed to parse given input into a Temporal value.', previous: $previous);
	}

	public static function failedToFormatValue(): self
	{
		return new self('Failed to format a Temporal value.');
	}

	public static function failedToConvertToDateTime(): self
	{
		return new self('Failed to convert a Temporal value to DateTime.');
	}

	public static function failedToConvertFromDateTime(): self
	{
		return new self('Failed to convert DateTime to a Temporal value.');
	}
}
