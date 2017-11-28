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
	t_matrice* TT;

	fichierEnTableau(nameFile,&M,&seqL,&seqC);
	printf("taille séquence : %d\n", seqL.sequences[0]->taille);
	TT = initialise_TT(M.m, seqL.sequences[0]->taille);
/*
	if ((enumeration(0, 1, &M)) || enumeration(0,2, &M))
		printf("Coloriée\n");
	else
		printf("Non coloriée\n");
*/

	if (testVecteurLigne_Rec(&M, 0, (M.m)-1, seqL.sequences[0]->taille-1, TT) == 1)
		printf("OK\n");
	else
		printf("KO\n");
		
	affiche_matrice(TT);
	affiche_matrice(&M);
	return 0;
}
