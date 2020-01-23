#ifndef UTILS_H
#define UTILS_H
#include "SDL.h"
#include "star.h"

template <typename float_t>

constexpr float_t const_pow(float_t x, int y)
{
	float_t res = x;
	for (int i = 1; i < y; i++)
		res *= x;
	return res;
}

class Block;

constexpr double LIGHT_YEAR = (9.461 * const_pow<double>(10, 15));	// Année lumière (en mètres)
constexpr double PI = 3.14159265;									// Pi
constexpr double G = 0.00000000006674;								// Constante gravitationnelle (en newton mètre carré par kilogramme carré)
constexpr double HEIGHT = 1080.;									// Hauteur de la fenêtre (en pixels)
constexpr double WIDTH = 1920.;										// Largeur de la fenêtre (en pixels)
constexpr double SOLAR_MASS = (1.989 * const_pow<double>(10, 30));	// Masse solaire (en kilogrammes)
constexpr double YEAR = 31536000.;									// Année (en secondes)

enum View { default_view, xy, xz, yz }; // Vues possibles de la simulation

extern SDL_Renderer* renderer;

int random_int(const int& min, const int& max);
double random_double(const double& min, const double& max);
void draw_stars(Star::range& alive_galaxy, const Vector& mass_center, const double& area, const double& zoom, View view);

#endif