#include <iostream>
#include <stdlib.h>
#include <FL/Fl.H>
#include <FL/fl_ask.H>
#include <FL/Fl_File_Chooser.H>
using namespace std;
#include "u1-interface.h"
#include "u2-dessin.h"
#include "u3-callbacks.h"
#include "u4-fonctions.h"

void ZoneDessinSourisCB( Fl_Widget* widget, void* data ) {
    // ATTENTION : X et Y ne sont pas relatifs a la zone mais a la fenetre qui la contient !!!!

    // Gestion du zoom cadre (clic droit)
    static int x1;
    static int y1;
    static int x2;
    static int y2;
    int bouton=Fl::event_button();
    //cout<<bouton<<endl;
    // prise des coordonnees initiales de la souris
    if(Fl::event() == FL_PUSH && bouton ==3){
        printf("Mouse push = %i x = %i y = %i\n", Fl::event_button(), Fl::event_x(), Fl::event_y());
        x1=Fl::event_x();
        y1=Fl::event_y();
    }
    // prise des coordonnees finales
    if(Fl::event() == FL_RELEASE && bouton == 3){
        printf("Mouse release = %i x = %i y = %i\n", Fl::event_button(), Fl::event_x(), Fl::event_y());
        x2=Fl::event_x();
        y2=Fl::event_y();
        // Recadrage de l'image
        if(x1<x2)
            real(gDonnees.ig)=real(gDonnees.ig)+(x1)*gDonnees.pasxy;
        else
            real(gDonnees.ig)=real(gDonnees.ig)+(x2)*gDonnees.pasxy;

        if (y1>y2)
            imag(gDonnees.ig)=imag(gDonnees.ig)+(H_ZONE-y1)*gDonnees.pasxy;
        else
            imag(gDonnees.ig)=imag(gDonnees.ig)+(H_ZONE-y2)*gDonnees.pasxy;

        // Modification du pas
        if(x1<x2)
          gDonnees.pasxy=gDonnees.pasxy*(x2-x1)/L_ZONE;
        else
            gDonnees.pasxy=gDonnees.pasxy*(x1-x2)/L_ZONE;

        //if(x1<x2){
        //    gDonnees.pasxy=gDonnees.pasxy*(x2-x1)/L_ZONE;
        //}

        //else{
        //    gDonnees.pasxy=gDonnees.pasxy*(x1-x2)/L_ZONE;
        //}
            //Definit C pour Julia

        gInterface.ZoneDessin->redraw();
    }


    //Gestion du zoom roulette
    if(Fl::event() == FL_MOUSEWHEEL) {
        gDonnees.pasxy = gDonnees.pasxy*(1.+0.2*(double)(Fl::event_dy()));
        gInterface.ZoneDessin->redraw();
    }

    //Gestion du déplacement (clic gauche)
    static int u1;
    static int u2;
    static int v1;
    static int v2;
    // prise des coordonnees initiales de la souris
    if(Fl::event() == FL_PUSH && bouton ==1){
        printf("Mouse push = %i x = %i y = %i\n", Fl::event_button(), Fl::event_x(), Fl::event_y());
        u1=Fl::event_x();
        v1=Fl::event_y();
    }
    // prise des coordonnees finales
    if(Fl::event() == FL_RELEASE && bouton == 1){
        printf("Mouse release = %i x = %i y = %i\n", Fl::event_button(), Fl::event_x(), Fl::event_y());
        u2=Fl::event_x();
        v2=Fl::event_y();
        //déplacement de l'image
        real(gDonnees.ig)=real(gDonnees.ig)+(u1-u2)*gDonnees.pasxy;
        imag(gDonnees.ig)=imag(gDonnees.ig)+(v2-v1)*gDonnees.pasxy;
        gInterface.ZoneDessin->redraw();
    }

    //Definit C pour Julia
    if(Fl::event_button()==2 && Fl::event()==FL_PUSH){
        double x,y;
        x=Fl::event_x();
        y=Fl::event_y();
        real(gDonnees.C)=real(gDonnees.ig)+x*gDonnees.pasxy;
        imag(gDonnees.C)=imag(gDonnees.ig)+y*gDonnees.pasxy;
        cout<<"C= : ("<<real(gDonnees.C)<<","<<imag(gDonnees.C)<<")"<<endl;
        gInterface.ZoneDessin->redraw();
    }
}



void BoutonQuitterCB(Fl_Widget* w, void* data){
    // Fin du programme
    exit(0);
}

void BoutonEnregistrerCB(Fl_Widget* w, void* data){
    // Enregistre le fichier image et texte

}

void BoutonResetCB(Fl_Widget* w, void* data){
    // retour aux paramètres initiaux
    InitialiserDonnees();
    gInterface.ZoneDessin->redraw();
}


void ChampProfondeurCB(Fl_Widget* w, void* data){
     //gInterface.ChampProfondeur->value(gDonnees.rangMax);
    float temp=gDonnees.rangMax; //c'est pour réduire le rang des couleurs en mm temps
    gDonnees.rangMax = (int)gInterface.ChampProfondeur->value();
    printf("ChampProfondeurCB : %d\n", gDonnees.rangMax);
    temp=temp/gDonnees.rangMax;
    gDonnees.rangColor1=gDonnees.rangColor1/temp;
    gDonnees.rangColor2=gDonnees.rangColor2/temp;
    gDonnees.rangColor3=gDonnees.rangColor3/temp;
    gInterface.Slider1->scrollvalue(gDonnees.rangColor1,0,0,gDonnees.rangMax);
    gInterface.Slider1->color(gDonnees.color1,gDonnees.color1);
    gInterface.Slider2->scrollvalue(gDonnees.rangColor2,0,0,gDonnees.rangMax);
    gInterface.Slider2->color(gDonnees.color2,gDonnees.color2);
    gInterface.Slider3->scrollvalue(gDonnees.rangColor3,0,0,gDonnees.rangMax);
    gInterface.Slider3->color(gDonnees.color3,gDonnees.color3);
    gInterface.ZoneDessin->redraw();
}

void ChampModuleDeSortieCB(Fl_Widget* w, void* data){
    gDonnees.moduleMax = (int)gInterface.ChampModuleDeSortie->value();
    printf("ChampModuleDeSortieCB : %lf\n", gDonnees.moduleMax);
    gInterface.ZoneDessin->redraw();
}



void MenuFractaleCB(Fl_Widget* w, void* data){
    int Fractale = (int)gInterface.MenuFractale->value() ;
    switch((int)gInterface.MenuFractale->value()){
        case 0: gDonnees.Fractale=MANDELBROT;
            break;
        case 1: gDonnees.Fractale=JULIA;
            break;
        case 2: gDonnees.Fractale=COSC;
            break;
        case 3: gDonnees.Fractale=SINZO;
            break;
        case 4: gDonnees.Fractale=PERSONNA;
            break;
    }
    gTests.calcul=1;
    gTests.dessin=1;
    gInterface.ZoneDessin->redraw();
}

void ChampXMinCB(Fl_Widget* w, void* data){
    real(gDonnees.ig) = gInterface.ChampXMin->value();
    gTests.calcul=1;
    gTests.dessin=1;
    gInterface.ZoneDessin->redraw();
}

void ChampYMinCB(Fl_Widget* w, void* data){
    imag(gDonnees.ig) = gInterface.ChampYMin->value();
    gTests.calcul=1;
    gTests.dessin=1;
    gInterface.ZoneDessin->redraw();
}

void ChampLargeurCB(Fl_Widget* w, void* data){
    gDonnees.pasxy = ((double)gInterface.ChampLargeur->value())/L_ZONE;
    gTests.calcul=1;
    gTests.dessin=1;
    gInterface.ZoneDessin->redraw();
}

void Slider1CB(Fl_Widget* w, void* data){
    gTests.slider=1;
    gDonnees.rangColor1=(int)gInterface.Slider1->value();
    if(gDonnees.rangColor1>gDonnees.rangColor2){
        gDonnees.rangColor2=gDonnees.rangColor1;
        gInterface.Slider2->value(gDonnees.rangColor2);
    }
    if(gDonnees.rangColor1>gDonnees.rangColor3){
        gDonnees.rangColor3=gDonnees.rangColor1;
        gInterface.Slider3->value(gDonnees.rangColor3);
    }
    gTests.dessin=1;
    gInterface.ZoneDessin->redraw();
}

void Slider2CB(Fl_Widget* w, void* data){
    gTests.slider=2;
    gDonnees.rangColor2=(int)gInterface.Slider2->value();
    if(gDonnees.rangColor1>gDonnees.rangColor2){
        gDonnees.rangColor1=gDonnees.rangColor2;
        gInterface.Slider1->value(gDonnees.rangColor1);
    }
    if(gDonnees.rangColor2>gDonnees.rangColor3){
        gDonnees.rangColor3=gDonnees.rangColor2;
        gInterface.Slider3->value(gDonnees.rangColor3);
    }
    gTests.dessin=1;
    gInterface.ZoneDessin->redraw();
}


void Slider3CB(Fl_Widget* w, void* data){
    gTests.slider=3;
    gDonnees.rangColor3=(int)gInterface.Slider3->value();
    if(gDonnees.rangColor1>gDonnees.rangColor3){
        gDonnees.rangColor1=gDonnees.rangColor3;
        gInterface.Slider1->value(gDonnees.rangColor1);
    }
    if(gDonnees.rangColor2>gDonnees.rangColor3){
        gDonnees.rangColor2=gDonnees.rangColor3;
        gInterface.Slider2->value(gDonnees.rangColor2);
    }
    gTests.dessin=1;
    gInterface.ZoneDessin->redraw();
}

void CarreChoixCouleurCB(Fl_Widget* w, void* data){
    float r=255*gInterface.CarreChoixCouleur->r();
    float g=255*gInterface.CarreChoixCouleur->g();
    float b=255*gInterface.CarreChoixCouleur->b();

    switch(gTests.slider){
        case 1: gDonnees.color1=255+256*(int)b+256*256*(int)g+256*256*256*(int)r;
                gInterface.Slider1->color(gDonnees.color1,gDonnees.color1);
            break;
        case 2: gDonnees.color2=255+256*(int)b+256*256*(int)g+256*256*256*(int)r;
                gInterface.Slider2->color(gDonnees.color2,gDonnees.color2);
            break;
        case 3: gDonnees.color3=255+256*(int)b+256*256*(int)g+256*256*256*(int)r;
                gInterface.Slider3->color(gDonnees.color3,gDonnees.color3);
            break;
        default:
            break;
    }
    gTests.dessin=1;
    gInterface.ZoneDessin->redraw();
}
