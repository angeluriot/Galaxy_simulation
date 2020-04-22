#ifndef STAR_H
#define STAR_H

#include "vector.h"

class Block;

/**
 * \class Star
 * \brief Définit une étoile.
 */
class Star {

public:

	using container = std::vector<Star>; // Plus rapide : contigüe en mémoire.

	struct range {
		container::iterator begin;
		container::iterator end;
	};

	//! Position d'avant
	glm::dvec3 previous_position{ 0, 0, 0 };
	//! Position
	glm::dvec3 position{ 0, 0, 0 };
	//! La vitesse
	glm::dvec3 speed{ 0, 0, 0 };
	//! L'accélération
	glm::dvec3 acceleration{ 0, 0, 0 };
	//! Masse en kilogramme
	double mass{ 0 };
	//! Densité autour de l'étoile
	double density{ 0 };
	//! La couleur de l'étoile
	glm::u8vec3 color{ 0, 0, 0 };
	//! Indice de l'étoile
	std::size_t index{ 0 };
	//! Indice du bloc
	std::size_t block_index{ 0 };
	//! Flag pour la prise en compte de l'étoile.
	bool is_alive{ false };

	Star() = default;

	virtual ~Star() = default;

	Star(const double &speed_initial, const double &area, const double &step, const double &galaxy_thickness);

	Star(const Star &star) = default;

	Star(Star &&star) = default;

	Star &operator=(const Star &star) = default;

	Star &operator=(Star &&star) = default;

	void update_position(const double &step, bool verlet_integration);

	void update_speed(const double &step, const double &area);

	void update_acceleration_and_density(const double &precision, const Block &block);

	void update_color();
};

glm::dvec3 force_and_density_calculation(const double &precision, Star &star, const Block &block);

void initialize_galaxy(Star::container &galaxy,
					   int stars_number,
					   const double &area,
					   const double &initial_speed,
					   const double &step,
					   bool is_black_hole,
					   const double &black_hole_mass,
					   const double &galaxy_thickness);

#endif