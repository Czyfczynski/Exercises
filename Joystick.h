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

void initJoy(void);
void resetWatch(struct Timer *Stopwatch);
void initTimer(void);
void TIM_2_IRQHandler(void);

uint8_t readJoystick(void);
char setLed(uint8_t value);
char Timerinput(uint8_t value, struct Timer *split);
char readTerminal(void);
#endif
