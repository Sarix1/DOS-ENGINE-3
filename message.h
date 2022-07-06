#ifndef MESSAGE_H
#define MESSAGE_H

void (*message)(const char* format, ...);
void statusMsg(int status);
int prompt(char* str);

#endif/* MESSAGE_H */
