#include "utils.h"
#include "Star.h"
#include "Simulation.h"
#include "Menu.h"

uint16_t screen_width;

// Construit un gestionnaire d'événement

My_event::My_event()
{
	window = NULL;
	simulation = NULL;
	restart_button = NULL;
	end = NULL;
	simulation_end = NULL;
}

// Construit un gestionnaire d'événement à partir d'un autre

My_event::My_event(const My_event& sf)
{
	*this = sf;
}

// Construit un gestionnaire d'événement à partir des pointeurs qu'il utilise

My_event::My_event(sf::RenderWindow* window, Simulation* simulation, Restart* restart_button, bool* end, bool* simulation_end)
{
	this->window = window;
	this->simulation = simulation;
	this->restart_button = restart_button;
	this->end = end;
	this->simulation_end = simulation_end;
}

// Assignation

void My_event::operator=(const My_event& sf)
{
	window = sf.window;
	simulation = sf.simulation;
	restart_button = sf.restart_button;
	end = sf.end;
	simulation_end = sf.simulation_end;
}

// Gestion des différents types d'événements

bool My_event::events(sf::Event& sf_event)
{
	if (sf_event.type == sf::Event::Closed)
	{
		*end = true;
		return true;
	}

	if (restart_button->is_active)
	{
		if (restart_button->update(*window))
		{
			*simulation_end = true;
			window->clear(sf::Color::Black);
			simulation->draw();
			restart_button->draw(*window);
			window->display();
			return true;
		}

		window->clear(sf::Color::Black);
		simulation->draw();
		restart_button->draw(*window);
		window->display();
	}

	return false;
}

// Vérifie si un événement se produit

bool My_event::check()
{
	static sf::Event sf_event;

	window->pollEvent(sf_event);

	if (events(sf_event))
		return true;

	return false;
}

// Attend qu'un événement se produit

bool My_event::wait()
{
	static sf::Event sf_event;

	window->waitEvent(sf_event);

	return events(sf_event);
}

// Donne un entier entre min et max

uint32_t random_int(int32_t min, int32_t max)
{
	return rand() % (max - min) + min;
}

// Donne un réel entre min et max

Float random_Float(const Float& min, const Float& max)
{
	return (static_cast<Float>(rand()) / static_cast<Float>(RAND_MAX)) * (max - min) + min;
}

// Donne "vrai" avec une probabilité choisie

bool rand_probability(const Float& probability)
{
	if (probability < 0.f)
		return false;

	if (probability < 1.f)
		return (rand() / static_cast<Float>(RAND_MAX) < probability);

	return true;
}

// Donne la position sur l'écran à partir de la position dans la simulation

sf::Vector2f simu_to_screen(const Vector& position, const Float& area, View view)
{
	if (view == View::Default)
		return sf::Vector2f((position.x / (area * 1.2f)) * 1080.f * RESIZE + 960.f * RESIZE,
			((position.y / (area * 1.2f)) * 1080.f * RESIZE + 540.f * RESIZE) / 2.f + ((position.z / (area * 1.2f)) * 1080.f * RESIZE + 540.f * RESIZE) / 2.f);

	if (view == View::XY)
		return sf::Vector2f((position.x / (area * 1.2f)) * 1080.f * RESIZE + 960.f * RESIZE, (position.y / (area * 1.2f)) * 1080.f * RESIZE + 540.f * RESIZE);

	if (view == View::XZ)
		return sf::Vector2f((position.x / (area * 1.2f)) * 1080.f * RESIZE + 960.f * RESIZE, (position.z / (area * 1.2f)) * 1080.f * RESIZE + 540.f * RESIZE);

	if (view == View::YZ)
		return sf::Vector2f((position.y / (area * 1.2f)) * 1080.f * RESIZE + 960.f * RESIZE, (position.z / (area * 1.2f)) * 1080.f * RESIZE + 540.f * RESIZE);
}

// Donne la taille sur l'écran à partir de la taille dans la simulation

sf::Vector2f simu_to_screen(const Float& size, const Float& area)
{
	return sf::Vector2f((size / (area * 1.2f)) * 1080.f * RESIZE , (size / (area * 1.2f)) * 1080.f * RESIZE );
}

bool sleep_every(uint16_t milliseconds)
{
	static sf::Clock clock;
	
	if (clock.getElapsedTime() >= sf::milliseconds(milliseconds))
	{
		clock.restart();
		return true;
	}

	else
		return false;
}