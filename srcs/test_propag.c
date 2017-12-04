#include <string.h>
#include "tomographie.h"

int main(int argc, char **argv){
	char* nameFile;
	t_matrice M;
	
	if (argc != 2){
		printf("Usage: %s <instances/fichier>\n", argv[0]);
		return 1;
	}
	
	nameFile = strdup(argv[1]);

	fichierEnTableau(nameFile,&M);

	if (propagation(&M)){
		printf("Tayo tayo!\n");
		affiche_matrice(&M);
		printf("Nombre de cases non coloriees: %d\n", pourcentage_coloriees(&M));
		completer_coloriage(&M);
		affiche_matrice(&M);
	}else{
		printf("Oula!!\n");
	}
	
	return 0;
}


