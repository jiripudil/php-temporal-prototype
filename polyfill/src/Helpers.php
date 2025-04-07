<?php

declare(strict_types=1);

namespace Temporal;

use function assert;

/**
 * @internal
 */
final class Helpers
{
	private function __construct() {}

	public static function isLeapYear(int $year): bool
	{
		return (($year & 3) === 0) && (($year % 100) !== 0 || ($year % 400) === 0);
	}

	public static function getDaysInYear(int $year): int
	{
		return self::isLeapYear($year) ? 366 : 365;
	}

	public static function getWeeksInYear(int $year): int
	{
		$firstJanuary = LocalDate::of($year, 1, 1)->getDayOfWeek();
		$has53Weeks = $firstJanuary === 4 || ($firstJanuary === 3 && self::isLeapYear($year));
		return $has53Weeks ? 53 : 52;
	}

	public static function getDaysInMonth(int $year, int $month): int
	{
		return match ($month) {
			2 => self::isLeapYear($year) ? 29 : 28,
			4, 6, 9, 11 => 30,
			default => 31,
		};
	}

	public static function getMaxDaysInMonth(int $month): int
	{
		return match ($month) {
			2 => 29,
			4, 6, 9, 11 => 30,
			default => 31,
		};
	}

	public static function getFirstDayOfYear(int $year, int $month): int
	{
		assert($month >= 1 && $month <= 12);
		$leap = self::isLeapYear($year) ? 1 : 0;
		return match ($month) {
			1 => 1,
			2 => 32,
			3 => 60 + $leap,
			4 => 91 + $leap,
			5 => 121 + $leap,
			6 => 152 + $leap,
			7 => 182 + $leap,
			8 => 213 + $leap,
			9 => 244 + $leap,
			10 => 274 + $leap,
			11 => 305 + $leap,
			12 => 335 + $leap,
		};
	}
}
