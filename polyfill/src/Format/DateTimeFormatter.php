<?php

declare(strict_types=1);

namespace Temporal\Format;

use Temporal\LocalDate;
use Temporal\LocalDateTime;
use Temporal\LocalTime;
use Temporal\ZonedDateTime;

final class DateTimeFormatter
{
	private function __construct() {}

	public static function ofPattern(string $pattern, string|null $locale = null): self {}

	public static function ofLocalizedPattern(string $localizedPattern, string|null $locale = null): self {}

	public static function ofDate(FormatStyle $dateStyle, string|null $locale = null): self {}

	public static function ofTime(FormatStyle $timeStyle, string|null $locale = null): self {}

	public static function ofDateTime(FormatStyle $dateStyle, FormatStyle $timeStyle, string|null $locale = null): self {}

	public function formatLocalTime(LocalTime $value): string {}

	public function formatLocalDate(LocalDate $value): string {}

	public function formatLocalDateTime(LocalDateTime $value): string {}

	public function formatZonedDateTime(ZonedDateTime $value): string {}
}
