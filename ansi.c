#include "ansi.h"

void fgcolor(uint8_t foreground) {
/*  Value      foreground     Value     foreground
    ------------------------------------------------
      0        Black            8       Dark Gray
      1        Red              9       Light Red
      2        Green           10       Light Green
      3        Brown           11       Yellow
      4        Blue            12       Light Blue
      5        Purple          13       Light Purple
      6        Cyan            14       Light Cyan
      7        Light Gray      15       White
*/
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%dm", ESC, type, foreground+30);
}

void bgcolor(uint8_t background) {
/* IMPORTANT:   When you first use this function you cannot get back to true white background in HyperTerminal.
   Why is that? Because ANSI does not support true white background (ANSI white is gray to most human eyes).
                The designers of HyperTerminal, however, preferred black text on white background, which is why
                the colors are initially like that, but when the background color is first changed there is no
 	              way comming back.
   Hint:        Use resetbgcolor(); clrscr(); to force HyperTerminal into gray text on black background.

    Value      Color
    ------------------
      0        Black
      1        Red
      2        Green
      3        Brown
      4        Blue
      5        Purple
      6        Cyan
      7        Gray
*/
  printf("%c[%dm", ESC, background+40);
}

void color(uint8_t foreground, uint8_t background) {
// combination of fgcolor() and bgcolor() - uses less bandwidth
  uint8_t type = 22;             // normal text
	if (foreground > 7) {
	  type = 1;                // bold text
		foreground -= 8;
	}
  printf("%c[%d;%d;%dm", ESC, type, foreground+30, background+40);
}

void resetbgcolor() {

// gray on black text, no underline, no blink, no reverse
  printf("%c[m", ESC);
}

void clrscr(void){
    printf("%c[%d%c",ESC,2,0x4A); //Printer funktionen som i pdf'en, der beskriver at programmet fjerner alt der st�r inde i vinduet
}

void clreol(void){
    printf("%c[%c",ESC,0x4B); //Printer funktionen som i pdf'en der beskriver at programmet fjerner linjen efter mark�ren
}

void gotoxy(uint8_t r, uint8_t c){  ////Printer funktionen som i pdf'en der f�r programmet til at g� til en speciel position
    printf("%c[%d;%d%c",ESC,r,c,0x48);
}

void underline(uint8_t on){ //Printer funktionen som i pdf'en som g�r at teksten bliver understreget
    if (on == 1)    //Laver et if-statemant, s� det kun sker hvis man kalder funktionen med et 1-tal som statement
        printf("%c[%d%c",ESC,04,0x6D);
    else            //Ellers laver den under understregning
        printf("%c[%d%c",ESC,24,0x6D);

}

void blink(uint8_t on){ //Printer funktionen som i pdf'en der for teskten til at blinke
    if (on == 1)        //Printer kun hvis man kalder den med et 1-tal som statement
        printf("%c[%d%c",ESC,05,0x6D);
    else                //Ellers printer den uden at teksten printer
        printf("%c[%d%c",ESC,25,0x6D);
}

void inverse(uint8_t on){ //Printer funktionen som i pdf'en som g�r at tekstens farve bliver inverteret
    if (on == 1)          //Printer kun hvis man klader den med et 1-tal som statement
        printf("%c[%d%c",ESC,07,0x6D);
    else                  //Ellser printer den med alm farve.
        printf("%c[%d%c",ESC,27,0x6D);
}

void window(uint8_t r1, uint8_t c1, uint8_t r2, uint8_t c2, char title[],uint8_t type){  //Opretter en funktion som kan oprette et vundue med en title, samt v�lge hvilken type vundue det skal v�re


    int i;
    int o;                   //Indentificere for forskellige integers til senere brug i for loops
    int s;
    uint8_t len = 0;

    while (1){
            if (title[len] == '\0'){
                break;
            }
            else{
                len++;
            }
    }

    if (type == 1){         //V�lger hvilken type vindue man vil have

        gotoxy(r1,c1);           // G�r til x1,y1
        printf("%c%c%s%c",201,185,title,204);       //Printer den �verste linje med titel

        for (i=1;i<c2-c1;i++){  //For loop til de to sider
            gotoxy(r1,c1+i);    //G�r til venstre kollonne og g�t nedaf ved at tilf�je i for hvert print
            printf("%c",186);
            gotoxy(r2,c1+i);    //G�r til h�jre kollonne og g�r nedaf ved at tilf�je i for hvert print
            printf("%c",186);
            }
        gotoxy(r1,c2);          //G�t til bunden i venstre
        printf("%c",200);       //Tilf�jer hj�rne
        gotoxy(r2,c2);          //G�r til bunden i h�jre
        printf("%c",188);       //Tilf�jer hj�rne


        for (o=1;o<r2-r1;o++){  //For loop for at lave bunden
            gotoxy(r1+o,c2);    //Tilf�jer 1 hver gang vha. o
            printf("%c",205);   //Printer bunden
        }
        gotoxy(r2,c1);          //G�r til sidste hj�rne
        printf("%c",187);       //Printer hj�rne

        for (s=1;s<=r2-(r1+len+3);s++){   //For loop for det sidste efter titelen, og hen til kollonnen til h�jre
            gotoxy(r1+len+2+s,c1);        //Tager et skridt til h�jre
            printf("%c",205);                       //Printer toppen
        }
        gotoxy(0,0);            //G�r tilbage til 0,0
    }

    else{

        gotoxy(r1,c1);           // G�r til x1,y1
        printf("%c%c%s%c",218,180,title,195);       //Printer den �verste linje med titel

        for (i=1;i<c2-c1;i++){  //For loop til de to sider
            gotoxy(r1,c1+i);    //G�r til venstre kollonne og g�t nedaf ved at tilf�je i for hvert print
            printf("%c",179);
            gotoxy(r2,c1+i);    //G�r til h�jre kollonne og g�t nedaf ved at tilf�je i for hvert print
            printf("%c",179);
            }
        gotoxy(r1,c2);          //G�t til bunden i venstre
        printf("%c",192);       //Tilf�jer hj�rne
        gotoxy(r2,c2);          //G�r til bunden i h�jre
        printf("%c",217);       //Tilf�jer hj�rne


        for (o=1;o<r2-r1;o++){  //For loop for at lave bunden
            gotoxy(r1+o,c2);    //Tilf�jer 1 hver gang vha. o
            printf("%c",196);   //Printer bunden
        }
        gotoxy(r2,c1);          //G�r til sidste hj�rne
        printf("%c",191);       //Printer hj�rne

        for (s=1;s<=r2-(r1+len+3);s++){   //For loop for det sidste efter titelen, og hen til kollonnen til h�jre
            gotoxy(r1+len+2+s,c1);        //Tager et skridt til h�jre
            printf("%c",196);                       //Printer toppen
        }
        gotoxy(0,0);            //G�r tilbage til 0,0

    }
}

void printFix(int32_t i){    //Prints a signed 16.16 fixed point number

    if ((i & 0x80000000) != 0) {
        printf("-");
        i = ~i + 1;
    }
    printf("%ld.%04ld", i >> 16, 10000 * (uint32_t) (i & 0xFFFF) >> 16);    //Print a maximum of 4 decimal digits to avoid overflow
}

int32_t expand(int32_t i){   //Converts an 18.14 fixed point number to 16.16

    return i << 2;
}

void printBall(uint32_t r, uint32_t c){
    /*
    En funktion der pritner bolden p� dens rigtige position
    */
    gotoxy(r,c);                                                    //G�r til rigtige koordinater
    printf("o");                                                    //Printer bolden som et o
}

void deleteball(uint32_t r, uint32_t c){
    /*
    En funktion der sletter bolen igen
    */
    gotoxy(r,c);                                                //g�r til de rigtige koordinater
    printf("%c",255);                                           //Printer tomt print oven p� bolden dermed sletter den bolden
}

void windowgame(uint8_t h, uint8_t b, uint8_t r1, uint8_t c1){  //Opretter en funktion som kan oprette et vundue med en title, samt v�lge hvilken type vundue det skal v�re
    /*
    h = antal r�kker vinduet er langt
    b = antal kolonner vinduet er bredt
    r1 = R�kken hvor vinduet starter
    c1 = kolonnen hvor vinduet starter
    */
    uint8_t r2 = h+r1;                                          //Definerer r�kke placering vinduets slutning
    uint8_t c2 = b+c1;                                          //Definerer cullum placering vinduets slutning
    int8_t i;                                                   //En tom t�lle variable

    gotoxy(r1,c1);                                              // G�r til vindues �vre venstre hj�rne
    printf("%c",201);                                           // Printer hj�rnet (201)

    for (i=1;i<b;i++){                                          //For loop til at udf�re �vre side af vindue

        gotoxy(r1,c1+i);                                        //G�r 1 kolenne vidre for hvert loop
        printf("%c",205);                                       // Printer =

    }

    gotoxy(r1,c2);                                              //G�t til �vre h�jre h�rne
    printf("%c",187);                                           //Tilf�jer hj�rnet

    for (i=1;i<h;i++){                                          //For loop for at lave h�jre side

        gotoxy(r1+i,c2);                                        //G�r en r�kke ned for hvert loop
        printf("%c",186);                                       //Printer ||

    }

    gotoxy(r2,c2);                                              //G�r til nedre h�jre hj�rne
    printf("%c",188);                                           //Tilf�jer hj�rnet

    for (i=1;i<b;i++){                                          //For loop til bunden

        gotoxy(r2,c2-i);                                        //G�r en kolonne tilbage for hvert loop
        printf("%c",205);                                       //Printer =

    }

    gotoxy(r2,c1);                                              //G�r til nedre venstre hj�rne
    printf("%c",200);                                           //Printer hj�rnet

    for (i=1;i<h;i++){                                          //For loop for at lave bunden

        gotoxy(r2-i,c1);                                        //G�r en r�kken op for hvert loop
        printf("%c",186);                                       //Printer ||

    /*
    Opretter en boks, hvori der er en hit-count
    */
    }
    gotoxy(h+7,10);                                             //G�r til �vre venstre hj�rne
    printf("%c",201);                                           //Printer hj�rnet

    gotoxy(h+8,10);                                             //G�r en r�kke ned
    printf("%c",186);                                           //Printer ||

    gotoxy(h+9,10);                                             //G�r til nedre venstre hj�rne
    printf("%c",200);                                           //Printer hj�rnet

    for (i=1;i<12;i++){                                         //For loop til bund
        gotoxy(h+9,10+i);                                       //G�r en kolonne vidre for hvert loop
        printf("%c",205);                                       //Printer =
    }

    gotoxy(h+9,22);                                             //G�r til nederste venstre hj�rne
    printf("%c",188);                                           //Printer hj�rnet

    gotoxy(h+8,22);                                             //G�r en r�kke op
    printf("%c",186);                                           //Printer ||

    gotoxy(h+7,22);                                             //G�r til �vre h�jre hj�rne
    printf("%c",187);                                           //Printer hj�rnet

    for (i=1;i<12;i++){                                         //For loop til top
        gotoxy(h+7,22-i);                                       //G�r en kolonne tilbage for hvert loop
        printf("%c",205);                                       //Printer =
    }

    gotoxy(h+8,11);                                             //G�r til f�rste plads i boksen
    printf("Hits:");                                            //Printer Hits:
}

void printhits(int16_t i, int8_t h){
    /*
    En funktion der printer i fra main som er antalet af hits
    */
    gotoxy(h+8,17);                                             //G�r til den plads hvor hit count skal st�
    printf("%d",i);                                             //Printer hit count
}

void printTimer(void){
    printf("Timer : %.2d:%.2d:%.2d.%.2d\n",Stopwatch.hrsCount, Stopwatch.minCount,Stopwatch.sekCount,Stopwatch.hunCount);
}

void printsplit(struct Timer *split,uint8_t statevec){
    printf("Split %d : %.2d:%.2d:%.2d.%.2d\n",statevec-2,split->hrsCount, split->minCount,split->sekCount,split->hunCount);
}
