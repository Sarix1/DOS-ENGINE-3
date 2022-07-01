//#ifndef COMMON_H
//#define COMMON_H

#include "watcom.h"
#include "types.h"
#include "colors.h"
#include "error.h"
#include "macro.h"
#include "bit.h"

#define DEBUG 1
#define ASPECT 1

#if DEBUG == 1
#include "debug.h"
#endif

#if ASPECT == 1
#define A(x) (((x)*6)/5)
#else
#define A(x) (x)
#endif

#define YES             1
#define NO              0
#define ENABLED         1
#define DISABLED        0
#define INITIALIZED     1
#define UNINITIALIZED   0
#define HANDLED         1
#define NOT_HANDLED     0

#define ALIGN_CENTER    -1
#define ALIGN_LEFT      -2
#define ALIGN_RIGHT     -3
#define ALIGN_TOP       -4
#define ALIGN_BOTTOM    -5

#define AUTO            -1
#define DEFAULT         -2

void quit();

//#endif/* COMMON_H */
