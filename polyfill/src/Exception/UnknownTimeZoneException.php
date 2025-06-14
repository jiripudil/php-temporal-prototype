<?php

declare(strict_types=1);

namespace Temporal\Exception;

use Temporal\TemporalException;
use function sprintf;

final class UnknownTimeZoneException extends TemporalException
{
	/**
	 * @internal
	 */
	public static function of(string $id): self
	{
		return new self(sprintf('Unrecognized time zone identifier "%s"', $id));
	}
}
