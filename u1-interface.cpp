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
    gInterface.Fenetre=new Fl_Double_Window(X_ZONE+L_ZONE+450,Y_ZONE+H_ZONE);
    gInterface.Fenetre->label("Générateur de fractales");
    gInterface.Fenetre->begin();

    // Creation des boutons supérieurs
    gInterface.BoutonEnregistrer= new Fl_Button(X_ZONE,     0, 100, Y_ZONE, "Enregistrer");
    gInterface.BoutonReset      = new Fl_Button(X_ZONE+100, 0, 100, Y_ZONE, "Reset");
    gInterface.BoutonQuitter    = new Fl_Button(X_ZONE+200, 0, 100, Y_ZONE, "Quitter");
    gInterface.BoutonAide       = new Fl_Button(X_ZONE+300, 0, 100, Y_ZONE, "Aide");
    gInterface.BoutonSaveParams = new Fl_Button(X_ZONE+400, 0, 175, Y_ZONE, "Enregistrer les Paramètres");
    gInterface.BoutonBackParams = new Fl_Button(X_ZONE+575, 0, 175, Y_ZONE, "Restaurer des Paramètres");

    gInterface.BoutonEnregistrer->callback(BoutonEnregistrerCB, NULL);
    gInterface.BoutonReset      ->callback(BoutonResetCB,       NULL);
    gInterface.BoutonQuitter    ->callback(BoutonQuitterCB,     NULL);
    gInterface.BoutonAide       ->callback(BoutonAideCB,     NULL);
    gInterface.BoutonSaveParams ->callback(BoutonSaveParamsCB, NULL);
    gInterface.BoutonBackParams ->callback(BoutonBackParamsCB, NULL);
    // Creation de la zone de dessin
    gInterface.ZoneDessin=new DrawingArea(X_ZONE,Y_ZONE,L_ZONE,H_ZONE);
    gInterface.ZoneDessin->draw_callback(ZoneDessinInitialisation, NULL);
    gInterface.ZoneDessin->mouse_callback(ZoneDessinSourisCB, NULL);

/*
        Ceci est la définition des champs à droite.
*/
    int hauteur=0;          // Permet une modification simplifiée de l'interface
    int y_champs=200;
    int largeur_champs=235;
    int largeur_smalls=(largeur_champs-30)/2;   // Il faut réserver 30px pour le texte + i*

    hauteur+=30;
    // Creation du menu de choix du type de fractale
    gInterface.MenuFractale=
        new      Fl_Choice(X_ZONE+L_ZONE+y_champs, hauteur, largeur_champs, 20, "Type de Fractale :");
    gInterface.MenuFractale->add("Mandelbrot",  "", MenuFractaleCB);
    gInterface.MenuFractale->add("Julia",       "", MenuFractaleCB);
    gInterface.MenuFractale->add("Cos+C",       "", MenuFractaleCB);
    gInterface.MenuFractale->add("Sin+z0",      "", MenuFractaleCB);
    gInterface.MenuFractale->add("Personna",    "", MenuFractaleCB);
    gInterface.MenuFractale->value(0);
    gInterface.MenuFractale->callback(MenuFractaleCB);

    hauteur+=30;
    // Creation du champ de saisie module de sortie
    gInterface.ChampModuleDeSortie=
        new Fl_Value_Input(X_ZONE+L_ZONE+y_champs, hauteur, largeur_champs, 20, "Module de sortie :");
    gInterface.ChampModuleDeSortie->value(gDonnees.moduleMax);
    gInterface.ChampModuleDeSortie->when(FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE);
    gInterface.ChampModuleDeSortie->callback(ChampModuleDeSortieCB, NULL);

    hauteur+=30;
    // Creation du champ de saisie profondeur
    gInterface.ChampProfondeur=
        new Fl_Value_Input(X_ZONE+L_ZONE+y_champs, hauteur, largeur_champs, 20, "Rang maximum de calcul :");
    gInterface.ChampProfondeur->value(gDonnees.rangMax);
    gInterface.ChampProfondeur->when(FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE);
    gInterface.ChampProfondeur->callback(ChampProfondeurCB, NULL);

    hauteur+=30;

    //Choix du coin inférieur gauche
    gInterface.ChampXMin =
        new Fl_Value_Input(X_ZONE+L_ZONE+y_champs, hauteur, largeur_smalls, 20, "Coordonnées du Min :");
    gInterface.ChampYMin =
        new Fl_Value_Input(X_ZONE+L_ZONE+y_champs
                   +largeur_champs-largeur_smalls, hauteur, largeur_smalls, 20,"+ i*");
    gInterface.ChampXMin->when(FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE);
    gInterface.ChampXMin->callback(ChampXMinCB, NULL);
    gInterface.ChampYMin->when(FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE);
    gInterface.ChampYMin->callback(ChampYMinCB, NULL);

    hauteur+=30;

    //Choix de la largeur de l'affichage
    gInterface.ChampLargeur =
        new Fl_Value_Input(X_ZONE+L_ZONE+y_champs, hauteur, largeur_champs, 20, "Largeur de l'affichage :");
    gInterface.ChampLargeur->when(FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE);
    gInterface.ChampLargeur->callback(ChampLargeurCB, NULL);

    hauteur+=30;
    //Chammp C
    gInterface.ChampCX =
        new Fl_Value_Input(X_ZONE+L_ZONE+y_champs, hauteur, largeur_smalls, 20, "Coordonnees de C :");
    gInterface.ChampCY =
        new Fl_Value_Input(X_ZONE+L_ZONE+y_champs
                   +largeur_champs-largeur_smalls, hauteur, largeur_smalls, 20, "+ i*");
    gInterface.ChampCX->callback(ChampCXCB, NULL);
    gInterface.ChampCY->callback(ChampCYCB, NULL);

    hauteur+=30;



    int y_colorc=75;
    int largeurc=y_champs-y_colorc+largeur_champs;
    int hauteurc=200;
    //Carré couleur
    gInterface.CarreChoixCouleur =
        new Fl_Color_Chooser(X_ZONE+L_ZONE+y_colorc, hauteur, largeurc, hauteurc);
    gInterface.CarreChoixCouleur->rgb(1,0,0);
    gInterface.CarreChoixCouleur->callback(CarreChoixCouleurCB, NULL);

    hauteur+=hauteurc+20;

    //Sliders
    gInterface.Slider1=
        new Fl_Value_Slider(X_ZONE+L_ZONE+y_colorc, hauteur,largeurc,20,"Couleur 1");
    gInterface.Slider1->type(FL_HOR_NICE_SLIDER);
    gInterface.Slider1->callback(Slider1CB, NULL);
    hauteur+=40;
    gInterface.Slider2=
        new Fl_Value_Slider(X_ZONE+L_ZONE+y_colorc, hauteur,largeurc,20,"Couleur 2");
    gInterface.Slider2->type(FL_HOR_NICE_SLIDER);
    gInterface.Slider2->callback(Slider2CB, NULL);
    hauteur+=40;
    gInterface.Slider3=
        new Fl_Value_Slider(X_ZONE+L_ZONE+y_colorc, hauteur,largeurc,20,"Couleur 3");
    gInterface.Slider3->type(FL_HOR_NICE_SLIDER);
    gInterface.Slider3->callback(Slider3CB, NULL);
    hauteur+=40;



    // Affichage de la fenetre
    gInterface.Fenetre->end();
    gInterface.Fenetre->show();
}
