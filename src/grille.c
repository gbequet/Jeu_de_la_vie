src/io.c                                                                                            000644  000765  000024  00000005732 13254724054 013564  0                                                                                                    ustar 00guillaume                       staff                           000000  000000                                                                                                                                                                         /**
 * \file io.c
 * \brief Fonctions d'affichage de la grille et de debut du jeu
 */

#include "../inc/io.h"

static void affiche_trait(int c){
  int i;
  for (i=0; i<c; ++i) printf ("|---");
  printf("|\n");
  return;
}

static void affiche_ligne(int ligne, const grille *g) {
  for (int i=0; i < g->nbc; ++i) {
    if(est_viable(ligne, i, *g))
    {
      if (est_vivante(ligne, i, *g))
        printf ("| %d ", g->cellules[ligne][i]);
      else
        printf ("|   ");
    }
    else
      printf ("| X ");
  }
  printf("|\n");
  return;
}

void affiche_grille(const grille *g, unsigned int evol) {
  printf("\n");
  printf("Evolution : %u\n", evol);

  affiche_trait(g->nbc);
  for (int i=0; i < g->nbl; ++i) {
    affiche_ligne(i, g);
    affiche_trait(g->nbc);
  }
  printf("\n");
  return;
}

void efface_grille(const grille *g) {
  printf("\n\e[%dA", g->nbl * 2 + 6);
}

void debut_jeu(grille *g, grille *gc) {
  int c = getchar();
  int nb_pas = 1;
  int distance = 1;
  int (*compte_voisins)(int, int, int, grille) = compte_voisins_vivants_c;
  bool vieillissement = false;
  while (c != 'q')
  { // touche 'q' pour quitter
    switch (c) {
      case '\n' :
        { // touche "entree" pour évoluer
          evolue(g, gc, distance, compte_voisins, vieillissement);
          efface_grille(gc);
          affiche_grille(g, nb_pas);
          nb_pas++;
          break;
        }
      case 'c' :
        { // touche 'c' pour activer/desactiver le voisinage cyclique
          getchar(); // pas de bug

          if(compte_voisins == compte_voisins_vivants_c){
            printf("\r\e[0KVoisinage cyclique désactivé\n");
            compte_voisins = compte_voisins_vivants_nc;
          }
          else{
            printf("\r\e[0KVoisinage cyclique a nouveau activé\n");
            compte_voisins = compte_voisins_vivants_c;
          }
          printf("\n\e[%dA", 3); // remonter de 3 lignes
          // printf("\r"); // repartir a la marge
          break;
        }
      case 'v' :
      { // touche 'v' pour activer/desactiver le vieillissement
        getchar();

        if (vieillissement)
        {
          printf("\r\e[0KVieillissement désactivé\n");
          vieillissement = false;
        }
        else
        {
          printf("\r\e[0KVieillissement activé\n");
          vieillissement = true;
        }
        printf("\n\e[%dA", 3); // remonter de 3 lignes
        // printf("\r"); // repartir a la marge
        break;
        }
      case 'n' :
        { // touche 'n' pour modifier la distance de voisinage
          printf("\r\e[0KVeuillez entrer un nouvelle distance de voisinage : \n");
          scanf("%d", &distance);
          printf("\r\e[0KÀ partir de ce moment un voisinage de distance %d sera utilisé\n", distance);

          getchar();
          printf("\n\e[%dA", 5); // remonter de 3 lignes
          break;
        }
      default :
        { // touche non traitée
          printf("\n\e[1A");
          break;
        }
    }
    c = getchar();
  }
  return;
}
                                      src/jeu.c                                                                                           000644  000765  000024  00000003677 13254724047 013750  0                                                                                                    ustar 00guillaume                       staff                           000000  000000                                                                                                                                                                         /**
 * \file jeu.c
 * \brief Fonctions appelées lors du jeu
 */

#include "../inc/jeu.h"
#include <stdlib.h>

int valeur_cyclique(int val, int cycle) { // Cycle > 0
div_t res = div(val, cycle);
if (res.rem < 0)
  return res.rem + cycle;
else
  return res.rem;
}

int compte_voisins_vivants_c(int i, int j, int distance, grille g){
  int nb_voisin = 0;

  for (int n = -distance; n <= distance; n++)
  {
    int n_cycl = valeur_cyclique(i+n, g.nbl);
    for (int m = -distance; m <= distance; m++)
    {
      int m_cycl = valeur_cyclique(j+m, g.nbc);
      if (est_vivante(n_cycl, m_cycl, g))
        nb_voisin++;
    }
  }

  if (est_vivante(i, j, g))
    nb_voisin--; // car les boucles teste aussi la cellule(i,j)

  return nb_voisin;
}

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

int compte_voisins_vivants_nc(int i, int j, int distance, grille g){
  int nb_voisin = 0;

  for (int n = max(0, i-distance); n <= min(g.nbl-1, i+distance); n++) 
  {
    for (int m = max(0, j-distance); m <= min(g.nbc-1, j+distance); m++)
    {
      if ((n != i || m != j) && est_vivante(n, m, g))
          nb_voisin++;
    }
  }

  return nb_voisin;
}

void evolue(grille *g, grille *gc, int dist, int (*compte_v)(int, int, int, grille), bool vieil)
{
  copie_grille(g, gc); // copie temporaire de la grille

  for (int i = 0; i < gc->nbl; i++)
  {
    for (int j = 0; j < gc->nbc; ++j)
    {
      if(est_viable(i, j, *gc))
      {
        if (est_vivante(i, j, *gc))
        {
          if (compte_v(i, j, dist, *gc) != 2 && compte_v(i, j, dist, *gc) != 3)
            set_morte(i, j, *g);
          else
          { 
            if(vieil){
              if(gc->cellules[i][j] == 8)
                set_morte(i, j, *g); 
              else
                set_vivante(i, j, *g); 
            }
          }
        }
        else
        {
          if (compte_v(i, j, dist, *gc) == 3)
            set_vivante(i, j, *g);
        }
      }
    }
  }
}
                                                                 src/main.c                                                                                          000644  000765  000024  00000000771 13254724041 014073  0                                                                                                    ustar 00guillaume                       staff                           000000  000000                                                                                                                                                                         /**
 * \file main.c
 * \brief Fonction principale
 */

#include <stdlib.h>
#include <stdio.h>

#include "../inc/grille.h"
#include "../inc/io.h"
#include "../inc/jeu.h"

int main (int argc, char ** argv) {
  if (argc != 2) {
    printf("Usage : %s <fichier grille>\n", argv[0]);
    return 1;
  }

  grille g, gc;
  init_grille_from_file(argv[1],&g);
  alloue_grille (g.nbl, g.nbc, &gc);
  affiche_grille(&g, 0);

  debut_jeu(&g, &gc);

  libere_grille(&g);
  libere_grille(&gc);
  return EXIT_SUCCESS;
}
       inc/grille.h                                                                                        000644  000765  000024  00000005454 13254140702 014413  0                                                                                                    ustar 00guillaume                       staff                           000000  000000                                                                                                                                                                         /**
 * \file grille.h
 * \brief Declaration et operations sur les grilles
 */

#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdbool.h>

/**
 * \struct grille
 * \brief grille contenant les cellules du jeu
 *        Une grille est contient son nombre de colonnes, de lignes
 *        et un tableau a deux dimensions contenant des celulles qui
 *        sont representées par 0 ou 1
 */
typedef struct {
  int nbl;
  int nbc;
  int **cellules;
} grille;

/**
 * \fn alloue_grille(int l, int c, grille* g)
 * \brief Fonction allouant une grille de l lignes et c colonnes
 *
 * \param l nombre de lignes
 * \param c nombre de colonnes
 * \param g la grille a allouer
 * \return La grille avec toutes les celulles initialisée à mortes.
 */
void alloue_grille(int l, int c, grille* g);

/**
 * \fn libere_grille(grille* g)
 * \brief Fonction permettant de liberer une grille
 *
 * \param g la grille a liberer
 * \return void
 */
void libere_grille(grille* g);

/**
 * \fn init_grille_from_file(char const*const filename, grille* g)
 * \brief alloue et initialise une grille a partir d'un fichier
 *
 * \param filename nom du fichier contenant les conditions de depart du jeu de la vie
 * \param g grille que l'on veut modifier
 * \return void mais la liste a ete modifier par effet de bord
 */
void init_grille_from_file(char const*const filename, grille* g);

/**
 * \fn set_vivante(int i, int j, grille g)
 * \brief Fonction rendant vivante la cellule(i,j)
 *
 * \param i indice de la ligne
 * \param j indice de la colonne
 * \param g grille a laquelle appartient la cellule
 * \return void mais la liste a ete modifier par effet de bord
 */
inline void set_vivante(int i, int j, grille g) {
  g.cellules[i][j]++;
}

/**
 * \fn set_morte(int i, int j, grille g)
 * \brief Fonction tuant la cellule(i,j)
 *
 * \param i indice de la ligne
 * \param j indice de la colonne
 * \param g grille a laquelle appartient la cellule
 * \return void mais la liste a ete modifier par effet de bord
 */
inline void set_morte(int i, int j, grille g) {
  g.cellules[i][j] = 0;
}

inline void set_non_viable(int i, int j, grille g){
  g.cellules[i][j] = -1;
}

/**
 * \fn est_vivante(int i, int j, grille g)
 * \brief Teste si la cellule(i,j) est vivante
 *
 * \param i indice de la ligne
 * \param j indice de la colonne
 * \param g grille a laquelle appartient la cellule
 * \return un booleen
 */
inline bool est_vivante(int i, int j, grille g){
  return g.cellules[i][j] >= 1;
}

inline bool est_viable(int i, int j, grille g) {
  return g.cellules[i][j] != -1;
}

/**
 * \fn copie_grille(const grille *gs, grille *gd)
 * \brief Copie gs dans gd
 *
 * \param gs grille qu'on souhaite copier
 * \param gd grille ou l'on souhaite coller
 * \return void mais gd a ete modifiée par effet de bord
 */
void copie_grille(const grille *gs, grille *gd);

#endif // __GRILLE_H
                                                                                                                                                                                                                    inc/io.h                                                                                            000644  000765  000024  00000001532 13253665247 013554  0                                                                                                    ustar 00guillaume                       staff                           000000  000000                                                                                                                                                                         /**
 * \file io.h
 * \brief Declaration des fonctions d'affichage d'une grille
 */

#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

/**
 * \fn affiche_grille(const grille *g)
 * \brief Affiche une grille
 *
 * \param g grille a afficher
 * \return void mais la grille a été affichée
 */
void affiche_grille(const grille *g, unsigned int evol);

/**
 * \fn efface_grille (const grille *g)
 * \brief Efface une grille
 *
 * \param g grille a effacer
 * \return void mais la grille a été affacée
 */
void efface_grille (const grille *g);

/**
 * \fn debut_jeu(grille *g, grille *gc)
 * \brief Debute le jeu avec g comme grille de depart a t0
 *
 * \param g grille au moment t
 * \param gc grille qui va servir a garder g en memoire
 * \return void le jeu commence
 */
void debut_jeu(grille *g, grille *gc);

#endif
                                                                                                                                                                      inc/jeu.h                                                                                           000644  000765  000024  00000003240 13254140702 013707  0                                                                                                    ustar 00guillaume                       staff                           000000  000000                                                                                                                                                                         /**
 * \file jeu.h
 * \brief Declaration des fonctions utiliées durant le jeu
 */

#ifndef __JEU_H
#define __JEU_H

#include "grille.h"

/**
 * \fn modulo(int i, int m)
 * \brief Renvoie le modulo modifié pour traiter le calcul 
 *        des voisins avec bords cycliques
 * 
 * \param i entier
 * \param m entier
 * \return (i+m)%m
 */
static inline int modulo(int i, int m){
    return (i+m)%m;
}

/**
 * \fn compte_voisins_vivants (int i, int j, grille *g)
 * \brief Compte le nombre de voisins d'une cellule(i,j)
 *        avec bords cycliques
 * 
 * \param i index de la ligne
 * \param j index de la colonne
 * \param distance distance de voisinage des cellules
 * \param g grille
 * \return le nombre de voisins de la cellule(i,j)
 */
int compte_voisins_vivants_c(int i, int j, int distance, grille g);

/**
 * \fn compte_voisins_vivants (int i, int j, grille *g)
 * \brief Compte le nombre de voisins d'une cellule(i,j)
 *        sans les bords cycliques
 * 
 * \param i index de la ligne
 * \param j index de la colonne
 * \param distance distance de voisinage des cellules
 * \param g grille
 * \return le nombre de voisins de la cellule(i,j)
 */
int compte_voisins_vivants_nc(int i, int j, int distance, grille g);

/**
 * \fn evolue (grille *g, grille *gc)
 * \brief Fait evoluer la grille g d'un pas de temps
 * 
 * \param g grille qui a t
 * \param gc grille qui gardera les valeurs initiales de g
 * \param dist distance de voisinage souhaité
 * \param compte_v pointeur de fonction qui est gere le calcul des voisins vivants (cyclique ou non) de g
 * \return g a t+1
 */
void evolue(grille *g, grille *gc, int dist, int (*compte_v)(int, int, int, grille), bool vieil);

#endif
                                                                                                                                                                                                                                                                                                                                                                makefile                                                                                            000644  000765  000024  00000001444 13255174514 013717  0                                                                                                    ustar 00guillaume                       staff                           000000  000000                                                                                                                                                                         .PHONY : all clean archive doc

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
	doxygen $(INC)Doxyfile

# archive
archive :
	tar -cvf $(SRC)*.c $(INC)*.h makefile .gitignore bequet_guillaume_jdv.tar
	gzip bequet_guillaume_jdv.tar                                                                                                                                                                                                                            .gitignore                                                                                          000644  000765  000024  00000000050 13254140702 014166  0                                                                                                    ustar 00guillaume                       staff                           000000  000000                                                                                                                                                                         *.o
all
all.dSYM/
.DS_Store
html/
latex/                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        