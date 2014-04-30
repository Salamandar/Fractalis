#include <iostream>
#include <complex>
#include <stdlib.h>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include "main.h"
#include "u1-interface.h"
#include "u2-dessin.h"
#include "u3-callbacks.h"
#include "u4-fonctions.h"
using namespace std;

void CycleCB( void* );

int main (int argc, char ** argv)
{
    CreerInterface();

    // Initialisation du logiciel
    InitialiserDonnees(); // On initialise les donnees

    convergencePlan();
    ActualiserInterface(); // On affiche les donnees sur l'interface
    gInterface.ZoneDessin->redraw(); // On redessine la zone de dessin
    // Lancer la boucle de gestion des evenements
    return Fl::run();
}

// Fonction cyclique
void CycleCB( void* )
{
    // Appel de la fonction TraiterCycleCB ( u3-callbacks )
    TraiterCycleCB();

}














// Déclaré dans drawing.h
// Classe et methodes DrawingArea : a considerer comme une librairie fournie, NE PAS MODIFIER

DrawingArea::DrawingArea(int X,int Y,int W,int H)
: Fl_Widget(X,Y,W,H)
{
    _draw_callback_function = NULL;
    _draw_callback_data = NULL;

    _mouse_callback_function = NULL;
    _mouse_callback_data = NULL;

    _keyboard_callback_function = NULL;
    _keyboard_callback_data = NULL;
}

void DrawingArea::draw_callback( void (*Function) ( Fl_Widget* w, void* data), void* Data ){
    _draw_callback_function = Function;
    _draw_callback_data = Data;
}

void DrawingArea::mouse_callback( void (*Function) ( Fl_Widget* w, void* data), void* Data ){
    _mouse_callback_function = Function;
    _mouse_callback_data = Data;
}

void DrawingArea::keyboard_callback( void (*Function) ( Fl_Widget* w, void* data), void* Data ){
    _keyboard_callback_function = Function;
    _keyboard_callback_data = Data;
}

void DrawingArea::draw(){
    fl_push_clip(this->x(), this->y(), this->w(), this->h());
    if ( _draw_callback_function != NULL )
        (* _draw_callback_function ) ( this, _draw_callback_data );
    fl_pop_clip();
}

int DrawingArea::handle(int event){
    switch(event)
    {
        case FL_PUSH:
        case FL_RELEASE:
        case FL_DRAG:
             if ( _mouse_callback_function != NULL )
                (* _mouse_callback_function ) ( this, _mouse_callback_data );
            return 1;
            break;
        case FL_ENTER:
            return 1;
            break;
        case FL_MOVE:
             if ( _mouse_callback_function != NULL )
                (* _mouse_callback_function ) ( this, _mouse_callback_data );
            return 1;
            break;

        case FL_KEYBOARD:
             if ( _keyboard_callback_function != NULL )
                (* _keyboard_callback_function ) ( this, _keyboard_callback_data );
            return 1;
            break;

        case FL_FOCUS:
            return 1;
            break;

        default:
            return Fl_Widget::handle(event);
    }
}

//  Fin classe et methodes DrawingArea
