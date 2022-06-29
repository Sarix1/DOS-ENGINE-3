#ifndef MATH_DEFS_H
#define MATH_DEFS_H

#include "common.h"

// common math
#define MIN(a,b)                (((a) < (b)) ? (a) : (b))
#define MAX(a,b)                (((a) > (b)) ? (a) : (b))
#define MIN3(a,b,c)             (MIN(MIN((a), (b)), (c)))
#define MAX3(a,b,c)             (MAX(MAX((a), (b)), (c)))
#define SIGN(x)                 (((x) < 0) ? -1 : (((x) > 0) ? 1 : 0))
#define ABS(x)                  (((x) < 0) ? -(x) : (x))
#define SAME_SIGNS(a,b)         (((int32_t)((uint32_t)(a) ^ (uint32_t)(b))) >= 0)
#define XOR(a,b)                (!(a) != !(b))
#define MUL_PI(x)               (((x)*355L)/113)
#define DIV_PI(x)               ((((x)*113L)/355)

// trigonometry, binary radians
#define BRAD_SHIFT              14
#define BRAD_2PI                (1<<BRAD_SHIFT)
#define BRAD_PI                 ((1<<BRAD_SHIFT)/2)
#define BRAD_HPI                ((1<<BRAD_SHIFT)/4)
#define BRAD_QPI                ((1<<BRAD_SHIFT)/8)

#define DEG_1                   ((1<<BRAD_SHIFT)/360)
#define DEG_5                   ((1<<BRAD_SHIFT)/72)
#define DEG_10                  ((1<<BRAD_SHIFT)/36)
#define DEG_15                  ((1<<BRAD_SHIFT)/24)
#define DEG_45                  ((1<<BRAD_SHIFT)/8)
#define DEG_90                  ((1<<BRAD_SHIFT)/4)
#define DEG_180                 ((1<<BRAD_SHIFT)/2)
#define DEG_270                 ((1<<BRAD_SHIFT)/2 + (1<<BRAD_SHIFT)/4)
#define DEG_360                 (1<<BRAD_SHIFT)

#define DEG_360_MASK            ((1<<BRAD_SHIFT)-1)
#define DEG_180_MASK            ((1<<(BRAD_SHIFT-1))-1)
#define DEG_90_MASK             ((1<<(BRAD_SHIFT-2))-1)
#define DEG_45_MASK             ((1<<(BRAD_SHIFT-3))-1)

#define SIN_TABLE_SHIFT         10
#define SIN_TABLE_SIZE          (1U<<SIN_TABLE_SHIFT)
#define SIN_SHIFT               16
#define SIN_ONE                 ((1U<<SIN_SHIFT)-1)

#define SIN_ACOS_TABLE_SHIFT    10
#define SIN_ACOS_TABLE_SIZE     (1U<<SIN_ACOS_TABLE_SHIFT)
#define SIN_ACOS_SHIFT          16
#define SIN_ACOS_ONE            ((1U<<SIN_ACOS_SHIFT)-1)

#define ATAN_SHIFT              (BRAD_SHIFT-3)
#define ATAN_ONE                (1<<ATAN_SHIFT)
#define ATAN_TABLE_SHIFT        10
#define ATAN_TABLE_SIZE         (1<<ATAN_TABLE_SHIFT)

#define FIX_SHIFT               16
#define FIX_ONE                 (1L<<FIX_SHIFT)
#define FIX_FRAC_MASK           ((1L<<FIX_SHIFT)-1)
#define FIX_WHOLE_MASK          ~((1L<<FIX_SHIFT)-1)

#define F(x)                    ((fixp)(x)*FIX_ONE)

// miscellaneous
#define DONT_INTERSECT          0
#define DO_INTERSECT            1
#define OUTCODE_INSIDE          0
#define OUTCODE_LEFT            1
#define OUTCODE_RIGHT           2
#define OUTCODE_TOP             4
#define OUTCODE_BOTTOM          8

#endif/* MATH_DEFS_H */
