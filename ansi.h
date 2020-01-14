#ifndef ANSI_H
#define ANSI_H

#include <stdint.h>
#include <stdio.h>
#include "Joystick.h"
#define ESC 0x1B

#define FIX14_SHIFT 14
#define FIX14_MULT(a,b) ((a)*(b) >> FIX14_SHIFT)
#define FIX14_DIV(a,b) ( ((a) << FIX14_SHIFT) / b)

void fgcolor(uint8_t foreground);
void bgcolor(uint8_t background);
void color(uint8_t foreground, uint8_t background);
void clrscr(void);
void clreol(void);
void gotoxy(uint8_t c, uint8_t r);
void underline(uint8_t on);
void blink(uint8_t on);
void inverse(uint8_t on);
void window(uint8_t c1, uint8_t r1, uint8_t c2, uint8_t r2, char title[],uint8_t type);
void printBall(uint32_t r, uint32_t c);
void deleteball(uint32_t r, uint32_t c);
void windowgame(uint8_t h, uint8_t b, uint8_t r1, uint8_t c1);
void printhits(int16_t i, int8_t h);
void printTimer(void);
void printsplit(struct Timer *split,uint8_t statevec);

#endif
