.PHONY : all clean archive doc

CC=gcc
CFLAGS=-W -Wall
INC=inc/
SRC=src/
OBJ=obj/
BIN=bin/

# executable
all : main.o jeu.o io.o grille.o
	$(CC) -o all $(SRC)main.c $(SRC)jeu.c $(SRC)io.c $(SRC)grille.c -g
	mv $@ $(BIN)

main.o : $(SRC)main.c $(INC)grille.h $(INC)io.h $(INC)jeu.h 
	$(CC) -c $(SRC)main.c $(CFLAGS)
	mv $@ $(OBJ)

jeu.o : $(SRC)jeu.c $(INC)jeu.h
	$(CC) -c $(SRC)jeu.c $(CFLAGS)
	mv $@ $(OBJ)

io.o : $(SRC)io.c $(INC)io.h
	$(CC) -c $(SRC)io.c $(CFLAGS)
	mv $@ $(OBJ)

grille.o : $(SRC)grille.c $(INC)grille.h
	$(CC) -c $(SRC)grille.c $(CFLAGS)
	mv $@ $(OBJ)

# supprime .o et all
clean :
	rm -rf $(OBJ)*.o $(BIN)all

# Documentation
doc:
	doxygen Doxyfile

# archive
archive :
	tar -cvf bequet_guillaume_jdv.tar $(SRC)*.c $(INC)*.h makefile .gitignore Doxyfile
	gzip bequet_guillaume_jdv.tar