#ifndef __TOMO_H__
#define __TOMO_H__	
#include "entree_sortie.h"

// Séquence 
typedef struct sequence{ 
	int taille; // nombre de blocs de la séquence 
	int* seq; // tableau dont chaque case représente le nombre de blocs à colorier
} Sequence;

// Ensemble des séquences de ligne/colonne à respecter 
typedef struct ens_seq{
	int taille; // correspond au nombre de lignes ou de colonnes de la matrice
	struct sequence** sequences; // tableau de pointeurs sur séquences
} Ens_sequences;

typedef struct matrice{
	int n; // nombre de lignes
	int m; // nombre de colonnes;
	Ens_sequences* seqL;
	Ens_sequences* seqC;
	int **mat; 
} Matrice;


void fichierEnTableau(char* s,Matrice* matrice,Ens_sequences* seqL,Ens_sequences* seqC);

int compare_seq_ligne(int i, Matrice* matrice);

int compare_seq_col(int j, Matrice* matrice);

//void fichierEnTableau(char* s,int** matrice,int** seqL,int** seqC);

#endif
