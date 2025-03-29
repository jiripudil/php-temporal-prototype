<?php

declare(strict_types=1);

namespace Temporal;

interface Clock
{
	public function getTime(): Instant;
}
