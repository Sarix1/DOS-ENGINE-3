#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
//#include <stdbool.h> // not sure about this

#define true 1
#define True 1
#define TRUE 1

#define false 0
#define False 0
#define FALSE 0

typedef uint8_t  bool;
typedef int32_t  fix16_16;
typedef fix16_16 fixp;
typedef int16_t  brad;
typedef uint8_t  byte;
typedef uint16_t word;
typedef int16_t  sword;
typedef uint32_t dword;
typedef int32_t  time_t;
typedef uint16_t flags_t;
typedef uint16_t control_t;
typedef uint16_t id_t;

typedef void (*fnp)();
typedef void (*fnp_ptr)(void*);
typedef void (*fnp_int)(int);
typedef void (*fnp_2int)(int, int);

#endif/* TYPES_H */
