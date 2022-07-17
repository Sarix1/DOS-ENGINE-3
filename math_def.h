#ifndef MATH_DEF_H
#define MATH_DEF_H

#include "common.h"

// intersection flags/status
#define DONT_INTERSECT          0
#define DO_INTERSECT            1
#define OUTCODE_INSIDE          0
#define OUTCODE_LEFT            BIT_0
#define OUTCODE_RIGHT           BIT_1
#define OUTCODE_TOP             BIT_2
#define OUTCODE_BOTTOM          BIT_3

// trigonometry, binary radians
#define BRAD_SHIFT              14
#define BRAD_2PI                (1<<BRAD_SHIFT)
#define BRAD_PI                 (1<<(BRAD_SHIFT-1))
#define BRAD_HPI                (1<<(BRAD_SHIFT-2))
#define BRAD_QPI                (1<<(BRAD_SHIFT-3))
#define BRAD_1_8TH_PI           (1<<(BRAD_SHIFT-4))
#define BRAD_1_16TH_PI          (1<<(BRAD_SHIFT-5))
#define BRAD_1_32ND_PI          (1<<(BRAD_SHIFT-6))
#define BRAD_1_64TH_PI          (1<<(BRAD_SHIFT-7))
#define BRAD_1_128TH_PI         (1<<(BRAD_SHIFT-8))
#define BRAD_1_256TH_PI         (1<<(BRAD_SHIFT-9))
#define BRAD_1_512TH_PI         (1<<(BRAD_SHIFT-10))
#define BRAD_1_1024TH_PI        (1<<(BRAD_SHIFT-11))
#define BRAD_1_2048TH_PI        (1<<(BRAD_SHIFT-12))
#define BRAD_1_4096TH_PI        (1<<(BRAD_SHIFT-13))
#define BRAD_1_8192ND_PI        (1<<(BRAD_SHIFT-14))

#define DEG_01                  ((1<<BRAD_SHIFT)/3600)
#define DEG_025                 (1+(1<<BRAD_SHIFT)/1440)
#define DEG_05                  ((1<<BRAD_SHIFT)/720)
#define DEG_1                   ((1<<BRAD_SHIFT)/360)
#define DEG_2                   ((1<<BRAD_SHIFT)/180)
#define DEG_3                   ((1<<BRAD_SHIFT)/120)
#define DEG_4                   ((1<<BRAD_SHIFT)/90)
#define DEG_5                   ((1<<BRAD_SHIFT)/72)
#define DEG_6                   ((1<<BRAD_SHIFT)/60)
#define DEG_7                   ((1<<BRAD_SHIFT)/60 + (1<<BRAD_SHIFT)/360)
#define DEG_8                   ((1<<BRAD_SHIFT)/45)
#define DEG_9                   ((1<<BRAD_SHIFT)/40)
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

#if ASPECT == 1
#define A(x) (((x)*6)/5)
#define a(x) (((x)*5)/6)
#define av2(v) vec2aspect(v)
#define AV2(v) vec2Aspect(v)
#else
#define A(x) (x)
#define a(x) (x)
#define av2(v) (v)
#define AV2(v) (v)
#endif/* MATH_DEF_H */

#endif/* MATH_DEFS_H */
