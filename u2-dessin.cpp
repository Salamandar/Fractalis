#include <iostream>
#include <complex>
#include <stdlib.h>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <complex>
#include "main.h"
#include "u1-interface.h"
#include "u2-dessin.h"
#include <stdio.h>

#include "u4-fonctions.h"

void ZoneDessinInitialisation(Fl_Widget* widget, void* data) {
    fl_color(FL_BLACK);
    fl_rectf(X_ZONE, Y_ZONE, L_ZONE, H_ZONE);
}

void ZoneDessinDessinerCB( Fl_Widget* widget, void* data ) {
    // On efface toute la zone ( en dessinant dessus un rectangle plein, noir )
    fl_color(FL_BLACK);
    fl_rectf(X_ZONE, Y_ZONE, L_ZONE, H_ZONE);
    //convergencePlan();
    afficheFractaleLigne();

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

void afficheFractaleLigne(){
    pointeurFct fonction = retourne_fonction(); // Détermine la fonction
    double pas=gDonnees.pasxy;
    double x_ini=real(gDonnees.ig);
    double y_ini=imag(gDonnees.ig);
    complex<double>coord_init=gDonnees.ig;
    complex<double>pas_complx=(0,gDonnees.pasxy);
    complex<double>coordonnees=coord_init;
    long tab[gDonnees.rangMax];
    couleurs(gDonnees.color1,gDonnees.color2,gDonnees.color3,gDonnees.rangColor1,gDonnees.rangColor2,gDonnees.rangColor3,tab);
    for (int j = 0; j < gDonnees.hauteur; ++j) {
        convergenceLigne(coordonnees, fonction, j);
        coordonnees=complex<double>(x_ini,y_ini+j*pas);
        //coordonnees=coord_init+(double)j*pas_complx;
        for (int i = 0; i < L_ZONE; ++i) {
            printf("TEST1\n");
            if (gDonnees.Tab[i][j].n==-1 )
                fl_color(FL_BLACK);
            else {
                fl_color(tab[gDonnees.Tab[i][j].n]);
            }
                printf("TEST\n");

            fl_point(i+X_ZONE,j+Y_ZONE);
        }
        printf("Attention Redraw !\n");
        gInterface.ZoneDessin->redraw();
    }
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
