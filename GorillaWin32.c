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

#define SET_COMM_STATE(win32Handle, lpdcb) \
        if (SetCommState(win32Handle, lpdcb) == FALSE) { \
            zend_throw_exception(NULL, "failed to set property.", GetLastError() TSRMLS_CC); \
        } 

#define GET_COMM_TIMEOUTS(win32Handle, lptimeouts, onerror) \
        if (!GetCommTimeouts(win32Handle, lptimeouts)) { \
            zend_throw_exception(NULL, "failed to get timeouts property", GetLastError() TSRMLS_CC); \
            onerror \
        }

#define SET_COMM_TIMEOUTS(win32Handle, lptimeouts, onerror) \
        if (!SetCommTimeouts(win32Handle, lptimeouts)) { \
            zend_throw_exception(NULL, "failed to set timeouts property", GetLastError() TSRMLS_CC); \
            onerror \
        }

#define SerialPort_return_win32_timeouts_property(win32Handle, timeouts, prop) { \
            win32Handle = SerialPort_property__win32Handle_entity(GORILLA_METHOD_PARAM_PASSTHRU); \
            GET_COMM_TIMEOUTS(win32Handle, &timeouts, { return; }); \
            return timeouts.prop; \
        }

#define SerialPort_set_win32_timeouts_property(win32Handle, timeouts, prop, time) { \
            win32Handle = SerialPort_property__win32Handle_entity(GORILLA_METHOD_PARAM_PASSTHRU); \
            GET_COMM_TIMEOUTS(win32Handle, &timeouts, { return; }); \
            timeouts.prop = time; \
            SET_COMM_TIMEOUTS(win32Handle, &timeouts, {}); \
        }

#define SerialPort_set_win32_timeouts_for_posix_read(win32Handle, timeouts, _ReadIntervalTimeout, _ReadTotalTimeoutMultiplier, _ReadTotalTimeoutConstant) { \
            win32Handle = SerialPort_property__win32Handle_entity(GORILLA_METHOD_PARAM_PASSTHRU); \
            GET_COMM_TIMEOUTS(win32Handle, &timeouts, { return; }); \
            timeouts.ReadIntervalTimeout = _ReadIntervalTimeout; \
            timeouts.ReadTotalTimeoutMultiplier = _ReadTotalTimeoutMultiplier; \
            timeouts.ReadTotalTimeoutConstant = _ReadTotalTimeoutConstant; \
            SET_COMM_TIMEOUTS(win32Handle, &timeouts, {}); \
        }

#define SerialPort_check_vtime_vmin_is_negative() \
        if (SerialPort_property_get__win32VTime(GORILLA_METHOD_PARAM_PASSTHRU) != -1 \
                || SerialPort_property_get__win32VMin(GORILLA_METHOD_PARAM_PASSTHRU) != -1) { \
            zend_throw_exception(NULL, "operation not allowed. you must switch vtime and vmin value to -1 before this operation.", 54 TSRMLS_CC); \
            return; \
        }

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
    SET_COMM_STATE(win32Handle, &dcb);
    
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

long SerialPort_read_vmin0_vtime0_impl(long serial_port_fd, char *buf, int buf_len, GORILLA_METHOD_PARAMETERS) {
    char _buf[1];
    long written = 0;
        
    while (written < buf_len && read(serial_port_fd, _buf, 1)) {
        buf[written++] = _buf[0];
    }
    
    return written;
}

long SerialPort_read_vmin1_vtime0_impl(long serial_port_fd, char *buf, int buf_len, GORILLA_METHOD_PARAMETERS) {
    char _buf[1];
    long written = 0, vmin;
    
    vmin = SerialPort_property_get__win32VMin(GORILLA_METHOD_PARAM_PASSTHRU);
    while (written < buf_len) {
        if (!read(serial_port_fd, _buf, 1)) {
            if (written >= vmin) {
                break;
            } else {
                continue;
            }
        }
        buf[written++] = _buf[0];
    }
    
    return written;
}

long SerialPort_read_vmin1_vtime1_impl(long serial_port_fd, char *buf, int buf_len, GORILLA_METHOD_PARAMETERS) {
    
}

long SerialPort_read_vmin0_vtime1_impl(long serial_port_fd, char *buf, int buf_len, GORILLA_METHOD_PARAMETERS) {
    
}

zval *SerialPort_read_impl(int length, GORILLA_METHOD_PARAMETERS) {
    HANDLE win32Handle;
    COMMTIMEOUTS timeouts;
    DWORD _ReadIntervalTimeout, 
                _ReadTotalTimeoutMultiplier, 
                _ReadTotalTimeoutConstant;
    zval *zval_data;
    char *buf;
    long serial_port_fd, actual_length;
    
    win32Handle = SerialPort_property__win32Handle_entity(GORILLA_METHOD_PARAM_PASSTHRU);
    GET_COMM_TIMEOUTS(win32Handle, &timeouts, {
        zend_throw_exception(NULL, "failed to get timeouts property.", 420 TSRMLS_CC);
        return 0;
    });
    _ReadIntervalTimeout = timeouts.ReadIntervalTimeout;
    _ReadTotalTimeoutMultiplier = timeouts.ReadTotalTimeoutMultiplier;
    _ReadTotalTimeoutConstant = timeouts.ReadTotalTimeoutConstant;
    
    serial_port_fd = SerialPort_property_get__streamFd(GORILLA_METHOD_PARAM_PASSTHRU);
    
    ALLOC_INIT_ZVAL(zval_data);
    buf = emalloc(length);

    // POSIX canonical read
    if (SerialPort_property_get__win32IsCanonical(GORILLA_METHOD_PARAM_PASSTHRU)) {
        timeouts.ReadIntervalTimeout = MAXDWORD;
        timeouts.ReadTotalTimeoutMultiplier = 0;
        timeouts.ReadTotalTimeoutConstant = 50;
        SET_COMM_TIMEOUTS(win32Handle, &timeouts, {
            zend_throw_exception(NULL, "failed to set timeouts property for canonical read.", 424 TSRMLS_CC);
            return 0;
        });
        
        actual_length = SerialPort_read_canonical_impl(serial_port_fd, buf, length, GORILLA_METHOD_PARAM_PASSTHRU);
    } else if ( // POSIX non canonical read VTIME = 0 VMIN = 0
            SerialPort_property_get__win32VMin(GORILLA_METHOD_PARAM_PASSTHRU) == 0 
            && SerialPort_property_get__win32VTime(GORILLA_METHOD_PARAM_PASSTHRU) == 0) 
    {
        timeouts.ReadIntervalTimeout = MAXDWORD;
        timeouts.ReadTotalTimeoutMultiplier = 0;
        timeouts.ReadTotalTimeoutConstant = 0;
        SET_COMM_TIMEOUTS(win32Handle, &timeouts, {
            zend_throw_exception(NULL, "failed to set timeouts property for vmin = 0, vtime = 0.", 425 TSRMLS_CC);
            return 0;
        });
        
        actual_length = SerialPort_read_vmin0_vtime0_impl(serial_port_fd, buf, length, GORILLA_METHOD_PARAM_PASSTHRU);
    } else if ( // POSIX non canonical read VTIME = 0 VMIN > 0
            SerialPort_property_get__win32VMin(GORILLA_METHOD_PARAM_PASSTHRU) > 0 
            && SerialPort_property_get__win32VTime(GORILLA_METHOD_PARAM_PASSTHRU) == 0) 
    {
        timeouts.ReadIntervalTimeout = MAXDWORD;
        timeouts.ReadTotalTimeoutMultiplier = 0;
        timeouts.ReadTotalTimeoutConstant = 50;
        SET_COMM_TIMEOUTS(win32Handle, &timeouts, {
            zend_throw_exception(NULL, "failed to set timeouts property for vmin > 0, vtime = 0.", 426 TSRMLS_CC);
            return 0;
        });
        
        actual_length = SerialPort_read_vmin1_vtime0_impl(serial_port_fd, buf, length, GORILLA_METHOD_PARAM_PASSTHRU);
    } else if ( // POSIX non canonical read VTIME > 0 VMIN > 0
            SerialPort_property_get__win32VMin(GORILLA_METHOD_PARAM_PASSTHRU) > 0 
            && SerialPort_property_get__win32VTime(GORILLA_METHOD_PARAM_PASSTHRU) > 0) 
    {
        actual_length = SerialPort_read_vmin1_vtime1_impl(serial_port_fd, buf, length, GORILLA_METHOD_PARAM_PASSTHRU);
    } else if ( // POSIX non canonical read VTIME > 0 VMIN = 0
            SerialPort_property_get__win32VMin(GORILLA_METHOD_PARAM_PASSTHRU) == 0 
            && SerialPort_property_get__win32VTime(GORILLA_METHOD_PARAM_PASSTHRU) > 0) 
    {
        actual_length = SerialPort_read_vmin0_vtime1_impl(serial_port_fd, buf, length, GORILLA_METHOD_PARAM_PASSTHRU);
    } else {
        actual_length = read(serial_port_fd, buf, length);
    }
    
    ZVAL_STRINGL(zval_data, buf, actual_length, 1);
    efree(buf);
    
    timeouts.ReadIntervalTimeout = _ReadIntervalTimeout;
    timeouts.ReadTotalTimeoutMultiplier = _ReadTotalTimeoutMultiplier;
    timeouts.ReadTotalTimeoutConstant = _ReadTotalTimeoutConstant;
    SET_COMM_TIMEOUTS(win32Handle, &timeouts, {
        zend_throw_exception(NULL, "failed to restore timeouts property for canonical read.", 422 TSRMLS_CC);
        return 0;
    });
    
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
    
    SET_COMM_STATE(win32Handle, &dcb);
    
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
    DCB dcb;
    HANDLE win32Handle;
    
    SerialPort_read_current_dcb(win32Handle, dcb);
    
    switch (dcb.StopBits) {
        case ONESTOPBIT:
            return STOP_BITS_1_0;
        case ONE5STOPBITS:
            return STOP_BITS_1_5;
        case TWOSTOPBITS:
            return STOP_BITS_2_0;
        default:
            zend_throw_exception(NULL, "unknown stop bits.", PARITY_INVALID TSRMLS_CC);
            return 0;
    }
}

void SerialPort_setNumOfStopBits_impl(long stop_bits, GORILLA_METHOD_PARAMETERS) {
    DCB dcb;
    HANDLE win32Handle;
    
    SerialPort_read_current_dcb(win32Handle, dcb);
    
    switch (stop_bits) {
        case STOP_BITS_1_0:
            dcb.StopBits = ONESTOPBIT;
            break;
        case STOP_BITS_1_5:
            dcb.StopBits = ONE5STOPBITS;
            break;
        case STOP_BITS_2_0:
            dcb.StopBits = TWOSTOPBITS;
            break;
        default:
            zend_throw_exception(NULL, "unknown stop bits specified.", PARITY_INVALID TSRMLS_CC);
            return;
    }
    
    SET_COMM_STATE(win32Handle, &dcb);
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
    
    SET_COMM_STATE(win32Handle, &dcb);
    return;
}

long SerialPort_getVMin_impl(GORILLA_METHOD_PARAMETERS) {
    return SerialPort_property_get__win32VMin(GORILLA_METHOD_PARAM_PASSTHRU);
}

void SerialPort_setVMin_impl(long vmin, GORILLA_METHOD_PARAMETERS) {
    HANDLE win32Handle;
    COMMTIMEOUTS timeouts;
    
    SerialPort_property_set__win32VMin(vmin, GORILLA_METHOD_PARAM_PASSTHRU);
}

int SerialPort_getVTime_impl(GORILLA_METHOD_PARAMETERS) {
    return SerialPort_property_get__win32VTime(GORILLA_METHOD_PARAM_PASSTHRU);
}

void SerialPort_setVTime_impl(long vtime, GORILLA_METHOD_PARAMETERS) {
    HANDLE win32Handle;
    COMMTIMEOUTS timeouts;
    
    SerialPort_property_set__win32VTime(vtime, GORILLA_METHOD_PARAM_PASSTHRU);
}

long SerialPort_getWin32ReadIntervalTimeout_impl(GORILLA_METHOD_PARAMETERS) {
    HANDLE win32Handle;
    COMMTIMEOUTS timeouts;
    
    SerialPort_return_win32_timeouts_property(win32Handle, timeouts, ReadIntervalTimeout);
}

void SerialPort_setWin32ReadIntervalTimeout_impl(long time, GORILLA_METHOD_PARAMETERS) {
    HANDLE win32Handle;
    COMMTIMEOUTS timeouts;
    
    SerialPort_check_vtime_vmin_is_negative();
    SerialPort_set_win32_timeouts_property(win32Handle, timeouts, ReadIntervalTimeout, time);
}

long SerialPort_getWin32ReadTotalTimeoutMultiplier_impl(GORILLA_METHOD_PARAMETERS) {
    HANDLE win32Handle;
    COMMTIMEOUTS timeouts;
    
    SerialPort_return_win32_timeouts_property(win32Handle, timeouts, ReadTotalTimeoutMultiplier);
}

void SerialPort_setWin32ReadTotalTimeoutMultiplier_impl(long time, GORILLA_METHOD_PARAMETERS) {
    HANDLE win32Handle;
    COMMTIMEOUTS timeouts;
    
    SerialPort_check_vtime_vmin_is_negative();
    SerialPort_set_win32_timeouts_property(win32Handle, timeouts, ReadTotalTimeoutMultiplier, time);
}

long SerialPort_getWin32ReadTotalTimeoutConstant_impl(GORILLA_METHOD_PARAMETERS) {
    HANDLE win32Handle;
    COMMTIMEOUTS timeouts;
    
    SerialPort_return_win32_timeouts_property(win32Handle, timeouts, ReadTotalTimeoutConstant);
}

void SerialPort_setWin32ReadTotalTimeoutConstant_impl(long time, GORILLA_METHOD_PARAMETERS) {
    HANDLE win32Handle;
    COMMTIMEOUTS timeouts;
    
    SerialPort_check_vtime_vmin_is_negative();
    SerialPort_set_win32_timeouts_property(win32Handle, timeouts, ReadTotalTimeoutConstant, time);
}

long SerialPort_getWin32WriteTotalTimeoutMultiplier_impl(GORILLA_METHOD_PARAMETERS) {
    HANDLE win32Handle;
    COMMTIMEOUTS timeouts;
    
    SerialPort_return_win32_timeouts_property(win32Handle, timeouts, WriteTotalTimeoutMultiplier);
}

void SerialPort_setWin32WriteTotalTimeoutMultiplier_impl(long time, GORILLA_METHOD_PARAMETERS) {
    HANDLE win32Handle;
    COMMTIMEOUTS timeouts;
    
    SerialPort_set_win32_timeouts_property(win32Handle, timeouts, WriteTotalTimeoutMultiplier, time);
}

long SerialPort_getWin32WriteTotalTimeoutConstant_impl(GORILLA_METHOD_PARAMETERS) {
    HANDLE win32Handle;
    COMMTIMEOUTS timeouts;
    
    SerialPort_return_win32_timeouts_property(win32Handle, timeouts, WriteTotalTimeoutConstant);
}

void SerialPort_setWin32WriteTotalTimeoutConstant_impl(long time, GORILLA_METHOD_PARAMETERS) {
    HANDLE win32Handle;
    COMMTIMEOUTS timeouts;
    
    SerialPort_set_win32_timeouts_property(win32Handle, timeouts, WriteTotalTimeoutConstant, time);
}

void SerialPort_setCharSize_impl(long char_size, GORILLA_METHOD_PARAMETERS) {
    DCB dcb;
    HANDLE win32Handle;
    long _char_size = CHAR_SIZE_8;
    
    SerialPort_read_current_dcb(win32Handle, dcb);
    
    switch (char_size) {
        case CHAR_SIZE_5:
        case CHAR_SIZE_6:
        case CHAR_SIZE_7:
        case CHAR_SIZE_8:
            _char_size = char_size;
            break;
        default:
            zend_throw_exception(NULL, "invalid char size specified", 5 TSRMLS_CC);
            return;
    }
    
    dcb.ByteSize = _char_size;
    SET_COMM_STATE(win32Handle, &dcb);
    return;
}

long SerialPort_getCharSize_impl(GORILLA_METHOD_PARAMETERS) {
    DCB dcb;
    HANDLE win32Handle;
    
    SerialPort_read_current_dcb(win32Handle, dcb);
    return dcb.ByteSize;
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
    long _baud_rate;
    
    SerialPort_read_current_dcb(win32Handle, dcb);
    switch (baud_rate) {
        case BAUD_RATE_50:
        case BAUD_RATE_75:
        case BAUD_RATE_110:
        case BAUD_RATE_134:
        case BAUD_RATE_150:
        case BAUD_RATE_200:
        case BAUD_RATE_300:
        case BAUD_RATE_600:
        case BAUD_RATE_1200:
        case BAUD_RATE_1800:
        case BAUD_RATE_2400:
        case BAUD_RATE_4800:
        case BAUD_RATE_9600:
        case BAUD_RATE_19200:
        case BAUD_RATE_38400:
        case BAUD_RATE_57600:
        case BAUD_RATE_115200:
        case BAUD_RATE_230400:
            _baud_rate = baud_rate;
            break;
        default:
            zend_throw_exception(NULL, "invalid baud rate.", baud_rate TSRMLS_CC);
            return;
    }
    
    dcb.BaudRate = baud_rate;
    SET_COMM_STATE(win32Handle, &dcb);
    return;
}

#endif