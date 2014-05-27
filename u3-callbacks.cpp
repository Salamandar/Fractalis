#include <iostream>
#include <stdlib.h>
#include <FL/Fl.H>
#include <FL/fl_ask.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/fl_draw.H>
using namespace std;
#include "u1-interface.h"
#include "u2-dessin.h"
#include "u3-callbacks.h"
#include "u4-fonctions.h"

void ZoneDessinSourisCB( Fl_Widget* widget, void* data )
{
    // ATTENTION : X et Y ne sont pas relatifs a la zone mais a la fenetre qui la contient !!!!


    //Gestion du zoom cadre
    static int x1;
    static int y1;
    static int x2;
    static int y2;

    //Gestion du deplacement (clic gauche)
    static int deplX;
    static int deplY;
    int diffX, diffY;
    bool deplacement=false;


    switch(Fl::event_button())
    {
        int x,y;
    case 1:
        if(Fl::event()==FL_PUSH)    // Deplacement
        {
            deplX=Fl::event_x();// X_ZONE et Y_ZONE pas necessaires car on fait une difference
            deplY=Fl::event_y();
            printf("Mouse push,    x = %d, y = %d\n", deplX, deplY);
        }
        else if(Fl::event()==FL_RELEASE)
        {
            diffX=deplX-Fl::event_x();
            diffY=Fl::event_y()-deplY;
            real(gDonnees.ig)=real(gDonnees.ig)+diffX*gDonnees.pasxy;
            imag(gDonnees.ig)=imag(gDonnees.ig)+diffY*gDonnees.pasxy;
            printf("Deplacement de x = %d, y = %d\n", diffX, diffY);
            if (diffX!=0 && diffY!=0)
            {
                deplacement=true;
            }
        }
        break;

    case 2:
        if (Fl::event()==FL_PUSH)       // Definition de la constante C pour Julia et Cos+C
        {
            real(gDonnees.C)=real(gDonnees.ig)+(Fl::event_x()-X_ZONE)*gDonnees.pasxy;// Pas les bons calculs de coordonnees.
            imag(gDonnees.C)=imag(gDonnees.ig)+(Fl::event_y()-Y_ZONE)*gDonnees.pasxy;
            cout<<"C= : ("<<real(gDonnees.C)<<","<<imag(gDonnees.C)<<")"<<endl;
            deplacement=true;      // En fait il faudrait quand même redraw si Julia.
            gInterface.ChampCX->value(real(gDonnees.C));
            gInterface.ChampCY->value(real(gDonnees.C));
        }
        break;

    case 3:
        if(Fl::event()==FL_PUSH)    // Zoom avec cadrage ; prise des coordonnees initiales
        {
            printf("Mouse push = %i x = %i y = %i\n", Fl::event_button(), Fl::event_x(), Fl::event_y());
            x1=Fl::event_x()-X_ZONE;
            y1=Fl::event_y()-Y_ZONE;

        }
        if ( Fl::event_button3())//draw cadre
        {
            fl_draw_image(gDonnees.buffer,X_ZONE,Y_ZONE,L_ZONE,H_ZONE,3);
            x=Fl::event_x()-X_ZONE;
            y=Fl::event_y()-Y_ZONE;
            if(x<L_ZONE&&x>0)
            {

                if(y-y1>0)
                    y=y1+max((x-x1),(x1-x))*H_ZONE/L_ZONE;
                else
                    y=y1-max((x-x1),(x1-x))*H_ZONE/L_ZONE;
                if(y<Y_ZONE+H_ZONE&&y>0)
                {
                    tracerCadre(x1,y1+Y_ZONE,x,y+Y_ZONE);
                }
            }
        }

        // prise des coordonnees finales
        if(Fl::event()==FL_RELEASE)
        {
            printf("Mouse release = %i x = %i y = %i\n", Fl::event_button(), Fl::event_x(), Fl::event_y());
            x2=Fl::event_x()-X_ZONE;
            y2=Fl::event_y()-Y_ZONE;
            if(y2-y1>0)
            y2=y1+max((x2-x1),(x1-x2))*H_ZONE/L_ZONE;
            else
            y2=y1-max((x2-x1),(x1-x2))*H_ZONE/L_ZONE;
            // Recalcul du point ig
                real(gDonnees.ig)=real(gDonnees.ig)+min(x1, x2)*gDonnees.pasxy;

                imag(gDonnees.ig)=imag(gDonnees.ig)+(H_ZONE-max(y1,y2))*gDonnees.pasxy;
                // Modification du pas
                gDonnees.pasxy=gDonnees.pasxy*abs(x1-x2)/L_ZONE;

                deplacement=true;

        }
        break;

    default:
        break;
    }

    //Gestion du zoom roulette. Il faudra aussi modifier le point ig.
    int zoom=0;
    if(Fl::event() == FL_MOUSEWHEEL)
    {
        int s=Fl::event_x()-X_ZONE;
        int t=Fl::event_y()-Y_ZONE;
        zoom=Fl::event_dy();
        real(gDonnees.ig)=real(gDonnees.ig)-(gDonnees.pasxy*s*0.2*((double)(zoom)));
        imag(gDonnees.ig)=imag(gDonnees.ig)-(gDonnees.pasxy*(-t+H_ZONE)*0.2*((double)(zoom)));
        gDonnees.pasxy = gDonnees.pasxy*(1.+0.2*((double)(zoom)));
        cout <<gDonnees.pasxy<< endl;
        //cout << imag(gDonnees.ig)<< endl;
        gTests.calcul=true;
        gInterface.ZoneDessin->redraw();
    }


    if(deplacement)
    {
        gTests.calcul=1;
        gInterface.ChampLargeur->value(gDonnees.pasxy*H_ZONE);
        gInterface.ChampXMin->value(real(gDonnees.ig));
        gInterface.ChampYMin->value(imag(gDonnees.ig));
        gInterface.ZoneDessin->redraw();
    }
}



void BoutonQuitterCB(Fl_Widget* w, void* data)
{
    // Fin du programme
    exit(0);
}

void BoutonEnregistrerCB(Fl_Widget* w, void* data)
{
    const char* Saisie ; // et pas : char Saisie[80]
    int Entier=0 ;
    int Ok ;

    // Saisie de la valeur
    Ok = 0 ;
    Saisie = fl_input("Quelle resolution (largeur) ?", "" ) ;
    if ( Saisie != NULL )
        Ok = sscanf( Saisie, "%d", &Entier ) ;
    if (Entier!=0)
    {
    char* NomFichier ;  // et pas : char NomFichier[128]

    NomFichier = (char*) fl_file_chooser("Choisissez un fichier", "*.ppm", NULL);

    if ( NomFichier != NULL )
    {
        printf("BoutonChoisirFichierCB : Fichier choisi = %s\n", NomFichier);
    }
    else
    {
        printf("BoutonChoisirFichierCB : Aucun fichier choisi\n");
    }

        /*Saisie = fl_input("Nom du fichier ?", "" ) ;
        if ( Saisie != NULL )
            Ok = sscanf( Saisie, "%s", filename ) ;*/
        int err = enregistrerPPM(Entier,NomFichier);
        if(err==0){fl_message("Erreur lors de la creation/ouverture du fichier");}
        if(err==1){fl_message("Image enregistree dans %s",NomFichier);}

    }
}

void BoutonResetCB(Fl_Widget* w, void* data)
{
    // retour aux parametres initiaux
    InitialiserDonnees();
    gTests.calcul=1;
    gInterface.ZoneDessin->redraw();
    gInterface.Slider1->redraw();
}

void BoutonAideCB(Fl_Widget* w, void* data)
{
    fl_message(" Aide :\n Bouton gauche (maintient appui)->Deplacement\n Molette Souris : Zoom\n Appui molette : Definition de C a l'endroit du curseur \n Bouton droit (maintient appui) : Zoom cadre");
}

void BoutonSaveParamsCB(Fl_Widget* w, void* data)
{
    const char* Saisie = fl_input("Quel nouveau fichier de configuration ?", "" ) ;
    if (Saisie != NULL)
        enregistrerParams(Saisie);
}
void BoutonBackParamsCB(Fl_Widget* w, void* data)
{
    const char* Saisie = fl_input("Lire quel fichier de configuration ?", "" ) ;
    if (Saisie != NULL)
        restaurerParams(Saisie);
}

void ChampProfondeurCB(Fl_Widget* w, void* data)
{
    float temp=gDonnees.rangMax; //c'est pour reduire le rang des couleurs en mm temps
    gDonnees.rangMax = (int)gInterface.ChampProfondeur->value();
	gDonnees.slider[gDonnees.nbSlider+1][0]=COULEUR_INIT;
    gDonnees.slider[gDonnees.nbSlider+1][1]=gDonnees.rangMax;
    temp=temp/gDonnees.rangMax;
 	for (int i = 0; i < gDonnees.nbSlider; ++i)
    {
    gDonnees.slider[i+1][1]= gDonnees.slider[i+1][1]/temp;
    if (gDonnees.slider[i+1][1]==0)
    {
    	gDonnees.slider[i+1][1]=1;
    }
    //cout<<gDonnees.slider[i+1][1]<<"aaaze"<<endl;
	}
    gInterface.Slider1->scrollvalue(gDonnees.slider[1][1],0,1,gDonnees.rangMax-1);
    gInterface.Slider1->color(gDonnees.slider[1][0],gDonnees.slider[1][0]);
    gInterface.Slider2->scrollvalue(gDonnees.slider[2][1],0,1,gDonnees.rangMax-1);
    gInterface.Slider2->color(gDonnees.slider[2][0],gDonnees.slider[2][0]);
    gInterface.Slider3->scrollvalue(gDonnees.slider[3][1],0,1,gDonnees.rangMax-1);
    gInterface.Slider3->color(gDonnees.slider[3][0],gDonnees.slider[3][0]);
    gTests.calcul=1;
    gTests.calcul=1;
    gInterface.ZoneDessin->redraw();
}

void ChampModuleDeSortieCB(Fl_Widget* w, void* data)
{
    gDonnees.moduleMax = (int)gInterface.ChampModuleDeSortie->value();
    gTests.calcul=1;
    gInterface.ZoneDessin->redraw();
}



void MenuFractaleCB(Fl_Widget* w, void* data)
{
    int Fractale = (int)gInterface.MenuFractale->value() ;
    switch((int)gInterface.MenuFractale->value())
    {
    case 0:
        gDonnees.Fractale=MANDELBROT;
        break;
    case 1:
        gDonnees.Fractale=JULIA;
        break;
    case 2:
        gDonnees.Fractale=COSC;
        break;
    case 3:
        gDonnees.Fractale=SINZO;
        break;
    case 4:
        gDonnees.Fractale=PERSONNA;
        break;
    }
    gTests.calcul=1;
    gInterface.ZoneDessin->redraw();
}

void ChampXMinCB(Fl_Widget* w, void* data)
{
    real(gDonnees.ig) = gInterface.ChampXMin->value();
    gTests.calcul=1;
    gInterface.ZoneDessin->redraw();
}

void ChampYMinCB(Fl_Widget* w, void* data)
{
    imag(gDonnees.ig) = gInterface.ChampYMin->value();
    gTests.calcul=1;
    gInterface.ZoneDessin->redraw();
}

void ChampLargeurCB(Fl_Widget* w, void* data)
{
    gDonnees.pasxy = ((double)gInterface.ChampLargeur->value())/L_ZONE;
    gTests.calcul=1;
    gInterface.ZoneDessin->redraw();
}

void ChampCXCB(Fl_Widget* w, void* data)
{
    real(gDonnees.C) = gInterface.ChampCX->value();
    gTests.calcul=1;
    gInterface.ZoneDessin->redraw();
}

void ChampCYCB(Fl_Widget* w, void* data)
{
    imag(gDonnees.C) = gInterface.ChampCY->value();
    gTests.calcul=1;
    gInterface.ZoneDessin->redraw();
}

void Slider1CB(Fl_Widget* w, void* data)
{
    gTests.slider=1;
    gDonnees.slider[1][1]=(int)gInterface.Slider1->value();
    if(gDonnees.slider[1][1]>gDonnees.slider[2][1])
    {
        gDonnees.slider[2][1]=gDonnees.slider[1][1];
        gInterface.Slider2->value(gDonnees.slider[2][1]);
    }
    if(gDonnees.slider[1][1]>gDonnees.slider[3][1])
    {
        gDonnees.slider[3][1]=gDonnees.slider[1][1];
        gInterface.Slider3->value(gDonnees.slider[3][1]);
    }
    setColorChooserColor(gDonnees.slider[1][0]);
    gTests.calccouleurs=1;
    gInterface.ZoneDessin->redraw();
}

void Slider2CB(Fl_Widget* w, void* data)
{
    gTests.slider=2;
    gDonnees.slider[2][1]=(int)gInterface.Slider2->value();
    if(gDonnees.slider[1][1]>gDonnees.slider[2][1])
    {
        gDonnees.slider[1][1]=gDonnees.slider[2][1];
        gInterface.Slider1->value(gDonnees.slider[1][1]);
    }
    if(gDonnees.slider[2][1]>gDonnees.slider[3][1])
    {
        gDonnees.slider[3][1]=gDonnees.slider[2][1];
        gInterface.Slider3->value(gDonnees.slider[3][1]);
    }
    setColorChooserColor(gDonnees.slider[2][0]);
    gTests.calccouleurs=1;

    gInterface.ZoneDessin->redraw();
}


void Slider3CB(Fl_Widget* w, void* data)
{
    gTests.slider=3;
    gDonnees.slider[3][1]=(int)gInterface.Slider3->value();
    if(gDonnees.slider[1][1]>gDonnees.slider[3][1])
    {
        gDonnees.slider[1][1]=gDonnees.slider[3][1];
        gInterface.Slider1->value(gDonnees.slider[1][1]);
    }
    if(gDonnees.slider[2][1]>gDonnees.slider[3][1])
    {
        gDonnees.slider[2][1]=gDonnees.slider[3][1];
        gInterface.Slider2->value(gDonnees.slider[2][1]);
    }
    setColorChooserColor(gDonnees.slider[3][0]);
    gTests.calccouleurs=1;

    gInterface.ZoneDessin->redraw();
}

void CarreChoixCouleurCB(Fl_Widget* w, void* data)
{
    float r=255*gInterface.CarreChoixCouleur->r();
    float g=255*gInterface.CarreChoixCouleur->g();
    float b=255*gInterface.CarreChoixCouleur->b();

    switch(gTests.slider)
    {

    case 1:
        gDonnees.slider[1][0]=255+256*(int)b+256*256*(int)g+256*256*256*(int)r;
        gInterface.Slider1->color(gDonnees.slider[1][0],gDonnees.slider[1][0]);
        gInterface.Slider1->redraw();
        break;
    case 2:
        gDonnees.slider[2][0]=255+256*(int)b+256*256*(int)g+256*256*256*(int)r;
        gInterface.Slider2->color(gDonnees.slider[2][0],gDonnees.slider[2][0]);
        gInterface.Slider2->redraw();
        break;
    case 3:
        gDonnees.slider[3][0]=255+256*(int)b+256*256*(int)g+256*256*256*(int)r;
        gInterface.Slider3->color(gDonnees.slider[3][0],gDonnees.slider[3][0]);
        gInterface.Slider3->redraw();
        break;
    default:
        break;
    }
    gTests.calccouleurs=1;

    gInterface.ZoneDessin->redraw();
}




// Ne fonctionne pas correctement.

void setColorChooserColor(unsigned long int A)
{
    double R,G,B;
    A=(A-A%256)/256;
    B=A % 256;
    A=(A-B)/256;
    G=A % 256;
    A=(A-G)/256;
    R=A%256;

    gInterface.CarreChoixCouleur->rgb(R/255,G/255,B/255);
}
