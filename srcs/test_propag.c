#include <string.h>
#include "tomographie.h"
#include <time.h>

int main(){
	t_matrice *M;
	FILE *f_temps_propagation;
	int i;
	clock_t temps_initial;
	clock_t temps_final;
	double temps_cpu;
	double pourcentage;
	int propag;

	char *instances[] = {"instances/0.tom", "instances/1.tom","instances/2.tom", "instances/3.tom","instances/4.tom", "instances/5.tom","instances/6.tom", "instances/7.tom","instances/8.tom", "instances/9.tom","instances/10.tom", "instances/11.tom","instances/12.tom","instances/13.tom", "instances/14.tom", "instances/15.tom","instances/16.tom"};

	
	for (i=0; i<17; i++){
		f_temps_propagation = fopen("temps_propagation", "a");
		M = (t_matrice*)malloc(sizeof(t_matrice));
		fichierEnTableau(instances[i] , M);
		temps_initial = clock();
		pourcentage = 0;	

		temps_initial = clock();
		
		propag = propagation(M, &pourcentage);
		
		temps_final = clock();
		temps_cpu = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
		fprintf(f_temps_propagation, "%d %f %f\n", M->n*M->m, temps_cpu, pourcentage);

		if (propag){
			printf("Instance %s coloriée (partiellement): \n", instances[i]);
			affiche_matrice(M);
			completer_coloriage(M);
			printf("Instance %s coloriée (complètement): \n", instances[i]);

		}else{
			printf("Instance %s non coloriée\n", instances[i]);
		}
		fclose(f_temps_propagation);
	}
	
	return 0;
}


