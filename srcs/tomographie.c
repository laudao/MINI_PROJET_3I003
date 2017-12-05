#include "tomographie.h"

// fonction qui lit le contenu du fichiers et qui initialise la matrice avec le tableau des sequences des lignes
void fichierEnTableau(char* s, t_matrice* matrice){
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
//	printf("%d\n", n);
	Skip(f);
	m = GetEntier(f);
//	printf("%d\n", m);
	SkipLine(f);

	matrice->n=n;
	matrice->m=m;
	
	matrice->seqL = (t_ens_sequences*)malloc(sizeof(t_ens_sequences));
	matrice->seqC = (t_ens_sequences*)malloc(sizeof(t_ens_sequences));

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

//	//affichage de la matrice
//	printf("Oh surprise voici la matrice non coloriee !\n");
//	for(i=0;i<n;i++){
//		for(j=0;j<m;j++){
//			printf("%d ",matrice->mat[i][j]);
//		}
//		printf("\n");
//	}
	
	//initialisation du tableau des seq des lignes avec les valeurs lues dans le fichier et affichage sur le flux de sortie

	matrice->seqL->sequences=(t_sequence**)malloc(sizeof(t_sequence*)*n);
	matrice->seqL->taille=n;

//	printf("Diable voici le tableau des sequences des lignes!\n");
	for(i=0;i<n;i++){ // pour chaque ligne de la matrice 
		taille_seqL= GetEntier(f); // taille de la séquence de la ligne i
		matrice->seqL->sequences[i]=(t_sequence*)malloc(sizeof(t_sequence)); 
		matrice->seqL->sequences[i]->taille=taille_seqL;
		matrice->seqL->sequences[i]->seq = (int*)malloc(sizeof(int)*taille_seqL); // allocation d'un tableau d'entiers de taille_seqL cases

		if (taille_seqL > 0){
			Skip(f);
			for(l=0;l<taille_seqL;l++){ // pour chaque bloc de la séquence 
				matrice->seqL->sequences[i]->seq[l]=GetEntier(f);
	//			printf("%d ",matrice->seqL->sequences[i]->seq[l]);
				Skip(f);
			}
		}
//		printf("\n");
	}
	
//	printf("\n");
//initialisation du tableau des seq des colonnes avec les valeurs lues dans le fichier et affichage sur le flux de sortie
	
	matrice->seqC->sequences=(t_sequence**)malloc(sizeof(t_sequence*)*m);
	matrice->seqC->taille=m;
	//printf("Oh WTF ! voici le tableau des sequences des colonnes!\n");

	for(j=0;j<m;j++){
		taille_seqC= GetEntier(f);
		matrice->seqC->sequences[j]=(t_sequence*)malloc(sizeof(t_sequence));
		matrice->seqC->sequences[j]->taille=taille_seqC;
		matrice->seqC->sequences[j]->seq=(int*)malloc(sizeof(int)*taille_seqC);
		

		if (taille_seqC > 0){ // séquence non vide
			Skip(f); 
			for(l=0;l<taille_seqC;l++){ // pour chaque bloc de la séquence 
				matrice->seqC->sequences[j]->seq[l]=GetEntier(f);
	//			printf("%d ",matrice->seqC->sequences[j]->seq[l]);
				Skip(f);
			}
		}

		//printf("\n"); 
	} 
	
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

	if ((taille_seqL == 0) && (matrice->m==1))
		return 1;

	for (j=0; j<m; j++){
//		printf("(%d, %d) : %d\n", i, j, matrice->mat[i][j]);
		if (matrice->mat[i][j] == 2){ // case noire
			if (k>=taille_seqL){ // on a examiné tous les blocs et il y a une case noire en trop
	//			printf("Ligne %d : bloc %d (%d) non satisfait (plus de bloc à examiner et une case noire en trop)\n", i, k, sequence->seq[k]);
				return 0;
			}
			cpt++;
			if (cpt > sequence->seq[k]){ // trop de cases noires pour le bloc 
		//		printf("Ligne %d : bloc %d (%d) non satisfait à la case %d(trop de cases noires)\n", i, k, sequence->seq[k], j);
				return 0;
			}
		}
		else { // case blanche ou non coloriée
			if (k<taille_seqL){
				if (cpt == sequence->seq[k]){ // bloc satisfait
			//		printf("Ligne %d : bloc %d (%d) satisfait\n", i, k, sequence->seq[k]);
					k++;
					cpt=0;
				}
				else{
					if ((cpt>0) && (cpt < sequence->seq[k])){ // il manque des cases noires	
				//		printf("Ligne %d : bloc %d (%d) non satisfait (il manque des cases noires)\n", i, k, sequence->seq[k]);
						return 0;
					}
				}
			}
		}
	}

	if ((k == taille_seqL-1) && (cpt == sequence->seq[k]))
		return 1;

	if (k<taille_seqL){
	//	printf("Ligne %d : il manque au moins un bloc\n", i);
		return 0;
	}

	if ((k == 0) && (taille_seqL>0)){ // aucun bloc colorié mais séquence contient au moins un bloc
		//printf("Ligne %d : bloc %d (%d) non satisfait (aucun bloc colorié)\n", i, k, sequence->seq[k]);
		return 0;
	}

	return 1;
	
}

int compare_seq_col(int j, t_matrice* matrice)
{
	int i=0;
	int k=0;
	int cpt=0;
	int n = matrice->n;
	t_sequence *sequence = matrice->seqC->sequences[i];
	int taille_seqC = sequence->taille;
	
	if ((taille_seqC == 0) && (matrice->n==1))
		return 1;

	for (i=0; i<n; i++){
		if (matrice->mat[i][j] == 2){ // case noire
			if (k>=taille_seqC){ // on a examiné tous les blocs et il y a une case noire en trop
		//		printf("Colonne %d : bloc %d non satisfait (plus de bloc à examiner et une case noire en trop)\n", j, k);
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
				//	printf("Colonne %d : bloc %d (%d) satisfait\n", j, k, sequence->seq[k]);
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

	if ((k == taille_seqC-1) && (cpt == sequence->seq[k]))
		return 1;

	if (k<taille_seqC){
	//	printf("Ligne %d : il manque au moins un bloc\n", i);
		return 0;
	}

	if ((k == 0) && (taille_seqC>0)){ // aucun bloc colorié mais séquence contient au moins un bloc
//		printf("Colonne %d : bloc %d (%d) non satisfait (aucun bloc colorié)\n", j, k, sequence->seq[k]);
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
		if ((i == n-1) && (j == m-1)){
			return 1;
		}
		ok = (enumeration(k+1, 1, matrice)) || (enumeration(k+1, 2, matrice));
	}

	if ((!ok) && (raz)){
		matrice->mat[i][j] = 0;
	}
	return ok;
}

t_matrice* initialise_TT(int nbLignes, int nbColonnes){
	int i,j;
	t_matrice *TT = (t_matrice*)malloc(sizeof(t_matrice));
	TT->n = nbLignes;
	TT->m = nbColonnes;
	TT->mat=(int**)malloc(sizeof(int*)*(TT->n));	
		
	for(i=0;i<TT->n;i++){
		TT->mat[i] = (int*)malloc(sizeof(int)*(TT->m));
		for(j=0;j<TT->m;j++){
			TT->mat[i][j]=3; //non visité
		}
	}
	return TT;
}

void reinitialise_TT(t_matrice **TT)
{
	int i, j;
	for (i=0; i<(*TT)->n; i++){
		for (j=0; j<(*TT)->m; j++){
			(*TT)->mat[i][j] = 3;
		}
	}
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


	if(l==-1){ // séquence vide
		return testSiAucunLigne(matrice,i,0,j,2);
	} 
	
	L = matrice->seqL->sequences[i]->seq[l]; // nombre de cases dans le bloc l de la séquence de la ligne i
	if((l==0)&&(j==L-1)){
		return testSiAucunLigne(matrice,i,0,j,1);
	}
	
	if(j<=L-1){
		return 0;
	}
	
	if((TT->mat[j][l])!=3){
		return TT->mat[j][l];
	}
	
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
	return TT->mat[j][l];
}

int testVecteurColonne_Rec(t_matrice* matrice, int j, int i, int l, t_matrice *TT)
{
	int c1; //cas ou la case j est blanche
	int c2; //cas ou la case j est noire
	int L;

	if(l==-1){
		return testSiAucunCol(matrice,j,0,i,2);
	}
	
	L = matrice->seqC->sequences[j]->seq[l]; //L de l

	if((l==0)&&(i==L-1)){
		return testSiAucunCol(matrice,j,0,i,1);
	}
	
	if(i<=L-1){
		return 0;
	}
	
	if(TT->mat[i][l]!=3){
		return TT->mat[i][l];
	}
	
	if(matrice->mat[i][j]==2){
		c1=0;
	}
	else{
		c1=testVecteurColonne_Rec(matrice,j,i-1,l,TT);
	}
	
	if(!testSiAucunCol(matrice,j,i-(L-1),i,1)){
		c2=0;
	}
	else{
		if(matrice->mat[i-L][j]==2){
			c2=0;
		}
		else{
			c2=testVecteurColonne_Rec(matrice,j,i-L-1,l-1,TT);
		}
	}
	TT->mat[i][l]=c1||c2;
	return TT->mat[i][l];
}

int propagLigne(t_matrice* matrice, int i, int* marqueC, int *nb)
{
	int j;
 	int c1, c2;
 	int cptcolor;
 	int m;
	int l;

	l = matrice->seqL->sequences[i]->taille-1;
 	t_matrice* TT;
 	cptcolor = 0;
 	(*nb) = 0;
	m = matrice->m;
	TT = initialise_TT(m, matrice->seqL->sequences[i]->taille);

	for (j=(m-1); j>=0; j--){
		if (matrice->mat[i][j] == 0){
			matrice->mat[i][j] = 1;
			c1 = testVecteurLigne_Rec(matrice, i, m-1, l, TT);
			reinitialise_TT(&TT);
			matrice->mat[i][j] = 2;
			c2 = testVecteurLigne_Rec(matrice, i, m-1, l, TT);
			reinitialise_TT(&TT);
			matrice->mat[i][j] = 0;
			
			if ((!c1) && (!c2)){
				return 0;
			}
			if ((c1) && (!c2)){
				matrice->mat[i][j] = 1;	
				cptcolor++;
				if (!marqueC[j]){
					marqueC[j] = 1;
					(*nb)++;
				}
			}
			if ((!c1) && (c2)){
				matrice->mat[i][j] = 2;
				cptcolor++;
				if (!marqueC[j]){
					marqueC[j] = 1;
					(*nb)++;
				}
			}
		}
 	}
 	return 1;
}

int propagCol(t_matrice* matrice, int j, int* marqueL, int *nb)
{
	int i;
 	int c1, c2;
 	int cptcolor;
 	int n;
	int l;
 	t_matrice* TT;
 	cptcolor = 0;
 	*nb = 0;
	n = matrice->n;
	TT = initialise_TT(n, matrice->seqC->sequences[j]->taille);

	l = matrice->seqC->sequences[j]->taille-1;
	
	if (l == -1)
		return 1;

	for (i=n-1; i>=0; i--){
		if (matrice->mat[i][j] == 0){
			matrice->mat[i][j] = 1;
			c1 = testVecteurColonne_Rec(matrice, j, n-1, l, TT);
			reinitialise_TT(&TT);
			matrice->mat[i][j] = 2;
			c2 = testVecteurColonne_Rec(matrice, j, n-1, l, TT);
			reinitialise_TT(&TT);
			matrice->mat[i][j] = 0;
			if ((!c1) && (!c2)){
				return 0;
			}
			if ((c1) && (!c2)){
				matrice->mat[i][j] = 1;
				cptcolor++;
				if (!marqueL[i]){
					marqueL[i] = 1;
					(*nb)++;
				}
			}
			if ((!c1) && (c2)){
				matrice->mat[i][j] = 2;
				cptcolor++;
				if (!marqueL[i]){
					marqueL[i] = 1;
					(*nb)++;
				}
			}

		}
 	}
 	return 1;
}

int propagation(t_matrice *matrice)
{
	int *marqueL, *marqueC;
	int nbmL, nbmC, nb;
	int i, j;
	int ok;
	int n, m;

	n = matrice->n;
	m = matrice->m;

	ok = 1;
	marqueL = (int*)malloc(sizeof(int)*n);
	for (i=0; i<n; i++)
		marqueL[i] = 1;
	marqueC = (int*)malloc(sizeof(int)*m);
	for (j=0; j<m; j++)
		marqueC[j] = 1;

	nbmL = n;
	nbmC = m;
	j=0;
	printf("n = %d m = %d\n", n, m);
	while ((ok) && ((nbmL != 0) || (nbmC != 0))){
		i = 0;
		while ((ok) && (i<n)){
			if (marqueL[i]){
				ok = propagLigne(matrice, i, marqueC, &nb);
				nbmC += nb;
				marqueL[i] = 0;
				nbmL--;
			}
			i++;
		}
		j=0;
		while ((ok) && (j<m)){
			if (marqueC[j]){
				ok = propagCol(matrice, j, marqueL, &nb);
				nbmL += nb;
				marqueC[j] = 0;
				nbmC--;
			}
			j++;
		}
	}
	printf("nb = %d\n", nb);
	printf("nbmL = %d\n", nbmL);
	printf("nbmC = %d\n", nbmC);
	return ok;
}

int pourcentage_coloriees(t_matrice* matrice)
{
	int i, j;
	int n, m;
	int cpt;

	cpt=0;
	n = matrice->n;
	m = matrice->m;

	for (i=0; i<n; i++){
		for (j=0; j<m; j++){
			if (matrice->mat[i][j] == 0){
				cpt++;
			}
		}
	}
	return cpt;
}

void completer_coloriage(t_matrice *matrice)
{
	int i, j;
	int n, m;
	int res;

	n = matrice->n;
	m = matrice->m;

	for (i=0; i<n; i++){
		for (j=0; j<m; j++){
			if (matrice->mat[i][j] == 0){
				res = enumeration((i*n)+j, 1, matrice)||enumeration((i*n)+j,2, matrice);
				if (res){
					printf("Coloriage complété pour la case (%d, %d)\n", i, j);
				}
			}
		}
	}
}
