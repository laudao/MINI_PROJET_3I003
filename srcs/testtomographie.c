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
	if ((enumeration(0,1, &M)) || (enumeration(0,2,&M)))
		printf("ok\n");
	else
		printf("ko\n");
	

//	M.mat[0][0] = 2;
//	M.mat[0][1] = 2;
//	M.mat[0][2] = 2;
//	M.mat[0][3] = 1;
//	M.mat[0][4] = 1;
//	M.mat[1][0] = 1;
//	M.mat[1][1] = 1;
//	M.mat[1][2] = 1;
//	M.mat[1][3] = 1;
//	M.mat[1][4] = 1;
//	M.mat[2][0] = 2;
//	M.mat[2][1] = 1;
//	M.mat[2][2] = 2;
//	M.mat[2][3] = 1;
//	M.mat[2][4] = 2;
//	M.mat[3][0] = 1;
//	M.mat[3][1] = 1;
//	M.mat[3][2] = 2;
//	M.mat[3][3] = 2;
//	M.mat[3][4] = 2;
//
//	for (i=0; i<M.n; i++){
//		for (j=0; j<M.m; j++){
//			printf("%d ", M.mat[i][j]);
//		}
//		printf("\n");
//	}
//
//	for (i=0; i<M.n; i++){
//		if (compare_seq_ligne(i, &M))
//			printf("ligne %d OK \n", i);
//		else
//			printf("ligne %d KO \n", i);
//	}
//	printf("\n");
//	for (j=0; j<M.m; j++){
//		if (compare_seq_col(j, &M))
//			printf("col %d OK \n", j);
//		else
//			printf("col %d KO \n", j);
//	}

	return 0;
}
