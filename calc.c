#include "calc.h"


int16_t power(int8_t a, int8_t exp) {
//Calculates a^exp
    int16_t i,r = a;
    for (i = 1; i <exp; i++){
        r *= a;
    }
    return(r);
}

int32_t sinus(int16_t angle){                                                       //Funktion til udregning af sinusv�rdi
    return SIN[angle & 0x1FF];                                                      //henter sinus v�rdigen i SIN registeret
}

int32_t cosinus(int16_t angle){                                                     //Funktion til udregning af cosinusv�rdi
    return sinus(angle+128);                                                        //Henter cosinus v�rdigen i vores sinus funktion da der er 512 v�rdiger passer 128 til 90gr derfor plus 128
}

void setvec(struct vector_t *v, int32_t r, int32_t c){
    /*
    definere x og y til vektor v' (via givet addrese) givet af bruger via main.
    */

    v->r = r << FIX14_SHIFT; // Shifter fra 32.0 til 18.14 fixed point.
    v->c = c << FIX14_SHIFT;
}

void rotateVector(struct vector_t *v, int16_t grad){
    int32_t r1 = v->r;
    int32_t c1 = v->c;
    v->r = (FIX14_MULT((r1),cosinus(grad)) - FIX14_MULT((c1), (sinus(grad))));
    v->c = (FIX14_MULT((r1),sinus(grad)) + FIX14_MULT((c1), (cosinus(grad))));
}

void setBall(struct ball *b, int32_t r, int32_t c, int32_t vr, int32_t vc){
    /*
    definere x og y til vektor v' (via givet addrese) givet af bruger via main.
    */

    b->pos.r = r << FIX14_SHIFT;                                                    // Shifter fra 32.0 til 18.14 fixed point.
    b->pos.c = c << FIX14_SHIFT;                                                    // Shifter fra 32.0 til 18.14 fixed point.
    b->v.r = vr << FIX14_SHIFT;                                                     // Shifter fra 32.0 til 18.14 fixed point.
    b->v.c = vc << FIX14_SHIFT;                                                     // Shifter fra 32.0 til 18.14 fixed point.

}

void moveBall(struct ball *b, int32_t k){
    /*
    En funktion der flytter position p� bolden
    */

    k = k << FIX14_SHIFT;                                                           // Shifter fra 32.0 til 18.14 fixed point.

    b->pos.r = b->pos.r + FIX14_MULT(b->v.r, k);                                    //�ndre hvilken r�kke bolden er p� formlen x=x+vx*k er brugt
    b->pos.c = b->pos.c + FIX14_MULT(b->v.c, k);                                    //�ndre hvilken colone bolden er p� formlen y=x+vy*k er brugt
}

void shiftPos(struct ball *b, int32_t *r, int32_t *c){
    /*
    En funktion der shifter tilbage til 32.0 s� det kan bruges til print funktioner
    */
    *r = b->pos.r >> FIX14_SHIFT;                                                   // shifter tilbage til 32.0 for r
    *c = b->pos.c >> FIX14_SHIFT;                                                   // shifter tilbage til 32.0 for c
}

int32_t collision(struct ball *b,int32_t i,int8_t h,int8_t w, uint8_t swr, uint8_t swc){
    /*
    En funktion der rykker bolden og tjekker om den remmer ind i en v�g n�ste
    gang og i s� fald �ndre dens velocity vektor s� den simulerer den remmer v�ggen
    */
    int32_t r,c;
    r = b->pos.r  >> FIX14_SHIFT;                                                   //Gemmer boldens nuv�rende r position og shifter den til et heltal
    c = b->pos.c  >> FIX14_SHIFT;                                                   //Gemmer boldens nuv�rende c position og shifter den til et heltal
    if (r==swr+1 || r==h+swr-1){                                                            //Hvis bolden remmer et felt opaf den �verste eller nederste linje i game vinduet
        i++;                                                                        //lig da 1 til i
        if (c==w+swc-1 ||c==swc+1){                                                        //Hvis den ogs� er i et felt der ligger opaf en side dermed er i et hj�rne
            b->v.r = -b->v.r;                                                       //Vend vr
            b->v.c = -b->v.c;                                                       //Vend vc
            return i;                                                               //retuner i til count
        }
        b->v.r = -b->v.r;                                                           //ellers vend kun vr
        return i;                                                                   //retuner i til count
    }
    /*
    Da hj�rnerne bliver gennemg�et i de to �vre if statements skal de ikke indg� her
    */
    if (c==swc+1 || c==w+swc-1){                                                           //Hvis bolden remmer et felt opaf h�jre eller venstre linje i game vinduet
        i++;                                                                        //lig da 1 til i
        b->v.c = -b->v.c;                                                           //ellers vend kun vc
        return i;                                                                   //retuner i til count
    }
    return i;                                                                       //Hvis igen af if statementsne bliver opfyldt vil i blot retuneres som den kom ind
}
