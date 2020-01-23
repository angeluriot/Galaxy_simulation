#include "star.h"
#include "vector.h"
#include "utils.h"
#include "block.h"
#include <time.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

struct MutexRange {
	Star::range part;
	std::atomic<int> ready = 0;
};

template <size_t N>

void make_partitions(std::array<MutexRange, N>& mutparts, Star::range alive_galaxy, size_t total)
{
	const size_t nPerPart = total / N;
	auto currentIt = alive_galaxy.begin, prevIt = alive_galaxy.begin;
	for (size_t i = 0; i < N - 1; ++i)
	{
		for (size_t iIt = 0; iIt < nPerPart; ++iIt, ++currentIt);

		mutparts[i].part = { prevIt, currentIt };
		mutparts[i].ready = 1;

		prevIt = currentIt;
	}
	mutparts.back().part = { currentIt, alive_galaxy.end };
	mutparts.back().ready = 1;
}

int main(int argc, char* argv[])
{


	// ------------------------- Paramètres de la simulation -------------------------

	double	area = 1000.;				// Taille de la zone d'apparition des étoiles (en années lumière)
	double	galaxy_thickness = 0.05;	// Epaisseur de la galaxie (en "area")
	double	precision = 1.;				// Précision du calcul de l'accélération (algorithme de Barnes-Hut)
	bool	verlet_integration = true;	// Utiliser l'intégration de Verlet au lieu de la méthode d'Euler

	int		stars_number = 50000;		// Nombre d'étoiles
	double	initial_speed = 9000.;		// Vitesse initiale des d'étoiles (en mètres par seconde)
	double	black_hole_mass = 0.;		// Masse du trou noir (en masses solaires)
	bool	is_black_hole = false;		// Présence d'un trou noir

	View	view = xy;					// Type de vue (default_view, xy, xz ou yz)
	double	zoom = 800.;				// Taille de "area" (en pixel)
	bool	real_colors = false;		// Activer la couleur réelle des étoiles
	bool	show_blocks = false;		// Afficher les blocs

	double	step = 100000.;				// Pas de temps de la simulation (en années)
	time_t	simulation_time = 3600;		// Temps de simulation (en seconde)



	// -------------------------------------------------------------------------------



	SDL_Init(SDL_INIT_VIDEO);

	window = NULL;
	renderer = NULL;

	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetWindowTitle(window, "Galaxy simulation");
	SDL_Event event;
	constexpr size_t nThread = 4;

	if (area < 0.1) area = 0.1;
	if (galaxy_thickness > 1.) galaxy_thickness = 1.;
	if (precision < 0.) precision = 0.;
	if (stars_number < 1.) stars_number = 1.;
	if (initial_speed < 0.) initial_speed = 0.;
	if (black_hole_mass < 0.) black_hole_mass = 0.;
	if (zoom < 1.) zoom = 1.;
	if (step < 0.) step = 0.;
	if (simulation_time < 1) simulation_time = 1;

	area *= LIGHT_YEAR;
	step *= YEAR;

	Star::container galaxy;
	Block block;

	double total_mass = stars_number * (0.764 * ((0.08 + 0.45) / 2.) + 0.121 * ((0.45 + 0.8) / 2.) + 0.076 * ((0.8 + 1.04) / 2.) + 0.030 * ((1.04 + 1.4) / 2.) + 0.006 * ((1.4 + 2.1) / 2.) + 0.0013 * ((2.1 + 16) / 2.) + is_black_hole * black_hole_mass) * SOLAR_MASS;

	initialize_galaxy(galaxy, stars_number, area, initial_speed, step, is_black_hole, black_hole_mass, galaxy_thickness, total_mass);

	Star::range alive_galaxy = { galaxy.begin(), galaxy.end() };
	float step2 = step * step;
	double currentStep = static_cast<double>(1.);
	bool stopThreads = false;

	auto updateStars = [&block, precision, verlet_integration, step, area, real_colors, &stopThreads, &currentStep](MutexRange* mutpart)
	{
		using namespace std::chrono_literals;

		while (mutpart->ready != 1)
			std::this_thread::sleep_for(2ms);

		while (!stopThreads)
		{
			for (auto itStar = mutpart->part.begin; itStar != mutpart->part.end; ++itStar) // Boucle sur les étoiles de la galaxie
			{
				itStar->update_acceleration_and_density(precision, block);

				if (!(verlet_integration))
					itStar->update_speed(step * currentStep, area);

				itStar->update_position(step * currentStep, verlet_integration);

				if (!is_in(block, *itStar))
					itStar->is_alive = false;

				else if (!(real_colors))
					itStar->update_color();
			}

			mutpart->ready = 2;

			while (mutpart->ready != 1 && !stopThreads)
				std::this_thread::sleep_for(2ms);
		}
	};

	std::array<std::thread, nThread> mythreads;
	std::array<MutexRange, nThread> mutparts;

	for (int i = 0; i < mythreads.size(); ++i)
	{
		mutparts[i].ready = 0;
		mythreads[i] = std::thread(updateStars, &mutparts[i]);
	}

	auto totalGalaxy = std::distance(alive_galaxy.begin, alive_galaxy.end);
	auto t0 = std::chrono::steady_clock::now();

	while (true) // Boucle du pas de temps de la simulation
	{
		using namespace std::chrono_literals;
		create_blocks(area, block, alive_galaxy);

		make_partitions<nThread >(mutparts, alive_galaxy, totalGalaxy);
		for (auto& mp : mutparts)
			while (mp.ready != 2)
				std::this_thread::sleep_for(1ms);
		{
			auto prevEnd = alive_galaxy.end;
			alive_galaxy.end = std::partition(alive_galaxy.begin, alive_galaxy.end, [](const Star& star) { return star.is_alive; });
			totalGalaxy -= std::distance(alive_galaxy.end, prevEnd);
		}

		SDL_PollEvent(&event);

		if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
			break;

		
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);

		draw_stars(alive_galaxy, block.mass_center, area, zoom, view);

		SDL_RenderPresent(renderer);
		SDL_GL_SwapWindow(window);

		auto t1 = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::ratio<1, 60>> duree = t1 - t0;
		t0 = t1;
		currentStep = duree.count();
	}

	stopThreads = true;

	for (auto& thr : mythreads)
		thr.join();

	if (renderer)
		SDL_DestroyRenderer(renderer);

	if (window)
		SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}