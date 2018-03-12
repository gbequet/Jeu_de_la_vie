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

/*------------------------------------------------------------------------------------------------------------*/

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

/*------------------------------------------------------------------------------------------------------------*/

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

/*------------------------------------------------------------------------------------------------------------*/

void efface_grille(const grille *g) {
  printf("\n\e[%dA", g->nbl * 2 + 5);
}

/*------------------------------------------------------------------------------------------------------------*/

void debut_jeu(grille *g, grille *gc) {
  int c = getchar();
  int nb_pas = 1;
  int distance = 1;
  int (*compte_voisins)(int, int, int, grille) = compte_voisins_vivants_c;
  while (c != 'q')
  { // touche 'q' pour quitter
    switch (c) {
      case '\n' :
        { // touche "entree" pour évoluer
          printf("Temps d'evolution : %d", nb_pas);
          evolue(g, gc, distance, compte_voisins); // la distance par defaut est 1 et le voisinage par default est cyclique
          efface_grille(g);
          affiche_grille(g);
          nb_pas++;
          break;
        }
      case 'c' :
        { // touche 'c' pour activer/desactiver voisinage cyclique
          if(compte_voisins == compte_voisins_vivants_c){
            printf("Voisinage cyclique désactivé\n");
            compte_voisins = compte_voisins_vivants_nc;
          }
          else{
            printf("Voisinage cyclique a nouveau activé\n");
            compte_voisins = compte_voisins_vivants_c;
          }
          break;
        }
      case 'n' :
        { // touche 'n' pour modifier la distance de voisinage
          printf("Veuillez entrer un nouvelle distance de voisinage : \n");
          scanf("%d", &distance);
          printf("À partir de ce moment un voisinage de distance %d sera utilisé\n", distance);
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
