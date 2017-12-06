#include <string.h>
#include "tomographie.h"
#include <time.h>

int main(){
	t_matrice *M;
	t_matrice *TT;
	FILE *f_temps_vecteur;
	int i;
	int l;
	clock_t temps_initial;
	clock_t temps_final;
	double temps_cpu;

	char *instances[] = {"instances/vec_20.tom","instances/vec_30.tom","instances/vec_35.tom","instances/vec_40.tom","instances/vec_45.tom","instances/vec_50.tom","instances/vec_55.tom","instances/vec_60.tom","instances/vec_100.tom","instances/vec_1000.tom","instances/vec_10000.tom","instances/vec_20000.tom","instances/vec_30000.tom","instances/vec_40000.tom","instances/vec_50000.tom","instances/vec_60000.tom","instances/vec_70000.tom","instances/vec_80000.tom","instances/vec_90000.tom","instances/vec_100000.tom","instances/vec_100000_0.tom","instances/vec_110000.tom","instances/vec_120000.tom"};
	

	for (i=0; i<23; i++){
		f_temps_vecteur = fopen("temps_testVecteurLigne", "a");
		M = (t_matrice*)malloc(sizeof(t_matrice));
		fichierEnTableau(instances[i] , M);
		l = M->seqL->sequences[0]->taille;
		TT = initialise_TT(M->m, l); 
		temps_initial = clock();
		
		if (testVecteurLigne_Rec(M, 0, (M->m)-1, l-1, TT)){
			printf("Instance %s coloriable\n", instances[i]);
		}else{
			printf("Instance %s non coloriable\n", instances[i]);
		}

		temps_final = clock();
		temps_cpu = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
		fprintf(f_temps_vecteur, "%d %f\n", M->m, temps_cpu);
		free(TT);
		free(M);
		fclose(f_temps_vecteur);
	}

	return 0;
}
