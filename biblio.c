#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "biblio.h"

Biblio *charge_n_entrees(const char *nom_fichier, int n ){
    Biblio *B = nouvelle_biblio();
    FILE *f = fopen(nom_fichier, "r");
    int entier;
    int taille;
    char *titre = NULL;
    char *artiste = NULL;
    int i = n;
    while (i != 0 &&  end_of_file(f)!=1) {
        parse_int( f , &entier);
        parse_char( f , '\t' );
        parse_string( f , &titre, &taille, '\t');
        parse_char( f , '\t');
        parse_string( f , &artiste, &taille, '\n');
        parse_char( f , '\n');
        insere( B , entier , titre , artiste);
        i--;
    }
    free(titre);
    free(artiste);
    fclose(f);
    return B;
}

void uniques_graphe(int borne_inf , int pas, int borne_sup,char *fichier){
    FILE *F= fopen(fichier,"w");
    Biblio *B, *Bunique;
    clock_t temps_initial ; /* Temps initial en micro-secondes */
    clock_t temps_final ;
    for (int i = borne_inf; i<=borne_sup; i= i +pas){
        printf("%d\n",i);
        B = charge_n_entrees("BiblioMusicale.txt", i);
        temps_initial = clock () ; 
        Bunique= uniques(B);
        temps_final = clock () ;
        libere_biblio(Bunique);
        libere_biblio(B);
        fprintf(F, "%d %f\n",i, (( double ) ( temps_final - temps_initial ) ) / CLOCKS_PER_SEC);
    }
    fclose(F);
}