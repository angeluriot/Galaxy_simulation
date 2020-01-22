#ifndef STAR_H
#define STAR_H
#include "vector.h"
#include <Windows.h>

class Block;



// Classe définissant une étoile

class Star
{

public:

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
	Star(const double& speed_initial, const double& area, const double& step, const double& galaxy_thickness);
	Star(const Star& star);

	void operator=(const Star& star);

	void update_position(const double& step, const bool& verlet_integration);
	void update_speed(const double& step, const double& area);
	void update_acceleration_and_density(const double& precision, const std::vector<Star>& galaxy, const std::vector<Block>& blocks);
	void update_color();
};

Vector force_and_density_calculation(const double& precision, Star& star, const std::vector<Block>& blocks, int index);
void initialize_galaxy(std::vector<Star>& galaxy, const int& stars_number, const double& area, const double& speed_initial, const double& step, const bool& is_black_hole, const double& black_hole_mass, const double& galaxy_thickness);

#endif