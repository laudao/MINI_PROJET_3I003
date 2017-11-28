#include <string.h>
#include "tomographie.h"

int main(int argc, char **argv){

	if (argc != 2){
		printf("Erreur");
		return 1;
	}
	
	char* nameFile = strdup(argv[1]);

	t_matrice M;
	t_ens_sequences seqL;
	t_ens_sequences seqC;

	fichierEnTableau(nameFile,&M,&seqL,&seqC);

//	M.mat[0][0] = 1;
//	M.mat[1][0] = 2;
//	M.mat[2][0] = 1;	
//	M.mat[3][0] = 2;	
//	M.mat[4][0] = 2;	
//	M.mat[5][0] = 2;
//
//	if (compare_seq_col(0, &M))
//		printf("OK\n");
//	else
//		printf("KO\n");
	if ((enumeration(0, 1, &M)) || enumeration(0,2, &M))
		printf("Coloriée\n");
	else
		printf("Non coloriée\n");

	affiche_matrice(&M);
	return 0;
}
