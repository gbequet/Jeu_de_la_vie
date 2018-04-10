/**
 * \file main.c
 * \brief Fonction principale pour la version graphique
 */

#include <stdlib.h>
#include <stdio.h>

#include "../inc/grille.h"
#include "../inc/io_graphique.h"
#include "../inc/jeu.h"

int main (int argc, char ** argv) {
  if (argc != 2) {
    printf("Usage : %s <fichier grille>\n", argv[0]);
    return 1;
  }

  grille g, gc;
  init_grille_from_file(argv[1],&g);
  alloue_grille (g.nbl, g.nbc, &gc);

  debut_jeu_gr(&g, &gc);

  libere_grille(&g);
  libere_grille(&gc);
  return EXIT_SUCCESS;
}
