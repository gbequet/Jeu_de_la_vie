/**
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
void affiche_grille(const grille *g);

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
