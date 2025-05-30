<?php

/**
 * @generate-class-entries
 * @generate-legacy-arginfo 80100
 */

namespace Temporal\Format
{
	final class DateTimeFormatter
	{
		private function __construct() {}
		public static function ofPattern(string $pattern, string|null $locale = null): DateTimeFormatter {}
		public static function ofLocalizedPattern(string $localizedPattern, string|null $locale = null): DateTimeFormatter {}
		public static function ofDate(FormatStyle $style, string|null $locale = null): DateTimeFormatter {}
		public static function ofTime(FormatStyle $style, string|null $locale = null): DateTimeFormatter {}
		public static function ofDateTime(FormatStyle $dateStyle, FormatStyle $timeStyle, string|null $locale = null): DateTimeFormatter {}
		public function formatLocalTime(\Temporal\LocalTime $value): string {}
		public function formatLocalDate(\Temporal\LocalDate $value): string {}
		public function formatLocalDateTime(\Temporal\LocalDateTime $value): string {}
		public function formatZonedDateTime(\Temporal\ZonedDateTime $value): string {}
	}
}
