#include <iostream>
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
    static int ligne=0;     // Indice de la ligne en cours de calcul + affichage (static pour la conserver cross-lignes :) )
    pointeurFct fonction = retourne_fonction();
    unsigned long tabDegrade[gDonnees.rangMax];     // On pourrait faire une struct de vars actuelles
    //if(1){
    if(gTests.calccouleurs){
        printf("Calcul de couleur\n");
        couleurs(gDonnees.color1,gDonnees.color2,gDonnees.color3,gDonnees.rangColor1,gDonnees.rangColor2,gDonnees.rangColor3,tabDegrade);
        gTests.calccouleurs=0;
    }
    if (ligne<H_ZONE){
        if (gTests.calcul)
            convergenceLigne(ligne, fonction);
        if(gTests.dessin)   // Inutile comme test,non ?
            afficheLigne(ligne, tabDegrade);
        ligne+=2;
        Fl::add_timeout(0.00, gestionAffichage, NULL);
    }
    else{   // On arrive à la fin
        if(ligne&1) {   // On a tout affiché
            ligne=0;
            gTests.calcul=0;    // On n'a plus besoin de calculer jusqu'à modif des params de calcul
            gTests.dessin=0;    // On n'a plus besoin d'afficher jusqu'à modif des params de calcul ou d'affichage
            gTests.calccouleurs=1;  // On n'a pas à calculer le dégradé de couleurs jusqu'à modif des params de couleur. À virer…
        }
        else {          // On n'a affiché que les lignes paires
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
