#include <string.h>
#include "tomographie.h"

int main(int argc, char **argv){

	if (argc != 2){
		printf("Erreur");
		return 1;
	}
	
	char* nameFile = strdup(argv[1]);
	
	t_matrice M;

	fichierEnTableau(nameFile,&M);
	if (propagation(&M)){
		printf("Tayo tayo!\n");
		affiche_matrice(&M);
	}else{
		printf("Oula!!\n");
	}
	
	return 0;
}


