<?php

declare(strict_types=1);

namespace Temporal;

final class TimeZoneOffset extends TimeZone
{
	private function __construct() {}

	public static function of(int $hours, int $minutes = 0, int $seconds = 0): self {}

	public static function ofTotalSeconds(int $totalSeconds): self {}

	public static function utc(): self {}

	public static function parse(string $text): self {}

	public function getTotalSeconds(): int {}

	public function getId(): string {}

	public function getOffset(Instant $instant): int {}
}
