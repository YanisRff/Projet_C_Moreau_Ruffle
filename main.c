#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "fir.h"
#include "iir.h"
#include "tests/autotests.h"
#include "mesure.h"
#include "lecture.h"

int main (int argc, char** argv) {
    //Struct callbacks
    absorp myAbsorp;
    oxy myOxy;
    absorp old_Absorp = {0};
    absorp old_iir = {0};
    absorp absorp_memory[51] = {0};

    //Variables callbacks
    float time = 0.;
    float periode = 0.;
    int etat = 0;
    float max_acr;
    float min_acr;
    float max_acir;
    float min_acir;
    float old_acr;
    bool verif;
    int am_count = 0;
    int front = 0;


    //main
    while(1){
        myAbsorp = lecture(&time);
        myAbsorp = fir(myAbsorp, absorp_memory, &am_count, &front);
        myAbsorp = iir(myAbsorp, &old_Absorp, &old_iir);
        verif = mesure(myAbsorp, &myOxy, &etat, &max_acr, &min_acr, &max_acir, &min_acir, &old_acr, &time, &periode);
        if(verif){
            affichage(myOxy);
        }
    }
    return 0;
}
