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

    int x1;
    int x2;
    int y1;
    int y2;

    // prise des coordonn�es initiales de la souris
    if ( Fl::event() == FL_PUSH ){
        printf("Mouse push = %i x = %i y = %i\n", Fl::event_button(), Fl::event_x(), Fl::event_y());
        Fl::event_x()=x1;
        Fl::event_y()=y1;
    }

    // prise des coordonn�es finale
    if ( Fl::event() == FL_DRAG ){
            if(Fl::event() == FL_MOVE){
                if(Fl::event() == FL_RELEASE){
                    printf("Mouse push = %i x = %i y = %i\n", Fl::event_button(), Fl::event_x(), Fl::event_y());
                    Fl::event_x()=x2;
                    Fl::event_y()=y2;
                }
            }
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
    // retour au param�tre initiales
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

void ChampXMinCB(Fl_Widget* w, void* data){
    re(gDonnees.ig) = (int)gInterface.ChampXMin->value();
    printf("ChampXMinCB : %i\n", gDonnees.moduleMax);
}

void ChampYMinCB(Fl_Widget* w, void* data){
    re(gDonnees.ig) = (int)gInterface.ChampYMin->value();
    printf("ChampYMinCB : %i\n", gDonnees.moduleMax);
}

void ChampLargeurCB(Fl_Widget* w, void* data){
    re(gDonnees.ig) = (int)gInterface.ChampLargeur->value();
    printf("ChampLargeurCB : %i\n", gDonnees.moduleMax);

}

