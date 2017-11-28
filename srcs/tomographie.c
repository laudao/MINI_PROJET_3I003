#include "tomographie.h"


// fonction qui lit le contenu du fichiers et qui initialise la matrice avec le tableau des sequences des lignes
void fichierEnTableau(char* s, t_matrice* matrice, t_ens_sequences* seqL, t_ens_sequences* seqC){
	int taille_seqC=0;
	int taille_seqL=0;
	int l=0;
	int i=0;
	int j=0;
	int m=0;
	int n=0;
	FILE* f=NULL;

	f=fopen(s,"r");
	
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
	for(i=0;i<n;i++){
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


	seqL->sequences=(t_sequence**)malloc(sizeof(t_sequence*)*n);
	seqL->taille=n;

	printf("Diable voici le tableau des sequences des lignes!\n");
	for(i=0;i<n;i++){ // pour chaque ligne de la matrice 
		taille_seqL= GetEntier(f); // taille de la séquence de la ligne i
		seqL->sequences[i]=(t_sequence*)malloc(sizeof(t_sequence)); 
		seqL->sequences[i]->taille=taille_seqL;
		seqL->sequences[i]->seq = (int*)malloc(sizeof(int)*taille_seqL); // allocation d'un tableau d'entiers de taille_seqL cases

		if (taille_seqL > 0){
			Skip(f);
			for(l=0;l<taille_seqL;l++){ // pour chaque bloc de la séquence 
				seqL->sequences[i]->seq[l]=GetEntier(f);
				printf("%d ",seqL->sequences[i]->seq[l]);
				Skip(f);
			}
		}
		printf("\n");
	}
	
	printf("\n");
//initialisation du tableau des seq des colonnes avec les valeurs lues dans le fichier et affichage sur le flux de sortie
	
	seqC->sequences=(t_sequence**)malloc(sizeof(t_sequence*)*m);
	printf("Oh WTF ! voici le tableau des sequences des colonnes!\n");

	for(j=0;j<m;j++){
		taille_seqC= GetEntier(f);
		seqC->sequences[j]=(t_sequence*)malloc(sizeof(t_sequence));
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

void affiche_matrice(t_matrice* matrice){
	int i, j;
	for (i=0; i<matrice->n; i++){
		for (j=0; j<matrice->m; j++){
			printf("%d ", matrice->mat[i][j]);
		}
		printf("\n");
	}
}

/* fonction qui, étant donné une ligne i entièrement coloriée de matrice, 
    vérifie si le coloriage respecte bien la séquence seqL 
*/
int compare_seq_ligne(int i, t_matrice* matrice)
{
	int j=0;
	int k=0;
	int cpt=0;
	int m = matrice->m;
	t_sequence *sequence = matrice->seqL->sequences[i];
	int taille_seqL = sequence->taille;
	
	for (j=0; j<m; j++){
		if (matrice->mat[i][j] == 2){ // case noire
			if (k>=taille_seqL){ // on a examiné tous les blocs et il y a une case noire en trop
//				printf("Ligne %d : bloc %d (%d) non satisfait (plus de bloc à examiner et une case noire en trop)\n", i, k, sequence->seq[k]);
				return 0;
			}
			cpt++;
			if (cpt > sequence->seq[k]){ // trop de cases noires pour le bloc 
	//			printf("Ligne %d : bloc %d (%d) non satisfait (trop de cases noires)\n", i, k, sequence->seq[k]);
				return 0;
			}
		}
		else { // case blanche ou non coloriée
			if (k<taille_seqL){
				if (cpt == sequence->seq[k]){ // bloc satisfait
	//			printf("Ligne %d : bloc %d (%d) satisfait\n", i, k, sequence->seq[k]);
					k++;
					cpt=0;
				}
				else{
					if ((cpt>0) && (cpt < sequence->seq[k])){ // il manque des cases noires	
			//			printf("Ligne %d : bloc %d (%d) non satisfait (il manque des cases noires)\n", i, k, sequence->seq[k]);
						return 0;
					}
				}
			}
		}
	}

	if ((k == 0) && (taille_seqL>0)){ // aucun bloc colorié mais séquence contient au moins un bloc
		//printf("Ligne %d : bloc %d (%d) non satisfait (aucun bloc colorié)\n", i, k, sequence->seq[k]);
		return 0;
	}else{
		return 1;
	}
}

int compare_seq_col(int j, t_matrice* matrice)
{
	int i=0;
	int k=0;
	int cpt=0;
	int n = matrice->n;
	t_sequence *sequence = matrice->seqC->sequences[i];
	int taille_seqC = sequence->taille;
	
	for (i=0; i<n; i++){
		if (matrice->mat[i][j] == 2){ // case noire
			if (k>=taille_seqC){ // on a examiné tous les blocs et il y a une case noire en trop
			//	printf("Colonne %d : bloc %d non satisfait (plus de bloc à examiner et une case noire en trop)", j, k);
				return 0;
			}
			cpt++;
			if (cpt > sequence->seq[k]){ // trop de cases noires pour le bloc 
			//	printf("Colonne %d : bloc %d (%d) non satisfait (trop de cases noires)\n", j, k, sequence->seq[k]);
				return 0;
			}
		}
		else { // case blanche ou non coloriée
			if (k<taille_seqC){
				if (cpt == sequence->seq[k]){ // bloc satisfait
					//printf("Colonne %d : bloc %d (%d) satisfait\n", j, k, sequence->seq[k]);
					k++;
					cpt=0;
				}
				else{
					if ((cpt>0) && (cpt < sequence->seq[k])){ // il manque des cases noires
					//	printf("Colonne %d : bloc %d (%d) non satisfait (il manque des cases noires)\n", j, k, sequence->seq[k]);
						return 0;
					}
				}
			}
		}
	}

	if ((k == 0) && (taille_seqC>0)){ // aucun bloc colorié mais séquence contient au moins un bloc
	//	printf("Colonne %d : bloc %d (%d) non satisfait (aucun bloc colorié)\n", j, k, sequence->seq[k]);
		return 0;
	}else{
		return 1;
	}
}

int enumeration(int k, int c, t_matrice* matrice)
{
	int ok;
	int raz;
	int i,j;
	int n, m;

	n = matrice->n;
	m = matrice->m;

	i = floor(k/m);
	j = k % m;

	printf("i : %d  j: %d n*m : %d\n", i, j, n*m);

	if (matrice->mat[i][j] == 0){
		matrice->mat[i][j] = c;
		raz = 1;
	}
	else{
		if (matrice->mat[i][j] != c){
			return 0;
		}
		else {
			raz = 0;
		}
	}
	ok = 1;
	if (i == (n-1))
		ok = compare_seq_col(j, matrice);
	if ((ok) && (j == (m-1)))
		ok = compare_seq_ligne(i, matrice);
	
	if (ok){
		if ((i == n-1) && (j == m-1))
			return 1;
		ok = ((enumeration(k+1, 1, matrice)) + (enumeration(k+1, 2, matrice)));
	}
	if ((!ok) && (raz))
		matrice->mat[i][j] = 0;
	
	return ok;
}

t_matrice* initialise_TT(int taille, int k){
	int i,j;
	t_matrice *TT = (t_matrice*)malloc(sizeof(t_matrice));
	TT->n=taille;
	TT->m=k;
	TT->mat=(int**)malloc(sizeof(int*)*(TT->n));	
		
	for(i=0;i<TT->n;i++){
		TT->mat[i] = (int*)malloc(sizeof(int)*(TT->m));
		for(j=0;j<TT->m;j++){
			TT->mat[i][j]=3;//non visite
		}
	}
	return TT;
}

int testSiAucunLigne(t_matrice *matrice, int i, int j1, int j2, int couleur)
{
	int* V = matrice->mat[i];
	int j;
	for(j=j1; j<=j2; j++){
		if (V[j] == couleur){
			return 0;
		}
	}
	return 1;
}

int testSiAucunCol(t_matrice *matrice, int j, int i1, int i2, int couleur)
{
	int i;
	for (i=i1; i<=i2; i++){
		if (matrice->mat[i][j] == couleur){
			return 0;
		}
	}
	return 1;
}

int testVecteurLigne_Rec(t_matrice* matrice, int i, int j, int l, t_matrice *TT)
{
	int c1; //cas ou la case j est blanche
	int c2; //cas ou la case j est noire
	int L; //L de l

	if(l==-1){
		return testSiAucunLigne(matrice,i,0,j,2);
	}
	
	L = matrice->seqL->sequences[i]->seq[l];
	
	if((l=0)&&(j=L-1)){
		return testSiAucunLigne(matrice,i,0,j,1);
	}
	
	if(j<=L-1){
		return 0;
	}
	
	if((TT->mat[j][l])!=3){
		return TT->mat[j][l];
	}
	printf("Diable\n");
	if(matrice->mat[i][j]==2){
		c1=0;
	}
	else{
		c1=testVecteurLigne_Rec(matrice,i,j-1,l,TT);
	}
	
	if(!testSiAucunLigne(matrice,i,j-(L-1),j,1)){
		c2=0;
	}
	else{
		if(matrice->mat[i][j-L]==2){
			c2=0;
		}
		else{
			c2=testVecteurLigne_Rec(matrice,i,j-L-1,l-1,TT);
		}
	}

	TT->mat[j][l]=c1||c2;
	printf("TT[%d][%d] = %d\n", j, l, TT->mat[j][l]);
	return TT->mat[j][l];
}

int testVecteurColonne_Rec(t_matrice* matrice, int i, int j, int l, t_matrice *TT)
{
	int c1; //cas ou la case j est blanche
	int c2; //cas ou la case j est noire
	int L = matrice->seqC->sequences[j]->seq[l]; //L de l
	
	if(l==0){
		return testSiAucunCol(matrice,j,0,i,2);
	}
	
	if((l==1)&&(i=L-1)){
		return testSiAucunCol(matrice,j,0,i,1);
	}
	
	if(i<=L-1){
		return 0;
	}
	
	if(TT->mat[i][j]!=3){
		return TT->mat[i][j];
	}
	
	if(matrice->mat[i][j]==2){
		c1=0;
	}
	else{
		c1=testVecteurColonne_Rec(matrice,i-1,j,l,TT);
	}
	
	if(!testSiAucunCol(matrice,j,i-(L-1),i,1)){
		c2=0;
	}
	else{
		if(matrice->mat[i-L][j]==2){
			c2=0;
		}
		else{
			c2=testVecteurColonne_Rec(matrice,i-L-1,j,l-1,TT);
		}
	}
	TT->mat[i][l]=c1||c2;
	printf("TT[%d][%d] = %d\n", i, l, TT->mat[i][l]);
	return TT->mat[i][l];
}
