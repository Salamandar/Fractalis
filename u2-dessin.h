#ifndef _u2_dessin_h
#define _u2_dessin_h
#include <FL/Fl_Widget.H>

void ZoneDessinInitialisation(Fl_Widget* widget, void* data);
void gestionAffichage( void* data ) ;
void afficheFractale();
void afficheFractaleLigne();
void afficheLigne(int j);
void affiche(Fl_Widget* widget, void* data);

#endif
