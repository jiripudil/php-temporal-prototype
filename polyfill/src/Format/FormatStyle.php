<?php

declare(strict_types=1);

namespace Temporal\Format;

use IntlDateFormatter;

enum FormatStyle
{
	case FULL;
	case LONG;
	case MEDIUM;
	case SHORT;

	/**
	 * @internal
	 * @return IntlDateFormatter::FULL|IntlDateFormatter::LONG|IntlDateFormatter::MEDIUM|IntlDateFormatter::SHORT
	 */
	public function toIntlConstant(): int
	{
		return match ($this) {
			self::FULL => IntlDateFormatter::FULL,
			self::LONG => IntlDateFormatter::LONG,
			self::MEDIUM => IntlDateFormatter::MEDIUM,
			self::SHORT => IntlDateFormatter::SHORT,
		};
	}
}
