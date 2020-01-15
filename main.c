/*
**
**                           Main.c
**
**
**********************************************************************/
/*
   Last committed:     $Revision: 00 $
   Last changed by:    $Author: $
   Last changed date:  $Date:  $
   ID:                 $Id:  $

**********************************************************************/
#include "stm32f30x_conf.h"
#include "30010_io.h"
#include "Joystick.h"
#include "ansi.h"
#include <stdio.h>
#include "calc.h"
#include <string.h>
#include <stdlib.h>

int main(void)
{
    struct ball b;
    struct Timer split;
    int32_t r,c,i,h,w,vr,vc,l;
    uint8_t swr,swc,f,statevec,oldstatevec;
    int8_t p;
    char key[20];                                               // Opretter string med 20 elementer
    memset(key, 0, 20*sizeof(key[0]));                          //

    uart_init(9600);                                            //Initialize USB serial at 9600 baud
    initJoy();
    resetWatch(&Stopwatch);
    initTimer();
    clrscr();
    i = 0;                                                      //i = hit count
    h = 40;                                                     //H�jde p� vinduet
    w = 80;                                                     //Breden p� vinduet, kunne ikke hedde b da vi bruge b i andet form�l
    r = 20;                                                     //R�kken bolden starter p�
    c = 20;                                                     //kolonnen bolden starter p�
    vr = 1;                                                     //Boldens fart i r�kke retningen
    vc = 1;                                                     //Boldens fart i kolonne retningen
    l = 1;                                                      //l = k kunne ikke f� lov til at kalde den k s� brokkede compiler sig
    swr = 5;                                                    //R�kken vinduet starter i
    swc = 10;                                                   //kolonne vinduet starter i

    printf("\e[?25l");                                          //G�r et cursor ikke bliver vist
    color(2,0);                                                 //S�tter bagrund og forgrunds farver
    clrscr();                                                   //Sletter gamle ting fra display
//    windowgame(h,w,swr,swc);                                    //Printer vinduet
//    setBall(&b,r,c,vr,vc);                                      //Definerer boldens start position
//    shiftPos(&b,&r,&c);                                         //�ndre r og c til 32.0 s� printfunktion kan l�se dem
//    printBall(r,c);                                             //Printer boldens start position
    gotoxy(0,0);
    //readTerminal();
    while(1){
        gotoxy(1,1);
        printTimer();



        readKeyboard(key, &p);
            if (key[p-1]==0x0D){
                key[p-1] = 0;

                //printf("%s",key);
                p = 0;
            }

            stringCompare(key);

        if(statevec != oldstatevec){

            Timerinput(statevec,&split);

        if (statevec == 3){
            gotoxy(2,1);
            printsplit(&split, statevec);

        }
        if (statevec == 4){
            gotoxy(3,1);
            printsplit(&split, statevec);

        }


        }
        oldstatevec = statevec;
////        moveBall(&b,l);                                             //Flytter bolden til dens n�ste position
////        i = collision(&b,i,h,w,swr,swc);                            //Tj�kker om bolden remmer en v�g og t�ller i i hvis den g�r
////        deleteball(r,c);                                            //sletter boldens forrigen position
////        shiftPos(&b,&r,&c);                                         //opdatere r og c til ny position og �ndre til 32.0 s� printfunktion kan l�se dem
////        printBall(r,c);                                             //Printer bolden p� dens nye position
////        printhits(i,h);                                             //Printer hit count
////        gotoxy(30,30);
//    gotoxy(1,1);

    }
}
