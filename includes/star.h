#ifndef STAR_H
#define STAR_H
#include "vector.h"
#include <Windows.h>

class Block;



// Classe définissant une étoile

class Star
{

public:

	using container = std::list<Star>;

	struct range
	{
		container::iterator begin;
		container::iterator end;
	};

	bool		is_alive;			// Indique si l'étoile est prise en compte
	Vector		previous_position;	// Position d'avant
	Vector		position;			// Position
	Vector		speed;				// Vitesse
	Vector		acceleration;		// Accélération
	double		mass;				// Masse (en kilogrames)
	double		density;			// Densité autour de l'étoile
	COLORREF	color;				// Couleur
	int			index;				// Indice
	int			block_index;		// Indice du bloc

	Star();
	Star(const double& speed_initial, const double& area, const double& step, const double& galaxy_thickness, const double& total_mass);
	Star(const Star& star);

	void operator=(const Star& star);

	void update_position(const double& step, const bool& verlet_integration);
	void update_speed(const double& step, const double& area);
	void update_acceleration_and_density(const double& precision, const Block& block);
	void update_color();
};

Vector force_and_density_calculation(const double& precision, Star& star, const Block& block);
void initialize_galaxy(Star::container& galaxy, const int& stars_number, const double& area, const double& initial_speed, const double& step, const bool& is_black_hole, const double& black_hole_mass, const double& galaxy_thickness, const double& total_mass);

#endif