#include "block.h"
#include "utils.h"
#include "vector.h"
#include "star.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <vector>
#include <cmath>
#include <time.h>
#include "SDL.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int main(int argc, char* argv[])
{


	// ------------------------- Paramètres de la simulation -------------------------

	double	area = 500.;				// Taille de la zone d'apparition des étoiles (en années lumière)
	double	galaxy_thickness = 0.05;	// Epaisseur de la galaxie (en "area")
	double	precision = 0.5;			// Précision du calcul de l'accélération (algorithme de Barnes-Hut)
	bool	verlet_integration = true;	// Utiliser l'intégration de Verlet au lieu de la méthode d'Euler

	int		stars_number = 30000;		// Nombre d'étoiles (Limité à 30 000 par les std::vector<>)
	double	initial_speed = 2500.;		// Vitesse initiale des d'étoiles (en mètres par seconde)
	double	black_hole_mass = 0.;		// Masse du trou noir (en masses solaires)
	bool	is_black_hole = false;		// Présence d'un trou noir

	View	view = default_view;		// Type de vue (default_view, xy, xz ou yz)
	double	zoom = 800.;				// Taille de "area" (en pixel)
	bool	real_colors = false;		// Activer la couleur réelle des étoiles
	bool	show_blocks = false;		// Afficher les blocs

	double	step = 200000.;				// Pas de temps de la simulation (en années)
	time_t	simulation_time = 3600;		// Temps de simulation (en seconde)



	// -------------------------------------------------------------------------------

	

	SDL_Init(SDL_INIT_VIDEO);

	window = NULL;
	renderer = NULL;

	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);
	SDL_SetWindowTitle(window, "Galaxy simulation");
	SDL_Event event;

	if (area < 0.1) area = 0.1;
	if (galaxy_thickness < 0.5) galaxy_thickness = 0.5;
	if (precision < 0.) precision = 0.;
	if (precision > 1.) precision = 1.;
	if (stars_number < 1.) stars_number = 1.;
	if (stars_number > 30000.) stars_number = 30000.;
	if (initial_speed < 0.) initial_speed = 0.;
	if (black_hole_mass < 0.) black_hole_mass = 0.;
	if (zoom < 1.) zoom = 1.;
	if (step < 0.) step = 0.;
	if (simulation_time < 1) simulation_time = 1;

	area *= LIGHT_YEAR;
	black_hole_mass *= SOLAR_MASS;
	step *= YEAR;

	std::vector<Star> galaxy;
	std::vector<Block> blocks;
	std::vector<Block> blocks_temp;
	galaxy.clear();
	blocks.clear();
	blocks_temp.clear();

	initialize_galaxy(galaxy, stars_number, area, initial_speed, step, is_black_hole, black_hole_mass, galaxy_thickness);

	time_t start = time(NULL);

	while (time(NULL) < start + simulation_time) // Boucle du pas de temps de la simulation
	{
		create_blocks(area, blocks, galaxy, blocks_temp);

		for (int i = 0; i < galaxy.size(); i++) // Boucle sur les étoiles de la galaxie
		{
			if (galaxy.at(i).is_alive)
			{
				galaxy.at(i).acceleration_and_density_maj(precision, galaxy, blocks);

				if (!(verlet_integration))
					galaxy.at(i).speed_maj(step, area);

				galaxy.at(i).position_maj(step, verlet_integration);

				if (!(real_colors))
					galaxy.at(i).color_maj();
			}

			// Affichage

			SDL_PollEvent(&event);
			if (event.type == SDL_QUIT)
			{
				SDL_Quit();
				exit(1);
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		draw_stars(galaxy, blocks.at(0).mass_center, area, zoom, view);

		if (show_blocks)
			draw_blocks(blocks, blocks.at(0).mass_center, area, zoom, view);

		SDL_RenderPresent(renderer);
	}

	if (renderer)
		SDL_DestroyRenderer(renderer);

	if (window)
		SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}
