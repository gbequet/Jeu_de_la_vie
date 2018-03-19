/**
 * \file grille.h
 * \brief Declaration et operations sur les grilles
 */

#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdbool.h>

/**
 * \struct grille
 * \brief grille contenant les cellules du jeu
 *        Une grille est contient son nombre de colonnes, de lignes
 *        et un tableau a deux dimensions contenant des celulles qui
 *        sont representées par 0 ou 1
 */
typedef struct {
  int nbl;
  int nbc;
  int **cellules;
} grille;

/**
 * \fn alloue_grille(int l, int c, grille* g)
 * \brief Fonction allouant une grille de l lignes et c colonnes
 *
 * \param l nombre de lignes
 * \param c nombre de colonnes
 * \param g la grille a allouer
 * \return La grille avec toutes les celulles initialisée à mortes.
 */
void alloue_grille(int l, int c, grille* g);

/**
 * \fn libere_grille(grille* g)
 * \brief Fonction permettant de liberer une grille
 *
 * \param g la grille a liberer
 * \return void
 */
void libere_grille(grille* g);

/**
 * \fn init_grille_from_file(char const*const filename, grille* g)
 * \brief alloue et initialise une grille a partir d'un fichier
 *
 * \param filename nom du fichier contenant les conditions de depart du jeu de la vie
 * \param g grille que l'on veut modifier
 * \return void mais la liste a ete modifier par effet de bord
 */
void init_grille_from_file(char const*const filename, grille* g);

/**
 * \fn set_vivante(int i, int j, grille g)
 * \brief Fonction rendant vivante la cellule(i,j)
 *
 * \param i indice de la ligne
 * \param j indice de la colonne
 * \param g grille a laquelle appartient la cellule
 * \return void mais la liste a ete modifier par effet de bord
 */
inline void set_vivante(int i, int j, grille g) {
  g.cellules[i][j] = 1;
}

/**
 * \fn set_morte(int i, int j, grille g)
 * \brief Fonction tuant la cellule(i,j)
 *
 * \param i indice de la ligne
 * \param j indice de la colonne
 * \param g grille a laquelle appartient la cellule
 * \return void mais la liste a ete modifier par effet de bord
 */
inline void set_morte(int i, int j, grille g) {
  g.cellules[i][j] = 0;
}

/**
 * \fn est_vivante(int i, int j, grille g)
 * \brief Teste si la cellule(i,j) est vivante
 *
 * \param i indice de la ligne
 * \param j indice de la colonne
 * \param g grille a laquelle appartient la cellule
 * \return un booleen
 */
inline bool est_vivante(int i, int j, grille g) {
  return g.cellules[i][j] == 1;
}

/**
 * \fn copie_grille(const grille *gs, grille *gd)
 * \brief Copie gs dans gd
 *
 * \param gs grille qu'on souhaite copier
 * \param gd grille ou l'on souhaite coller
 * \return void mais gd a ete modifiée par effet de bord
 */
void copie_grille(const grille *gs, grille *gd);

#endif // __GRILLE_H
