/**
 * \file main_texte.c
 * \brief Fonction principale pour la version texte
 */

#include <stdlib.h>
#include <stdio.h>

#define SIZEX 1000
#define SIZEY 500

#include "../inc/grille.h"
#include "../inc/io.h"
#include "../inc/jeu.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage : %s <fichier grille>\n", argv[0]);
        return 1;
    }

    grille g, gc;
    init_grille_from_file(argv[1], &g);
    alloue_grille(g.nbl, g.nbc, &gc);
    affiche_grille(&g, 0);

    debut_jeu(&g, &gc);

    libere_grille(&g);
    libere_grille(&gc);

    return EXIT_SUCCESS;
}
