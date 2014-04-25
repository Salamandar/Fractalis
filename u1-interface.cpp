#include <iostream>
#include <complex>
#include <stdlib.h>
#include "u1-interface.h"
#include "u2-dessin.h"
#include "u3-callbacks.h"
#include "u4-fonctions.h"
using namespace std;

// Definition des donnees de l'interface - structure globale de variables
struct Interface gInterface;

void CreerInterface()
{


    // Creation de la fenetre principale
    gInterface.Fenetre = new Fl_Double_Window(X_ZONE+L_ZONE+400,Y_ZONE+H_ZONE);
    gInterface.Fenetre->label("Generateur de fractales");
    gInterface.Fenetre->begin();

    // Creation de la zone de dessin
    gInterface.ZoneDessin = new DrawingArea(X_ZONE,Y_ZONE,L_ZONE,H_ZONE);
    gInterface.ZoneDessin->draw_callback( ZoneDessinDessinerCB, NULL );
    gInterface.ZoneDessin->mouse_callback( ZoneDessinSourisCB, NULL );

    // Creation du menu de choix du type de fractale
    gInterface.MenuFractale = new Fl_Choice( X_ZONE+L_ZONE+100 , 50  ,100, 20, "Type Fractale : " );
    gInterface.MenuFractale->add( "Julia", "", MenuFractaleCB );
    gInterface.MenuFractale->add( "Mandelbrot", "", MenuFractaleCB );
    gInterface.MenuFractale->add( "Cosinus", "", MenuFractaleCB );
    gInterface.MenuFractale->add( "Sinus", "", MenuFractaleCB );

    // Creation du champ de saisie module de sortie
    gInterface.ChampModuleDeSortie = new Fl_Value_Input(X_ZONE+L_ZONE+100, 90 , 100, 20, "Module de sortie : ");
	gInterface.ChampModuleDeSortie->when( FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE );
	gInterface.ChampModuleDeSortie->callback(ChampModuleDeSortieCB, NULL );

    // Creation du champ de saisie profondeur
    gInterface.ChampProfondeur = new Fl_Value_Input(X_ZONE+L_ZONE+100, 130 , 100, 20, "Profondeur : ");
	gInterface.ChampProfondeur->when( FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE );
	gInterface.ChampProfondeur->callback(ChampProfondeurCB, NULL );

    // Creation du bouton Enregistrer
    gInterface.BoutonEnregistrer = new Fl_Button(X_ZONE,Y_ZONE-20 , 100, 20, "Enregistrer");
    gInterface.BoutonEnregistrer->callback( BoutonQuitterCB, NULL );

    // Creation du bouton Reset
    gInterface.BoutonReset = new Fl_Button(X_ZONE+100,Y_ZONE-20, 100, 20, "Reset");
    gInterface.BoutonReset->callback( BoutonQuitterCB, NULL );

    // Creation du bouton Quitter
    gInterface.BoutonQuitter = new Fl_Button(X_ZONE+200, Y_ZONE-20 , 100, 20, "Quitter");
    gInterface.BoutonQuitter->callback( BoutonQuitterCB, NULL );






    // Affichage de la fenetre
    gInterface.Fenetre->end();
    gInterface.Fenetre->show();
}

void ActualiserInterface()
{

}
