#ifdef PHP_WIN32
#include "php_Gorilla.h"

static long SerialPort_read__streamFd(GORILLA_METHOD_PARAMETERS) {
    return Z_LVAL_P(zend_read_property(_this_ce, _this_zval, "_streamFd", strlen("_streamFd"), 1 TSRMLS_CC));
}

static int SerialPort_getLineStatus(GORILLA_METHOD_PARAMETERS) {
    return 0;
}


static void SerialPort_setLineStatus(zend_bool stat, int line, GORILLA_METHOD_PARAMETERS) {
    return;
}

PHPAPI void SerialPort_open_impl(const char *device, GORILLA_METHOD_PARAMETERS) {
    return;
}

PHPAPI void SerialPort_setCanonical_impl(zend_bool canonical, GORILLA_METHOD_PARAMETERS) {
    return;
}

PHPAPI int SerialPort_isCanonical_impl(GORILLA_METHOD_PARAMETERS) {
    return 0;
}

PHPAPI int SerialPort_getFlowControl_impl(GORILLA_METHOD_PARAMETERS) {
    
    return FLOW_CONTROL_DEFAULT;
}

PHPAPI void SerialPort_setFlowControl_impl(int flow_control, GORILLA_METHOD_PARAMETERS) {
    return;
}

PHPAPI int SerialPort_getCTS_impl(GORILLA_METHOD_PARAMETERS) {
    return 0;
}

PHPAPI int SerialPort_getRTS_impl(GORILLA_METHOD_PARAMETERS) {
    return 0;
}

PHPAPI void SerialPort_setRTS_impl(zend_bool rts, GORILLA_METHOD_PARAMETERS) {
    return;
}

PHPAPI int SerialPort_getDSR_impl(GORILLA_METHOD_PARAMETERS) {
    return 0;
}

PHPAPI int SerialPort_getDTR_impl(GORILLA_METHOD_PARAMETERS) {
    return 0;
}

PHPAPI void SerialPort_setDTR_impl(zend_bool dtr, GORILLA_METHOD_PARAMETERS) {
    return;
}

PHPAPI int SerialPort_getDCD_impl(GORILLA_METHOD_PARAMETERS) {
    return 0;
}

PHPAPI int SerialPort_getRNG_impl(GORILLA_METHOD_PARAMETERS) {
    return 0;
}

PHPAPI int SerialPort_getNumOfStopBits_impl(GORILLA_METHOD_PARAMETERS) {
    return 1;
}

PHPAPI void SerialPort_setNumOfStopBits_impl(long stop_bits, GORILLA_METHOD_PARAMETERS) {
    return;
}

PHPAPI int SerialPort_getParity_impl(GORILLA_METHOD_PARAMETERS) {
    return PARITY_INVALID;
}

PHPAPI void SerialPort_setParity_impl(int parity, GORILLA_METHOD_PARAMETERS) {
    return;
}

PHPAPI long SerialPort_getVMin_impl(GORILLA_METHOD_PARAMETERS) {
    return 0;
}

PHPAPI void SerialPort_setVMin_impl(long vmin, GORILLA_METHOD_PARAMETERS) {
    return;
}

PHPAPI int SerialPort_getVTime_impl(GORILLA_METHOD_PARAMETERS) {
    return 0;
}

PHPAPI void SerialPort_setVTime_impl(long vtime, GORILLA_METHOD_PARAMETERS) {
    return;
}

PHPAPI void SerialPort_setCharSize_impl(long char_size, GORILLA_METHOD_PARAMETERS) {
    return;
}

PHPAPI long SerialPort_getCharSize_impl(GORILLA_METHOD_PARAMETERS) {
    return CHAR_SIZE_DEFAULT;
}

PHPAPI long SerialPort_getBaudRate_impl(GORILLA_METHOD_PARAMETERS) {
    return BAUD_RATE_9600;
}

PHPAPI void SerialPort_setBaudRate_impl(long baud_rate, GORILLA_METHOD_PARAMETERS) {
    return;
}

#endif