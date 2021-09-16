#ifndef MENU_HPP
#define MENU_HPP

#include "libraries.hpp"

enum class IntergrationMethod : int
{
	Euler		= 0,
	Verlet		= 1,
	Leapfrog	= 2
};

class Menu
{
	public:

		static bool		visible;
		static bool		active;
		static bool		pause;
		static float	step;
		static int		intergration_method;
		static float	smoothing_length;
		static float	precision;
		static int		nb_stars;
		static float	galaxy_diameter;
		static float	galaxy_thickness;
		static float	stars_speed;

		static void check_events(const sf::Event& sf_event);
		static void display();
};

#endif
