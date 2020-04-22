#include "utils.h"
#include "block.h"



// Donne un int aléatoire entre deux bornes

int random_int(const int &min, const int &max) {
	return rand() % (max - min) + min;
}



// Donne un double aléatoire entre deux bornes

double random_double(const double &min, const double &max) {
	return (double(rand()) / double(RAND_MAX)) * (max - min) + min;
}



// Affiche les étoiles de la galaxie

void draw_stars(Star::range &alive_galaxy, const glm::dvec3 &mass_center, const double &area, const double &zoom, View view) {
	double x, y, z;
//	Vector screen_position;
	const double coef = 1. / (area / zoom);

	for (auto itStar = alive_galaxy.begin; itStar != alive_galaxy.end; ++itStar) {
		const auto tmp = itStar->position - mass_center;
		switch (view) {
			case default_view: { // Portée obligatoire : initialisation d'une variable à l'intérieur d'un case.
				x = tmp.x;
				y = tmp.y / 3. - tmp.z / 1.5;

				const glm::dvec3 camera(0., area * 0.5, area * 0.5);
				const auto screen_position = create_spherical(glm::length(glm::dvec3{ x, y, 0. }) / glm::distance(itStar->position, camera),
															  glm::get_phi(glm::dvec3{ x, y, 0. }),
															  glm::get_theta(glm::dvec3{ x, y, 0. }));

				x = screen_position.x * zoom + WIDTH * 0.5;
				y = screen_position.y * zoom + HEIGHT * 0.5;
			}
				break;

			case xy:

				x = tmp.x * coef + WIDTH * 0.5;
				y = tmp.y * coef + HEIGHT * 0.5;
				break;

			case xz:

				x = tmp.x * coef + WIDTH * 0.5;
				y = tmp.z * coef + HEIGHT * 0.5;
				break;

			case yz:

				x = tmp.y * coef + WIDTH * 0.5;
				y = tmp.z * coef + HEIGHT * 0.5;
				break;
		}
		{
			const int x_sdl = static_cast<int>(x), y_sdl = static_cast<int>(y);
			SDL_SetRenderDrawColor(renderer, itStar->color.r, itStar->color.g, itStar->color.b, SDL_ALPHA_OPAQUE);

			SDL_RenderDrawPoint(renderer, x_sdl, y_sdl);

			SDL_SetRenderDrawColor(renderer, itStar->color.r, itStar->color.g, itStar->color.b, SDL_ALPHA_OPAQUE * 0.5);

			SDL_RenderDrawPoint(renderer, x_sdl - 1, y_sdl);
			SDL_RenderDrawPoint(renderer, x_sdl, y_sdl - 1);
			SDL_RenderDrawPoint(renderer, x_sdl, y_sdl + 1);
			SDL_RenderDrawPoint(renderer, x_sdl + 1, y_sdl);

			SDL_SetRenderDrawColor(renderer, itStar->color.r, itStar->color.g, itStar->color.b, SDL_ALPHA_OPAQUE * 0.25);

			SDL_RenderDrawPoint(renderer, x_sdl - 1, y_sdl - 1);
			SDL_RenderDrawPoint(renderer, x_sdl - 1, y_sdl + 1);
			SDL_RenderDrawPoint(renderer, x_sdl + 1, y_sdl - 1);
			SDL_RenderDrawPoint(renderer, x_sdl + 1, y_sdl + 1);
		}
	}
}