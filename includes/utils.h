#ifndef UTILS_H
#define UTILS_H
#include "Star.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <vector>
#include <cmath>
#include "SDL.h"

#define LIGHT_YEAR	(9.461 * pow(10, 15))	// Année lumière (en mètres)
#define PI			3.14159265				// Pi
#define G			0.00000000006674		// Constante gravitationnelle (en newton mètre carré par kilogramme carré)
#define HEIGHT		1080.					// Hauteur de la fenêtre (en pixels)
#define WIDTH		1920.					// Largeur de la fenêtre (en pixels)
#define SOLAR_MASS	(1.989 * pow(10, 30))	// Masse solaire (en kilogrammes)
#define YEAR		31536000.				// Année (en secondes)

enum View { default_view, xy, xz, yz };		// Vues possibles de la simulation

extern SDL_Renderer* renderer;

int random_int(const int& min, const int& max);
double random_double(const double& min, const double& max);
void draw_stars(std::vector<Star>& galaxy, const Vector& mass_center, const double& area, const double& zoom, const View& view);
void draw_blocks(const std::vector<Block>& blocks, const Vector& mass_center, const double& area, const double& zoom, const View& view);

#endif