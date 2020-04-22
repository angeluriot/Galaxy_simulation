#ifndef STAR_H
#define STAR_H

#include "vector.h"

#if defined(_WIN32) || defined(WIN32)

#include <Windows.h>

#else
#define GLM_FORCE_INLINE
#define GLM_FORCE_SIZE_T_LENGTH

#include <glm/vec3.hpp>

#endif

class Block;



// Classe définissant une étoile

class Star {

public:

	using container = std::vector<Star>; // Plus rapide : contigüe en mémoire.

	struct range {
		container::iterator begin;
		container::iterator end;
	};

	Vector previous_position{ 0, 0, 0 };    // Position d'avant
	Vector position{ 0, 0, 0 };            // Position
	Vector speed{ 0, 0, 0 };                // Vitesse
	Vector acceleration{ 0, 0, 0 };        // Accélération
	double mass{ 0 };                // Masse (en kilogrames)
	double density{ 0 };            // Densité autour de l'étoile
	glm::u8vec3 color;                // Couleur, x, y, z et r, g, b sont deux structures dans une union. Les données se confondent.
	std::size_t index{ 0 };                // Indice
	std::size_t block_index{ 0 };        // Indice du bloc
	bool is_alive{ false };            // Indique si l'étoile est prise en compte

	Star() = default;

	virtual ~Star() = default;

	Star(const double &speed_initial, const double &area, const double &step, const double &galaxy_thickness);

	Star(const Star &star) = default;

	Star &operator=(const Star &star) = default;

	void update_position(const double &step, bool verlet_integration);

	void update_speed(const double &step, const double &area);

	void update_acceleration_and_density(const double &precision, const Block &block);

	void update_color();
};

Vector force_and_density_calculation(const double &precision, Star &star, const Block &block);

void initialize_galaxy(Star::container &galaxy,
					   int stars_number,
					   const double &area,
					   const double &initial_speed,
					   const double &step,
					   bool is_black_hole,
					   const double &black_hole_mass,
					   const double &galaxy_thickness);

#endif