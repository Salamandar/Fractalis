#ifndef _u2_dessin_h
#define _u2_dessin_h
#include <FL/Fl_Widget.H>

void ZoneDessinInitialisation(Fl_Widget* widget, void* data);
void ZoneDessinDessinerCB( Fl_Widget* widget, void* data ) ;
void afficheFractale();
void afficheFractaleLigne();
void afficheLigne(int j);

#endif
