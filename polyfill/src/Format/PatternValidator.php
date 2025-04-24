<?php

declare(strict_types=1);

namespace Temporal\Format;

use Temporal\LocalDate;
use Temporal\LocalDateTime;
use Temporal\LocalTime;
use Temporal\TemporalException;
use Temporal\ZonedDateTime;
use function array_key_exists;
use function preg_match;
use function str_split;

/**
 * @internal
 */
final class PatternValidator
{
	private const FIELD_DATE = 1 << 0;
	private const FIELD_TIME = 1 << 1;
	private const FIELD_TIMEZONE = 1 << 2;

	private const FIELDS = [
		'G' => self::FIELD_DATE,
		'y' => self::FIELD_DATE,
		'Y' => self::FIELD_DATE,
		'u' => self::FIELD_DATE,
		'U' => self::FIELD_DATE,
		'r' => self::FIELD_DATE,
		'Q' => self::FIELD_DATE,
		'q' => self::FIELD_DATE,
		'M' => self::FIELD_DATE,
		'L' => self::FIELD_DATE,
		'l' => self::FIELD_DATE,
		'w' => self::FIELD_DATE,
		'W' => self::FIELD_DATE,
		'd' => self::FIELD_DATE,
		'D' => self::FIELD_DATE,
		'F' => self::FIELD_DATE,
		'g' => self::FIELD_DATE,
		'E' => self::FIELD_DATE,
		'e' => self::FIELD_DATE,
		'c' => self::FIELD_DATE,

		'a' => self::FIELD_TIME,
		'b' => self::FIELD_TIME,
		'B' => self::FIELD_TIME,
		'h' => self::FIELD_TIME,
		'H' => self::FIELD_TIME,
		'K' => self::FIELD_TIME,
		'k' => self::FIELD_TIME,
		'm' => self::FIELD_TIME,
		's' => self::FIELD_TIME,
		'S' => self::FIELD_TIME,
		'A' => self::FIELD_TIME,

		'z' => self::FIELD_TIMEZONE,
		'Z' => self::FIELD_TIMEZONE,
		'O' => self::FIELD_TIMEZONE,
		'v' => self::FIELD_TIMEZONE,
		'V' => self::FIELD_TIMEZONE,
		'X' => self::FIELD_TIMEZONE,
		'x' => self::FIELD_TIMEZONE,
	];

	private function __construct() {}

	public static function validatePattern(string $pattern, LocalDate|LocalTime|LocalDateTime|ZonedDateTime $value): void
	{
		$mask = self::resolveMask($value);

		$escaped = false;
		foreach (str_split($pattern) as $char) {
			if ($char === '\'') {
				$escaped = !$escaped;
				continue;
			}

			if ($escaped) {
				continue;
			}

			if (preg_match('/^\p{L}$/u', $char) !== 1) {
				continue;
			}

			if ( ! array_key_exists($char, self::FIELDS)) {
				throw TemporalException::failedToFormatValue();
			}

			if (($mask & self::FIELDS[$char]) === 0) {
				throw TemporalException::failedToFormatValue();
			}
		}
	}

	private static function resolveMask(LocalDate|LocalTime|LocalDateTime|ZonedDateTime $value): int
	{
		if ($value instanceof LocalDate) {
			return self::FIELD_DATE;
		}

		if ($value instanceof LocalTime) {
			return self::FIELD_TIME;
		}

		if ($value instanceof LocalDateTime) {
			return self::FIELD_DATE | self::FIELD_TIME;
		}

		return self::FIELD_DATE | self::FIELD_TIME | self::FIELD_TIMEZONE;
	}
}
