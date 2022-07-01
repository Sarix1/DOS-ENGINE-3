#ifndef ERROR_H
#define ERROR_H

enum ERROR_CODES
{
    SUCCESS,
    ERROR,
    ERROR_VIDEO_MEMORY,
    ERROR_TIMER_FROZEN,
    ERROR_TIMER_SLOW,
    ERROR_TIMER_FAST,
    NUM_ERRORS
};

extern const char far* error_str[NUM_ERRORS];

void echoMsg(char* a, char* b, char* c);
void statusMsg(int error);

#endif/* ERROR_H */
