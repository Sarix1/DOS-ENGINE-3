#ifndef TXT_LOG_H
#define TXT_LOG_H

#include "common.h"
#include "txt_typ.h"
#include "inp_typ.h"
#include <stdarg.h>

#define FORMAT_BUFFER_SIZE  256

extern char far format_buffer[FORMAT_BUFFER_SIZE];

int  strcmptok          (char* str, char* token, char delim);
void initRingBuf        (RingBuf_t* buf, byte* str, size_t size);

void   logPruneLine     (Log_t* log);
size_t logNumChars      (Log_t* log);
size_t logNumNewLines   (Log_t* log);
size_t logLineLen       (Log_t* log, Line_t* line);

void logWrite           (Log_t* log, char* str, int len, byte color);
void v_logWrite_f       (Log_t* log, byte color, char* format, va_list args);
void logWrite_f         (Log_t* log, byte color, char* format, ...);

inline size_t logMaxChars(Log_t* log)
{
    return log->Buffer.end - log->Buffer.start;
}

inline size_t logMaxLines(Log_t* log)
{
    return log->L_end - log->L_start;
}

inline size_t logNumChars(Log_t* log)
{
    return (log->Buffer.write < log->Buffer.read) ?
        logMaxChars(log) - (log->Buffer.read - log->Buffer.write) :
        (log->Buffer.write - log->Buffer.read);
}

inline size_t logNumNewLines(Log_t* log)
{
    return (log->L_write < log->L_read) ?
        logMaxLines(log) - (log->L_read - log->L_write) :
        log->L_write - log->L_read;
}

inline size_t logLineLen(Log_t* log, Line_t* line)
{
    return (line->end < line->start) ?
        logMaxChars(log) - (line->start - line->end) :
        (line->end - line->start);
}

inline void logPutChar(Log_t* log, byte c)
{
    *log->Buffer.write = c;
    log->Buffer.write++;
    if (log->Buffer.write == log->Buffer.end)
        log->Buffer.write = log->Buffer.start;
    if (log->Buffer.write == log->Buffer.read)
        logPruneLine(log);
}

inline void logPruneLine(Log_t* log)
{
    log->Buffer.read = log->L_read->end;
    log->L_read++;
    if (log->L_read == log->L_end)
        log->L_read = log->L_start;
}

inline void logNewLine(Log_t* log, byte color)
{
    log->L_write++;
    if (log->L_write == log->L_end)
        log->L_write = log->L_start;
    if (log->L_write == log->L_read)
        logPruneLine(log);
    log->L_write->start = log->L_write->end = log->Buffer.write;
    log->L_write->color = color;
}

void resetInput     (TextInput_t* input);
int  handleTextInput(InputEvent_t event);

#endif/* TXT_LOG_H */
