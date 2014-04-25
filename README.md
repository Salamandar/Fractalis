Projet Fractales
======

Visionneur de fractales, développé dans le cadre du BE d'informatique de Phelma.

Contributeurs :

> Julia Dupuis

> Nils Exibard

> Félix Piédallu

## 1. Structure des données fonctionnelles

### Définition des données fonctionnelles dans ``u4-fonctions.h``
```c++
// Profondeur max à vérifier (Maximum du réglage utilisateur)
#define PROFONDEUR_MAX 10000
// Données utilisateurs initiales :
    // Type de fractale initiale (au lancement du logiciel)
#define FRACT_INIT MANDELBROT
    // Rang de convergence
#define RANGMAX_INIT    250
    // Module maximal de convergence
#define MODULEMAX_INIT  2
    // Constante de calcul initiale
#define C_INIT  (1,1)
    //Position initiale de la fenêtre sur le plan complexe
#define IG_INIT (1,1)
#define SD_INIT (2,2)
    // Taille du tableau, à ne pas modifier normalement : (=Taille de la fenêtre d'affichage en pixels)
#define HAUTEUR 400
#define LARGEUR 600

    // Type de fractale initiale (au lancement du logiciel)
typedef std::complex<double> (*pointeurFct)(std::complex<double>, std::complex<double>);

    // Type énuméré définissant les fractales possibles
enum fractype {
    MANDELBROT,
    JULIA,
    PERSONNA
};

    // Structure de Pixels contenus dans un tableau
struct Pixel {
    std::complex<double> z; // Coordonnées dans le plan std::complexe
    int n;  // rang de divergence
};

    // Structure des paramètres utilisateur
struct Donnees {
    enum fractype Fractale;     // Type de fractales choisie
    int     rangMax;            // Rang de convergence
    double  moduleMax;          // Module de convergence (détermination de la convergence on non de la fonction)
    std::complex<double> C;     // Constante de calcul
    std::complex<double> ig;    // Coordonnées du point inférieur gauche
    std::complex<double> sd;    // Coordonnées du point haut droit
    struct Pixel Tab[HAUTEUR][LARGEUR]; // Matrice des pixels de l'image.
};
```

## 2. Structure des données de l’interface graphique

### Esquisse de l’interface :
![alt tag](https://raw.github.com/salamandar/Fractalis/master/interface.png)

### Définition des données de l’interface graphique dans ``u2-fonctions.h``

```c++
// Declaration des objets de l'interface
struct Interface {
    Fl_Double_Window*Fenetre;       // Fenêtre du projet
    DrawingArea* ZoneDessin;        // Zone de dessin
    Fl_Button* BoutonQuitter;       // Quitter le programme
    Fl_Button* BoutonEnregistrer;   // Enregistrer l'image
    Fl_Button* BoutonSauvePosition; // Enregistrer les paramètres actuels
    Fl_Button* BoutonReset;         // Revenir aux paramères par défaut
    Fl_Value_Input*ModuleDeSortie;  // Module de sortie
    Fl_Value_Input*Profondeur;      // Profondeur
    Fl_Choice* TypeFractale;        // Type de fractale
    Fl_Button*ZoomPlus;             // Zoomer
    Fl_Button*ZoomMoins;            // Dézoomer
};
```

### Définition des callbacks associées aux objets de l’interface dans ``u3-fonctions.h``
```c++
    // Prototypes des callbacks
void ModuleDeSortieCB   (Fl_Widget* w, void* data);
void ProfondeurCB       (Fl_Widget* w, void* data);
void FractaleCB         (Fl_Widget* w, void* data);
void BoutonQuitterCB    (Fl_Widget* w, void* data);
void BoutonEnregistrerCB(Fl_Widget* w, void* data);

    // On peut utiliser de préférence la souris, sinon :
void BoutonZoomPlusCB   (Fl_Widget* w, void* data);
void BoutonZoomMoinsCB  (Fl_Widget* w, void* data);
```

## 3. Fonctions de calcul et d'affichage, définies dans ``u4-fonctions.cpp``
```c++
void Initialiser ();
    // Inialiser l'interface avec un premier affichage avec les paramètres par défaut

void Affichage();
    // Affiche la fractale dans la zone de dessin

void calcule(struct Donnee);
    // Calcule la fractale et retourne les profondeurs.

CalculeCouleurs(struct Donnee);

    // Initialisation des données, effectué au démarrage du programme ou au reset des paramètres
void InitialiserDonnees() ;

    //int couleurN(int N);    // Sort une couleur à partir d'un N. Géré par Nils ?

    // Fonction de test, utilisée pour tester sans l'affichage des paramètres sensibles
int testFonction();

    // Pointe vers la fonction fractale utilisée. Permet de gérer plus facilement les différents types.
pointeurFct retourne_fonction();

    // Donne un rang de convergence pour un point du plan complexe et une fonction
int convergence(std::complex<double> position, pointeurFct);

    // Fonctions fractales, prenant en entrée la position de calcul et le terme Zn de calcul de convergence
std::complex<double> mandelbrot(std::complex<double> position, std::complex<double> z);
std::complex<double> julia     (std::complex<double> position, std::complex<double> z);
std::complex<double> personna  (std::complex<double> position, std::complex<double> z);

    // Fonctions de conversion Position dans le tableau -- Position sur le plan complexe
    // (Demande des pointeurs car 2 valeurs à ressortir)
void tableauFromComplex(std::complex<double> position, int* x, int* y);

std::complex<double> position complexFromTableau(int x, int y);

```

##4. Directions :

*Dans un premier temps*, il s'agira de déveloper un projet assez simple, permettant d'afficher les quatre types de fractale définies dans le sujet.
Le travail sur la couleur sera effectué uniquement entre deux couleurs choisies par l'utilisateur.
Nous réaliserons également un zoom basique et un enregistrement au fomat PPM de l'image, ainsi que des paramètres choisis dans un fichier texte.
L'interface devra être complète et attractive pour l'utilisateur .


*Dans un second temps*, nous pourrons ajouter des fonctionnalités avancées, telles que :

* Zoom plus efficace (upscaling puis recalcul)
* Bon système de couleurs, avec points de contrôle et fonction d'interpolation non linéaire (quadratique,…)
* Changement progressif de couleur (animation)
* Meilleure qualité d'enregistrement d'images (meilleure que l'affichage)
* Fractales 3D
* Interface plus conviviale (changement de couleur graphique si possible,…)
* Enregistrement des paramètres dans un fichier texte. (Zooms et positions actuelles)
* Fonction éditable par l'utilisateur


Répartition des taches :
> Nils :gestion des couleurs

> Félix : Fonctions et définitions

> Julia : Interface et Callbacks


