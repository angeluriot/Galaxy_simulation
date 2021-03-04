#ifndef STAR_H
#define STAR_H
#include "Vector.h"
#include "utils.h"

class Block;

// Classe définissant une étoile

class Star
{
public:

	Vector		previous_position;	// Position d'avant
	Vector		position;			// Position
	Vector		speed;				// Vitesse
	Vector		acceleration;		// Accélération
	Float		density;			// Densité autour de l'étoile
	sf::Color	color;				// Couleur
	Block*		block_index;		// Pointeur vers le bloc

				Star();
				Star(const Float& speed_initial, const Float& area, const Float& galaxy_thickness, const Float& step);
				Star(const Star& star);

	void		operator=(const Star& star);

	void		update_position(const Float& step);
	void		update_speed(const Float& step);
	void		update_acceleration(Galaxy& galaxy, const Float& acc_max, const Block& block, const Float& precision);
	void		force_calculation(const Block& block, const Float& precision);
	void		update_color(uint32_t nb_stars);
	void		draw(const Float& area, sf::Image& texture, View view) const;
};

#endif