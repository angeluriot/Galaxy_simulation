#include "Simulator.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>

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
Simulator::CameraView Simulator::camera_view = Simulator::CameraView::Isometric;

void Simulator::init()
{
	dim::PerspectiveCamera cam(45.f, 1.f, 10000.f);
	cam.set_position(dim::Vector3(0.f, 0.f, 130.f));
	dim::Window::set_camera(cam);
	apply_camera_view();
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
	print_configuration();

	computation_done = false;
	waiting = false;
	reload = false;
}

void Simulator::print_configuration()
{
	std::cout << configuration_line() << std::endl;
}

std::string Simulator::configuration_line()
{
	const char* simulation_type_name = "Galaxy";
	switch (Menu::simulation_type)
	{
	case SimulationType::Galaxy: simulation_type_name = "Galaxy"; break;
	case SimulationType::Collision: simulation_type_name = "Collision"; break;
	case SimulationType::Universe: simulation_type_name = "Universe"; break;
	}

	const char* matter_distribution_name = "CoreHalo";
	switch (Menu::matter_distribution)
	{
	case MatterDistribution::CoreHalo: matter_distribution_name = "CoreHalo"; break;
	case MatterDistribution::RandomMix: matter_distribution_name = "RandomMix"; break;
	case MatterDistribution::SplitX: matter_distribution_name = "SplitX"; break;
	}

	std::ostringstream out;
	out << std::fixed << std::setprecision(6);
	out
		<< "SIMCFG "
		<< "simulation_type=" << simulation_type_name << " "
		<< "step=" << Menu::step << " "
		<< "smoothing_length=" << Menu::smoothing_length << " "
		<< "interaction_rate=" << Menu::interaction_rate << " "
		<< "nb_stars=" << Menu::nb_stars << " "
		<< "galaxy_diameter=" << Menu::galaxy_diameter << " "
		<< "galaxy_thickness=" << Menu::galaxy_thickness << " "
		<< "galaxies_distance=" << Menu::galaxies_distance << " "
		<< "stars_speed=" << Menu::stars_speed << " "
		<< "black_hole_mass=" << Menu::black_hole_mass << " "
		<< "negative_attraction_constant=" << Menu::negative_attraction_constant << " "
		<< "repulsion_constant=" << Menu::repulsion_constant << " "
		<< "matter_distribution=" << matter_distribution_name << " "
		<< "type_diameter=" << Menu::type_diameter << " "
		<< "positive_ratio=" << Menu::positive_ratio << " "
		<< "core_extra_negative_density=" << Menu::core_extra_negative_density << " "
		<< "camera_view=" << (camera_view == CameraView::Top ? "top" : "isometric") << " "
		<< "batch_steps=2000 "
		<< "snapshots=4 "
		<< "output_dir=outputs";

	return out.str();
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

void Simulator::apply_camera_view()
{
	dim::Camera& camera = dim::Window::get_camera();
	const float radius = std::max(1.0f, camera.get_position().get_norm());

	switch (camera_view)
	{
	case CameraView::Top:
	{
		const dim::Vector3 position(0.0f, radius, 0.001f);
		camera.set_position(position);
		camera.set_direction(-position);
		break;
	}

	case CameraView::Isometric:
	default:
	{
		dim::Vector3 position(0.f, 0.f, radius);
		position.set_phi(dim::pi / 3.f);
		camera.set_position(position);
		camera.set_direction(-position);
		break;
	}
	}
}
