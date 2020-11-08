/*
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors: Stanislav Malyshev <stas@zend.com>                          |
   +----------------------------------------------------------------------+
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <unicode/utypes.h>
#include <unicode/unum.h>
#include <unicode/ustring.h>

#include "php_intl.h"
#include "formatter_class.h"
#include "formatter_format.h"

/* {{{ formatter_register_constants
 * Register constants common for the both (OO and procedural)
 * APIs.
 */
void formatter_register_constants( INIT_FUNC_ARGS )
{
	if( NumberFormatter_ce_ptr == NULL) {
		zend_error(E_ERROR, "NumberFormatter class not defined");
	}

	#define FORMATTER_EXPOSE_CONST(x) REGISTER_LONG_CONSTANT(#x, x, CONST_PERSISTENT | CONST_CS)
	#define FORMATTER_EXPOSE_CLASS_CONST(x) zend_declare_class_constant_long( NumberFormatter_ce_ptr, ZEND_STRS( #x ) - 1, UNUM_##x );
	#define FORMATTER_EXPOSE_CUSTOM_CLASS_CONST(name, value) zend_declare_class_constant_long( NumberFormatter_ce_ptr, ZEND_STRS( name ) - 1, value );

	/* UNumberFormatStyle constants */
	FORMATTER_EXPOSE_CLASS_CONST( PATTERN_DECIMAL );
	FORMATTER_EXPOSE_CLASS_CONST( DECIMAL );
	FORMATTER_EXPOSE_CLASS_CONST( CURRENCY );
	FORMATTER_EXPOSE_CLASS_CONST( PERCENT );
	FORMATTER_EXPOSE_CLASS_CONST( SCIENTIFIC );
	FORMATTER_EXPOSE_CLASS_CONST( SPELLOUT );
	FORMATTER_EXPOSE_CLASS_CONST( ORDINAL );
	FORMATTER_EXPOSE_CLASS_CONST( DURATION );
	FORMATTER_EXPOSE_CLASS_CONST( PATTERN_RULEBASED );
	FORMATTER_EXPOSE_CLASS_CONST( IGNORE );
#if U_ICU_VERSION_MAJOR_NUM >= 53
	FORMATTER_EXPOSE_CLASS_CONST( CURRENCY_ACCOUNTING );
#endif
	FORMATTER_EXPOSE_CUSTOM_CLASS_CONST( "DEFAULT_STYLE",  UNUM_DEFAULT );

	/* UNumberFormatRoundingMode */
	FORMATTER_EXPOSE_CLASS_CONST( ROUND_CEILING );
	FORMATTER_EXPOSE_CLASS_CONST( ROUND_FLOOR );
	FORMATTER_EXPOSE_CLASS_CONST( ROUND_DOWN );
	FORMATTER_EXPOSE_CLASS_CONST( ROUND_UP );
	FORMATTER_EXPOSE_CLASS_CONST( ROUND_HALFEVEN );
	FORMATTER_EXPOSE_CLASS_CONST( ROUND_HALFDOWN );
	FORMATTER_EXPOSE_CLASS_CONST( ROUND_HALFUP );

	/* UNumberFormatPadPosition */
	FORMATTER_EXPOSE_CLASS_CONST( PAD_BEFORE_PREFIX );
	FORMATTER_EXPOSE_CLASS_CONST( PAD_AFTER_PREFIX );
	FORMATTER_EXPOSE_CLASS_CONST( PAD_BEFORE_SUFFIX );
	FORMATTER_EXPOSE_CLASS_CONST( PAD_AFTER_SUFFIX );

	/* UNumberFormatAttribute */
	FORMATTER_EXPOSE_CLASS_CONST( PARSE_INT_ONLY );
	FORMATTER_EXPOSE_CLASS_CONST( GROUPING_USED );
	FORMATTER_EXPOSE_CLASS_CONST( DECIMAL_ALWAYS_SHOWN );
	FORMATTER_EXPOSE_CLASS_CONST( MAX_INTEGER_DIGITS );
	FORMATTER_EXPOSE_CLASS_CONST( MIN_INTEGER_DIGITS );
	FORMATTER_EXPOSE_CLASS_CONST( INTEGER_DIGITS );
	FORMATTER_EXPOSE_CLASS_CONST( MAX_FRACTION_DIGITS );
	FORMATTER_EXPOSE_CLASS_CONST( MIN_FRACTION_DIGITS );
	FORMATTER_EXPOSE_CLASS_CONST( FRACTION_DIGITS );
	FORMATTER_EXPOSE_CLASS_CONST( MULTIPLIER );
	FORMATTER_EXPOSE_CLASS_CONST( GROUPING_SIZE );
	FORMATTER_EXPOSE_CLASS_CONST( ROUNDING_MODE );
	FORMATTER_EXPOSE_CLASS_CONST( ROUNDING_INCREMENT );
	FORMATTER_EXPOSE_CLASS_CONST( FORMAT_WIDTH );
	FORMATTER_EXPOSE_CLASS_CONST( PADDING_POSITION );
	FORMATTER_EXPOSE_CLASS_CONST( SECONDARY_GROUPING_SIZE );
	FORMATTER_EXPOSE_CLASS_CONST( SIGNIFICANT_DIGITS_USED );
	FORMATTER_EXPOSE_CLASS_CONST( MIN_SIGNIFICANT_DIGITS );
	FORMATTER_EXPOSE_CLASS_CONST( MAX_SIGNIFICANT_DIGITS );
	FORMATTER_EXPOSE_CLASS_CONST( LENIENT_PARSE );

	/* UNumberFormatTextAttribute */
	FORMATTER_EXPOSE_CLASS_CONST( POSITIVE_PREFIX );
	FORMATTER_EXPOSE_CLASS_CONST( POSITIVE_SUFFIX );
	FORMATTER_EXPOSE_CLASS_CONST( NEGATIVE_PREFIX );
	FORMATTER_EXPOSE_CLASS_CONST( NEGATIVE_SUFFIX );
	FORMATTER_EXPOSE_CLASS_CONST( PADDING_CHARACTER );
	FORMATTER_EXPOSE_CLASS_CONST( CURRENCY_CODE );
	FORMATTER_EXPOSE_CLASS_CONST( DEFAULT_RULESET );
	FORMATTER_EXPOSE_CLASS_CONST( PUBLIC_RULESETS );

	/* UNumberFormatSymbol */
	FORMATTER_EXPOSE_CLASS_CONST( DECIMAL_SEPARATOR_SYMBOL );
	FORMATTER_EXPOSE_CLASS_CONST( GROUPING_SEPARATOR_SYMBOL );
	FORMATTER_EXPOSE_CLASS_CONST( PATTERN_SEPARATOR_SYMBOL );
	FORMATTER_EXPOSE_CLASS_CONST( PERCENT_SYMBOL );
	FORMATTER_EXPOSE_CLASS_CONST( ZERO_DIGIT_SYMBOL );
	FORMATTER_EXPOSE_CLASS_CONST( DIGIT_SYMBOL );
	FORMATTER_EXPOSE_CLASS_CONST( MINUS_SIGN_SYMBOL );
	FORMATTER_EXPOSE_CLASS_CONST( PLUS_SIGN_SYMBOL );
	FORMATTER_EXPOSE_CLASS_CONST( CURRENCY_SYMBOL );
	FORMATTER_EXPOSE_CLASS_CONST( INTL_CURRENCY_SYMBOL );
	FORMATTER_EXPOSE_CLASS_CONST( MONETARY_SEPARATOR_SYMBOL );
	FORMATTER_EXPOSE_CLASS_CONST( EXPONENTIAL_SYMBOL );
	FORMATTER_EXPOSE_CLASS_CONST( PERMILL_SYMBOL );
	FORMATTER_EXPOSE_CLASS_CONST( PAD_ESCAPE_SYMBOL );
	FORMATTER_EXPOSE_CLASS_CONST( INFINITY_SYMBOL );
	FORMATTER_EXPOSE_CLASS_CONST( NAN_SYMBOL );
	FORMATTER_EXPOSE_CLASS_CONST( SIGNIFICANT_DIGIT_SYMBOL );
	FORMATTER_EXPOSE_CLASS_CONST( MONETARY_GROUPING_SEPARATOR_SYMBOL );

	FORMATTER_EXPOSE_CUSTOM_CLASS_CONST( "TYPE_DEFAULT", FORMAT_TYPE_DEFAULT );
	FORMATTER_EXPOSE_CUSTOM_CLASS_CONST( "TYPE_INT32", FORMAT_TYPE_INT32 );
	FORMATTER_EXPOSE_CUSTOM_CLASS_CONST( "TYPE_INT64", FORMAT_TYPE_INT64 );
	FORMATTER_EXPOSE_CUSTOM_CLASS_CONST( "TYPE_DOUBLE", FORMAT_TYPE_DOUBLE );
	FORMATTER_EXPOSE_CUSTOM_CLASS_CONST( "TYPE_CURRENCY", FORMAT_TYPE_CURRENCY );

	#undef FORMATTER_EXPOSE_CUSTOM_CLASS_CONST
	#undef FORMATTER_EXPOSE_CLASS_CONST
	#undef FORMATTER_EXPOSE_CONST
}
/* }}} */
