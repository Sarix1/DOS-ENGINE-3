#include "common.h"
#include "vid_def.h"
#include "maths.h"
#include "maths2.h"

// to-do:
// fixed point versions of intersection functions
// intersection detection without finding the point
// vec3 variants of all vec2 functions
// int64_sqrt

int32_t int32_sqrt(int32_t x)
{
    if (x == 0)
        return 0;
    else
    {
        register uint32_t rem = x;
        register uint32_t bit = 0x40000000;
        register uint32_t root = 0;

        while (bit >= 256)
        {
            register uint32_t temp = root+bit;
            root >>= 1; //root/2
            if (rem >= temp)
            {
                rem = rem-temp;
                root += bit;
            }
            bit >>= 2; //bit/4
        }
        return (int32_t)root;
    }
}

fix16_16 int32toFix16_16_sqrt(int32_t x)
{
    if (x == 0)
        return 0;
    else
    {
        register uint32_t bit  = 0x40000000;
        register uint32_t rem  = x;
        register uint32_t root = 0;

        while (bit > 0)
        {
            register uint32_t temp = root+bit;
            if (rem >= temp)
            {
                rem -= temp;
                root = temp+bit;
            }
            rem <<= 1;
            bit >>= 1;
        }
        if (rem > root)
            root++;

        return (fix16_16)root;
    }
}

fix16_16 fix16_16_sqrt(fix16_16 x)
{
    if (x == 0)
        return 0;
    else
    {
        register uint32_t bit  = 0x40000000;
        register uint32_t rem  = x;
        register uint32_t root = 0;

        while (bit > 0x40)
        {
            register uint32_t temp = root+bit;
            if (rem >= temp)
            {
                rem -= temp;
                root = temp+bit;
            }
            rem <<= 1;
            bit >>= 1;
        }
        root >>= 8;

        return root;
    }
}

fixp fixpSin(brad angle)
{
    // mirror 90-180 and 270-360
    if (angle & DEG_90)
        angle ^= DEG_90_MASK;
    // negate value for downwards angle
    if (angle & DEG_180)
    {
        angle = (angle & DEG_90_MASK) >> (BRAD_SHIFT-SIN_TABLE_SHIFT-2);

        return -(fixp)(SinTable[angle] << (FIX_SHIFT-SIN_SHIFT));
    }
    angle = (angle & DEG_90_MASK) >> (BRAD_SHIFT-SIN_TABLE_SHIFT-2);

    return (fixp)(SinTable[angle] << (FIX_SHIFT-SIN_SHIFT));
}

fixp fixpSinAcos(fixp x) // this could be inlined, but needs access to the table
{
    return SinAcosTable[(x >> (FIX_SHIFT-SIN_ACOS_TABLE_SHIFT)) & FIX_FRAC_MASK];
}

Vec2 vec2rot(Vec2 v, brad angle)
{
    Vec2 u;
    const int64_t sini = fixpSin(angle);
    const int64_t cosi = fixpCos(angle);
    u.x = (cosi*v.x + sini*v.y) >> FIX_SHIFT;
    u.y = -(cosi*v.y - sini*v.x) >> FIX_SHIFT;

    return u;
}

Vec2 vec2rotV(Vec2 v, Vec2 dir)
{
    Vec2 u;
    u.x = ((int64_t)dir.x*v.x + (int64_t)dir.y*v.y) >> FIX_SHIFT;
    u.y = -((int64_t)dir.x*v.y - (int64_t)dir.y*v.x) >> FIX_SHIFT;

    return u;
}

void vecs2rot(Vec2* dest, Vec2* src, int num_vecs, brad angle)
{
    Vec2 v;
    int i;
    const int64_t sini = fixpSin(angle);
    const int64_t cosi = fixpCos(angle);

    for (i=0; i<num_vecs; i++)
    {
        v = src[i];
        dest[i].x = (cosi*v.x + sini*v.y) >> FIX_SHIFT;
        dest[i].y = -(cosi*v.y - sini*v.x) >> FIX_SHIFT;
    }
}

void vecs2rotV(Vec2* dest, Vec2* src, int num_vecs, Vec2 dir)
{
    Vec2 v;
    int i;

    for (i=0; i<num_vecs; i++)
    {
        v = src[i];
        dest[i].x = ((int64_t)dir.x*v.x + (int64_t)dir.y*v.y) >> FIX_SHIFT;
        dest[i].y = -((int64_t)dir.x*v.y - (int64_t)dir.y*v.x) >> FIX_SHIFT;
    }
}

void vecs2scale(Vec2* dest, Vec2* src, int num_vecs, fixp scale)
{
    int i;
    for (i=0; i<num_vecs; i++)
        dest[i] = vec2scale(src[i], scale);
}

Vec2 vec2scaleRot(Vec2 v, fixp scale, brad angle)
{
    Vec2 u;
    const int64_t sini = fixpSin(angle);
    const int64_t cosi = fixpCos(angle);
    u.x = ((int64_t)scale * (cosi*v.x + sini*v.y)) >> (FIX_SHIFT*2);
    u.y = -((int64_t)scale * (cosi*v.y - sini*v.x)) >> (FIX_SHIFT*2);

    return u;
}

// has separate multiplications and divisions to prevent overflow
Vec2 vec2scaleRot_safe(Vec2 v, fixp scale, brad angle)
{
    Vec2 u;
    const int64_t sini = fixpSin(angle);
    const int64_t cosi = fixpCos(angle);
    v.x = ((uint64_t)v.x*scale) >> FIX_SHIFT;
    v.y = ((uint64_t)v.y*scale) >> FIX_SHIFT;
    u.x = (cosi*v.x + sini*v.y) >> FIX_SHIFT;
    u.y = -(cosi*v.y - sini*v.x) >> FIX_SHIFT;

    return u;
}

Vec2 vec2scaleRotV(Vec2 v, fixp scale, Vec2 dir)
{
    Vec2 u;
    u.x = ((int64_t)scale * ((int64_t)dir.x*v.x + (int64_t)dir.y*v.y)) >> (FIX_SHIFT*2);
    u.y = -((int64_t)scale * ((int64_t)dir.x*v.y - (int64_t)dir.y*v.x)) >> (FIX_SHIFT*2);

    return u;
}

// has separate multiplications and divisions to prevent overflow
Vec2 vec2scaleRotV_safe(Vec2 v, fixp scale, Vec2 dir)
{
    Vec2 u;
    v.x = ((uint64_t)v.x*scale) >> FIX_SHIFT;
    v.y = ((uint64_t)v.y*scale) >> FIX_SHIFT;
    u.x = ((int64_t)dir.x*v.x + (int64_t)dir.y*v.y) >> FIX_SHIFT;
    u.y = -((int64_t)dir.x*v.y - (int64_t)dir.y*v.x) >> FIX_SHIFT;

    return u;
}

void vecs2scaleRot(Vec2* dest, Vec2* src, int num_vecs, fixp scale, brad angle)
{
    int i;
    for (i=0; i<num_vecs; i++)
        dest[i] = vec2scaleRot(src[i], scale, angle);
}

// has separate multiplications and divisions to prevent overflow
void vecs2scaleRot_safe(Vec2* dest, Vec2* src, int num_vecs, fixp scale, brad angle)
{
    int i;
    for (i=0; i<num_vecs; i++)
        dest[i] = vec2scaleRot_safe(src[i], scale, angle);
}


void vecs2scaleRotV(Vec2* dest, Vec2* src, int num_vecs, fixp scale, Vec2 dir)
{
    int i;
    for (i=0; i<num_vecs; i++)
        dest[i] = vec2scaleRotV(src[i], scale, dir);
}

// has separate multiplications and divisions to prevent overflow
void vecs2scaleRotV_safe(Vec2* dest, Vec2* src, int num_vecs, fixp scale, Vec2 dir)
{
    int i;
    for (i=0; i<num_vecs; i++)
        dest[i] = vec2scaleRotV_safe(src[i], scale, dir);
}

Vec2 vec2proj(Vec2 v, Vec2 u)
{
    Vec2 p;
    const int64_t num = (int64_t)u.x*v.x + (int64_t)u.y*v.y;
    const int64_t denom = (int64_t)v.x*v.x + (int64_t)v.y*v.y;
    p.x = (v.x*num)/denom;
    p.y = (v.y*num)/denom;

    return p;
}

Vec2 vec2projOff(Vec2 offset, Vec2 v, Vec2 u)
{
    Vec2 p;
    const int64_t vx = v.x - offset.x;
    const int64_t vy = v.y - offset.y;
    const int64_t ux = u.x - offset.x;
    const int64_t uy = u.y - offset.y;
    const int64_t num = ux*vx + uy*vy;
    const int64_t denom = vx*vx + vy*vy;
    p.x = (vx*num)/denom + offset.x;
    p.y = (vy*num)/denom + offset.y;

    return p;
}

Vec2 vec2fixpProj(Vec2 v, Vec2 u)
{
    Vec2 p;
    const int64_t num = ((int64_t)u.x*v.x + (int64_t)u.y*v.y) >> FIX_SHIFT;
    const int64_t denom = ((int64_t)v.x*v.x + (int64_t)v.y*v.y) >> FIX_SHIFT;
    p.x = (v.x*num)/denom;
    p.y = (v.y*num)/denom;

    return p;
}

Vec2 vec2fixpProjOff(Vec2 offset, Vec2 v, Vec2 u)
{
    Vec2 p;
    const int64_t vx = v.x - offset.x;
    const int64_t vy = v.y - offset.y;
    const int64_t ux = u.x - offset.x;
    const int64_t uy = u.y - offset.y;
    const int64_t num = (ux*vx + uy*vy) >> FIX_SHIFT;
    const int64_t denom = (vx*vx + vy*vy) >> FIX_SHIFT;
    p.x = (vx*num)/denom + offset.x;
    p.y = (vy*num)/denom + offset.y;

    return p;
}

int lineLineIntersect(Vec2 p0, Vec2 p1, Vec2 p2, Vec2 p3, Vec2* intersect)
{
    const int64_t a1 = p1.y-p0.y;
    const int64_t a2 = p3.y-p2.y;
    const int64_t b1 = p0.x-p1.x;
    const int64_t b2 = p2.x-p3.x;
    const int64_t c1 = a1*p0.x + b1*p0.y;
    const int64_t c2 = a2*p2.x + b2*p2.y;
    const int64_t denom = a1*b2 - a2*b1;
    // detect parallel or collinear lines
    if (denom == 0)
        return DONT_INTERSECT;
    // line intersection point
    // +denom/2 fixes integer rounding error
    intersect->x = ((b2*c1 - b1*c2) + denom/2) / denom;
    intersect->y = ((a1*c2 - a2*c1) + denom/2) / denom;

    return DO_INTERSECT;
}

int segSegIntersect(Vec2 p0, Vec2 p1, Vec2 p2, Vec2 p3, Vec2* intersect)
{
    const int32_t a1    = p1.y-p0.y;
    const int32_t a2    = p3.y-p2.y;
    const int32_t b1    = p0.x-p1.x;
    const int32_t b2    = p2.x-p3.x;
    const int64_t c1    = (int64_t)a1*p0.x + (int64_t)b1*p0.y;
    const int64_t c2    = (int64_t)a2*p2.x + (int64_t)b2*p2.y;
    const int64_t denom = (int64_t)a1*b2 - (int64_t)a2*b1;
    int32_t ix, iy, dx_sign, dy_sign;
    // detect parallel or collinear lines
    if (denom == 0)
        return DONT_INTERSECT;
    // line intersection point
    // +denom/2 fixes integer rounding error
    intersect->x = ix = ((b2*c1 - b1*c2) + denom/2) / denom;
    intersect->y = iy = ((a1*c2 - a2*c1) + denom/2) / denom;
    // point not on segment p0-->p1?
    if (b1)
    {
        dx_sign = (int32_t)(ix-p1.x) ^ (int32_t)(p0.x-p1.x);
        if (dx_sign < 0 || ABS(ix-p1.x) > ABS(b1))
            return DONT_INTERSECT;
    }
    else
    {
        dy_sign = (int32_t)(iy-p1.y) ^ (int32_t)(p0.y-p1.y);
        if (dy_sign < 0 || ABS(iy-p1.y) > ABS(a1))
            return DONT_INTERSECT;
    }
    // point not on segment p2-->p3?
    if (b2)
    {
        dx_sign = (int32_t)(ix-p3.x) ^ (int32_t)(p2.x-p3.x);
        if (dx_sign < 0 || ABS(ix-p3.x) > ABS(b2))
            return DONT_INTERSECT;
    }
    else
    {
        dy_sign = (int32_t)(iy-p3.y) ^ (int32_t)(p2.y-p3.y);
        if (dy_sign < 0 || ABS(iy-p3.y) > ABS(a2))
            return DONT_INTERSECT;
    }

    return DO_INTERSECT;
}

int lineSegIntersect(Vec2 l0, Vec2 l1, Vec2 s0, Vec2 s1, Vec2* intersect)
{
    const int32_t a1 = l1.y-l0.y;
    const int32_t a2 = s1.y-s0.y;
    const int32_t b1 = l0.x-l1.x;
    const int32_t b2 = s0.x-s1.x;
    const int64_t c1 = (int64_t)a1*l0.x + (int64_t)b1*l0.y;
    const int64_t c2 = (int64_t)a2*s0.x + (int64_t)b2*s0.y;
    const int64_t denom = (int64_t)a1*b2 - (int64_t)a2*b1;
    int32_t ix, iy, dx_sign, dy_sign;
    // detect parallel or collinear
    if (denom == 0)
        return DONT_INTERSECT;
    // line intersection point
    // +denom/2 fixes integer rounding error
    intersect->x = ix = ((b2*c1 - b1*c2) + denom/2) / denom;
    intersect->y = iy = ((a1*c2 - a2*c1) + denom/2) / denom;
    // point not on segment p2-->p3?
    if (b2)
    {
        dx_sign = (int32_t)(ix-s1.x) ^ (int32_t)(s0.x-s1.x);
        if (dx_sign < 0 || ABS(ix-s1.x) > ABS(b2))
            return DONT_INTERSECT;
    }
    else
    {
        dy_sign = (int32_t)(iy-s1.y) ^ (int32_t)(s0.y-s1.y);
        if (dy_sign < 0 || ABS(iy-s1.y) > ABS(a2))
            return DONT_INTERSECT;
    }

    return DO_INTERSECT;
}

int raySegIntersect(Vec2 r0, Vec2 r1, Vec2 s0, Vec2 s1, Vec2* intersect)
{
    const int32_t a1 = r1.y-r0.y;
    const int32_t a2 = s1.y-s0.y;
    const int32_t b1 = r0.x-r1.x;
    const int32_t b2 = s0.x-s1.x;
    const int64_t c1 = (int64_t)a1*r0.x + (int64_t)b1*r0.y;
    const int64_t c2 = (int64_t)a2*s0.x + (int64_t)b2*s0.y;
    const int64_t denom = (int64_t)a1*b2 - (int64_t)a2*b1;
    int32_t ix, iy, dx_sign, dy_sign;
    // detect parallel or collinear
    if (denom == 0)
        return DONT_INTERSECT;
    // line intersection point
    // +denom/2 fixes integer rounding error
    intersect->x = ix = ((b2*c1 - b1*c2) + denom/2) / denom;
    intersect->y = iy = ((a1*c2 - a2*c1) + denom/2) / denom;
    // point not on ray p0-->p1?
    if (b1 && (r0.x < ix && r0.x > r1.x || r0.x > ix && r0.x < r1.x))
        return DONT_INTERSECT;
    else if (r0.y < iy && r0.y > r1.y || r0.y > iy && r0.y < r1.y)
        return DONT_INTERSECT;

    // point not on segment p2-->p3?
    if (b2)
    {
        dx_sign = (int32_t)(ix-s1.x) ^ (int32_t)(s0.x-s1.x);
        if (dx_sign < 0 || ABS(ix-s1.x) > ABS(b2))
            return DONT_INTERSECT;
    }
    else
    {
        dy_sign = (int32_t)(iy-s1.y) ^ (int32_t)(s0.y-s1.y);
        if (dy_sign < 0 || ABS(iy-s1.y) > ABS(a2))
            return DONT_INTERSECT;
    }

    return DO_INTERSECT;
}

int rayLineIntersect(Vec2 r0, Vec2 r1, Vec2 l0, Vec2 l1, Vec2* intersect)
{
    const int32_t a1 = r1.y - r0.y;
    const int32_t a2 = l1.y - l0.y;
    const int32_t b1 = r0.x - r1.x;
    const int32_t b2 = l0.x - l1.x;
    const int64_t c1 = (int64_t)a1*r0.x + (int64_t)b1*r0.y;
    const int64_t c2 = (int64_t)a2*l0.x + (int64_t)b2*l0.y;
    const int64_t denom = (int64_t)a1*b2 - (int64_t)a2*b1;
    int32_t ix, iy;
    // detect parallel or collinear
    if (denom == 0)
        return DONT_INTERSECT;
    // line intersection point
    // +denom/2 fixes integer rounding error
    intersect->x = ix = ((b2*c1 - b1*c2) + denom/2) / denom;
    intersect->y = iy = ((a1*c2 - a2*c1) + denom/2) / denom;
    // point not on ray p0-->p1?
    if (b1 && (r0.x < ix && r0.x > r1.x || r0.x > ix && r0.x < r1.x))
        return DONT_INTERSECT;
    else if (r0.y < iy && r0.y > r1.y || r0.y > iy && r0.y < r1.y)
        return DONT_INTERSECT;

    return DO_INTERSECT;
}

int rayRayIntersect(Vec2 p0, Vec2 p1, Vec2 p2, Vec2 p3, Vec2* intersect)
{
    const int32_t a1 = p1.y-p0.y;
    const int32_t a2 = p3.y-p2.y;
    const int32_t b1 = p0.x-p1.x;
    const int32_t b2 = p2.x-p3.x;
    const int64_t c1 = (int64_t)a1*p0.x + (int64_t)b1*p0.y;
    const int64_t c2 = (int64_t)a2*p2.x + (int64_t)b2*p2.y;
    const int64_t denom = (int64_t)a1*b2 - (int64_t)a2*b1;
    int32_t ix, iy;
    // detect parallel or collinear
    if (denom == 0)
        return DONT_INTERSECT;
    // line intersection point
    // +denom/2 fixes integer rounding error
    intersect->x = ix = ((b2*c1 - b1*c2) + denom/2) / denom;
    intersect->y = iy = ((a1*c2 - a2*c1) + denom/2) / denom;
    // point not on ray p0-->p1?
    if (b1 && (p0.x < ix && p0.x > p1.x || p0.x > ix && p0.x < p1.x))
        return DONT_INTERSECT;
    else if (p0.y < iy && p0.y > p1.y || p0.y > iy && p0.y < p1.y)
        return DONT_INTERSECT;
    // point not on ray p2-->p3?
    if (b1 && (p2.x < ix && p2.x > p3.x || p2.x > ix && p2.x < p3.x))
        return DONT_INTERSECT;
    else if (p2.y < iy && p2.y > p3.y || p2.y > iy && p2.y < p3.y)
        return DONT_INTERSECT;

    return DO_INTERSECT;
}

int lineCircleIntersect(Vec2 p0, Vec2 p1, Vec2 circle, int64_t r_squared)
{
    Vec2 p = vec2projOff(circle, p0, p1);
    int64_t d_squared = vec2distSquare(p, circle);

    if (d_squared < r_squared)
        return DO_INTERSECT;
    
    return DONT_INTERSECT;
}

int rayCircleIntersect(Vec2 a, Vec2 b, Vec2 circle, int32_t r_squared)
{
    ;
}

int segCircleIntersect(Vec2 a, Vec2 b, Vec2 circle, int32_t r_squared)
{
    ;
}

byte pointInScreen(int x, int y)
{
    byte outcode = OUTCODE_INSIDE;

    if      (x < 0)              outcode |= OUTCODE_LEFT;
    else if (x >= SCREEN_WIDTH)  outcode |= OUTCODE_RIGHT;
    if      (y < 0)              outcode |= OUTCODE_TOP;
    else if (y >= SCREEN_HEIGHT) outcode |= OUTCODE_BOTTOM;

    return outcode;
}

int clipLineToScreen(Vec2* p0, Vec2* p1)
{
    int32_t x, y, dx, dy;
    int32_t ax = p0->x;
    int32_t ay = p0->y;
    int32_t bx = p1->x;
    int32_t by = p1->y;
    byte outcode;
    byte outcode0 = pointInScreen(ax, ay);
    byte outcode1 = pointInScreen(bx, by);

    while (1)
    {
        if ((outcode0 | outcode1) == OUTCODE_INSIDE)
            return DO_INTERSECT;
        else if ((outcode0 & outcode1) != OUTCODE_INSIDE)
            return DONT_INTERSECT;
        else
        {
            outcode = MAX(outcode0, outcode1);
            dx = bx-ax;
            dy = by-ay;

            if (outcode & OUTCODE_LEFT)
            {
                y = ay + (-ax*dy + dx/2) / dx;
                x = 0;
            }
            else if (outcode & OUTCODE_RIGHT)
            {
                y = ay + ((SCREEN_WIDTH-ax)*dy + dx/2) / dx;
                x = SCREEN_WIDTH-1;
            }
            else if (outcode & OUTCODE_TOP)
            {
                x = ax + (-ay*dx + dy/2) / dy;
                y = 0;
            }
            else if (outcode & OUTCODE_BOTTOM)
            {
                x = ax + ((SCREEN_HEIGHT-ay)*dx + dy/2) / dy;
                y = SCREEN_HEIGHT-1;
            }

            if (outcode == outcode0)
            {
                p0->x = ax = x;
                p0->y = ay = y;
                outcode0 = pointInScreen(ax, ay);
            }
            else
            {
                p1->x = bx = x;
                p1->y = by = y;
                outcode1 = pointInScreen(bx, by);
            }
        }
    }
}
