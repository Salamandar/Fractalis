#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <api/inc/fmod.h>
#include <api/inc/fmod_errors.h>
#include "u1-interface.h"
#include "u4-fonctions.h"
using namespace std;
struct Donnees gDonnees;

void InitialiserDonnees() {
    gDonnees.Fractale = FRACT_INIT;
    gDonnees.N = N_INIT;
    gDonnees.Z = Z_INIT;
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




