/* biblio.h */

#ifndef  biblio_h
#define  biblio_h

#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Biblio Biblio;
typedef struct CellMorceau CellMorceau;

/* Alloue et retourne l'adresse d'une nouvelle Biblio */
Biblio *nouvelle_biblio(void);

/* Charge au plus n morceaux par lecture du fichier nom_fichier */
Biblio *charge_n_entrees(const char *nom_fichier, int n);

/*Libère intégralement la biblio */
void libere_biblio(Biblio *B);

/* Insère le morceau dont les caractéristiques sont num, titre et artiste*/
void insere(Biblio *B, int num, char *titre, char *artiste);


/*Affiche un morceau */
void afficheMorceau(CellMorceau *);

/*Affiche les morceaux contenus dans la Biblio */
void affiche(Biblio *B);

/* Retourne une nouvelle biblio contenant les morceaux de B sans doublons */
Biblio *uniques(Biblio *B);

/* printf dans un fichier.txt le temps CPU que prend la fonction unique en fonction du nombre de morceaux*/
void uniques_graphe(int borne_inf , int pas, int borne_sup, char*fichier);

/* Supprime la premiere occurence du morceau de titre titre et d'artiste artiste de la Biblio B et revoie la biblio*/
Biblio *supprimerUnMorceau(Biblio *B, char *titre, char *artiste);

/* Supprime un morceau de numero num de la Biblio B et revoie la biblio*/
int supprimeMorceauParNum(Biblio *B, int num);

/* Affiche le seul morceau de numéro num */
void rechercheMorceauNumero(Biblio *B, int num);
/* Affiche une nouvelle biblio qui contient uniquement les morceaux de l'artiste artiste */
void rechercheMorceauArtiste(Biblio *B , char *artiste);
/* Affiche un morceau de titre titre */
void rechercheMorceauTitre(Biblio *B , char *titre);

#endif /* biblio.h */
