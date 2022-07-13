#ifndef TXT_TYP_H
#define TXT_TYP_H

typedef struct
{
    byte* buffer;
    int capacity;
    int length;
    int cursor;
    int start;
} TextInput_t;

typedef struct
{
    byte* start;
    byte* end;
    byte color;
} Line_t;

typedef struct
{
    byte* start;
    byte* end;
    byte* read;
    byte* write;
} RingBuf_t;

typedef struct
{
    RingBuf_t Buffer;
    Line_t* L_start;
    Line_t* L_end;
    Line_t* L_write;
    Line_t* L_read;
    int max_cols;   // max columns per line
    int max_lines;  // size of the line buffer
    int vis_lines;  // max lines visible at once
    byte bg_color;
} Log_t;

typedef void (*fnp_input)(TextInput_t* input);

#endif/* LOG_TYP_H */
