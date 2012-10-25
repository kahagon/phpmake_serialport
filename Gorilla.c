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

#include "php_Gorilla.h"

#if HAVE_GORILLA

/* {{{ Class definitions */

/* {{{ Class SerialPort */

static zend_class_entry * SerialPort_ce_ptr = NULL;

/* {{{ Methods */


/* {{{ proto object __construct(string dev)
   */
PHP_METHOD(SerialPort, __construct)
{
    zend_class_entry * _this_ce;
    zval * _this_zval;

    const char * dev = NULL;
    int dev_len = 0;



    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &dev, &dev_len) == FAILURE) {
        return;
    }

    _this_zval = getThis();
    _this_ce = Z_OBJCE_P(_this_zval);


    PROP_SET_STRINGL(_device, dev, dev_len);

    return_value_ptr = &_this_zval;
}
/* }}} __construct */



/* {{{ proto object open()
   */
PHP_METHOD(SerialPort, open)
{
    zend_class_entry * _this_ce;
    zval * _this_zval = NULL;
    php_stream *stream;
    zval *_stream;

    if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, SerialPort_ce_ptr) == FAILURE) {
        return;
    }

    _this_ce = Z_OBJCE_P(_this_zval);

    SerialPort_open_impl(_this_ce, _this_zval, PROP_GET_STRING(_device));
    
    return_value_ptr = &_this_ce;
}
/* }}} open */



/* {{{ proto bool close()
   */
PHP_METHOD(SerialPort, close)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, SerialPort_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	php_error(E_WARNING, "close: not yet implemented"); RETURN_FALSE;

	RETURN_FALSE;
}
/* }}} close */



/* {{{ proto bool isOpen()
   */
PHP_METHOD(SerialPort, isOpen)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, SerialPort_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	php_error(E_WARNING, "isOpen: not yet implemented"); RETURN_FALSE;

	RETURN_FALSE;
}
/* }}} isOpen */


/* {{{ proto string read(int length)
   */
PHP_METHOD(SerialPort, read)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	long length = 0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &_this_zval, SerialPort_ce_ptr, &length) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	php_error(E_WARNING, "read: not yet implemented"); RETURN_FALSE;

	RETURN_STRINGL("", 0, 1);
}
/* }}} read */


/* {{{ proto int write(string data)
   */
PHP_METHOD(SerialPort, write)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	const char * data = NULL;
	int data_len = 0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os", &_this_zval, SerialPort_ce_ptr, &data, &data_len) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	php_error(E_WARNING, "write: not yet implemented"); RETURN_FALSE;

	RETURN_LONG(0);
}
/* }}} write */


/* {{{ proto int getBaudRate()
   */
PHP_METHOD(SerialPort, getBaudRate)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, SerialPort_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	php_error(E_WARNING, "getBaudRate: not yet implemented"); RETURN_FALSE;

	RETURN_LONG(0);
}
/* }}} getBaudRate */



/* {{{ proto object setBaudRate(int baudRate)
   */
PHP_METHOD(SerialPort, setBaudRate)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	long baudRate = 0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &_this_zval, SerialPort_ce_ptr, &baudRate) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	php_error(E_WARNING, "setBaudRate: not yet implemented"); RETURN_FALSE;

	object_init(return_value);
}
/* }}} setBaudRate */



/* {{{ proto int getCharSize()
   */
PHP_METHOD(SerialPort, getCharSize)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, SerialPort_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	php_error(E_WARNING, "getCharSize: not yet implemented"); RETURN_FALSE;

	RETURN_LONG(0);
}
/* }}} getCharSize */



/* {{{ proto object setCharSize(int charSize)
   */
PHP_METHOD(SerialPort, setCharSize)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	long charSize = 0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &_this_zval, SerialPort_ce_ptr, &charSize) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	php_error(E_WARNING, "setCharSize: not yet implemented"); RETURN_FALSE;

	object_init(return_value);
}
/* }}} setCharSize */



/* {{{ proto string getFlowControl()
   */
PHP_METHOD(SerialPort, getFlowControl)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, SerialPort_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	php_error(E_WARNING, "getFlowControl: not yet implemented"); RETURN_FALSE;

	RETURN_STRINGL("", 0, 1);
}
/* }}} getFlowControl */



/* {{{ proto object setFlowControl(string flowControl)
   */
PHP_METHOD(SerialPort, setFlowControl)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	const char * flowControl = NULL;
	int flowControl_len = 0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os", &_this_zval, SerialPort_ce_ptr, &flowControl, &flowControl_len) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	php_error(E_WARNING, "setFlowControl: not yet implemented"); RETURN_FALSE;

	object_init(return_value);
}
/* }}} setFlowControl */



/* {{{ proto object getNumOfStopBits()
   */
PHP_METHOD(SerialPort, getNumOfStopBits)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, SerialPort_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	php_error(E_WARNING, "getNumOfStopBits: not yet implemented"); RETURN_FALSE;

	object_init(return_value);
}
/* }}} getNumOfStopBits */



/* {{{ proto bool setNumOfStopBits(int numOfStopBits)
   */
PHP_METHOD(SerialPort, setNumOfStopBits)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	long numOfStopBits = 0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &_this_zval, SerialPort_ce_ptr, &numOfStopBits) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	php_error(E_WARNING, "setNumOfStopBits: not yet implemented"); RETURN_FALSE;

	RETURN_FALSE;
}
/* }}} setNumOfStopBits */



/* {{{ proto string getParity()
   */
PHP_METHOD(SerialPort, getParity)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, SerialPort_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	php_error(E_WARNING, "getParity: not yet implemented"); RETURN_FALSE;

	RETURN_STRINGL("", 0, 1);
}
/* }}} getParity */



/* {{{ proto object setParity(string parity)
   */
PHP_METHOD(SerialPort, setParity)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	const char * parity = NULL;
	int parity_len = 0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os", &_this_zval, SerialPort_ce_ptr, &parity, &parity_len) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	php_error(E_WARNING, "setParity: not yet implemented"); RETURN_FALSE;

	object_init(return_value);
}
/* }}} setParity */



/* {{{ proto object setCanonical(bool canonical)
   */
PHP_METHOD(SerialPort, setCanonical)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	zend_bool canonical = 0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ob", &_this_zval, SerialPort_ce_ptr, &canonical) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	php_error(E_WARNING, "setCanonical: not yet implemented"); RETURN_FALSE;

	object_init(return_value);
}
/* }}} setCanonical */



/* {{{ proto bool isCanonical()
   */
PHP_METHOD(SerialPort, isCanonical)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, SerialPort_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	php_error(E_WARNING, "isCanonical: not yet implemented"); RETURN_FALSE;

	RETURN_FALSE;
}
/* }}} isCanonical */



/* {{{ proto int getVMin()
   */
PHP_METHOD(SerialPort, getVMin)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, SerialPort_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	php_error(E_WARNING, "getVMin: not yet implemented"); RETURN_FALSE;

	RETURN_LONG(0);
}
/* }}} getVMin */



/* {{{ proto object setVMin(int vMin)
   */
PHP_METHOD(SerialPort, setVMin)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	long vMin = 0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &_this_zval, SerialPort_ce_ptr, &vMin) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	php_error(E_WARNING, "setVMin: not yet implemented"); RETURN_FALSE;

	object_init(return_value);
}
/* }}} setVMin */



/* {{{ proto int getVTime()
   */
PHP_METHOD(SerialPort, getVTime)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, SerialPort_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	php_error(E_WARNING, "getVTime: not yet implemented"); RETURN_FALSE;

	RETURN_LONG(0);
}
/* }}} getVTime */



/* {{{ proto object setVTime(int vTime)
   */
PHP_METHOD(SerialPort, setVTime)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	long vTime = 0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &_this_zval, SerialPort_ce_ptr, &vTime) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	php_error(E_WARNING, "setVTime: not yet implemented"); RETURN_FALSE;

	object_init(return_value);
}
/* }}} setVTime */


static zend_function_entry SerialPort_methods[] = {
	PHP_ME(SerialPort, __construct, NULL, /**/ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(SerialPort, open, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, close, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, isOpen, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, read, SerialPort__read_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, write, SerialPort__write_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, getBaudRate, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, setBaudRate, SerialPort__setBaudRate_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, getCharSize, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, setCharSize, SerialPort__setCharSize_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, getFlowControl, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, setFlowControl, SerialPort__setFlowControl_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, getNumOfStopBits, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, setNumOfStopBits, SerialPort__setNumOfStopBits_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, getParity, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, setParity, SerialPort__setParity_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, setCanonical, SerialPort__setCanonical_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, isCanonical, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, getVMin, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, setVMin, SerialPort__setVMin_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, getVTime, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, setVTime, SerialPort__setVTime_args, /**/ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

/* }}} Methods */

static void class_init_SerialPort(void)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "SerialPort", SerialPort_methods);
	SerialPort_ce_ptr = zend_register_internal_class(&ce);

           /* {{{ Property registration */

            zend_declare_property_string(SerialPort_ce_ptr,
              "_device", 7, "",
              ZEND_ACC_PROTECTED TSRMLS_DC);

	zend_declare_property_null(SerialPort_ce_ptr, 
		"_stream", 7, 
		ZEND_ACC_PROTECTED TSRMLS_DC);

           /* }}} Property registration */

	/* {{{ Constant registration */

	do {
		zval *tmp, *val;
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_50", 12, 50 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_75", 12, 75 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_110", 13, 110 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_134", 13, 134 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_150", 13, 150 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_200", 13, 200 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_300", 13, 300 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_600", 13, 600 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_1200", 14, 1200 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_1800", 14, 1800 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_2400", 14, 2400 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_4800", 14, 4800 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_9600", 14, 9600 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_19200", 15, 19200 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_38400", 15, 38400 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_57600", 15, 57600 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_115200", 16, 115200 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_230400", 16, 230400 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "CHAR_SIZE_5", 11, 5 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "CHAR_SIZE_6", 11, 6 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "CHAR_SIZE_7", 11, 7 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "CHAR_SIZE_8", 11, 8 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "CHAR_SIZE_DEFAULT", 17, 8 TSRMLS_CC );
		zend_declare_class_constant_stringl(SerialPort_ce_ptr, "FLOW_CONTROL_HARD", 17, "FLOW_CONTROL_HARD", 17 TSRMLS_CC );
		zend_declare_class_constant_stringl(SerialPort_ce_ptr, "FLOW_CONTROL_SOFT", 17, "FLOW_CONTROL_SOFT", 17 TSRMLS_CC );
		zend_declare_class_constant_stringl(SerialPort_ce_ptr, "FLOW_CONTROL_NONE", 17, "FLOW_CONTROL_NONE", 17 TSRMLS_CC );
		zend_declare_class_constant_stringl(SerialPort_ce_ptr, "FLOW_CONTROL_DEFAULT", 20, "FLOW_CONTROL_NONE", 17 TSRMLS_CC );
		zend_declare_class_constant_stringl(SerialPort_ce_ptr, "PARITY_EVEN", 11, "PARITY_EVEN", 11 TSRMLS_CC );
		zend_declare_class_constant_stringl(SerialPort_ce_ptr, "PARITY_ODD", 10, "PARITY_ODD", 10 TSRMLS_CC );
		zend_declare_class_constant_stringl(SerialPort_ce_ptr, "PARITY_NONE", 11, "PARITY_NONE", 11 TSRMLS_CC );
		zend_declare_class_constant_stringl(SerialPort_ce_ptr, "PARITY_DEFAULT", 14, "PARITY_NONE", 11 TSRMLS_CC );
	} while(0);

	/* } Constant registration */

}

/* }}} Class SerialPort */

/* {{{ Class Arduino */

static zend_class_entry * Arduino_ce_ptr = NULL;

/* {{{ Methods */


/* {{{ proto object __construct(object serialPort)
   */
PHP_METHOD(Arduino, __construct)
{
    zend_class_entry * _this_ce;
    zval * _this_zval;

    zval * serialPort = NULL;



    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "o", &serialPort) == FAILURE) {
        return;
    }

    _this_zval = getThis();
    _this_ce = Z_OBJCE_P(_this_zval);

    php_error(E_WARNING, "__construct: not yet implemented"); RETURN_FALSE;

    object_init(return_value);
}
/* }}} __construct */



/* {{{ proto object output(array pinList)
   */
PHP_METHOD(Arduino, output)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	zval * pinList = NULL;
	HashTable * pinList_hash = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oa/", &_this_zval, Arduino_ce_ptr, &pinList) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);

	pinList_hash = HASH_OF(pinList);



	php_error(E_WARNING, "output: not yet implemented"); RETURN_FALSE;

	object_init(return_value);
}
/* }}} output */



/* {{{ proto bool close()
   */
PHP_METHOD(Arduino, close)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, Arduino_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	php_error(E_WARNING, "close: not yet implemented"); RETURN_FALSE;

	RETURN_FALSE;
}
/* }}} close */



/* {{{ proto object digitalWrite(int pin, int value)
   */
PHP_METHOD(Arduino, digitalWrite)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	long pin = 0;
	long value = 0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Oll", &_this_zval, Arduino_ce_ptr, &pin, &value) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	php_error(E_WARNING, "digitalWrite: not yet implemented"); RETURN_FALSE;

	object_init(return_value);
}
/* }}} digitalWrite */



/* {{{ proto object setHigh(int pin)
   */
PHP_METHOD(Arduino, setHigh)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	long pin = 0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &_this_zval, Arduino_ce_ptr, &pin) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	php_error(E_WARNING, "setHigh: not yet implemented"); RETURN_FALSE;

	object_init(return_value);
}
/* }}} setHigh */



/* {{{ proto object setLow(int pin)
   */
PHP_METHOD(Arduino, setLow)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	long pin = 0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &_this_zval, Arduino_ce_ptr, &pin) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	php_error(E_WARNING, "setLow: not yet implemented"); RETURN_FALSE;

	object_init(return_value);
}
/* }}} setLow */



/* {{{ proto int digitalRead(int pin)
   */
PHP_METHOD(Arduino, digitalRead)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	long pin = 0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &_this_zval, Arduino_ce_ptr, &pin) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	php_error(E_WARNING, "digitalRead: not yet implemented"); RETURN_FALSE;

	RETURN_LONG(0);
}
/* }}} digitalRead */



/* {{{ proto int getState(int pin)
   */
PHP_METHOD(Arduino, getState)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	long pin = 0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &_this_zval, Arduino_ce_ptr, &pin) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	php_error(E_WARNING, "getState: not yet implemented"); RETURN_FALSE;

	RETURN_LONG(0);
}
/* }}} getState */



/* {{{ proto bool isHigh(int pin)
   */
PHP_METHOD(Arduino, isHigh)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	long pin = 0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &_this_zval, Arduino_ce_ptr, &pin) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	php_error(E_WARNING, "isHigh: not yet implemented"); RETURN_FALSE;

	RETURN_FALSE;
}
/* }}} isHigh */



/* {{{ proto bool isLow(int pin)
   */
PHP_METHOD(Arduino, isLow)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;
	long pin = 0;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &_this_zval, Arduino_ce_ptr, &pin) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	php_error(E_WARNING, "isLow: not yet implemented"); RETURN_FALSE;

	RETURN_FALSE;
}
/* }}} isLow */



/* {{{ proto object turnOff()
   */
PHP_METHOD(Arduino, turnOff)
{
	zend_class_entry * _this_ce;

	zval * _this_zval = NULL;



	if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, Arduino_ce_ptr) == FAILURE) {
		return;
	}

	_this_ce = Z_OBJCE_P(_this_zval);


	php_error(E_WARNING, "turnOff: not yet implemented"); RETURN_FALSE;

	object_init(return_value);
}
/* }}} turnOff */


static zend_function_entry Arduino_methods[] = {
	PHP_ME(Arduino, __construct, NULL, /**/ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(Arduino, output, Arduino__output_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(Arduino, close, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(Arduino, digitalWrite, Arduino__digitalWrite_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(Arduino, setHigh, Arduino__setHigh_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(Arduino, setLow, Arduino__setLow_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(Arduino, digitalRead, Arduino__digitalRead_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(Arduino, getState, Arduino__getState_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(Arduino, isHigh, Arduino__isHigh_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(Arduino, isLow, Arduino__isLow_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(Arduino, turnOff, NULL, /**/ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

/* }}} Methods */

static void class_init_Arduino(void)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "Arduino", Arduino_methods);
	Arduino_ce_ptr = zend_register_internal_class(&ce);

	/* {{{ Property registration */

	zend_declare_property_null(Arduino_ce_ptr, 
		"_serialPort", 11, 
		ZEND_ACC_PROTECTED TSRMLS_DC);

	zend_declare_property_null(Arduino_ce_ptr, 
		"_pinList", 8, 
		ZEND_ACC_PROTECTED TSRMLS_DC);

	/* }}} Property registration */


	/* {{{ Constant registration */

	do {
		zval *tmp, *val;
		zend_declare_class_constant_long(Arduino_ce_ptr, "HIGH", 4, 1 TSRMLS_CC );
		zend_declare_class_constant_long(Arduino_ce_ptr, "LOW", 3, 0 TSRMLS_CC );
	} while(0);

	/* } Constant registration */

}

/* }}} Class Arduino */

/* }}} Class definitions*/

/* {{{ Gorilla_functions[] */
function_entry Gorilla_functions[] = {
	{ NULL, NULL, NULL }
};
/* }}} */


/* {{{ Gorilla_module_entry
 */
zend_module_entry Gorilla_module_entry = {
	STANDARD_MODULE_HEADER,
	"Gorilla",
	Gorilla_functions,
	PHP_MINIT(Gorilla),     /* Replace with NULL if there is nothing to do at php startup   */ 
	PHP_MSHUTDOWN(Gorilla), /* Replace with NULL if there is nothing to do at php shutdown  */
	PHP_RINIT(Gorilla),     /* Replace with NULL if there is nothing to do at request start */
	PHP_RSHUTDOWN(Gorilla), /* Replace with NULL if there is nothing to do at request end   */
	PHP_MINFO(Gorilla),
	PHP_GORILLA_VERSION, 
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_GORILLA
ZEND_GET_MODULE(Gorilla)
#endif


/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(Gorilla)
{
	class_init_SerialPort();
	class_init_Arduino();

	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_MSHUTDOWN_FUNCTION */
PHP_MSHUTDOWN_FUNCTION(Gorilla)
{

	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(Gorilla)
{
	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_RSHUTDOWN_FUNCTION */
PHP_RSHUTDOWN_FUNCTION(Gorilla)
{
	/* add your stuff here */

	return SUCCESS;
}
/* }}} */


/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(Gorilla)
{
	php_printf("API for talking to serialport and arduino\n");
	php_info_print_table_start();
	php_info_print_table_row(2, "Version",PHP_GORILLA_VERSION " (alpha)");
	php_info_print_table_row(2, "Released", "2012-10-25");
	php_info_print_table_row(2, "CVS Revision", "$Id: $");
	php_info_print_table_row(2, "Authors", "Keng-ichi Ahagon 'k.ahagon@n-3.so' (lead)\n");
	php_info_print_table_end();
	/* add your stuff here */

}
/* }}} */

#endif /* HAVE_GORILLA */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
