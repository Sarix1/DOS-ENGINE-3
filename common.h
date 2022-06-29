//#ifndef COMMON_H
//#define COMMON_H

#include "watcom.h"
#include "types.h"
#include "macro.h"
#include "bit.h"

#define DEBUG 1

#if DEBUG == 1
#include "debug.h"
#endif

#define ENABLED         1
#define DISABLED        0
#define INITIALIZED     1
#define NOT_INITIALIZED 0
#define HANDLED         1
#define NOT_HANDLED     0
#define SUCCESS         0
#define FAILURE         1

#define POS_CENTERED    -1
#define AUTOMATIC       -2
#define DEFAULT         -2

void quit();

//#endif/* COMMON_H */
