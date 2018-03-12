/**
 * \file jeu.c
 * \brief Fonctions appelées lors du jeu
 */

#include "jeu.h"


int compte_voisins_vivants_c(int i, int j, int distance, grille g){
  int nb_voisin = 0;

  for (int n = -distance; n <= distance; n++)
  {
    for (int m = -distance; m <= distance; m++)
    {
      if (est_vivante(modulo(i + n, g.nbl), modulo(j + m, g.nbc), g))
        nb_voisin++;
    }
  }

  if (est_vivante(i, j, g))
    nb_voisin--; // car les boucles teste aussi la cellule(i,j)

  return nb_voisin;
}

int compte_voisins_vivants_nc(int i, int j, int distance, grille g){
  int nb_voisin = 0;

  for (int n = -distance; n <= distance; n++)
  {
    for (int m = -distance; m <= distance; m++)
    {
      // il faut que la cellule voisine ne se trouve pas sur un bord de la grille
      if (i + n > 0 && j + m > 0 && i + n < g.nbl && j + m < g.nbc){
        if(est_vivante(i+n, j+m, g))
          nb_voisin++;
      }
    }
  }

  if (est_vivante(i, j, g))
    nb_voisin--; // car les boucles teste aussi la cellule(i,j)

  return nb_voisin;
}

void evolue(grille *g, grille *gc)
{
  copie_grille (g,gc); // copie temporaire de la grille
  for (int i=0; i < g->nbl; i++) 
  {
    for (int j=0; j < g->nbc; ++j) 
    {
      if(est_vivante(i, j, *gc))
      {
        if (compte_voisins_vivants_nc(i, j, 2, *gc) != 2 && compte_voisins_vivants_nc(i, j, 2, *gc) != 3)
          set_morte(i, j, *g); // si la cellule est vivante et qu'elle n'a ni 2 ni 3 voisins vivants alors elle meurt
      }
      else
      {
        if (compte_voisins_vivants_nc(i, j, 2, *gc) == 3)
          set_vivante(i, j, *g); // si la cellule est morte et qu'elle a 3 voisins vivants alors elle vit
      }
    }
  }
}
