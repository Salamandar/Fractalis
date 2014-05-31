#include <iostream>
#include <stdio.h>
using namespace std;
#include <FL/Fl.H>
#include "u1-interface.h"
#include "u4-fonctions.h"


struct Donnees gDonnees;
struct Tests gTests;

void InitialiserDonnees() {
    gDonnees.Fractale = FRACT_INIT;
    gDonnees.rangMax  = RANGMAX_INIT;
    gDonnees.moduleMax= MODULEMAX_INIT;
    gDonnees.C =complex<double>C_INIT;
    gDonnees.ig=complex<double>IG_INIT;
    gDonnees.pasxy= PASXY;
    gDonnees.slider[0][0]=COULEUR_INIT;
    gDonnees.slider[1][0]=0xFF000000;
    gDonnees.slider[2][0]=0x00FF0000;
    gDonnees.slider[3][0]=0x0000FF00;
    gDonnees.slider[0][1]=0;
    gDonnees.slider[1][1]=4;
    gDonnees.slider[2][1]=17;
    gDonnees.slider[3][1]=25;
    gDonnees.nbSlider=3;
    gDonnees.slider[gDonnees.nbSlider+1][0]=COULEUR_INIT;
    gDonnees.slider[gDonnees.nbSlider+1][1]=gDonnees.rangMax;
    gDonnees.hauteur=H_ZONE;



    //Init des tests
    gTests.slider=1;
    gTests.dessin=1;
    gTests.calcul=1;
    gTests.calccouleurs=1;

    //interface, je met la car ça bug quand j'include u4 fct dans u1 interface
    gInterface.MenuFractale->value(0);
    gInterface.ChampModuleDeSortie->value(gDonnees.moduleMax);
    gInterface.ChampProfondeur->value(gDonnees.rangMax);
    gInterface.ChampXMin->value(real(gDonnees.ig));
    gInterface.ChampYMin->value(imag(gDonnees.ig));
    gInterface.ChampLargeur->value(gDonnees.pasxy*L_ZONE);
    gInterface.Slider1->scrollvalue(gDonnees.slider[1][1],0,1,gDonnees.rangMax-1);
    gInterface.Slider1->color(gDonnees.slider[1][0],gDonnees.slider[1][0]);
    gInterface.Slider2->scrollvalue(gDonnees.slider[2][1],0,1,gDonnees.rangMax-1);
    gInterface.Slider2->color(gDonnees.slider[2][0],gDonnees.slider[2][0]);
    gInterface.Slider3->scrollvalue(gDonnees.slider[3][1],0,1,gDonnees.rangMax-1);
    gInterface.Slider3->color(gDonnees.slider[3][0],gDonnees.slider[3][0]);

}

// Pointe vers les fonctions suivantes en fonction de la fractale choisie
pointeurFct retourne_fonction() {
    switch(gDonnees.Fractale){
        case MANDELBROT: return mandelbrot;
            break;
        case JULIA: return julia;
            break;
        case SINZO: return sinzo;
            break;
        case COSC: return cosc;
            break;
        case PERSONNA: return personna;
            break;
    }
}
int mandelbrot(std::complex<double> position){
    int rang=1;
    complex<double> Zrang=position;
    do {
        Zrang=Zrang*Zrang + position;
        rang++;
    } while (std::abs(Zrang) < gDonnees.moduleMax && rang<gDonnees.rangMax);
    return rang==gDonnees.rangMax ? -1 : rang;      // Operation ternaire
}
int julia(complex<double> position) {
    int rang=0;
    complex<double> Zrang=position;
    do {
        Zrang=Zrang*Zrang + gDonnees.C;
        rang++;
    } while (std::abs(Zrang) < gDonnees.moduleMax && rang<gDonnees.rangMax);
    return rang==gDonnees.rangMax ? -1 : rang;      // Operation ternaire
}
int sinzo     (complex<double> position){
    int rang=0;
    complex<double> Zrang=position;
    do {
        Zrang=sin(Zrang) + position;
        rang++;
    } while (std::abs(Zrang) < gDonnees.moduleMax && rang<gDonnees.rangMax);
    return rang==gDonnees.rangMax ? -1 : rang;      // Operation ternaire
}
int cosc      (complex<double> position){
    int rang=0;
    complex<double> Zrang=position;
    do {
        Zrang=cos(Zrang) + gDonnees.C;
        rang++;
    } while (std::abs(Zrang) < gDonnees.moduleMax && rang<gDonnees.rangMax);
    return rang==gDonnees.rangMax ? -1 : rang;      // Operation ternaire
}
int personna(complex<double> position) {
    return 0;//(0,0);
    /*  À voir. Ce sera la fonction personnalisable, mais implementee seulement quand TOUT le reste fonctionnera.
        J'aurai besoin de maîtriser le parsage de fonction mathematique, puis l'allocation dynamique de fonction.
        Ça sera extrêmement moche, donc si Nils a une idee elle est la bienvenue.
    */
}

// Calcul d'indices de convergence pour une ligne. L_ZONE a virer.
void convergenceLigne(int j, pointeurFct fonction){
    double pas=gDonnees.pasxy;
    complex<double> position= gDonnees.ig;
    imag(position)+=(H_ZONE-j)*pas;
    for (int i = 0; i < L_ZONE; ++i) {// Boucle ligne par ligne
        gDonnees.Tab[i][j].n=fonction(position);
        position+=pas;
    }
}


// À compléter s'il te plait Nils vu que tu t'occupes des couleurs. Tu peux changer la forme des fonctions pour les
// utiliser dans ton code, ce serait plus clair/évolué/propre ;)


unsigned long int RGBtoFlColor(int r, int g, int b){

}
int FlColorToRgb(unsigned long int color, int* r, int* g, int* b){
    
}


void degradeRGB(unsigned long int A, unsigned long int B, int N, int tab[][3]) {
    //cout<<"A"<<A<<" B"<<B<<" N "<<N<<endl;
    A=(A-A%256)/256;
    B=(B-B%256)/256;
        tab[0][2]=A % 256;
        tab[N-1][2]=B % 256;
    A=(A-tab[0][2])/256;
    B=(B-tab[N-1][2])/256;
        tab[0][1]=A % 256;
        tab[N-1][1]=B % 256;
    A=(A-tab[0][1])/256;
    B=(B-tab[N-1][1])/256;
        tab[0][0]=A%256;
        tab[N-1][0]=B%256;

    // codage du degrade dans un tableau de triplets RGB de N case tab[N][3], et oui, vive les cast
    // C'est ça qui sera donc a changer pour avoir une interpolation de couleurs plus "belle"
    double dr,dg,db;
    dr=((double)(tab[N-1][0]-tab[0][0]))/N;
    dg=((double)(tab[N-1][1]-tab[0][1]))/N;
    db=((double)(tab[N-1][2]-tab[0][2]))/N;

    for(int i=0; i<N; i++) {
        tab[i][0]=tab[0][0]+i*dr;
        tab[i][1]=tab[0][1]+i*dg;
        tab[i][2]=tab[0][2]+i*db;
      // cout << tab[i][0] << ";" << tab[i][1] << ";" << tab[i][2] << endl;
    }
}

/*void couleurs(unsigned long int A, unsigned long int B, unsigned long int C, int N1, int N2, int N3, unsigned long int tab[]) {
    //cout<<"calculcouleurs"<<endl;
    unsigned long int I=COULEUR_INIT;
    int tab1[N1][3];
    int tab2[N2][3];
    int tab3[N3][3];
    int tab4[gDonnees.rangMax-N3][3];
    degradeRGB(I,A,N1,tab1);
    degradeRGB(A,B,N2-N1,tab2);
    degradeRGB(B,C,N3-N2,tab3);
    degradeRGB(C,I,gDonnees.rangMax-N3,tab4);

    tab[0]=0;
    for(int i=1; i<N1; i++) {
        tab[i]=255+256*tab1[i   ][2]+256*256*tab1[i   ][1]+256*256*256*tab1[i   ][0];
    }
    for(int i=N1; i<N2; i++) {
        tab[i]=255+256*tab2[i-N1][2]+256*256*tab2[i-N1][1]+256*256*256*tab2[i-N1][0];
    }
    for(int i=N2; i<N3 ; i++) {
        tab[i]=255+256*tab3[i-N2][2]+256*256*tab3[i-N2][1]+256*256*256*tab3[i-N2][0];
        //cout<<tab[i]<<";"<<i<<endl;
    }
    for(int i=N3; i<gDonnees.rangMax; i++) {
        tab[i]=255+256*tab4[i-N3][2]+256*256*tab4[i-N3][1]+256*256*256*tab4[i-N3][0];
    }
    //cout<<gDonnees.rangMax;
}*/
void couleursRGB(unsigned long tabSlider[][2], int tab[][3]) {
    unsigned long int I=COULEUR_INIT;
    for (int i = 0; i < 50; ++i) {
        for (int j = 0; j < 3; ++j) {
            tab[i][j]=0;
        }
    }
    for (int i = 0; i < gDonnees.nbSlider+1; ++i) {
       // printf("degradé entre le slider %d et %d, de rangs %d et %d, rang max=%d\n",i,i+1,tabSlider[i][1],tabSlider[i+1][1],gDonnees.rangMax);
        degradeRGB(tabSlider[i][0],tabSlider[i+1][0],tabSlider[i+1][1]-tabSlider[i][1],&tab[tabSlider[i][1]]);
        //degradeRGB(tabSlider[i][0],tabSlider[i+1][0],0,&tab[tabSlider[i][1]]);
        //cout <<i<<"=1 ;"<< tabSlider[i][0] << "=tabSlider i 0;" << tab[i+1][0] << "=tabSlider i+1 0;" << tabSlider[i+1][1] - tabSlider[i][1] <<"=diff tab"<< endl;
        //printf("ecriture de la case %lu a la case %lu\n",tabSlider[i][1],tabSlider[i+1][1]);
    }

    for (int i = 0; i < gDonnees.rangMax; ++i) {
          //     cout <<i<<";"<< tab[i][0] << ";" << tab[i][1] << ";" << tab[i][2] << endl;
    }
}


int enregistrerPPM(int Largeur, char Fichier[32]){
    FILE* pFile;
    pFile = fopen(Fichier,"w");
    if (pFile==NULL){return 0;};
    fprintf(pFile,"P3\n%d %d\n255\n",Largeur,Largeur*H_ZONE/L_ZONE);

    pointeurFct fonction = retourne_fonction(); // Determine la fonction
    int hauteur=Largeur*H_ZONE/L_ZONE;
    double pas=gDonnees.pasxy/Largeur*(gDonnees.hauteur*L_ZONE/H_ZONE);
    double x_ini=real(gDonnees.ig);
    double y_ini=imag(gDonnees.ig);
    complex<double>coord_init=gDonnees.ig;
    complex<double>pas_complx=(0,pas);
    complex<double>coordonnees=coord_init;
    int tab[gDonnees.rangMax][3];
    couleursRGB(gDonnees.slider,tab);
    //coordonnees=coord_init+(double)j*pas_complx;
    for (int j = 0; j < hauteur; j++) {
        coordonnees=complex<double>(x_ini,y_ini+j*pas);
        for(int i = 0; i<Largeur;i++){
            int rang=fonction(coordonnees);
            coordonnees+=pas_complx;


            if (rang==-1 )
                fprintf(pFile, "0 0 0 ");
            else{

                fprintf(pFile,"%d %d %d ",tab[rang][0],tab[rang][1],tab[rang][2]);
            }
        }
    }
    fclose(pFile);
    return(1);
}

void calcBuffer(int tabdeg[][3]){
    for (int i = 0; i < 325; i++) {
        for (int j = 0; j < 3; ++j) {
            gDonnees.bufferDeg[3*i+j]=tabdeg[(i*gDonnees.rangMax/325)][j];
        }
    }
}


int enregistrerParams(const char* fichier){
    FILE* fichierEcriture=fopen(fichier, "wt");

    if (fichierEcriture==NULL)
        return 1;

    int r=0, g=0, b=0;

    fprintf(fichierEcriture, "FractalisFile\n");
    fprintf(fichierEcriture, "Fractale… : %d\n", gDonnees.Fractale);
    fprintf(fichierEcriture, "RangMaxCo : %d\n", gDonnees.rangMax);
    fprintf(fichierEcriture, "ModuleMax : %lf\n", gDonnees.moduleMax);
    fprintf(fichierEcriture, "Constante : %lf+i*%lf\n", real(gDonnees.C ), imag(gDonnees.C ));
    fprintf(fichierEcriture, "PtInfGauc : %lf+i*%lf\n", real(gDonnees.ig), imag(gDonnees.ig));
    fprintf(fichierEcriture, "PasAffXY… : %lf\n", gDonnees.pasxy);
    fprintf(fichierEcriture, "Hauteur…… : %d\n", gDonnees.hauteur);
    fprintf(fichierEcriture, "NbSliders : %d\n", gDonnees.nbSlider);

    for (int i = 1; i < MAX_SLIDER+1; ++i) {
        FlColorToRgb(gDonnees.slider[i][2], &r, &g, &b); //===================================================================
        fprintf(fichierEcriture, "Couleur%d… : %d %d %d\n", i, r, g, b);
        fprintf(fichierEcriture, "RangCoul%d : %d\n", i, gDonnees.slider[i][1]);
    }
    fclose(fichierEcriture);
}


int restaurerParams(const char* fichier){
	int ligne=1, err;
    int tempInt;
    char code_err[15], deux_points[3], fileTitle[100];
    double tempFloat1, tempFloat2;
    unsigned long int tempCouleur;

    FILE* fichierLecture=fopen(fichier, "rt");
    if (fichierLecture==NULL)
        return -1;

    err=fscanf(fichierLecture, "%s\n",fileTitle);
    if (err!=1&&fileTitle!="FractalisFile")
        return ligne; 

    ligne++;
    err=fscanf(fichierLecture, "%s %s %d\n",code_err, deux_points, &tempInt);
    if (err!=3&&code_err!="Fractale…"&&deux_points!=":")
        return ligne;
    else
        gDonnees.Fractale=(fractype)tempInt;

    ligne++;
    err=fscanf(fichierLecture, "%s %s %d\n",code_err, deux_points, &tempInt);
    if (err!=3&&code_err!="RangMaxCo"&&deux_points!=":")
        return ligne;
    else
        gDonnees.rangMax=tempInt;

    ligne++;
    err=fscanf(fichierLecture, "%s %s %lf\n",code_err, deux_points, &tempFloat1);
    if (err!=3&&code_err!="ModuleMax"&&deux_points!=":")
        return ligne;
    else
        gDonnees.moduleMax=tempFloat1;

    // Lecture de complexes…

    ligne++;
    err=fscanf(fichierLecture, "%s %s %lf+i*%lf\n", code_err, deux_points, &tempFloat1, &tempFloat2);
    if (err!=4&&code_err!="Constante"&&deux_points!=":")
        return ligne;
    else
        gDonnees.C=complex<double>(tempFloat1,tempFloat2);

    ligne++;
    err=fscanf(fichierLecture, "%s %s %lf+i*%lf\n", code_err, deux_points, &tempFloat1, &tempFloat2);
    if (err!=4&&code_err!="PtInfGauc"&&deux_points!=":")
        return ligne;
    else
        gDonnees.ig=complex<double>(tempFloat1,tempFloat2);

    ligne++;
    err=fscanf(fichierLecture, "%s %s %lf\n", code_err, deux_points, &tempFloat1);
    if (err!=3&&code_err!="PasAffXY…"&&deux_points!=":")
        return ligne;
    else
        gDonnees.pasxy=tempFloat1;

    ligne++;
    err=fscanf(fichierLecture, "%s %s %d\n", code_err, deux_points, &tempInt);
    if (err!=3&&code_err!="Hauteur……"&&deux_points!=":")
        return ligne;
    else
        gDonnees.hauteur=tempInt;

    ligne++;
    err=fscanf(fichierLecture, "%s %s %d\n", code_err, deux_points, &tempInt);
    if (err!=3&&code_err!="NbSliders"&&deux_points!=":")
        return ligne;
    else
        gDonnees.nbSlider=tempInt;

    int j, r, g, b;
    for (int i = 1; i < MAX_SLIDER+1; ++i) {
    	ligne++;
        err=fscanf(fichierLecture, "Couleur%d… %s %d %d %d\n", &j, deux_points, &r, &g, &b);
        if (err!=5&&j!=i&&deux_points!=":")
        	return ligne;
        else
            //gDonnees.slider[i][2]=RGBtoFlColor(r, g, b); ========================================================================

        ligne++;
        err=fscanf(fichierLecture, "RangCoul%d %s %d\n", &j, deux_points, &tempInt);
        if (err!=3&&j!=i&&deux_points!=":"){
            return ligne;
            }
        else
            gDonnees.slider[i][1]=tempInt;
    }
    
    fclose(fichierLecture);


    //Init des tests
    gTests.dessin=1;
    gTests.calcul=1;
    gTests.calccouleurs=1;
    gTests.slider=1;

    //interface, je met la car ça bug quand j'include u4 fct dans u1 interface
    gInterface.MenuFractale->value(gDonnees.Fractale);
    gInterface.ChampModuleDeSortie->value(gDonnees.moduleMax);
    gInterface.ChampProfondeur->value(gDonnees.rangMax);
    gInterface.ChampXMin->value(real(gDonnees.ig));
    gInterface.ChampYMin->value(imag(gDonnees.ig));
    gInterface.ChampLargeur->value(gDonnees.pasxy*L_ZONE);
    gInterface.ChampCX->value(real(gDonnees.C));
    gInterface.ChampCY->value(imag(gDonnees.C));

    gInterface.ChoixSlider->value(gDonnees.nbSlider);
    gInterface.Slider1->scrollvalue(gDonnees.slider[1][1],0,1,gDonnees.rangMax-1);
    gInterface.Slider1->color(gDonnees.slider[1][0],gDonnees.slider[1][0]);
    gInterface.Slider2->scrollvalue(gDonnees.slider[2][1],0,1,gDonnees.rangMax-1);
    gInterface.Slider2->color(gDonnees.slider[2][0],gDonnees.slider[2][0]);
    gInterface.Slider3->scrollvalue(gDonnees.slider[3][1],0,1,gDonnees.rangMax-1);
    gInterface.Slider3->color(gDonnees.slider[gDonnees.nbSlider][0],gDonnees.slider[gDonnees.nbSlider][0]);    

    gInterface.Fenetre->redraw();
}


//fl_rgb_color(uchar r, uchar g, uchar b);
