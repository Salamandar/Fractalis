#ifndef _u4_fonctions_h
#define _u4_fonctions_h
#include <complex>

// Max d'étapes à vérifier
#define PROFONDEUR_MAX 10000
// Données utilisateurs initiales :
#define FRACT_INIT MANDELBROT
#define N_INIT  250
#define Z_INIT  1
#define C_INIT  (1,1)
#define IG_INIT (1,1)
#define SD_INIT (2,2)
// Taille du tableau, à ne pas modifier normalement :
#define HAUTEUR 100
#define LARGEUR 100

// Structure de Pixel
struct Pixel {
    std::complex<double> z;  // Coordonnées dans le plan std::complexe
    int n;      // rang de divergence
};

enum fractype {
    MANDELBROT,
    JULIA
};


// Structure des paramètres utilisateur
struct Donnees {
    enum fractype Fractale; // Type de fractales choisie (Type énuméré)
    int N;                  // Rang maximal de convergence
    int Z;                  // Module de convergence (détermination de la convergence on non de la fonction)
    std::complex<double> C;          // Constante de calcul
    std::complex<double> ig;         // Coordonnées du point inférieur gauche
    std::complex<double> sd;         // Coordonnées du point haut droit
    struct Pixel Tab[HAUTEUR][LARGEUR]; // Matrice des pixels de l'image.
};


extern struct Donnees gDonnees;

void InitialiserDonnees() ;


void Attente(double Seconds);


//int couleurN(int N);    // Sort une couleur à partir d'un N. Géré par Nils ?

int convergence(std::complex<double> position); // Donne un rang de convergence pour un point du plan complexe,
















#endif // _u4_fonctions_h
