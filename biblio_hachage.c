#include <math.h>

#include "biblio.h"

#define TAILLE 524288

struct CellMorceau {
    struct CellMorceau *suiv;
    unsigned int cle;
    int num;
    char *titre;
    char *artiste;
};

struct Biblio {
    int nE; /* nombre d''elements contenus dans la table de hachage*/
    int m; /* taille de la table de hachage */
    CellMorceau **T; /* table avec resolution des collisions par chainage*/
};

CellMorceau **nouveau_tableau(int m){
    CellMorceau **tab = (CellMorceau **) malloc(sizeof(CellMorceau) * m);
    for (int i = 0; i<m ; i++){
        tab[i] = NULL;
    }
    return tab;
}

Biblio *nouvelle_biblio(void){
    Biblio *B = (Biblio *) malloc ( sizeof(Biblio));
    if (B == NULL){
        printf("Erreur d'allocation de la Biblio\n");
        return NULL;
    }
    B->nE = 0;
    B->m = TAILLE;
    B->T = nouveau_tableau(TAILLE);
    return B;
}

void afficheMorceau(CellMorceau *cell)
{
	printf("\t$L$ %8d $ %-32.32s $ %-32.32s $L$\n", cell->num, cell->titre, cell->artiste);
}

/* Fonction calculant le nombre de collisions par case et le nombre total */
/* Permet de déterminer la meilleure fonction de hachage */
void collision(CellMorceau *list, int *cpt){
    CellMorceau *cell = list;
    int taille = 10;
    char **tab = (char **) malloc(sizeof(char*) * taille);
    for( int i = 1; i<taille; i++){
        tab[i] = NULL;
    }
    int cptlocal = -1;
    int i = 0;
    int k = 0;
    while (cell){ // Parcourt des morceaux
        for (k = 0 ; k <= cptlocal; k++){
            if ( !strcmp(cell->artiste, tab[k]) ){ // Vérifie que le morcau est celui recherché
                i=1;
                break;
            }
            
        }
        if (i == 1 ){
            i=0;
        }
        else{
            if (taille == cptlocal+1){
                taille = taille *2;
                tab = (char **)realloc(tab , sizeof(char*)*taille );
                for( int j = cptlocal+1; j < taille + 1; j++){
                    tab[j]=NULL;
                }
            }
            cptlocal++;
            tab[cptlocal]= strdup(cell->artiste);
        }
        cell=cell->suiv;
    } 
    for( int i = 0; i<taille; i++){
        free(tab[i]);
    }
    free(tab);
    *cpt = *cpt + cptlocal;
    printf("Nombre de collisions dans la case : %d\n", cptlocal);
}

void affiche_CellMorceau( CellMorceau *list, int *i){
    CellMorceau *cell = list;
    while (cell){ // Parcourt des morceaux
        afficheMorceau(cell);
        cell= cell->suiv;
        *i=*i+1;
    }
}


void affiche(Biblio *B){
    /* Vérifie que la bibliothèque exsite */
    if ( B == NULL){
        printf("Erreur la biblioteque n'est pas alloue\n");
        return;
    }
    /* Vérifie que la bibliothèque possède des morceaux */
    if (B->nE == 0){
        printf("La bibliothèque est vide\n");
        return;
    }
    int i = 0; // Compte le nombre de morceaux parcourus
    int k = 0; // Compte le nombre de cases parcourues dans le tableau
    int nE= B->nE; 
    int m = B->m;
    int cpt = 0;
    CellMorceau **tab = B->T;
    while ( i<nE && k<m ){ // Parcourt des morceaux
        if (tab[k] != NULL){ // Vérifie que la case existe
            if (tab[k]->artiste != NULL && tab[k]->titre != NULL){ // Vérifie que la case n'est pas vide
                printf("Case %d :\n", k);
                affiche_CellMorceau(tab[k], &i);
            }
            collision(tab[k], &cpt);
        }
        k++;
    }
    printf("\nNombre de morceaux totale: %d\n", B->nE);
    printf("Nombre de collision totale: %d\n \n", cpt);
}

void libere_CellMorceau( CellMorceau *list, int *i){
    CellMorceau *tmp = list;
    CellMorceau *tmp1 = NULL;
    while (tmp->suiv != NULL){ // Parcourt des morceaux de la case
        free(tmp->titre);
        free(tmp->artiste);
        tmp1 = tmp;
        tmp = tmp ->suiv;
        free(tmp1);
        *i=*i+1;
    }
    free(tmp->titre);
    free(tmp->artiste);
    free(tmp);
}

void libere_biblio( Biblio *B){
    int i = 0; // Compte le nombre de morceaux parcourus
    int k = 0; // Compte le nombre de cases parcourues dans le tableau
    int nE= B->nE; 
    int m = B->m;
    CellMorceau **tab = B->T;
    while ( i<nE && k<m){ // Parcourt des cases de la table
        if ( (B->T)[k] != NULL ){ // Vérifie que la case n'est pas vide
            libere_CellMorceau( tab[k] , &i);
        }
        k++;
    }
    free(B->T);
    free(B);
}

unsigned int fonction_cle6(const char *artiste){
    int cle = 0;
    int len = strlen(artiste); 
    for (int i = 0; artiste[i] != '\0'; i++){
        
        if (i == len-1)
            cle= cle + (((artiste[i] << 16)|(artiste[i] << 16))^(artiste[i]));
        else
        {
            cle= cle + (((artiste[i] << 16)|(artiste[i] << 16))^(artiste[i+1]));
        }
        
    }
    return cle;
}

unsigned int fonction_cle2(const char *artiste){ // additions des caracteres ASSCI * l'index du caractère
    int cle = 0;
    for (int i = 0 ; artiste[i] != '\0'; i++){
        cle = cle + artiste[i]*(i+1);
    }
    return cle;
}

unsigned int fonction_cle(const char *artiste){ // additions des caracteres ASSCI
    int cle = 0;
    for (int i = 0 ; artiste[i] != '\0'; i++){
        cle = cle + artiste[i];
    }
    return cle;
}

unsigned int fonction_hachage(unsigned int cle, int m){
    double A =cle* ( sqrt(5) -1 ) /2;
    double L = floor( A ) ;
    double res= floor( m*( A - L ) ) ;
    return (int) res;
}


void insere ( Biblio *B, int num, char *titre, char *artiste){
    /* Vérifie que la bibliothèque exsite */
    if ( B == NULL){
        printf("L'insertion a echoue la biblioteque pointe vers NULL\n");
        return ;
    }
    /* Vérifie que la bibliothèque possède des morceaux */
    if ( B->T == NULL){
        printf("L'insertion a echoue le tableau de la biblioteque pointe vers NULL\n");
        return ;
    }
    B->nE++;
    unsigned int cle = fonction_cle2(artiste);
    unsigned int hach = fonction_hachage(cle , B->m);
    CellMorceau **tab = B->T;
    CellMorceau *cell = ( CellMorceau *) malloc(sizeof(CellMorceau));
    cell->artiste = strdup(artiste);
    cell->titre = strdup(titre);
    cell->num = num;
    cell->cle = cle;
    if (tab[hach] == NULL){ // si la case de la table de hachage est vide
        cell->suiv = NULL;
        tab[hach] = cell;
    }
    else{
        cell->suiv = tab[hach];
        tab[hach]= cell ;   
    }   
}

/* Fonction vérifiant que le morceau ne possède pas de doublon */
int RechercheDoublons ( CellMorceau *list , CellMorceau *morceau){
    CellMorceau *cell = list;
    char *titre = morceau->titre;
	char *artiste = morceau->artiste;
    int une_fois = 0;
    while ( cell ){ // Parcourt des morceaux
        if (!strcmp(cell->titre,titre) && !strcmp(cell->artiste,artiste) ){ // Vérifie que le morcau est celui recherché

            if (une_fois){
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

Biblio *uniques(Biblio *B){
    /* Vérifie que la bibliothèque exsite */
    if( B == NULL){
        printf("La biblioteque pointe vers NULL\n");
        return NULL;
    }
    Biblio *final = nouvelle_biblio();
    /* Vérifie que la bibliothèque possède des morceaux */
    if (B->T == NULL){
        printf("La table de hachage pointe vers NULL");
        return final;
    } 
    int i = 0; // Compte le nombre de morceaux parcourus
    int k = 0; // Compte le nombre de cases parcourues dans le tableau
    int nE= B->nE; 
    int m = B->m;
    CellMorceau **tab = B->T;
    CellMorceau *cell;
    while( i<nE && k<m){ // Parcourt des morceaux
        if (tab[k] != NULL){  // Si la case du tableau est non vide
            cell = tab[k];
            while( cell){ // Applique la fonction unique a chaque liste de morceaux d'une case
                if (RechercheDoublons(tab[k] ,cell)){
                    insere( final , cell->num, cell->titre , cell->artiste);
                }
                cell= cell->suiv;
                i++;
            }       
        }
        k++;
    }
    return final;
}

int supprimeMorceauParNum(Biblio *B, int num)
{
    /* Vérifie que la bibliothèque exsite */
    if( B == NULL){
        printf("La biblioteque pointe vers NULL\n");
        return 0 ;
    }
    if (B->nE == 0){
        printf("La bibliotheque est vide");
        return 0;
    }
    int i = 0;
    int k = 0;
    int m = B->m;
    int nE = B->nE;
    CellMorceau **tab = B->T;
    CellMorceau *trash;
    CellMorceau *cell;
    CellMorceau *tmp;
    
    while( i<nE && k<m){ // Parcourt des case de la table
        if (tab[k] != NULL){ // Vérifie que la case n'est pas vide
            if ( (tab[k]->num)==num ){ //Si le morceau à supprimer est le premier morceau de la liste à tab[i]
                trash = tab[k];
                tab[k]= tab[k]->suiv;
                free(trash->titre);
                free(trash->artiste);
                free(trash);
                (B->nE)--; 
                return 1;
            }
            cell = tab[k];
            tmp = cell;
            cell = cell->suiv;
            i++;
            while( cell ){ // Parcourt des morceaux de la case
                if ( cell->num==num ){ // Vérifie que le morcau est celui recherché
                    trash = cell ;
                    tmp->suiv= cell->suiv;
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
                i++;
            }
        }
        k++;
    }
    printf("La suppression du morceau de numero %d n'a pas eu lieu\n", num);
    return 0;
}

Biblio *supprimerUnMorceau(Biblio *B, char *titre, char *artiste){
    /* Vérifie que la bibliothèque exsite */
    if( B == NULL){
        printf("La bibliotheque pointe vers NULL\n");
        return B ;
    }
    /* Vérifie que la bibliothèque possède des morceaux */
    if (B->nE == 0){
        printf("La bibliotheque est vide");
        return B;
    }
    unsigned int cle = fonction_cle2(artiste);
    unsigned int hach = fonction_hachage(cle , B->m);
    CellMorceau **tab = B->T;
    if (tab[hach] == NULL){ // Si la case de la table d'hachage est vide
        printf("La suppression du morceau %s de %s n'a pas eu lieu\n", titre, artiste);
        return B;
    }
    CellMorceau *trash;
    if ( ! strcmp(tab[hach]->titre, titre )  && !strcmp(tab[hach]->artiste,artiste) ){ //Si le morceau à supprimer est le premier morceau de la liste à tab[hach]
        trash = tab[hach];
        tab[hach]= tab[hach]->suiv;
        free(trash->titre);
        free(trash->artiste);
        free(trash);
        (B->nE)--; 
        return B;
    }
    CellMorceau *cell= tab[hach];
    CellMorceau *tmp = cell;
    cell = cell->suiv;
    while( cell ){ // Parcourt des morceaux
        if ( !strcmp(cell->titre,titre) && !strcmp(cell->artiste,artiste) ){ // Vérifie que le morcau est celui recherché
            trash = cell ;
            tmp->suiv= cell->suiv;
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
    printf("La suppression du morceau %s de %s n'a pas eu lieu\n", titre,artiste);
    return B;
}

void rechercheMorceauNumero(Biblio *B, int num){
    /* Vérifie que la bibliothèque exsite */
    if( B == NULL){
        printf("La biblioteque pointe vers NULL\n");
        return ;
    }
    /* Vérifie que la bibliothèque possède des morceaux */
    if (B->nE == 0){
        printf("La Bibliothèque est vide");
        return;
    }
    int i = 0; // Compte le nombre de morceaux parcourus
    int k = 0; // Compte le nombre de cases parcourues dans le tableau
    int nE= B->nE; 
    int m = B->m;
    CellMorceau **tab = B->T;
    CellMorceau *cell;
    while( i<nE && k<m){ // Parcourt de la table de hachage
        if (tab[k] != NULL){ // Si la case du tableau est non vide
            cell = tab[k];
            while( cell){ // Parcourt des morceaux
                if (num == cell->num){ // Compare pour chaque CellMorceau si le numéro est le meme
                    printf("Le morceau numero %d est le suivant : \n", num);
                    printf("%d\t%s\t%s\n", cell->num, cell->titre, cell->artiste);
                    return;
                }
                cell= cell->suiv;
                i++;
            }       
        }
        k++;
    }
    printf("Il n'y a pas de morceaux de numero %d dans cette biblioteque\n", num);
}

void rechercheMorceauArtiste(Biblio *B , char *artiste){
    /* Vérifie que la bibliothèque exsite */
    if( B == NULL){
        printf("La biblioteque pointe vers NULL\n");
        return ;
    }
    /* Vérifie que la bibliothèque possède des morceaux */
    if (B->nE == 0){
        printf("La bibliothèque est vide");
        return;
    }
    unsigned int cle = fonction_cle2(artiste);
    unsigned int hach = fonction_hachage(cle , B->m);
    CellMorceau **tab = B->T;
    if (tab[hach] == NULL){ // Si la case de la table d'hachage est vide
        printf("Il n'y a pas de morceaux de %s dans la biblioteque\n" , artiste);
        return;
    }
    int bool=0;
    CellMorceau *cell = tab[hach];
    while(cell){ // Parcourt des morceaux
        if ( !strcmp(cell->artiste,artiste) ){ // Vérifie que le morcau est celui de l'artiste recherché
            if (bool == 0){ // Message à mettre avant le premier morceau de l'artiste
                printf("\nLes morceaux de %s sont les suivants :\n" , artiste);
                bool = 1;
            }
            printf("%d\t%s\t%s\n", cell->num, cell->titre, artiste);
        }
        cell = cell->suiv;
    }
    printf("\n");
    if (!bool) // Si la bibliothèque n'a aucun morceau de l'artiste
        printf("Il n'y a pas de morceaux de %s dans cette biblioteque\n",artiste);
    
}

void rechercheMorceauTitre(Biblio *B , char *titre){
    /* Vérifie que la bibliothèque exsite */
    if( B == NULL){
        printf("La biblioteque pointe vers NULL\n");
        return ;
    }
    /* Vérifie que la bibliothèque possède des morceaux */
    if (B->nE == 0){
        printf("La bibliothèque est vide");
        return;
    }
    int i = 0; // Compte le nombre de morceaux parcourus
    int k = 0; // Compte le nombre de cases parcourues dans le tableau
    int nE= B->nE; 
    int m = B->m;
    CellMorceau **tab = B->T;
    CellMorceau *cell;
    while( i<nE && k<m){ // Parcourt de la table de hachage
        if (tab[k] != NULL){  // Si la case du tableau est non vide
            cell = tab[k];
            while( cell){  // Parcourt les morceaux de la case
                if (! strcmp(titre , cell->titre)){ // Vérifie que le morcau est celui recherché
                    printf("Le morceau de titre %s est le suivant : \n", titre);
                    printf("%d\t%s\t%s\n", cell->num, cell->titre, cell->artiste);
                    return;
                }
                cell= cell->suiv;
                i++;
            }       
        }
        k++;
    }
    printf("Il n'y a pas de morceaux de titre %s dans cette biblioteque\n", titre);
}