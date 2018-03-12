/**
 * \file jeu.h
 * \brief Declaration des fonctions utiliées durant le jeu
 */

#ifndef __JEU_H
#define __JEU_H

#include "grille.h"

/**
 * \fn modulo(int i, int m)
 * \brief Renvoie le modulo modifié pour traiter le calcul 
 *        des voisins avec bords cycliques
 * 
 * \param i entier
 * \param m entier
 * \return (i+m)%m
 */
static inline int modulo(int i, int m){
    return (i+m)%m;
}

/**
 * \fn compte_voisins_vivants (int i, int j, grille *g)
 * \brief Compte le nombre de voisins d'une cellule(i,j)
 *        avec bords cycliques
 * 
 * \param i index de la ligne
 * \param j index de la colonne
 * \param g grille
 * \return le nombre de voisins de la cellule(i,j)
 */
int compte_voisins_vivants_c(int i, int j, grille g);

/**
 * \fn compte_voisins_vivants (int i, int j, grille *g)
 * \brief Compte le nombre de voisins d'une cellule(i,j)
 *        sans les bords cycliques
 * 
 * \param i index de la ligne
 * \param j index de la colonne
 * \param g grille
 * \return le nombre de voisins de la cellule(i,j)
 */
int compte_voisins_vivants_nc(int i, int j, grille g);

/**
 * \fn evolue (grille *g, grille *gc)
 * \brief Fait evoluer la grille g d'un pas de temps
 * 
 * \param g grille qui a t
 * \param gc grille qui gardera les valeurs initiales de g
 * \return g a t+1
 */
    void evolue(grille *g, grille *gc);

#endif
