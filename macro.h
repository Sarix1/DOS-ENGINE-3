#ifndef MACRO_H
#define MACRO_H

#define S(x)            #x      
#define SELF(x)         x

#define IIF(cond)       IIF_ ## cond
#define IIF_0(t, f)     f
#define IIF_1(t, f)     t

#define CAT(a,b)        CAT_(a,b)
#define CAT_(a,b)       a##b
#define CAT3(a,b,c)     CAT3_(a,b,c)
#define CAT3_(a,b,c)    a##b##c

#define EMPTY()
#define NONE_ EMPTY()
#define _NONE EMPTY()
#define FORMAT_TOKEN(pre,x,suf) CAT3(CAT(pre, _), x, CAT(_, suf))

#define wrap(x,max)         if ((x)<0||(x)>=(max))  (x)=0
#define wrapEnd(x,max)      if ((x)>=(max))         (x)=0
#define wrapStart(x,max)    if ((x)<0)              (x)=(max)-1   
#define incAndWrap(x,max)   if (++(x)>=(max))       (x)=0
#define decAndWrap(x,max)   if (--(x)<0)            (x)=(max)-1

#define rWrap(x,max)        ((x)>=(max)||(x)<0) ? 0:(x)
#define rWrapEnd(x,max)     ((x)>=(max)) ? 0:(x)
#define rWrapStart(x,max)   ((x)<0) ? (max)-1:(x)
#define rIncAndWrap(x,max)  ((x)+1>=(max)) ? 0:(x)+1
#define rDecAndWrap(x,max)  ((x)-1<0) ? (max)-1:(x)-1

#define MIN(a,b)            (((a) < (b)) ? (a) : (b))
#define MAX(a,b)            (((a) > (b)) ? (a) : (b))
#define MIN3(a,b,c)         (MIN(MIN((a), (b)), (c)))
#define MAX3(a,b,c)         (MAX(MAX((a), (b)), (c)))
#define SIGN(x)             (((x) < 0) ? -1 : (((x) > 0) ? 1 : 0))
#define SAME_SIGNS(a,b)     (((int32_t)((uint32_t)(a) ^ (uint32_t)(b))) >= 0)
#define ABS(x)              (((x) < 0) ? -(x) : (x))
#define XOR(a,b)            (!(a) != !(b))
#define MUL_PI(x)           (((x)*355L)/113)
#define DIV_PI(x)           (((x)*113L)/355)

#define BIT(x)              (1<<(x))
#define LOW_BYTE(n)         ((n) & 0x00ff)
#define HIGH_BYTE(n)        (((n)>>8) & 0x00ff)
#define SET_BITS_FROM(i)    (((i) == 8) ? 0xFFu : (1u << (i)) - 1)
#define SET_BIT_RANGE(f,to) ((SET_BITS_FROM(f)) & (~SET_BITS_FROM(to)))

#define LOWEST_SET_BIT2(x)  ((x) & 0x1    ? 0 : 1)
#define LOWEST_SET_BIT4(x)  ((x) & 0x3    ? LOWEST_SET_BIT2(x)  : 2  + LOWEST_SET_BIT2((x) >> 2))
#define LOWEST_SET_BIT8(x)  ((x) & 0xF    ? LOWEST_SET_BIT4(x)  : 4  + LOWEST_SET_BIT4((x) >> 4))
#define LOWEST_SET_BIT16(x) ((x) & 0xFF   ? LOWEST_SET_BIT8(x)  : 8  + LOWEST_SET_BIT8((x) >> 8))
#define LOWEST_SET_BIT32(x) ((x) & 0xFFFF ? LOWEST_SET_BIT16(x) : 16 + LOWEST_SET_BIT16((x) >> 16))
#define LOWEST_SET_BIT(x)   LOWEST_SET_BIT32(x)

#define SAFE_CALL(f)    if ((f) != NULL) (f)()

#if DEBUG_ASSERT == 1
#include <stdio.h>

// evaluate expression; exit on false
#define ASSERT(exp) \
    if (!(exp)) { \
        fprintf(stderr, "%s:%d: assert failure\n", __FILE__, __LINE__); \
        fprintf(stderr, "%s\n", #exp); \
        exit(); }

// evaluate expression; infinite loop on false
#define ASSERT_L(exp) \
    if (!(exp)) { \
        fprintf(stderr, "%s:%d: assert failure\n", __FILE__, __LINE__); \
        fprintf(stderr, "%s\n", #exp); \
        while(1); }

// evaluate A op B, print their values as (long) and exit on false
#define ASSERT_AB(a,op,b) \
    if (!((a) op (b))) { \
        fprintf(stderr, "%s:%d: assert failure\n", __FILE__, __LINE__); \
        fprintf(stderr, "%s %s %s\n%ld %s %ld\n" \
            #a, #op, #b, (long)(a), #op, (long)(b)); \
        exit(); }

// evaluate A op B, print their values as (long) and infinite loop on false
#define ASSERT_AB_L(a,op,b) \
    if (!((a) op (b))) { \
        fprintf(stderr, "%s:%d: assert failure\n", __FILE__, __LINE__); \
        fprintf(stderr, "%s %s %s\n%ld %s %ld\n" \
            #a, #op, #b, (long)(a), #op, (long)(b)); \
        while(1); }

#else
#define ASSERT(exp)     
#define ASSERT_R(exp,r)   
#define ASSERT_L(exp)   
#define ASSERT_LR(exp,r)   
#endif

#endif/* MACRO_H */
