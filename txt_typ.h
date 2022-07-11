#ifndef TXT_TYP_H
#define TXT_TYP_H

typedef struct
{
    char* buffer;
    int capacity;
    int length;
    int cursor;
    int start;
} InputField_t;

typedef struct
{
    char* str;
    int len;
    byte color;
} String_t;

typedef struct
{
    char* str;
    int size;
    int count;
    int read;
    int write;
} RingBuffer_t;

typedef struct
{
    RingBuffer_t Buffer;
    String_t* Lines;

    byte line_count;
    byte line_read;
    byte line_write;
    byte max_cols;
    byte max_lines; // size of the line buffer
    byte vis_lines; // max lines visible at once
    byte bg_color;
} Log_t;

typedef void (*fnp_input)(InputField_t* input);

#endif/* LOG_TYP_H */
