#ifndef _u4_fonctions_h
#define _u4_fonctions_h
#include <complex>

// Max d'étapes à vérifier
#define PROFONDEUR_MAX 10000
// Données utilisateurs initiales :
#define FRACT_INIT MANDELBROT
#define RANGMAX_INIT    250
#define MODULEMAX_INIT  2
#define C_INIT  (1,1)
#define IG_INIT (1,1)
#define SD_INIT (2,2)
// Taille du tableau, à ne pas modifier normalement :
#define HAUTEUR 400
#define LARGEUR 600

typedef std::complex<double> (*pointeurFct)(std::complex<double>, std::complex<double>);
    // Type d'une fonction qui renvoie un pointeur vers le type de fractale

enum fractype {
    MANDELBROT,
    JULIA,
    PERSONNA
};

// Structure de Pixel
struct Pixel {
    std::complex<double> z; // Coordonnées dans le plan std::complexe
    int n;  // rang de divergence
};

// Structure des paramètres utilisateur
struct Donnees {
    enum fractype Fractale;     // Type de fractales choisie (Type énuméré)
    int     rangMax;            // Rang maximal de convergence
    double  moduleMax;          // Module de convergence (détermination de la convergence on non de la fonction)
    std::complex<double> C;     // Constante de calcul
    std::complex<double> ig;    // Coordonnées du point inférieur gauche
    std::complex<double> sd;    // Coordonnées du point haut droit
    struct Pixel Tab[HAUTEUR][LARGEUR]; // Matrice des pixels de l'image.

    // Données de détermination des couleurs
    long    color1,     color2,     color3;
    int rangColor1, rangColor2, rangColor3;
};

void InitialiserDonnees() ;

//Prends en arg 2 long et ressort le dégradé sur N dans un tableau de taille[N][3]
void degradeRGB(long * A, long * B,int N, int tab[][3]);

int testFonction();

int convergence(std::complex<double> position, pointeurFct); // Donne un rang de convergence pour un point du plan complexe

pointeurFct retourne_fonction();    // Pointe vers les fonctions suivantes en fonction de la fractale choisie

std::complex<double> mandelbrot(std::complex<double> position, std::complex<double> z);
std::complex<double> julia     (std::complex<double> position, std::complex<double> z);
std::complex<double> personna  (std::complex<double> position, std::complex<double> z);


#endif
