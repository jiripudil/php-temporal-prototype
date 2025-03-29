<?php

declare(strict_types=1);

namespace Temporal\Clock;

use Temporal\Clock;
use Temporal\Instant;

final class SystemClock implements Clock
{
	public function getTime(): Instant {}
}
