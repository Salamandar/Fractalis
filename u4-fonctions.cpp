#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <api/inc/fmod.h>
#include <api/inc/fmod_errors.h>
#include <complex.h>
#include "u1-interface.h"
#include "u4-fonctions.h"
using namespace std;

// Definition des donnees fonctionnelles du projet - structure globale de variables
struct Donnees gDonnees;

// Initialiser
void InitialiserDonnees() {
    gDonnees.fractype = FRACT_INIT;
    gDonnees.N = N_INIT;
    gDonnees.Z = Z_INIT;
    gDonnees.C = C_INIT;
    gDonnees.ig= IG_INIT;
    gDonnees.sd= SD_INIT;
}


// Utilitaires

void JouerSon(const char * FichierSon) {
    FMOD_SYSTEM      *system;
    FMOD_SOUND       *sound;
    FMOD_CHANNEL     *channel = 0;
    FMOD_RESULT       result;
    int               key;
    unsigned int      version;

    result = FMOD_System_Create(&system);
    result = FMOD_System_GetVersion(system, &version);
    result = FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, NULL);
    result = FMOD_System_CreateSound(system, FichierSon, FMOD_SOFTWARE, 0, &sound);
    result = FMOD_Sound_SetMode(sound, FMOD_LOOP_OFF);
    result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound, 0, &channel);
}

// Cette procedure permet une attente de x secondes, x peut etre en secondes mais aussi en flottant par exemple : 0.1 s
void Attente ( double Seconds ) {
    clock_t Endwait;
    Endwait = (int) (clock () + Seconds * CLOCKS_PER_SEC);
    while (clock() < Endwait);
}
