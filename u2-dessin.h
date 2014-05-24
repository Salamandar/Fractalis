#ifndef _u2_dessin_h
#define _u2_dessin_h
#include <FL/Fl_Widget.H>

void ZoneDessinInitialisation(Fl_Widget* widget, void* data);
void gestionAffichage(void* data);
void gestionAffichage_iter(void* data);
void afficheFractale();
void afficheFractaleLigne();
//void afficheLigne(int j, unsigned long tableau[]); remplacée pour afficher avec buffer
void afficheLigneRGB(int j, unsigned long tableauCouleurs[][3]);
void tracerCadre (int x1, int y1 , int x2, int y2);
void zoneDegrade(Fl_Widget* widget, void* data);

#endif
