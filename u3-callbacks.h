#ifndef _u3_callbacks_h
#define _u3_callbacks_h
#include <FL/Fl_Widget.H>
int cycleAffichage();

void ZoneDessinSourisCB (Fl_Widget* widget, void* data ) ;
void ChampModuleDeSortieCB(Fl_Widget* w, void* data);
void ChampProfondeurCB  (Fl_Widget* w, void* data);
void MenuFractaleCB     (Fl_Widget* w, void* data);
void BoutonQuitterCB    (Fl_Widget* w, void* data);
void BoutonEnregistrerCB(Fl_Widget* w, void* data);
void BoutonResetCB      (Fl_Widget* w, void* data);
void ChampXMinCB        (Fl_Widget* w, void* data);
void ChampYMinCB        (Fl_Widget* w, void* data);
void ChampLargeurCB     (Fl_Widget* w, void* data);
void CarreChoixCouleurCB(Fl_Widget* w, void* data);
void Slider1CB          (Fl_Widget* w, void* data);
void Slider2CB          (Fl_Widget* w, void* data);
void Slider3CB          (Fl_Widget* w, void* data);

#endif
