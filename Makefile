
GCC_FLAGS = -g -Wall

liste: biblio_liste.o biblio.o parser.o main.o
	gcc $(GCC_FLAGS) biblio_liste.o biblio.o parser.o main.o -o main

arbre: biblio_arbrelex.o biblio.o parser.o main.o
	gcc $(GCC_FLAGS) biblio_arbrelex.o biblio.o parser.o main.o -o main

tab: biblio_tabdyn.o biblio.o parser.o main.o
	gcc $(GCC_FLAGS) biblio_tabdyn.o biblio.o parser.o main.o -o main

hachage: biblio_hachage.o biblio.o parser.o main.o
	gcc $(GCC_FLAGS) biblio_hachage.o biblio.o parser.o main.o -o main -lm

parser.o: parser.c parser.h
	gcc $(GCC_FLAGS) -c parser.c

biblio_liste.o 	: biblio_liste.c  biblio.h
	gcc $(GCC_FLAGS) -c biblio_liste.c

biblio_arbrelex.o: biblio_arbrelex.c biblio.h
	gcc $(GCC_FLAGS) -c biblio_arbrelex.c

biblio_tabdyn.o: biblio_tabdyn.c biblio.h
	gcc $(GCC_FLAGS) -c biblio_tabdyn.c
	
biblio_hachage.o: biblio_hachage.c biblio.h
	gcc $(GCC_FLAGS) -c biblio_hachage.c

biblio.o 	: biblio.c biblio.h  parser.h
	gcc $(GCC_FLAGS) -c biblio.c

main.o 	: main.c biblio.h  parser.h
	gcc $(GCC_FLAGS) -c main.c

clean	:
	rm -f *.o main
