#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include "macro.h"

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

#include "math_typ.h"

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
