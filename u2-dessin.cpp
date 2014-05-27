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
    //fl_color(FL_BLACK);
    //fl_rectf(X_ZONE, Y_ZONE, L_ZONE, H_ZONE);
    fl_draw_image(gDonnees.buffer,X_ZONE,Y_ZONE,L_ZONE,H_ZONE,3);//evite l'écran noir lors du refresh mais affiche un double lors des redraw.
//     On initialise la gestion de l'affichage de la fractale seulement quand la fenêtre est correctement créée
    gTests.dessin=true;
    Fl::add_timeout(0, gestionAffichage_iter, NULL );
    //Fl::wait(0);
    //gestionAffichage_iter(NULL);
}

void gestionAffichage_iter(void*)
{
    if(!gTests.animation)
    {
        gTests.dessin=false;
        pointeurFct fonction = retourne_fonction();
        int ligne;
        unsigned long tabDegrade[gDonnees.rangMax][3];     // On pourrait faire une struct de vars actuelles
        //if(gTests.calccouleurs) {
        printf("Calcul de couleur\n");
        couleursRGB(gDonnees.color1,    gDonnees.color2,    gDonnees.color3,
                 gDonnees.rangColor1,gDonnees.rangColor2,gDonnees.rangColor3,tabDegrade);
        gTests.calccouleurs=0;
        //}

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
        gTests.calccouleurs=0;
    }
    else //ANIMATION
    {
        gTests.dessin=false;
        pointeurFct fonction = retourne_fonction();
        int ligne;

        for (ligne=0 ; ligne<H_ZONE; ligne+=2)
        {
            Fl::wait(0);
            if (gTests.calcul)
                convergenceLigne(ligne, fonction);
        }

        for (ligne-- ; ligne>0; ligne-=2)
        {
            Fl::wait(0);
            if (gTests.calcul)
                convergenceLigne(ligne, fonction);
        }
        unsigned long tabDegrade[gDonnees.rangMax][3];     // On pourrait faire une struct de vars actuelles
        //if(gTests.calccouleurs) {
        printf("Calcul de couleur\n");
        couleursRGB(gDonnees.color1,gDonnees.color2,gDonnees.color3,gDonnees.rangColor1,gDonnees.rangColor2,gDonnees.rangColor3,tabDegrade);
        for(int j=0; j<H_ZONE; j++)
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
        gTests.calccouleurs=0;
        gTests.calcul=0;

    }
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
void afficheLigneRGB(int j, unsigned long tabDegrade[][3])
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

}
