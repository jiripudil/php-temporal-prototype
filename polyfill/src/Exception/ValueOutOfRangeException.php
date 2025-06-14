<?php

declare(strict_types=1);

namespace Temporal\Exception;

use Temporal\TemporalException;
use function sprintf;

final class ValueOutOfRangeException extends TemporalException
{
	/**
	 * @internal
	 */
	public static function of(string $name, int $value, int $min, int $max): self
	{
		return new self(sprintf('Value %d is out of range for $%s: %d..%d', $value, $name, $min, $max));
	}
}
