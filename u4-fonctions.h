#ifndef _u4_fonctions_h
#define _u4_fonctions_h
#include <complex>
using namespace std;

// Max d'étapes à vérifier
#define PROFONDEUR_MAX 10000
// Données utilisateurs initiales :
#define FRACT_INIT MANDELBROT
#define RANGMAX_INIT    250
#define MODULEMAX_INIT  2
#define C_INIT  (1,1)
#define IG_INIT (1,1)
#define SD_INIT (2,2)
#define Couleur_Init 0
typedef complex<double> (*pointeurFct)(complex<double>, complex<double>);
    // Type d'une fonction qui renvoie un pointeur vers le type de fractale

enum fractype {
    MANDELBROT,
    JULIA,
    PERSONNA
};

// Structure de Pixel
struct Pixel {
    complex<double> z; // Coordonnées dans le plan std::complexe
    int n;  // rang de divergence
};

// Structure des paramètres utilisateur
struct Donnees {
    enum fractype Fractale;// Type de fractales choisie (Type énuméré)
    int     rangMax;       // Rang maximal de convergence
    double  moduleMax;     // Module de convergence (détermination de la convergence on non de la fonction)
    complex<double> C;     // Constante de calcul
    complex<double> ig;    // Coordonnées du point inférieur gauche
    complex<double> sd;    // Coordonnées du point haut droit
    struct Pixel Tab[H_ZONE][L_ZONE]; // Matrice des pixels de l'image.

    // Données de détermination des couleurs
    long    color1,     color2,     color3;
    int rangColor1, rangColor2, rangColor3;
};

void InitialiserDonnees() ;

//Prends en arg 2 long et ressort le dégradé sur N dans un tableau de taille[N][3]
void degradeRGB(long * A, long * B,int N, int tab[][3]);
void couleurs(long A, long B, long C, int N1, int N2, int N3);

void testFonction();

int convergence(complex<double> position, pointeurFct); // Donne un rang de convergence pour un point du plan complexe

pointeurFct retourne_fonction();    // Pointe vers les fonctions suivantes en fonction de la fractale choisie

complex<double> mandelbrot(complex<double> position, complex<double> z);
complex<double> julia     (complex<double> position, complex<double> z);
complex<double> personna  (complex<double> position, complex<double> z);


#endif
