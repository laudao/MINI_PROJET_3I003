#include <string.h>
#include "tomographie.h"

int main(int argc, char **argv){

	if (argc != 2){
		printf("Erreur");
		return 1;
	}
	
	char* nameFile = strdup(argv[1]);

	t_matrice M;
//	t_matrice* TT;
	double pourcentage;

	fichierEnTableau(nameFile,&M); //&seqL,&seqC);
	if (propagation(&M, &pourcentage)){
		printf("Matrice coloriée\n");
	}
	affiche_matrice(&M);
	printf("\n");
	completer_coloriage(&M);
	affiche_matrice(&M);
//	printf("taille séquence : %d\n", seqC.sequences[0]->taille);
//	TT = initialise_TT(M.m, M.seqL->sequences[0]->taille);
//	int nb=0;
//	int marqueC[M.m];
//	int i;
//	for (i=0; i<M.m; i++){
//		marqueC[i] = 1;
//	}
//	if (propagLigne(&M, 0, marqueC, &nb))
//		affiche_matrice(&M);

//	affiche_matrice(TT);
	return 0;
}
