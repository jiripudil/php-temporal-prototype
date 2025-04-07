<?php

declare(strict_types=1);

namespace Temporal\Tests\Clock;

use PHPUnit\Framework\TestCase;
use Temporal\Clock\SystemClock;
use function usleep;

final class SystemClockTest extends TestCase
{
	public function testSystemClock(): void
	{
		$clock = new SystemClock();
		$a = $clock->getTime();

		usleep(1);
		$b = $clock->getTime();

		self::assertTrue($a->isBefore($b));
	}
}
