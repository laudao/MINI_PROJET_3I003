#include <string.h>
#include "tomographie.h"

int main(int argc, char **argv){

	if (argc != 2){
		printf("Erreur");
		return 1;
	}
	
	char* nameFile = strdup(argv[1]);

	int** matrice=NULL;
	int** tableau1=NULL;
	int** tableau2=NULL;

	fichierEnTableau(nameFile,matrice,tableau1,tableau2);

	return 0;
}
