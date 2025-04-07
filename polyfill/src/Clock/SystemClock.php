<?php

declare(strict_types=1);

namespace Temporal\Clock;

use Temporal\Clock;
use Temporal\Instant;
use function explode;
use function microtime;
use function substr;

final class SystemClock implements Clock
{
	public function getTime(): Instant
	{
		[$fraction, $epochSecond] = explode(' ', microtime());

		$epochSecond = (int) $epochSecond;
		$nanos = 10 * (int) substr($fraction, 2, 8);

		return Instant::of($epochSecond, $nanos);
	}
}
