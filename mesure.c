#include "mesure.h"
#include "fichiers.h"

int table_de_correspondance(float rsir){
    if (rsir <= 1.0){
        float result = -25.0 * rsir + 110;
        return (int)result;
    }
    else{
        float result = -(425.0/12.0) * rsir + 120.4;
        return result;
    }
}

bool mesure(absorp myAbsorp,oxy* myOxy, int* etat, float* max_acr, float* min_acr, float*max_acir, float* min_acir, float* old_acr, float* time, float* periode){
    if(*old_acr == 0.f){
        *old_acr = myAbsorp.acr;
    }
    if(*old_acr > 0.f && myAbsorp.acr < 0.f && *etat ==1){
        float rsir = ((max_acr - min_acr)/myAbsorp.dcr)/((max_acir - min_acir)/myAbsorp.dcir);
        myOxy->spo2 = table_de_correspondance(rsir);
        myOxy->pouls = 60/(*periode);
        printf("mesure\n");
        printf("max_acr : %f\n", *max_acr);
        printf("min_acr : %f\n", *min_acr);
        printf("SPO2 : %d\n", myOxy->spo2);
        printf("Pouls : %d\n", myOxy->pouls);
        printf("\n");
        return true;
    }
    if(*old_acr > 0.f && myAbsorp.acr < 0.f && *etat == 0){
        *etat = 1;
        *periode = 0;
        *max_acr = myAbsorp.acr;
        *min_acr = myAbsorp.acr;
        *max_acir = myAbsorp.acir;
        *min_acir = myAbsorp.acir;
    }
    if(myAbsorp.acr > *max_acr){
        *max_acr = myAbsorp.acr;
    }
    if(myAbsorp.acr < *min_acr){
        *min_acr = myAbsorp.acr;
    }
    if(myAbsorp.acir > *max_acir){
        *max_acir = myAbsorp.acir;
    }
    if(myAbsorp.acir < *min_acir){
        *min_acir = myAbsorp.acir;
    }
    if(*etat == 1){
        *periode += *time;
    }
    *old_acr = myAbsorp.acr;
    
    printf("mesure en cours\n");
    printf("max_acr : %f\n", *max_acr);
    printf("min_acr : %f\n", *min_acr);
    printf("acr : %f\n", myAbsorp.acr);
    printf("acir : %f\n", myAbsorp.acir);
    printf("\n");
    return false;
}
