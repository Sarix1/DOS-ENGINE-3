#ifndef TXT_LOG_H
#define TXT_LOG_H

#include "common.h"
#include "txt_typ.h"
#include "inp_typ.h"
#include <stdarg.h>

#define FORMAT_BUFFER_SIZE  256

extern char far format_buffer[FORMAT_BUFFER_SIZE];

// inserts character into buffer; does not check for count overflow, and allows circular overwrite
inline void putcBuf(RingBuffer_t* buf, char c)
{
    buf->str[buf->write] = c;
    incAndWrap(buf->write, buf->size);
    buf->count++;
}

inline char* getBufferTail(RingBuffer_t* buf)
{
    return &(buf->str[buf->write]);
}

inline char* getBufferHead(RingBuffer_t* buf)
{
    return &(buf->str[buf->read]);
}

inline String_t* getLineTail(Log_t* log)
{
    return &log->Lines[log->line_write];
}

inline String_t* getLineHead(Log_t* log)
{
    return &log->Lines[log->line_read];
}

int strcmptok       (char* str, char* token, char delim);
void resetInput     (InputField_t* input);
void writeLog       (Log_t* log, char* str, int len, byte color);
void v_writeLog_f   (Log_t* log, byte color, char* format, va_list args);
void writeLog_f     (Log_t* log, byte color, char* format, ...);
int handleTextInput (InputEvent_t event);

#endif/* TXT_LOG_H */
