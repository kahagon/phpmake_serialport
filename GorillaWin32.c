#ifdef PHP_WIN32
#include "php_Gorilla.h"

static int SerialPort_getLineStatus(GORILLA_METHOD_PARAMETERS) {
    return 0;
}


static void SerialPort_setLineStatus(zend_bool stat, int line, GORILLA_METHOD_PARAMETERS) {
    return;
}

void SerialPort_open_impl(const char *device, GORILLA_METHOD_PARAMETERS) {
    return;
}

void SerialPort_setCanonical_impl(zend_bool canonical, GORILLA_METHOD_PARAMETERS) {
    return;
}

int SerialPort_isCanonical_impl(GORILLA_METHOD_PARAMETERS) {
    return 0;
}

int SerialPort_getFlowControl_impl(GORILLA_METHOD_PARAMETERS) {
    
    return FLOW_CONTROL_DEFAULT;
}

void SerialPort_setFlowControl_impl(int flow_control, GORILLA_METHOD_PARAMETERS) {
    return;
}

int SerialPort_getCTS_impl(GORILLA_METHOD_PARAMETERS) {
    return 0;
}

int SerialPort_getRTS_impl(GORILLA_METHOD_PARAMETERS) {
    return 0;
}

void SerialPort_setRTS_impl(zend_bool rts, GORILLA_METHOD_PARAMETERS) {
    return;
}

int SerialPort_getDSR_impl(GORILLA_METHOD_PARAMETERS) {
    return 0;
}

int SerialPort_getDTR_impl(GORILLA_METHOD_PARAMETERS) {
    return 0;
}

void SerialPort_setDTR_impl(zend_bool dtr, GORILLA_METHOD_PARAMETERS) {
    return;
}

int SerialPort_getDCD_impl(GORILLA_METHOD_PARAMETERS) {
    return 0;
}

int SerialPort_getRNG_impl(GORILLA_METHOD_PARAMETERS) {
    return 0;
}

int SerialPort_getNumOfStopBits_impl(GORILLA_METHOD_PARAMETERS) {
    return 1;
}

void SerialPort_setNumOfStopBits_impl(long stop_bits, GORILLA_METHOD_PARAMETERS) {
    return;
}

int SerialPort_getParity_impl(GORILLA_METHOD_PARAMETERS) {
    return PARITY_INVALID;
}

void SerialPort_setParity_impl(int parity, GORILLA_METHOD_PARAMETERS) {
    return;
}

long SerialPort_getVMin_impl(GORILLA_METHOD_PARAMETERS) {
    return 0;
}

void SerialPort_setVMin_impl(long vmin, GORILLA_METHOD_PARAMETERS) {
    return;
}

int SerialPort_getVTime_impl(GORILLA_METHOD_PARAMETERS) {
    return 0;
}

void SerialPort_setVTime_impl(long vtime, GORILLA_METHOD_PARAMETERS) {
    return;
}

void SerialPort_setCharSize_impl(long char_size, GORILLA_METHOD_PARAMETERS) {
    return;
}

long SerialPort_getCharSize_impl(GORILLA_METHOD_PARAMETERS) {
    return CHAR_SIZE_DEFAULT;
}

long SerialPort_getBaudRate_impl(GORILLA_METHOD_PARAMETERS) {
    return BAUD_RATE_9600;
}

void SerialPort_setBaudRate_impl(long baud_rate, GORILLA_METHOD_PARAMETERS) {
    return;
}

#endif