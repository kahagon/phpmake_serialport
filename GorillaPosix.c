#ifndef PHP_WIN32

#include "php_Gorilla.h"
#include <fcntl.h>

PHPAPI void SerialPort_open_impl(const char *device, GORILLA_METHOD_PARAMETERS) {
    php_stream *stream;
    zval *zval_stream;
    
    int serial_port_fd = open(PROP_GET_STRING(_device), O_RDWR|O_NOCTTY);
    if (serial_port_fd == -1) {
        zend_throw_exception(NULL, strerror(errno), errno TSRMLS_CC);
        return NULL;
    }
    
    stream = php_stream_fopen_from_fd_rel(serial_port_fd, "r+", NULL);
    zval_stream = zend_read_property(_this_ce, _this_zval, "_stream", strlen("_stream"), 1 TSRMLS_CC);
    php_stream_to_zval(stream, zval_stream);
    
    return;
}

#endif