#include "biblio.h"


struct CellMorceau
{
    struct CellMorceau *suiv;
    int num;
    char *titre;
    char *artiste;
};

/* Cellule de l'arbre lexicographique */
typedef struct Noeud {
    struct Noeud *liste_car; //Liste des choix possibles des caractères 
    struct Noeud *car_suiv; //caractère suivant dans la chaine 
    CellMorceau *liste_morceaux; // liste des morceaux ayant le m^eme interprète 
    char car;
} Noeud;

struct Biblio {
    int nE; // nombre d''element contenus dans l'arbre 
    Noeud *A; //arbre lexicograpj=hique
};

Biblio *nouvelle_biblio(void){
    Biblio *B = (Biblio *) malloc ( sizeof(Biblio));
    /* Vérifie que la bibliothèque a bien été allouée */
    if (B ==NULL){
        printf("Erreur d'allocation de la Biblio\n");
        return NULL;
    }
    B->nE = 0;
    B->A = NULL;
    return B;
}

Noeud *nouveau_noeud(char c ){
    Noeud *N = (Noeud *) malloc (sizeof(Noeud));
    N->liste_car = NULL;
    N->car_suiv = NULL;
    N->liste_morceaux =NULL;
    N->car = c;
    return N;
}

CellMorceau *nouveau_morceau( const int num, const char *titre, const char *artiste){
    CellMorceau *B = (CellMorceau* ) malloc ( sizeof(CellMorceau));
    /* Vérifie que le morceau a bien été allouée */
    if (B ==NULL){
        printf("Erreur d'allocation de la CellMorceau\n");
        return NULL;
    }
    B->num = num; 
    B->titre = strdup(titre);
    B->artiste = strdup(artiste);
    B->suiv = NULL;
    return B;
}

void libere_CellMorceau( CellMorceau *list){
    /* Vérifie que la liste de morceaux exsite et qu'elle possède des morceaux */
    if(list == NULL)
        return;
    CellMorceau *tmp = list;
    while(list != NULL){ // Parcourt les morceaux de la liste
        tmp = list;
        list = list->suiv;
        free(tmp->titre);
        free(tmp->artiste);
        free(tmp);
    }
}

void libere_Noeud( Noeud *noeud){
    /* Vérifie que le noeud exsite */
    if (noeud == NULL)
        return;
    libere_CellMorceau(noeud->liste_morceaux);
    libere_Noeud(noeud->car_suiv);
    libere_Noeud(noeud->liste_car);
    free(noeud);
}

void libere_biblio ( Biblio *B){
    /* Vérifie que la bibliothèque exsite */
    if ( B == NULL )
        return ;
    libere_Noeud(B->A);
    free(B);
}

void afficheMorceau(CellMorceau *cell)
{
	printf("\t$L$ %8d $ %-32.32s $ %-32.32s $L$\n", cell->num, cell->titre, cell->artiste);
}

int affiche_CellMorceau( CellMorceau *list){
    printf("Musique(s) de  %s :\n",  list->artiste);
    CellMorceau *cell = list;
    int k;
    while (cell != NULL) { // Parcourt les morceaux de la liste
        afficheMorceau(cell);
        cell = cell->suiv;
        k++;
    }
    return k;
}

int afficheNoeud(const Noeud *noeud, int nE){
    /* Vérifie que le noeud exsite et que tous les morceaux n'ont pas été parcourus */
    if (noeud == NULL || nE == 0){
        return nE;
    }
    /* Vérifie que le noeud possède des morceaux */
    if (noeud->liste_morceaux != NULL){
           nE -= affiche_CellMorceau(noeud->liste_morceaux);
    }
    nE = afficheNoeud(noeud->car_suiv, nE);
    nE = afficheNoeud(noeud->liste_car, nE);
    return nE;
}

void affiche( Biblio *B ){
    /* Vérifie que la bibliothèque exsite */
    if (B == NULL){
        printf("La Biblioteque n'est pas alloué\n");
        return;
    }
    /* Vérifie que la bibliothèque possède des morceaux */
    if(B->A == NULL){
        printf("La biblioteque est vide\n");
        return;
    }
    afficheNoeud(B->A, B->nE);
    printf("Nombre de morceaux : %d\n \n", B->nE);
}

void insere_morceau(Noeud **noeud , int num , char *titre, char *artiste){
    /* Vérifie que le noeud exsite*/
    if ( *noeud == NULL){
        printf("Error");
        return;
    }
    CellMorceau *C = nouveau_morceau( num , titre , artiste);
    C->suiv = (*noeud)->liste_morceaux;
    (*noeud)->liste_morceaux = C;
}

/* Fonction créant les noeuds manquants pour les caractères manquants de l'artiste */
Noeud* insereArtiste (int num, char *titre, char *artiste, int i){
    Noeud *noeud = nouveau_noeud(artiste[i]);
    Noeud *cell = noeud;
    for (int k = i + 1; k < strlen(artiste); k++ ){
            cell->car_suiv = nouveau_noeud ( artiste[k] );;
            cell = cell->car_suiv;
    }
    insere_morceau(&cell, num , titre, artiste);
    return noeud;
}

void insere ( Biblio *B, int num, char *titre, char *artiste){
    int i = 0;
    Noeud *tmp, *cell;
    B->nE ++;
    if (B->A == NULL){ // si l'arbre est vide
        /* Créations des noeuds manquants */
        B->A = insereArtiste( num, titre, artiste, i);
        return;
    }
    cell = B->A;
    while (cell != NULL){  // Parcourt les noeuds de l'arbre
        if ( artiste[i] == cell->car){ // Vérifie que le caractère correspond à celui "actuel"
            i++;
            if ( artiste[i] == '\0' ){ // Vérifie si la fin de la chaîne de caractère a été atteinte
                insere_morceau(&cell, num , titre , artiste);
                return;
            }
            if ( cell->car_suiv != NULL){ // Vérifie que la liste de caractère possède encore des caractères
                cell = cell->car_suiv;
            } else {
                /* Créations des noeuds manquants */
                cell->car_suiv = insereArtiste(num, titre, artiste, i);
                return;
            }
        } else {
            tmp = cell;
            cell = cell->liste_car;
        }
    }
    cell = tmp;
    /* Créations des noeuds manquants */
    cell->liste_car = insereArtiste( num, titre, artiste, i);
}

int supprimeMorceauParNumCellMorceau(CellMorceau **list, int num, int *nE)
{
	CellMorceau *tmp = NULL;
    CellMorceau *cell = *list;
    if ( cell->num == num ){ //Si le premier element doit etre supprime
        (*list) = (*list)->suiv;
        free(cell->titre);
        free(cell->artiste);
        free(cell);
        return 1;
    }
    tmp = cell;
    cell = cell->suiv;
    while( cell ){ // Parcourt les morceaux de la liste
        if ( cell->num == num ){ // Vérifie que le morcau est celui recherché
            tmp->suiv = cell->suiv;
            free(cell->titre);
            free(cell->artiste);
            free(cell);
            return 1;
        }
        else {
            tmp = cell;
            cell = tmp->suiv;
        }
        (*nE)--;
    }
    return 0;
}

int supprimerUnMorceauParNumNoeud(Noeud *noeud, int num, int *nE){
    /* Vérifie que la noeud exsite et que tous les morceaux n'ont pas été parcourus */
    if (noeud == NULL || *nE == 0)
        return 0;
    /* Vérifie que le noeud possède des morceaux */
    if (noeud->liste_morceaux != NULL){
        if (supprimeMorceauParNumCellMorceau(&noeud->liste_morceaux, num, nE))
            return 1;
        if (*nE == 0) // Vérifie que tous les morceaux n'ont pas été parcourus
            return 0;
    }
    /* Suite de tests pour savoir si la suppression a fonctionnée dans les noeuds suivants */
    if (supprimerUnMorceauParNumNoeud(noeud->car_suiv, num, nE))
        return 1;
    if (supprimerUnMorceauParNumNoeud(noeud->liste_car, num, nE))
        return 1;
    return 0; // La suppresion n'a pas fonctionnée
}

int supprimeMorceauParNum(Biblio *B, int num){
    /* Vérifie que la bibliothèque exsite*/
    if (B == NULL){
        printf("La Biblioteque n'est pas alloué\n");
        return 0;
    }
    int nE = B->nE; // Compteur pour savoir le nombre de morceaux non parcoourus
    if( supprimerUnMorceauParNumNoeud(B->A, num, &nE)){ // Test si la suppresion a lieu
        (B->nE)--;
        return 1;
    }
    printf("La suppression du morceau de numero %d n'a pas eu lieu\n",num);
    return 0;
}


CellMorceau *supprimerCellMorceau( Biblio *B, CellMorceau *list , char *titre){
    CellMorceau *tmp = list;
    if ( !strcmp(list->titre, titre)  ){ // Si le premier element doit etre supprime
        list = list->suiv;
        free(tmp->titre);
        free(tmp->artiste);
        free(tmp);
        (B->nE)--;
        return list;
    }
    CellMorceau *cell = list;
    cell = cell->suiv;

    while( cell ){ // Parcourt les morceaux de la liste
        if ( !strcmp(cell->titre, titre)  ){ // Test que le morcau est celui recherché
            tmp->suiv = cell->suiv;
            free(cell->titre);
            free(cell->artiste);
            free(cell);
            (B->nE)--;
            return list; 
        }
        else {
            tmp = cell;
            cell = cell->suiv;
        }
    }
    printf("La suppression du morceau %s de %s n'a pas eu lieu\n", titre, list->artiste);
    return list;
}

Biblio *supprimerUnMorceau(Biblio *B, char *titre, char *artiste){
    /* Vérifie que la bibliothèque possède des morceaux */
    if (B->A == NULL){
        return B;
    }
    int i = 0;

    Noeud *cell = B->A;
    while (cell){ // Parcourt de l'arbre
        if ( artiste[i] == cell->car){ // Vérifie que le caractère correspond au caractère "actuel" de l'artiste
            i++;
            if (artiste[i] == '\0'){ // Test si le dernier caractère du nom de l'artiste a été atteint
                cell->liste_morceaux = supprimerCellMorceau(B, cell->liste_morceaux, titre);
                return B;
            }
            cell = cell->car_suiv;
        } else {
            cell = cell->liste_car;
        }
    }
    printf("La suppression du morceau %s de %s n'a pas eu lieu\n", titre, artiste);
    return B;
}

int rechercheCellMorceauNumero(CellMorceau *C, int num, int *nE){
    /* Vérifie que la liste exsite */
    if (C == NULL)
        return 0;
    CellMorceau *cell = C;
    while ( cell ){ // Parcourt les morceaux
        if (cell->num == num){ // Vérifie que le morcau est celui recherché
            printf("\nLe morceau de numero %d correspond au titre suivant :\n" , num);
            afficheMorceau(cell);
            return 1;
        }
        cell = cell->suiv;
        (*nE)--;
    }
    return 0;
}

int rechercheNoeudNumero(Noeud *noeud, int num, int *nE){
    /* Vérifie que le noeud exsite et que tous les morceaux n'ont pas été parcourus */
    if (noeud == NULL || *nE == 0)
        return 0;
    /* Vérifie que la liste de morceaux exsite */
    if (noeud->liste_morceaux != NULL){
        if (rechercheCellMorceauNumero(noeud->liste_morceaux, num, nE))
            return 1;
        if (*nE == 0) // Vérifie que tous les morceaux n'ont pas été parcourus
            return 0;
    }
    /* Tests pour savoir si le morceau a été trouvé dans les noeuds suivants */
    if (rechercheNoeudNumero(noeud->car_suiv, num, nE))
        return 1;
    if (rechercheNoeudNumero(noeud->liste_car, num, nE))
        return 1;
    return 0;
}

void rechercheMorceauNumero(Biblio *B, int num){
    /* Vérifie que la bibliothèque exsite */
    if (B == NULL){
        printf("La Biblioteque est vide \n");
        return;
    }
    int nE = B->nE; // Compteur pour savoir le nombre de morceaux non parcoourus
    if( !rechercheNoeudNumero(B->A, num, &nE)){ // Test si le morceau a été trouvé
            printf("Le morceau de numero %d n'est pas dans cette biblioteque\n",num);
    }
}

int rechercheCellMorceauTitre(CellMorceau *C, char* titre, int *nE){
    /* Vérifie que la liste de morceaux exsite */
    if (C == NULL)
        return 0;
    CellMorceau *cell = C;
    while ( cell ){ // Parcourt la liste de morceaux
        if (!strcmp(cell->titre, titre)){ // Vérifie que le morcau est celui recherché
            printf( "\nLe morceau que vous recherchez est le suivant :\n");
            afficheMorceau(cell);
            return 1;
        }
        cell = cell->suiv;
        (*nE)--;
    }
    return 0;
}

int rechercheNoeudTitre(Noeud *noeud, char* titre, int *nE){
    /* Vérifie que le noeud exsite et que tous les morceaux n'ont pas été parcourus */
    if (noeud == NULL || *nE == 0)
        return 0;
    /* Vérifie que la liste de morceaux exsite */
    if (noeud->liste_morceaux != NULL){
        if (rechercheCellMorceauTitre(noeud->liste_morceaux, titre, nE))
            return 1;
        if (*nE == 0) // Vérifie que tous les morceaux n'ont pas été parcourus
            return 0;
    }
    /* Tests pour savoir si le morceau a été trouvé */
    if (rechercheNoeudTitre(noeud->car_suiv, titre, nE))
        return 1;
    if (rechercheNoeudTitre(noeud->liste_car, titre, nE))
        return 1;
    return 0;
}

void rechercheMorceauTitre(Biblio *B, char* titre){
    /* Vérifie que la bibliothèque exsite */
    if (B == NULL){
        printf("La Biblioteque est vide\n");
        return;
    }
    int nE = B->nE; // Compteur pour savoir le nombre de morceaux non parcoourus
    if ( !rechercheNoeudTitre(B->A, titre, &nE) ) // Vérifié si le morceau a été trouvé
        printf("Il n'y a aucun morceau %s dans cette biblioteque \n", titre);
}

void rechercheMorceauArtiste(Biblio *B, char* artiste){
    /* Vérifie que la bibliothèque exsite */
    if (B == NULL){
        printf("La Biblioteque pointe sur NULL\n");
        return;
    }
    Noeud *cell = B->A;
    int i = 0; 
    while(cell != NULL){ // Parcourt l'arbre
        if ( artiste[i] == cell->car){ // Vérifie que le caractère correspond au caractère "actuel" de l'artiste
            i++;
            if ( artiste[i] == '\0' ){ // Test si la fin du nom de l'artiste a été atteinte
                if (cell->liste_morceaux == NULL) // Vérifie qu'il y a des morceaux de l'artiste
                    break;
                affiche_CellMorceau(cell->liste_morceaux);
                return;
            }
            cell = cell->car_suiv;
        } else {
            cell=cell->liste_car;
        }
    }
    printf ( "Il n'y a aucun morceau de %s dans cette biblioteque\n", artiste);
}

/* Fonction utilisé dans uniques pour savoir si le morceau ne possède aucun doublon */
int RechercheDoublons( CellMorceau *list , CellMorceau *morceau){
    /* Vérifie que la liste exsite */
    if (list == NULL){
        return 0;
    }
    char *titre = morceau->titre;
	char *artiste = morceau->artiste;
    CellMorceau *cell = list;
    int une_fois = 0;
    while (cell){ // Parcourt la liste de morceaux
        if (!strcmp(cell->titre, titre) && !strcmp(cell->artiste, artiste) ){ // Vérifie que le morcau est celui recherché
            if (une_fois){ // Vérifie que c'est la 1ère occurrence du morceau
                return 0;
            }
            else{
                une_fois = 1;
            }
        }
        cell = cell->suiv;
    }
    return 1;
}

void uniquesNoeud(Noeud *noeud , Biblio *final, int *nE){
    /* Vérifie que le noeud exsite et que tous les morceaux n'ont pas été parcourus */
    if (noeud == NULL || *nE == 0){
        return;
    }
    /* Vérifie que la liste de morceaux n'est pas vide */
    if (noeud->liste_morceaux != NULL){
        CellMorceau *cell = noeud->liste_morceaux;
        while (cell){ // Parcourt la liste
            if ( RechercheDoublons(noeud->liste_morceaux, cell) ){ // Vérifie que le morcau est celui recherché
                insere(final, cell->num, cell->titre, cell->artiste);
            }
            cell = cell->suiv;
            (*nE)--;
        }
        if (*nE == 0)
            return;
    }
    uniquesNoeud(noeud->car_suiv, final, nE);
    uniquesNoeud(noeud->liste_car, final, nE);
}

Biblio *uniques( Biblio *B){
    /* Vérifie que la bibliothèque exsite */
    if (B == NULL){
        printf ("La biblioteque pointe sur NULL ");
        return NULL;
    }
    Biblio *final = nouvelle_biblio();
    int nE = B->nE; // Compteur pour savoir le nombre de morceaux non parcoourus
    uniquesNoeud(B->A, final, &nE);
    return final;
}
