#include <dim/dimension3D.hpp>
#include "Simulator.hpp"
#include <GL/glew.h>
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <exception>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <cctype>


// Function to print OpenGL context information
void print_opengl_info()
{
    const GLubyte* renderer = glGetString(GL_RENDERER); // Get renderer string
    const GLubyte* vendor = glGetString(GL_VENDOR); // Get vendor string
    const GLubyte* version = glGetString(GL_VERSION); // Version as a string
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION); // GLSL version string

    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    std::cout << "OpenGL Renderer: " << renderer << std::endl;
    std::cout << "OpenGL Vendor: " << vendor << std::endl;
    std::cout << "OpenGL Version: " << version << std::endl;
    std::cout << "GLSL Version: " << glslVersion << std::endl;
    std::cout << "OpenGL Version: " << major << "." << minor << std::endl;
}

struct BatchOptions
{
	bool enabled = false;
	int steps = 0;
	int snapshots = 3;
	std::string output_dir = "outputs";
	std::string config_path;
	std::string batch_config_path;
};

static int parse_int(const char* value, int fallback)
{
	if (value == nullptr)
		return fallback;
	try
	{
		return std::stoi(value);
	}
	catch (const std::exception&)
	{
		return fallback;
	}
}

static BatchOptions parse_args(int argc, char** argv)
{
	BatchOptions options;

	for (int i = 1; i < argc; ++i)
	{
		std::string arg = argv[i];
		if (arg == "--batch-steps" && i + 1 < argc)
		{
			options.steps = std::max(0, parse_int(argv[++i], 0));
			options.enabled = (options.steps > 0);
		}
		else if (arg == "--snapshots" && i + 1 < argc)
			options.snapshots = std::max(1, parse_int(argv[++i], 3));
		else if (arg == "--output-dir" && i + 1 < argc)
			options.output_dir = argv[++i];
		else if (arg == "--config" && i + 1 < argc)
			options.config_path = argv[++i];
		else if (arg == "--batch-config" && i + 1 < argc)
			options.batch_config_path = argv[++i];
	}

	return options;
}

static bool to_float(const std::string& text, float& value)
{
	try { value = std::stof(text); return true; } catch (...) { return false; }
}

static bool to_int(const std::string& text, int& value)
{
	try { value = std::stoi(text); return true; } catch (...) { return false; }
}

static bool parse_simulation_type(const std::string& text, SimulationType& value)
{
	if (text == "Galaxy" || text == "0") { value = SimulationType::Galaxy; return true; }
	if (text == "Collision" || text == "1") { value = SimulationType::Collision; return true; }
	if (text == "Universe" || text == "2") { value = SimulationType::Universe; return true; }
	return false;
}

static bool parse_matter_distribution(const std::string& text, MatterDistribution& value)
{
	if (text == "CoreHalo" || text == "Core+halo" || text == "0") { value = MatterDistribution::CoreHalo; return true; }
	if (text == "RandomMix" || text == "1") { value = MatterDistribution::RandomMix; return true; }
	if (text == "SplitX" || text == "2") { value = MatterDistribution::SplitX; return true; }
	return false;
}

static bool parse_camera_view(const std::string& text, Simulator::CameraView& value)
{
	if (text == "isometric" || text == "iso" || text == "0") { value = Simulator::CameraView::Isometric; return true; }
	if (text == "top" || text == "1") { value = Simulator::CameraView::Top; return true; }
	return false;
}

using ConfigKV = std::unordered_map<std::string, std::string>;

static ConfigKV parse_config_line(const std::string& raw)
{
	std::string line = raw;
	const size_t comment_pos = line.find('#');
	if (comment_pos != std::string::npos)
		line = line.substr(0, comment_pos);

	std::istringstream in(line);
	std::string token;
	ConfigKV values;

	while (in >> token)
	{
		if (token == "SIMCFG" || token == "BATCHCFG")
			continue;

		const size_t eq = token.find('=');
		if (eq == std::string::npos || eq == 0 || eq + 1 >= token.size())
			continue;

		values[token.substr(0, eq)] = token.substr(eq + 1);
	}

	return values;
}

static std::vector<ConfigKV> load_config_jobs(const std::string& path)
{
	std::ifstream file(path);
	std::vector<ConfigKV> jobs;

	if (!file.is_open())
		return jobs;

	std::string line;
	while (std::getline(file, line))
	{
		ConfigKV kv = parse_config_line(line);
		if (!kv.empty())
			jobs.push_back(std::move(kv));
	}

	return jobs;
}

static bool apply_config_kv(const ConfigKV& kv, BatchOptions& batch, bool* output_dir_overridden = nullptr)
{
	if (output_dir_overridden != nullptr)
		*output_dir_overridden = false;

	auto get = [&](const char* key) -> const std::string*
	{
		const auto it = kv.find(key);
		return (it == kv.end()) ? nullptr : &it->second;
	};

	if (const std::string* v = get("simulation_type"))
	{
		SimulationType type = Menu::simulation_type;
		if (parse_simulation_type(*v, type))
			Menu::simulation_type = type;
	}
	if (const std::string* v = get("matter_distribution"))
	{
		MatterDistribution distribution = Menu::matter_distribution;
		if (parse_matter_distribution(*v, distribution))
			Menu::matter_distribution = distribution;
	}
	if (const std::string* v = get("camera_view"))
	{
		Simulator::CameraView view = Simulator::camera_view;
		if (parse_camera_view(*v, view))
			Simulator::camera_view = view;
	}

	auto set_float = [&](const char* key, float& target)
	{
		if (const std::string* v = get(key))
		{
			float parsed = target;
			if (to_float(*v, parsed))
				target = parsed;
		}
	};
	auto set_int = [&](const char* key, int& target)
	{
		if (const std::string* v = get(key))
		{
			int parsed = target;
			if (to_int(*v, parsed))
				target = parsed;
		}
	};

	set_float("step", Menu::step);
	set_float("smoothing_length", Menu::smoothing_length);
	set_float("interaction_rate", Menu::interaction_rate);
	set_int("nb_stars", Menu::nb_stars);
	set_float("galaxy_diameter", Menu::galaxy_diameter);
	set_float("galaxy_thickness", Menu::galaxy_thickness);
	set_float("galaxies_distance", Menu::galaxies_distance);
	set_float("stars_speed", Menu::stars_speed);
	set_float("black_hole_mass", Menu::black_hole_mass);
	set_float("negative_attraction_constant", Menu::negative_attraction_constant);
	set_float("repulsion_constant", Menu::repulsion_constant);
	set_float("type_diameter", Menu::type_diameter);
	set_float("positive_ratio", Menu::positive_ratio);
	set_float("core_extra_negative_density", Menu::core_extra_negative_density);

	if (const std::string* v = get("batch_steps"))
	{
		int parsed = batch.steps;
		if (to_int(*v, parsed))
		{
			batch.steps = std::max(0, parsed);
			batch.enabled = (batch.steps > 0);
		}
	}
	if (const std::string* v = get("snapshots"))
	{
		int parsed = batch.snapshots;
		if (to_int(*v, parsed))
			batch.snapshots = std::max(1, parsed);
	}
	if (const std::string* v = get("output_dir"))
	{
		batch.output_dir = *v;
		if (output_dir_overridden != nullptr)
			*output_dir_overridden = true;
	}

	return true;
}

static bool save_window_snapshot(const std::string& path)
{
	sf::RenderWindow& window = dim::Window::get_window();
	const sf::Vector2u size = window.getSize();
	sf::Texture texture;

	if (!texture.create(size.x, size.y))
		return false;

	texture.update(window);
	const sf::Image image = texture.copyToImage();
	return image.saveToFile(path);
}

static void set_snapshot_camera_angle(float theta, float phi = dim::pi / 3.f)
{
	dim::Camera& camera = dim::Window::get_camera();
	const float radius = camera.get_position().get_norm();
	const dim::Vector3 position = dim::Vector3::Spherical(radius, theta, phi);
	camera.set_position(position);
	camera.set_direction(-position);
}

static int run_batch_mode(const BatchOptions& options, bool close_window)
{
	std::cout << "Running batch mode for " << options.steps << " steps..." << std::endl;

	Menu::pause = false;
	for (int i = 0; i < options.steps && dim::Window::running; ++i)
	{
		Simulator::menu_update();
		Computer::compute();
	}

	Renderer::update_vbo();

	std::error_code ec;
	std::filesystem::create_directories(options.output_dir, ec);
	if (ec)
		std::cerr << "Warning: failed to create output directory: " << options.output_dir << std::endl;

	for (int i = 0; i < options.snapshots; ++i)
	{
		const float theta = (2.f * dim::pi * static_cast<float>(i)) / static_cast<float>(options.snapshots);
		set_snapshot_camera_angle(theta);

		dim::Window::clear(dim::Color::black);
		dim::Window::update();
		Renderer::clear();
		Simulator::draw();
		dim::Window::display();

		const std::string path = options.output_dir + "/snapshot_" + std::to_string(i) + ".png";
		if (save_window_snapshot(path))
			std::cout << "Saved " << path << std::endl;
		else
			std::cerr << "Failed to save " << path << std::endl;
	}

	if (close_window)
		dim::Window::close();
	return EXIT_SUCCESS;
}

int main(int argc, char** argv)
{
	const BatchOptions batch_options = parse_args(argc, argv);
	BatchOptions mutable_batch_options = batch_options;

	dim::Window::open("Galaxy simulation", 0.75f, "resources/icons/icon.png");
	Simulator::init();

	// Print OpenGL context information
    print_opengl_info();

	if (!mutable_batch_options.config_path.empty())
	{
		const std::vector<ConfigKV> jobs = load_config_jobs(mutable_batch_options.config_path);
		if (jobs.empty())
			std::cerr << "Warning: no valid config line found in " << mutable_batch_options.config_path << std::endl;
		else
		{
			apply_config_kv(jobs.front(), mutable_batch_options);
			Simulator::restart();
			Simulator::apply_camera_view();
		}
	}

	if (!mutable_batch_options.batch_config_path.empty())
	{
		const std::vector<ConfigKV> jobs = load_config_jobs(mutable_batch_options.batch_config_path);
		if (jobs.empty())
		{
			std::cerr << "Error: no valid batch jobs found in " << mutable_batch_options.batch_config_path << std::endl;
			dim::Window::close();
			return EXIT_FAILURE;
		}

		for (size_t i = 0; i < jobs.size(); ++i)
		{
			BatchOptions job_options = mutable_batch_options;
			bool output_dir_overridden = false;
			apply_config_kv(jobs[i], job_options, &output_dir_overridden);

			if (!job_options.enabled)
			{
				std::cerr << "Skipping job " << (i + 1) << ": missing batch_steps" << std::endl;
				continue;
			}

			if (!output_dir_overridden && jobs.size() > 1)
				job_options.output_dir = mutable_batch_options.output_dir + "/run_" + std::to_string(i + 1);

			std::cout << "[Batch] Job " << (i + 1) << "/" << jobs.size() << std::endl;
			Simulator::restart();
			Simulator::apply_camera_view();
			run_batch_mode(job_options, false);
		}

		dim::Window::close();
		return EXIT_SUCCESS;
	}

	if (mutable_batch_options.enabled)
		return run_batch_mode(mutable_batch_options, true);

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
