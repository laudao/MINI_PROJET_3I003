#include "tomographie.h"


//focntion qui prend en argument le nom du fichier qui lit le contenu et qui renvoie 2 pointeur sur tableau un avec la matrice et un avec les sequences  
void fichierEnTableau(char* s,int** matrice,int** tableau){

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
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			printf("%d ",matrice[i][j]);
		}
		printf("\n");
	}
	

	//initialisation du tableau des seq avec les valeurs lues dans le fichier et affichage sur le flux de sortie

	int taille_seq=0;
	int cpt=0;

	tableau=(int**)malloc(sizeof(int*)*n);
	
	for(int k=0;k<n;k++){
		taille_seq= GetEntier(f);
		tableau[k]=(int*)malloc(sizeof(int)*taille_seq);
		Skip(f);
		for(int l=0;l<taille_seq;l++){
			tableau[k][l]=GetEntier(f);
			printf("%d ",matrice[k][l]);
		}
		SkipLine(f);
		printf("\n");
	}

	if (f)
		fclose(f);
	
}
