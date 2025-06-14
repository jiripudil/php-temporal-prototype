<?php

/**
 * @generate-class-entries
 * @generate-legacy-arginfo 80100
 */

namespace Temporal
{
	class TemporalException extends \Exception {}
}

namespace Temporal\Exception
{
	final class DateTimeConversionException extends \Temporal\TemporalException {}
	final class FormattingException extends \Temporal\TemporalException {}
	final class ParsingException extends \Temporal\TemporalException {}
	final class ValueOutOfRangeException extends \Temporal\TemporalException {}
	final class UnknownTimeZoneException extends \Temporal\TemporalException {}
}
