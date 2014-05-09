#include <iostream>
#include <complex>
#include <stdlib.h>
#include <FL/Fl.H>
#include <FL/fl_ask.H>
#include <FL/Fl_File_Chooser.H>
#include "u1-interface.h"
#include "u2-dessin.h"
#include "u3-callbacks.h"
#include "u4-fonctions.h"

void TraiterCycleCB() {
    //afficheFractaleLigne();

    gInterface.ZoneDessin->redraw();
}

void ZoneDessinSourisCB( Fl_Widget* widget, void* data ) {
    // ATTENTION : X et Y ne sont pas relatifs a la zone mais a la fenetre qui la contient !!!!

    int x1;
    int x2;
    int y1;
    int y2;

    // prise des coordonn?s initiales de la souris
    if ( Fl::event() == FL_PUSH ){
        printf("Mouse push = %i x = %i y = %i\n", Fl::event_button(), Fl::event_x(), Fl::event_y());
        x1=Fl::event_x();
        y1=Fl::event_y();
    }

    // prise des coordonn?s finale
    if ( Fl::event() == FL_DRAG ){
        if(Fl::event() == FL_MOVE){
            if(Fl::event() == FL_RELEASE){
                printf("Mouse push = %i x = %i y = %i\n", Fl::event_button(), Fl::event_x(), Fl::event_y());
                x2=Fl::event_x();
                y2=Fl::event_y();
            }
        }
    }
    // calcul du décalage à effectuer
    re(gDonnees.ig)=re(gDonnees.ig)+(x2-x1);
    im(gDonnees.ig)=im(gDonnees.ig)+(y2-y1);

}



void BoutonQuitterCB(Fl_Widget* w, void* data){
    // Fin du programme
    exit(0);
}

void BoutonEnregistrerCB(Fl_Widget* w, void* data){
    // Enregistre le fichier image et texte

}

void BoutonReset(Fl_Widget* w, void* data){
    // retour au param?re initiales
    gDonnees.Fractale=FRACT_INIT;
    gDonnees.rangMax=RANGMAX_INIT;
    gDonnees.moduleMax=MODULEMAX_INIT;
    gDonnees.C=C_INIT;
    gDonnees.ig=IG_INIT;
    gDonnees.pasxy=PASXY;
}


void ChampProfondeurCB(Fl_Widget* w, void* data){
     gDonnees.rangMax = (int)gInterface.ChampProfondeur->value();
    printf("ChampProfondeurCB : %d\n", gDonnees.rangMax);
}

void ChampModuleDeSortieCB(Fl_Widget* w, void* data){
    gDonnees.moduleMax = (int)gInterface.ChampModuleDeSortie->value();
    printf("ChampModuleDeSortieCB : %lf\n", gDonnees.moduleMax);
}



void MenuFractaleCB(Fl_Widget* w, void* data){
}

void ChampXMinCB(Fl_Widget* w, void* data){
    re(gDonnees.ig) = (int)gInterface.ChampXMin->value();
    printf("ChampXMinCB : %lf\n", re(gDonnees.ig));
}

void ChampYMinCB(Fl_Widget* w, void* data){
    im(gDonnees.ig) = (int)gInterface.ChampYMin->value();
    printf("ChampYMinCB : %lf\n", in(gDonnees.ig));
}

void ChampLargeurCB(Fl_Widget* w, void* data){
    gDonnees.pasxy*L_ZONE = (int)gInterface.ChampLargeur->value();
    printf("ChampLargeurCB : %lf\n", gDonnees.pasxy*L_ZONE);

}

