#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <api/inc/fmod.h>
#include <api/inc/fmod_errors.h>
#include <complex>
using namespace std;

#include "u1-interface.h"
#include "u4-fonctions.h"

struct Donnees gDonnees;

// Donne un rang de convergence pour un point du plan complexe, à utiliser pour déterminer couleur d'affichage
int convergence(std::complex<double> position){
    pointeurFct fonction = retourne_fonction();
    int rangDivergence = -1;
    int i=0;
    std::complex<double> terme = position;
    while ((std::abs(terme = fonction(position,terme)))>gDonnees.moduleMax){
        i++;
    }
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


std::complex<double> mandelbrot(std::complex<double> positZero, std::complex<double> position){
    return position*position + gDonnees.C;
}
std::complex<double> julia     (std::complex<double> positZero, std::complex<double> position){
    return position*position + positZero;
}
std::complex<double> personna  (std::complex<double> constante, std::complex<double> position){
    return (0,0);
}
/*  À voir. Ce sera la fonction personnalisable, mais implémentée seulement quand TOUT le reste fonctionnera.
    J'aurai besoin de maîtriser le parsage de fonction mathématique, puis l'allocation dynamique de fonction.
    Ça sera extrêmement moche, donc si Nils a une idée elle est la bienvenue.
*/


// Fonctions de test.





void InitialiserDonnees() {
    gDonnees.Fractale = FRACT_INIT;
    gDonnees.rangMax  = RANGMAX_INIT;
    gDonnees.moduleMax= MODULEMAX_INIT;
    gDonnees.C = C_INIT;
    gDonnees.ig= IG_INIT;
    gDonnees.sd= SD_INIT;
}

// Cette procedure permet une attente de x secondes, x peut etre en secondes mais aussi en flottant par exemple : 0.1 s
void Attente ( double Seconds ) {
    clock_t Endwait;
    Endwait = (int) (clock () + Seconds * CLOCKS_PER_SEC);
    while (clock() < Endwait);
}

