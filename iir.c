#include "iir.h"
#include "fichiers.h"

absorp iir(absorp actual_absorp, absorp* old_absorp, absorp* old_iir){ // (FIR t, FIR t-1, IRR t-1)
	absorp f_iir; //Creation de la structure du filtre iir modele absorp

	f_iir.acr = actual_absorp.acr - old_absorp->acr + alpha*old_iir->acr;
	f_iir.acir = actual_absorp.acir - old_absorp->acir + alpha*old_iir->acir;
	f_iir.dcr = actual_absorp.dcr; //Dcr et Dcir restent inchangés
	f_iir.dcir = actual_absorp.dcir;

	*old_absorp = actual_absorp; //actualisation de la valeur FIR t-1
	*old_iir = f_iir; // IRR t-1
    
    printf("iir \n");
    printf("acr : %f\n", f_iir.acr);
    printf("acir : %f\n", f_iir.acir);
    printf("dcr : %f\n", f_iir.dcr);
    printf("dcir : %f\n", f_iir.dcir);
    printf("\n");
	return f_iir;
}



absorp iirTest(char* filename){
	absorp	myAbsorp;
	/*
	absorp actual;
	int fileState = 0;
	absorp* old_FIR = {0}; //Init des valeurs t-1 (non connues)
	absorp* old_IR = {0};
	FILE* pf=initFichier(filename); //Ouverture fichier
	actual = lireFichier(pf,&fileState); //1ere ligne de lecture
	while(fileState != EOF) { //EOF -> End of File
		myAbsorp = iir(actual, old_FIR, old_IR);
		*old_FIR = actual;
		*old_IR = myAbsorp;
		actual = lireFichier(pf,&fileState); //incrementation ligne du fichier
	}
	finFichier(pf); //Close fichier

	return myAbsorp;
*/
}

