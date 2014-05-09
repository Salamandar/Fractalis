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


void cycleAffichage() {
    afficheFractaleLigne();
}


void ZoneDessinSourisCB( Fl_Widget* widget, void* data ) {
    // ATTENTION : X et Y ne sont pas relatifs a la zone mais a la fenetre qui la contient !!!!

    int x1=0;
    int x2=0;
    int y1=0;
    int y2=0;

    // prise des coordonn?s initiales de la souris
    if ( Fl::event() == FL_PUSH ){
        printf("Mouse push = %i x = %i y = %i\n", Fl::event_button(), Fl::event_x(), Fl::event_y());
        x1=Fl::event_x();
        y1=Fl::event_y();
    }

    // prise des coordonn?s finale
    if(Fl::event() == FL_RELEASE){
        printf("Mouse release = %i x = %i y = %i\n", Fl::event_button(), Fl::event_x(), Fl::event_y());
        x2=Fl::event_x();
        y2=Fl::event_y();
    }

    //printf("partie reelle init : %lf" ,real(gDonnees.ig));


    // calcul du décalage à effectuer
    real(gDonnees.ig)=real(gDonnees.ig)+(x2-x1);
    imag(gDonnees.ig)=imag(gDonnees.ig)+(y2-y1);


    //printf("partie reelle finale : %lf\n" ,real(gDonnees.ig));

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
    real(gDonnees.ig) = (int)gInterface.ChampXMin->value();
    printf("ChampXMinCB : %lf\n", real(gDonnees.ig));
}

void ChampYMinCB(Fl_Widget* w, void* data){
    imag(gDonnees.ig) = (int)gInterface.ChampYMin->value();
    printf("ChampYMinCB : %lf\n", imag(gDonnees.ig));
}

void ChampLargeurCB(Fl_Widget* w, void* data){
    gDonnees.pasxy = ((double)gInterface.ChampLargeur->value())/L_ZONE;
    printf("ChampLargeurCB : %lf\n", gDonnees.pasxy*L_ZONE);

}

void CarreChoixCouleurCB(Fl_Widget* w, void* data){

}

