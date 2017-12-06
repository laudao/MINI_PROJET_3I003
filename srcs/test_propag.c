#include <string.h>
#include "tomographie.h"
#include <time.h>

int main(){
	t_matrice *M;

	int i;
	clock_t temps_initial;
	clock_t temps_final;
	double temps_cpu;

	char *instances[] = {"instances/0.tom", "instances/1.tom","instances/2.tom", "instances/3.tom","instances/4.tom", "instances/5.tom","instances/6.tom", "instances/7.tom","instances/8.tom", "instances/9.tom","instances/10.tom", "instances/11.tom","instances/12.tom","instances/13.tom", "instances/14.tom", "instances/15.tom","instances/16.tom"};
	
	for (i=0; i<17; i++){
		M = (t_matrice*)malloc(sizeof(t_matrice));
		fichierEnTableau(instances[i] , M);
		temps_initial = clock();
		
		if (propagation(M)){
			printf("Instance %s coloriée\n", instances[i]);
			affiche_matrice(M);
//			completer_coloriage(M);
		}else{
			printf("Instance %s non coloriée\n", instances[i]);
		}

		temps_final = clock();
		temps_cpu = ((double)(temps_final - temps_initial))/CLOCKS_PER_SEC;
		printf("%d %f\n", M->m, temps_cpu);

	}
	
	return 0;
}


