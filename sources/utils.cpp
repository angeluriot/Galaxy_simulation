#include "utils.h"
#include "block.h"



// Donne un int aléatoire entre deux bornes

int random_int(const int& min, const int& max)
{
	return rand() % (max - min) + min;
}



// Donne un double aléatoire entre deux bornes

double random_double(const double& min, const double& max)
{
	return (double(rand()) / double(RAND_MAX)) * (max - min) + min;
}



// Affiche les étoiles de la galaxie

void draw_stars(Star::range& alive_galaxy, const Vector& mass_center, const double& area, const double& zoom, View view)
{
	double x;
	double y;
	double z;
	Vector screen_position;
	Vector camera = Vector(0., area / 2., area / 2.);
	double  coef = 1. / (area / zoom);

	for (auto itStar = alive_galaxy.begin; itStar != alive_galaxy.end; ++itStar)
	{
		switch (view)
		{
		case default_view:

			x = (itStar->position - mass_center).x;
			y = (itStar->position - mass_center).y / 3. - (itStar->position - mass_center).z / 1.5;

			screen_position = create_spherical(Vector(x, y, 0.).get_radius() / (get_distance(itStar->position, camera)), Vector(x, y, 0.).get_phi(), Vector(x, y, 0.).get_theta());

			x = screen_position.x * zoom + WIDTH / 2.;
			y = screen_position.y * zoom + HEIGHT / 2.;
			break;

		case xy:

			x = (itStar->position - mass_center).x * coef + WIDTH / 2.;
			y = (itStar->position - mass_center).y * coef + HEIGHT / 2.;
			break;

		case xz:

			x = (itStar->position - mass_center).x * coef + WIDTH / 2.;
			y = (itStar->position - mass_center).z * coef + HEIGHT / 2.;
			break;

		case yz:

			x = (itStar->position - mass_center).y * coef + WIDTH / 2.;
			y = (itStar->position - mass_center).z * coef + HEIGHT / 2.;
			break;
		}

		SDL_SetRenderDrawColor(renderer, GetRValue(itStar->color), GetGValue(itStar->color), GetBValue(itStar->color), SDL_ALPHA_OPAQUE);

		SDL_RenderDrawPoint(renderer, x, y);

		SDL_SetRenderDrawColor(renderer, GetRValue(itStar->color), GetGValue(itStar->color), GetBValue(itStar->color), SDL_ALPHA_OPAQUE * 0.5);

		SDL_RenderDrawPoint(renderer, x - 1, y);
		SDL_RenderDrawPoint(renderer, x, y - 1);
		SDL_RenderDrawPoint(renderer, x, y + 1);
		SDL_RenderDrawPoint(renderer, x + 1, y);

		SDL_SetRenderDrawColor(renderer, GetRValue(itStar->color), GetGValue(itStar->color), GetBValue(itStar->color), SDL_ALPHA_OPAQUE * 0.25);

		SDL_RenderDrawPoint(renderer, x - 1, y - 1);
		SDL_RenderDrawPoint(renderer, x - 1, y + 1);
		SDL_RenderDrawPoint(renderer, x + 1, y - 1);
		SDL_RenderDrawPoint(renderer, x + 1, y + 1);
	}
}