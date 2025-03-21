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

    struct timeval timee;
    struct timeval timee2;
    struct timeval timee3;

    double temps_a_virgule;
    long long int temps_passe;
    double temps_a_virgule_prems;

    gettimeofday(&timee, NULL);
    temps_passe = (timee.tv_sec * 1000000) + timee.tv_usec;
    temps_a_virgule_prems = (double)temps_passe / 1000000.0;


    //main
    while(1){
        myAbsorp = lecture(&time);

        gettimeofday(&timee, NULL);
        temps_passe = (timee.tv_sec * 1000000) + timee.tv_usec;
        temps_a_virgule = (double)temps_passe / 1000000.0  - temps_a_virgule_prems;

        printf("Temps : %lf\n", temps_a_virgule);
        myAbsorp = fir(myAbsorp, absorp_memory, &am_count);
        
        gettimeofday(&timee, NULL);
        temps_passe = (timee.tv_sec * 1000000) + timee.tv_usec;
        temps_a_virgule = (double)temps_passe / 1000000.0  - temps_a_virgule_prems;
        printf("Temps2 : %lf\n", temps_a_virgule);

        myAbsorp = iir(myAbsorp, &old_Absorp, &old_iir);
        
        gettimeofday(&timee, NULL);
        temps_passe = (timee.tv_sec * 1000000) + timee.tv_usec;
        temps_a_virgule = (double)temps_passe / 1000000.0  - temps_a_virgule_prems;
        printf("Temps3 : %lf\n", temps_a_virgule);

        verif = mesure(myAbsorp, &myOxy, &etat, &max_acr, &min_acr, &max_acir, &min_acir, &old_acr, &time, &periode);
        
        gettimeofday(&timee, NULL);
        temps_passe = (timee.tv_sec * 1000000) + timee.tv_usec;
        temps_a_virgule = (double)temps_passe / 1000000.0  - temps_a_virgule_prems;
        printf("Temps4 : %lf\n", temps_a_virgule);


        if(verif){
            affichage(myOxy);
        }
    }
    return 0;
}
