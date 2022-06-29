#ifndef MATHS_H
#define MATHS_H

#include "math_def.h"
#include "math_typ.h"

//externs
extern const uint16_t SinTable[SIN_TABLE_SIZE];
extern const uint16_t SinAcosTable[SIN_ACOS_TABLE_SIZE];

int32_t  int32_sqrt          (int32_t x);
//int32_t  int64_sqrt          (int64_t x);
fix16_16 int32toFix16_16_sqrt(int32_t x);
fix16_16 fix16_16_sqrt       (fix16_16 x);
fixp    fixpSin              (brad angle);
fixp    fixpSinAcos          (fixp x) ;

Vec2 vec2rot            (Vec2 v, brad angle);
Vec2 vec2rotV           (Vec2 v, Vec2 dir);
void vecs2rot           (Vec2* dest, Vec2* src, int num_vecs, brad angle);
void vecs2rotV          (Vec2* dest, Vec2* src, int num_vecs, Vec2 dir);
void vecs2scale         (Vec2* dest, Vec2* src, int num_vecs, fixp scale);
Vec2 vec2scaleRot       (Vec2 v, fixp scale, brad angle);
Vec2 vec2scaleRotV      (Vec2 v, fixp scale, Vec2 dir);
Vec2 vec2scaleRot_safe  (Vec2 v, fixp scale, brad angle);
Vec2 vec2scaleRotV_safe (Vec2 v, fixp scale, Vec2 dir);
void vecs2scaleRot      (Vec2* dest, Vec2* src, int num_vecs, fixp scale, brad angle);
void vecs2scaleRotV     (Vec2* dest, Vec2* src, int num_vecs, fixp scale, Vec2 dir);
void vecs2scaleRot_safe (Vec2* dest, Vec2* src, int num_vecs, fixp scale, brad angle);
void vecs2scaleRotV_safe(Vec2* dest, Vec2* src, int num_vecs, fixp scale, Vec2 dir);
Vec2 vec2proj           (Vec2 u, Vec2 v);
Vec2 vec2projOff        (Vec2 offset, Vec2 v, Vec2 u);
Vec2 vec2fixpProj       (Vec2 v, Vec2 u);
Vec2 vec2fixpProjOff    (Vec2 offset, Vec2 v, Vec2 u);

int lineCircleIntersect (Vec2 p0, Vec2 p1, Vec2 circle, int64_t r_squared);
int clipLineToScreen    (Vec2* p0, Vec2* p1);
int lineLineIntersect   (Vec2 p0, Vec2 p1, Vec2 p2, Vec2 p3, Vec2* intersect);
int segSegIntersect     (Vec2 p0, Vec2 p1, Vec2 p2, Vec2 p3, Vec2* intersect);
int lineSegIntersect    (Vec2 p0, Vec2 p1, Vec2 p2, Vec2 p3, Vec2* intersect);
int raySegIntersect     (Vec2 p0, Vec2 p1, Vec2 p2, Vec2 p3, Vec2* intersect);
int rayLineIntersect    (Vec2 p0, Vec2 p1, Vec2 p2, Vec2 p3, Vec2* intersect);
int rayRayIntersect     (Vec2 p0, Vec2 p1, Vec2 p2, Vec2 p3, Vec2* intersect);

#include "maths2.h"

#endif/* MATHS_H */
