#ifndef MENU_HPP
#define MENU_HPP

#include "libraries.hpp"

/**
 * @brief The type of simulation.
 */
enum class SimulationType : int
{
	Galaxy		= 0,	// A unique galaxy.
	Collision	= 1,	// Two galaxies colliding.
	Universe	= 2		// The big bang.
};

/**
 * @brief The initial distribution of positive/negative matter.
 */
enum class MatterDistribution : int
{
	CoreHalo	= 0,	// Positive core and negative halo (radius threshold).
	RandomMix	= 1,	// Random mix based on positive ratio.
	SplitX		= 2		// Split space in two halves along the X axis.
};

/**
 * @brief The window to edit the settings of the simulation.
 */
class Menu
{
public:

	static bool				visible;			// True if the menu is visible, false otherwise.
	static bool				active;				// True if you clicked on the menu, false otherwise.
	static bool				pause;				// True if the simulation is paused, false otherwise.
	static SimulationType	simulation_type;	// The type of the simulation.
	static float			step;				// The time step of the simulation.
	static float			smoothing_length;	// The smoothing length of the gravitational force.
	static float			interaction_rate;	// The proportion of interactive stars.
	static int				nb_stars;			// The number of stars.
	static float			galaxy_diameter;	// The diameter of the galaxy.
	static float			galaxy_thickness;	// The thickness of the galaxy.
	static float			galaxies_distance;	// The distance between the galaxies.
	static float			stars_speed;		// The speed of the stars.
	static float			black_hole_mass;	// The mass of the black hole.
	static float			negative_attraction_constant;	// Multiplier for negative-negative attraction.
	static float			repulsion_constant;				// Multiplier for opposite-type interaction.
	static float			type_diameter;					// Diameter used by core/halo matter distribution.
	static MatterDistribution matter_distribution;		// Initial positive/negative matter distribution model.
	static float			positive_ratio;					// Positive matter ratio for random mix.
	static float			core_extra_negative_density;	// Extra negative density injected inside the core.

	/**
	 * @brief Handle the events of the menu.
	 *
	 * @param sf_event the SFML event object
	 */
	static void check_events(const sf::Event& sf_event);

	/**
	 * @brief Show the title of a part of the menu.
	 *
	 * @param text the title text
	 */
	static void title(const std::string& text);

	/**
	 * @brief Show centered buttons
	 *
	 * @param texts the text of the buttons
	 * @param buttons_height the height of the buttons
	 * @param spaces_size the size of the space between the buttons
	 * @return an array of booleans that are true if the corresponding button was clicked
	 */
	static std::vector<bool> centered_buttons(const std::vector<std::string> texts, float buttons_height, float spaces_size);

	/**
	 * @brief Set the default values of the simulation settings.
	 */
	static void set_default_values();

	/**
	 * @brief Show the galaxy settings.
	 */
	static void galaxy();

	/**
	 * @brief Show the collision settings.
	 */
	static void collision();

	/**
	 * @brief Show the universe settings.
	 */
	static void universe();

	/**
	 * @brief Show the settings.
	 */
	static void display();
};

#endif
