#ifndef PHP_WIN32

#include "php_Gorilla.h"
#include <fcntl.h>
#include <termios.h>

static long SerialPort_read__streamFd(GORILLA_METHOD_PARAMETERS) {
    return Z_LVAL_P(zend_read_property(_this_ce, _this_zval, "_streamFd", strlen("_streamFd"), 1 TSRMLS_CC));
}

PHPAPI void SerialPort_open_impl(const char *device, GORILLA_METHOD_PARAMETERS) {
    php_stream *stream;
    zval *zval_stream;
    
    int serial_port_fd = open(PROP_GET_STRING(_device), O_RDWR|O_NOCTTY);
    if (serial_port_fd == -1) {
        zend_throw_exception(NULL, strerror(errno), errno TSRMLS_CC);
        return NULL;
    }
    
    zend_update_property_long(_this_ce, _this_zval, "_streamFd", strlen("_streamFd"), serial_port_fd TSRMLS_CC);
    stream = php_stream_fopen_from_fd_rel(serial_port_fd, "r+", NULL);
    zval_stream = zend_read_property(_this_ce, _this_zval, "_stream", strlen("_stream"), 1 TSRMLS_CC);
    php_stream_to_zval(stream, zval_stream);
    
    return;
}

PHPAPI long SerialPort_getBaudRate_impl(GORILLA_METHOD_PARAMETERS) {
    struct termios attr;
    long serial_port_fd;
    
    serial_port_fd = SerialPort_read__streamFd(GORILLA_METHOD_PARAM_PASSTHRU);
    if (tcgetattr(serial_port_fd, &attr) != 0) {
        zend_throw_exception(NULL, strerror(errno), errno TSRMLS_CC);
    }
    
    switch (cfgetospeed(&attr)) {
        case B50:
            return BAUD_RATE_50;
        case B75:
            return BAUD_RATE_75;
        case B110:
            return BAUD_RATE_110;
        case B134:
            return BAUD_RATE_134;
        case B150:
            return BAUD_RATE_150;
        case B200:
            return BAUD_RATE_200;
        case B300:
            return BAUD_RATE_300;
        case B600:
            return BAUD_RATE_600;
        case B1200:
            return BAUD_RATE_1200;
        case B1800:
            return BAUD_RATE_1800;
        case B2400:
            return BAUD_RATE_2400;
        case B4800:
            return BAUD_RATE_4800;
        case B9600:
            return BAUD_RATE_9600;
        case B19200:
            return BAUD_RATE_19200;
        case B38400:
            return BAUD_RATE_38400;
        case B57600:
            return BAUD_RATE_57600;
        case B115200:
            return BAUD_RATE_115200;
        case B230400:
            return BAUD_RATE_230400;
        default:
            return 0;
    }
}
#endif