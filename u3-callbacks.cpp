#include <iostream>
#include <complex>
#include <stdlib.h>
#include <FL/Fl.H>
#include <FL/fl_ask.H>
#include <FL/Fl_File_Chooser.H>
#include "u1-interface.h"

#include "u3-callbacks.h"
#include "u4-fonctions.h"

void TraiterCycleCB() {
    gInterface.ZoneDessin->redraw();
}

void ZoneDessinSourisCB( Fl_Widget* widget, void* data ) {
    // ATTENTION : X et Y ne sont pas relatifs a la zone mais a la fenetre qui la contient !!!!

    if ( Fl::event() == FL_PUSH ){
        printf("Mouse push = %i x = %i y = %i\n", Fl::event_button(), Fl::event_x(), Fl::event_y());
    }

    if ( Fl::event() == FL_MOVE ){
    }
}



void BoutonQuitterCB(Fl_Widget* w, void* data){
    // Fin du programme
    exit(0);
}

void BoutonEnregistrerCB(Fl_Widget* w, void* data){
    // Enregistre le fichier image et texte

}

void BoutonReset(Fl_Widget* w, void* data){
    // retour au paramètre initiales
    gDonnees.Fractale=FRACT_INIT;
    gDonnees.rangMax=RANGMAX_INIT;
    gDonnees.moduleMax=MODULEMAX_INIT;
    gDonnees.C=C_INIT;
    gDonnees.ig=IG_INIT;
    gDonnees.sd=SD_INIT;
}


void ChampProfondeurCB(Fl_Widget* w, void* data){
     gDonnees.rangMax = (int)gInterface.ChampProfondeur->value();
    printf("ChampProfondeurCB : %s\n", gDonnees.rangMax);
}

void ChampModuleDeSortieCB(Fl_Widget* w, void* data){
    gDonnees.moduleMax = (int)gInterface.ChampModuleDeSortie->value();
    printf("ChampModuleDeSortieCB : %i\n", gDonnees.moduleMax);
}



void MenuFractaleCB(Fl_Widget* w, void* data){
}


