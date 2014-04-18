#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <api/inc/fmod.h>
#include <api/inc/fmod_errors.h>
#include "u1-interface.h"
#include "u4-fonctions.h"
using namespace std;

// Definition des donnees fonctionnelles du projet - structure globale de variables
struct Donnees gDonnees;

// Initialiser
void InitialiserDonnees()
{
    // On initialise le generateur de nombres aleatoires
    srand(time(NULL));
    // Initialisation de Rebond
    gDonnees.Rebond = 0 ;
    // On initialise Texte
    strcpy(gDonnees.Texte, "Texte ...") ;
    // On initialise Valeur
    gDonnees.Valeur = 0 ;
    // On initialise Parametre
    gDonnees.Parametre = 5 ;
    // on initialise Option1
    gDonnees.Option1 = 1 ;
    // On initialise Option2
    gDonnees.Option2 = 3 ;
    // On initialise Option3
    gDonnees.Option3 = 3 ;
    // On initialise la boule
    gDonnees.Boule.X = L_ZONE / 2 ;
    gDonnees.Boule.Y = L_ZONE / 2 ;
    gDonnees.Boule.VX = 5 ;
    gDonnees.Boule.VY = 3 ;

    // Exemple son
    JouerSon("media/starwars.mp3");
}

void DeplacerBouleSansRebond()
{
    // Nouvelle position de la boule ...
    gDonnees.Boule.X = gDonnees.Boule.X + gDonnees.Boule.VX ;
    gDonnees.Boule.Y = gDonnees.Boule.Y + gDonnees.Boule.VY ;

    // ... ramenee sur la sphere
    if ( gDonnees.Boule.X > L_ZONE )
        gDonnees.Boule.X = gDonnees.Boule.X - L_ZONE;

    if ( gDonnees.Boule.X < 0 )
        gDonnees.Boule.X = L_ZONE + gDonnees.Boule.X ;

    if ( gDonnees.Boule.Y > H_ZONE )
        gDonnees.Boule.Y = gDonnees.Boule.Y - gDonnees.Boule.Y;

    if ( gDonnees.Boule.Y < 0 )
        gDonnees.Boule.Y = H_ZONE + gDonnees.Boule.Y ;
}


void DeplacerBouleAvecRebonds()
{
    // Nouvelle position de la boule ...
    gDonnees.Boule.X = gDonnees.Boule.X + gDonnees.Boule.VX ;
    gDonnees.Boule.Y = gDonnees.Boule.Y + gDonnees.Boule.VY ;

    // Gestion des rebonds sur les bords du rectangle

    if ( gDonnees.Boule.X >= L_ZONE )
    {
        gDonnees.Boule.X = L_ZONE ;
        gDonnees.Boule.VX = -1 * gDonnees.Boule.VX ;
    }

    if ( gDonnees.Boule.Y >= H_ZONE )
    {
        gDonnees.Boule.Y = H_ZONE ;
        gDonnees.Boule.VY = -1 * gDonnees.Boule.VY ;
    }

    if ( gDonnees.Boule.X <= 0 )
    {
        gDonnees.Boule.X = 0 ;
        gDonnees.Boule.VX = -1 * gDonnees.Boule.VX ;
    }

    if ( gDonnees.Boule.Y <= 0 )
    {
        gDonnees.Boule.Y = 0 ;
        gDonnees.Boule.VY = -1 * gDonnees.Boule.VY ;
    }
}

// Utilitaires

// Joue le fichier son passe en parametre, mp3, etc...
void JouerSon(const char * FichierSon)
{
    // Musique de fond
    FMOD_SYSTEM      *system;
    FMOD_SOUND       *sound;
    FMOD_CHANNEL     *channel = 0;
    FMOD_RESULT       result;
    int               key;
    unsigned int      version;
    /*
        Create a System object and initialize.
    */
    result = FMOD_System_Create(&system);
    result = FMOD_System_GetVersion(system, &version);
    result = FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, NULL);
    result = FMOD_System_CreateSound(system, FichierSon, FMOD_SOFTWARE, 0, &sound);
    result = FMOD_Sound_SetMode(sound, FMOD_LOOP_OFF);
    result = FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sound, 0, &channel);
}

// Cette procedure permet une attente de x secondes, x peut etre en secondes mais aussi en flottant par exemple : 0.1 s
void Attente ( double Seconds )
{
    clock_t Endwait;
    Endwait = (int) (clock () + Seconds * CLOCKS_PER_SEC);
    while (clock() < Endwait);
}
