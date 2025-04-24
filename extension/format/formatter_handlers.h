#ifndef TEMPORAL_FORMATTER_HANDLERS_H
#define TEMPORAL_FORMATTER_HANDLERS_H

#include <php.h>

extern zend_object_handlers php_temporal_formatter_handlers;

void php_temporal_register_formatter_handlers();

#endif // TEMPORAL_FORMATTER_HANDLERS_H