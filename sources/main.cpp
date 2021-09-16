#include <dim/dimension3D.hpp>
#include "Simulation.hpp"

int main()
{
	dim::Window::open("Galaxy simulation", 0.75f, "resources/icons/icon.png");

	dim::PerspectiveCamera cam(45.f, 1.f, 10000.f);
	cam.set_position(dim::Vector3(0.f, 0.f, 100.f));
	dim::Window::set_camera(cam);
	dim::Window::set_controller(dim::OrbitController(dim::Vector3::null, dim::OrbitController::default_sensitivity, 2.f));

	dim::Shader::add("star", "shaders/star.vert", "shaders/star.frag");
	dim::Shader::add("galaxy", "shaders/galaxy.vert", "shaders/galaxy.frag");
	dim::Shader::add("blur", "shaders/blur.vert", "shaders/blur.frag");
	dim::Shader::add("post", "shaders/post.vert", "shaders/post.frag");
	dim::Shader::add("test", "shaders/test.vert", "shaders/test.frag");

	Simulation::restart();

	std::thread simulation_thread([]()
	{
		while (dim::Window::running)
			Simulation::update();
	});

	while (dim::Window::running)
	{
		sf::Event sf_event;
		while (dim::Window::poll_event(sf_event))
		{
			if (sf_event.type == sf::Event::MouseWheelScrolled)
				dim::Window::get_controller().enable(true);

			dim::Window::check_events(sf_event);
			Menu::check_events(sf_event);
			Simulation::check_events(sf_event);
		}

		dim::Window::get_controller().enable(!Menu::active || !Menu::visible, dim::Controller::Action::Look);

		dim::Window::clear();
		Simulation::clear();
		dim::Window::update();

		//Simulation::send_mesh();
		Simulation::draw();

		Menu::display();
		dim::Window::display();
	}

	simulation_thread.join();
	dim::Window::close();
	return EXIT_SUCCESS;
}
