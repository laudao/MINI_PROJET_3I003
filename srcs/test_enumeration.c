#include <string.h>
#include "tomographie.h"
#include <time.h>

int main(){
	t_matrice *M;
	FILE *f_temps_enumeration;
	int i;
	clock_t temps_initial;
	clock_t temps_final;
	double temps_cpu;

	char *instances[] = {"instances/vec_20.tom", "instances/vec_35.tom"};
	//char *instances[] = {"instances/vec_100.tom", "instances/vec_40.tom","instances/vec_1000.tom","instances/vec_40000.tom","instances/vec_10000.tom", "instances/vec_45.tom","instances/vec_100000.tom","instances/vec_50.tom","instances/vec_100000_0.tom", "instances/vec_50000.tom","instances/vec_110000.tom", "instances/vec_55.tom","instances/vec_120000.tom","instances/vec_60.tom","instances/vec_20.tom","instances/vec_60000.tom","instances/vec_20000.tom","instances/vec_70000.tom","instances/vec_30.tom","instances/vec_80000.tom","instances/vec_30000.tom","instances/vec_90000.tom","instances/vec_35.tom"};
	
	f_temps_enumeration = fopen("temps_enumeration", "w");

	for (i=0; i<2; i++){
		M = (t_matrice*)malloc(sizeof(t_matrice));
		fichierEnTableau(instances[i] , M);
		temps_initial = clock();
		
		if ((enumeration(0, 1, M)) || (enumeration(0, 2, M))){
			printf("Instance %s coloriée\n", instances[i]);
			affiche_matrice(M);
		}else{
			printf("Instance %s non coloriée\n", instances[i]);
		}

		temps_final = clock();
		temps_cpu = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
		fprintf(f_temps_enumeration, "%d %f\n", M->m, temps_cpu);
	}

	return 0;
}
