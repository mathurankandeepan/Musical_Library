#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "biblio.h"

void menu (){
    printf ("\nMenu :\n");
    printf ("0-Sortie\n");
    printf ("1-Affichage\n");
    printf ("2-Recherche morceau uniques\n");
    printf ("3-Recherche morceau par numero\n");
    printf ("4-Recherche morceau par titre\n");
    printf ("5-Recherche morceau par artiste\n");
    printf ("6-Affiche le temps de calcul de 7 morceaux pour la recherche par un numero\n");
    printf ("7-Affiche le temps de calcul de 7 morceaux pour la recherche par titre\n");
    printf ("8-Affiche le temps de calcul de 7 morceaux pour la recherche par artiste\n");
    printf ("9-Ecris dans un fichier.txt le temps des fonctions uniques en fonction du nombre de morceaux\n");
    printf ("10-Jeu de test complet\n");

    printf ("Votre choix  : ");
}

void JeudeTest(){ 
    printf("\n\n################################## JEU DE TEST ################################\n\n\n");
    Biblio *Buniques; 
    Biblio *biblio;

    printf("\n################################## Nouvelle_Biblio ##################################\n");
    biblio = nouvelle_biblio();
    affiche(biblio);

    printf("\n################################## Insere ##################################\n");
    printf("\nOn insere d'abord un morceau de titre 000 et d'artiste AAA à partir d'une biblio vide\n");
    insere(biblio , 1 , "000" , "AAA");
    affiche(biblio);
    printf("\nOn insere ensuite d'autres morceaux d'artistes differents\n");
    insere(biblio , 2 , "111" , "BBB");
    insere(biblio , 3 , "222" , "CCC");
    insere(biblio , 4 , "333" , "DDD");
    affiche(biblio);
    printf("\nOn insere ensuite d'autres morceaux d'artistes déjà présents\n");
    insere(biblio , 5 , "444" , "AAA");
    insere(biblio , 6 , "555" , "AAA");
    insere(biblio , 7 , "666" , "BBB");
    affiche(biblio);

    printf("\n################################## SupprimeUnMorceau par titre et artiste ##################################\n");
    printf("\nOn supprime le morceau de titre 666 et d'artiste BBB\n");
    biblio= supprimerUnMorceau( biblio, "666" ,"BBB");
    affiche(biblio);
    printf("\nOn supprime le morceau de titre 222 et d'artiste CCC\n");
    biblio= supprimerUnMorceau( biblio, "222" ,"CCC");
    affiche(biblio);
    printf("\nOn essaye de supprimer un morceau de titre 999 et d'artiste ZZZ qui n'est pas dans la biblio\n");
    biblio= supprimerUnMorceau( biblio, "999" ,"ZZZ");
    affiche(biblio);


    printf("\n################################## SupprimeMorceauParNum ##################################\n\n");
    printf("\nOn supprime le morceau de numero 4 \n");
    supprimeMorceauParNum(biblio,4);
    affiche(biblio);
    printf("\nOn supprime le morceau de numero 6 \n");
    supprimeMorceauParNum(biblio,6);
    affiche(biblio);
    printf("\nOn essaye de supprimer un morceau de numero 100 qui n'est pas dans la biblio\n\n");
    supprimeMorceauParNum(biblio,100);
    affiche(biblio);
    

    printf("\n################################## Uniques ##################################\n\n");
    printf("Test de la fonction unique sur une biblio sans doublons :\n");;
    printf("Bibliotèque de départ :\n");
    affiche(biblio);
    printf("Bibliotèque après l'utilisation de la fonction uniques :\n");
    Buniques = uniques(biblio);
    affiche(Buniques);
    libere_biblio(Buniques);
    printf("Création d'une biblioteque avec des doublons :\n");
    insere(biblio , 8 , "444" , "AAA");
    insere(biblio , 9 , "555" , "AAA");
    insere(biblio , 10 , "666" , "BBB");
    insere(biblio , 11 , "666" , "BBB");
    insere(biblio , 12 , "666" , "BBB");
    insere(biblio , 13 , "777" , "CCC");
    insere(biblio , 14 , "777" , "CCC");
    affiche(biblio);
    printf("Bibliotèque après l'utilisation de la fonction uniques :\n");
    Buniques = uniques(biblio);
    affiche(Buniques);
    libere_biblio(Buniques);
    printf("Test de la fonction unique sur une biblio avec que des doublons :\n");
    insere(biblio , 13 , "000" , "AAA");
    insere(biblio , 14 , "555" , "AAA");
    insere(biblio , 11 , "111" , "BBB");
    printf("Bibliotèque de départ :\n");
    affiche(biblio);
    printf("Bibliotèque après l'utilisation de la fonction uniques :\n");
    Buniques = uniques(biblio);
    affiche(Buniques);
    libere_biblio(Buniques);

    printf("\n################################## RechercheMorceauNumero ##################################\n\n");
    insere(biblio , 15 , "777" , "EEE");
    printf("Bibliotèque sur laquelle nous allons effectué nos test :\n");
    affiche(biblio);
    printf("\nRecherche d'un morceau de numero 15\n");
    rechercheMorceauNumero(biblio,15);
    printf("\nRecherche d'un morceau de numero 12\n");
    rechercheMorceauNumero(biblio,12);
    printf("\nRecherche d'un morceau de numero 100 (Il n'est pas dans la biblioteque)\n");
    rechercheMorceauNumero(biblio,100);

    printf("\n################################## RechercheMorceauTitre ##################################\n\n");
    printf("Bibliotèque sur laquelle nous allons effectué nos test (la même que la précedente) :\n");
    affiche(biblio);
    printf("\nRecherche d'un morceau de titre 444\n");
    rechercheMorceauTitre(biblio,"444");
    printf("\nRecherche d'un morceau de titre 777\n");
    rechercheMorceauTitre(biblio,"777");
    printf("\nRecherche d'un morceau de titre 999 (Il n'est pas dans la biblioteque)\n");
    rechercheMorceauTitre(biblio,"999");

    printf("\n################################## RechercheMorceauArtiste ##################################\n\n");
    printf("Bibliotèque sur laquelle nous allons effectué nos test (la même que la précedente) :\n");
    affiche(biblio);
    printf("\nRecherche d'un morceau de l'artiste AAA\n");
    rechercheMorceauArtiste(biblio,"AAA");
    printf("\nRecherche d'un morceau de l'artiste EEE\n");
    rechercheMorceauArtiste(biblio,"EEE");
    printf("\nRecherche d'un morceau de l'artiste ZZZ (Il n'est pas dans la biblioteque)\n");
    rechercheMorceauArtiste(biblio,"ZZZ");


    printf("\n\n################################## JEU DE TEST TERMINEE ################################\n\n\n");

    libere_biblio(biblio);
}

int main ( int argc , const char *argv[]){
    if (argc != 3 ){
        printf ("Erreur format : %s <NomFichierBiblio.txt> <NbLigneALire\n", argv[0]);
        return 1;
    }
    
    const char *nomfic = argv[1];
    int nlignes = atoi(argv[2]);

    printf ("Lecture : \n\n");
    Biblio *biblio = charge_n_entrees(nomfic , nlignes);

    
    if ( biblio!= NULL)
        printf( "La lecture du fichier a ete effectue avec brio\n\n");
    
    int ch, num, lus, i;
    char *recherche=malloc(sizeof(char)*100);
    char *fichier=malloc(sizeof(char)*100);
    clock_t temps_initial ; /* Temps initial en micro-secondes */
    clock_t temps_final ;
    /* Temps final en micro-secondes */
    double temps_cpu ;
    do {
        menu();
        lus = scanf( " %d", &ch);
        if ( lus == 0 ){
            ch = 0;
        }

        switch(ch){
            case 1:
                printf("Affichage \n");
                affiche(biblio);
                break;
            case 2 :
            {
                Biblio *Bunique = uniques (biblio);
                affiche(Bunique);
                libere_biblio(Bunique);
                break;
            }
            case 3 : 
            {
                printf("\nTapez le numero du morceau que vous recherchez : \n");
                scanf( "%d", &num);
                rechercheMorceauNumero(biblio, num);
                break;
            }
            
            case 4 :
            {
                i=0;
                printf("\nTapez le nom du morceaux que vous recherchez : \n");
                while(getc(stdin)!='\n');
                recherche[0]=getc(stdin);
                while(recherche[i]!='\n'){
                  recherche[++i]=getc(stdin);
                }
                recherche[i]='\0';
                rechercheMorceauTitre(biblio, recherche);
                break;
            }
            case 5 :
            {
                i=0;
                printf("\nTapez le nom de l'artiste que vous recherchez : \n");
                while(getc(stdin)!='\n');
                recherche[0]=getc(stdin);
                while(recherche[i]!='\n'){
                  recherche[++i]=getc(stdin);
                }
                recherche[i]='\0';
                rechercheMorceauArtiste(biblio, recherche);
                break;
            }
            case 6 :
            {
                temps_initial = clock () ; 
                rechercheMorceauNumero(biblio, 1);
                rechercheMorceauNumero(biblio, 100);
                rechercheMorceauNumero(biblio, 1000);
                rechercheMorceauNumero(biblio, 10000);
                rechercheMorceauNumero(biblio, 100000);
                rechercheMorceauNumero(biblio, 300599);
                rechercheMorceauNumero(biblio, 1000000);
                temps_final = clock () ;
                temps_cpu = (( double ) ( temps_final - temps_initial ) ) / CLOCKS_PER_SEC ;
                printf ( "\nTemps en seconde pour la recherche par numero : %f \n" , temps_cpu ) ;
                break;
            }
            case 7 : 
            {
                temps_initial = clock () ; 
                rechercheMorceauTitre(biblio,"Bright");
                rechercheMorceauTitre(biblio,"Shake Me, Wake Me (When It's Over)");
                rechercheMorceauTitre(biblio,"How Do I Survive");
                rechercheMorceauTitre(biblio,"Every Time I Close My Eyes");
                rechercheMorceauTitre(biblio,"I Wish That We Were Married");
                rechercheMorceauTitre(biblio,"You Still Touch Me");
                rechercheMorceauTitre(biblio,"MorceauPasDansLaBiblioPourTestPireCas");
                temps_final = clock () ;
                temps_cpu = (( double ) ( temps_final - temps_initial ) ) / CLOCKS_PER_SEC ;
                printf ( "\nTemps en seconde pour la recherche par titre : %f \n" , temps_cpu ) ;
                break;
            }
            case 8 :
            {
                temps_initial = clock () ; 
                rechercheMorceauArtiste(biblio,"Echosmith");
                rechercheMorceauArtiste(biblio,"Four Tops");
                rechercheMorceauArtiste(biblio,"Amy Holland");
                rechercheMorceauArtiste(biblio,"Babyface");
                rechercheMorceauArtiste(biblio,"Sting");
                rechercheMorceauArtiste(biblio,"Ronnie and The Hi-Lites");
                rechercheMorceauArtiste(biblio,"MorceauPasDansLaBiblioPourTestPireCas");
                temps_final = clock () ;
                temps_cpu = (( double ) ( temps_final - temps_initial ) ) / CLOCKS_PER_SEC ;
                printf ( "\nTemps en seconde pour la recherche par artiste : %f \n" , temps_cpu ) ;
                break;
            }
            case 9 :
            {
                i=0;
                printf("\nTapez le nom du fichier sur lequel vous voulez écrire (doit finir en .txt) : \n");
                while(getc(stdin)!='\n');
                fichier[0]=getc(stdin);
                while(fichier[i]!='\n'){
                  fichier[++i]=getc(stdin);
                }
                fichier[i]='\0';
                uniques_graphe(1000,1000, 300000,fichier);

                break;
            }
            case 10:
            {
                JeudeTest();
                break;
            }
            default :
                ch = 0;
                break; 
        }
    } while ( ch != 0);
    free(recherche);
    free(fichier);
    libere_biblio(biblio);  
    printf("\nAu revoir \n");

    return 0;
}


