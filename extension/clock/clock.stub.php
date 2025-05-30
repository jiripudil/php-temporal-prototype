<?php

/**
 * @generate-class-entries
 * @generate-legacy-arginfo 80100
 */

namespace Temporal
{
	interface Clock
	{
		public function getTime(): Instant;
	}
}
