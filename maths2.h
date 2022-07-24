#ifndef MATHS2_H
#define MATHS2_H

// inline functions

#include "common.h"
#include "math_def.h"
#include "math_typ.h"

int32_t  sqrt   (int32_t x);
fix16_16 sqrtI2F(int32_t x);
fix16_16 sqrtF2F(fix16_16 x);
fixp     fixpSin(brad angle);

inline int32_t abs(int32_t x)
{
    return (x < 0) ? -x : x;
}

inline int64_t square(int32_t x)
{
    return (int64_t)x*x;
}

inline fixp fixpCos(brad angle)
{
    return fixpSin(angle+DEG_90);
}

inline int32_t toInt(fixp i)
{
    return (i >> FIXP_SHIFT);
}

inline fixp toFixp(int32_t i)
{
    return ((fixp)i << FIXP_SHIFT);
}

inline int64_t fixpMul(fixp a, fixp b)
{
    return (((int64_t)a*b) >> FIXP_SHIFT);
}

inline fixp fixpDiv(fixp num, fixp denom)
{
    return (((int64_t)num << FIXP_SHIFT) / denom);
}

inline int64_t fixpSquare(fixp x)
{
    return ((int64_t)x*x) >> FIXP_SHIFT;
}

inline fixp fixpSqrt(fixp x)
{
    return sqrtF2F(x);
}

inline fixp intToFixpSqrt(int32_t x)
{
    return sqrtI2F(x);
}

inline fixp fixpSinAcos_slow(fixp x)
{
    return fixpSqrt(FIXP_ONE-fixpSquare(x));
}

// for printing out fractional part of fixp value
inline uint16_t fixpFracToDecimal(fixp x)
{
    x &= FIXP_FRAC_MASK;

    return (uint16_t)x;
}

// for printing out whole part of fixp value
inline int16_t fixpWholeToDecimal(fixp x)
{
    return (int)(x >> FIXP_SHIFT);
}

// for printing out a fixp value as a decimal fraction
char* fixpStr(fixp x)
{
    static char str[16];
    sprintf(str, "%d.%02u", fixpWholeToDecimal(x), fixpFracToDecimal(x));

    return str;
}

inline Vec2 newVec2(fixp x, fixp y)
{
    Vec2 v;
    v.x = x;
    v.y = y;

    return v;
}

inline Vec2 newVec2_I2F(int32_t x, int32_t y)
{
    Vec2 v;
    v.x = ((fixp)x)<<FIXP_SHIFT;
    v.y = ((fixp)y)<<FIXP_SHIFT;

    return v;
}

inline Vec2 newVec2_angle(brad angle)
{
    Vec2 v;
    v.x = fixpCos(angle);
    v.y = -fixpSin(angle);

    return v;
}

inline Vec2 newVec2_len(brad angle, fixp length)
{
    Vec2 v;
    v.x = ((int64_t)fixpCos(angle) * length) >> FIXP_SHIFT;
    v.y = ((int64_t)-fixpSin(angle) * length) >> FIXP_SHIFT;

    return v;
}

inline Vec2 vec2abs(Vec2 v)
{
    v.x = ABS(v.x);
    v.y = ABS(v.y);

    return v;
}

inline Vec2 vec2_I2F(Vec2 v)
{
    v.x <<= FIXP_SHIFT;
    v.y <<= FIXP_SHIFT;

    return v;
}

inline Vec2 vec2_F2I(Vec2 v)
{
    v.x >>= FIXP_SHIFT;
    v.y >>= FIXP_SHIFT;

    return v;
}

inline Vec2 vec2_90left(Vec2 v)
{
    Vec2 u;
    u.x = v.y;
    u.y = -v.x;

    return u;
}

inline Vec2 vec2_90right(Vec2 v)
{
    Vec2 u;
    u.x = -v.y;
    u.y = v.x;

    return u;
}

inline Vec2 vec2inv(Vec2 v)
{
    Vec2 u;
    u.x = -v.x;
    u.y = -v.y;

    return u;
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
    v.x = ((int64_t)v.x*scale) >> FIXP_SHIFT;
    v.y = ((int64_t)v.y*scale) >> FIXP_SHIFT;
    
    return v;
}

inline int32_t vec2cross(Vec2 a, Vec2 b)
{
    return (a.x)*(b.y)-(a.y)*(b.x);
}

inline int32_t vec2fixpCross(Vec2 a, Vec2 b)
{
    return ((int64_t)a.x*b.y - (int64_t)a.y*b.x) >> FIXP_SHIFT;
}

inline int32_t vec2dot(Vec2 a, Vec2 b)
{
    return (a.x*b.x) + (a.y*b.y);
}

inline fixp vec2fixpDot(Vec2 a, Vec2 b)
{
    return (fixp)(((int64_t)a.x*b.x + (int64_t)a.y*b.y) >> FIXP_SHIFT);
}

inline brad vec2angle(Vec2 v)
{
    return 0;
    //return fixpAtan2(v.y, v.x);
}

inline int64_t vec2square(Vec2 v)
{
    return ((int64_t)v.x*v.x + (int64_t)v.y*v.y);
}

inline int32_t vec2len(Vec2 v)
{
    return sqrt((int64_t)v.x*v.x + (int64_t)v.y*v.y);
}

inline int32_t vec2dist(Vec2 a, Vec2 b)
{
    a.x -= b.x;
    a.y -=  b.y;

    return vec2len(a);
}

inline int64_t vec2distSquare(Vec2 a, Vec2 b)
{
    a.x -= b.x;
    a.y -=  b.y;

    return (int64_t)a.x*a.x + (int64_t)a.y*a.y;
}

inline int64_t vec2fixpLenSquare(Vec2 v)
{
    return ((int64_t)v.x*v.x + (int64_t)v.y*v.y) >> FIXP_SHIFT;
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

inline Vec2 vec2aspect(Vec2 v)
{
    v.y = a(v.y);
    return v;
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
    ab.x = ((int64_t)a.y*b.z - (int64_t)a.z*b.y) >> FIXP_SHIFT; 
    ab.y = ((int64_t)a.z*b.x - (int64_t)a.x*b.z) >> FIXP_SHIFT; 
    ab.z = ((int64_t)a.x*b.y - (int64_t)a.y*b.x) >> FIXP_SHIFT; 

    return ab;
}

inline int32_t vec3dot(Vec3 a, Vec3 b)
{
    return (a.x*b.x) + (a.y*b.y) + (a.z*b.z);
}

inline fixp vec3fixpDot(Vec3 a, Vec3 b)
{
    return (fixp)(((int64_t)a.x*b.x + (int64_t)a.y*b.y + (int64_t)a.z*b.z) >> FIXP_SHIFT);
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