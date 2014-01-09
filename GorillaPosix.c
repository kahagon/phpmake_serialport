#ifndef PHP_WIN32

#include "php_Gorilla.h"
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>

static int SerialPort_getLineStatus(GORILLA_METHOD_PARAMETERS) {
    int serial_port_fd, line_status;
    
    serial_port_fd = SerialPort_property_get__streamFd(GORILLA_METHOD_PARAM_PASSTHRU);
    if (ioctl(serial_port_fd, TIOCMGET, &line_status) != 0) {
        zend_throw_exception(NULL, strerror(errno), errno TSRMLS_CC);
        return 0;
    }
    
    return line_status;
}


static void SerialPort_setLineStatus(zend_bool stat, int line, GORILLA_METHOD_PARAMETERS) {
    int serial_port_fd, line_status;
    
    serial_port_fd = SerialPort_property_get__streamFd(GORILLA_METHOD_PARAM_PASSTHRU);
    if (ioctl(serial_port_fd, TIOCMGET, &line_status) != 0) {
        zend_throw_exception(NULL, strerror(errno), errno TSRMLS_CC);
        return;
    }
    
    if (stat) {
        line_status |= line;
    } else {
        line_status &= ~line;
    }
    
    if (ioctl(serial_port_fd, TIOCMSET, &line_status) != 0) {
        zend_throw_exception(NULL, strerror(errno), errno TSRMLS_CC);
        return;
    }
    
    return;
}

void SerialPort_open_impl(const char *device, GORILLA_METHOD_PARAMETERS) {
    php_stream *stream;
    zval *zval_stream;
    struct termios attr;
    
    int serial_port_fd = open(PROP_GET_STRING(_device), O_RDWR|O_NOCTTY);
    if (serial_port_fd == -1) {
        zend_throw_exception(NULL, strerror(errno), errno TSRMLS_CC);
        return;
    }
    
    SerialPort_property_set__streamFd(serial_port_fd, GORILLA_METHOD_PARAM_PASSTHRU);
    stream = php_stream_fopen_from_fd_rel(serial_port_fd, "r+", NULL);
    zval_stream = zend_read_property(_this_ce, _this_zval, "_stream", strlen("_stream"), 1 TSRMLS_CC);
    php_stream_to_zval(stream, zval_stream);
    
    if (tcgetattr(serial_port_fd, &attr) != 0) {
        zend_throw_exception(NULL, strerror(errno), errno TSRMLS_CC);
        return;
    }
    
    attr.c_lflag &= ~ECHO;
    attr.c_lflag &= ~ECHONL;
    if (tcsetattr(serial_port_fd, TCSANOW, &attr) != 0) {
        zend_throw_exception(NULL, strerror(errno), errno TSRMLS_CC);
        return;
    }
    
    return;
}

zend_bool SerialPort_close_impl(GORILLA_METHOD_PARAMETERS) {
    zval *zval_stream;
    php_stream *stream;
    int result = -1;
    
    SerialPort_property_set__streamFd(-1, GORILLA_METHOD_PARAM_PASSTHRU);
    zval_stream = zend_read_property(_this_ce, _this_zval, "_stream", strlen("_stream"), 1 TSRMLS_CC);
    php_stream_from_zval(stream, &zval_stream);
    result = php_stream_close(stream);
    ZVAL_NULL(zval_stream);

    return (zend_bool)(result == 0);
}

int SerialPort_flush_impl(GORILLA_METHOD_PARAMETERS) {
    zval *zval_stream;
    php_stream *stream;
    int result = -1;

    zval_stream = zend_read_property(_this_ce, _this_zval, "_stream", strlen("_stream"), 1 TSRMLS_CC);
    php_stream_from_zval(stream, &zval_stream);
    
    return _php_stream_flush(stream, 0 TSRMLS_CC)==0;
}

void SerialPort_read_impl(int length, zval *zval_data, GORILLA_METHOD_PARAMETERS) {
    char *buf;
    long serial_port_fd, actual_length;
    
    buf = emalloc(length);
    
    serial_port_fd = SerialPort_property_get__streamFd(GORILLA_METHOD_PARAM_PASSTHRU);
    actual_length = read(serial_port_fd, buf, length);
    
    ZVAL_STRINGL(zval_data, buf, actual_length, 1);
    efree(buf);
}

size_t SerialPort_write_impl(const char * data, int data_len, GORILLA_METHOD_PARAMETERS) {
    zval *zval_stream;
    php_stream *stream;
    long actual_size;
    
    zval_stream = zend_read_property(_this_ce, _this_zval, "_stream", strlen("_stream"), 1 TSRMLS_CC);
    php_stream_from_zval(stream, &zval_stream);
    return php_stream_write(stream, data, data_len);
}

void SerialPort_setCanonical_impl(zend_bool canonical, GORILLA_METHOD_PARAMETERS) {
    struct termios attr;
    long serial_port_fd;
    
    serial_port_fd = SerialPort_property_get__streamFd(GORILLA_METHOD_PARAM_PASSTHRU);
    if (tcgetattr(serial_port_fd, &attr) != 0) {
        zend_throw_exception(NULL, strerror(errno), errno TSRMLS_CC);
        return;
    }
    
    if (canonical) {
        attr.c_lflag |= ICANON;
    } else {
        attr.c_lflag &= ~ICANON;
    }
    if (tcsetattr(serial_port_fd, TCSANOW, &attr) != 0) {
        zend_throw_exception(NULL, strerror(errno), errno TSRMLS_CC);
        return;
    }
}

int SerialPort_isCanonical_impl(GORILLA_METHOD_PARAMETERS) {
    struct termios attr;
    long serial_port_fd;
    
    serial_port_fd = SerialPort_property_get__streamFd(GORILLA_METHOD_PARAM_PASSTHRU);
    if (tcgetattr(serial_port_fd, &attr) != 0) {
        zend_throw_exception(NULL, strerror(errno), errno TSRMLS_CC);
        return 0;
    }
    
    return attr.c_lflag & ICANON;
}

int SerialPort_getFlowControl_impl(GORILLA_METHOD_PARAMETERS) {
    struct termios attr;
    long serial_port_fd;
    
    serial_port_fd = SerialPort_property_get__streamFd(GORILLA_METHOD_PARAM_PASSTHRU);
    if (tcgetattr(serial_port_fd, &attr) != 0) {
        zend_throw_exception(NULL, strerror(errno), errno TSRMLS_CC);
        return FLOW_CONTROL_INVALID;
    }
    
    if (attr.c_iflag & (IXON|IXOFF)
            && attr.c_cc[VSTART] == ASCII_DC1
            && attr.c_cc[VSTOP] == ASCII_DC3) 
    {
        return FLOW_CONTROL_SOFT;
    } else if (attr.c_cflag & CRTSCTS) {
        return FLOW_CONTROL_HARD;
    } else {
        return FLOW_CONTROL_DEFAULT;
    }
    
}

void SerialPort_setFlowControl_impl(int flow_control, GORILLA_METHOD_PARAMETERS) {
    struct termios attr;
    long serial_port_fd;
    
    serial_port_fd = SerialPort_property_get__streamFd(GORILLA_METHOD_PARAM_PASSTHRU);
    if (tcgetattr(serial_port_fd, &attr) != 0) {
        zend_throw_exception(NULL, strerror(errno), errno TSRMLS_CC);
        return FLOW_CONTROL_INVALID;
    }
    
    if (flow_control & FLOW_CONTROL_HARD) {
        attr.c_cflag |= CRTSCTS;
    } else {
        attr.c_cflag &= ~CRTSCTS;
    }
    
    if (flow_control & FLOW_CONTROL_SOFT) {
        attr.c_iflag |= (IXON | IXOFF | IXANY);
    } else {
        attr.c_iflag &= ~(IXON | IXOFF | IXANY);
        attr.c_cc[VSTART] = ASCII_DC1;
        attr.c_cc[VSTOP] = ASCII_DC3;
    }
    
    if (
            flow_control == FLOW_CONTROL_HARD 
            && flow_control == FLOW_CONTROL_SOFT 
            && flow_control != FLOW_CONTROL_NONE) 
    {
        zend_throw_exception(NULL, "invalid flow control", FLOW_CONTROL_INVALID TSRMLS_CC);
        return;
    }
    
    if (tcsetattr(serial_port_fd, TCSANOW, &attr) != 0) {
        zend_throw_exception(NULL, "failed to set flow control", FLOW_CONTROL_INVALID TSRMLS_CC);
        return;
    }
}

int SerialPort_getCTS_impl(GORILLA_METHOD_PARAMETERS) {
    int line_status;
    
    line_status = SerialPort_getLineStatus(GORILLA_METHOD_PARAM_PASSTHRU);
    return line_status & TIOCM_CTS ? 1 : 0;
}

int SerialPort_getRTS_impl(GORILLA_METHOD_PARAMETERS) {
    int line_status;
    
    line_status = SerialPort_getLineStatus(GORILLA_METHOD_PARAM_PASSTHRU);
    return line_status & TIOCM_RTS ? 1 : 0;
}

void SerialPort_setRTS_impl(zend_bool rts, GORILLA_METHOD_PARAMETERS) {
    SerialPort_setLineStatus(rts, TIOCM_RTS, GORILLA_METHOD_PARAM_PASSTHRU);
    return;
}

int SerialPort_getDSR_impl(GORILLA_METHOD_PARAMETERS) {
    int line_status;
    
    line_status = SerialPort_getLineStatus(GORILLA_METHOD_PARAM_PASSTHRU);
    return line_status & TIOCM_DSR ? 1 : 0;
}

int SerialPort_getDTR_impl(GORILLA_METHOD_PARAMETERS) {
    int line_status;
    
    line_status = SerialPort_getLineStatus(GORILLA_METHOD_PARAM_PASSTHRU);
    return line_status & TIOCM_DTR ? 1 : 0;
}

void SerialPort_setDTR_impl(zend_bool dtr, GORILLA_METHOD_PARAMETERS) {
    SerialPort_setLineStatus(dtr, TIOCM_DTR, GORILLA_METHOD_PARAM_PASSTHRU);
    return;
}

int SerialPort_getDCD_impl(GORILLA_METHOD_PARAMETERS) {
    int line_status;
    
    line_status = SerialPort_getLineStatus(GORILLA_METHOD_PARAM_PASSTHRU);
    return line_status & TIOCM_CD ? 1 : 0;
}

int SerialPort_getRNG_impl(GORILLA_METHOD_PARAMETERS) {
    int line_status;
    
    line_status = SerialPort_getLineStatus(GORILLA_METHOD_PARAM_PASSTHRU);
    return line_status & TIOCM_RNG ? 1 : 0;
}

int SerialPort_getNumOfStopBits_impl(GORILLA_METHOD_PARAMETERS) {
    struct termios attr;
    long serial_port_fd;
    
    serial_port_fd = SerialPort_property_get__streamFd(GORILLA_METHOD_PARAM_PASSTHRU);
    if (tcgetattr(serial_port_fd, &attr) != 0) {
        zend_throw_exception(NULL, strerror(errno), errno TSRMLS_CC);
        return;
    }
    
    if (attr.c_cflag & CSTOPB) {
        return STOP_BITS_2_0;
    } else {
        return STOP_BITS_1_0;
    }
}

void SerialPort_setNumOfStopBits_impl(long stop_bits, GORILLA_METHOD_PARAMETERS) {
    struct termios attr;
    long serial_port_fd;
    
    serial_port_fd = SerialPort_property_get__streamFd(GORILLA_METHOD_PARAM_PASSTHRU);
    if (tcgetattr(serial_port_fd, &attr) != 0) {
        zend_throw_exception(NULL, strerror(errno), errno TSRMLS_CC);
        return;
    }
    
    switch (stop_bits) {
        case STOP_BITS_1_0:
            attr.c_cflag &= ~CSTOPB;
            break;
        case STOP_BITS_2_0:
            attr.c_cflag |= CSTOPB;
            break;
        default:
            zend_throw_exception(NULL, "unknown stop bits specified. stop bits must be 1 or 2.", 6 TSRMLS_CC);
            return;
    }
    
    if (tcsetattr(serial_port_fd, TCSANOW, &attr) != 0) {
        zend_throw_exception(NULL, strerror(errno), errno TSRMLS_CC);
        return;
    }
}

int SerialPort_getParity_impl(GORILLA_METHOD_PARAMETERS) {
    struct termios attr;
    long serial_port_fd;
    
    serial_port_fd = SerialPort_property_get__streamFd(GORILLA_METHOD_PARAM_PASSTHRU);
    if (tcgetattr(serial_port_fd, &attr) != 0) {
        zend_throw_exception(NULL, strerror(errno), errno TSRMLS_CC);
        return PARITY_INVALID;
    }
    
    if (attr.c_cflag & PARENB) {
        if (attr.c_cflag & PARODD) {
            return PARITY_ODD;
        } else {
            return PARITY_EVEN;
        }
    } else {
        return PARITY_NONE;
    }
}

void SerialPort_setParity_impl(int parity, GORILLA_METHOD_PARAMETERS) {
    struct termios attr;
    long serial_port_fd;
    
    serial_port_fd = SerialPort_property_get__streamFd(GORILLA_METHOD_PARAM_PASSTHRU);
    if (tcgetattr(serial_port_fd, &attr) != 0) {
        zend_throw_exception(NULL, strerror(errno), errno TSRMLS_CC);
        return;
    }
    
    switch (parity) {
        case PARITY_EVEN:
            attr.c_cflag |= PARENB;
            attr.c_cflag &= ~PARODD;
            break;
        case PARITY_ODD:
            attr.c_cflag |= PARENB;
            attr.c_cflag |= PARODD;
            break;
        case PARITY_NONE:
            attr.c_cflag &= ~PARENB;
            break;
        case PARITY_MARK: case PARITY_SPACE:
            zend_throw_exception(NULL, "parity checking 'mark' and 'space' does not supported on POSIX.", PARITY_INVALID TSRMLS_CC);
            return;
        default:
            zend_throw_exception(NULL, "invalid parity specified.", PARITY_INVALID TSRMLS_CC);
            return;
    }
    
    if (tcsetattr(serial_port_fd, TCSANOW, &attr) != 0) {
        zend_throw_exception(NULL, strerror(errno), errno TSRMLS_CC);
        return;
    }
}

long SerialPort_getVMin_impl(GORILLA_METHOD_PARAMETERS) {
    struct termios attr;
    long serial_port_fd;
    
    serial_port_fd = SerialPort_property_get__streamFd(GORILLA_METHOD_PARAM_PASSTHRU);
    if (tcgetattr(serial_port_fd, &attr) != 0) {
        zend_throw_exception(NULL, strerror(errno), errno TSRMLS_CC);
        return -1;
    }
    
    return attr.c_cc[VMIN];
}

void SerialPort_setVMin_impl(long vmin, GORILLA_METHOD_PARAMETERS) {
    struct termios attr;
    long serial_port_fd;
    
    serial_port_fd = SerialPort_property_get__streamFd(GORILLA_METHOD_PARAM_PASSTHRU);
    if (tcgetattr(serial_port_fd, &attr) != 0) {
        zend_throw_exception(NULL, strerror(errno), errno TSRMLS_CC);
        return;
    }
    
    if (vmin < -1) vmin = 0;
    attr.c_cc[VMIN] = (cc_t)vmin;
    
    if (tcsetattr(serial_port_fd, TCSANOW, &attr) != 0) {
        zend_throw_exception(NULL, strerror(errno), errno TSRMLS_CC);
        return;
    }
}

int SerialPort_getVTime_impl(GORILLA_METHOD_PARAMETERS) {
    struct termios attr;
    long serial_port_fd;
    
    serial_port_fd = SerialPort_property_get__streamFd(GORILLA_METHOD_PARAM_PASSTHRU);
    if (tcgetattr(serial_port_fd, &attr) != 0) {
        zend_throw_exception(NULL, strerror(errno), errno TSRMLS_CC);
        return -1;
    }
    
    return attr.c_cc[VTIME];
}

void SerialPort_setVTime_impl(long vtime, GORILLA_METHOD_PARAMETERS) {
    struct termios attr;
    long serial_port_fd;
    
    serial_port_fd = SerialPort_property_get__streamFd(GORILLA_METHOD_PARAM_PASSTHRU);
    if (tcgetattr(serial_port_fd, &attr) != 0) {
        zend_throw_exception(NULL, strerror(errno), errno TSRMLS_CC);
        return;
    }
    
    if (vtime < 0) vtime = 0;
    attr.c_cc[VTIME] = (cc_t)vtime;
    
    if (tcsetattr(serial_port_fd, TCSANOW, &attr) != 0) {
        zend_throw_exception(NULL, strerror(errno), errno TSRMLS_CC);
        return;
    }
}

long SerialPort_getWin32ReadIntervalTimeout_impl(GORILLA_METHOD_PARAMETERS) {
    php_error(E_ERROR, "this method is implemented on Windows only.");
    return -1;
}

void SerialPort_setWin32ReadIntervalTimeout_impl(long time, GORILLA_METHOD_PARAMETERS) {
    php_error(E_ERROR, "this method is implemented on Windows only.");
}

long SerialPort_getWin32ReadTotalTimeoutMultiplier_impl(GORILLA_METHOD_PARAMETERS) {
    php_error(E_ERROR, "this method is implemented on Windows only.");
    return -1;
}

void SerialPort_setWin32ReadTotalTimeoutMultiplier_impl(long time, GORILLA_METHOD_PARAMETERS) {
    php_error(E_ERROR, "this method is implemented on Windows only.");
}

long SerialPort_getWin32ReadTotalTimeoutConstant_impl(GORILLA_METHOD_PARAMETERS) {
    php_error(E_ERROR, "this method is implemented on Windows only.");
    return -1;
}

void SerialPort_setWin32ReadTotalTimeoutConstant_impl(long time, GORILLA_METHOD_PARAMETERS) {
    php_error(E_ERROR, "this method is implemented on Windows only.");
}

long SerialPort_getWin32WriteTotalTimeoutMultiplier_impl(GORILLA_METHOD_PARAMETERS) {
    php_error(E_ERROR, "this method is implemented on Windows only.");
    return -1;
}

void SerialPort_setWin32WriteTotalTimeoutMultiplier_impl(long time, GORILLA_METHOD_PARAMETERS) {
    php_error(E_ERROR, "this method is implemented on Windows only.");
}

long SerialPort_getWin32WriteTotalTimeoutConstant_impl(GORILLA_METHOD_PARAMETERS) {
    php_error(E_ERROR, "this method is implemented on Windows only.");
    return -1;
}

void SerialPort_setWin32WriteTotalTimeoutConstant_impl(long time, GORILLA_METHOD_PARAMETERS) {
    php_error(E_ERROR, "this method is implemented on Windows only.");
}


void SerialPort_setCharSize_impl(long char_size, GORILLA_METHOD_PARAMETERS) {
    struct termios attr;
    long serial_port_fd;
    long _char_size = CS8;
    
    serial_port_fd = SerialPort_property_get__streamFd(GORILLA_METHOD_PARAM_PASSTHRU);
    if (tcgetattr(serial_port_fd, &attr) != 0) {
        zend_throw_exception(NULL, strerror(errno), errno TSRMLS_CC);
        return;
    }
    
    switch (char_size) {
        case CHAR_SIZE_5:
            _char_size = CS5;
            break;
        case CHAR_SIZE_6:
            _char_size = CS6;
            break;
        case CHAR_SIZE_7:
            _char_size = CS7;
            break;
        case CHAR_SIZE_8:
            _char_size = CS8;
            break;
        default:
            zend_throw_exception(NULL, "invalid char size specified", 5 TSRMLS_CC);
            return;
    }
    
    if (_char_size != CS8) {
        attr.c_iflag &= ~ISTRIP;
    } else {
        attr.c_iflag |= ISTRIP;
    }
    
    attr.c_cflag &= ~CSIZE;
    attr.c_cflag |= _char_size;
    
    if (tcsetattr(serial_port_fd, TCSANOW, &attr) != 0) {
        zend_throw_exception(NULL, strerror(errno), errno TSRMLS_CC);
        return;
    }
}

long SerialPort_getCharSize_impl(GORILLA_METHOD_PARAMETERS) {
    struct termios attr;
    long serial_port_fd;
    
    serial_port_fd = SerialPort_property_get__streamFd(GORILLA_METHOD_PARAM_PASSTHRU);
    if (tcgetattr(serial_port_fd, &attr) != 0) {
        zend_throw_exception(NULL, strerror(errno), errno TSRMLS_CC);
        return 0;
    }
    
    switch (attr.c_cflag & CSIZE) {
        case CS5:
            return CHAR_SIZE_5;
        case CS6:
            return CHAR_SIZE_6;
        case CS7:
            return CHAR_SIZE_7;
        case CS8:
            return CHAR_SIZE_8;
        default:
            zend_throw_exception(NULL, "unknow char size detected.", 5 TSRMLS_CC);
            return 0;
    }
}

long SerialPort_getBaudRate_impl(GORILLA_METHOD_PARAMETERS) {
    struct termios attr;
    long serial_port_fd;
    
    serial_port_fd = SerialPort_property_get__streamFd(GORILLA_METHOD_PARAM_PASSTHRU);
    if (tcgetattr(serial_port_fd, &attr) != 0) {
        zend_throw_exception(NULL, strerror(errno), errno TSRMLS_CC);
        return 0;
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

void SerialPort_setBaudRate_impl(long baud_rate, GORILLA_METHOD_PARAMETERS) {
    struct termios attr;
    long serial_port_fd;
    long _baud_rate;
    
    serial_port_fd = SerialPort_property_get__streamFd(GORILLA_METHOD_PARAM_PASSTHRU);
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
