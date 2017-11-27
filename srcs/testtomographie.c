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
//	int i, j;

	fichierEnTableau(nameFile,&M,&seqL,&seqC);

	M.mat[0][0] = 2;
	M.mat[0][1] = 2;
	M.mat[0][2] = 1;
	M.mat[0][3] = 2;
	M.mat[0][4] = 2;
	M.mat[0][5] = 2;

	if (compare_seq_ligne(0, &M))
		printf("OK\n");
	else
		printf("KO\n");
//	if ((enumeration(0,1, &M)) || (enumeration(0,2,&M)))
//		printf("ok\n");
//	else
//		printf("ko\n");
	
	affiche_matrice(&M);
	return 0;
}
