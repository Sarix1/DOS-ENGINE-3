#include <stdio.h>
#include "common.h"
#include "error.h"

const char far* error_str[NUM_ERRORS] =
{
    "OK",
    "ERROR",
    "Failed to allocate off-screen video buffer",
    "Timer is frozen",
    "Timer is too slow",
    "Timer is too fast",
};

void echoMsg(char* a, char* b, char* c)
{
    int ch;
    uint32_t stderr_pos = ftell(stderr);

    fprintf(stderr, "%s%s%s", a,b,c);

    fseek(stderr, stderr_pos, SEEK_SET);
    while ((ch = fgetc(stderr)) != EOF)
        putchar(ch);
}

void statusMsg(int status)
{
    int ch;
    uint32_t stderr_pos = ftell(stderr);

    if (status == ERROR || status == SUCCESS)
        fprintf(stderr, "%s\n", error_str[status]);
    else
        fprintf(stderr, "%s: %s\n", error_str[ERROR], error_str[status]);

    fseek(stderr, stderr_pos, SEEK_SET);
    while ((ch = fgetc(stderr)) != EOF)
        putchar(ch);
}
