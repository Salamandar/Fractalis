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
     static int x2;
     static int y1;
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
          //recadrage de l'image
        if(x1<x2){
            real(gDonnees.ig)=real(gDonnees.ig)+(x1)*gDonnees.pasxy;
            }
        else {
            real(gDonnees.ig)=real(gDonnees.ig)+(x2)*gDonnees.pasxy;
            }
        if (y1>y2){
            imag(gDonnees.ig)=imag(gDonnees.ig)+(H_ZONE-y1)*gDonnees.pasxy;
            }
        else {
            imag(gDonnees.ig)=imag(gDonnees.ig)+(H_ZONE-y2)*gDonnees.pasxy;
            }

            //modification du pas
        if(x1<x2){
          gDonnees.pasxy=gDonnees.pasxy*(x2-x1)/L_ZONE;
        }
        else{
            gDonnees.pasxy=gDonnees.pasxy*(x1-x2)/L_ZONE;
        }


        gInterface.ZoneDessin->redraw();
    }


    //Gestion du zoom roulette
    int zoom=0;
    if(Fl::event() == FL_MOUSEWHEEL){
        int s=Fl::event_x();
        int t=Fl::event_y();
        double realFixe =gDonnees.pasxy*s;
        double imagFixe =gDonnees.pasxy*t;
        zoom=Fl::event_dy();
        real(gDonnees.ig)=real(gDonnees.ig)-(gDonnees.pasxy*s*0.2*((double)(zoom)));
        imag(gDonnees.ig)=imag(gDonnees.ig)-(gDonnees.pasxy*(H_ZONE+t)*0.2*((double)(zoom)));
        gDonnees.pasxy = gDonnees.pasxy*(1.+0.2*((double)(zoom)));
        cout <<real(gDonnees.ig)<< endl;
        cout << imag(gDonnees.ig)<< endl;
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
    // retour au parametre initiales
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


    if(Fractale==0){
        gDonnees.Fractale=MANDELBROT;
        }
    if (Fractale==1){
        gDonnees.Fractale=JULIA;
    }

    if (Fractale==2){
        gDonnees.Fractale=JULIA;
    }
        gInterface.ZoneDessin->redraw();

}

void ChampXMinCB(Fl_Widget* w, void* data){
    real(gDonnees.ig) = gInterface.ChampXMin->value();
    printf("ChampXMinCB : %lf\n", real(gDonnees.ig));
    gInterface.ZoneDessin->redraw();

}

void ChampYMinCB(Fl_Widget* w, void* data){
    imag(gDonnees.ig) = gInterface.ChampYMin->value();
    printf("ChampYMinCB : %lf\n", imag(gDonnees.ig));
    gInterface.ZoneDessin->redraw();

}

void ChampLargeurCB(Fl_Widget* w, void* data){
    gDonnees.pasxy = ((double)gInterface.ChampLargeur->value())/L_ZONE;
    printf("ChampLargeurCB : %lf\n", gDonnees.pasxy*L_ZONE);
    gInterface.ZoneDessin->redraw();


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
