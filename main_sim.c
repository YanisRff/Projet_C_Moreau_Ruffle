#include <stdlib.h>
#include <stdio.h>


#include "fichiers.h"
#include "fir.h"
#include "iir.h"
#include "mesure.h"
#include "affichage.h"

int main (int argc, char** argv) {
    //Struct callbacks
    absorp myAbsorp;
    oxy myOxy;
    absorp old_fir={0};
    absorp old_iir={0};
    absorp absorp_memory[51] = {0};
    absorp ligne;

    //Variables callbacks

    float time = 0.;
    int point = 0;
    int etat = 0;
    int mesure_ok = 0;
    float max_acr;
    float min_acr;
    float max_acir;
    float min_acir;
    float old_acr;
    bool verif;
    int am_count = 0;


    int fileState = 0;

    char* filename = "../log/log2/log2.dat";
    FILE* pf=initFichier(filename);
    ligne = lireFichier(pf,&fileState);
    //main
    while(fileState != EOF) {
        myAbsorp=fir(ligne, absorp_memory, &am_count);
        myAbsorp=iir(myAbsorp, &old_fir, &old_iir);
        mesure_ok = mesure(myAbsorp, &myOxy, &etat, &max_acr, &min_acr, &max_acir, &min_acir, &old_acr, &time, &point);
        if (mesure_ok) {
            affichage(myOxy);
        }
        else {
        }
        ligne=lireFichier(pf,&fileState);
    }
    return 0;
}
