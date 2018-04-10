/**
 * \file io_graphique.c
 * \brief Fonctions d'affichage de la grille 
 *  affichage graphique avec la librairie cairo
 *  dans une fenetre X11
 */

#include "../inc/io_graphique.h"
#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>

#define SIZEX 900
#define SIZEY 500

void clean_surface(cairo_surface_t *surface)
{
    cairo_t *cr;
    cairo_text_extents_t te;

    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_rectangle(cr, 0.0, 0.0, SIZEX-1, SIZEY-1);
    cairo_fill(cr);
}

void affiche_grille_gr(const grille *g, cairo_surface_t *surface, unsigned int temps_evolution)
{
    printf("Evolution : %d\n", temps_evolution);
    printf("\n\e[%dA", 2);

    cairo_t *cr;
    cairo_text_extents_t te;

    double h = 80;
    double hauteur_case = (SIZEY - 120.0) / g->nbl;
    double l = 30;
    double largeur_case = (SIZEX - 60.0) / g->nbc;

    cr = cairo_create(surface);

    for (int i = 0; i < g->nbl; i++)
    {
        for (int j = 0; j < g->nbc; j++)
        {
            cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
            cairo_rectangle(cr, l, h, largeur_case, hauteur_case);
            cairo_set_line_width(cr, 1);
            cairo_stroke(cr);

            if (est_vivante(i, j, *g))
            {
                switch (g->cellules[i][j])
                {
                    case 1: {
                        cairo_set_source_rgb(cr, 0.2, 0.2, 0.2);
                        break;
                    }
                    case 2: {
                        cairo_set_source_rgb(cr, 0.3, 0.3, 0.3);
                        break;
                    }
                    case 3: {
                        cairo_set_source_rgb(cr, 0.4, 0.4, 0.4);
                        break;
                    }
                    case 4: {
                        cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
                        break;
                    }
                    case 5: {
                        cairo_set_source_rgb(cr, 0.6, 0.6, 0.6);
                        break;
                    }
                    case 6: {
                        cairo_set_source_rgb(cr, 0.7, 0.7, 0.7);
                        break;
                    }
                    case 7: {
                        cairo_set_source_rgb(cr, 0.75, 0.75, 0.75);
                        break;
                    }
                    case 8: {
                        cairo_set_source_rgb(cr, 0.8, 0.8, 0.8);
                        break;
                    }
                }
            }
            else
            {
                if (!est_viable(i, j, *g))
                    cairo_set_source_rgb(cr, 0.9, 0.0, 0.2);
                else
                    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
            }

            cairo_rectangle(cr, l + 2, h + 2, largeur_case - 4, hauteur_case - 4);
            cairo_fill(cr);

            l += largeur_case;
        }

        l = 30;
        h += hauteur_case;
    }

    cairo_set_source_rgb(cr, 0.2, 0.2, 0.2);
    cairo_select_font_face(cr, "Courier",
                           CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 50);
    cairo_text_extents(cr, "JEU DE LA VIE", &te);
    cairo_move_to(cr, 10, 50);
    cairo_show_text(cr, "JEU DE LA VIE");

    cairo_set_font_size(cr, 20);
    cairo_text_extents(cr, "Bequet Guillaume", &te);
    cairo_move_to(cr, SIZEX - 200, SIZEY - 15);
    cairo_show_text(cr, "Bequet Guillaume");

    return;
}

void efface_grille_gr(cairo_surface_t *surface)
{
    cairo_surface_destroy(surface);
}

bool grilles_egales(grille *g, grille *gc)
{
    bool res = true;

    if (g->nbl != gc->nbl || g->nbc != gc->nbc)
        res = false;

    for (int i = 0; i < g->nbl && res; i++)
    {
        for (int j = 0; j < g->nbc && res; j++)
        {
            if (g -> cellules[i][j] != gc->cellules[i][j])
                res = false;
        }
    }

    return res;
}

void debut_jeu_gr(grille *g, grille *gc)
{
    Display *dpy;
    Window rootwin;
    Window win;
    XEvent e;
    int scr;

    bool vieillissement = false;
    int (*compte_voisins)(int, int, int, grille) = compte_voisins_vivants_c;
    int distance = 1;
    unsigned int temps_evolution = 0;

    if (!(dpy = XOpenDisplay(NULL)))
    {
        fprintf(stderr, "ERROR: Could not open display\n");
        exit(1);
    }

    scr = DefaultScreen(dpy);
    rootwin = RootWindow(dpy, scr);

    win = XCreateSimpleWindow(dpy, rootwin, 1, 1, SIZEX, SIZEY, 0,
                              WhitePixel(dpy, scr), WhitePixel(dpy, scr));

    XStoreName(dpy, win, "Jeu de la vie");
    XSelectInput(dpy, win, ExposureMask | ButtonPressMask | KeyPressMask);
    XMapWindow(dpy, win);

    cairo_surface_t *cs;
    cs = cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);

    while (1)
    {
        XNextEvent(dpy, &e);

        if (e.type == KeyPress)
        {
            switch (e.xkey.keycode)
            {
                case 10:
                { // 'd'
                    printf("\r\e[0KVeuillez entrer un nouvelle distance de voisinage : \n");
                    printf("\n\e[%dA", 1);
                    scanf("%d", &distance);
                    printf("\n\e[%dA", 1);
                    printf("\r\e[0KÀ partir de ce moment un voisinage de distance %d sera utilisé\n", distance);
                    printf("\n\e[%dA", 1);
                    break;
                }
                case 16:
                { // 'c'
                    if (compte_voisins == compte_voisins_vivants_c)
                        compte_voisins = compte_voisins_vivants_nc;
                    else
                        compte_voisins = compte_voisins_vivants_c;
                    break;
                }
                case 17:
                { // 'v'
                    vieillissement = !vieillissement;
                    break;
                }
                case 44:
                { // '\n'
                    efface_grille_gr(cs);
                    evolue(g, gc, distance, compte_voisins, vieillissement);
                    break;
                }
                case 53:
                { // 'n'
                    char grille[100];
                    printf("\r\e[0KNouvelle grille a charger : \n");
                    scanf("%s", grille);

                    libere_grille(g);
                    libere_grille(gc);

                    init_grille_from_file(grille, g);
                    alloue_grille(g->nbl, g->nbc, gc);
                    // cairo_surface_destroy(cs);
                    clean_surface(cs);

                    temps_evolution = 0;
                    affiche_grille_gr(g, cs, temps_evolution);
                    break;
                }
            }
        }
        else if(e.type == ButtonPress)
        {
            if (e.xbutton.button == 1)
            { // clique
                efface_grille_gr(cs);
                evolue(g, gc, distance, compte_voisins, vieillissement);
            }
            else if(e.xbutton.button == 3)
            { // clique droit
                efface_grille_gr(cs);
                break;
            }
        }
        affiche_grille_gr(g, cs, temps_evolution);
        temps_evolution++;
    }
    return;
}