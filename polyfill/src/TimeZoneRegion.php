<?php

declare(strict_types=1);

namespace Temporal;

use DateTimeImmutable;
use DateTimeZone;
use Exception;
use function sprintf;

final class TimeZoneRegion extends TimeZone
{
	private function __construct(
		private readonly DateTimeZone $zone,
	) {}

	public static function of(string $id): self
	{
		if ($id === '' || $id === 'Z' || $id === 'z' || $id[0] === '+' || $id[0] === '-') {
			throw new TemporalException(sprintf('Unknown time zone region "%s".', $id));
		}

		try {
			return new self(new DateTimeZone($id));
		} catch (Exception) {
			throw new TemporalException(sprintf('Unknown time zone region "%s".', $id));
		}
	}

	public static function parse(string $text): self
	{
		try {
			return self::of($text);
		} catch (TemporalException $e) {
			throw TemporalException::failedToParseInput($e);
		}
	}

	public function getId(): string
	{
		return $this->zone->getName();
	}

	public function getOffset(Instant $instant): int
	{
		$dateTime = new DateTimeImmutable('@' . $instant->getEpochSecond(), new DateTimeZone('UTC'));
		return $this->zone->getOffset($dateTime);
	}

	public function toDateTimeZone(): DateTimeZone
	{
		return clone $this->zone;
	}
}
