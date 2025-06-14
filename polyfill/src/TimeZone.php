<?php

declare(strict_types=1);

namespace Temporal;

use DateTimeZone;
use JsonSerializable;
use Stringable;
use Temporal\Exception\ParsingException;

abstract class TimeZone implements JsonSerializable, Stringable
{
	public static function fromIsoString(string $text): self
	{
		if ($text === 'Z' || $text === 'z') {
			return TimeZoneOffset::utc();
		}

		if ($text === '') {
			throw ParsingException::invalidIsoString($text);
		}

		if ($text[0] === '+' || $text[0] === '-') {
			return TimeZoneOffset::fromIsoString($text);
		}

		return TimeZoneRegion::fromIsoString($text);
	}

	public static function utc(): self
	{
		return TimeZoneOffset::utc();
	}

	abstract public function getId(): string;

	abstract public function getOffset(Instant $instant): int;

	public function isEqualTo(self $other): bool
	{
		return $this->getId() === $other->getId();
	}

	abstract public function toDateTimeZone(): DateTimeZone;

	public static function fromDateTimeZone(DateTimeZone $zone): self
	{
		return self::fromIsoString($zone->getName());
	}

	public function jsonSerialize(): string
	{
		return $this->getId();
	}

	public function __toString(): string
	{
		return $this->getId();
	}
}
