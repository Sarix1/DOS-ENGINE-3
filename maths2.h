#ifndef MATHS2_H
#define MATHS2_H

#include "common.h"
#include "math_def.h"
#include "math_typ.h"

inline int64_t square(int32_t x)
{
    return (int64_t)x*x;
}

fixp fixpSin(brad angle);
inline fixp fixpCos(brad angle)
{
    return fixpSin(angle+DEG_90);
}

inline int32_t toInt(fixp i)
{
    return (i >> FIX_SHIFT);
}

inline fixp toFixp(int i)
{
    return ((fixp)i << FIX_SHIFT);
}

inline int64_t fixpMul(fixp a, fixp b)
{
    return (((int64_t)a*b) >> FIX_SHIFT);
}

inline fixp fixpDiv(fixp num, fixp denom)
{
    return (((int64_t)num << FIX_SHIFT) / denom);
}

inline int64_t fixpSquare(fixp x)
{
    return ((int64_t)x*x) >> FIX_SHIFT;
}

fix16_16 fix16_16_sqrt(fix16_16 x);
inline fixp fixpSqrt(fixp x)
{
    return fix16_16_sqrt(x);
}

fix16_16 int32toFix16_16_sqrt(int32_t x);
inline fixp intToFixpSqrt(int32_t x)
{
    return int32toFix16_16_sqrt(x);
}

inline fixp fixpSinAcos_slow(fixp x)
{
    return fixpSqrt(FIX_ONE-fixpSquare(x));
}



inline Vec2 vec2add(Vec2 a, Vec2 b)
{
    a.x += b.x;
    a.y += b.y;
    
    return a;
}

inline Vec2 vec2add3(Vec2 a, Vec2 b, Vec2 c)
{
    a.x += b.x+c.x;
    a.y += b.y+c.y;
    
    return a;
}

inline Vec2 vec2sub(Vec2 min, Vec2 sub)
{
    min.x -= sub.x;
    min.y -= sub.y;
    
    return min;
}

inline Vec2 vec2mul(Vec2 a, Vec2 b)
{
    a.x *= b.x;
    a.y *= b.y;
    
    return a;
}

inline Vec2 vec2div(Vec2 num, Vec2 denom)
{
    num.x /= denom.x;
    num.y /= denom.y;
    
    return num;
}

inline Vec2 vec2fixpMul(Vec2 a, Vec2 b)
{
    a.x = fixpMul(a.x,b.x);
    a.y = fixpMul(a.y,b.y);
    
    return a;
}

inline Vec2 vec2fixpDiv(Vec2 a, Vec2 b)
{
    a.x = fixpDiv(a.x,b.x);
    a.y = fixpDiv(a.y,b.y);
    
    return a;
}

inline Vec2 vec2scale(Vec2 v, fixp scale)
{
    v.x = ((int64_t)v.x*scale) >> FIX_SHIFT;
    v.y = ((int64_t)v.y*scale) >> FIX_SHIFT;
    
    return v;
}

inline Vec2 vec2intToFixp(Vec2 v)
{
    v.x <<= FIX_SHIFT;
    v.y <<= FIX_SHIFT;

    return v;
}

inline Vec2 vec2fixpToInt(Vec2 v)
{
    v.x >>= FIX_SHIFT;
    v.y >>= FIX_SHIFT;

    return v;
}

inline int32_t vec2cross(Vec2 a, Vec2 b)
{
    return (a.x)*(b.y)-(a.y)*(b.x);
}

inline int32_t vec2fixpCross(Vec2 a, Vec2 b)
{
    return ((int64_t)a.x*b.y - (int64_t)a.y*b.x) >> FIX_SHIFT;
}


inline Vec3 vec3cross(Vec3 a, Vec3 b)
{
    Vec3 ab;
    ab.x = a.y*b.z - a.z*b.y; 
    ab.y = a.z*b.x - a.x*b.z; 
    ab.z = a.x*b.y - a.y*b.x; 

    return ab;
}

inline Vec3 vec3fixpCross(Vec3 a, Vec3 b)
{
    Vec3 ab;
    ab.x = ((int64_t)a.y*b.z - (int64_t)a.z*b.y) >> FIX_SHIFT; 
    ab.y = ((int64_t)a.z*b.x - (int64_t)a.x*b.z) >> FIX_SHIFT; 
    ab.z = ((int64_t)a.x*b.y - (int64_t)a.y*b.x) >> FIX_SHIFT; 

    return ab;
}

inline int32_t vec2dot(Vec2 a, Vec2 b)
{
    return (a.x*b.x) + (a.y*b.y);
}

inline fixp vec2fixpDot(Vec2 a, Vec2 b)
{
    return (fixp)(((int64_t)a.x*b.x + (int64_t)a.y*b.y) >> FIX_SHIFT);
}

inline int32_t vec3dot(Vec3 a, Vec3 b)
{
    return (a.x*b.x) + (a.y*b.y) + (a.z*b.z);
}

inline fixp vec3fixpDot(Vec3 a, Vec3 b)
{
    return (fixp)(((int64_t)a.x*b.x + (int64_t)a.y*b.y + (int64_t)a.z*b.z) >> FIX_SHIFT);
}

inline Vec2 vec2unit(brad angle)
{
    Vec2 v;
    v.x = fixpCos(angle);
    v.y = -fixpSin(angle);

    return v;
}

inline Vec2 vec2(brad angle, fixp length)
{
    Vec2 v;
    v.x = ((int64_t)fixpCos(angle) * length) >> FIX_SHIFT;
    v.y = ((int64_t)-fixpSin(angle) * length) >> FIX_SHIFT;

    return v;
}

/*
inline brad vec2angle(Vec2 v)
{
    return fixpAtan2(v.y, v.x);
}
*/

inline int64_t vec2square(Vec2 v)
{
    return ((int64_t)v.x*v.x + (int64_t)v.y*v.y);
}

int32_t int32_sqrt(int32_t x);
inline int32_t vec2Len(Vec2 v)
{
    return int32_sqrt((int64_t)v.x*v.x + (int64_t)v.y*v.y);
}

inline int32_t vec2dist(Vec2 a, Vec2 b)
{
    a.x -= b.x;
    a.y -=  b.y;

    return vec2Len(a);
}

inline int64_t vec2distSquare(Vec2 a, Vec2 b)
{
    a.x -= b.x;
    a.y -=  b.y;

    return (int64_t)a.x*a.x + (int64_t)a.y*a.y;
}

inline int64_t vec2fixpLenSquare(Vec2 v)
{
    return ((int64_t)v.x*v.x + (int64_t)v.y*v.y) >> FIX_SHIFT;
}

inline fixp vec2fixpLen(Vec2 v)
{
    return fixpSqrt(vec2fixpLenSquare(v));
}

inline fixp Vec2fixpDist(Vec2 a, Vec2 b)
{
    return vec2fixpLen(vec2sub(b,a));
}

inline fixp vec2fixpDistSquare(Vec2 a, Vec2 b)
{
    return vec2fixpLenSquare(vec2sub(b,a));
}

inline int circleCircleIntersect(Vec2 circle0, Vec2 circle1, int32_t r0, int32_t r1)
{
    return (vec2fixpDistSquare(circle0, circle1) < square(r0)+square(r1)) ? DO_INTERSECT : DONT_INTERSECT;
}

inline int circleCircleIntersectSq(Vec2 circle0, Vec2 circle1, int32_t r0_squared, int32_t r1_squared)
{
    return (vec2distSquare(circle0, circle1) < r0_squared+r1_squared) ? DO_INTERSECT : DONT_INTERSECT;
}

#endif/* MATHS2_H */
