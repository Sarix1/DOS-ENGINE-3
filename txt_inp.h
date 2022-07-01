#ifndef TXT_INP_H
#define TXT_INP_H

#include "common.h"

enum TEXT_FX
{
    TEXT_FX_NONE = 0,
    TEXT_FX_FLAG = 1,
    TEXT_FX_GRAD = 2
};

typedef struct
{
    char* buffer;
    int   capacity;
    int   length;
    int   cursor;
    int   start;
} TextField_t;

int textInput(TextField_t* text, byte keycode);

#endif/* TXT_INP_H */
