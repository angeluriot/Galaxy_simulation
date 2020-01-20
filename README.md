# Galaxy simulation

![release](https://img.shields.io/badge/release-v2.3-blueviolet)
![language](https://img.shields.io/badge/language-C%2B%2B-0052cf)
![library](https://img.shields.io/badge/library-SDL2-00cf2c)
![size](https://img.shields.io/badge/size-76%20Mo-f12222)
![license](https://img.shields.io/badge/license-CC--0-0bb9ec)

<br/>

Ce dépôt contient le code source d'une simulation de type n-body utilisant l'algorithme de Barnes-Hut pour l'optimisation, elle 
est spécifiquement conçue pour la modélisation de galaxies.

<br/>

<p align="center">
    <img src="https://i.imgur.com/yTRdyJa.png" width="700">
</p>

<br/>

# Utilisation

Vous trouverez dans le fichier [main.cpp](https://github.com/angeluriot/Galaxy_simulation/blob/master/sources/main.cpp) le morceau 
de code permettant de modifier les différents paramètres de la simulation :

```cpp
// ------------------------- Paramètres de la simulation -------------------------

double  area = 500.;                // Taille de la zone d'apparition des étoiles (en années lumière)
double  galaxy_thickness = 0.05;    // Epaisseur de la galaxie (en "area")
double  precision = 0.5;            // Précision du calcul de l'accélération (algorithme de Barnes–Hut)
bool    verlet_integration = true;  // Utiliser l'intégration de Verlet au lieu de la méthode d'Euler

int     stars_number = 30000;       // Nombre d'étoiles (Limité à 30 000 par les std::vector<>)
double  initial_speed = 2500.;      // Vitesse initiale des d'étoiles (en mètres par seconde)
double  black_hole_mass = 0.;       // Masse du trou noir (en masses solaires)
bool    is_black_hole = false;      // Présence d'un trou noir

View    view = default_view;        // Type de vue
double  zoom = 800.;                // Taille de "area" (en pixel)
double  real_colors = false;        // Activer la couleur réelle des étoiles
bool    show_blocks = false;        // Afficher les blocs

double  step = 200000.;             // Pas de temps de la simulation (en années)
time_t  simulation_time = 3600;     // Temps de simulation (en seconde)

// -------------------------------------------------------------------------------
```

<br/>

# Installation

&nbsp; • &nbsp; Si vous possédez déjà le compilateur **MinGW** et de quoi utiliser un Makefile
sur Windows, il vous suffit de télécharger l'intégralité du dépôt et de faire la commande **`make`** dans le répertoire correspondant.

<br/>

&nbsp; • &nbsp; Si ce n'est pas le cas, cliquez sur l'aide dont vous avez besoin :

&nbsp; &nbsp; &nbsp; - &nbsp; [Mode d'emploi pour installer **MinGW**.](#installer-mingw)

&nbsp; &nbsp; &nbsp; - &nbsp; [Mode d'emploi pour utiliser **`make`**.](#utiliser-make)

<br/>

## Installer MinGW

Dans un premier temps, téléchargez l'installeur de **MinGW** en utilisant ce lien :&nbsp; [[télécharger MinGW]](http://www.mediafire.com/file/zeac28nmd3rh03m/mingw-get-setup.exe/file)

<br/>

En ouvrant l'installeur, vous devriez avoir cette fenêtre :

<br/>

<p align="center">
    <img src="https://i.imgur.com/jMztODh.png" width="400">
</p>

<br/>

<br/>

Cliquez sur **Install**, puis, après avoir choisi le répertoire d'installation, copiez le chemin, ce sera utile pour la suite :

<br/>

<p align="center">
<img src="https://i.imgur.com/bhKNOqt.png" width="400">
</p>

<br/>

<br/>

Après avoir fini l'installation, la fenêtre **MinGW Installation Manager** va se lancer *(si ce n'est pas le cas, ouvrez-là avec la 
recherche Windows)*, cliquez ensuite sur **All Packages** en haut à gauche :

<br/>

<p align="center">
<img src="https://i.imgur.com/qvcvS4C.png" width="300">
</p>

<br/>

<br/>




