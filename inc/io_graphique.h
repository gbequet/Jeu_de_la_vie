/**
 * \file io_graphique.h
 * \brief Declaration des fonctions d'affichage graffique d'une grille
 */

#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include "grille.h"
#include "jeu.h"

/**
 * \fn affiche_grille_gr(const grille *g, cairo_surface_t *surface)
 * \brief Affiche dans une fenetre X11 une grille
 *
 * \param g grille a afficher
 * \param surface surface cairo sur laquelle sera affichée la grille
 * \return void mais la grille a été affichée dans une fenetre X11
 */
void affiche_grille_gr(const grille *g, cairo_surface_t *surface, unsigned int temps_evolution);

/**
 * \fn efface_grille_gr(cairo_surface_t *surface)
 * \brief Efface une surface cairo
 *
 * \param surface surface a effacer
 * \return void
 */
void efface_grille_gr(cairo_surface_t *surface);

/**
 * \fn debut_jeu_gr(grille *g, grille *gc)
 * \brief Debute le jeu avec g comme grille de depart a t0
 *
 * \param g grille au moment t
 * \param gc grille qui va servir a garder g en memoire
 * \return void le jeu commence et est affiché dans une fenetre X11
 */
void debut_jeu_gr(grille *g, grille *gc);

void clean_surface(cairo_surface_t *surface);

/**
 * \fn grilles_egales(grille *g, grille *gc)
 * \brief Compare si deux grilles sont identiques
 *
 * \param g 
 * \param gc 
 * \return Un booleen representant g == gc
 */
    bool grilles_egales(grille *g, grille *gc);

#endif
