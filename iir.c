#include "iir.h"
#include "fichiers.h"

absorp iir(absorp actual_absorp, absorp* old_absorp, absorp* old_iir){

	absorp f_iir;

	f_iir.acr = actual_absorp.acr - old_absorp->acr + alpha*old_iir->acr;
	f_iir.acir = actual_absorp.acir - old_absorp->acir + alpha*old_iir->acir;
	f_iir.dcr = actual_absorp.dcr;
	f_iir.dcir = actual_absorp.dcir;

	*old_absorp = actual_absorp;
	*old_iir = f_iir;

	return f_iir;
}



absorp iirTest(char* filename){
	absorp	myAbsorp;
	absorp actual;
	int fileState = 0;
	absorp old_FIR = {0};
	absorp old_IR = {0};
	FILE* pf=initFichier(filename);
	actual = lireFichier(pf,&fileState);
	while(fileState != EOF) {
		myAbsorp = iir(actual, old_FIR, old_IR);
		old_FIR = actual;
		old_IR = myAbsorp;
		actual = lireFichier(pf,&fileState);
	}
	finFichier(pf);

	return myAbsorp;
}

