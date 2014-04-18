#include <iostream>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <complex>
#include "u1-interface.h"
#include "u2-dessin.h"
#include "u4-fonctions.h"
using namespace std;

void ZoneDessinDessinerCB( Fl_Widget* widget, void* data )
{
    // On efface toute la zone ( en dessinant dessus un rectangle plein, noir )
    fl_color(FL_BLACK);
    fl_rectf(X_ZONE, Y_ZONE, L_ZONE, H_ZONE);


}
