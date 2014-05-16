#include <iostream>
#include <complex>
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
    // Mode déplacement
    static int x1;
    static int x2;
    static int y1;
    static int y2;
    int bouton=Fl::event_button();
    cout<<bouton<<endl;
    // prise des coordonnees initiales de la souris
    if(Fl::event() == FL_PUSH && bouton ==3){
        printf("Mouse push = %i x = %i y = %i\n", Fl::event_button(), Fl::event_x(), Fl::event_y());
        x1=Fl::event_x();
        y1=Fl::event_y();
        cout<<"aze"<<endl;
    }

    // prise des coordonnees finales
    if(Fl::event() == FL_RELEASE && bouton == 3){
        printf("Mouse release = %i x = %i y = %i\n", Fl::event_button(), Fl::event_x(), Fl::event_y());
        x2=Fl::event_x();
        y2=Fl::event_y();
        cout<<"plop"<<endl;

        //cout<<"x1 x2 y1 y2 \n"<<x1<<endl<<x2<<endl<<y1<<endl<<y2<<endl;

          // calcul du décalage à effectuer
        if(x1<x2){real(gDonnees.ig)=real(gDonnees.ig)+(x1-X_ZONE)*gDonnees.pasxy;}
        else {real(gDonnees.ig)=real(gDonnees.ig)+(x2-X_ZONE)*gDonnees.pasxy;}
        if (y1>y2){imag(gDonnees.ig)=imag(gDonnees.ig)+(y1-Y_ZONE-H_ZONE)*gDonnees.pasxy;}
        else {imag(gDonnees.ig)=imag(gDonnees.ig)+(y2-Y_ZONE-H_ZONE)*gDonnees.pasxy;}

        cout<<"ig "<<gDonnees.ig;


        gInterface.ZoneDessin->redraw();
    }

    //printf("partie reelle init : %lf" ,real(gDonnees.ig));





    //printf("partie reelle finale : %lf\n" ,real(gDonnees.ig));

    //Mode zoom
    int zoom=0;
    if(Fl::event() == FL_MOUSEWHEEL){
        zoom=Fl::event_dy();
        //cout<<"zoom : "<<zoom<<endl;
        gDonnees.pasxy = gDonnees.pasxy*(1.+0.2*((double)(zoom)));
        cout<<"zoom -> pasxy = "<<gDonnees.pasxy<<endl;
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
    // retour au parametre initiales
    gDonnees.Fractale=FRACT_INIT;
    gDonnees.rangMax=RANGMAX_INIT;
    gDonnees.moduleMax=MODULEMAX_INIT;
    gDonnees.C=C_INIT;
    gDonnees.ig=IG_INIT;
    gDonnees.pasxy=PASXY;
    gInterface.ChampProfondeur->value(gDonnees.rangMax);
    gInterface.ChampModuleDeSortie->value(gDonnees.moduleMax);
    gInterface.CarreChoixCouleur->rgb(1,0,0);
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
    gInterface.ZoneDessin->redraw();
}

void ChampModuleDeSortieCB(Fl_Widget* w, void* data){
    gDonnees.moduleMax = (int)gInterface.ChampModuleDeSortie->value();
    printf("ChampModuleDeSortieCB : %lf\n", gDonnees.moduleMax);
    gInterface.ZoneDessin->redraw();
}



void MenuFractaleCB(Fl_Widget* w, void* data){
}

void ChampXMinCB(Fl_Widget* w, void* data){
    real(gDonnees.ig) = (int)gInterface.ChampXMin->value();
    printf("ChampXMinCB : %lf\n", real(gDonnees.ig));
}

void ChampYMinCB(Fl_Widget* w, void* data){
    imag(gDonnees.ig) = (int)gInterface.ChampYMin->value();
    printf("ChampYMinCB : %lf\n", imag(gDonnees.ig));
}

void ChampLargeurCB(Fl_Widget* w, void* data){
    gDonnees.pasxy = ((double)gInterface.ChampLargeur->value())/L_ZONE;
    printf("ChampLargeurCB : %lf\n", gDonnees.pasxy*L_ZONE);

}



void Slider1CB(Fl_Widget* w, void* data){
    gTests.dessin=1;
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
    gInterface.ZoneDessin->redraw();

}

void Slider2CB(Fl_Widget* w, void* data){
        gTests.dessin=1;
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
    gInterface.ZoneDessin->redraw();

}


void Slider3CB(Fl_Widget* w, void* data){
         gTests.dessin=1;
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
    gInterface.ZoneDessin->redraw();
}

void CarreChoixCouleurCB(Fl_Widget* w, void* data){
    gTests.dessin=1;
    float r=255*gInterface.CarreChoixCouleur->r();
    float g=255*gInterface.CarreChoixCouleur->g();
    float b=255*gInterface.CarreChoixCouleur->b();
    if(gTests.slider==1){
        gDonnees.color1=255+256*(int)b+256*256*(int)g+256*256*256*(int)r;
        gInterface.Slider1->color(gDonnees.color1,gDonnees.color1);
        gInterface.Slider1->redraw();

    }
    if(gTests.slider==2){
        gDonnees.color2=255+256*(int)b+256*256*(int)g+256*256*256*(int)r;
        gInterface.Slider2->color(gDonnees.color2,gDonnees.color2);
        gInterface.Slider2->redraw();
    }
    if(gTests.slider==3){
        gDonnees.color3=255+256*(int)b+256*256*(int)g+256*256*256*(int)r;
        gInterface.Slider3->color(gDonnees.color3,gDonnees.color3);
        gInterface.Slider3->redraw();
    }
    gInterface.ZoneDessin->redraw();
}
