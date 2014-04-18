#ifndef _u4_fonctions_h
#define _u4_fonctions_h
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
    complex z;  // Coordonnées dans le plan complexe
    int n;      // rang de divergence
};

enum fractype {
    MANDELBROT,
    JULIA
}


// Structure des paramètres utilisateur
struct Donnees {
    enum fractype F;    // Type de fractales choisie (Type énuméré)
    int N;              // Rang maximal de convergence
    int Z:              // Module de convergence (détermination de la convergence on non de la fonction)
    complex C;          // Constante de calcul
    complex ig;         // Coordonnées du point inférieur gauche
    complex sd;         // Coordonnées du point haut droit
    struct Pixel Tab[HAUTEUR][LARGEUR];     // Matrice des pixels de l'image.
};


extern struct Donnees gDonnees;

// Déclaration des sous-programmes
void InitialiserDonnees() ;


void JouerSon(const char *) ;
void Attente(double Seconds);

















#endif // _u4_fonctions_h
