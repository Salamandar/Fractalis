#ifndef _u4_fonctions_h
#define _u4_fonctions_h
#define DUREE_CYCLE 0.015    // 0.500 secondes, depend du materiel utilise
#define RAYON_BOULE  20

struct Boule {
    int X;
    int Y;
    int VX;
    int VY;
} ;

// Structure globale pour les variables fonctionnelles
struct Donnees {
    struct Boule    Boule ;

    int             Rebond ;
    char            Texte[80] ;
    unsigned int    Valeur ;
    int             Parametre ;
    int             Option1 ;
    int             Option2 ;
    int             Option3 ;
};

extern struct Donnees gDonnees;

// Déclaration des sous-programmes
void InitialiserDonnees() ;
void DeplacerBouleSansRebond() ;
void DeplacerBouleAvecRebonds() ;

void JouerSon(const char *) ;
void Attente(double Seconds);

#endif // _u4_fonctions_h
