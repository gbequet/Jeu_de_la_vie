/**
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
