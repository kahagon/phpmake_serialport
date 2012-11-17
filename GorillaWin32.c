#ifdef PHP_WIN32
#include "php_Gorilla.h"
#include <tchar.h>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <share.h>

#define SerialPort_read_current_dcb(win32Handle, dcb) do { \
            win32Handle = SerialPort_property__win32Handle_entity(GORILLA_METHOD_PARAM_PASSTHRU); \
            memset(&dcb, 0, sizeof(DCB)); \
            if (GetCommState(win32Handle, &dcb) == FALSE) { \
                zend_throw_exception(NULL, "failed to GetCommState()", 2134 TSRMLS_CC); \
                return; \
            } \
        } while(0);

static HANDLE SerialPort_property__win32Handle_entity(GORILLA_METHOD_PARAMETERS) {
    zval *zval_win32Handle;
    int zval_win32Handle_id = -1;
    HANDLE win32Handle;
    
    zval_win32Handle = SerialPort_property_get__win32Handle(GORILLA_METHOD_PARAM_PASSTHRU);
    ZEND_FETCH_RESOURCE(win32Handle, HANDLE, &zval_win32Handle, zval_win32Handle_id, "Win32Handle", le_Win32Handle);
    
    return win32Handle;
}


static int SerialPort_getLineStatus(GORILLA_METHOD_PARAMETERS) {
    HANDLE win32Handle;
    int status;
    
    win32Handle = SerialPort_property__win32Handle_entity(GORILLA_METHOD_PARAM_PASSTHRU);
    if (GetCommModemStatus(win32Handle, (LPDWORD)&status) == FALSE) {
        zend_throw_exception(NULL, "failed to get line status", 641 TSRMLS_CC);
        return 0;
    }
    
    return status;
}


static void SerialPort_setLineStatus(zend_bool stat, int line, GORILLA_METHOD_PARAMETERS) {
    return;
}

void SerialPort_open_impl(const char *device, GORILLA_METHOD_PARAMETERS) {
    zval *zval_win32Handle, *zval_win32CanonicalBuffer;
    SerialPort_canonical_buffer *canonical_buffer;
    HANDLE win32Handle = NULL;
    DCB dcb;
    int serial_port_fd;
    int flags = O_CREAT|O_APPEND|O_RDWR|O_BINARY;
    
    SerialPort_canonical_buffer_alloc_init(canonical_buffer);
    zval_win32CanonicalBuffer = SerialPort_property_get__win32CanonicalBuffer(GORILLA_METHOD_PARAM_PASSTHRU);
    ZEND_REGISTER_RESOURCE(zval_win32CanonicalBuffer, canonical_buffer, le_CanonicalBuffer);
    
    win32Handle = CreateFile(
            device, 
            GENERIC_READ|GENERIC_WRITE, 
            FILE_SHARE_READ|FILE_SHARE_WRITE, 
            NULL, 
            OPEN_EXISTING, 
            FILE_ATTRIBUTE_NORMAL, 
            0);
    if (win32Handle == INVALID_HANDLE_VALUE) {
        zend_throw_exception(NULL, "failed to CreateFile()", 346 TSRMLS_CC);
        return;
    }
    zval_win32Handle = SerialPort_property_get__win32Handle(GORILLA_METHOD_PARAM_PASSTHRU);
    ZEND_REGISTER_RESOURCE(zval_win32Handle, win32Handle, le_Win32Handle);
    
    serial_port_fd = _open_osfhandle(win32Handle, flags);
    if (serial_port_fd == -1) {
        zend_throw_exception(NULL, strerror(errno), errno TSRMLS_CC);
        return;
    }
    SerialPort_property_set__streamFd(serial_port_fd, GORILLA_METHOD_PARAM_PASSTHRU);
    
    memset(&dcb, 0, sizeof(DCB));
    GetCommState(win32Handle, &dcb);
    dcb.fDtrControl = DTR_CONTROL_ENABLE;
    dcb.fRtsControl = RTS_CONTROL_ENABLE;
    if (SetCommState(win32Handle, &dcb) == FALSE) {
        zend_throw_exception(NULL, "failed to SetCommState()", 347 TSRMLS_CC);
        return;
    }
    
    SerialPort_setDTR_impl((zend_bool)1, GORILLA_METHOD_PARAM_PASSTHRU);
    SerialPort_setRTS_impl((zend_bool)1, GORILLA_METHOD_PARAM_PASSTHRU);
    
    return;
}

zend_bool SerialPort_close_impl(GORILLA_METHOD_PARAMETERS) {
    long serial_port_fd;
    int result = -1;
    
    serial_port_fd = SerialPort_property_get__streamFd(GORILLA_METHOD_PARAM_PASSTHRU);
    result = _close(serial_port_fd);
    SerialPort_property_set__streamFd(-1, GORILLA_METHOD_PARAM_PASSTHRU);
    
    return (zend_bool)(result == 0);
}

long SerialPort_read_canonical_impl(long serial_port_fd, char *buf, int buf_len, GORILLA_METHOD_PARAMETERS) {
    char previous, current, _buf[1], *nl;
    int actual_read = 0, nl_len, written = 0;
    zval *zval_win32CanonicalBuffer;
    SerialPort_canonical_buffer *canonical_buffer;
    
    zval_win32CanonicalBuffer = SerialPort_property_get__win32CanonicalBuffer(GORILLA_METHOD_PARAM_PASSTHRU);
    ZEND_FETCH_RESOURCE(
            canonical_buffer, 
            SerialPort_canonical_buffer *, 
            &zval_win32CanonicalBuffer, 
            -1, 
            "CanonicalBuffer", 
            le_CanonicalBuffer);
    
    nl = SerialPort_property_get__win32NewLine(GORILLA_METHOD_PARAM_PASSTHRU);
    nl_len = strlen(nl);
    
    if (canonical_buffer->read == 0 && canonical_buffer->written == 0) {
        while (canonical_buffer->written <= canonical_buffer->buffer_size) {
            actual_read = read(serial_port_fd, _buf, 1);
            if (actual_read != 1) {
                Sleep(100);
                continue;
            }

            current = _buf[0];
            if (strcmp(nl, "\r") == 0 || strcmp(nl, "\n") == 0) {
                if (current == nl[0]) {
                    int offset = (canonical_buffer->written == canonical_buffer->buffer_size ? 1 : 0);
                    canonical_buffer->buffer[canonical_buffer->written - offset] = current;
                    break;
                }
            } else if (strcmp(nl, "\r\n") == 0) {
                if (previous == '\r' && current == '\n') {
                    int offset = 1 + (canonical_buffer->written == canonical_buffer->buffer_size ? 1 : 0);
                    canonical_buffer->buffer[canonical_buffer->written - offset--] = '\r';
                    canonical_buffer->buffer[canonical_buffer->written - offset] = '\n';
                    break;
                }
            }

            if (canonical_buffer->written < canonical_buffer->buffer_size) {
                canonical_buffer->buffer[canonical_buffer->written++] = current;
            }
            previous = current;
        }
    }

    if (canonical_buffer->written < canonical_buffer->buffer_size) {
        canonical_buffer->written++;
    }
    
    if (canonical_buffer->read < canonical_buffer->written) {
        for (
            written = 0;
            written < buf_len && canonical_buffer->read < canonical_buffer->written; 
            written++, canonical_buffer->read++) 
        {
            buf[written] = canonical_buffer->buffer[canonical_buffer->read];
        }
        
        if (canonical_buffer->read == canonical_buffer->written) {
            canonical_buffer->read = canonical_buffer->written = 0;
        }
    }

    return written;
}

zval *SerialPort_read_impl(int length, GORILLA_METHOD_PARAMETERS) {
    zval *zval_data;
    char *buf;
    long serial_port_fd, actual_length;
 
    serial_port_fd = SerialPort_property_get__streamFd(GORILLA_METHOD_PARAM_PASSTHRU);
    
    ALLOC_INIT_ZVAL(zval_data);
    buf = emalloc(length);
 
    actual_length = SerialPort_property_get__win32IsCanonical(GORILLA_METHOD_PARAM_PASSTHRU) 
            ? SerialPort_read_canonical_impl(serial_port_fd, buf, length, GORILLA_METHOD_PARAM_PASSTHRU) 
            : read(serial_port_fd, buf, length);
    
    ZVAL_STRINGL(zval_data, buf, actual_length, 1);
    efree(buf);
    return zval_data;
}

size_t SerialPort_write_impl(const char * data, int data_len, GORILLA_METHOD_PARAMETERS) {
    long serial_port_fd, actual_length;
    
    serial_port_fd = SerialPort_property_get__streamFd(GORILLA_METHOD_PARAM_PASSTHRU);
    actual_length = write(serial_port_fd, data, data_len);
    if (actual_length < 0) {
        php_error(E_WARNING, "failed to write data. %s", strerror(errno));
        actual_length = 0;
    }   
    
    return actual_length;
}

void SerialPort_setCanonical_impl(zend_bool canonical, GORILLA_METHOD_PARAMETERS) {
    SerialPort_property_set__win32IsCanonical(canonical, GORILLA_METHOD_PARAM_PASSTHRU);
}

int SerialPort_isCanonical_impl(GORILLA_METHOD_PARAMETERS) {
    return SerialPort_property_get__win32IsCanonical(GORILLA_METHOD_PARAM_PASSTHRU);
}

static int SerialPort_getFlowControl_hardware(DCB *dcb) {
    return (dcb->fOutxCtsFlow == TRUE 
            && dcb->fRtsControl == RTS_CONTROL_HANDSHAKE)
                ? FLOW_CONTROL_HARD : 0;
}

static int SerialPort_getFlowControl_software(DCB *dcb) {
    return (dcb->fOutX == TRUE 
            && dcb->fInX == TRUE) 
                ? FLOW_CONTROL_SOFT : 0;
}

int SerialPort_getFlowControl_impl(GORILLA_METHOD_PARAMETERS) {
    HANDLE win32Handle;
    DCB dcb;
    int is_soft, is_hard;
    
    SerialPort_read_current_dcb(win32Handle, dcb);
    
    is_soft = (dcb.fOutX == TRUE 
            && dcb.fInX == TRUE) 
                ? FLOW_CONTROL_SOFT : 0;
    is_hard = (dcb.fOutxCtsFlow == TRUE 
            && dcb.fRtsControl == RTS_CONTROL_HANDSHAKE)
                ? FLOW_CONTROL_HARD : 0;
    
    return is_soft | is_hard;
}

void SerialPort_setFlowControl_impl(int flow_control, GORILLA_METHOD_PARAMETERS) {
    HANDLE win32Handle;
    DCB dcb;
    
    SerialPort_read_current_dcb(win32Handle, dcb);
    
    if (flow_control & FLOW_CONTROL_HARD) {
        dcb.fOutxCtsFlow = TRUE;
        dcb.fRtsControl = RTS_CONTROL_HANDSHAKE;
    } else {
        dcb.fOutxCtsFlow = FALSE;
        dcb.fRtsControl = RTS_CONTROL_ENABLE;
    }
    
    if (flow_control & FLOW_CONTROL_SOFT) {
        dcb.fOutX = TRUE;
        dcb.fInX = TRUE;
    } else {
        dcb.fOutX = FALSE;
        dcb.fInX = FALSE;
    }
    
    if (SetCommState(win32Handle, &dcb) == FALSE) {
        zend_throw_exception(NULL, "failed to SetCommState()", 2135 TSRMLS_CC);
        return;
    }
    
    return;
}

int SerialPort_getCTS_impl(GORILLA_METHOD_PARAMETERS) {
    int status;
    
    status = SerialPort_getLineStatus(GORILLA_METHOD_PARAM_PASSTHRU);
    return status & MS_CTS_ON ? 1 : 0;
}

int SerialPort_getRTS_impl(GORILLA_METHOD_PARAMETERS) {
    return SerialPort_property_get__win32Rts(GORILLA_METHOD_PARAM_PASSTHRU);
}

void SerialPort_setRTS_impl(zend_bool rts, GORILLA_METHOD_PARAMETERS) {
    HANDLE win32Handle;
    
    win32Handle = SerialPort_property__win32Handle_entity(GORILLA_METHOD_PARAM_PASSTHRU);
    if (EscapeCommFunction(win32Handle, rts ? SETRTS : CLRRTS)) {
        SerialPort_property_set__win32Rts((zend_bool)(rts ? 1 : 0), GORILLA_METHOD_PARAM_PASSTHRU);
        return;
    }
    
    zend_throw_exception(NULL, "failed to set rts", 2165 TSRMLS_CC);
    return;
}

int SerialPort_getDSR_impl(GORILLA_METHOD_PARAMETERS) {
    int status;
    
    status = SerialPort_getLineStatus(GORILLA_METHOD_PARAM_PASSTHRU);
    return status & MS_DSR_ON ? 1 : 0;
}

int SerialPort_getDTR_impl(GORILLA_METHOD_PARAMETERS) {
    return SerialPort_property_get__win32Dtr(GORILLA_METHOD_PARAM_PASSTHRU);
}

void SerialPort_setDTR_impl(zend_bool dtr, GORILLA_METHOD_PARAMETERS) {
    HANDLE win32Handle;
    
    win32Handle = SerialPort_property__win32Handle_entity(GORILLA_METHOD_PARAM_PASSTHRU);
    if (EscapeCommFunction(win32Handle, dtr ? SETDTR : CLRDTR)) {
        SerialPort_property_set__win32Dtr((zend_bool)(dtr ? 1 : 0), GORILLA_METHOD_PARAM_PASSTHRU);
        return;
    }
    
    zend_throw_exception(NULL, "failed to set dtr", 2365 TSRMLS_CC);
    return;
}

int SerialPort_getDCD_impl(GORILLA_METHOD_PARAMETERS) {
    int status;
    
    status = SerialPort_getLineStatus(GORILLA_METHOD_PARAM_PASSTHRU);
    return status & MS_RLSD_ON ? 1 : 0;
}

int SerialPort_getRNG_impl(GORILLA_METHOD_PARAMETERS) {
    int status;
    
    status = SerialPort_getLineStatus(GORILLA_METHOD_PARAM_PASSTHRU);
    return status & MS_RING_ON ? 1 : 0;
}

int SerialPort_getNumOfStopBits_impl(GORILLA_METHOD_PARAMETERS) {
    return 1;
}

void SerialPort_setNumOfStopBits_impl(long stop_bits, GORILLA_METHOD_PARAMETERS) {
    return;
}

int SerialPort_getParity_impl(GORILLA_METHOD_PARAMETERS) {
    DCB dcb;
    HANDLE win32Handle;
    
    SerialPort_read_current_dcb(win32Handle, dcb);
    
    
    switch (dcb.Parity) {
        case EVENPARITY:
            return PARITY_EVEN;
        case ODDPARITY:
            return PARITY_ODD;
        case NOPARITY:
            return PARITY_NONE;
        case MARKPARITY:
            return PARITY_MARK;
        case SPACEPARITY:
            return PARITY_SPACE;
        default:
            return PARITY_INVALID;
    }
}

void SerialPort_setParity_impl(int parity, GORILLA_METHOD_PARAMETERS) {
    DCB dcb;
    HANDLE win32Handle;
    
    SerialPort_read_current_dcb(win32Handle, dcb);
    
    switch (parity) {
        case PARITY_EVEN:
            dcb.fParity = TRUE;
            dcb.Parity = EVENPARITY;
            break;
        case PARITY_ODD:
            dcb.fParity = TRUE;
            dcb.Parity = ODDPARITY;
        case PARITY_NONE:
            dcb.fParity = FALSE;
            dcb.Parity = NOPARITY;
        case PARITY_MARK:
            dcb.fParity = TRUE;
            dcb.Parity = MARKPARITY;
        case PARITY_SPACE:
            dcb.fParity = TRUE;
            dcb.Parity = SPACEPARITY;
            break;
        default:
            zend_throw_exception(NULL, "invalid parity specified.", PARITY_INVALID TSRMLS_CC);
            return;
    }
    
    SetCommState(win32Handle, &dcb);
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
    DCB dcb;
    HANDLE win32Handle;
    
    SerialPort_read_current_dcb(win32Handle, dcb);
    return dcb.BaudRate;
}

void SerialPort_setBaudRate_impl(long baud_rate, GORILLA_METHOD_PARAMETERS) {
    DCB dcb;
    HANDLE win32Handle;
    
    SerialPort_read_current_dcb(win32Handle, dcb);
    dcb.BaudRate = baud_rate;
    SetCommState(win32Handle, &dcb);
    return;
}

#endif