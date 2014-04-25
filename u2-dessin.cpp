#include <iostream>
#include <complex>
#include <stdlib.h>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <complex>
#include "main.h"
#include "u1-interface.h"
#include "u2-dessin.h"

#include "u4-fonctions.h"

void ZoneDessinDessinerCB( Fl_Widget* widget, void* data )
{
    // On efface toute la zone ( en dessinant dessus un rectangle plein, noir )
    fl_color(FL_BLACK);
    fl_rectf(X_ZONE, Y_ZONE, L_ZONE, H_ZONE);


}

void afficheFractale(){
	for (int i = 0; i < H_ZONE; ++i)
	{
		for (int j = 0; j < L_ZONE; ++j)
		{

		}
	}
}
