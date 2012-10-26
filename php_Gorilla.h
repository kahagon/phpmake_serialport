/*
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.0 of the PHP license,       |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_0.txt.                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors: Keng-ichi Ahagon <k.ahagon@n-3.so>                          |
   +----------------------------------------------------------------------+
*/

/* $ Id: $ */ 

#ifndef PHP_GORILLA_H
#define PHP_GORILLA_H

#ifdef  __cplusplus
extern "C" {
#endif

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>

#ifdef HAVE_GORILLA
#define PHP_GORILLA_VERSION "0.0.1"


#include <php_ini.h>
#include <SAPI.h>
#include <ext/standard/info.h>
#include <Zend/zend_extensions.h>
#include <Zend/zend_exceptions.h>
#ifdef  __cplusplus
} // extern "C" 
#endif
#ifdef  __cplusplus
extern "C" {
#endif

extern zend_module_entry Gorilla_module_entry;
#define phpext_Gorilla_ptr &Gorilla_module_entry

#ifdef PHP_WIN32
#define PHP_GORILLA_API __declspec(dllexport)
#else
#define PHP_GORILLA_API
#endif

PHP_MINIT_FUNCTION(Gorilla);
PHP_MSHUTDOWN_FUNCTION(Gorilla);
PHP_RINIT_FUNCTION(Gorilla);
PHP_RSHUTDOWN_FUNCTION(Gorilla);
PHP_MINFO_FUNCTION(Gorilla);

#ifdef ZTS
#include "TSRM.h"
#endif

#define FREE_RESOURCE(resource) zend_list_delete(Z_LVAL_P(resource))

#define PROP_GET_LONG(name)    Z_LVAL_P(zend_read_property(_this_ce, _this_zval, #name, strlen(#name), 1 TSRMLS_CC))
#define PROP_SET_LONG(name, l) zend_update_property_long(_this_ce, _this_zval, #name, strlen(#name), l TSRMLS_CC)

#define PROP_GET_DOUBLE(name)    Z_DVAL_P(zend_read_property(_this_ce, _this_zval, #name, strlen(#name), 1 TSRMLS_CC))
#define PROP_SET_DOUBLE(name, d) zend_update_property_double(_this_ce, _this_zval, #name, strlen(#name), d TSRMLS_CC)

#define PROP_GET_STRING(name)    Z_STRVAL_P(zend_read_property(_this_ce, _this_zval, #name, strlen(#name), 1 TSRMLS_CC))
#define PROP_GET_STRLEN(name)    Z_STRLEN_P(zend_read_property(_this_ce, _this_zval, #name, strlen(#name), 1 TSRMLS_CC))
#define PROP_SET_STRING(name, s) zend_update_property_string(_this_ce, _this_zval, #name, strlen(#name), s TSRMLS_CC)
#define PROP_SET_STRINGL(name, s, l) zend_update_property_stringl(_this_ce, _this_zval, #name, strlen(#name), s, l TSRMLS_CC)


#define GORILLA_METHOD_PARAMETERS zend_class_entry * _this_ce, zval * _this_zval, INTERNAL_FUNCTION_PARAMETERS
#define GORILLA_METHOD_PARAM_PASSTHRU _this_ce, _this_zval, INTERNAL_FUNCTION_PARAM_PASSTHRU

#define BAUD_RATE_50 50
#define BAUD_RATE_75 75
#define BAUD_RATE_110 110
#define BAUD_RATE_134 134
#define BAUD_RATE_150 150
#define BAUD_RATE_200 200
#define BAUD_RATE_300 300
#define BAUD_RATE_600 600
#define BAUD_RATE_1200 1200
#define BAUD_RATE_1800 1800
#define BAUD_RATE_2400 2400
#define BAUD_RATE_4800 4800
#define BAUD_RATE_9600 9600
#define BAUD_RATE_19200 19200
#define BAUD_RATE_38400 38400
#define BAUD_RATE_57600 57600
#define BAUD_RATE_115200 115200
#define BAUD_RATE_230400 230400
#define CHAR_SIZE_5 5
#define CHAR_SIZE_6 6
#define CHAR_SIZE_7 7
#define CHAR_SIZE_8 8
#define CHAR_SIZE_DEFAULT CHAR_SIZE_8
#define FLOW_CONTROL_HARD "FLOW_CONTROL_HARD"
#define FLOW_CONTROL_SOFT "FLOW_CONTROL_SOFT"
#define FLOW_CONTROL_NONE "FLOW_CONTROL_NONE"
#define FLOW_CONTROL_DEFAULT "FLOW_CONTROL_DEFAULT"
#define PARITY_EVEN "PARITY_EVEN"
#define PARITY_ODD "PARITY_ODD"
#define PARITY_NONE "PARITY_NONE"
#define PARITY_DEFAULT "PARITY_DEFAULT"

PHPAPI void SerialPort_open_impl(const char *device, GORILLA_METHOD_PARAMETERS);
PHPAPI long SerialPort_getBaudRate_impl(GORILLA_METHOD_PARAMETERS);

PHP_METHOD(SerialPort, __construct);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(SerialPort____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define SerialPort____construct_args NULL
#endif

PHP_METHOD(SerialPort, open);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(SerialPort__open_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define SerialPort__open_args NULL
#endif

PHP_METHOD(SerialPort, close);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(SerialPort__close_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define SerialPort__close_args NULL
#endif

PHP_METHOD(SerialPort, isOpen);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(SerialPort__isOpen_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define SerialPort__isOpen_args NULL
#endif

PHP_METHOD(SerialPort, read);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(SerialPort__read_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, length)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define SerialPort__read_args NULL
#endif

PHP_METHOD(SerialPort, write);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(SerialPort__write_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, data)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define SerialPort__write_args NULL
#endif
        
PHP_METHOD(SerialPort, getBaudRate);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(SerialPort__getBaudRate_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define SerialPort__getBaudRate_args NULL
#endif

PHP_METHOD(SerialPort, setBaudRate);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(SerialPort__setBaudRate_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, baudRate)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define SerialPort__setBaudRate_args NULL
#endif

PHP_METHOD(SerialPort, getCharSize);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(SerialPort__getCharSize_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define SerialPort__getCharSize_args NULL
#endif

PHP_METHOD(SerialPort, setCharSize);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(SerialPort__setCharSize_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, charSize)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define SerialPort__setCharSize_args NULL
#endif

PHP_METHOD(SerialPort, getFlowControl);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(SerialPort__getFlowControl_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define SerialPort__getFlowControl_args NULL
#endif

PHP_METHOD(SerialPort, setFlowControl);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(SerialPort__setFlowControl_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, flowControl)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define SerialPort__setFlowControl_args NULL
#endif

PHP_METHOD(SerialPort, getNumOfStopBits);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(SerialPort__getNumOfStopBits_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define SerialPort__getNumOfStopBits_args NULL
#endif

PHP_METHOD(SerialPort, setNumOfStopBits);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(SerialPort__setNumOfStopBits_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, numOfStopBits)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define SerialPort__setNumOfStopBits_args NULL
#endif

PHP_METHOD(SerialPort, getParity);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(SerialPort__getParity_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define SerialPort__getParity_args NULL
#endif

PHP_METHOD(SerialPort, setParity);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(SerialPort__setParity_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, parity)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define SerialPort__setParity_args NULL
#endif

PHP_METHOD(SerialPort, setCanonical);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(SerialPort__setCanonical_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, canonical)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define SerialPort__setCanonical_args NULL
#endif

PHP_METHOD(SerialPort, isCanonical);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(SerialPort__isCanonical_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define SerialPort__isCanonical_args NULL
#endif

PHP_METHOD(SerialPort, getVMin);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(SerialPort__getVMin_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define SerialPort__getVMin_args NULL
#endif

PHP_METHOD(SerialPort, setVMin);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(SerialPort__setVMin_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, vMin)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define SerialPort__setVMin_args NULL
#endif

PHP_METHOD(SerialPort, getVTime);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(SerialPort__getVTime_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define SerialPort__getVTime_args NULL
#endif

PHP_METHOD(SerialPort, setVTime);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(SerialPort__setVTime_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, vTime)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define SerialPort__setVTime_args NULL
#endif

PHP_METHOD(Arduino, __construct);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(Arduino____construct_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define Arduino____construct_args NULL
#endif

PHP_METHOD(Arduino, output);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(Arduino__output_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
#if (PHP_MINOR_VERSION > 0)
  ZEND_ARG_ARRAY_INFO(0, pinList, 1)
#else
  ZEND_ARG_INFO(0, pinList)
#endif
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define Arduino__output_args NULL
#endif

PHP_METHOD(Arduino, close);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(Arduino__close_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define Arduino__close_args NULL
#endif

PHP_METHOD(Arduino, digitalWrite);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(Arduino__digitalWrite_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 2)
  ZEND_ARG_INFO(0, pin)
  ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define Arduino__digitalWrite_args NULL
#endif

PHP_METHOD(Arduino, setHigh);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(Arduino__setHigh_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, pin)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define Arduino__setHigh_args NULL
#endif

PHP_METHOD(Arduino, setLow);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(Arduino__setLow_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, pin)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define Arduino__setLow_args NULL
#endif

PHP_METHOD(Arduino, digitalRead);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(Arduino__digitalRead_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, pin)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define Arduino__digitalRead_args NULL
#endif

PHP_METHOD(Arduino, getState);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(Arduino__getState_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, pin)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define Arduino__getState_args NULL
#endif

PHP_METHOD(Arduino, isHigh);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(Arduino__isHigh_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, pin)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define Arduino__isHigh_args NULL
#endif

PHP_METHOD(Arduino, isLow);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(Arduino__isLow_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 1)
  ZEND_ARG_INFO(0, pin)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define Arduino__isLow_args NULL
#endif

PHP_METHOD(Arduino, turnOff);
#if (PHP_MAJOR_VERSION >= 5)
ZEND_BEGIN_ARG_INFO_EX(Arduino__turnOff_args, ZEND_SEND_BY_VAL, ZEND_RETURN_VALUE, 0)
ZEND_END_ARG_INFO()
#else /* PHP 4.x */
#define Arduino__turnOff_args NULL
#endif

#ifdef  __cplusplus
} // extern "C" 
#endif

#endif /* PHP_HAVE_GORILLA */

#endif /* PHP_GORILLA_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
