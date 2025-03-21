#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "fir.h"
#include "iir.h"
#include "tests/autotests.h"
#include "mesure.h"
#include "lecture.h"
#include <time.h>
#include <sys/time.h>
#include "affichage.h"

int main (int argc, char** argv) {
    /*
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
    int point = 0;
    float max_acr;
    float min_acr;
    float max_acir;
    float min_acir;
    float old_acr;
    bool verif;
    int am_count = 0;
    FT_HANDLE ftHandle;

    struct timeval timee;

    float temps_debut;
    float temps_fin;
    long long int temps_passe;
    double temps_a_virgule_prems;

    gettimeofday(&timee, NULL);
    temps_passe = (timee.tv_sec * 1000000) + timee.tv_usec;
    temps_a_virgule_prems = (float)temps_passe / 1000000.0;


    //main
    init_lecture(&ftHandle);
    while(1){
        gettimeofday(&timee, NULL);
        temps_passe = (timee.tv_sec * 1000000) + timee.tv_usec;
        temps_fin = (float)temps_passe / 1000000.0  - temps_a_virgule_prems;
        
        time = temps_fin - temps_debut;
        printf("temps : %f\n", time);

        myAbsorp = lecture(&ftHandle);
        
        gettimeofday(&timee, NULL);
        temps_passe = (timee.tv_sec * 1000000) + timee.tv_usec;
        temps_debut = (float)temps_passe / 1000000.0  - temps_a_virgule_prems;

        myAbsorp = fir(myAbsorp, absorp_memory, &am_count);
        
        myAbsorp = iir(myAbsorp, &old_Absorp, &old_iir);
        

        verif = mesure(myAbsorp, &myOxy ,&point , &etat, &max_acr, &min_acr, &max_acir, &min_acir, &old_acr, &time, &periode);
        
        if(verif){
            affichage(myOxy);
        }
        if(am_count == 52){
            am_count = 1;
        }
    }
    FT_Close(ftHandle);
    */

    //Tests
    testBlocFIR();
    firTest("../log/log1/log1.dat");
    testBlocIIR();
    testBlocMesure();
    testBlocAffichage();


    return 0;
}
