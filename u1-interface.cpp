#include <iostream>
using namespace std;
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

    // Creation des boutons supérieurs
    gInterface.BoutonEnregistrer= new Fl_Button(X_ZONE,     0, 100, Y_ZONE, "Enregistrer");
    gInterface.BoutonEnregistrer->callback(BoutonEnregistrerCB, NULL);
    gInterface.BoutonReset      = new Fl_Button(X_ZONE+100, 0, 100, Y_ZONE, "Reset");
    gInterface.BoutonReset      ->callback(BoutonResetCB,       NULL);
    gInterface.BoutonQuitter    = new Fl_Button(X_ZONE+200, 0, 100, Y_ZONE, "Quitter");
    gInterface.BoutonQuitter    ->callback(BoutonQuitterCB,     NULL);

    // Creation de la zone de dessin
    gInterface.ZoneDessin=new DrawingArea(X_ZONE,Y_ZONE,L_ZONE,H_ZONE);
    gInterface.ZoneDessin->draw_callback(ZoneDessinInitialisation, NULL);
    gInterface.ZoneDessin->mouse_callback(ZoneDessinSourisCB, NULL);


    // Creation du menu de choix du type de fractale
    gInterface.MenuFractale=new Fl_Choice(X_ZONE+L_ZONE+200, 30, 100, 20, "Type de Fractale :");
    gInterface.MenuFractale->add("Mandelbrot", "", MenuFractaleCB);
    gInterface.MenuFractale->add("Julia", "", MenuFractaleCB);
    gInterface.MenuFractale->add("Cos+C", "", MenuFractaleCB);
    gInterface.MenuFractale->add("Sin+z0", "", MenuFractaleCB);
    gInterface.MenuFractale->add("Personna", "", MenuFractaleCB);
    gInterface.MenuFractale->value(0);
    gInterface.MenuFractale->callback(MenuFractaleCB);

    // Creation du champ de saisie module de sortie
    gInterface.ChampModuleDeSortie = new Fl_Value_Input(X_ZONE+L_ZONE+200, 60 , 100, 20, "Module de sortie :");
    //gInterface.ChampModuleDeSortie->value(gDonnees.moduleMax);
    gInterface.ChampModuleDeSortie->when(FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE);
    gInterface.ChampModuleDeSortie->callback(ChampModuleDeSortieCB, NULL);

    // Creation du champ de saisie profondeur
    gInterface.ChampProfondeur = new Fl_Value_Input(X_ZONE+L_ZONE+200, 90 , 100, 20, "Rang maximum de calcul :");
    //gInterface.ChampProfondeur->value(gDonnees.rangMax);
    gInterface.ChampProfondeur->when(FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE);
    gInterface.ChampProfondeur->callback(ChampProfondeurCB, NULL);

    //Choix du coin inférieur gauche
    gInterface.ChampXMin = new Fl_Value_Input(X_ZONE+L_ZONE+200, 120, 100, 20, "Coordonnées du Min : X ");
    gInterface.ChampXMin->when(FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE);
    gInterface.ChampXMin->callback(ChampXMinCB, NULL);

    gInterface.ChampYMin = new Fl_Value_Input(X_ZONE+L_ZONE+200, 150, 100, 20,"Y ");
    gInterface.ChampYMin->when(FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE);
    gInterface.ChampYMin->callback(ChampYMinCB, NULL);

    //Choix de la largeur de l'affichage
    gInterface.ChampLargeur = new Fl_Value_Input(X_ZONE+L_ZONE+200, 180 , 100, 20, "Largeur de l'affichage :");
    gInterface.ChampLargeur->when(FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE);
    gInterface.ChampLargeur->callback(ChampLargeurCB, NULL);

    //Carré couleur
    gInterface.CarreChoixCouleur = new Fl_Color_Chooser(X_ZONE+L_ZONE+75,210, 225, 150);
    gInterface.CarreChoixCouleur->rgb(1,0,0);
    gInterface.CarreChoixCouleur->callback(CarreChoixCouleurCB, NULL);

    //Sliders
    gInterface.Slider1 = new Fl_Value_Slider(X_ZONE+L_ZONE+75,370,225,20,"Couleur 1");
    gInterface.Slider1->type(FL_HOR_NICE_SLIDER);
    gInterface.Slider1->callback(Slider1CB, NULL);
    gInterface.Slider2 = new Fl_Value_Slider(X_ZONE+L_ZONE+75,410,225,20,"Couleur 2");
    gInterface.Slider2->type(FL_HOR_NICE_SLIDER);
    gInterface.Slider2->callback(Slider2CB, NULL);
    gInterface.Slider3 = new Fl_Value_Slider(X_ZONE+L_ZONE+75,450,225,20,"Couleur 3");
    gInterface.Slider3->type(FL_HOR_NICE_SLIDER);
    gInterface.Slider3->callback(Slider3CB, NULL);

    // Affichage de la fenetre
    gInterface.Fenetre->end();
    gInterface.Fenetre->show();
}
