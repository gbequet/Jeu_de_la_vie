#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

// affichage d'une grille
void affiche_grille (const grille *g);

// effacement d'une grille
void efface_grille (const grille *g);

// debute le jeu
void debut_jeu(grille *g, grille *gc);

#endif
