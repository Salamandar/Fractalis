#ifndef _u1_interface_h
#define _u1_interface_h

#include "main.h"
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Value_Output.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Value_Input.H>

#define X_ZONE  25
#define Y_ZONE  25
#define L_ZONE  650
#define H_ZONE  650

struct Interface {
    Fl_Double_Window*   Fenetre;       // Fenêtre du projet
    DrawingArea*        ZoneDessin;        // Zone de dessin
    Fl_Button*          BoutonQuitter;       // Quitter le programme
    Fl_Button*          BoutonEnregistrer;   // Enregistrer l'image
    Fl_Button*          BoutonReset;         // Revenir aux paramères par défaut
    Fl_Value_Input*     ChampModuleDeSortie;  // Module de sortie
    Fl_Value_Input*     ChampProfondeur;      // Profondeur
    Fl_Choice*          MenuFractale;        // Type de fractale
    //Fl_Button*ZoomPlus;             // Zoomer
    //Fl_Button*ZoomMoins;            // Dézoomer
};

extern struct Interface gInterface;


void CreerInterface();
void ActualiserInterface();

#endif
