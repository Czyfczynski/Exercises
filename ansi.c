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
    printf("%c[%d%c",ESC,2,0x4A); //Printer funktionen som i pdf'en, der beskriver at programmet fjerner alt der står inde i vinduet
}

void clreol(void){
    printf("%c[%c",ESC,0x4B); //Printer funktionen som i pdf'en der beskriver at programmet fjerner linjen efter markøren
}

void gotoxy(uint8_t r, uint8_t c){  ////Printer funktionen som i pdf'en der får programmet til at gå til en speciel position
    printf("%c[%d;%d%c",ESC,r,c,0x48);
}

void underline(uint8_t on){ //Printer funktionen som i pdf'en som gør at teksten bliver understreget
    if (on == 1)    //Laver et if-statemant, så det kun sker hvis man kalder funktionen med et 1-tal som statement
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

void inverse(uint8_t on){ //Printer funktionen som i pdf'en som gør at tekstens farve bliver inverteret
    if (on == 1)          //Printer kun hvis man klader den med et 1-tal som statement
        printf("%c[%d%c",ESC,07,0x6D);
    else                  //Ellser printer den med alm farve.
        printf("%c[%d%c",ESC,27,0x6D);
}

void window(uint8_t r1, uint8_t c1, uint8_t r2, uint8_t c2, char title[],uint8_t type){  //Opretter en funktion som kan oprette et vundue med en title, samt vælge hvilken type vundue det skal være


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

    if (type == 1){         //Vælger hvilken type vindue man vil have

        gotoxy(r1,c1);           // Går til x1,y1
        printf("%c%c%s%c",201,185,title,204);       //Printer den øverste linje med titel

        for (i=1;i<c2-c1;i++){  //For loop til de to sider
            gotoxy(r1,c1+i);    //Går til venstre kollonne og gåt nedaf ved at tilføje i for hvert print
            printf("%c",186);
            gotoxy(r2,c1+i);    //Går til højre kollonne og går nedaf ved at tilføje i for hvert print
            printf("%c",186);
            }
        gotoxy(r1,c2);          //Gåt til bunden i venstre
        printf("%c",200);       //Tilføjer hjørne
        gotoxy(r2,c2);          //Går til bunden i højre
        printf("%c",188);       //Tilføjer hjørne


        for (o=1;o<r2-r1;o++){  //For loop for at lave bunden
            gotoxy(r1+o,c2);    //Tilføjer 1 hver gang vha. o
            printf("%c",205);   //Printer bunden
        }
        gotoxy(r2,c1);          //Går til sidste hjørne
        printf("%c",187);       //Printer hjørne

        for (s=1;s<=r2-(r1+len+3);s++){   //For loop for det sidste efter titelen, og hen til kollonnen til højre
            gotoxy(r1+len+2+s,c1);        //Tager et skridt til højre
            printf("%c",205);                       //Printer toppen
        }
        gotoxy(0,0);            //Går tilbage til 0,0
    }

    else{

        gotoxy(r1,c1);           // Går til x1,y1
        printf("%c%c%s%c",218,180,title,195);       //Printer den øverste linje med titel

        for (i=1;i<c2-c1;i++){  //For loop til de to sider
            gotoxy(r1,c1+i);    //Går til venstre kollonne og gåt nedaf ved at tilføje i for hvert print
            printf("%c",179);
            gotoxy(r2,c1+i);    //Går til højre kollonne og gåt nedaf ved at tilføje i for hvert print
            printf("%c",179);
            }
        gotoxy(r1,c2);          //Gåt til bunden i venstre
        printf("%c",192);       //Tilføjer hjørne
        gotoxy(r2,c2);          //Går til bunden i højre
        printf("%c",217);       //Tilføjer hjørne


        for (o=1;o<r2-r1;o++){  //For loop for at lave bunden
            gotoxy(r1+o,c2);    //Tilføjer 1 hver gang vha. o
            printf("%c",196);   //Printer bunden
        }
        gotoxy(r2,c1);          //Går til sidste hjørne
        printf("%c",191);       //Printer hjørne

        for (s=1;s<=r2-(r1+len+3);s++){   //For loop for det sidste efter titelen, og hen til kollonnen til højre
            gotoxy(r1+len+2+s,c1);        //Tager et skridt til højre
            printf("%c",196);                       //Printer toppen
        }
        gotoxy(0,0);            //Går tilbage til 0,0

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
    En funktion der pritner bolden på dens rigtige position
    */
    gotoxy(r,c);                                                    //Går til rigtige koordinater
    printf("o");                                                    //Printer bolden som et o
}

void deleteball(uint32_t r, uint32_t c){
    /*
    En funktion der sletter bolen igen
    */
    gotoxy(r,c);                                                //går til de rigtige koordinater
    printf("%c",255);                                           //Printer tomt print oven på bolden dermed sletter den bolden
}

void windowgame(uint8_t h, uint8_t b, uint8_t r1, uint8_t c1){  //Opretter en funktion som kan oprette et vundue med en title, samt vælge hvilken type vundue det skal være
    /*
    h = antal rækker vinduet er langt
    b = antal kolonner vinduet er bredt
    r1 = Rækken hvor vinduet starter
    c1 = kolonnen hvor vinduet starter
    */
    uint8_t r2 = h+r1;                                          //Definerer række placering vinduets slutning
    uint8_t c2 = b+c1;                                          //Definerer cullum placering vinduets slutning
    int8_t i;                                                   //En tom tælle variable

    gotoxy(r1,c1);                                              // Går til vindues øvre venstre hjørne
    printf("%c",201);                                           // Printer hjørnet (201)

    for (i=1;i<b;i++){                                          //For loop til at udføre øvre side af vindue

        gotoxy(r1,c1+i);                                        //Går 1 kolenne vidre for hvert loop
        printf("%c",205);                                       // Printer =

    }

    gotoxy(r1,c2);                                              //Gåt til øvre højre hørne
    printf("%c",187);                                           //Tilføjer hjørnet

    for (i=1;i<h;i++){                                          //For loop for at lave højre side

        gotoxy(r1+i,c2);                                        //Går en række ned for hvert loop
        printf("%c",186);                                       //Printer ||

    }

    gotoxy(r2,c2);                                              //Går til nedre højre hjørne
    printf("%c",188);                                           //Tilføjer hjørnet

    for (i=1;i<b;i++){                                          //For loop til bunden

        gotoxy(r2,c2-i);                                        //Går en kolonne tilbage for hvert loop
        printf("%c",205);                                       //Printer =

    }

    gotoxy(r2,c1);                                              //Går til nedre venstre hjørne
    printf("%c",200);                                           //Printer hjørnet

    for (i=1;i<h;i++){                                          //For loop for at lave bunden

        gotoxy(r2-i,c1);                                        //Går en rækken op for hvert loop
        printf("%c",186);                                       //Printer ||

    /*
    Opretter en boks, hvori der er en hit-count
    */
    }
    gotoxy(h+7,10);                                             //Går til øvre venstre hjørne
    printf("%c",201);                                           //Printer hjørnet

    gotoxy(h+8,10);                                             //Går en række ned
    printf("%c",186);                                           //Printer ||

    gotoxy(h+9,10);                                             //Går til nedre venstre hjørne
    printf("%c",200);                                           //Printer hjørnet

    for (i=1;i<12;i++){                                         //For loop til bund
        gotoxy(h+9,10+i);                                       //Går en kolonne vidre for hvert loop
        printf("%c",205);                                       //Printer =
    }

    gotoxy(h+9,22);                                             //Går til nederste venstre hjørne
    printf("%c",188);                                           //Printer hjørnet

    gotoxy(h+8,22);                                             //Går en række op
    printf("%c",186);                                           //Printer ||

    gotoxy(h+7,22);                                             //Går til øvre højre hjørne
    printf("%c",187);                                           //Printer hjørnet

    for (i=1;i<12;i++){                                         //For loop til top
        gotoxy(h+7,22-i);                                       //Går en kolonne tilbage for hvert loop
        printf("%c",205);                                       //Printer =
    }

    gotoxy(h+8,11);                                             //Går til første plads i boksen
    printf("Hits:");                                            //Printer Hits:
}

void printhits(int16_t i, int8_t h){
    /*
    En funktion der printer i fra main som er antalet af hits
    */
    gotoxy(h+8,17);                                             //Går til den plads hvor hit count skal stå
    printf("%d",i);                                             //Printer hit count
}

void printTimer(void){
    printf("Timer : %.2d:%.2d:%.2d.%.2d\n",Stopwatch.hrsCount, Stopwatch.minCount,Stopwatch.sekCount,Stopwatch.hunCount);
}

void printsplit(struct Timer *split,uint8_t statevec){
    printf("Split %d : %.2d:%.2d:%.2d.%.2d\n",statevec-2,split->hrsCount, split->minCount,split->sekCount,split->hunCount);
}
