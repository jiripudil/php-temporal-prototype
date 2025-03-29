<?php

declare(strict_types=1);

namespace Temporal;

use JsonSerializable;
use Stringable;

abstract class TimeZone implements JsonSerializable, Stringable
{
	public static function parse(string $text): self {}

	public static function utc(): self {}

	abstract public function getId(): string;

	abstract public function getOffset(Instant $instant): int;

	public function isEqualTo(self $other): bool {}

	public function jsonSerialize(): string {}

	public function __toString(): string {}
}
