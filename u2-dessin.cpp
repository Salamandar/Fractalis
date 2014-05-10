#include <iostream>
#include <complex>
#include <stdio.h>
#include <stdlib.h>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <complex>
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

void affiche(Fl_Widget* widget, void* data){
        while (cycleAffichage()<H_ZONE){}
}

void gestionAffichage(void*) {
    static int ligne=0;     // Indice de la ligne en cours de calcul + affichage (static pour la conserver cross-boucles :) )
    pointeurFct fonction = retourne_fonction();
    while (ligne<H_ZONE){
    convergenceLigne(fonction, ligne);
    afficheLigne(ligne);
    ligne++;
    }
}

void afficheFractale() {
    fl_color(FL_BLACK);
    //a mettre ailleurs pour ne pas le recalculer a chaque fois?
    long tab[gDonnees.rangMax];
    couleurs(gDonnees.color1,gDonnees.color2,gDonnees.color3,gDonnees.rangColor1,gDonnees.rangColor2,gDonnees.rangColor3,tab);
    for (int j = 0; j < H_ZONE; ++j) {
        for (int i = 0; i < L_ZONE; ++i) {
            if (gDonnees.Tab[i][j].n==-1 )
                {}
            else
                fl_color(tab[gDonnees.Tab[i][j].n]);
                fl_point(i+X_ZONE,j+Y_ZONE);
                fl_color(FL_BLACK);
        }
    }
}

void afficheLigne(int j){
    long tab[gDonnees.rangMax];
    couleurs(gDonnees.color1,gDonnees.color2,gDonnees.color3,gDonnees.rangColor1,gDonnees.rangColor2,gDonnees.rangColor3,tab);
    for (int i = 0; i < L_ZONE; ++i) {
        if (gDonnees.Tab[i][j].n==-1 ){
            fl_color(FL_BLACK);
        }
        else {
            fl_color(tab[gDonnees.Tab[i][j].n]);
        }
        fl_point(i+X_ZONE,j+Y_ZONE);
    }
    //gInterface.ZoneDessin->redraw();
}

    /*
    long tabb[gDonnees.rangMax],c;
    couleurs(gDonnees.color1,gDonnees.color2,gDonnees.color3,gDonnees.rangColor1, gDonnees.rangColor2,gDonnees.rangColor3,tabb);
    long tabb[gDonnees.rangMax],c;
    long A=0xFF000000,B=0x00FF0000,C=0x0000FF00;
    couleurs(A,B,C,10,10,10,tabb);
    fancy colours, quelques tests
    for (int i = 0; i < gDonnees.rangMax; ++i)
    {
        //calcule la couleur a partir du tableau
        c=tabb[i];
        fl_color(0xFFFF);
        fl_pie(X_ZONE+5*(i),Y_ZONE+100,5,10,0,360 );
        //cout << c << endl;
        fl_color(c);
        fl_pie(X_ZONE+5*(i),Y_ZONE+120,5,30,0,360 );
        fl_color(165810);
        fl_pie(X_ZONE+5*(i),Y_ZONE+140,5,5,0,360 );
        fl_color(331366);
        fl_pie(X_ZONE+5*(i),Y_ZONE+160,5,5,0,360 );
        fl_color(c);
        fl_pie(X_ZONE+2*(i),Y_ZONE+180,4,20,0,360 );
    }
    */
