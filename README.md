Fractalis
=========

Visionneur de fractales, développé dans le cadre du BE d'informatique de Phelma.

Contributeurs :

> Julia Dupuis

> Nils Exibard

> Félix Piédallu


Caractéristiques futures
----------------
* Modélisation de fractales de Mandelbrot et d'ensembles de Julia.

* Représentation de fractales issues de plusieurs fonctions complexes :
 * ``F(z)=z²+C``
 * ``F(z)=cos(z)×C``
 * ``F(z)=sin(z)×z_0``
 * ``F(z)=z²+z_0``

* Paramètres d'affichage modifiables :
 * Zoom
 * Déplacement
 * Profondeur de calcul
 * Constance C

* Gestion des couleurs (Réglage par 8 points d'un dégradé)

* Sauvegarde de la configuration (xml ?), et de l'image :
 * Dans un premier temps, au format PPM
 * Ensuite, si possible, PNG.

Liens utiles
-----

Documentation PPM : http://netpbm.sourceforge.net/doc/ppm.html

Structure des données fonctionnelles
-----

### Définition des données fonctionnelles dans ``u4-fonctions.h``
Constantes :

```c
// Paramètres par défaut
# define PROFONDEUR_MAX
# define POINT_I_G
# define POINT_S_D
# define CONSTANTE
```

Variables :
```c
// Structure globale pour les variables fonctionnelles
struct Donnees_Image
{
    int X; //coordonnées dans le plan complexe
    int Y;
    int n;//rang de divergence
};
// Structure paramètres utilisateur
{
    int F; // fractale choisie
    int N; //profondeur
    int Z: // module de convergence (détermination de la convergence on non de la fonction)
    complex c; // constante de calcul
    complex ig; //point inferieur gauche
    complex sd; //point haut droit
}
```


Structure des données de l’interface graphique
---------

###Esquisse de l’interface : Définition des données de l’interface graphique dans ``u2-fonctions.h`` :

```c
// Declaration des objets de l'interface
struct Interface {
    Fl_Double_Window*Fenetre ;// Fenetre du projet
    DrawingArea* ZoneDessin ;// Zone de dessin
    Fl_Button* BoutonQuitter ;// Quitter le programme
    Fl_Button* BoutonEnregistrer ;// Enregistrer l'image
    Fl_Button* BoutonReset ;// Revenir aux paramères par défaut
    Fl_Value_Input*ModuleDeSortie ;// Module de sortie
    Fl_Value_Input*Profondeur ;// Profondeur 
    Fl_Choice* TypeFractale ; // Type de fractale
    Fl_Button* BoutonQuitter ;// Quitter le programme
} ;
```

Définition des callbacks associées aux objets de l’interface dans u3-fonctions.h
// Prototypes des callbacks
void CurseurTailleCB( Fl_Widget* w, void* data ) ;
void CurseurDensiteCB( Fl_Widget* w, void* data ) ;
void CurseurResineuxCB( Fl_Widget* w, void* data ) ;
void CurseurForceVentCB( Fl_Widget* w, void* data ) ;
void BoutonRadioVentCB( Fl_Widget* w, void* data ) ;
void CurseurForceVentCB( Fl_Widget* w, void* data ) ;
void CurseurNbCycleFeuCB( Fl_Widget* w, void* data ) ;
void ChampNbFeuCB( Fl_Widget* w, void* data ) ;
void BoutonFeuCB( Fl_Widget* w, void* data ) ;
void BoutonPauseCB( Fl_Widget* w, void* data ) ;
void BoutonQuitterCB( Fl_Widget* w, void* data ) ;
void BoutonResetCB( Fl_Widget* w, void* data ) ;