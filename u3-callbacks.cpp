#include <iostream>
#include <complex>
#include <stdlib.h>
#include <FL/Fl.H>
#include <FL/fl_ask.H>
#include <FL/Fl_File_Chooser.H>
#include "u1-interface.h"

#include "u3-callbacks.h"
#include "u4-fonctions.h"
using namespace std;

void TraiterCycleCB() {
    gInterface.ZoneDessin->redraw();
}

void ZoneDessinSourisCB( Fl_Widget* widget, void* data ) {
    // ATTENTION : X et Y ne sont pas relatifs a la zone mais a la fenetre qui la contient !!!!

    if ( Fl::event() == FL_PUSH ){
        printf("Mouse push = %i x = %i y = %i\n", Fl::event_button(), Fl::event_x(), Fl::event_y());
    }

    if ( Fl::event() == FL_MOVE ){
    }
}


void ZoneDessinClavierCB( Fl_Widget* widget, void* data ){
    // Definition des variables
    int Touche;

    // Recuperation de la touche clavier activee
    Touche = Fl::event_key();

    switch ( Touche ){
        case FL_Left :
            printf("Appui sur la touche Gauche\n");
            break;
        case FL_Right :
            printf("Appui sur la touche Droite\n");
            break;
        case FL_Up :
            printf("Appui sur la touche Haut\n");
            break;
        case FL_Down :
            printf("Appui sur la touche Bas\n");
            break;
        case ' ' :
            printf("Appui sur la touche Espace\n");
            break;
        case 'a' :
            printf("Appui sur le caractere a\n");
            break;
        case 'b' :
            printf("Appui sur le caractere b\n");
            break;
        case '1' :
            printf("Appui sur le caractere 1\n");
            break;
        case '2' :
            printf("Appui sur le chiffre 2\n");
            break;
    }
}

void BoutonQuitterCB(Fl_Widget* w, void* data){
    // Fin du programme
    exit(0);
}

void CaseRebondCB(Fl_Widget* w, void* data){
}

void BoutonActionCB(Fl_Widget* w, void* data){
     printf("BoutonActionCB\n");
}

void ChampSaisieTxtCB(Fl_Widget* w, void* data){
    char Saisie[80];
    strcpy( Saisie, gInterface.ChampSaisieTxt->value() );
    printf("ChampSaisieTxtCB : %s\n", Saisie);
}

void ChampSaisieNumCB(Fl_Widget* w, void* data){
    int Valeur;
    Valeur = (int)gInterface.ChampSaisieNum->value();
    printf("ChampSaisieNumCB : %i\n", Valeur);
}


void CurseurCB(Fl_Widget* w, void* data){
}

void CaseCocherCB(Fl_Widget* w, void* data){
}

void BoutonRadioCB(Fl_Widget* w, void* data){
}

void MenuOptionsCB(Fl_Widget* w, void* data){
}


void BoutonMessageCB(Fl_Widget* w, void* data){
    int Score = 2002;
    fl_message("Bravo, votre score est : %d", Score );
}


void BoutonAvertissementCB(Fl_Widget* w, void* data){
    int Seuil = 12;
	fl_alert("Seuil critique atteint : %d", Seuil );
}

void BoutonQuestionCB(Fl_Widget* w, void* data){
	int Reponse;
	Reponse = fl_choice("Voulez vous continuer ?","Non", "Oui", "Annuler");
    printf("BoutonQuestionCB : Reponse = %i\n", Reponse);
}

void BoutonChoisirFichierCB( Fl_Widget* w, void* data ){
	char* NomFichier;  // et pas : char NomFichier[128]

    NomFichier = (char*) fl_file_chooser("Choisissez un fichier", "*.txt", NULL);

    if ( NomFichier != NULL )
    {
        printf("BoutonChoisirFichierCB : Fichier choisi = %s\n", NomFichier);
    }
    else
    {
        printf("BoutonChoisirFichierCB : Aucun fichier choisi\n");
    }
}

void BoutonSaisirChaineCB(Fl_Widget* w, void* data){
	const char* Saisie; // et pas : char Saisie[80]
	char Chaine[80];

	// Saisie de la chaine
	strcpy(Chaine, "" );
	do
	{
		Saisie = fl_input("Entrez une chaine", "" );
		if ( Saisie != NULL )
			//sscanf( Saisie, "%s", Chaine );
			strcpy (Chaine, Saisie);
	} while ( strcmp( Chaine, "" ) == 0 );

    printf("BoutonSaisirChaineCB : Chaine = %s\n", Chaine);
}

void BoutonSaisirEntierCB(Fl_Widget* w, void* data){
	const char* Saisie;
	int Entier;
    int Ok=0;
	do
	{
		Saisie = fl_input("Entrez un entier", "" );
		if ( Saisie != NULL )
			Ok = sscanf(Saisie, "%d", &Entier);
	} while (Ok != 1);
    printf("BoutonSaisirEntierCB : Entier = %i\n", Entier);
}
