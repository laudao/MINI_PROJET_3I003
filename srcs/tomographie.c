#include "tomographie.h"


// fonction qui lit le contenu du fichiers et qui initialise la matrice avec le tableau des sequences des lignes
void fichierEnTableau(char* s,int** matrice,int** seqL,int** seqC){

	FILE* f=fopen(s,"r");
	
	if (f == NULL){
		fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", s);
	}
	
	int n = GetEntier(f);
	printf("%d\n", n);
	Skip(f);
	int m = GetEntier(f);
	printf("%d\n", m);
	SkipLine(f);

	int i=0;
	//allocation de la matrice dans la memoire
	matrice=(int**)malloc(sizeof(int*)*n);
	for(int i=0;i<n;i++){
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
	//	int cpt=0;

	seqL=(int**)malloc(sizeof(int*)*n);
	
	printf("Diable voici le tableau des sequences des lignes!\n");
	for(i=0;i<n;i++){ // pour chaque ligne de la matrice 
		taille_seqL= GetEntier(f); // taille de la séquence de la ligne i
		seqL[i]=(int*)malloc(sizeof(int)*taille_seqL); // allocation d'un tableau d'entiers de taille_seqL cases

		if (taille_seqL > 0){
			Skip(f);
			for(int l=0;l<taille_seqL;l++){ // pour chaque bloc de la séquence 
				seqL[i][l]=GetEntier(f);
				printf("%d ",seqL[i][l]);
				Skip(f);
			}
		}
//		SkipLine(f);
		/*
		if(taille_seqL==0){ // pas de bloc à colorier sur cette ligne
			SkipLine(f);
		}
		else{
			for(int l=0;l<taille_seqL;l++){ // pour chaque bloc de la séquence 
				seqL[i][l]=GetEntier(f);
				Skip(f);
				printf("%d ",seqL[i][l]);
			}
		}
		SkipLine(f);*/
		printf("\n");
	}
	
	printf("\n");
//initialisation du tableau des seq des colonnes avec les valeurs lues dans le fichier et affichage sur le flux de sortie
	int taille_seqC=0;
	int l=0;

	seqC=(int**)malloc(sizeof(int*)*m);
	printf("Oh WTF ! voici le tableau des sequences des colonnes!\n");

	for(j=0;j<m;j++){
		taille_seqC= GetEntier(f);
		seqC[j]=(int*)malloc(sizeof(int)*taille_seqC);
		

		if (taille_seqC > 0){ // séquence non vide
			Skip(f); 
			for(l=0;l<taille_seqC;l++){ // pour chaque bloc de la séquence 
				seqC[j][l]=GetEntier(f);
				printf("%d ",seqC[j][l]);
				Skip(f);
			}
		}

		/*
		if(taille_seqC==0){
			SkipLine(f);
		} else {
			for(int l=0;l<taille_seqC;l++){
				seqC[j][l]=GetEntier(f);
				Skip(f);
				printf("%d ",seqC[j][l]);
			}
		}
		SkipLine(f);*/
		printf("\n"); 
	} 

	if (f)
		fclose(f);
	
}
