<?php

declare(strict_types=1);

namespace Temporal;

final class TimeZoneRegion extends TimeZone
{
	private function __construct() {}

	public static function of(string $id): self {}

	public static function parse(string $text): self {}

	public function getId(): string {}

	public function getOffset(Instant $instant): int {}
}
