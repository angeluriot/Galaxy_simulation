#include "Simulation.h"

// Crée une simulation

Simulation::Simulation()
{
	window = NULL;
	thread_nb = 0;
	finished.clear();
	galaxy.clear();
	nb_stars = 0;
	area = 0.f;
	acc_max = 0.f;
	precision = 0.f;
	step = 0.f;
}

// Crée une simulation à partir des données du menu

Simulation::Simulation(const Menu& menu, sf::RenderWindow* window, My_event& my_event)
{
	restart(menu, window, my_event);
}

// Recrée une simulation à partir des données du menu

void Simulation::restart(const Menu& menu, sf::RenderWindow* window, My_event& my_event)
{
	// Affichage
	void_image.create(WIDTH, HEIGHT, sf::Color(0, 0, 0));
	image = void_image;
	texture.create(WIDTH, HEIGHT);
	this->window = window;

	// Multithreading
	thread_nb = std::max(static_cast<int>(std::thread::hardware_concurrency()) - FREE_THREAD, 1);
	finished = std::vector<std::atomic<bool>>(thread_nb);
	std::fill(finished.begin(), finished.end(), false);

	// Paramétres
	area = menu["area"];
	acc_max = menu["acc_max"];
	precision = menu["precision"];
	step = menu["step"];

	// Galaxie

	galaxy.clear();

	for (uint32_t i = 0; i < menu["star_nb"]; i++)
		galaxy.push_back(Star(menu["initial_speed"], area, menu["galaxy_thickness"], step));

	nb_stars = galaxy.size();
	update(my_event);
}

// Recentre la galaxie

void Simulation::center_galaxy()
{
	Vector mass_center = Vector();

	for (Star& star : galaxy)
		mass_center += star.position;

	mass_center /= static_cast<Float>(galaxy.size());

	for (Star& star : galaxy)
	{
		star.position -= mass_center;
		star.previous_position -= mass_center;
	}
}

// Donne les limites des coupes de la galaxie pour le multithreading

std::vector<Part> Simulation::split_galaxy()
{
	std::vector<Part> parts;
	Galaxy::iterator begin = galaxy.begin();
	Galaxy::iterator end;
	uint32_t part_size = galaxy.size() / thread_nb - 1;
	uint8_t t = 0;
	uint32_t i = 1;

	for (auto it = ++galaxy.begin(); it != galaxy.end(); ++it)
	{
		if (i % part_size == 0)
		{
			end = it;
			parts.push_back(Part({ begin, end }));
			t++;
			begin = it;
		}

		if (t == thread_nb)
			break;

		i++;
	}

	parts.back()[1] = galaxy.end();
	return parts;
}

// Met é jour l'accélération des étoiles pour un thread

void Simulation::acceleration_update(const Galaxy::iterator& begin, const Galaxy::iterator& end, uint8_t thread_id)
{
	for (auto it = begin; it != end; ++it)
	{
		it->update_acceleration(galaxy, acc_max, block, precision);

		if (finished[thread_id])
			return;
	}

	finished[thread_id] = true;
}

// Met é jour la position et la couleur des étoiles pour un thread

void Simulation::position_update(const Galaxy::iterator& begin, const Galaxy::iterator& end, uint8_t thread_id)
{
	for (auto it = begin; it != end; ++it)
	{
		it->update_position(step);
		it->update_color(nb_stars);

		if (finished[thread_id])
			return;
	}

	finished[thread_id] = true;
}

// Check les évenements et stop les threads

bool Simulation::check_events(My_event& my_event, std::vector<std::thread>& threads)
{
	while (!std::all_of(finished.begin(), finished.end(), [](bool i) -> bool { return i; }))
		if (sleep_every(FPS_BUTTONS))
			if (my_event.check())
				std::fill(finished.begin(), finished.end(), true);

	for (auto& thread : threads)
		thread.join();

	if (*(my_event.end) || *(my_event.simulation_end))
		return true;

	return false;

}

// Check les évenements et stop le thread

bool Simulation::check_events(My_event& my_event, std::thread& thread)
{
	while (!finished.front())
		if (sleep_every(FPS_BUTTONS))
			if (my_event.check())
				finished.front() = true;

	thread.join();

	if (*(my_event.end) || *(my_event.simulation_end))
		return true;

	return false;
}

// Met é jour la simulation (Gére le multithreading)

void Simulation::update(My_event& my_event)
{
	// Multithreading
	std::fill(finished.begin(), finished.end(), false);
	auto parts = split_galaxy();
	std::vector<std::thread> threads(thread_nb);
	std::thread thread;

	// Maj les blocs de l'algorithme de Barnes-Hut
	std::fill(finished.begin(), finished.end(), false);
	thread = std::thread([this]() { block.reload(*this); finished.front() = true; });

	// Evénements
	if (check_events(my_event, thread))
		return;

	// Acceleration

	std::fill(finished.begin(), finished.end(), false);

	for (uint8_t i = 0; i < threads.size(); i++)
		threads[i] = std::thread([this, i, parts]() { this->acceleration_update(parts[i][0], parts[i][1], i); });

	// Evénements
	if (check_events(my_event, threads))
		return;

	// Position et couleur

	std::fill(finished.begin(), finished.end(), false);

	for (uint8_t i = 0; i < threads.size(); i++)
		threads[i] = std::thread([this, i, parts]() { this->position_update(parts[i][0], parts[i][1], i); });

	// Evénements
	if (check_events(my_event, threads))
		return;

	// Recenter la galaxie et dessiner la simulation

	std::fill(finished.begin(), finished.end(), false);
	thread = std::thread([this]() { this->center_galaxy(); this->draw_simulation(); finished.front() = true; });

	// Evénements
	if (check_events(my_event, thread))
		return;
}

// Affiche la simulation sur l'image

void Simulation::draw_simulation()
{
	image = void_image;

	//block.draw(area, image, View::XY); // Décommenter pour afficher les blocs

	for (Star& star : galaxy)
		star.draw(area, image, View::XY);

	//save_image(""); // Décommenter pour enregister une image par frame (attention il faut mettre un chemin)
}

// Affiche la simulation sur l'écran

void Simulation::draw()
{
	texture.update(image);
	window->draw(sf::Sprite(texture));
}

// Enregistre chaque images dans un dossier

void Simulation::save_image(const std::string& folder)
{
	static uint32_t nb = 0;
	image.saveToFile(folder + (!folder.empty() && folder.back() == '/' ? "" : "/") + "image_" + std::to_string(nb) + ".png");
	nb++;
}