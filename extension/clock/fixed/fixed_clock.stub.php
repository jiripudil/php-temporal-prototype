<?php

/**
 * @generate-class-entries
 * @generate-legacy-arginfo 80100
 */

namespace Temporal\Clock
{
	final class FixedClock implements \Temporal\Clock
	{
		private \Temporal\Instant $instant;
		public function __construct(\Temporal\Instant $instant) {}
		public function getTime(): \Temporal\Instant {}
		public function setTime(\Temporal\Instant $instant): void {}
	}
}
