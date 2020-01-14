#include <stdio.h>
#include "Joystick.h"
#include "stm32f30x_conf.h"
#include "30010_io.h"

char readJoystick(int8_t *f){

    uint8_t right = GPIOC -> IDR & (0x0001) << 0;
    uint8_t up = GPIOA -> IDR & (0x0001) << 4;
    uint8_t center = GPIOB -> IDR & (0x0001) << 5;
    uint8_t left = GPIOC -> IDR & (0x0001) << 1;
    uint8_t down = GPIOB -> IDR & (0x0001) << 0;

RCC->AHBENR |= RCC_AHBPeriph_GPIOA; //Enable clock for GPIO Port A

RCC->AHBENR |= RCC_AHBPeriph_GPIOB; //Enable clock for GPIO Port B

RCC->AHBENR |= RCC_AHBPeriph_GPIOC; //Enable clock for GPIO Port C

// Set pin PC0 to input
GPIOC->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
GPIOC->MODER |= (0x00000000 << (0 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
GPIOC->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
GPIOC->PUPDR |= (0x00000002 << (0 * 2)); // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)

// Set pin PA4 to input
GPIOA->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
GPIOA->MODER |= (0x00000000 << (4 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
GPIOA->PUPDR &= ~(0x00000003 << (4 * 2)); // Clear push/pull register
GPIOA->PUPDR |= (0x00000002 << (4 * 2)); // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)

// Set pin PB5 to input
GPIOB->MODER &= ~(0x00000003 << (5 * 2)); // Clear mode register
GPIOB->MODER |= (0x00000000 << (5 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
GPIOB->PUPDR &= ~(0x00000003 << (5 * 2)); // Clear push/pull register
GPIOB->PUPDR |= (0x00000002 << (5 * 2)); // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)

// Set pin PC1 to input
GPIOC->MODER &= ~(0x00000003 << (1 * 2)); // Clear mode register
GPIOC->MODER |= (0x00000000 << (1 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
GPIOC->PUPDR &= ~(0x00000003 << (1 * 2)); // Clear push/pull register
GPIOC->PUPDR |= (0x00000002 << (1 * 2)); // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)

// Set pin PB0 to input
GPIOB->MODER &= ~(0x00000003 << (0 * 2)); // Clear mode register
GPIOB->MODER |= (0x00000000 << (0 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)
GPIOB->PUPDR &= ~(0x00000003 << (0 * 2)); // Clear push/pull register
GPIOB->PUPDR |= (0x00000002 << (0 * 2)); // Set push/pull register (0x00 - No pull, 0x01 - Pull-up, 0x02 - Pull-down)


//printf("0 0 0 %d .  %d %d %d %d\n",center >> 5, right, left >> 1, down, up >> 4);
int8_t storage = 0x00;

if (up > 0){
    if (storage != 0x01){
            storage |= 1 << 0;
            printf("Up\n");
            *f = 1;
    }
    else{
            storage &= ~(1 << 0);
    }
}

if (down > 0){
    if (storage != 0x02){
            storage |= 1 << 1;
            printf("Down\n");
            *f = 2;
    }
    else{
            storage &= ~(1 << 1);
    }
}


if (left > 0){
    if (storage != 0x04){
            storage |= 1 << 2;
            printf("Left\n");
            *f = 3;
    }
    else{
            storage &= ~(1 << 2);
    }
}


if (right > 0){
    if (storage != 0x08){
            storage |= 1 << 3;
            printf("Right\n");
            *f = 4;
    }
    else{
            storage &= ~(1 << 3);
    }
}


if (center > 0){
    if (storage != 0x010){
            storage |= 1 << 4;
            printf("Center\n");
            *f = 5;
    }
    else{
            storage &= ~(1 << 4);
    }
}

//printf("%d\n",storage);



}

char setLed(uint8_t value){


RCC->AHBENR |= RCC_AHBPeriph_GPIOA; //Enable clock for GPIO Port A

RCC->AHBENR |= RCC_AHBPeriph_GPIOB; //Enable clock for GPIO Port B

RCC->AHBENR |= RCC_AHBPeriph_GPIOC; //Enable clock for GPIO Port C

 // Set pin PA9 to  (Blue)
 GPIOA->OSPEEDR &= ~(0x00000003 << (9 * 2)); // Clear speed register
 GPIOA->OSPEEDR |= (0x00000002 << (9 * 2)); // set speed register (0x01 - 10MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
 GPIOA->OTYPER &= ~(0x0001 << (9)); // Clear output type register
 GPIOA->OTYPER |= (0x0000 << (9)); // Set output type register (0x00 - Push pull, 0x01 - Open drain)
 GPIOA->MODER &= ~(0x00000003 << (9 * 2)); // Clear mode register
 GPIOA->MODER |= (0x00000001 << (9 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)

 uint16_t val = GPIOA->IDR & (0x0001 << 9); //Read from pin PA0
 GPIOA->ODR |= (0x0001 << 9); //Set pin PA9 to high


 // Set pin PB4 to output (Red)
 GPIOB->OSPEEDR &= ~(0x00000003 << (4 * 2)); // Clear speed register
 GPIOB->OSPEEDR |= (0x00000002 << (4 * 2)); // set speed register (0x01 - 10MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
 GPIOB->OTYPER &= ~(0x0001 << (4)); // Clear output type register
 GPIOB->OTYPER |= (0x0000 << (4)); // Set output type register (0x00 - Push pull, 0x01 - Open drain)
 GPIOB->MODER &= ~(0x00000003 << (4 * 2)); // Clear mode register
 GPIOB->MODER |= (0x00000001 << (4 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)

 uint16_t val2 = GPIOA->IDR & (0x0001 << 4); //Read from pin PA0
 GPIOB->ODR |= (0x0001 << 4); //Set pin PB4 to high


 // Set pin PC7 to output  (Green)
 GPIOC->OSPEEDR &= ~(0x00000003 << (7 * 2)); // Clear speed register
 GPIOC->OSPEEDR |= (0x00000002 << (7 * 2)); // set speed register (0x01 - 10MHz, 0x02 - 2 MHz, 0x03 - 50 MHz)
 GPIOC->OTYPER &= ~(0x0001 << (7)); // Clear output type register
 GPIOC->OTYPER |= (0x0000 << (7)); // Set output type register (0x00 - Push pull, 0x01 - Open drain)
 GPIOC->MODER &= ~(0x00000003 << (7 * 2)); // Clear mode register
 GPIOC->MODER |= (0x00000001 << (7 * 2)); // Set mode register (0x00 – Input, 0x01 - Output, 0x02 - Alternate Function, 0x03 - Analog in/out)

 uint16_t val3 = GPIOA->IDR & (0x0001 << 7); //Read from pin PA0
 GPIOC->ODR |= (0x0001 << 7); //Set pin PC7 to high

switch(value){

case 1:
   GPIOA->ODR |= (0x0001 << 9); //Set pin PA9 to high

   GPIOC->ODR |= (0x0001 << 7); //Set pin PC7 to low

   GPIOB->ODR &= ~(0x0001 << 4); //Set pin PB4 to low


    break;


case 2:
   GPIOA->ODR |= (0x0001 << 9); //Set pin PA9 to high

   GPIOC->ODR &= ~(0x0001 << 7); //Set pin PC7 to low

   GPIOB->ODR |= (0x0001 << 4); //Set pin PB4 to low


    break;

case 3:
   GPIOA->ODR &= ~(0x0001 << 9); //Set pin PA9 to high

   GPIOC->ODR |= (0x0001 << 7); //Set pin PC7 to low

   GPIOB->ODR |= (0x0001 << 4); //Set pin PB4 to low


    break;

case 4:
   GPIOA->ODR &= ~(0x0001 << 9); //Set pin PA9 to high

   GPIOC->ODR &= ~(0x0001 << 7); //Set pin PC7 to low

   GPIOB->ODR |= (0x0001 << 4); //Set pin PB4 to low


    break;

case 5:
   GPIOA->ODR &= ~(0x0001 << 9); //Set pin PA9 to high

   GPIOC->ODR |= (0x0001 << 7); //Set pin PC7 to low

   GPIOB->ODR &= ~(0x0001 << 4); //Set pin PB4 to low


    break;

case 6:
   GPIOA->ODR |= (0x0001 << 9); //Set pin PA9 to high

   GPIOC->ODR &= ~(0x0001 << 7); //Set pin PC7 to low

   GPIOB->ODR &= ~(0x0001 << 4); //Set pin PB4 to low


    break;

case 7:
   GPIOA->ODR &= ~(0x0001 << 9); //Set pin PA9 to high

   GPIOC->ODR &= ~(0x0001 << 7); //Set pin PC7 to low

   GPIOB->ODR &= ~(0x0001 << 4); //Set pin PB4 to low


    break;
}
}


// Definerer globale variable


void initTimer(void){
    RCC->APB1ENR |= RCC_APB1Periph_TIM2; // Enable clock
    TIM2->CR1 = 0x0000; // Configure timer 2
    TIM2->ARR = 0x9C3FF; // Set reload value (64000)
    TIM2->PSC = 0x00; // Set prescale value

    TIM2->DIER |=0x0001; // Enables timer 2 interrupts.

    NVIC_SetPriority(28,1);   // set interrupt priority
    NVIC_EnableIRQ(28);              // Enable interrupt
    TIM2->CR1 |= (0x01 << 0);
}


void init(struct Timer *Stopwatch){
    Stopwatch->hunCount = 00;
    Stopwatch->sekCount = 00;
    Stopwatch->minCount = 00;
    Stopwatch->hrsCount = 00;
}

void TIM2_IRQHandler(void){

    Stopwatch.hunCount++;
    if (Stopwatch.hunCount >= 100){
        Stopwatch.sekCount++;
        Stopwatch.hunCount = 00;
    }
    if (Stopwatch.sekCount >= 60){
        Stopwatch.minCount++;
        Stopwatch.sekCount = 00;
    }
    if (Stopwatch.minCount >= 60){
        Stopwatch.hrsCount++;
        Stopwatch.minCount = 00;
    }

    TIM2->SR &= ~(0x0001); // Clear interrupt bit
}
void printTimer(void){
    printf("%.2d:%.2d:%.2d.%.2d\n",Stopwatch.hrsCount, Stopwatch.minCount,Stopwatch.sekCount,Stopwatch.hunCount);
}

