#include "Simulation.h"

// Initialisation de la fenêtre en fonction de l'écran

void init_window(sf::RenderWindow& window, std::string project_name)
{
	uint16_t width;
	uint16_t height;

	if (sf::VideoMode::getDesktopMode().width > (16. / 9.) * sf::VideoMode::getDesktopMode().height)
		height = (sf::VideoMode::getDesktopMode().height * 3) / 4, width = (height * 16) / 9;

	else if (sf::VideoMode::getDesktopMode().width < (16. / 9.) * sf::VideoMode::getDesktopMode().height)
		width = (sf::VideoMode::getDesktopMode().width * 3) / 4, height = (width * 9) / 16;

	else
		width = (sf::VideoMode::getDesktopMode().width * 3) / 4, height = (sf::VideoMode::getDesktopMode().height * 3) / 4;

	screen_width = width;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	window.create(sf::VideoMode(width, height), project_name, sf::Style::Close | sf::Style::Titlebar, settings);

	sf::Image icon;
	icon.loadFromFile("dependencies/resources/icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

// Initialisation du menu

void init_menu(Menu& menu)
{
	menu.reload(sf::Color(20, 20, 200));

	menu.add_variable("star_nb", "Nombre d'etoiles", Int, 50000, 100, 500000);
	menu.add_variable("initial_speed", "Vitesse initiale", Double, 23., 0., 100., 1);
	menu.add_variable("area", "Taille de la galaxie", Double, 50., 10., 1000., 0);
	menu.add_variable("galaxy_thickness", "Epaisseur de la galaxie", Double, 1., 0., 10., 0);
	menu.add_variable("acc_max", "Limite de l'acceleration", Double, 700., 1., 2000., 1);
	menu.add_variable("precision", "Precision", Double, 0.5, 0., 2., 1);
	menu.add_variable("step", "Pas de temps", Double, 0.01, 0.001, 0.1, 3);
	menu.add_variable("simulation_speed", "Update / sec (0 = max)", Int, 0, 0, 1000);

	menu.init_names(50, 750, sf::Color::White, 150);
	menu.init_lines(700, 15, 1200, sf::Color(75, 75, 255));
	menu.init_circles(20, sf::Color::White);
	menu.init_values(40, 50, sf::Color::White);
	menu.init_boxes(45, 11, 900, sf::Color::White, sf::Color::Green);
	menu.init_start(150, 1920 * RESIZE - 150, 1080 * RESIZE - 150, sf::Color::White);
}

// Main

int main()
{
	// Initialisation

	sf::RenderWindow window;
	init_window(window, "Galaxy simulation");

	Menu menu;
	init_menu(menu);

	Restart restart_button(150, 1920 * RESIZE - 150, 1080 * RESIZE - 150, sf::Color::White);

	bool simulation_end = false;
	bool end = false;

	sf::Cursor cursor;
	cursor.loadFromSystem(sf::Cursor::Arrow);
	window.setMouseCursor(cursor);

	// lancement de la simulation

	Simulation simulation;
	My_event my_event(&window, &simulation, &restart_button, &end, &simulation_end);

	while (!end)
	{
		// Lancement du menu

		while (!menu.end && !end)
		{
			if (sleep_every(FPS_BUTTONS))
			{
				my_event.check();

				menu.update(window);
				menu.draw(window);
			}
		}

		cursor.loadFromSystem(sf::Cursor::Wait);
		window.setMouseCursor(cursor);

		menu.end = false;
		simulation.restart(menu, &window, my_event);
		restart_button.is_active = true;

		if (restart_button.is_in(sf::Vector2f(sf::Mouse::getPosition(window))))
			cursor.loadFromSystem(sf::Cursor::Hand);

		else
			cursor.loadFromSystem(sf::Cursor::Arrow);

		window.setMouseCursor(cursor);

		// Lancement de la simulation

		while (!simulation_end && !end)
		{
			if (menu["simulation_speed"] != 0)
			{
				if (sleep_every(menu["simulation_speed"]))
					simulation.update(my_event);
			}

			else
				simulation.update(my_event);

			if (sleep_every(FPS_BUTTONS))
			{
				window.clear(sf::Color::Black);

				simulation.draw();
				my_event.check();
			}
		}

		simulation_end = false;
		restart_button.is_active = false;
	}

	window.close();
	return 0;
}