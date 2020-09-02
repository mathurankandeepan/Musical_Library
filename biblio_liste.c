#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblio.h"

struct CellMorceau
{
    struct CellMorceau *suiv;
    int num;
    char *titre;
    char *artiste;
};

struct Biblio {
    CellMorceau *L; /* Liste chainee des morceaux */
    int nE; /* Nombre de morceau dans la liste */
};

Biblio *nouvelle_biblio(void){
    Biblio *B;
    B = (Biblio *) malloc ( sizeof(Biblio));
    /* Vérification que la bibliothèque a été créée */
    if (B == NULL) {
        printf("Erreur d'allocation de la Biblio");
        return NULL;
    }
    B->L = NULL;
    B->nE = 0;
    return B;
}

CellMorceau *nouveau_morceau(const int num, const char *titre, const char *artiste){
    CellMorceau *B;
    B = (CellMorceau *) malloc(sizeof(CellMorceau));
    /* Vérification que la bibliothèque existe */
    if (B == NULL){
        printf("Erreur d'allocation de la CellMorceau");
        return NULL;
    }
    B->num = num; 
    B->titre = strdup(titre);
    B->artiste = strdup(artiste);
    B->suiv = NULL;
    return B;
}

void libere_biblio(Biblio *B){
    /* Vérification que la bibliothèque existe et qu'elle possède au moins un morceau */
    if (B == NULL || B->L == NULL){
        free(B);
        return;
    }
    CellMorceau *tmp = B->L;
    CellMorceau *tmp1 = NULL;
    while (tmp->suiv != NULL){ // Parcourt de l'ensemble des morceaux
        free(tmp->titre);
        free(tmp->artiste);
        tmp1 = tmp;
        tmp = tmp ->suiv;
        free(tmp1);
    }
    free(tmp->titre);
    free(tmp->artiste);
    free(tmp);
    free(B);
}

void insere(Biblio *B , int num , char *titre, char *artiste){
    /* Vérification que la bibliothèque existe */
    if (B == NULL){
        printf("L'insertion a echoue la biblioteque pointe vers NULL\n");
        return ;
    }
    B->nE++;
    /* Insertion en tête du morceau */
    CellMorceau *D = nouveau_morceau( num , titre , artiste);
    D->suiv = B->L;
    B->L = D;
}

void afficheMorceau(CellMorceau *cell)
{
	printf("$L$ %8d $ %-32.32s $ %-32.32s $L$\n", cell->num, cell->titre, cell->artiste);
}


void affiche( Biblio *B){
    /* Vérification que la bibliothèque existe */
    if (B==NULL){
		printf("La biblioteque n'est pas alloue'\n");
		return;
	}
    /* Vérification que la bibliothèque n'est pas vide */
    if (B->L==NULL){
		printf("La biblioteque est vide\n");
		return;
	}
    CellMorceau *cell = B->L;
    while (cell){ // Parcourt de l'ensemble des morceaux
        afficheMorceau(cell);
        cell = cell->suiv;
    }
        printf("Nombre de morceaux : %d \n", B->nE);
}

/* Fonction a utiliser dans "uniques" pour récupérer aucune occurence des doublons */
int RechercheDoublons ( Biblio *B , CellMorceau *list){
    CellMorceau *cell = B->L;
    char *titre = list->titre;
	char *artiste = list->artiste;
    int une_fois = 0;
    while( cell ){ // Parcourt de l'ensemble des morceaux
        if ( !strcmp(cell->titre, titre) && !strcmp(cell->artiste, artiste) ){ // Vérifie si le morceau correspond à celui cherché
            if (une_fois){ // Vérifie si c'est la première occurrence du morceau
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

Biblio *uniques (Biblio *B)
{
    /* Vérifie que la bibliothèque existe */
    if (B == NULL){
        printf("La biblioteque est null ");
        return B;
    }
    Biblio *final = nouvelle_biblio();
    /* Vérifie que la bibliothèque n'est pas vide */
    if (B->L == NULL)
        return final;
    CellMorceau *cell = B->L;
    while( cell ){ // Parcourt des morceaux la bibliothèque
        if (RechercheDoublons (B , cell)){ // Vérifie que le morceau possède aucun doublon
            insere( final , cell->num, cell->titre , cell->artiste);
        }
        cell= cell->suiv;
    }
    return final;
}

void supprimerTouslesMorceaux(Biblio *B, char *titre, char *artiste){
    /* Vérifie que la bibliothèque exsite et qu'elle possède des morceaux */
    if (B == NULL || B->L == NULL)
        return;
    CellMorceau *trash = NULL;
    if (!strcmp(B->L->titre,titre) && !strcmp(B->L->artiste,artiste) ){ // Si le premier element doit etre supprime
        trash = B->L;   
        B->L = B->L->suiv;
        free(trash->titre);
        free(trash->artiste);
        free(trash);
        supprimerTouslesMorceaux(B, titre, artiste); // Rappelle la fonction si jamais le nouveau premier est le morceau cherché
        (B->nE)--; 
        return;
    }
    CellMorceau *cell = B->L;
    CellMorceau *tmp = cell;
    cell = cell->suiv;

    while( cell ){ // Parcourt tous les morceaux
        if ( !strcmp(cell->titre,titre) && !strcmp(cell->artiste,artiste) ){ // Vérifie que le morceau est celui recherché
            trash = cell ;
            tmp->suiv= cell->suiv;
            cell = tmp->suiv;
            free(trash->titre);
            free(trash->artiste);
            free(trash);
            (B->nE)--; 
        }
        else {
            tmp = cell;
            cell = tmp->suiv;
        }
    }
}

int supprimeMorceauParNum(Biblio *B, int num)
{
    /* Vérifie que la bibliothèque exsite et qu'elle possède des morceaux */
	if (B == NULL || B->L == NULL)
        return 0;
    CellMorceau *trash = NULL;
	CellMorceau* tmp;
    CellMorceau *cell = B->L;
    if ( cell->num ==num ){ //Si le premier element doit etre supprime
        trash = cell; 
        B->L = cell->suiv;  
        free(trash->titre);
        free(trash->artiste);
        free(trash);
        (B->nE)--;
        return 1;
    }
    tmp = cell;
    cell = cell->suiv;

    while( cell ){ // Parcourt les morceaux de la bibliothèque
        if ( cell->num == num ){ // Vérifie que le morceau est celui recherché
            trash = cell ;
            tmp->suiv= cell->suiv;
            cell = tmp->suiv;
            free(trash->titre);
            free(trash->artiste);
            free(trash);
            (B->nE)--; 
            return 1;
        }
        else {
            tmp = cell;
            cell = tmp->suiv;
        }
    }
    printf("La suppression du morceau de numero %d a echoue\n",num);
    return 0;
}


Biblio *supprimerUnMorceau(Biblio *B, char *titre, char *artiste){
    /* Vérifie que la bibliothèque exsite et qu'elle possède des morceaux */
    if (B == NULL || B->L == NULL)
        return B;
    CellMorceau *trash = NULL;
    if ( !strcmp(B->L->titre,titre) && !strcmp(B->L->artiste,artiste) ){ //Si le premier element doit etre supprime
        trash = B->L; 
        CellMorceau* tmp = B->L->suiv;
        B->L = tmp;  
        free(trash->titre);
        free(trash->artiste);
        free(trash);
        (B->nE)--;
        return B;
    }
    CellMorceau *cell = B->L;
    CellMorceau *tmp = cell;
    cell = cell->suiv;

    while( cell ){ // Parcourt des morceaux
        if ( !strcmp(cell->titre,titre) && !strcmp(cell->artiste,artiste) ){
            trash = cell ;
            tmp->suiv= cell->suiv;
            cell = tmp->suiv;
            free(trash->titre);
            free(trash->artiste);
            free(trash);
            (B->nE)--; 
            return B;
        }
        else {
            tmp = cell;
            cell = tmp->suiv;
        }
    }
    printf("La suppression du morceau %s de %s n'a pas eu lieu\n", titre, artiste);
    return B;
}




void rechercheMorceauNumero(Biblio *B, int num){
    /* Vérifie que la bibliothèque exsite */
    if(B == NULL){
        printf( "\nLa Bibliotheque n'existe pas \n");
        return ;
    }
    /* Vérifie que la bibliothèque possède des morceaux */
    if (B->L == NULL){
        printf("\nLa Bibliotheque est vide");
        return;
    }
    CellMorceau *cell = B->L;
    while ( cell  ){ // Parcourt des morceaux
        if (cell->num == num){ // Vérifie que le morceau est celui recherché
            afficheMorceau(cell);
            return;
        }
        cell = cell->suiv;
    }
    printf("Le morceau %d n'est pas dans cette biblioteque\n",num);
}

void rechercheMorceauTitre(Biblio *B , char *titre){
    /* Vérifie que la bibliothèque exsite */
    if(B == NULL){
        printf( "\nLa Biblioteque pointe vers NULL \n");
        return ;
    }
    /* Vérifie que la bibliothèque possède des morceaux */
    if (B->L == NULL){
        printf("\nLa Bibliotheque est vide");
        return;
    }
    CellMorceau *cell = B->L;
    while ( cell ){ // Parcourt des morceaux
        if ( !strcmp(cell->titre,titre) ){ // Vérifie que le morcau est celui recherché
            printf( "\nLe morceau que vous recherchez est le suivant :\n");
            afficheMorceau(cell);
            return;
        }
        cell = cell->suiv;
    }
    printf( "\nIl n'y a aucun morceau de titre %s dans cette biblioteque\n", titre);
}

void rechercheMorceauArtiste(Biblio *B , char *artiste){
    /* Vérifie que la bibliothèque exsite */
    if(B == NULL){
        printf( "\nLa Biblioteque pointe vers NULL \n");
        return ;
    }
    /* Vérifie que la bibliothèque possède des morceaux */
    if (B->L == NULL){
        printf("\nLa Bibliotheque est vide");
        return;
    }
    int bool =0;
    CellMorceau *cell = B->L;
    while ( cell ){ // Parcourt des morceaux
        if ( !strcmp(cell->artiste,artiste) ){ // Vérifie que le morcau est celui recherché
            if (bool == 0){ // Regarde si c'est le premier morceau de l'artiste trouvé
                printf("\nLes morceaux de %s sont les suivants :\n" , artiste);
                bool = 1;
            }
            afficheMorceau(cell);
        }
        cell = cell->suiv;
    }
    printf("\n");
    if (!bool) // Si aucun morceau n'a été trouvé pour cet artiste
        printf("Il n'y a pas de morceaux de %s dans cette biblioteque\n",artiste);

}   