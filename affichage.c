#include "affichage.h"
#include "fichiers.h"
#include <unistd.h>

int verrou() {
	int etat;
	if( access( ".verrouData", F_OK ) != -1 ) {
		etat = 1;
	}
	else {
		etat =0;
	}
	return etat;
}


void affichage(oxy myOxy){
	if (verrou() == 0) {
		fopen(".verrouData","w+");
		FILE* data = fopen("data.txt","w");
        printf("SPO2 : %d\n", myOxy.spo2);
        printf("Pouls : %d\n", myOxy.pouls);
		fprintf(data, "%d\n", myOxy.spo2);
		fprintf(data, "%d\n", myOxy.pouls);
		fclose(data);
		remove(".verrouData");
	}
	else {}
}

