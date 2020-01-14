#ifndef CALC_H
#define CALC_H

#include <stdint.h>
#include <stdio.h>
#define ESC 0x1B
#include <LUT.h>

#define FIX14_SHIFT 14
#define FIX14_MULT(a,b) ((a)*(b) >> FIX14_SHIFT)
#define FIX14_DIV(a,b) ( ((a) << FIX14_SHIFT) / b)


struct vector_t{
        int32_t r;
        int32_t c;
};

struct ball{
    struct vector_t pos;
    struct vector_t v;
};

int16_t power(int8_t a, int8_t exp);
int32_t sinus(int16_t angle);
int32_t cosinus(int16_t angle);
void rotateVector(struct vector_t *v, int16_t grad);
void setvec(struct vector_t *v, int32_t x, int32_t y);
int32_t expand(int32_t i);
void printFix(int32_t i);
void setBall(struct ball *b, int32_t r, int32_t c, int32_t vr, int32_t vc);
void moveBall(struct ball *b, int32_t k);
void shiftPos(struct ball *b, int32_t *r, int32_t *c);
int32_t collision(struct ball *b,int32_t i,int8_t h,int8_t w, uint8_t swr, uint8_t swc);


#endif
