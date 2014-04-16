// u3-callbacks.h
// Sentinelle d'inclusion
#ifndef _u3_callbacks_h
#define _u3_callbacks_h

// Declarations externes
#include <FL/Fl_Widget.H>

// Declaration des sous-programmes
void TraiterCycleCB() ;
void ZoneDessinSourisCB( Fl_Widget* widget, void* data ) ;
void ZoneDessinClavierCB( Fl_Widget* widget, void* data ) ;
void BoutonQuitterCB( Fl_Widget* w, void* data ) ;
void CaseRebondCB( Fl_Widget* w, void* data ) ;
void BoutonActionCB( Fl_Widget* w, void* data ) ;
void ChampSaisieTxtCB( Fl_Widget* w, void* data ) ;
void ChampSaisieNumCB( Fl_Widget* w, void* data ) ;
void CurseurCB( Fl_Widget* w, void* data ) ;
void CaseCocherCB( Fl_Widget* w, void* data ) ;
void BoutonRadioCB( Fl_Widget* w, void* data ) ;
void MenuOptionsCB( Fl_Widget* w, void* data ) ;

void BoutonMessageCB( Fl_Widget* w, void* data ) ;
void BoutonAvertissementCB( Fl_Widget* w, void* data ) ;
void BoutonQuestionCB( Fl_Widget* w, void* data ) ;
void BoutonChoisirFichierCB( Fl_Widget* w, void* data ) ;
void BoutonSaisirChaineCB( Fl_Widget* w, void* data ) ;
void BoutonSaisirEntierCB( Fl_Widget* w, void* data ) ;


#endif // _u3_callbacks_h
