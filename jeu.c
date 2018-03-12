/**
 * \file jeu.c
 * \brief Fonctions appelées lors du jeu
 */

#include "jeu.h"

int compte_voisins_vivants(int i, int j, grille g) {
  int nb_voisin = 0;

  for(int n = -1; n <= 1; n++)
  {
    for(int m = -1; m <= 1; m++)
    {
      if (est_vivante(modulo(i+n, g.nbl), modulo(j+m, g.nbc), g))
        nb_voisin++;
    }
  }

  if(est_vivante(i,j,g))
    nb_voisin--; // car les boucles teste aussi la cellule(i,j)

  return nb_voisin;
}

void evolue(grille *g, grille *gc) {
  copie_grille (g,gc); // copie temporaire de la grille
  for (int i=0; i < g->nbl; i++) 
  {
    for (int j=0; j < g->nbc; ++j) 
    {
      if(est_vivante(i, j, *gc))
      {
        if (compte_voisins_vivants(i, j, *gc) != 2 && compte_voisins_vivants(i, j, *gc) != 3)
          set_morte(i, j, *g); // si la cellule est vivante et qu'elle n'a ni 2 ni 3 voisins vivants alors elle meurt
      }
      else
      {
        if (compte_voisins_vivants(i, j, *gc) == 3)
          set_vivante(i, j, *g); // si la cellule est morte et qu'elle a 3 voisins vivants alors elle vit
      }
    }
  }
}
