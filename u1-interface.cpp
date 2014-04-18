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
    gInterface.Fenetre = new Fl_Double_Window(800,600);
    gInterface.Fenetre->label("Projet Type");
    gInterface.Fenetre->begin();

    // Creation de la zone de dessin
    gInterface.ZoneDessin = new DrawingArea(X_ZONE,Y_ZONE,L_ZONE,H_ZONE);
    gInterface.ZoneDessin->draw_callback( ZoneDessinDessinerCB, NULL );
    gInterface.ZoneDessin->mouse_callback( ZoneDessinSourisCB, NULL );
    gInterface.ZoneDessin->keyboard_callback( ZoneDessinClavierCB, NULL );

    // Creation du bouton Quitter
    gInterface.BoutonQuitter = new Fl_Button(20, 460, 100, 20, "Quitter");
    gInterface.BoutonQuitter->callback( BoutonQuitterCB, NULL );

    // Creation de la case a cocher Rebond
    gInterface.CaseRebond = new Fl_Check_Button(140, 460, 100, 20, "Rebond");
    gInterface.CaseRebond->callback( CaseRebondCB, NULL );

    // Creation du bouton Action
    gInterface.BoutonAction = new Fl_Button(580, 50, 100, 20, "Action");
    gInterface.BoutonAction->callback( BoutonActionCB, NULL );

    // Creation du champ texte
    gInterface.ChampTxt = new Fl_Output(580, 80, 200, 20, "Champ Texte : ");

    // Creation du champ numerique
    gInterface.ChampNum = new Fl_Value_Output(580, 110, 100, 20, "Champ Num : ");

    // Creation du champ de saisie texte
    gInterface.ChampSaisieTxt = new Fl_Input(580, 140, 200, 20, "Champ Saisie Texte : ");
	gInterface.ChampSaisieTxt->when( FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE );
	gInterface.ChampSaisieTxt->callback(ChampSaisieTxtCB, NULL );

    // Creation du champ de saisie numerique
    gInterface.ChampSaisieNum = new Fl_Value_Input(580, 170, 200, 20, "Champ Saisie Num : ");
	gInterface.ChampSaisieNum->when( FL_WHEN_ENTER_KEY | FL_WHEN_RELEASE );
	gInterface.ChampSaisieNum->callback(ChampSaisieNumCB, NULL );

     // Creation du curseur
    gInterface.Curseur = new Fl_Value_Slider(580, 200, 100, 20, "Curseur : ");
    gInterface.Curseur->type( FL_HORIZONTAL );
    gInterface.Curseur->align( FL_ALIGN_LEFT );
    gInterface.Curseur->precision( 0 );
    gInterface.Curseur->bounds( 0, 10 );
	gInterface.Curseur->callback(CurseurCB, NULL );

     // Creation de la case a cocher
    gInterface.CaseCocher = new Fl_Check_Button(580, 230, 100, 20, "CaseCocher");
	gInterface.CaseCocher->callback(CaseCocherCB, NULL );

    // Creation du groupe de boutons radio
    // Aide : methode new Fl_Group( X, Y, L, H, Libelle ) :
    // Le groupe doit englober l'ensemble des boutons (largeur et hauteur).
    // Le libelle du groupe n'est pas considere comme faisant partie du bloc au niveau des interactions.
    // En pratique :
    // - Largeur L : on met pareil que les boutons.
    // - Hauteur H : on met la hauteur d'un bouton multipliee par [le nombre de boutons].
    // - Hauteur H : si probleme, multiplier la hauteur d'un bouton par [le nombre de boutons + 1] ou [le nombre de boutons + 2]

    gInterface.GroupeBoutonsRadio = new Fl_Group( 580, 260, 120, 60, "GroupeBoutonsRadio :" );
    gInterface.GroupeBoutonsRadio->align( FL_ALIGN_LEFT );
    gInterface.GroupeBoutonsRadio->begin();

    gInterface.BoutonRadio1 = new  Fl_Round_Button( 580, 260, 120, 20, "BoutonRadio1");
    gInterface.BoutonRadio1->type(FL_RADIO_BUTTON);
	gInterface.BoutonRadio1->callback(BoutonRadioCB, NULL );

    gInterface.BoutonRadio2 = new  Fl_Round_Button( 580, 280, 120, 20, "BoutonRadio2");
    gInterface.BoutonRadio2->type(FL_RADIO_BUTTON);
	gInterface.BoutonRadio2->callback(BoutonRadioCB, NULL );

    gInterface.BoutonRadio3 = new  Fl_Round_Button( 580, 300, 120, 20, "BoutonRadio3");
    gInterface.BoutonRadio3->type(FL_RADIO_BUTTON);
	gInterface.BoutonRadio3->callback(BoutonRadioCB, NULL );

    gInterface.GroupeBoutonsRadio->end();

    // Creation du menu d'options
    gInterface.MenuOptions = new Fl_Choice( 580, 340, 100, 20, "MenuOptions : " );
    gInterface.MenuOptions->add( "Item1", "", MenuOptionsCB );
    gInterface.MenuOptions->add( "Item2", "", MenuOptionsCB );
    gInterface.MenuOptions->add( "Item3", "", MenuOptionsCB );
    gInterface.MenuOptions->add( "Item4", "", MenuOptionsCB );

    // Creation du bouton Message
    gInterface.BoutonMessage = new  Fl_Button( 580, 390, 100, 20, "Message");
    gInterface.BoutonMessage->callback( BoutonMessageCB);

    // Creation du bouton Avertissement
    gInterface.BoutonAvertissement = new  Fl_Button( 580, 420, 100, 20, "Avertissement");
    gInterface.BoutonAvertissement->callback( BoutonAvertissementCB);

    // Creation du bouton Question
    gInterface.BoutonQuestion = new  Fl_Button( 580, 450, 100, 20, "Question");
    gInterface.BoutonQuestion->callback( BoutonQuestionCB);

    // Creation du bouton ChoixFichier
    gInterface.BoutonChoixFichier = new  Fl_Button( 580, 480, 100, 20, "Choisir Fichier");
    gInterface.BoutonChoixFichier->callback( BoutonChoisirFichierCB);

    // Creation du bouton SaisirChaine
    gInterface.BoutonSaisirChaine = new  Fl_Button( 580, 510, 100, 20, "Saisir Chaine");
    gInterface.BoutonSaisirChaine->callback( BoutonSaisirChaineCB);

    // Creation du bouton SaisirEntier
    gInterface.BoutonSaisirEntier = new  Fl_Button( 580, 540, 100, 20, "Saisir Entier");
    gInterface.BoutonSaisirEntier->callback( BoutonSaisirEntierCB);

    // Affichage de la fenetre
    gInterface.Fenetre->end();
    gInterface.Fenetre->show();
}

void ActualiserInterface()
{
    
}
