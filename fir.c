#include "fir.h"
#include "fichiers.h"

float FIR_TAPS[51]={
    1.4774946e-019,
    1.6465231e-004,
    3.8503956e-004,
    7.0848037e-004,
    1.1840522e-003,
    1.8598621e-003,
    2.7802151e-003,
    3.9828263e-003,
    5.4962252e-003,
    7.3374938e-003,
    9.5104679e-003,
    1.2004510e-002,
    1.4793934e-002,
    1.7838135e-002,
    2.1082435e-002,
    2.4459630e-002,
    2.7892178e-002,
    3.1294938e-002,
    3.4578348e-002,
    3.7651889e-002,
    4.0427695e-002,
    4.2824111e-002,
    4.4769071e-002,
    4.6203098e-002,
    4.7081811e-002,
    4.7377805e-002,
    4.7081811e-002,
    4.6203098e-002,
    4.4769071e-002,
    4.2824111e-002,
    4.0427695e-002,
    3.7651889e-002,
    3.4578348e-002,
    3.1294938e-002,
    2.7892178e-002,
    2.4459630e-002,
    2.1082435e-002,
    1.7838135e-002,
    1.4793934e-002,
    1.2004510e-002,
    9.5104679e-003,
    7.3374938e-003,
    5.4962252e-003,
    3.9828263e-003,
    2.7802151e-003,
    1.8598621e-003,
    1.1840522e-003,
    7.0848037e-004,
    3.8503956e-004,
    1.6465231e-004,
    1.4774946e-019
};

int etat = 0;
int am_count = 0;
int front;
absorp absorp_memory[51] = {0};

absorp fir(absorp donnes) {
	absorp result={0};
	absorp_memory[am_count%51] = donnes;
	am_count++;
	front = am_count%51;
	for(int i = 0; i<51; i++){
		result.acr += absorp_memory[(50+front-i)%51].acr * FIR_TAPS[i];
		result.dcr = absorp_memory[50].dcr;
		result.acir += absorp_memory[(50+front-i)%51].acir * FIR_TAPS[i];
		result.dcir = absorp_memory[50].dcir;
	}
	return result;
}






absorp firTest(char* filename){
	absorp	myAbsorp;
	//absorp absorp_memory[51] = {0};
	//int etat = 0;
	//int am_count = 0;
	FILE* file = initFichier(filename);
	absorp result;
	//int front;
	myAbsorp = lireFichier(file, &etat);
	while(etat != EOF){
		result = fir(myAbsorp);
		/*result.acr = 0;
		result.dcr = 0;
		result.acir = 0;
		result.dcir = 0;
		absorp_memory[am_count%51] = myAbsorp;
		am_count++;
		front = am_count%51;

		for(int i = 0; i<51; i++){
                	result.acr += absorp_memory[(50+front-i)%51].acr * FIR_TAPS[i];
                	result.dcr = absorp_memory[50].dcr;
                	result.acir += absorp_memory[(50+front-i)%51].acir * FIR_TAPS[i];
                	result.dcir = absorp_memory[50].dcir;
        	}*/
		myAbsorp = lireFichier(file, &etat);
	}
	finFichier(file);
	return result;

}





