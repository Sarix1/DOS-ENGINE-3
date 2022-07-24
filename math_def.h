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

#define FIXP_SHIFT              16
#define FIXP_ONE                (1L<<FIXP_SHIFT)
#define FIXP_FRAC_MASK          ((1L<<FIXP_SHIFT)-1)
#define FIXP_WHOLE_MASK         ~((1L<<FIXP_SHIFT)-1)

#define FIXP_001 ((FIXP_ONE* 1)/100)
#define FIXP_002 ((FIXP_ONE* 2)/100)
#define FIXP_003 ((FIXP_ONE* 3)/100)
#define FIXP_004 ((FIXP_ONE* 4)/100)
#define FIXP_005 ((FIXP_ONE* 5)/100)
#define FIXP_006 ((FIXP_ONE* 6)/100)
#define FIXP_007 ((FIXP_ONE* 7)/100)
#define FIXP_008 ((FIXP_ONE* 8)/100)
#define FIXP_009 ((FIXP_ONE* 9)/100)
#define FIXP_010 ((FIXP_ONE*10)/100)
#define FIXP_011 ((FIXP_ONE*11)/100)
#define FIXP_012 ((FIXP_ONE*12)/100)
#define FIXP_013 ((FIXP_ONE*13)/100)
#define FIXP_014 ((FIXP_ONE*14)/100)
#define FIXP_015 ((FIXP_ONE*15)/100)
#define FIXP_016 ((FIXP_ONE*16)/100)
#define FIXP_017 ((FIXP_ONE*17)/100)
#define FIXP_018 ((FIXP_ONE*18)/100)
#define FIXP_019 ((FIXP_ONE*19)/100)
#define FIXP_020 ((FIXP_ONE*20)/100)
#define FIXP_021 ((FIXP_ONE*21)/100)
#define FIXP_022 ((FIXP_ONE*22)/100)
#define FIXP_023 ((FIXP_ONE*23)/100)
#define FIXP_024 ((FIXP_ONE*24)/100)
#define FIXP_025 ((FIXP_ONE*25)/100)
#define FIXP_026 ((FIXP_ONE*26)/100)
#define FIXP_027 ((FIXP_ONE*27)/100)
#define FIXP_028 ((FIXP_ONE*28)/100)
#define FIXP_029 ((FIXP_ONE*29)/100)
#define FIXP_030 ((FIXP_ONE*30)/100)
#define FIXP_031 ((FIXP_ONE*31)/100)
#define FIXP_032 ((FIXP_ONE*32)/100)
#define FIXP_033 ((FIXP_ONE*33)/100)
#define FIXP_034 ((FIXP_ONE*34)/100)
#define FIXP_035 ((FIXP_ONE*35)/100)
#define FIXP_036 ((FIXP_ONE*36)/100)
#define FIXP_037 ((FIXP_ONE*37)/100)
#define FIXP_038 ((FIXP_ONE*38)/100)
#define FIXP_039 ((FIXP_ONE*39)/100)
#define FIXP_040 ((FIXP_ONE*40)/100)
#define FIXP_041 ((FIXP_ONE*41)/100)
#define FIXP_042 ((FIXP_ONE*42)/100)
#define FIXP_043 ((FIXP_ONE*43)/100)
#define FIXP_044 ((FIXP_ONE*44)/100)
#define FIXP_045 ((FIXP_ONE*45)/100)
#define FIXP_046 ((FIXP_ONE*46)/100)
#define FIXP_047 ((FIXP_ONE*47)/100)
#define FIXP_048 ((FIXP_ONE*48)/100)
#define FIXP_049 ((FIXP_ONE*49)/100)
#define FIXP_050 ((FIXP_ONE*50)/100)
#define FIXP_051 ((FIXP_ONE*51)/100)
#define FIXP_052 ((FIXP_ONE*52)/100)
#define FIXP_053 ((FIXP_ONE*53)/100)
#define FIXP_054 ((FIXP_ONE*54)/100)
#define FIXP_055 ((FIXP_ONE*55)/100)
#define FIXP_056 ((FIXP_ONE*56)/100)
#define FIXP_057 ((FIXP_ONE*57)/100)
#define FIXP_058 ((FIXP_ONE*58)/100)
#define FIXP_059 ((FIXP_ONE*59)/100)
#define FIXP_060 ((FIXP_ONE*60)/100)
#define FIXP_061 ((FIXP_ONE*61)/100)
#define FIXP_062 ((FIXP_ONE*62)/100)
#define FIXP_063 ((FIXP_ONE*63)/100)
#define FIXP_064 ((FIXP_ONE*64)/100)
#define FIXP_065 ((FIXP_ONE*65)/100)
#define FIXP_066 ((FIXP_ONE*66)/100)
#define FIXP_067 ((FIXP_ONE*67)/100)
#define FIXP_068 ((FIXP_ONE*68)/100)
#define FIXP_069 ((FIXP_ONE*69)/100)
#define FIXP_070 ((FIXP_ONE*70)/100)
#define FIXP_071 ((FIXP_ONE*71)/100)
#define FIXP_072 ((FIXP_ONE*72)/100)
#define FIXP_073 ((FIXP_ONE*73)/100)
#define FIXP_074 ((FIXP_ONE*74)/100)
#define FIXP_075 ((FIXP_ONE*75)/100)
#define FIXP_076 ((FIXP_ONE*76)/100)
#define FIXP_077 ((FIXP_ONE*77)/100)
#define FIXP_078 ((FIXP_ONE*78)/100)
#define FIXP_079 ((FIXP_ONE*79)/100)
#define FIXP_080 ((FIXP_ONE*80)/100)
#define FIXP_081 ((FIXP_ONE*81)/100)
#define FIXP_082 ((FIXP_ONE*82)/100)
#define FIXP_083 ((FIXP_ONE*83)/100)
#define FIXP_084 ((FIXP_ONE*84)/100)
#define FIXP_085 ((FIXP_ONE*85)/100)
#define FIXP_086 ((FIXP_ONE*86)/100)
#define FIXP_087 ((FIXP_ONE*87)/100)
#define FIXP_088 ((FIXP_ONE*88)/100)
#define FIXP_089 ((FIXP_ONE*89)/100)
#define FIXP_090 ((FIXP_ONE*90)/100)
#define FIXP_091 ((FIXP_ONE*91)/100)
#define FIXP_092 ((FIXP_ONE*92)/100)
#define FIXP_093 ((FIXP_ONE*93)/100)
#define FIXP_094 ((FIXP_ONE*94)/100)
#define FIXP_095 ((FIXP_ONE*95)/100)
#define FIXP_096 ((FIXP_ONE*96)/100)
#define FIXP_097 ((FIXP_ONE*97)/100)
#define FIXP_098 ((FIXP_ONE*98)/100)
#define FIXP_099 ((FIXP_ONE*99)/100)
#define FIXP_1     FIXP_ONE
#define FIXP_1_1 ((FIXP_ONE*11)/10)
#define FIXP_1_2 ((FIXP_ONE*12)/10)
#define FIXP_1_3 ((FIXP_ONE*13)/10)
#define FIXP_1_4 ((FIXP_ONE*14)/10)
#define FIXP_1_5 ((FIXP_ONE*15)/10)
#define FIXP_1_6 ((FIXP_ONE*16)/10)
#define FIXP_1_7 ((FIXP_ONE*17)/10)
#define FIXP_1_8 ((FIXP_ONE*18)/10)
#define FIXP_1_9 ((FIXP_ONE*19)/10)
#define FIXP_2   ((FIXP_ONE*20)/10)
#define FIXP_2_1 ((FIXP_ONE*21)/10)
#define FIXP_2_2 ((FIXP_ONE*22)/10)
#define FIXP_2_3 ((FIXP_ONE*23)/10)
#define FIXP_2_4 ((FIXP_ONE*24)/10)
#define FIXP_2_5 ((FIXP_ONE*25)/10)
#define FIXP_2_6 ((FIXP_ONE*26)/10)
#define FIXP_2_7 ((FIXP_ONE*27)/10)
#define FIXP_2_8 ((FIXP_ONE*28)/10)
#define FIXP_2_9 ((FIXP_ONE*29)/10)
#define FIXP_3   ((FIXP_ONE*30)/10)
#define FIXP_3_1 ((FIXP_ONE*31)/10)
#define FIXP_3_2 ((FIXP_ONE*32)/10)
#define FIXP_3_3 ((FIXP_ONE*33)/10)
#define FIXP_3_4 ((FIXP_ONE*34)/10)
#define FIXP_3_5 ((FIXP_ONE*35)/10)
#define FIXP_3_6 ((FIXP_ONE*36)/10)
#define FIXP_3_7 ((FIXP_ONE*37)/10)
#define FIXP_3_8 ((FIXP_ONE*38)/10)
#define FIXP_3_9 ((FIXP_ONE*39)/10)
#define FIXP_4   ((FIXP_ONE*40)/10)
#define FIXP_4_1 ((FIXP_ONE*41)/10)
#define FIXP_4_2 ((FIXP_ONE*42)/10)
#define FIXP_4_3 ((FIXP_ONE*43)/10)
#define FIXP_4_4 ((FIXP_ONE*44)/10)
#define FIXP_4_5 ((FIXP_ONE*45)/10)
#define FIXP_4_6 ((FIXP_ONE*46)/10)
#define FIXP_4_7 ((FIXP_ONE*47)/10)
#define FIXP_4_8 ((FIXP_ONE*48)/10)
#define FIXP_4_9 ((FIXP_ONE*49)/10)
#define FIXP_5   ((FIXP_ONE*50)/10)
#define FIXP_5_1 ((FIXP_ONE*51)/10)
#define FIXP_5_2 ((FIXP_ONE*52)/10)
#define FIXP_5_3 ((FIXP_ONE*53)/10)
#define FIXP_5_4 ((FIXP_ONE*54)/10)
#define FIXP_5_5 ((FIXP_ONE*55)/10)
#define FIXP_5_6 ((FIXP_ONE*56)/10)
#define FIXP_5_7 ((FIXP_ONE*57)/10)
#define FIXP_5_8 ((FIXP_ONE*58)/10)
#define FIXP_5_9 ((FIXP_ONE*59)/10)
#define FIXP_6   ((FIXP_ONE*60)/10)
#define FIXP_6_1 ((FIXP_ONE*61)/10)
#define FIXP_6_2 ((FIXP_ONE*62)/10)
#define FIXP_6_3 ((FIXP_ONE*63)/10)
#define FIXP_6_4 ((FIXP_ONE*64)/10)
#define FIXP_6_5 ((FIXP_ONE*65)/10)
#define FIXP_6_6 ((FIXP_ONE*66)/10)
#define FIXP_6_7 ((FIXP_ONE*67)/10)
#define FIXP_6_8 ((FIXP_ONE*68)/10)
#define FIXP_6_9 ((FIXP_ONE*69)/10)
#define FIXP_7   ((FIXP_ONE*70)/10)
#define FIXP_7_1 ((FIXP_ONE*71)/10)
#define FIXP_7_2 ((FIXP_ONE*72)/10)
#define FIXP_7_3 ((FIXP_ONE*73)/10)
#define FIXP_7_4 ((FIXP_ONE*74)/10)
#define FIXP_7_5 ((FIXP_ONE*75)/10)
#define FIXP_7_6 ((FIXP_ONE*76)/10)
#define FIXP_7_7 ((FIXP_ONE*77)/10)
#define FIXP_7_8 ((FIXP_ONE*78)/10)
#define FIXP_7_9 ((FIXP_ONE*79)/10)
#define FIXP_8   ((FIXP_ONE*80)/10)
#define FIXP_8_1 ((FIXP_ONE*81)/10)
#define FIXP_8_2 ((FIXP_ONE*82)/10)
#define FIXP_8_3 ((FIXP_ONE*83)/10)
#define FIXP_8_4 ((FIXP_ONE*84)/10)
#define FIXP_8_5 ((FIXP_ONE*85)/10)
#define FIXP_8_6 ((FIXP_ONE*86)/10)
#define FIXP_8_7 ((FIXP_ONE*87)/10)
#define FIXP_8_8 ((FIXP_ONE*88)/10)
#define FIXP_8_9 ((FIXP_ONE*89)/10)
#define FIXP_9   ((FIXP_ONE*90)/10)
#define FIXP_9_1 ((FIXP_ONE*91)/10)
#define FIXP_9_2 ((FIXP_ONE*92)/10)
#define FIXP_9_3 ((FIXP_ONE*93)/10)
#define FIXP_9_4 ((FIXP_ONE*94)/10)
#define FIXP_9_5 ((FIXP_ONE*95)/10)
#define FIXP_9_6 ((FIXP_ONE*96)/10)
#define FIXP_9_7 ((FIXP_ONE*97)/10)
#define FIXP_9_8 ((FIXP_ONE*98)/10)
#define FIXP_9_9 ((FIXP_ONE*99)/10)
#define FIXP_10   (FIXP_ONE*10)

// use for constants, not for code math
#define F(x) ((x)*FIXP_ONE)

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
