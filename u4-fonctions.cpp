#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <api/inc/fmod.h>
#include <api/inc/fmod_errors.h>
#include <complex>
#include <iomanip>

#include "u1-interface.h"
#include "u4-fonctions.h"

struct Donnees gDonnees;

void InitialiserDonnees() {
    gDonnees.Fractale = FRACT_INIT;
    gDonnees.rangMax  = RANGMAX_INIT;
    gDonnees.moduleMax= MODULEMAX_INIT;
    gDonnees.C = C_INIT;
    gDonnees.ig= IG_INIT;
    gDonnees.sd= SD_INIT;
}

// Donne une correspondance entre coordonnées du tableau et coordonnées du plan complexe


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
std::complex<double> mandelbrot(std::complex<double> position, std::complex<double> z){
    return z*z + position;
}
std::complex<double> julia     (std::complex<double> position, std::complex<double> z){
    return position*position + z;
}
std::complex<double> personna  (std::complex<double> position, std::complex<double> z){
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
    pointeurFct fonction = retourne_fonction();
    for (int i = 0; i < H_ZONE; ++i)
        for (int j = 0; j < L_ZONE; ++j) {
            gDonnees.Tab[i][j].n=convergence(complex<double>(((double)j)/100,((double)i)/100), fonction);
}













// Cette procedure permet une attente de x secondes, x peut etre en secondes mais aussi en flottant par exemple : 0.1 s
//void Attente ( double Seconds ) {
 //   clock_t Endwait;
 //   Endwait = (int) (clock () + Seconds * CLOCKS_PER_SEC);
//   while (clock() < Endwait);
//}

void degradeRGB(long * A, long * B,int N, int tab[][3]){

    int i;
    *A=(*A-*A%256)/256;
    *B=(*B-*B%256)/256;
    tab[0][2]=*A % 256;
    *A=(*A-tab[0][2])/256;
    tab[0][1]=*A % 256;
    *A=(*A-tab[0][1])/256;
    tab[0][0]=*A%256;
    tab[N-1][2]=*B % 256;
    *B=(*B-tab[N-1][2])/256;
    tab[N-1][1]=*B % 256;
    *B=(*B-tab[N-1][2])/256;
    tab[N-1][0]=*B%256;

    //codage du dégradé dans un tableau de triplets RGB de N case tab[N][3], et oui, vive les cast
    double dr,dg,db;
    dr=((double)(tab[N-1][0]-tab[0][0]))/N;
    dg=((double)(tab[N-1][1]-tab[0][1]))/N;
    db=((double)(tab[N-1][2]-tab[0][2]))/N;

    for(i=0; i<N-1; i++)
	{
    tab[i][0]=tab[0][0]+i*dr;
        tab[i][1]=tab[0][1]+i*dg;
        tab[i][2]=tab[0][2]+i*db;
       //cout << tab[i][0] << ";" << tab[i][1] << ";" << tab[i][2] << endl;
    }
}

void couleurs(long A, long B, long C, int N1, int N2, int N3, long tab[])
{
    int i;
    int tab1[N1][3];
    int tab2[N2][3];
    int tab3[N3][3];
    int tab4[gDonnees.rangMax][3];
    degradeRGB(Couleur_Init,A,N1,tab1);
    degradeRGB(A,B,N2,tab2);
    degradeRGB(B,C,N3,tab3);
    degradeRGB(B,C,N3,tab4);

    for(i=0; i<N1; i++)
    {
        tab[i]=255+256*tab1[i][2]+256*256*tab1[i][1]+256*256*256*tab1[i][0];
    }
     for(i=N1; i<N2; i++)
    {
        tab[i]=255+256*tab2[i][2]+256*256*tab2[i][1]+256*256*256*tab2[i][0];
    }
     for(i=N2; i<N3
     ; i++)
    {
        tab[i]=255+256*tab3[i][2]+256*256*tab3[i][1]+256*256*256*tab3[i][0];
    }
    for(i=N3; i<gDonnees.rangMax; i++)
    {
        tab[i]=255+256*tab4[i][2]+256*256*tab4[i][1]+256*256*256*tab4[i][0];
    }
}
