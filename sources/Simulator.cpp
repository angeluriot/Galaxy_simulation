#include "Simulator.hpp"

std::atomic<bool>	Simulator::computation_done;
std::atomic<bool>	Simulator::reload;
std::atomic<bool>	Simulator::waiting;
SimulationType		Simulator::simulation_type;
float				Simulator::step;
float				Simulator::smoothing_length;
float				Simulator::interaction_rate;
int					Simulator::nb_stars;
float				Simulator::galaxy_diameter;
float				Simulator::galaxy_thickness;
float				Simulator::galaxies_distance;
float				Simulator::stars_speed;
float				Simulator::black_hole_mass;

void Simulator::init()
{
	dim::PerspectiveCamera cam(45.f, 1.f, 10000.f);
	cam.set_position(dim::Vector3(0.f, 0.f, 130.f));
	dim::Vector3 camera_pos = cam.get_position();
	camera_pos.set_phi(dim::pi / 3.f);
	cam.set_position(camera_pos);
	dim::Window::set_camera(cam);
	dim::Window::set_controller(dim::OrbitController(dim::Vector3::null, dim::OrbitController::default_sensitivity, 2.f));

	dim::Shader::add("galaxy", "shaders/galaxy.vert", "shaders/galaxy.frag");
	dim::Shader::add("blur", "shaders/blur.vert", "shaders/blur.frag");
	dim::Shader::add("post", "shaders/post.vert", "shaders/post.frag");

	ComputeShader::init("shaders/compute/cl_compute_shader.cl");
	Menu::set_default_values();
	Simulator::restart();
}

void Simulator::restart()
{
	simulation_type = Menu::simulation_type;
	step = Menu::step;
	smoothing_length = Menu::smoothing_length;
	interaction_rate = Menu::interaction_rate;
	nb_stars = Menu::nb_stars;
	galaxy_diameter = Menu::galaxy_diameter;
	galaxy_thickness = Menu::galaxy_thickness;
	galaxies_distance = Menu::galaxies_distance;
	stars_speed = Menu::stars_speed;
	black_hole_mass = Menu::black_hole_mass;

	Computer::init();
	Renderer::init();

	computation_done = false;
	waiting = false;
	reload = false;
}

void Simulator::menu_update()
{
	step = Menu::step;
	smoothing_length = Menu::smoothing_length;
	interaction_rate = Menu::interaction_rate;
}

void Simulator::compute_update()
{
	if (!Menu::pause && (!computation_done || waiting) && !reload)
	{
		menu_update();
		Computer::compute();
		computation_done = true;
	}

	if (Menu::pause)
		computation_done = true;
}

void Simulator::render_update()
{
	waiting = true;

	if (0.01f - dim::Window::get_elapsed_time() > 0.f)
		sf::sleep(sf::seconds(0.01f - dim::Window::get_elapsed_time()));

	waiting = false;

	if (computation_done)
	{
		if (reload)
			restart();

		else
		{
			Renderer::update_vbo();
			computation_done = false;
		}
	}
}

void Simulator::check_events(const sf::Event& sf_event)
{
	Renderer::check_events(sf_event);
}

void Simulator::draw()
{
	Renderer::clear();
	Renderer::draw();
}
