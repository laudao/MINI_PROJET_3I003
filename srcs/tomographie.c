#include "tomographie.h"


// fonction qui lit le contenu du fichiers et qui initialise la matrice avec le tableau des sequences des lignes
void fichierEnTableau(char* s, Matrice* matrice, Ens_sequences* seqL, Ens_sequences* seqC){
	int taille_seqC=0;
	int l=0;
	int taille_seqL=0;
	int i=0;
	int j=0;
	int m=0;
	int n=0;
	FILE* f=NULL;

	f=fopen(s,"r");
	
//	matrice=(Matrice*)malloc(sizeof(Matrice));
//	seqL=(Ens_sequences*)malloc(sizeof(Ens_sequences));
//	seqC=(Ens_sequences*)malloc(sizeof(Ens_sequences));
	
	if (f == NULL){
		fprintf(stderr, "Erreur lors de l'ouverture du fichier %s\n", s);
	}

	n = GetEntier(f);
	printf("%d\n", n);
	Skip(f);
	m = GetEntier(f);
	printf("%d\n", m);
	SkipLine(f);

	matrice->n=n;
	matrice->m=m;
	
	//allocation de la matrice dans la memoire
	matrice->mat=(int**)malloc(sizeof(int*)*n);
	for(int i=0;i<n;i++){
		matrice->mat[i]=(int*)malloc(sizeof(int)*m);
	}
	
	//initialisation de la matrice à 0
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			matrice->mat[i][j]=0;
		}
	}

	//affichage de la matrice
	printf("Oh surprise voici la matrice non coloriee !\n");
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			printf("%d ",matrice->mat[i][j]);
		}
		printf("\n");
	}
	
	printf("\n");
	//initialisation du tableau des seq des lignes avec les valeurs lues dans le fichier et affichage sur le flux de sortie


	seqL->sequences=(Sequence**)malloc(sizeof(Sequence*)*n);
	seqL->taille=n;

	printf("Diable voici le tableau des sequences des lignes!\n");
	for(i=0;i<n;i++){ // pour chaque ligne de la matrice 
		taille_seqL= GetEntier(f); // taille de la séquence de la ligne i
		seqL->sequences[i]=(Sequence*)malloc(sizeof(Sequence)); 
		seqL->sequences[i]->taille=taille_seqL;
		seqL->sequences[i]->seq = (int*)malloc(sizeof(int)*taille_seqL); // allocation d'un tableau d'entiers de taille_seqL cases

		if (taille_seqL > 0){
			Skip(f);
			for(int l=0;l<taille_seqL;l++){ // pour chaque bloc de la séquence 
				seqL->sequences[i]->seq[l]=GetEntier(f);
				printf("%d ",seqL->sequences[i]->seq[l]);
				Skip(f);
			}
		}
		printf("\n");
	}
	
	printf("\n");
//initialisation du tableau des seq des colonnes avec les valeurs lues dans le fichier et affichage sur le flux de sortie
	
	seqC->sequences=(Sequence**)malloc(sizeof(Sequence*)*m);
	printf("Oh WTF ! voici le tableau des sequences des colonnes!\n");

	for(j=0;j<m;j++){
		taille_seqC= GetEntier(f);
		seqC->sequences[j]=(Sequence*)malloc(sizeof(Sequence));
		seqC->sequences[j]->taille=taille_seqC;
		seqC->sequences[j]->seq=(int*)malloc(sizeof(int)*taille_seqC);
		

		if (taille_seqC > 0){ // séquence non vide
			Skip(f); 
			for(l=0;l<taille_seqC;l++){ // pour chaque bloc de la séquence 
				seqC->sequences[j]->seq[l]=GetEntier(f);
				printf("%d ",seqC->sequences[j]->seq[l]);
				Skip(f);
			}
		}

		printf("\n"); 
	} 
	
	matrice->seqL = seqL;
	matrice->seqC = seqC;

	if (f)
		fclose(f);	
}

/* fonction qui, étant donné une ligne i entièrement coloriée de matrice, 
    vérifie si le coloriage respecte bien la séquence seqL 
*/
int compare_seq_ligne(int i, Matrice* matrice)
{
	int j=0;
	int k=0;
	int cpt=0;
	int m = matrice->m;
	Sequence *sequence = matrice->seqL->sequences[i];
	int taille_seqL = sequence->taille;
	
	for (j=0; j<m; j++){
		if (matrice->mat[i][j] == 2){ // case noire
			if (k>=taille_seqL){
				return 0;
			}
			cpt++;
			if (cpt > sequence->seq[k]){ // trop de cases noires 
				return 0;
			}
			if (cpt == sequence->seq[k]){ // bloc satisfait
				k++;
				cpt = 0;
			}
		}
		else { // case blanche
			if ((cpt>0) && (cpt < sequence->seq[k])){ // il manque des cases noires
				return 0;
			}
		}
	}

	return 1;
}


/* fonction qui, étant donné une colonne j entièrement coloriée de matrice, 
    vérifie si le coloriage respecte bien la séquence seqC
*/
int compare_seq_col(int j, Matrice* matrice)
{
	int i=0;
	int k=0;
	int cpt=0;
	int n = matrice->n;
	Sequence *sequence = matrice->seqC->sequences[j];
	int taille_seqC = sequence->taille;
	
	for (i=0; i<n; i++){
		if (matrice->mat[i][j] == 2){ // case noire
			if (k>=taille_seqC){ // blocs en trop
				return 0;
			}
			cpt++;
			if (cpt > sequence->seq[k]){ // trop de cases noires pour le bloc 
				return 0;
			}
			if (cpt == sequence->seq[k]){ // bloc satisfait
				k++;
				cpt = 0;
			}
		}
		else { // case blanche
			if ((cpt>0) && (cpt < sequence->seq[k])){ // il manque des cases noires
				return 0;
			}
		}
	}

	return 1;
}

