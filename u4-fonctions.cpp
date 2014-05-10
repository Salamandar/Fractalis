#include <iostream>
#include <string.h>
#include <api/inc/fmod.h>
#include <api/inc/fmod_errors.h>
#include <complex>
#include <stdio.h>
#include "u1-interface.h"
#include "u4-fonctions.h"

struct Donnees gDonnees;

void InitialiserDonnees() {
    gDonnees.Fractale = FRACT_INIT;
    gDonnees.rangMax  = RANGMAX_INIT;
    gDonnees.moduleMax= MODULEMAX_INIT;
    gDonnees.C = C_INIT;
    gDonnees.ig=complex<double>IG_INIT;
    gDonnees.pasxy= PASXY;
    gDonnees.color1=0xFF000000;
    gDonnees.color2=0x00FF0000;
    gDonnees.color3=0x0000FF00;
    gDonnees.rangColor1=10;
    gDonnees.rangColor2=10;
    gDonnees.rangColor3=10;
    gDonnees.hauteur=H_ZONE;
}

// Pointe vers les fonctions suivantes en fonction de la fractale choisie
pointeurFct retourne_fonction() {
    switch(gDonnees.Fractale){
        case MANDELBROT:
            return mandelbrot;
            break;
        case JULIA:
            return julia;
            break;
        case PERSONNA:
            return personna;
            break;
    }
}
complex<double> mandelbrot(std::complex<double> position, complex<double> z){
    return z*z + position;
}
complex<double> julia     (std::complex<double> position, complex<double> z){
    return position*position + z;
}
complex<double> personna  (std::complex<double> position, complex<double> z){
    return (0,0);
    /*  À voir. Ce sera la fonction personnalisable, mais implémentée seulement quand TOUT le reste fonctionnera.
        J'aurai besoin de maîtriser le parsage de fonction mathématique, puis l'allocation dynamique de fonction.
        Ça sera extrêmement moche, donc si Nils a une idée elle est la bienvenue.
    */
}

// Donne un rang de convergence pour un point du plan complexe, à utiliser pour déterminer couleur d'affichage
int convergence(complex<double> position, pointeurFct fonction){
    int rang=0;
    complex<double> Zrang(0.,0.);
    do {
        Zrang=fonction(position,Zrang);
        rang++;
    } while (std::abs(Zrang) < gDonnees.moduleMax && rang<gDonnees.rangMax);
    if (rang==gDonnees.rangMax)
        return -1;
    else
        return rang;
}

// Calcule et enregistre tous les rangs de convergence dans le tableau
void convergencePlan(){
    pointeurFct fonction = retourne_fonction(); // Détermine la fonction
    for (int j = 0; j < gDonnees.hauteur; ++j)
        convergenceLigne(fonction, j);
}

void convergenceLigne(pointeurFct fonction, int j){
    double pas=gDonnees.pasxy;
    complex<double> position= gDonnees.ig + complex<double>(0,(double)j*pas);
    for (int i = 0; i < L_ZONE; ++i) {      // Boucle ligne par ligne
        gDonnees.Tab[i][j].n=convergence(position, fonction);
        position+=pas;
    }
}




// Cette procedure permet une attente de x secondes, x peut etre en secondes mais aussi en flottant par exemple : 0.1 s
//void Attente ( double Seconds ) {
 //   clock_t Endwait;
 //   Endwait = (int) (clock () + Seconds * CLOCKS_PER_SEC);
//   while (clock() < Endwait);
//}

void degradeRGB(unsigned long int A, unsigned long int B, int N, int tab[][3]) {
    int i;
    A=(A-A%256)/256;
    B=(B-B%256)/256;
    tab[0][2]=A % 256;
    A=(A-tab[0][2])/256;
    tab[0][1]=A % 256;
    A=(A-tab[0][1])/256;
    tab[0][0]=A%256;
    tab[N-1][2]=B % 256;
    B=(B-tab[N-1][2])/256;
    tab[N-1][1]=B % 256;
    B=(B-tab[N-1][1])/256;
    tab[N-1][0]=B%256;

    //codage du dégradé dans un tableau de triplets RGB de N case tab[N][3], et oui, vive les cast
    double dr,dg,db;
    dr=((double)(tab[N-1][0]-tab[0][0]))/N;
    dg=((double)(tab[N-1][1]-tab[0][1]))/N;
    db=((double)(tab[N-1][2]-tab[0][2]))/N;

    for(i=0; i<N; i++) {
        tab[i][0]=tab[0][0]+i*dr;
        tab[i][1]=tab[0][1]+i*dg;
        tab[i][2]=tab[0][2]+i*db;
       //cout << tab[i][0] << ";" << tab[i][1] << ";" << tab[i][2] << endl;
    }
}

void couleurs(unsigned long int A, unsigned long int B, unsigned long int C, int N1, int N2, int N3, unsigned long int tab[]) {
    int i;
    unsigned long int I=Couleur_Init;
    int tab1[N1][3];
    int tab2[N2][3];
    int tab3[N3][3];
    int tab4[gDonnees.rangMax-N3][3];
    degradeRGB(I,A,N1,tab1);
    degradeRGB(A,B,N2,tab2);
    degradeRGB(B,C,N3,tab3);
    degradeRGB(C,I,gDonnees.rangMax-N1-N2-N3,tab4);

    tab[0]=0;
    for(i=1; i<N1; i++) {
        tab[i]=255+256*tab1[i][2]+256*256*tab1[i][1]+256*256*256*tab1[i][0];
    }
     for(i=N1; i<N1+N2; i++) {
        tab[i]=255+256*tab2[i-N1][2]+256*256*tab2[i-N1][1]+256*256*256*tab2[i-N1][0];
    }
     for(i=N1+N2; i<N3+N1+N2 ; i++) {
        tab[i]=255+256*tab3[i-N2-N1][2]+256*256*tab3[i-N2-N1][1]+256*256*256*tab3[i-N2-N1][0];
        //cout<<tab[i]<<";"<<i<<endl;
    }
    for(i=N3+N2+N1; i<gDonnees.rangMax; i++) {
        tab[i]=255+256*tab4[i-N3-N2-N1][2]+256*256*tab4[i-N3-N2-N1][1]+256*256*256*tab4[i-N3-N2-N1][0];
    }
    //cout<<gDonnees.rangMax;
}

void enregistrerPPM(int Largeur, char Fichier[32]){
    FILE* ptrFichier;
    ptrFichier=fopen(Fichier,"w");
    if(ptrFichier=NULL){cout<<"impossible d'acceder au fichier";}

    fprintf(ptrFichier,"P3\n%d %d\n256\n",Largeur,Largeur*H_ZONE/L_ZONE);



    pointeurFct fonction = retourne_fonction(); // Détermine la fonction
    double pas=gDonnees.pasxy*Largeur/gDonnees.hauteur*L_ZONE/H_ZONE;
    double x_ini=real(gDonnees.ig);
    double y_ini=imag(gDonnees.ig);
    complex<double>coord_init=gDonnees.ig;
    complex<double>pas_complx=(0,gDonnees.pasxy);
    complex<double>coordonnees=coord_init;

    int tempHauteur=gDonnees.hauteur;
    gDonnees.hauteur=Largeur*H_ZONE/L_ZONE;
    unsigned long int tab[gDonnees.rangMax];
    couleurs(gDonnees.color1,gDonnees.color2,gDonnees.color3,gDonnees.rangColor1,gDonnees.rangColor2,gDonnees.rangColor3,tab);
    	for (int j = 0; j < gDonnees.hauteur; ++j) {
        convergenceLigne(fonction,j);
        coordonnees=complex<double>(x_ini,y_ini+j*pas);
        //coordonnees=coord_init+(double)j*pas_complx;
        	for (int i = 0; i < L_ZONE; ++i) {
            if (gDonnees.Tab[i][j].n==-1 )
                {fprintf(ptrFichier, "0 0 0 ");}
            else{}
        	}
    	}
}

