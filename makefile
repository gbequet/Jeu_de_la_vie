.PHONY : all clean archive

# executable
all : main.o jeu.o io.o grille.o
	gcc -o all main.c jeu.c io.c grille.c -g

main.o : main.c grille.h io.h jeu.h 
	gcc -c main.c

jeu.o : jeu.c jeu.h
	gcc -c jeu.c

io.o : io.c io.h
	gcc -c io.c

grille.o : grille.c grille.h
	gcc -c grille.c

# supprime .o et all
clean :
	rm -rf *.o all

# archive
archive :
	tar -cvf jeu_de_la_vie.tar ../LaVie/
	gzip jeu_de_la_vie.tar