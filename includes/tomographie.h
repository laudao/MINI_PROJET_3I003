#ifndef __TOMO_H__
#define __TOMO_H__	
#include "entree_sortie.h"
#include <math.h>

// Séquence 
typedef struct sequence{ 
	int taille; // nombre de blocs de la séquence 
	int* seq; // tableau dont chaque case représente le nombre de blocs à colorier
} t_sequence;

// Ensemble des séquences de ligne/colonne à respecter 
typedef struct ens_seq{
	int taille; // correspond au nombre de lignes ou de colonnes de la matrice
	t_sequence** sequences; // tableau de pointeurs sur séquences
} t_ens_sequences;

typedef struct matrice{
	int n; // nombre de lignes
	int m; // nombre de colonnes;
	t_ens_sequences* seqL;
	t_ens_sequences* seqC;
	int **mat; 
} t_matrice;


void fichierEnTableau(char* s, t_matrice* matrice, t_ens_sequences* seqL, t_ens_sequences* seqC);

int compare_seq_ligne(int i, t_matrice* matrice);

int compare_seq_col(int j, t_matrice* matrice);

int enumeration(int k, int c, t_matrice* m);

void affiche_matrice(t_matrice *matrice);

t_matrice* initialise_TT(int taille, int k);

int testSiAucunLigne(t_matrice *matrice, int i, int j1, int j2, int couleur);

int testSiAucunCol(t_matrice *matrice, int j, int i1, int i2, int couleur);

int testVecteurLigne_Rec(t_matrice* matrice, int i, int j, int l, t_matrice *TT);

int testVecteurColonne_Rec(t_matrice* matrice, int i, int j, int l, t_matrice *TT);

#endif
