#ifndef _u2_dessin_h
#define _u2_dessin_h
#include <FL/Fl_Widget.H>

void ZoneDessinInitialisation(Fl_Widget* widget, void* data);
void gestionAffichage(void* data);
void gestionAffichage_iter(void* data);
void afficheFractale();
void afficheFractaleLigne();
void afficheLigne(int j, unsigned long tableau[]);
void* calc1(void* tab);
void* calc2(void* tab);

#endif
