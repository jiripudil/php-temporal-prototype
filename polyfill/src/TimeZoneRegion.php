<?php

declare(strict_types=1);

namespace Temporal;

use DateTimeImmutable;
use DateTimeZone;
use Exception;
use Temporal\Exception\ParsingException;
use Temporal\Exception\UnknownTimeZoneException;
use function sprintf;

final class TimeZoneRegion extends TimeZone
{
	private function __construct(
		private readonly DateTimeZone $zone,
	) {}

	public static function of(string $id): self
	{
		if ($id === '' || $id === 'Z' || $id === 'z' || $id[0] === '+' || $id[0] === '-') {
			throw UnknownTimeZoneException::of($id);
		}

		try {
			return new self(new DateTimeZone($id));
		} catch (Exception) {
			throw UnknownTimeZoneException::of($id);
		}
	}

	public static function fromIsoString(string $text): self
	{
		try {
			return self::of($text);
		} catch (UnknownTimeZoneException $e) {
			throw ParsingException::unknownTimeZone($text, $e);
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

	public function __serialize(): array
	{
		return [
			'id' => $this->getId(),
		];
	}

	/**
	 * @param array{id: string} $data
	 */
	public function __unserialize(array $data): void
	{
		$this->zone = new DateTimeZone($data['id']);
	}
}
