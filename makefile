.PHONY : all clean archive doc

CC=gcc
CFLAGS=-W -Wall -Iinclude -I/opt/X11/include -I/opt/X11/include/cairo -L/opt/X11/lib -lX11 -lcairo
LDFLAGS=-Iinclude -I/opt/X11/include -I/opt/X11/include/cairo -L/opt/X11/lib -lX11 -lcairo
INC=inc/
SRC=src/
OBJ=obj/
BIN=bin/
MODE=GRAPHIQUE
IO=io_graphique
MAIN=main

ifeq ($(MODE), TEXTE)
	IO=io
	MAIN=main_texte
	CFLAGS=-W -Wall
	LDFLAGS=
endif

# executable
all : $(MAIN).o jeu.o $(IO).o grille.o
	$(CC) -o all $(SRC)$(MAIN).c $(SRC)jeu.c $(SRC)$(IO).c $(SRC)grille.c -g $(LDFLAGS)
	mv $@ $(BIN)
		
$(MAIN).o : $(SRC)$(MAIN).c $(INC)grille.h $(INC)$(IO).h $(INC)jeu.h 
	$(CC) -c $(SRC)$(MAIN).c $(CFLAGS)
	mv $@ $(OBJ)

jeu.o : $(SRC)jeu.c $(INC)jeu.h
	$(CC) -c $(SRC)jeu.c $(CFLAGS)
	mv $@ $(OBJ)

$(IO).o : $(SRC)$(IO).c $(INC)$(IO).h
	$(CC) -c $(SRC)$(IO).c $(CFLAGS)
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