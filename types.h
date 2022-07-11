#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>

#ifdef __WATCOMC__
#include <stdbool.h>
#else
typedef uint8_t bool;
typedef long long int64_t;
typedef unsigned long long uint64_t;
#endif/* TYPES_H */

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

typedef void (*fnp)(void);
typedef void (*fnp_i)(int);
typedef int (*i_fnp)(void);
typedef int (*i_fnp_i)(void);

#include "macro.h"
#include "math_typ.h"

// the following things should go to event.h
// along with KeyEvent.h and other event related stuff
typedef union
{
    Vec2 v2;
    struct { int16_t a, b, c, d; } vars;
    struct { id_t id; int16_t mode; } state;
    struct { int16_t x, y, z; union {int16_t w; id_t id; id_t type; brad angle;} var; } pos;
    struct { id_t id; int str_offset; } cmd;
} Params_t;
//const int bla = sizeof(Params_t);
//make sure it stays 8 bytes!

typedef union
{
    Vec3 v3;
    struct { Vec2 v, u; } vecs;
    struct { Params_t a, b; } params;
} BigParams_t;
//const int blabig = sizeof(BigParams_t);
//make sure it stays 16 bytes!

typedef union
{
    struct { id_t id; time_t tick; Params_t params; } event;
    BigParams_t big_params;
} Event_t;
//const int blaash = sizeof(Event_t);
//make sure it stays 16 bytes!

typedef void (*fnp_ev)(Event_t event);

// Why did I spend two days on this macro junk? Am I insane?
// Note to self: Please just typedef by hand what you actually need
/*
#define FOR_EACH_DATATYPE1(DO,a,b) \
    DO(void     , NONE  ) \
    DO(void*    , p     ) \
    DO(char     , c     ) \
    DO(int      , i     ) \
    DO(unsigned , u     ) \
    DO(int8_t   , i8    ) \
    DO(int16_t  , i16   ) \
    DO(int32_t  , i32   ) \
    DO(uint8_t  , u8    ) \
    DO(uint16_t , u16   ) \
    DO(uint32_t , u32   ) \
    DO(fixp     , f     ) \
    DO(Vec2     , v2    ) \
    DO(Vec3     , v3    )

#define FOR_EACH_DATATYPE2(DO,a,b) \
    DO(void     , NONE  ) \
    DO(void*    , p     ) \
    DO(char     , c     ) \
    DO(int      , i     ) \
    DO(unsigned , u     ) \
    DO(int8_t   , i8    ) \
    DO(int16_t  , i16   ) \
    DO(int32_t  , i32   ) \
    DO(uint8_t  , u8    ) \
    DO(uint16_t , u16   ) \
    DO(uint32_t , u32   ) \
    DO(fixp     , f     ) \
    DO(Vec2     , v2    ) \
    DO(Vec3     , v3    )

#define TYPEDEF_FNP(r,pre,a,suf) typedef r (*FORMAT_TOKEN(pre,fnp,suf))(a);
#define Q(a,suf, pre,r) TYPEDEF_FNP(r,pre,a,suf)
#define O(t,u, a,b) FOR_EACH_DATATYPE2(Q,u,u)
FOR_EACH_DATATYPE1(O,,)
#undef O
#undef Q
*/

#endif/* TYPES_H */
