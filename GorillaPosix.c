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

PHPAPI void SerialPort_setBaudRate_impl(long baud_rate, GORILLA_METHOD_PARAMETERS) {
    struct termios attr;
    long serial_port_fd;
    long _baud_rate;
    
    serial_port_fd = SerialPort_read__streamFd(GORILLA_METHOD_PARAM_PASSTHRU);
    if (tcgetattr(serial_port_fd, &attr) != 0) {
        zend_throw_exception(NULL, strerror(errno), errno TSRMLS_CC);
        return;
    }
    
    switch (baud_rate) {
        case BAUD_RATE_50:
            _baud_rate = B50;
            break;
        case BAUD_RATE_75:
            _baud_rate = B75;
            break;
        case BAUD_RATE_110:
            _baud_rate = B110;
            break;
        case BAUD_RATE_134:
            _baud_rate = B134;
            break;
        case BAUD_RATE_150:
            _baud_rate = B150;
            break;
        case BAUD_RATE_200:
            _baud_rate = B200;
            break;
        case BAUD_RATE_300:
            _baud_rate = B300;
            break;
        case BAUD_RATE_600:
            _baud_rate = B600;
            break;
        case BAUD_RATE_1200:
            _baud_rate = B1200;
            break;
        case BAUD_RATE_1800:
            _baud_rate = B1800;
            break;
        case BAUD_RATE_2400:
            _baud_rate = B2400;
            break;
        case BAUD_RATE_4800:
            _baud_rate = B4800;
            break;
        case BAUD_RATE_9600:
            _baud_rate = B9600;
            break;
        case BAUD_RATE_19200:
            _baud_rate = B19200;
            break;
        case BAUD_RATE_38400:
            _baud_rate = B38400;
            break;
        case BAUD_RATE_57600:
            _baud_rate = B57600;
            break;
        case BAUD_RATE_115200:
            _baud_rate = B115200;
            break;
        case BAUD_RATE_230400:
            _baud_rate = B230400;
            break;
        default:
            zend_throw_exception(NULL, "invalid baud rate.", baud_rate TSRMLS_CC);
            return;
    }
    
    if (cfsetispeed(&attr, _baud_rate) != 0) {
        zend_throw_exception(NULL, "failed to set input baud rate.", 2 TSRMLS_CC);
        return;
    }
    
    if (cfsetospeed(&attr, _baud_rate) != 0) {
        zend_throw_exception(NULL, "failed to set output baud rate.", 3 TSRMLS_CC);
        return;
    }
    
    if (tcsetattr(serial_port_fd, TCSANOW, &attr) != 0) {
        zend_throw_exception(NULL, "failed to apply new settings.", 4 TSRMLS_CC);
        return;
    }
}
#endif