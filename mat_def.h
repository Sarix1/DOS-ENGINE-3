#ifndef MATH_DEFS_H
#define MATH_DEFS_H

#include "common.h"

// bit twiddling
#define BIT_0   0x1
#define BIT_1   0x2
#define BIT_2   0x4
#define BIT_3   0x8
#define BIT_4   0x10
#define BIT_5   0x20
#define BIT_6   0x40
#define BIT_7   0x80
#define BIT_8   0x100
#define BIT_9   0x200
#define BIT_10  0x400
#define BIT_11  0x800
#define BIT_12  0x1000
#define BIT_13  0x2000
#define BIT_14  0x4000
#define BIT_15  0x8000
#define BIT_16  0x10000
#define BIT_17  0x20000
#define BIT_18  0x40000
#define BIT_19  0x80000
#define BIT_20  0x100000
#define BIT_21  0x200000
#define BIT_22  0x400000
#define BIT_23  0x800000
#define BIT_24  0x1000000
#define BIT_25  0x2000000
#define BIT_26  0x4000000
#define BIT_27  0x8000000
#define BIT_28  0x10000000
#define BIT_29  0x20000000
#define BIT_30  0x40000000
#define BIT_31  0x80000000
#define BIT_32  0x100000000
#define BIT_33  0x200000000
#define BIT_34  0x400000000
#define BIT_35  0x800000000
#define BIT_36  0x1000000000
#define BIT_37  0x2000000000
#define BIT_38  0x4000000000
#define BIT_39  0x8000000000
#define BIT_40  0x10000000000
#define BIT_41  0x20000000000
#define BIT_42  0x40000000000
#define BIT_43  0x80000000000
#define BIT_44  0x100000000000
#define BIT_45  0x200000000000
#define BIT_46  0x400000000000
#define BIT_47  0x800000000000
#define BIT_48  0x1000000000000
#define BIT_49  0x2000000000000
#define BIT_50  0x4000000000000
#define BIT_51  0x8000000000000
#define BIT_52  0x10000000000000
#define BIT_53  0x20000000000000
#define BIT_54  0x40000000000000
#define BIT_55  0x80000000000000
#define BIT_56  0x100000000000000
#define BIT_57  0x200000000000000
#define BIT_58  0x400000000000000
#define BIT_59  0x800000000000000
#define BIT_60  0x1000000000000000
#define BIT_61  0x2000000000000000
#define BIT_62  0x4000000000000000
#define BIT_63  0x8000000000000000

#define SET_BITS_FROM(i)        (((i) == 8) ? 0xFFu : (1u << (i)) - 1)
#define SET_BIT_RANGE(f,to)     ((SET_BITS_FROM(f)) & (~SET_BITS_FROM(to)))
#define LOWEST_SET_BIT2(x)      ((x) & 0x1    ? 0 : 1)
#define LOWEST_SET_BIT4(x)      ((x) & 0x3    ? LOWEST_SET_BIT2(x)  : 2  + LOWEST_SET_BIT2((x) >> 2))
#define LOWEST_SET_BIT8(x)      ((x) & 0xF    ? LOWEST_SET_BIT4(x)  : 4  + LOWEST_SET_BIT4((x) >> 4))
#define LOWEST_SET_BIT16(x)     ((x) & 0xFF   ? LOWEST_SET_BIT8(x)  : 8  + LOWEST_SET_BIT8((x) >> 8))
#define LOWEST_SET_BIT32(x)     ((x) & 0xFFFF ? LOWEST_SET_BIT16(x) : 16 + LOWEST_SET_BIT16((x) >> 16))
#define LOWEST_SET_BIT(x)       LOWEST_SET_BIT32(x)

#define INT8_SIGN  0x80
#define INT16_SIGN 0x8000
#define INT32_SIGN 0x80000000
#define INT64_SIGN 0x8000000000000000

// trigonometry, binary radians
#define BRAD_SHIFT  14
#define BRAD_2PI    (1<<BRAD_SHIFT)
#define BRAD_PI     ((1<<BRAD_SHIFT)/2)
#define BRAD_HPI    ((1<<BRAD_SHIFT)/4)
#define BRAD_QPI    ((1<<BRAD_SHIFT)/8)

#define DEG_1       ((1<<BRAD_SHIFT)/360)
#define DEG_5       ((1<<BRAD_SHIFT)/72)
#define DEG_10      ((1<<BRAD_SHIFT)/36)
#define DEG_15      ((1<<BRAD_SHIFT)/24)
#define DEG_45      ((1<<BRAD_SHIFT)/8)
#define DEG_90      ((1<<BRAD_SHIFT)/4)
#define DEG_180     ((1<<BRAD_SHIFT)/2)
#define DEG_270     ((1<<BRAD_SHIFT)/2 + (1<<BRAD_SHIFT)/4)
#define DEG_360     (1<<BRAD_SHIFT)

#define DEG_360_MASK ((1<<BRAD_SHIFT)-1)
#define DEG_180_MASK ((1<<(BRAD_SHIFT-1))-1)
#define DEG_90_MASK  ((1<<(BRAD_SHIFT-2))-1)
#define DEG_45_MASK  ((1<<(BRAD_SHIFT-3))-1)

#define SIN_TABLE_SHIFT 10
#define SIN_TABLE_SIZE  (1U<<SIN_TABLE_SHIFT)
#define SIN_SHIFT       16
#define SIN_ONE         ((1U<<SIN_SHIFT)-1)

#define SIN_ACOS_TABLE_SHIFT 10
#define SIN_ACOS_TABLE_SIZE  (1U<<SIN_ACOS_TABLE_SHIFT)
#define SIN_ACOS_SHIFT       16
#define SIN_ACOS_ONE         ((1U<<SIN_ACOS_SHIFT)-1)

#define ATAN_SHIFT       (BRAD_SHIFT-3)
#define ATAN_ONE         (1<<ATAN_SHIFT)
#define ATAN_TABLE_SHIFT 10
#define ATAN_TABLE_SIZE  (1<<ATAN_TABLE_SHIFT)

#define FIX_SHIFT        16
#define FIX_ONE          (1L<<FIX_SHIFT)
#define FIX_FRAC_MASK    ((1L<<FIX_SHIFT)-1)
#define FIX_WHOLE_MASK   ~((1L<<FIX_SHIFT)-1)

#define F(x) ((fixp)(x)*FIX_ONE)

// common math
#define MIN(a,b)        (((a) < (b)) ? (a) : (b))
#define MAX(a,b)        (((a) > (b)) ? (a) : (b))
#define MIN3(a,b,c)     (MIN(MIN((a), (b)), (c)))
#define MAX3(a,b,c)     (MAX(MAX((a), (b)), (c)))
#define SIGN(x)         (((x) < 0) ? -1 : (((x) > 0) ? 1 : 0))
#define ABS(x)          (((x) < 0) ? -(x) : (x))
#define SAME_SIGNS(a,b) (((int32_t)((uint32_t)(a) ^ (uint32_t)(b))) >= 0)
#define XOR(a,b)        (!(a) != !(b))
#define MUL_PI(x)       (((x)*355L)/113)
#define DIV_PI(x)       ((((x)*113L)/355)

// miscellaneous
#define DONT_INTERSECT  0
#define DO_INTERSECT    1
#define OUTCODE_INSIDE  0
#define OUTCODE_LEFT    1
#define OUTCODE_RIGHT   2
#define OUTCODE_TOP     4
#define OUTCODE_BOTTOM  8

// enums
/*
enum INTERSECTION_TYPE
{
    LINE_LINE,
    LINE_SEG,
    SEG_SEG,
    RAY_SEG,
    RAY_RAY,
    RAY_LINE
};
*/

#endif/* MATH_DEFS_H */
