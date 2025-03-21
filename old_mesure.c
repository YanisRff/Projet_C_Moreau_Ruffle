#include "mesure.h"
#include "fichiers.h"

oxy mesureTest(char* filename){
	oxy myOxy;
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
	int etat = 0;
	float max_acr;
	float min_acr;
	float max_acir;
	float min_acir;
	float période;
	int point = 0;
	int etat_point = 0;
	int save_point;
	float old_acir;
	FILE* file = initFichier(filename);
	absorp myAbsorp;
	myAbsorp = lireFichier(file, &etat);
	min_acr = myAbsorp.acr;
	max_acr = myAbsorp.acr;
	min_acir = myAbsorp.acir;
	max_acir = myAbsorp.acir;
	old_acir = myAbsorp.acir;
	float dcir;
	float dcr;
	while(etat != EOF){
		if(min_acr > myAbsorp.acr){
			min_acr = myAbsorp.acr;
		}
		if(max_acr < myAbsorp.acr){
			max_acr = myAbsorp.acr;
		}
		if(min_acir > myAbsorp.acir){
			min_acir = myAbsorp.acir;
		}
		if(max_acir < myAbsorp.acir){
			max_acir = myAbsorp.acir;
		}
		dcir = myAbsorp.dcir;
		dcr = myAbsorp.dcr;
		old_acir = myAbsorp.acir;
		myAbsorp = lireFichier(file, &etat);
		if(old_acir > 0. && myAbsorp.acir < 0.){
			if(etat_point == 0){
				etat_point = 1;
				max_acir = myAbsorp.acir;
				min_acir = myAbsorp.acir;
				max_acr = myAbsorp.acr;
				min_acr = myAbsorp.acr;
			}
			else{
				etat_point = 0;
			}
		}
		if(etat_point == 1){
			point++;
		}
		if(etat_point == 0){
			if(point > 0){
				save_point = point;
			}
			point = 0;
		}
	}
	float rsir = ((max_acr - min_acr)/dcr)/((max_acir - min_acir)/dcir);
	myOxy.spo2 = table_de_correspondance(rsir);
	myOxy.pouls = 1000*60/(2*save_point);
	return myOxy;
}
