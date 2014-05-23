#ifndef _u1_interface_h
#define _u1_interface_h

#include "main.h"
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Value_Output.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Color_Chooser.H>

#define X_ZONE  0
#define Y_ZONE  21
#define L_ZONE  800
#define H_ZONE  600

struct Interface {
    Fl_Double_Window*   Fenetre;            // Fenetre du projet
    DrawingArea*        ZoneDessin;         // Zone de dessin
    Fl_Button*          BoutonQuitter;      // Quitter le programme
    Fl_Button*          BoutonEnregistrer;  // Enregistrer l'image
    Fl_Button*          BoutonReset;        // Revenir aux param?es par d?aut
    Fl_Button*          BoutonAide;
    Fl_Button*          BoutonSaveParams;
    Fl_Button*          BoutonBackParams;

    Fl_Value_Input*     ChampModuleDeSortie;// Module de sortie
    Fl_Value_Input*     ChampProfondeur;    // Profondeur
    Fl_Choice*          MenuFractale;       // Type de fractale
    Fl_Value_Input*     ChampXMin;          // definition du coin inferieur gauche
    Fl_Value_Input*     ChampYMin;
    Fl_Value_Input*     ChampLargeur;       // largeur d'affichage
    Fl_Value_Input*     ChampCX;            //Coordonnées de C
    Fl_Value_Input*     ChampCY;
    Fl_Color_Chooser*   CarreChoixCouleur;  //
    Fl_Value_Slider*    Slider1;
    Fl_Value_Slider*    Slider2;
    Fl_Value_Slider*    Slider3;
};
extern struct Interface gInterface;

void CreerInterface();
#endif
