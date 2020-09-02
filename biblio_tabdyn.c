#include "biblio.h"

struct CellMorceau {
    char *titre;
    char *artiste;
    int num;
};

struct Biblio {
    int nE; /* Nombre de morceaux dans le tableau*/
    int capacite ; /* Capacite du tableau */
    CellMorceau *T; /* Tableau de morceaux */
};

Biblio *nouvelle_biblio(void) {
    Biblio *B = (Biblio*) malloc (sizeof(Biblio));
    B->nE = 0;
    B->capacite = 0;
    B->T = NULL;
    return B;
}

CellMorceau *nouveau_morceau( int num , char *titre, char *artiste){
    CellMorceau *M = (CellMorceau*) malloc(sizeof(CellMorceau));
    M->num = num;
    M->titre = strdup(titre);
    M->artiste = strdup(artiste);
    return M;
}

void afficheMorceau(CellMorceau *cell)
{
	printf("$L$ %8d $ %-32.32s $ %-32.32s $L$\n", cell->num, cell->titre, cell->artiste);
}

void affiche(Biblio *B){
    /* Vérification que la bibliothèque existe */
    if ( B == NULL){
        printf("Erreur la biblioteque n'est pas alloue\n");
        return;
    }
    /* Vérification que la bibliothèque possède au moins un morceau */
    if ( B->T == NULL){
        printf("La biblioteque est vide\n");
        return;
    }
    int i = 0; // Compte le nombre de morceaux parcourus
    int nE = B->nE;
    CellMorceau *tab = B->T;
    for (int k = 0; i < nE; k++){ // On parcout le tableau et on s'arrête lorsque tous les morceaux ont été parcourus
        if (tab[k].artiste != NULL && tab[k].titre != NULL){ // Vérifie que la case contient un morceau
            afficheMorceau( &(tab[k]) );
            i++;
        }
    }
    printf("Nombre de morceaux : %d\n \n", B->nE);
}

/* Libère la mémoire alloué par les strdup */
void libere_Morceau(CellMorceau *t){
    free(t->titre);
    free(t->artiste);
}

void libere_biblio( Biblio *B){
    if (B != NULL) { // Vérifie que la bibliothèque existe
        int i = 0; // Compte le nombre de morceaux parcourus
        int nE = B->nE;
        CellMorceau *tab = B->T;
        for (int k = 0; i < nE; k++) { // On parcout le tableau et on s'arrête lorsqu'on a parcourut tous les morceaux
            if ( &tab[k] != NULL ) { // Vérifie que la case contient un morceau
                libere_Morceau( &tab[k] );
                i++;
            }
        }
        free( B->T );
    }
    free( B );
}

void insere ( Biblio *B, int num, char *titre, char *artiste){
    /* Vérification que la bibliothèque existe */
    if ( B == NULL) {
        printf("L'insertion a echoue la biblioteque pointe vers NULL\n");
        return ;
    }
    /* Si la bibliothèque est vide, on cree un morceau et on l'ajoute à la bibliothèque */
    if (B->T == NULL) {
        B->T = nouveau_morceau(num, titre, artiste);
        B->nE = 1;
        B->capacite = 1;
        return;
    }
    /* Si le tableau est arrivé a sa capacite max, on double la capacité */
    if (B->nE == B->capacite) {
        B->capacite = B->capacite * 2;
        B->T = realloc(B->T, sizeof(CellMorceau) * B->capacite);
        for (int i = B->nE; i< (B->capacite); i++) {
            ((B->T)+ i)->titre = NULL;
            ((B->T)+ i)->artiste = NULL;
            ((B->T)+ i)->num = 0;
        }
    }
    /* Le tableau a de la place, on insere le morceau a la premiere place disponible */
    for (int i = 0; i < B->capacite; i++) {
        /* Recherche de la premiere case vide */
        if(((B->T) + i)->titre == NULL) {
            (B->T[i]).titre = strdup(titre);
            (B->T[i]).artiste = strdup(artiste);
            (B->T[i]).num = num;
            B->nE++;
            return;
        }
    }
}

int supprimeMorceauParNum(Biblio *B, int num)
{
    /* Vérification que la bibliothèque existe */
    if ( B == NULL) {
        printf("Erreur la biblioteque n'est pas alloue\n");
        return 0;
    }
    /* Vérification que la bibliothèque possède au moins un morceau */
    if ( B->T == NULL) {
        printf("La biblioteque est vide\n");
        return 0;
    }
    int i = 0; // Compte le nombre de morceaux parcourus
    int nE = B->nE;
    CellMorceau *tab = B->T;
    for (int k = 0; i < nE; k++) { // On parcout le tableau et on s'arrête lorsqu'on a parcourut tous les morceaux
        if ( tab[k].artiste != NULL && tab[k].titre != NULL) { // Vérifie que la case possède un morceau
            if ( tab[k].num == num ) { // Vérifie si le morceau correspond à celui cherché
                libere_Morceau(&tab[k]);
                tab[k].artiste = NULL;
                tab[k].titre = NULL;
                tab[k].num = 0;
                (B->nE)--;
                return 1;
            }
            i++;    
        }
    }
    printf("La suppression a echoue\n");
    return 0;
}

Biblio *supprimerUnMorceau(Biblio *B, char *titre, char *artiste){
    /* Vérification que la bibliothèque existe */
    if ( B == NULL) {
        printf("Erreur la biblioteque n'est pas alloue\n");
        return B;
    }
    /* Vérification que la bibliothèque possède au moins un morceau */
    if ( B->T == NULL) {
        printf("La biblioteque est vide\n");
        return B;
    }
    int i = 0; // Compte le nombre de morceaux parcourus
    int nE = B->nE; 
    CellMorceau *tab = B->T;
    for (int k = 0; i < nE; k++) { // On parcout le tableau et on s'arrête lorsqu'on a parcourut tous les morceaux
        if ( tab[k].artiste != NULL && tab[k].titre != NULL) { // Vérifie que la case possède un morceau
            if ( !strcmp(artiste, tab[k].artiste) && !strcmp(titre, tab[k].titre) ) { // Vérifie si le morceau correspond à celui cherché
                libere_Morceau(&tab[k]);
                tab[k].artiste = NULL;
                tab[k].titre = NULL;
                tab[k].num = 0;
                (B->nE)--;
                return B;
            }
            i++;    
        }
    }
    printf("La suppression a echoue\n");
    return B;
}

/* Fonction a utiliser dans "uniques" pour récupérer aucune occurence des doublons */
int RechercheDoublons ( Biblio *B , CellMorceau *list, int index){
    int i = 0; // Compte le nombre de morceaux parcourus
    int nE = B->nE;
    char *titre = list->titre;
	char *artiste = list->artiste;
    CellMorceau *tab = B->T;
    for (int k = 0; i < nE; k++) { // On parcout le tableau et on s'arrête lorsqu'on a parcourut tous les morceaux
        if ( tab[k].artiste != NULL && tab[k].titre != NULL) { // Vérifie que la case possède un morceau
            if ( !strcmp(artiste, tab[k].artiste) && !strcmp(titre, tab[k].titre) && k!=index ) { // Vérifie si le morceau correspond à celui cherché
                return 0;
            }
            i++;
        }
    }
    return 1;
}

Biblio *uniques(Biblio *B){
    /* Vérification que la bibliothèque existe */
    if (B == NULL){
        printf("La biblioteque est null ");
        return B;
    }
    Biblio *final = nouvelle_biblio();
    /* Vérification que la bibliothèque possède au moins un morceau */
    if (B->T == NULL){
        return final;
    }
    int i = 0; // Compte le nombre de morceaux parcourus
    int nE = B->nE;
    CellMorceau *tab = B->T;
    for (int k = 0; i < nE; k++){ // On parcout le tableau et on s'arrête lorsqu'on a parcourut tous les morceaux
        if ( tab[k].artiste != NULL && tab[k].titre != NULL ){ // Vérifie que la case possède un morceau
            if (RechercheDoublons ( B , &(tab[k]), k  )){ // Vérifie que le morceau n'a pas de doublon
                insere( final, tab[k].num, tab[k].titre , tab[k].artiste);
                tab = B->T; 
            }
            i++;
        }
    }
    return final;
}

void rechercheMorceauNumero(Biblio *B, int num){
    /* Vérification que la bibliothèque existe */
    if ( B == NULL){
        printf("Erreur la biblioteque n'est pas alloue\n");
        return;
    }
    /* Vérification que la bibliothèque possède au moins un morceau */
    if ( B->T == NULL){
        printf("La biblioteque est vide\n");
        return;
    }
    int i = 0; // Compte le nombre de morceaux parcourus
    int nE = B->nE;
    CellMorceau *tab = B->T;
    for (int k=0; i<nE; k++){ // On parcout le tableau et on s'arrête lorsqu'on a parcourut tous les morceaux
        if ( &tab[k] != NULL ){ // Vérifie que la case possède un morceau
            if (num == tab[k].num){ // Vérifie si le morceau correspond à celui cherché
                printf("\nLe num %d correspond au morceaux suivant :\n" , num);
                printf("%d\t%s\t%s\n", tab[k].num, tab[k].titre, tab[k].artiste);
                return;
            }
            i++;
        }
    }
    printf("Le morceau %d n'est pas dans cette biblioteque\n",num);
}

void rechercheMorceauArtiste(Biblio *B , char *artiste){
    /* Vérification que la bibliothèque existe */
    if ( B == NULL){
        printf("Erreur la biblioteque n'est pas alloue\n");
        return;
    }
    /* Vérification que la bibliothèque possède au moins un morceau */
    if ( B->T == NULL){
        printf("La biblioteque est vide\n");
        return;
    }
    int i = 0; // Compte le nombre de morceaux parcourus
    int bool = 0;
    int nE = B->nE;
    CellMorceau *tab = B->T;
    for (int k = 0; i < nE; k++){ // On parcout le tableau et on s'arrête lorsqu'on a parcourut tous les morceaux
        if ( &tab[k] != NULL ){ // Vérifie que la case possède un morceau
            if ( !strcmp(artiste, tab[k].artiste) ){ // Vérifie si le morceau correspond à celui cherché
                if (bool == 0){
                    printf("\nLes morceaux de %s sont les suivants :\n" , artiste);
                    bool = 1;
                }
                printf("%d\t%s\t%s\n", tab[k].num, tab[k].titre, tab[k].artiste);
            }
            i++;
        }
    }
    printf("\n");
    if (!bool)
        printf("Il n'y a pas de morceaux de %s dans cette biblioteque\n",artiste);
}

void rechercheMorceauTitre(Biblio *B , char *titre){
    /* Vérification que la bibliothèque existe */
    if ( B == NULL){
        printf("Erreur la biblioteque n'est pas alloue\n");
        return;
    }
    /* Vérification que la bibliothèque possède au moins un morceau */
    if ( B->T == NULL){
        printf("La biblioteque est vide\n");
        return;
    }
    int i = 0; // Compte le nombre de morceaux parcourus
    int nE= B->nE;
    CellMorceau *tab = B->T;
    for (int k=0; i<nE; k++){ // On parcout le tableau et on s'arrête lorsqu'on a parcourut tous les morceaux
        if ( &tab[k] != NULL ){ // Vérifie que la case possède un morceau
            if (!strcmp(titre , tab[k].titre)){ // Vérifie si le morceau correspond à celui cherché
                printf("\nLe titre %s correspond au morceau suivant :\n" , titre);
                printf("%d\t%s\t%s\n", tab[k].num, tab[k].titre, tab[k].artiste);
                return;
            }
            i++;
        }
    }
    printf("Il n'y a pas de morceaux %s dans cette biblioteque\n",titre);
}
