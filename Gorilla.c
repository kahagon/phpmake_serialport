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

/* {{{ Resource destructors */
int le_Win32Handle;
void Win32Handle_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	void * resource = (void *)(rsrc->ptr);

	do {
	} while (0);
}

int le_CanonicalBuffer;
void CanonicalBuffer_dtor(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	SerialPort_canonical_buffer * resource = (SerialPort_canonical_buffer *)(rsrc->ptr);

	do {
            
	} while (0);
	efree(resource);
}


/* }}} */

/* {{{ Class definitions */

/* {{{ Class SerialPort */

static zend_class_entry * SerialPort_ce_ptr = NULL;


long SerialPort_property_get__streamFd(GORILLA_METHOD_PARAMETERS) {
    return Z_LVAL_P(zend_read_property(_this_ce, _this_zval, "_streamFd", strlen("_streamFd"), 1 TSRMLS_CC));
}

void SerialPort_property_set__streamFd(long _streamFd, GORILLA_METHOD_PARAMETERS) {
    zend_update_property_long(_this_ce, _this_zval, "_streamFd", strlen("_streamFd"), _streamFd TSRMLS_CC);
}

zval *SerialPort_property_get__win32Handle(GORILLA_METHOD_PARAMETERS) {
    return zend_read_property(_this_ce, _this_zval, "_win32Handle", strlen("_win32Handle"), 1 TSRMLS_CC);
}

zval *SerialPort_property_get__win32CanonicalBuffer(GORILLA_METHOD_PARAMETERS) {
    return zend_read_property(_this_ce, _this_zval, "_win32CanonicalBuffer", strlen("_win32CanonicalBuffer"), 1 TSRMLS_CC);
}

zend_bool SerialPort_property_get__win32IsCanonical(GORILLA_METHOD_PARAMETERS) {
    return Z_BVAL_P(zend_read_property(_this_ce, _this_zval, "_win32IsCanonical", strlen("_win32IsCanonical"), 1 TSRMLS_CC));
}

void SerialPort_property_set__win32IsCanonical(zend_bool _isCanonical, GORILLA_METHOD_PARAMETERS) {
    zend_update_property_bool(_this_ce, _this_zval, "_win32IsCanonical", strlen("_win32IsCanonical"), _isCanonical TSRMLS_CC);
}

char *SerialPort_property_get__win32NewLine(GORILLA_METHOD_PARAMETERS) {
    return Z_STRVAL_P(zend_read_property(_this_ce, _this_zval, "_win32NewLine", strlen("_win32NewLine"), 1 TSRMLS_CC));
}

void SerialPort_property_set__win32NewLine(const char *nl, long nl_len, GORILLA_METHOD_PARAMETERS) {
    zend_update_property_stringl(_this_ce, _this_zval, "_win32NewLine", strlen("_win32NewLine"), nl, nl_len TSRMLS_CC);
}

zend_bool SerialPort_property_get__win32Rts(GORILLA_METHOD_PARAMETERS) {
    return Z_BVAL_P(zend_read_property(_this_ce, _this_zval, "_win32Rts", strlen("_win32Rts"), 1 TSRMLS_CC));
}

void SerialPort_property_set__win32Rts(zend_bool rts, GORILLA_METHOD_PARAMETERS) {
    zend_update_property_bool(_this_ce, _this_zval, "_win32Rts", strlen("_win32Rts"), rts TSRMLS_CC);
}

zend_bool SerialPort_property_get__win32Dtr(GORILLA_METHOD_PARAMETERS) {
    return Z_BVAL_P(zend_read_property(_this_ce, _this_zval, "_win32Dtr", strlen("_win32Dtr"), 1 TSRMLS_CC));
}

void SerialPort_property_set__win32Dtr(zend_bool dtr, GORILLA_METHOD_PARAMETERS) {
    zend_update_property_bool(_this_ce, _this_zval, "_win32Dtr", strlen("_win32Dtr"), dtr TSRMLS_CC);
}

long SerialPort_property_get__win32VMin(GORILLA_METHOD_PARAMETERS) {
    return Z_LVAL_P(zend_read_property(_this_ce, _this_zval, "_win32VMin", strlen("_win32VMin"), 1 TSRMLS_CC));
}

void SerialPort_property_set__win32VMin(long vmin, GORILLA_METHOD_PARAMETERS) {
    zend_update_property_long(_this_ce, _this_zval, "_win32VMin", strlen("_win32VMin"), vmin TSRMLS_CC);
}

long SerialPort_property_get__win32VTime(GORILLA_METHOD_PARAMETERS) {
    return Z_LVAL_P(zend_read_property(_this_ce, _this_zval, "_win32VTime", strlen("_win32VTime"), 1 TSRMLS_CC));
}

void SerialPort_property_set__win32VTime(long vtime, GORILLA_METHOD_PARAMETERS) {
    zend_update_property_long(_this_ce, _this_zval, "_win32VTime", strlen("_win32VTime"), vtime TSRMLS_CC);
}

/* {{{ Methods */

static zend_bool SerialPort_isOpen_impl(GORILLA_METHOD_PARAMETERS) {
    return (zend_bool)(SerialPort_property_get__streamFd(GORILLA_METHOD_PARAM_PASSTHRU) != -1);
}

/* {{{ proto object __construct([string device])
   */
PHP_METHOD(SerialPort, __construct)
{
    zend_class_entry * _this_ce;
    zval * _this_zval;

    const char * device = NULL;
    int device_len = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|s", &device, &device_len) == FAILURE) {
        return;
    }

    _this_zval = getThis();
    _this_ce = Z_OBJCE_P(_this_zval);
    
    if (device_len > 0) {
        PROP_SET_STRINGL(_device, device, device_len);
        SerialPort_open_impl(PROP_GET_STRING(_device), GORILLA_METHOD_PARAM_PASSTHRU);
    }
    
    RETVAL_ZVAL(_this_zval, 1, 0);
}
/* }}} __construct */


/* {{{ proto void __destruct()
   */
PHP_METHOD(SerialPort, __destruct)
{
    zend_class_entry * _this_ce;
    zval * _this_zval = NULL;

    if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, SerialPort_ce_ptr) == FAILURE) {
            return;
    }

    _this_ce = Z_OBJCE_P(_this_zval);
    if (SerialPort_isOpen_impl(GORILLA_METHOD_PARAM_PASSTHRU)) {
        SerialPort_close_impl(GORILLA_METHOD_PARAM_PASSTHRU);
    }
}
/* }}} __destruct */


/* {{{ proto object open(string device)
   */
PHP_METHOD(SerialPort, open)
{
    zend_class_entry * _this_ce;
    zval * _this_zval = NULL;
    const char * device = NULL;
    int device_len = 0;

    if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os", &_this_zval, SerialPort_ce_ptr, &device, &device_len) == FAILURE) {
        return;
    }

    _this_ce = Z_OBJCE_P(_this_zval);

    PROP_SET_STRINGL(_device, device, device_len);
    SerialPort_open_impl(PROP_GET_STRING(_device), GORILLA_METHOD_PARAM_PASSTHRU);
    
    RETVAL_ZVAL(_this_zval, 1, 0);
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

    if (SerialPort_isOpen_impl(GORILLA_METHOD_PARAM_PASSTHRU)) {
        RETURN_BOOL(SerialPort_close_impl(GORILLA_METHOD_PARAM_PASSTHRU));
    } else {
        RETURN_TRUE;
    }
    
}
/* }}} close */



/* {{{ proto bool isOpen()
   */
PHP_METHOD(SerialPort, isOpen)
{
    zend_class_entry * _this_ce;
    zval * _this_zval = NULL;
    zval *zval_stream;

    if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, SerialPort_ce_ptr) == FAILURE) {
        return;
    }

    _this_ce = Z_OBJCE_P(_this_zval);
    
    if (SerialPort_isOpen_impl(GORILLA_METHOD_PARAM_PASSTHRU)) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}
/* }}} isOpen */


/* {{{ proto string read([int length])
   */
PHP_METHOD(SerialPort, read)
{
    zend_class_entry * _this_ce;
    zval * _this_zval = NULL;
    long length = 1;
    zval *data;
    zval *zval_stream;
    php_stream *stream;
    char *buf;
    long actual_length;

    if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O|l", &_this_zval, SerialPort_ce_ptr, &length) == FAILURE) {
        return;
    }
    
    if (length == 0) {
        RETURN_STRINGL("", 0, 1);
    } else if (length < 0) {
        zend_throw_exception(NULL, "invalid length. length must be positive integer or zero.", 23 TSRMLS_CC);
        return;
    }

    _this_ce = Z_OBJCE_P(_this_zval);

    data = SerialPort_read_impl(length, GORILLA_METHOD_PARAM_PASSTHRU);
    RETVAL_STRINGL(Z_STRVAL_P(data), Z_STRLEN_P(data), 1);
    zval_dtor(data);
    return;
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
    
    RETURN_LONG((long)SerialPort_write_impl(data, data_len, GORILLA_METHOD_PARAM_PASSTHRU));
}
/* }}} write */



/* {{{ proto bool getCTS()
   */
PHP_METHOD(SerialPort, getCTS)
{
    zend_class_entry * _this_ce;
    zval * _this_zval = NULL;

    if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, SerialPort_ce_ptr) == FAILURE) {
        return;
    }

    _this_ce = Z_OBJCE_P(_this_zval);

    if (SerialPort_getCTS_impl(GORILLA_METHOD_PARAM_PASSTHRU)) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}
/* }}} getCTS */



/* {{{ proto bool getRTS()
   */
PHP_METHOD(SerialPort, getRTS)
{
    zend_class_entry * _this_ce;
    zval * _this_zval = NULL;

    if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, SerialPort_ce_ptr) == FAILURE) {
        return;
    }

    _this_ce = Z_OBJCE_P(_this_zval);

    if (SerialPort_getRTS_impl(GORILLA_METHOD_PARAM_PASSTHRU)) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}
/* }}} getRTS */



/* {{{ proto object setRTS(bool rts)
   */
PHP_METHOD(SerialPort, setRTS)
{
    zend_class_entry * _this_ce;
    zval * _this_zval = NULL;
    zend_bool rts = 0;

    if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ob", &_this_zval, SerialPort_ce_ptr, &rts) == FAILURE) {
        return;
    }

    _this_ce = Z_OBJCE_P(_this_zval);

    SerialPort_setRTS_impl(rts, GORILLA_METHOD_PARAM_PASSTHRU);

    RETVAL_ZVAL(_this_zval, 1, 0);
}
/* }}} setRTS */



/* {{{ proto bool getDSR()
   */
PHP_METHOD(SerialPort, getDSR)
{
    zend_class_entry * _this_ce;
    zval * _this_zval = NULL;

    if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, SerialPort_ce_ptr) == FAILURE) {
        return;
    }

    _this_ce = Z_OBJCE_P(_this_zval);

    if (SerialPort_getDSR_impl(GORILLA_METHOD_PARAM_PASSTHRU)) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}
/* }}} getDSR */



/* {{{ proto bool getDTR()
   */
PHP_METHOD(SerialPort, getDTR)
{
    zend_class_entry * _this_ce;
    zval * _this_zval = NULL;

    if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, SerialPort_ce_ptr) == FAILURE) {
        return;
    }

    _this_ce = Z_OBJCE_P(_this_zval);

    if (SerialPort_getDTR_impl(GORILLA_METHOD_PARAM_PASSTHRU)) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}
/* }}} getDTR */



/* {{{ proto object setDTR(bool dtr)
   */
PHP_METHOD(SerialPort, setDTR)
{
    zend_class_entry * _this_ce;
    zval * _this_zval = NULL;
    zend_bool dtr = 0;

    if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ob", &_this_zval, SerialPort_ce_ptr, &dtr) == FAILURE) {
        return;
    }

    _this_ce = Z_OBJCE_P(_this_zval);

    SerialPort_setDTR_impl(dtr, GORILLA_METHOD_PARAM_PASSTHRU);
    RETVAL_ZVAL(_this_zval, 1, 0);
}
/* }}} setDTR */



/* {{{ proto bool getDCD()
   */
PHP_METHOD(SerialPort, getDCD)
{
    zend_class_entry * _this_ce;
    zval * _this_zval = NULL;

    if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, SerialPort_ce_ptr) == FAILURE) {
        return;
    }

    _this_ce = Z_OBJCE_P(_this_zval);

    if (SerialPort_getDCD_impl(GORILLA_METHOD_PARAM_PASSTHRU)) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}
/* }}} getDCD */



/* {{{ proto bool getRNG()
   */
PHP_METHOD(SerialPort, getRNG)
{
    zend_class_entry * _this_ce;
    zval * _this_zval = NULL;

    if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, SerialPort_ce_ptr) == FAILURE) {
        return;
    }

    _this_ce = Z_OBJCE_P(_this_zval);

   if (SerialPort_getRNG_impl(GORILLA_METHOD_PARAM_PASSTHRU)) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}
/* }}} getRNG */


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

   RETURN_LONG(SerialPort_getBaudRate_impl(GORILLA_METHOD_PARAM_PASSTHRU));
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

    SerialPort_setBaudRate_impl(baudRate, GORILLA_METHOD_PARAM_PASSTHRU);
    
    RETVAL_ZVAL(_this_zval, 1, 0);
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
    
    RETURN_LONG(SerialPort_getCharSize_impl(GORILLA_METHOD_PARAM_PASSTHRU));
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
    
    SerialPort_setCharSize_impl(charSize, GORILLA_METHOD_PARAM_PASSTHRU);
    RETVAL_ZVAL(_this_zval, 1, 0);
}
/* }}} setCharSize */



/* {{{ proto string getFlowControl()
   */
PHP_METHOD(SerialPort, getFlowControl)
{
    zend_class_entry * _this_ce;
    zval * _this_zval = NULL;
    int flow_control;
    char *flow_control_str;

    if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, SerialPort_ce_ptr) == FAILURE) {
        return;
    }

    _this_ce = Z_OBJCE_P(_this_zval);

    flow_control = SerialPort_getFlowControl_impl(GORILLA_METHOD_PARAM_PASSTHRU);
    flow_control_str = FLOW_CONTROL_STR(flow_control);
    RETURN_STRINGL(flow_control_str, strlen(flow_control_str), 1);
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
    int flow_control;

    if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os", &_this_zval, SerialPort_ce_ptr, &flowControl, &flowControl_len) == FAILURE) {
        return;
    }

    _this_ce = Z_OBJCE_P(_this_zval);
    
    if (strncmp(flowControl, FLOW_CONTROL_HARD_STR, flowControl_len) == 0) {
        flow_control = FLOW_CONTROL_HARD;
    } else if (strncmp(flowControl, FLOW_CONTROL_SOFT_STR, flowControl_len) == 0) {
        flow_control = FLOW_CONTROL_SOFT;
    } else if (strncmp(flowControl, FLOW_CONTROL_NONE_STR, flowControl_len) == 0) {
        flow_control = FLOW_CONTROL_NONE;
    } else {
        zend_throw_exception(NULL, "invalid flow control", FLOW_CONTROL_INVALID TSRMLS_CC);
        return;
    }
    
    SerialPort_setFlowControl_impl(flow_control, GORILLA_METHOD_PARAM_PASSTHRU);
    RETVAL_ZVAL(_this_zval, 1, 0);
}
/* }}} setFlowControl */



/* {{{ proto int getNumOfStopBits()
   */
PHP_METHOD(SerialPort, getNumOfStopBits)
{
    zend_class_entry * _this_ce;
    zval * _this_zval = NULL;
    
    if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, SerialPort_ce_ptr) == FAILURE) {
        return;
    }

    _this_ce = Z_OBJCE_P(_this_zval);

    RETURN_LONG(SerialPort_getNumOfStopBits_impl(GORILLA_METHOD_PARAM_PASSTHRU));
}
/* }}} getNumOfStopBits */



/* {{{ proto object setNumOfStopBits(int numOfStopBits)
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

    SerialPort_setNumOfStopBits_impl(numOfStopBits, GORILLA_METHOD_PARAM_PASSTHRU);
    RETVAL_ZVAL(_this_zval, 1, 0);
}
/* }}} setNumOfStopBits */



/* {{{ proto string getParity()
   */
PHP_METHOD(SerialPort, getParity)
{
    zend_class_entry * _this_ce;
    zval * _this_zval = NULL;
    int parity;
    char *parity_str;

    if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, SerialPort_ce_ptr) == FAILURE) {
        return;
    }

    _this_ce = Z_OBJCE_P(_this_zval);

    parity = SerialPort_getParity_impl(GORILLA_METHOD_PARAM_PASSTHRU);
    parity_str = PARITY_STR(parity);
    
    RETURN_STRINGL(parity_str, strlen(parity_str), 1);
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
    int _parity;

    if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os", &_this_zval, SerialPort_ce_ptr, &parity, &parity_len) == FAILURE) {
            return;
    }

    _this_ce = Z_OBJCE_P(_this_zval);

    
    if (strncmp(parity, PARITY_EVEN_STR, parity_len) == 0) {
        _parity = PARITY_EVEN;
    } else if (strncmp(parity, PARITY_ODD_STR, parity_len) == 0) {
        _parity = PARITY_ODD;
    } else if (strncmp(parity, PARITY_NONE_STR, parity) == 0) {
        _parity = PARITY_NONE;
    } else if (strncmp(parity, PARITY_MARK_STR, parity) == 0) {
        _parity = PARITY_MARK;
    } else if (strncmp(parity, PARITY_SPACE_STR, parity) == 0) {
        _parity = PARITY_SPACE;
    } else {
        zend_throw_exception(NULL, "invalid parity specified.", PARITY_INVALID TSRMLS_CC);
        return;
    }
    
    SerialPort_setParity_impl(_parity, GORILLA_METHOD_PARAM_PASSTHRU);
    RETVAL_ZVAL(_this_zval, 1, 0);
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

    SerialPort_setCanonical_impl(canonical, GORILLA_METHOD_PARAM_PASSTHRU);

    RETVAL_ZVAL(_this_zval, 1, 0);
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

    if (SerialPort_isCanonical_impl(GORILLA_METHOD_PARAM_PASSTHRU)) {
        RETURN_TRUE;
    } else {
        RETURN_FALSE;
    }
}
/* }}} isCanonical */


/* {{{ proto string getWin32NewLine()
   */
PHP_METHOD(SerialPort, getWin32NewLine)
{
    zend_class_entry * _this_ce;
    zval * _this_zval = NULL;
    char *nl;

    if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, SerialPort_ce_ptr) == FAILURE) {
        return;
    }

    _this_ce = Z_OBJCE_P(_this_zval);

    nl = SerialPort_property_get__win32NewLine(GORILLA_METHOD_PARAM_PASSTHRU);
    RETURN_STRING(nl, 1);
}
/* }}} getWin32NewLine */



/* {{{ proto object setWin32NewLine(string nl)
   */
PHP_METHOD(SerialPort, setWin32NewLine)
{
    zend_class_entry * _this_ce;
    zval * _this_zval = NULL;
    const char * nl = NULL;
    int nl_len = 0;

    if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Os", &_this_zval, SerialPort_ce_ptr, &nl, &nl_len) == FAILURE) {
            return;
    }

    _this_ce = Z_OBJCE_P(_this_zval);

    if (strcmp(nl, "\n") != 0 && strcmp(nl, "\r") == 0 && strcmp(nl, "\r\n") == 0) {
        zend_throw_exception(NULL, "invalid string. newline must be CR, LF or CRLF.", 435 TSRMLS_CC);
        RETURN_NULL();
    }
    
    SerialPort_property_set__win32NewLine(nl, nl_len, GORILLA_METHOD_PARAM_PASSTHRU);
    RETVAL_ZVAL(_this_zval, 1, 0);
}
/* }}} setWin32NewLine */


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

    RETURN_LONG(SerialPort_getVMin_impl(GORILLA_METHOD_PARAM_PASSTHRU));
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

    if (vMin < -1 || vMin > 255) {
        zend_throw_exception(NULL, "range exception. VMIN must be greater than or equal to 0, and less than or equal to 255.", 4395 TSRMLS_CC);
        RETURN_NULL();
    }
    
    _this_ce = Z_OBJCE_P(_this_zval);

    SerialPort_setVMin_impl(vMin, GORILLA_METHOD_PARAM_PASSTHRU);
    RETVAL_ZVAL(_this_zval, 1, 0);
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

    RETURN_LONG(SerialPort_getVTime_impl(GORILLA_METHOD_PARAM_PASSTHRU));
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

    if (vTime < -1 || vTime > 255) {
        zend_throw_exception(NULL, "range exception. VTIME must be greater than or equal to 0, and less than or equal to 255.", 4324 TSRMLS_CC);
        RETURN_NULL();
    }
    
    _this_ce = Z_OBJCE_P(_this_zval);

    SerialPort_setVTime_impl(vTime, GORILLA_METHOD_PARAM_PASSTHRU);
    RETVAL_ZVAL(_this_zval, 1, 0);
}
/* }}} setVTime */


/* {{{ proto int getWin32ReadIntervalTimeout()
   */
PHP_METHOD(SerialPort, getWin32ReadIntervalTimeout)
{
    zend_class_entry * _this_ce;
    zval * _this_zval = NULL;

    if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, SerialPort_ce_ptr) == FAILURE) {
        return;
    }

    _this_ce = Z_OBJCE_P(_this_zval);

    RETURN_LONG(SerialPort_getWin32ReadIntervalTimeout_impl(GORILLA_METHOD_PARAM_PASSTHRU));
}
/* }}} getWin32ReadIntervalTimeout */



/* {{{ proto object setWin32ReadIntervalTimeout(int time)
   */
PHP_METHOD(SerialPort, setWin32ReadIntervalTimeout)
{
    zend_class_entry * _this_ce;
    zval * _this_zval = NULL;
    long time = 0;
    
    if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &_this_zval, SerialPort_ce_ptr, &time) == FAILURE) {
        return;
    }
    
    _this_ce = Z_OBJCE_P(_this_zval);

    SerialPort_setWin32ReadIntervalTimeout_impl(time, GORILLA_METHOD_PARAM_PASSTHRU);
    RETVAL_ZVAL(_this_zval, 1, 0);
}
/* }}} setWin32ReadIntervalTimeout */



/* {{{ proto int getWin32ReadTotalTimeoutMultiplier()
   */
PHP_METHOD(SerialPort, getWin32ReadTotalTimeoutMultiplier)
{
    zend_class_entry * _this_ce;
    zval * _this_zval = NULL;

    if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, SerialPort_ce_ptr) == FAILURE) {
        return;
    }

    _this_ce = Z_OBJCE_P(_this_zval);

    RETURN_LONG(SerialPort_getWin32ReadTotalTimeoutMultiplier_impl(GORILLA_METHOD_PARAM_PASSTHRU));
}
/* }}} getWin32ReadTotalTimeoutMultiplier */



/* {{{ proto object setWin32ReadTotalTimeoutMultiplier(int time)
   */
PHP_METHOD(SerialPort, setWin32ReadTotalTimeoutMultiplier)
{
    zend_class_entry * _this_ce;
    zval * _this_zval = NULL;
    long time = 0;

    if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &_this_zval, SerialPort_ce_ptr, &time) == FAILURE) {
        return;
    }

    _this_ce = Z_OBJCE_P(_this_zval);

    SerialPort_setWin32ReadTotalTimeoutMultiplier_impl(time, GORILLA_METHOD_PARAM_PASSTHRU);
    RETVAL_ZVAL(_this_zval, 1, 0);
}
/* }}} setWin32ReadTotalTimeoutMultiplier */



/* {{{ proto int getWin32ReadTotalTimeoutConstant()
   */
PHP_METHOD(SerialPort, getWin32ReadTotalTimeoutConstant)
{
    zend_class_entry * _this_ce;
    zval * _this_zval = NULL;

    if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, SerialPort_ce_ptr) == FAILURE) {
        return;
    }

    _this_ce = Z_OBJCE_P(_this_zval);

    RETURN_LONG(SerialPort_getWin32ReadTotalTimeoutConstant_impl(GORILLA_METHOD_PARAM_PASSTHRU));
}
/* }}} getWin32ReadTotalTimeoutConstant */



/* {{{ proto object setWin32ReadTotalTimeoutConstant(int time)
   */
PHP_METHOD(SerialPort, setWin32ReadTotalTimeoutConstant)
{
    zend_class_entry * _this_ce;
    zval * _this_zval = NULL;
    long time = 0;

    if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &_this_zval, SerialPort_ce_ptr, &time) == FAILURE) {
        return;
    }

    _this_ce = Z_OBJCE_P(_this_zval);

    SerialPort_setWin32ReadTotalTimeoutConstant_impl(time, GORILLA_METHOD_PARAM_PASSTHRU);
    RETVAL_ZVAL(_this_zval, 1, 0);
}
/* }}} setWin32ReadTotalTimeoutConstant */



/* {{{ proto int getWin32WriteTotalTimeoutMultiplier()
   */
PHP_METHOD(SerialPort, getWin32WriteTotalTimeoutMultiplier)
{
    zend_class_entry * _this_ce;
    zval * _this_zval = NULL;

    if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, SerialPort_ce_ptr) == FAILURE) {
        return;
    }

    _this_ce = Z_OBJCE_P(_this_zval);

    RETURN_LONG(SerialPort_getWin32WriteTotalTimeoutMultiplier_impl(GORILLA_METHOD_PARAM_PASSTHRU));
}
/* }}} getWin32WriteTotalTimeoutMultiplier */



/* {{{ proto object setWin32WriteTotalTimeoutMultiplier(int time)
   */
PHP_METHOD(SerialPort, setWin32WriteTotalTimeoutMultiplier)
{
    zend_class_entry * _this_ce;
    zval * _this_zval = NULL;
    long time = 0;

    if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &_this_zval, SerialPort_ce_ptr, &time) == FAILURE) {
        return;
    }

    _this_ce = Z_OBJCE_P(_this_zval);

    SerialPort_setWin32WriteTotalTimeoutMultiplier_impl(time, GORILLA_METHOD_PARAM_PASSTHRU);
    RETVAL_ZVAL(_this_zval, 1, 0);
}
/* }}} setWin32WriteTotalTimeoutMultiplier */



/* {{{ proto int getWin32WriteTotalTimeoutConstant()
   */
PHP_METHOD(SerialPort, getWin32WriteTotalTimeoutConstant)
{
    zend_class_entry * _this_ce;
    zval * _this_zval = NULL;

    if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "O", &_this_zval, SerialPort_ce_ptr) == FAILURE) {
        return;
    }

    _this_ce = Z_OBJCE_P(_this_zval);

    //php_error(E_WARNING, "getWin32WriteTotalTimeoutConstant: not yet implemented"); RETURN_FALSE;
    RETURN_LONG(SerialPort_getWin32WriteTotalTimeoutConstant_impl(GORILLA_METHOD_PARAM_PASSTHRU));
}
/* }}} getWin32WriteTotalTimeoutConstant */



/* {{{ proto object setWin32WriteTotalTimeoutConstant(int time)
   */
PHP_METHOD(SerialPort, setWin32WriteTotalTimeoutConstant)
{
    zend_class_entry * _this_ce;
    zval * _this_zval = NULL;
    long time = 0;

    if (zend_parse_method_parameters(ZEND_NUM_ARGS() TSRMLS_CC, getThis(), "Ol", &_this_zval, SerialPort_ce_ptr, &time) == FAILURE) {
        return;
    }

    _this_ce = Z_OBJCE_P(_this_zval);

    SerialPort_setWin32WriteTotalTimeoutConstant_impl(time, GORILLA_METHOD_PARAM_PASSTHRU);
    RETVAL_ZVAL(_this_zval, 1, 0);
}
/* }}} setWin32WriteTotalTimeoutConstant */


static zend_function_entry SerialPort_methods[] = {
	PHP_ME(SerialPort, __construct, NULL, /**/ZEND_ACC_PUBLIC | ZEND_ACC_CTOR)
	PHP_ME(SerialPort, __destruct, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, open, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, close, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, isOpen, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, read, SerialPort__read_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, write, SerialPort__write_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, getCTS, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, getRTS, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, setRTS, SerialPort__setRTS_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, getDSR, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, getDTR, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, setDTR, SerialPort__setDTR_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, getDCD, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, getRNG, NULL, /**/ZEND_ACC_PUBLIC)
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
	PHP_ME(SerialPort, getWin32NewLine, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, setWin32NewLine, SerialPort__setWin32NewLine_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, getVMin, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, setVMin, SerialPort__setVMin_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, getVTime, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, setVTime, SerialPort__setVTime_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, getWin32ReadIntervalTimeout, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, setWin32ReadIntervalTimeout, SerialPort__setWin32ReadIntervalTimeout_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, getWin32ReadTotalTimeoutMultiplier, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, setWin32ReadTotalTimeoutMultiplier, SerialPort__setWin32ReadTotalTimeoutMultiplier_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, getWin32ReadTotalTimeoutConstant, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, setWin32ReadTotalTimeoutConstant, SerialPort__setWin32ReadTotalTimeoutConstant_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, getWin32WriteTotalTimeoutMultiplier, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, setWin32WriteTotalTimeoutMultiplier, SerialPort__setWin32WriteTotalTimeoutMultiplier_args, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, getWin32WriteTotalTimeoutConstant, NULL, /**/ZEND_ACC_PUBLIC)
	PHP_ME(SerialPort, setWin32WriteTotalTimeoutConstant, SerialPort__setWin32WriteTotalTimeoutConstant_args, /**/ZEND_ACC_PUBLIC)
	{ NULL, NULL, NULL }
};

/* }}} Methods */

static void class_init_SerialPort(TSRMLS_D)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "SerialPort", SerialPort_methods);
	SerialPort_ce_ptr = zend_register_internal_class(&ce TSRMLS_CC);

           /* {{{ Property registration */

            zend_declare_property_string(SerialPort_ce_ptr,
                "_device", 7, "",
                ZEND_ACC_PROTECTED TSRMLS_CC);

            zend_declare_property_null(SerialPort_ce_ptr, 
                "_stream", 7, 
                ZEND_ACC_PRIVATE TSRMLS_CC);

            zend_declare_property_long(SerialPort_ce_ptr, 
                "_streamFd", 9, -1, 
                ZEND_ACC_PRIVATE TSRMLS_CC);

            zend_declare_property_null(SerialPort_ce_ptr, 
                "_win32Handle", 12, 
                ZEND_ACC_PRIVATE TSRMLS_CC);

            zend_declare_property_null(SerialPort_ce_ptr, 
                "_win32CanonicalBuffer", 21, 
                ZEND_ACC_PRIVATE TSRMLS_CC);

            zend_declare_property_bool(SerialPort_ce_ptr, 
                "_win32IsCanonical", 17, 0, 
                ZEND_ACC_PRIVATE TSRMLS_CC);

            zend_declare_property_string(SerialPort_ce_ptr, 
                "_win32NewLine", 13, PHP_EOL, 
                ZEND_ACC_PRIVATE TSRMLS_CC);
        
            zend_declare_property_null(SerialPort_ce_ptr, 
                "_win32Dtr", 9, 
                ZEND_ACC_PRIVATE TSRMLS_CC);

            zend_declare_property_null(SerialPort_ce_ptr, 
                "_win32Rts", 9, 
                ZEND_ACC_PRIVATE TSRMLS_CC);

            zend_declare_property_long(SerialPort_ce_ptr, 
                "_win32VTime", 11, -1, 
                ZEND_ACC_PRIVATE TSRMLS_CC);

            zend_declare_property_long(SerialPort_ce_ptr, 
                "_win32VMin", 10, -1, 
                ZEND_ACC_PRIVATE TSRMLS_CC);
            
           /* }}} Property registration */

	/* {{{ Constant registration */

	do {
		zval *tmp, *val;
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_50", 12, BAUD_RATE_50 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_75", 12, BAUD_RATE_75 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_110", 13, BAUD_RATE_110 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_134", 13, BAUD_RATE_134 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_150", 13, BAUD_RATE_150 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_200", 13, BAUD_RATE_200 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_300", 13, BAUD_RATE_300 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_600", 13, BAUD_RATE_600 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_1200", 14, BAUD_RATE_1200 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_1800", 14, BAUD_RATE_1800 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_2400", 14, BAUD_RATE_2400 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_4800", 14, BAUD_RATE_4800 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_9600", 14, BAUD_RATE_9600 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_19200", 15, BAUD_RATE_19200 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_38400", 15, BAUD_RATE_38400 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_57600", 15, BAUD_RATE_57600 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_115200", 16, BAUD_RATE_115200 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "BAUD_RATE_230400", 16, BAUD_RATE_230400 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "CHAR_SIZE_5", 11, CHAR_SIZE_5 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "CHAR_SIZE_6", 11, CHAR_SIZE_6 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "CHAR_SIZE_7", 11, CHAR_SIZE_7 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "CHAR_SIZE_8", 11, CHAR_SIZE_8 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "CHAR_SIZE_DEFAULT", 17, CHAR_SIZE_DEFAULT TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "STOP_BITS_1_0", 13, STOP_BITS_1_0 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "STOP_BITS_1_5", 13, STOP_BITS_1_5 TSRMLS_CC );
		zend_declare_class_constant_long(SerialPort_ce_ptr, "STOP_BITS_2_0", 13, STOP_BITS_2_0 TSRMLS_CC );
		zend_declare_class_constant_stringl(SerialPort_ce_ptr, "FLOW_CONTROL_HARD", 17, FLOW_CONTROL_HARD_STR, 17 TSRMLS_CC );
		zend_declare_class_constant_stringl(SerialPort_ce_ptr, "FLOW_CONTROL_SOFT", 17, FLOW_CONTROL_SOFT_STR, 17 TSRMLS_CC );
		zend_declare_class_constant_stringl(SerialPort_ce_ptr, "FLOW_CONTROL_NONE", 17, FLOW_CONTROL_NONE_STR, 17 TSRMLS_CC );
		zend_declare_class_constant_stringl(SerialPort_ce_ptr, "FLOW_CONTROL_DEFAULT", 20, FLOW_CONTROL_NONE_STR, 17 TSRMLS_CC );
		zend_declare_class_constant_stringl(SerialPort_ce_ptr, "PARITY_EVEN", 11, PARITY_EVEN_STR, 11 TSRMLS_CC );
		zend_declare_class_constant_stringl(SerialPort_ce_ptr, "PARITY_ODD", 10, PARITY_ODD_STR, 10 TSRMLS_CC );
		zend_declare_class_constant_stringl(SerialPort_ce_ptr, "PARITY_MARK", 11, PARITY_MARK_STR, 11 TSRMLS_CC );
		zend_declare_class_constant_stringl(SerialPort_ce_ptr, "PARITY_SPACE", 12, PARITY_SPACE_STR, 12 TSRMLS_CC );
		zend_declare_class_constant_stringl(SerialPort_ce_ptr, "PARITY_NONE", 11, PARITY_NONE_STR, 11 TSRMLS_CC );
		zend_declare_class_constant_stringl(SerialPort_ce_ptr, "PARITY_DEFAULT", 14, PARITY_NONE_STR, 11 TSRMLS_CC );
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

static void class_init_Arduino(TSRMLS_D)
{
	zend_class_entry ce;

	INIT_CLASS_ENTRY(ce, "Arduino", Arduino_methods);
	Arduino_ce_ptr = zend_register_internal_class(&ce TSRMLS_CC);

	/* {{{ Property registration */

	zend_declare_property_null(Arduino_ce_ptr, 
		"_serialPort", 11, 
		ZEND_ACC_PROTECTED TSRMLS_CC);

	zend_declare_property_null(Arduino_ce_ptr, 
		"_pinList", 8, 
		ZEND_ACC_PROTECTED TSRMLS_CC);

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
zend_function_entry Gorilla_functions[] = {
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
	le_Win32Handle = zend_register_list_destructors_ex(Win32Handle_dtor, 
						   NULL, "Win32Handle", module_number);
	le_CanonicalBuffer = zend_register_list_destructors_ex(CanonicalBuffer_dtor, 
						   NULL, "CanonicalBuffer", module_number);
	class_init_SerialPort(TSRMLS_C);
	class_init_Arduino(TSRMLS_C);

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
	php_info_print_table_row(2, "Released", "2012-11-21");
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
