#include <iostream>
#include <stdio.h>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
using namespace std;
#include "main.h"
#include "u1-interface.h"
#include "u2-dessin.h"
#include "u3-callbacks.h"
#include "u4-fonctions.h"

void ZoneDessinInitialisation(Fl_Widget* widget, void* data)
{
    if (gTests.calcul){
        fl_color(FL_BLACK);
        fl_rectf(X_ZONE, Y_ZONE, L_ZONE, H_ZONE);
}
 else   fl_draw_image(gDonnees.buffer,X_ZONE,Y_ZONE,L_ZONE,H_ZONE,3);//evite l'ecran noir lors du refresh mais affiche un double lors des redraw.
//     On initialise la gestion de l'affichage de la fractale seulement quand la fenêtre est correctement creee
    gTests.dessin=true;
    Fl::add_timeout(0, gestionAffichage_iter, NULL );
    //Fl::wait(0);
    //gestionAffichage_iter(NULL);
}

void gestionAffichage_iter(void*)
{
    gTests.dessin=false;
    pointeurFct fonction = retourne_fonction();
    int ligne;
    int tabDegrade[gDonnees.rangMax+50][3];     // On pourrait faire une struct de vars actuelles
    
    //printf("Calcul de couleur\n");
   couleursRGB(gDonnees.slider,tabDegrade);
    
    

    for (ligne=0 ; ligne<H_ZONE; ligne+=2)
    {
        Fl::wait(0);
        if (gTests.calcul)
            convergenceLigne(ligne, fonction);
        if (gTests.dessin)
            return void();
        afficheLigneRGB(ligne, tabDegrade);
    }

    for (ligne-- ; ligne>0; ligne-=2)
    {
        Fl::wait(0);
        if (gTests.calcul)
            convergenceLigne(ligne, fonction);
        if (gTests.dessin)
            return void();
        afficheLigneRGB(ligne, tabDegrade);
    }
    
    gTests.calcul=0;
    calcBuffer(tabDegrade);
    if(gTests.calccouleurs){
        gInterface.Degrade->redraw();
        gInterface.ZoneDessin->redraw();
    }
    gTests.calccouleurs=0;
    
    

}

/*void afficheLigne(int j, unsigned long tableauCouleurs[])
{
    for (int i = 0; i < L_ZONE; ++i)
    {
        if (gDonnees.Tab[i][j].n==-1 )
            fl_color(FL_BLACK);
        else
            fl_color(tableauCouleurs[gDonnees.Tab[i][j].n]);
        fl_point(i+X_ZONE,j+Y_ZONE);
    }
}*/
void afficheLigneRGB(int j, int tabDegrade[][3])
{
    for (int i = 0; i < L_ZONE; i=i+1)
    {
        if (gDonnees.Tab[i][j].n==-1 )
        {
            gDonnees.buffer[3*i+3*L_ZONE*j]=0;
            gDonnees.buffer[3*i+3*L_ZONE*j+1]=0;
            gDonnees.buffer[3*i+3*L_ZONE*j+2]=0;
        }

        else
        {

            gDonnees.buffer[3*i+3*L_ZONE*j]=tabDegrade[gDonnees.Tab[i][j].n][0];
            gDonnees.buffer[3*i+3*L_ZONE*j+1]=tabDegrade[gDonnees.Tab[i][j].n][1];
            gDonnees.buffer[3*i+3*L_ZONE*j+2]=tabDegrade[gDonnees.Tab[i][j].n][2];
        }

    }
    fl_draw_image(&gDonnees.buffer[3*L_ZONE*j],X_ZONE,Y_ZONE+j,L_ZONE,1,3);
}

void tracerCadre (int x1, int y1 , int x2, int y2)
{
    int a=x1;
    int b=y1;
    int a1=x1;
    int b1=y2;
    int a2=x2;
    int b2=y2;
    int a3=x2;
    int b3=y1;

    fl_loop(a, b, a1, b1, a2, b2, a3, b3);
    fl_loop(a+1,b+1,a1+1,b1+1,a2+1,b2+1,a3+1,b3+1);

}


void zoneDegrade(Fl_Widget* widget, void* data){
    for (int i = 0; i < 20; ++i)
    {
        fl_draw_image(gDonnees.bufferDeg,X_ZONE+L_ZONE+110,550+i,325,1,3);
    }
}