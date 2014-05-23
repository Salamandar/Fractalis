#ifndef _u4_fonctions_h
#define _u4_fonctions_h

#include <complex>
// Max d'étapes à vérifier
#define PROFONDEUR_MAX 100
// Données utilisateurs initiales :
#define FRACT_INIT MANDELBROT
#define RANGMAX_INIT    50
#define MODULEMAX_INIT  2
#define C_INIT  (0.3, 0.5)
#define IG_INIT (-2.2,-1.5)
#define PASXY   0.005
#define COULEUR_INIT 0

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
    complex<double> z; // Coordonnées dans le plan std::complexe
    int n;  // rang de divergence
};

// Structure des paramètres utilisateur
struct Donnees {
    enum fractype Fractale; // Type de fractales choisie (Type énuméré)
    int     rangMax;        // Rang maximal de convergence
    double  moduleMax;      // Module de convergence (détermination de la convergence on non de la fonction)
    complex<double> C;      // Constante de calcul
    complex<double> ig;     // Coordonnées du point inférieur gauche
    double pasxy;           // Pas de la matrice (incrémentation, en fait, et égale dans les 2 dimensions, car pixels carrés)
                            // À changer pendant le zoom :)
    struct Pixel Tab[L_ZONE][H_ZONE]; // Matrice des pixels de l'image.
    // Données de détermination des couleurs
    unsigned long int    color1,     color2,     color3;
    int rangColor1, rangColor2, rangColor3;
    int hauteur;
};

struct Tests {
    bool dessin;
    bool calcul;
    bool calccouleurs;
    bool CB;
    int slider;
};
extern Donnees gDonnees;
extern Tests gTests;
void InitialiserDonnees() ;

    // Donne une correspondance entre coordonnées du tableau et coordonnées du plan complexe
void realFromTab(double *bi, double *bj);

pointeurFct retourne_fonction();    // Pointe vers les fonctions suivantes en fonction de la fractale choisie
 // Donnent un rang de convergence pour un point du plan complexe, pour chaque fonction.
int mandelbrot(complex<double> position);
int julia     (complex<double> position);
int sinzo     (complex<double> position);
int cosc      (complex<double> position);
int personna  (complex<double> position);

void convergenceLigne(int j, pointeurFct fonction);

//Prend en arg 2 unsigned long int et ressort le dégradé sur N dans un tableau de taille[N][3]
void degradeRGB(unsigned long int A, unsigned long int  B,int N, int tab[][3]);
void couleurs(unsigned long int A, unsigned long int B, unsigned long int C, int N1, int N2, int N3, unsigned long int tab[]);

//Enregistre une image de largeur Largeur au format PPM, dans un fichier Fichier en recalculant tout
void enregistrerPPM(int Largeur, char Fichier[32]);



#endif
