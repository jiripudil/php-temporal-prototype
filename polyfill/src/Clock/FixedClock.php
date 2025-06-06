<?php

declare(strict_types=1);

namespace Temporal\Clock;

use Temporal\Clock;
use Temporal\Instant;

final class FixedClock implements Clock
{
	public function __construct(
		private Instant $instant,
	) {}

	public function getTime(): Instant
	{
		return $this->instant;
	}

	public function setTime(Instant $instant): void
	{
		$this->instant = $instant;
	}
}
