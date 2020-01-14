#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_
// Definerer global struct
struct Timer{
    int8_t hrsCount;
    int8_t minCount;
    int8_t sekCount;
    int8_t hunCount;
};

struct Timer Stopwatch;

void init(struct Timer *Stopwatch);
void initTimer(void);
void TIM_2_IRQHandler(void);
void printTimer(void);

char readJoystick(int8_t *f);
char setLed(uint8_t value);

#endif
