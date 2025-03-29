<?php

declare(strict_types=1);

namespace Temporal;

use DateTimeImmutable;
use DateTimeInterface;
use JsonSerializable;
use Stringable;
use Temporal\Format\DateTimeFormatter;

final class LocalTime implements JsonSerializable, Stringable
{
	private function __construct() {}

	public static function of(int $hour, int $minute, int $second = 0, int $nano = 0): self {}

	public static function ofSecondOfDay(int $secondOfDay): self {}

	public static function now(TimeZone $timeZone, Clock|null $clock = null): self {}

	public static function parse(string $text): self {}

	public static function midnight(): self {}

	public static function noon(): self {}

	public static function min(): self {}

	public static function max(): self {}

	public function getHour(): int {}

	public function withHour(int $hour): self {}

	public function getMinute(): int {}

	public function withMinute(int $minute): self {}

	public function getSecond(): int {}

	public function withSecond(int $second): self {}

	public function getNano(): int {}

	public function withNano(int $nano): self {}

	public function getSecondOfDay(): int {}

	public function plus(Duration $duration): self {}

	public function plusHours(int $hours): self {}

	public function plusMinutes(int $minutes): self {}

	public function plusSeconds(int $seconds): self {}

	public function plusNanos(int $nanos): self {}

	public function minus(Duration $duration): self {}

	public function minusHours(int $hours): self {}

	public function minusMinutes(int $minutes): self {}

	public function minusSeconds(int $seconds): self {}

	public function minusNanos(int $nanos): self {}

	public function atDate(LocalDate $date): LocalDateTime {}

	public function compareTo(self $other): int {}

	public function isEqualTo(self $other): bool {}

	public function isBefore(self $other): bool {}

	public function isBeforeOrEqualTo(self $other): bool {}

	public function isAfter(self $other): bool {}

	public function isAfterOrEqualTo(self $other): bool {}

	public function toDateTime(): DateTimeImmutable {}

	public static function fromDateTime(DateTimeInterface $dateTime): self {}

	public function toISOString(): string {}

	public function format(string $localizedPattern, string|null $locale = null): string {}

	public function formatWith(DateTimeFormatter $formatter): string {}

	public function jsonSerialize(): string {}

	public function __toString(): string {}
}
