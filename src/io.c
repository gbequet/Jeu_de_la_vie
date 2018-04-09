/**
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
          printf("\n\e[%dA", 5); // remonter de 5 lignes
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
