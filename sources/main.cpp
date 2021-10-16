#include <dim/dimension3D.hpp>
#include "Simulator.hpp"

int main()
{
	dim::Window::open("Galaxy simulation", 0.75f, "resources/icons/icon.png");
	Simulator::init();

	// The computation thread.
	std::thread simulation_thread([]()
	{
		while (dim::Window::running)
			Simulator::compute_update();
	});

	// The render thread.
	while (dim::Window::running)
	{
		// Check the events.
		sf::Event sf_event;
		while (dim::Window::poll_event(sf_event))
		{
			dim::Window::check_events(sf_event);
			Menu::check_events(sf_event);
			Simulator::check_events(sf_event);
		}

		dim::Window::get_controller().enable(!Menu::active || !Menu::visible, dim::Controller::Action::Look);

		dim::Window::clear(dim::Color::black);
		dim::Window::update();

		Simulator::render_update();
		Simulator::draw();

		Menu::display();
		dim::Window::display();
	}

	simulation_thread.join();
	dim::Window::close();
	return EXIT_SUCCESS;
}
