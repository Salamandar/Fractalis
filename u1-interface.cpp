#include <iostream>
#include <complex>
#include <stdlib.h>
#include "u1-interface.h"
#include "u2-dessin.h"
#include "u3-callbacks.h"
#include "u4-fonctions.h"

// Definition des donnees de l'interface - structure globale de variables
struct Interface gInterface;

void CreerInterface() {


    // Creation de la fenetre principale
    gInterface.Fenetre=new Fl_Double_Window(X_ZONE+L_ZONE+400,Y_ZONE+H_ZONE);
    gInterface.Fenetre->label("Générateur de fractales");
    gInterface.Fenetre->begin();

    // Creation du bouton Enregistrer
    gInterface.BoutonEnregistrer = new Fl_Button(X_ZONE, 0, 100, Y_ZONE, "Enregistrer");
    gInterface.BoutonEnregistrer->callback(BoutonQuitterCB, NULL);

    // Creation du bouton Reset
    gInterface.BoutonReset = new Fl_Button(X_ZONE+100, 0, 100, Y_ZONE, "Reset");
    gInterface.BoutonReset->callback(BoutonQuitterCB, NULL);

    // Creation du bouton Quitter
    gInterface.BoutonQuitter = new Fl_Button(X_ZONE+200, 0, 100, Y_ZONE, "Quitter");
    gInterface.BoutonQuitter->callback(BoutonQuitterCB, NULL);


    // Creation de la zone de dessin
    gInterface.ZoneDessin=new DrawingArea(X_ZONE,Y_ZONE,L_ZONE,H_ZONE);
    gInterface.ZoneDessin->draw_callback(ZoneDessinDessinerCB, NULL);
    gInterface.ZoneDessin->mouse_callback(ZoneDessinSourisCB, NULL);


    // Creation du menu de choix du type de fractale
    gInterface.MenuFractale=new Fl_Choice(X_ZONE+L_ZONE+200 , 50,100, 20, "Type de Fractale : ");
    gInterface.MenuFractale->add("Julia", "", MenuFractaleCB);
    gInterface.MenuFractale->add("Mandelbrot", "", MenuFractaleCB);
    gInterface.MenuFractale->add("Cosinus", "", MenuFractaleCB);
    gInterface.MenuFractale->add("Sinus", "", MenuFractaleCB);

    // Creation du champ de saisie module de sortie
    gInterface.ChampModuleDeSortie = new Fl_Value_Input(X_ZONE+L_ZONE+200, 90 , 100, 20, "Module de sortie : ");
    gInterface.ChampModuleDeSortie->when(FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE);
    gInterface.ChampModuleDeSortie->callback(ChampModuleDeSortieCB, NULL);

    // Creation du champ de saisie profondeur
    gInterface.ChampProfondeur = new Fl_Value_Input(X_ZONE+L_ZONE+200, 130 , 100, 20, "Profondeur : ");
    gInterface.ChampProfondeur->when(FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE);
    gInterface.ChampProfondeur->callback(ChampProfondeurCB, NULL);

    //Choix du coin inférieur gauche
    gInterface.ChampXMin = new Fl_Value_Input(X_ZONE+L_ZONE+200, 170, 25, 20, "coordonnées du Min ");
    gInterface.ChampXMin->when(FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE);
    gInterface.ChampXMin->callback(ChampXMinCB, NULL);

    gInterface.ChampYMin = new Fl_Value_Input(X_ZONE+L_ZONE+250, 170, 25, 20);
    gInterface.ChampYMin->when(FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE);
    gInterface.ChampYMin->callback(ChampYMinCB, NULL);

    //Choix de la largeur de l'affichage
    gInterface.ChampLargeur = new Fl_Value_Input(X_ZONE+L_ZONE+200, 210 , 50, 20);
    gInterface.ChampLargeur->when(FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE);
    gInterface.ChampLargeur->callback(ChampLargeurCB, NULL);

    //Carré couleur
    gInterface.CarreChoixCouleur = new Fl_Color_Chooser(X_ZONE+L_ZONE+125,250, 150, 150);
    gInterface.CarreChoixCouleur->callback(CarreChoixCouleurCB, NULL);

    // Affichage de la fenetre
    gInterface.Fenetre->end();
    gInterface.Fenetre->show();
}
