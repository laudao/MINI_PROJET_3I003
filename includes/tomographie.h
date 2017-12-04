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


void fichierEnTableau(char* s, t_matrice* matrice);

/* fonction qui, étant donné une ligne i entièrement coloriée de matrice,
     vérifie si le coloriage respecte bien la séquence de la ligne */
int compare_seq_ligne(int i, t_matrice* matrice);

/* fonction qui, étant donné une colonne j entièrement coloriée de matrice,
     vérifie si le coloriage respecte bien la séquence de la colonne */
int compare_seq_col(int j, t_matrice* matrice);

int enumeration(int k, int c, t_matrice* m);

void affiche_matrice(t_matrice *matrice);

t_matrice* initialise_TT(int nbLignes, int nbColonnes);

void reinitialise_TT(t_matrice** TT);

/* teste s'il n'existe aucune case de couleur couleur entre les cases
    j1 et j2 de la ligne i de la matrice */
int testSiAucunLigne(t_matrice *matrice, int i, int j1, int j2, int couleur);

/* teste s'il n'existe aucune case de couleur couleur entre les cases
    i1 et i2 de la colonne j de la matrice */
int testSiAucunCol(t_matrice *matrice, int j, int i1, int i2, int couleur);

int testVecteurLigne_Rec(t_matrice* matrice, int i, int j, int l, t_matrice *TT);

int testVecteurColonne_Rec(t_matrice* matrice, int j, int i, int l, t_matrice *TT);

int propagLigne(t_matrice* matrice, int i, int* marqueC, int *nb);

int propagCol(t_matrice* matrice, int j, int* marqueL, int *nb);

int propagation(t_matrice *matrice);

int pourcentage_coloriees(t_matrice* matrice);

void completer_coloriage(t_matrice *matrice);
#endif
