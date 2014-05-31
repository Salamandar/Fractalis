#ifndef _u4_fonctions_h
#define _u4_fonctions_h

#include <complex>
// Max d'etapes a verifier
#define PROFONDEUR_MAX 100
// Donnees utilisateurs initiales :
#define FRACT_INIT MANDELBROT
#define RANGMAX_INIT    50
#define MODULEMAX_INIT  2
#define C_INIT  (0.3, 0.5)
#define IG_INIT (-2.2,-1.5)
#define PASXY   0.005
#define COULEUR_INIT 0
#define MAX_SLIDER 10

typedef int (*pointeurFct)(complex<double>);
    // Type d'une fonction qui renvoie un pointeur vers le type de fractale

enum fractype {
    MANDELBROT,
    JULIA,
    COSC,
    SINZO,
    PERSONNA
};

// Structure de Pixel
struct Pixel {
    complex<double> z; // Coordonnees dans le plan std::complexe
    int n;  // rang de divergence
};

// Structure des parametres utilisateur
struct Donnees {
    enum fractype Fractale; // Type de fractales choisie (Type enumere)
    int     rangMax;        // Rang maximal de convergence
    double  moduleMax;      // Module de convergence (determination de la convergence on non de la fonction)
    complex<double> C;      // Constante de calcul
    complex<double> ig;     // Coordonnees du point inferieur gauche
    double pasxy;           // Pas de la matrice (incrementation, en fait, et egale dans les 2 dimensions, car pixels carres)
                            // À changer pendant le zoom :)
    struct Pixel Tab[L_ZONE][H_ZONE]; // Matrice des pixels de l'image.
    // Donnees de determination des couleurs
    int hauteur;
    unsigned char buffer[3*L_ZONE*H_ZONE];
    unsigned char bufferDeg[3*325];
    int nbSlider;
    unsigned long int slider[MAX_SLIDER+2][2]; //contient le rang et la couleur de chaque slider
};

struct Tests {
    bool dessin;
    bool calcul;
    bool calccouleurs;
    bool animation;
    int slider;
};
extern Donnees gDonnees;
extern Tests gTests;
void InitialiserDonnees() ;

    // Donne une correspondance entre coordonnees du tableau et coordonnees du plan complexe
void realFromTab(double *bi, double *bj);

pointeurFct retourne_fonction();    // Pointe vers les fonctions suivantes en fonction de la fractale choisie
 // Donnent un rang de convergence pour un point du plan complexe, pour chaque fonction.
int mandelbrot(complex<double> position);
int julia     (complex<double> position);
int sinzo     (complex<double> position);
int cosc      (complex<double> position);
int personna  (complex<double> position);

void convergenceLigne(int j, pointeurFct fonction);

unsigned long int RgbToFlColor(int r, int g, int b);

int FlColorToRgb(unsigned long int color, int* r, int* g, int* b);

//Prend en arg 2 unsigned long int et ressort le degrade sur N dans un tableau de taille[N][3]
void degradeRGB(unsigned long int A, unsigned long int  B,int N, int tab[][3]);
//void couleurs(unsigned long int A, unsigned long int B, unsigned long int C, int N1, int N2, int N3, unsigned long int tab[]);
void couleursRGB(unsigned long tabSlider[][2],int tab[][3]) ;

//Enregistre une image de largeur Largeur au format PPM, dans un fichier Fichier en recalculant tout
int enregistrerPPM(int Largeur, char Fichier[32]);

int enregistrerParams(const char* fichier);
int restaurerParams(const char* fichier);

void calcBuffer(int tabdeg[][3]);
#endif
