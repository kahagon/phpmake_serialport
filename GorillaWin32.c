#ifdef PHP_WIN32
#include "php_Gorilla.h"
#include <tchar.h>
#include <Windows.h>
#include <io.h>
#include <fcntl.h>
#include <share.h>

#define SerialPort_read_current_dcb(win32Handle, dcb) do { \
                    win32Handle = SerialPort_read__win32Handle_entity(GORILLA_METHOD_PARAM_PASSTHRU); \
                    memset(&dcb, 0, sizeof(DCB)); \
                    if (GetCommState(win32Handle, &dcb) == FALSE) { \
                        zend_throw_exception(NULL, "failed to GetCommState()", 2134 TSRMLS_CC); \
                        return; \
                    } \
                } while(0);

static HANDLE SerialPort_read__win32Handle_entity(GORILLA_METHOD_PARAMETERS) {
    zval *zval_win32Handle;
    int zval_win32Handle_id = -1;
    HANDLE win32Handle;
    
    zval_win32Handle = SerialPort_read__win32Handle(GORILLA_METHOD_PARAM_PASSTHRU);
    ZEND_FETCH_RESOURCE(win32Handle, HANDLE, &zval_win32Handle, zval_win32Handle_id, "Win32Handle", le_Win32Handle);
    
    return win32Handle;
}


static int SerialPort_getLineStatus(GORILLA_METHOD_PARAMETERS) {
    return 0;
}


static void SerialPort_setLineStatus(zend_bool stat, int line, GORILLA_METHOD_PARAMETERS) {
    return;
}

void SerialPort_open_impl(const char *device, GORILLA_METHOD_PARAMETERS) {
    php_stream *stream;
    zval *zval_stream;
    zval *zval_win32Handle;
    HANDLE win32Handle = NULL;
    DCB dcb;
    int serial_port_fd;
    int res = 0;
    int flags = 0;
    
    
#define mode "ab+"
    
    if (php_stream_parse_fopen_modes(mode, &flags) == FAILURE) {
        zend_throw_exception(NULL, "failed to get flags", 344 TSRMLS_CC);
        return;
    }
    
    res = _sopen_s(&serial_port_fd, device, flags, _SH_DENYNO, _S_IREAD|_S_IWRITE);
    if (res != 0) {
        zend_throw_exception(NULL, "failed to open device", 345 TSRMLS_CC);
        return;
    }
    zend_update_property_long(_this_ce, _this_zval, "_streamFd", strlen("_streamFd"), serial_port_fd TSRMLS_CC);
    
    win32Handle = _get_osfhandle(serial_port_fd);
    if (win32Handle == INVALID_HANDLE_VALUE) {
        zend_throw_exception(NULL, "failed to open Win32Handle", 346 TSRMLS_CC);
        return;
    }
    
    memset(&dcb, 0, sizeof(DCB));
    GetCommState(win32Handle, &dcb);
    dcb.fDtrControl = DTR_CONTROL_ENABLE;
    dcb.fRtsControl = RTS_CONTROL_ENABLE;
    if (SetCommState(win32Handle, &dcb) == FALSE) {
        zend_throw_exception(NULL, "failed to SetCommState()", 347 TSRMLS_CC);
        return;
    }
    
    zval_win32Handle = SerialPort_read__win32Handle(GORILLA_METHOD_PARAM_PASSTHRU);
    ZEND_REGISTER_RESOURCE(zval_win32Handle, win32Handle, le_Win32Handle);
    
    stream = php_stream_fopen_from_fd(serial_port_fd, mode, NULL);
    if (stream == NULL) {
        zend_throw_exception(NULL, "failed to open stream from file descriptor", 348 TSRMLS_CC);
        return;
    }
    zval_stream = zend_read_property(_this_ce, _this_zval, "_stream", strlen("_stream"), 1 TSRMLS_CC);
    php_stream_to_zval(stream, zval_stream);
    
    return;
}

void SerialPort_setCanonical_impl(zend_bool canonical, GORILLA_METHOD_PARAMETERS) {
    return;
}

int SerialPort_isCanonical_impl(GORILLA_METHOD_PARAMETERS) {
    return 0;
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