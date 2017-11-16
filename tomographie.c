#include "tomographie.h"


//focntion qui lit le contenu du fichiers et qui initialise la matrice le tableau des sequences des lignes
void fichierEnTableau(char* s,int** matrice,int** seqL,int** seqC){

	FILE* f=fopen(s,"r");
	int n = GetEntier(f);
	int m = GetEntier(f);
	SkipLine(f);

	if (f == NULL){
		fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", s);
	}
	
	
	int i=0;
	//allocation de la matrice dans la memoire
	matrice=(int**)malloc(sizeof(int*)*n);
		for(int i=0;i<m;i++){
			matrice[i]=(int*)malloc(sizeof(int)*m);
			}
	
	i=0;
	int j;
	//initialisation de la matrice à 0
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			matrice[i][j]=0;
		}
	}

	//affichage de la matrice
	printf("Oh surprise voici la matrice non coloriee !\n");
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			printf("%d ",matrice[i][j]);
		}
		printf("\n");
	}
	
	printf("\n");
	//initialisation du tableau des seq des lignes avec les valeurs lues dans le fichier et affichage sur le flux de sortie

	int taille_seqL=0;
	int cpt=0;

	seqL=(int**)malloc(sizeof(int*)*n);
	

	printf("Diable voici le tableau des sequences des lignes!\n");
	for(int k=0;k<n;k++){
		taille_seqL= GetEntier(f);
		seqL[k]=(int*)malloc(sizeof(int)*taille_seqL);
		Skip(f);
		if(taille_seqL==0){
			SkipLine(f);
		}
		else{
			for(int l=0;l<taille_seqL;l++){
				seqL[k][l]=GetEntier(f);
				printf("%d ",seqL[k][l]);
			}
		}
		SkipLine(f);
		printf("\n");
	}
	
	printf("\n");
//initialisation du tableau des seq des colonnes avec les valeurs lues dans le fichier et affichage sur le flux de sortie
	int taille_seqC=0;
	
	seqC=(int**)malloc(sizeof(int*)*n);
	printf("Oh WTF ! voici le tableau des sequences des colonnes!\n");

	for(int k=0;k<n;k++){
		taille_seqC= GetEntier(f);
		seqC[k]=(int*)malloc(sizeof(int)*taille_seqC);
		Skip(f);
		if(taille_seqC==0){
			SkipLine(f);
		}
		for(int l=0;l<taille_seqC;l++){
			seqC[k][l]=GetEntier(f);
			printf("%d ",seqC[k][l]);
		}
		SkipLine(f);
		printf("\n");
	}
	if (f)
		fclose(f);
	
}
