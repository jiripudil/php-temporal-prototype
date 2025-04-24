<?php

/** @generate-class-entries */

namespace Temporal
{
	interface Clock
	{
		public function getTime(): Instant;
	}
}
