#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "Menu.hpp"
#include "Computer.hpp"
#include "Renderer.hpp"
#include "ComputeShader.hpp"
#include <mutex>
#include <thread>
#include <atomic>
#include <string>

/**
 * @brief A static class representing the simulation.
 */
class Simulator
{
public:
	enum class CameraView : int
	{
		Isometric = 0,
		Top = 1
	};

	static std::atomic<bool>	computation_done;	// True if the computation is done.
	static std::atomic<bool>	reload;				// True if the simulation have to restart.
	static std::atomic<bool>	waiting;			// True if the renderer is waiting.
	static SimulationType		simulation_type;	// The type of the simulation.
	static float				step;				// The time step of the simulation.
	static float				smoothing_length;	// The smoothing length of the gravitational force.
	static float				interaction_rate;	// The proportion of interactive stars.
	static int					nb_stars;			// The number of stars.
	static float				galaxy_diameter;	// The diameter of the galaxy.
	static float				galaxy_thickness;	// The thickness of the galaxy.
	static float				galaxies_distance;	// The distance between the galaxies.
	static float				stars_speed;		// The initial speed of the stars.
	static float				black_hole_mass;	// The mass of the black hole.
	static CameraView			camera_view;		// Camera view preset at startup/config load.

	/**
	 * @brief Initialize the simulation.
	 */
	static void init();

	/**
	 * @brief Restart the simulation.
	 */
	static void restart();

	/**
	 * @brief Print all simulation parameters in one line.
	 */
	static void print_configuration();

	/**
	 * @brief Build all simulation parameters in one line.
	 *
	 * @return the configuration line
	 */
	static std::string configuration_line();

	/**
	 * @brief Update the simulation settings from the menu.
	 */
	static void menu_update();

	/**
	 * @brief Compute the simulation.
	 */
	static void compute_update();

	/**
	 * @brief Render the simulation.
	 */
	static void render_update();

	/**
	 * @brief Check the simulation events.
	 *
	 * @param sf_event the SFML event object
	 */
	static void check_events(const sf::Event& sf_event);

	/**
	 * @brief Draw the simulation.
	 */
	static void draw();

	/**
	 * @brief Apply the selected camera view preset.
	 */
	static void apply_camera_view();
};

#endif
