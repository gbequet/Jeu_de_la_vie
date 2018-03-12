/**
 * \file io.c
 * \brief Fonctions d'affichage de la grille et de debut du jeu
 */

#include "io.h"

static void affiche_trait(int c){
  int i;
  for (i=0; i<c; ++i) printf ("|---");
  printf("|\n");
  return;
}

static void affiche_ligne(int ligne, const grille *g) {
  for (int i=0; i < g->nbc; ++i) {
    if (est_vivante(ligne, i, *g))
      printf ("| O ");
    else
      printf ("|   ");
  }
  printf("|\n");
  return;
}

void affiche_grille(const grille *g) {
  printf("\n");
  affiche_trait(g->nbc);
  for (int i=0; i < g->nbl; ++i) {
    affiche_ligne(i, g);
    affiche_trait(g->nbc);
  }
  printf("\n");
  return;
}

void efface_grille(const grille *g) {
  printf("\n\e[%dA", g->nbl * 2 + 5);
}

void debut_jeu(grille *g, grille *gc) {
  int c = getchar();
  int nb_pas = 0;
  while (c != 'q') { // touche 'q' pour quitter
    switch (c) {
      case '\n' :
        { // touche "entree" pour évoluer
          printf("Temps d'evolution : %d", nb_pas);
          evolue(g,gc);
          efface_grille(g);
          affiche_grille(g);
          nb_pas++;
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
