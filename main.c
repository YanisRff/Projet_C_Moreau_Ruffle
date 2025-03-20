#include <stdlib.h>
#include <stdio.h>

#include "fir.h"
#include "iir.h"
#include "tests/autotests.h"
#include "mesure.h"
#include "lecture.h"

int main (int argc, char** argv) {
    //Struct callbacks
    absorp myAbsorp;
    oxy myOxy;

    //Variables callbacks
    float time = 0.;
    float periode = 0.;
    int etat = 0;
    float max_acr;
    float min_acr;
    float max_acir;
    float min_acir;
    float old_acr;

    //main
    while(1){
        lecture(&time);

    }

    return 0;
}
