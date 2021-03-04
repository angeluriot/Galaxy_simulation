#ifndef UTILS_H
#define UTILS_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>
#include <vector>
#include <iostream>
#include <list>
#include <thread>
#include <mutex>
#include <atomic>
#include <utility>
#include <array>
#include "Vector.h"

class Simulation;
class Star;
class Restart;

typedef					std::list<Star> Galaxy;						// Typedef désignant une galaxie

extern uint16_t			screen_width;								// Largeur de l'écran
	
enum class				View { Default, XY, XZ, YZ };				// Vues possibles de la simulation

#define					WIDTH		1920							// Largeur de l'écran
#define					HEIGHT		1080							// Hauteur de l'écran
#define					RESIZE		((1.f / 1920.f) * screen_width)	// Coéfficient en fonction de la taille de l'écran
#define					FREE_THREAD	2								// Nombre de threads libres
#define					FPS_BUTTONS	10								// Nombre de millisecondes entre chaque updates des buttons

// Classe de gestion d'événements

class My_event
{
public:

	sf::RenderWindow*	window;			// Fenêtre SFML
	Simulation*			simulation;		// Simulation
	Restart*			restart_button;	// Pointeur vers le bouton restart
	bool*				end;			// Fin de la simulation
	bool*				simulation_end;	// La simulation

						My_event();
						My_event(const My_event& sf);
						My_event(sf::RenderWindow* window, Simulation* simulation, Restart* restart_button, bool* end, bool* simulation_end);

	void				operator=(const My_event& sf);

	bool				events(sf::Event& sf_event);
	bool				check();
	bool				wait();
};

uint32_t				random_int(int32_t min, int32_t max);
Float					random_Float(const Float& min, const Float& max);
bool					rand_probability(const Float& probability);
sf::Vector2f			simu_to_screen(const Vector& position, const Float& area, View view);
sf::Vector2f			simu_to_screen(const Float& size, const Float& area);
bool					sleep_every(uint16_t milliseconds);

#endif