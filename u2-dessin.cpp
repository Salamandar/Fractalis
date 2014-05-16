#include <iostream>
#include <complex>
#include <stdio.h>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
using namespace std;
#include "main.h"
#include "u1-interface.h"
#include "u2-dessin.h"
#include "u3-callbacks.h"
#include "u4-fonctions.h"

void ZoneDessinInitialisation(Fl_Widget* widget, void* data) {
    fl_color(FL_BLACK);
    fl_rectf(X_ZONE, Y_ZONE, L_ZONE, H_ZONE);
    // On initialise la gestion de l'affichage de la fractale seulement quand la fenêtre est correctement créée
    Fl::add_timeout(0, gestionAffichage, NULL );
}

void gestionAffichage(void*) {
    cout<<gDonnees.ig<<endl;
    cout<<gDonnees.pasxy<<endl;
    //cout<<gTests.dessin<<endl;
    static int ligne=0;     // Indice de la ligne en cours de calcul + affichage (static pour la conserver cross-lignes :) )
    pointeurFct fonction = retourne_fonction();
    unsigned long tabDegrade[gDonnees.rangMax];
    if(1==1){
        couleurs(gDonnees.color1,gDonnees.color2,gDonnees.color3,gDonnees.rangColor1,gDonnees.rangColor2,gDonnees.rangColor3,tabDegrade);
        gTests.calccouleurs=0;
    }
    if (ligne<H_ZONE){
       if(gTests.dessin==0){ convergenceLigne(fonction, ligne);}
        afficheLigne(ligne, tabDegrade);
        ligne+=2;
        Fl::add_timeout(0.001, gestionAffichage, NULL);
    }
    else{
        if(ligne&1){
            ligne=0;
            gTests.dessin=0;
            gTests.calccouleurs=1;
          }
        else{
            ligne=1;
            Fl::add_timeout(0.0, gestionAffichage, NULL);
        }
    }
}

void afficheLigne(int j, unsigned long tableauCouleurs[]){
    for (int i = 0; i < L_ZONE; ++i) {
        if (gDonnees.Tab[i][j].n==-1 )
            fl_color(FL_BLACK);
        else
            fl_color(tableauCouleurs[gDonnees.Tab[i][j].n]);
        fl_point(i+X_ZONE,j+Y_ZONE);
    }
}
