#ifndef SIMULATION_H
#define SIMULATION_H
#include "Menu.h"
#include "Star.h"
#include "utils.h"
#include "Vector.h"
#include "Block.h"

typedef std::array<Galaxy::iterator, 2> Part;	// Typedef désignant une partie de la galaxie

// Classe définissant la simulation

class Simulation
{
public:

	sf::Image						void_image;	// Image vide
	sf::Image						image;		// Image é afficher
	sf::Texture						texture;	// Texture supportant l'image
	sf::RenderWindow*				window;		// Pointeur sur la fenétre
	uint8_t							thread_nb;	// Nombre de coeurs utilisés par le CPU
	std::vector<std::atomic<bool>>	finished;	// Indique pour chaque thread si il a terminé
	Galaxy							galaxy;		// Galaxie
	uint32_t						nb_stars;	// Nombre d'étoiles
	Block							block;		// Blocs de l'algorithme de BarneséHut
	Float							area;		// Zone d'apparition des étoiles
	Float							acc_max;	// Accélération maximum
	Float							precision;	// Précision de l'algorithme de BarneséHut
	Float							step;		// Pas de temps

									Simulation();
									Simulation(const Menu& menu, sf::RenderWindow* window, My_event& my_event);

	void							restart(const Menu& menu, sf::RenderWindow* window, My_event& my_event);
	void							center_galaxy();
	std::vector<Part>				split_galaxy();
	void							acceleration_update(const Galaxy::iterator& begin, const Galaxy::iterator& end, uint8_t thread_id);
	void							position_update(const Galaxy::iterator& begin, const Galaxy::iterator& end, uint8_t thread_id);
	bool							check_events(My_event& my_event, std::vector<std::thread>& threads);
	bool							check_events(My_event& my_event, std::thread& thread);
	void							update(My_event& my_event);
	void							draw_simulation();
	void							draw();
	void							save_image(const std::string& folder);
};

#endif