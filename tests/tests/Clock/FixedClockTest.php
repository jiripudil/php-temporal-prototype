<?php

declare(strict_types=1);

namespace Temporal\Tests\Clock;

use PHPUnit\Framework\TestCase;
use Temporal\Clock\FixedClock;
use Temporal\Instant;
use function usleep;

final class FixedClockTest extends TestCase
{
	public function testFixedClock(): void
	{
		$a = Instant::of(42);
		$clock = new FixedClock($a);

		$now = $clock->getTime();
		self::assertTrue($now->isEqualTo($a));

		usleep(1);

		$now = $clock->getTime();
		self::assertTrue($now->isEqualTo($a));

		$b = Instant::of(44);
		$clock->setTime($b);

		$now = $clock->getTime();
		self::assertTrue($now->isEqualTo($b));
	}
}
