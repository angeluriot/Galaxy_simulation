#include "Menu.hpp"
#include "Simulator.hpp"
#include <filesystem>
#include <fstream>
#include <exception>

bool			Menu::visible			= true;
bool			Menu::active			= false;
bool			Menu::pause				= false;
SimulationType	Menu::simulation_type	= SimulationType::Galaxy;
float			Menu::step;
float			Menu::smoothing_length;
float			Menu::interaction_rate;
int				Menu::nb_stars;
float			Menu::galaxy_diameter;
float			Menu::galaxy_thickness;
float			Menu::galaxies_distance;
float			Menu::stars_speed;
float			Menu::black_hole_mass;
float			Menu::negative_attraction_constant = 1.0f;
float			Menu::repulsion_constant = 1.0f;
float			Menu::type_diameter = 50.0f;
MatterDistribution	Menu::matter_distribution = MatterDistribution::CoreHalo;
float			Menu::positive_ratio = 0.5f;
float			Menu::core_extra_negative_density = 0.0f;


void Menu::check_events(const sf::Event& sf_event)
{
	if (sf_event.type == sf::Event::KeyReleased && sf_event.key.code == sf::Keyboard::Key::F1)
		visible = !visible;
}

void Menu::title(const std::string& text)
{
	float window_width = ImGui::GetWindowSize().x;
	float text_width = ImGui::CalcTextSize(text.data()).x;

	ImGui::NewLine();
	ImGui::SetCursorPosX((window_width - text_width) * 0.5f);
	ImGui::Text(text.data());
	ImGui::Separator();
}

std::vector<bool> Menu::centered_buttons(const std::vector<std::string> texts, float buttons_height, float spaces_size)
{
	float window_width = ImGui::GetWindowSize().x;
	float buttons_widths = (window_width - ((texts.size() + 2) * spaces_size)) / texts.size();
	std::vector<bool> result(texts.size());

	ImGui::NewLine();
	ImGui::NewLine();

	for (int i = 0; i < texts.size(); i++)
	{
		ImGui::SameLine();
		ImGui::SetCursorPosX(spaces_size + buttons_widths * i + spaces_size * i);
		ImGui::Text("");
		ImGui::SameLine();
		result[i] = ImGui::Button(texts[i].data(), ImVec2(buttons_widths, buttons_height));
	}

	return result;
}

void Menu::set_default_values()
{
	step				= 0.001f;
	smoothing_length	= 1.f;
	galaxies_distance	= 75.f;
	black_hole_mass		= 1000.f;
	negative_attraction_constant = 1.0f;
	repulsion_constant = 1.0f;
	type_diameter = 50.0f;
	matter_distribution = MatterDistribution::CoreHalo;
	positive_ratio = 0.5f;
	core_extra_negative_density = 0.0f;


	switch (simulation_type)
	{
	case SimulationType::Galaxy:
		interaction_rate	= 0.05f;
		nb_stars			= 20000;
		galaxy_diameter		= 100.f;
		galaxy_thickness	= 5.f;
		stars_speed			= 20.f;
		break;

	case SimulationType::Collision:
		interaction_rate	= 0.05f;
		nb_stars			= 20000;
		galaxy_diameter		= 50.f;
		galaxy_thickness	= 2.5f;
		stars_speed			= 20.f;
		break;

	case SimulationType::Universe:
		interaction_rate	= 0.005f;
		nb_stars			= 100000;
		galaxy_diameter		= 10.f;
		galaxy_thickness	= 10.f;
		stars_speed			= 185.f;
		break;

	default:
		break;
	}
}

void Menu::galaxy()
{
	ImGui::Text("The number of stars");
	ImGui::SliderInt("##nb_stars", &nb_stars, 1000, 1000000, NULL, ImGuiSliderFlags_Logarithmic);

	ImGui::NewLine();

	ImGui::Text("The diameter of the galaxy");
	ImGui::SliderFloat("##galaxy_diameter", &galaxy_diameter, 10.f, 1000.f, "%.0f");

	ImGui::NewLine();

	ImGui::Text("The thickness of the galaxy");
	ImGui::SliderFloat("##galaxy_thickness", &galaxy_thickness, 1.f, 100.f, "%.0f");

	ImGui::NewLine();

	ImGui::Text("The initial speed of the stars");
	ImGui::SliderFloat("##stars_speed", &stars_speed, 0.f, 500.f, "%.1f");

	ImGui::NewLine();

	ImGui::Text("The mass of the black hole");
	ImGui::SliderFloat("##black_hole_mass", &black_hole_mass, 100.f, 1000000.f, "%.0f", ImGuiSliderFlags_Logarithmic);
}

void Menu::collision()
{
	ImGui::Text("The number of stars");
	ImGui::SliderInt("##nb_stars", &nb_stars, 1000, 1000000, NULL, ImGuiSliderFlags_Logarithmic);

	ImGui::NewLine();

	ImGui::Text("The diameter of the galaxies");
	ImGui::SliderFloat("##galaxy_diameter", &galaxy_diameter, 10.f, 1000.f, "%.0f");

	ImGui::NewLine();

	ImGui::Text("The thickness of the galaxies");
	ImGui::SliderFloat("##galaxy_thickness", &galaxy_thickness, 1.f, 100.f, "%.0f");

	ImGui::NewLine();

	ImGui::Text("The distance between the galaxies");
	ImGui::SliderFloat("##galaxies_distance", &galaxies_distance, 10.f, 1000.f, "%.0f");

	ImGui::NewLine();

	ImGui::Text("The initial speed of the stars");
	ImGui::SliderFloat("##stars_speed", &stars_speed, 0.f, 500.f, "%.1f");
}

void Menu::universe()
{
	ImGui::Text("The number of galaxies");
	ImGui::SliderInt("##nb_stars", &nb_stars, 1000, 1000000, NULL, ImGuiSliderFlags_Logarithmic);

	ImGui::NewLine();

	ImGui::Text("Ihe initial diameter of the universe");
	ImGui::SliderFloat("##galaxy_diameter", &galaxy_diameter, 1.f, 100.f, "%.1f");

	ImGui::NewLine();

	ImGui::Text("The initial speed of the galaxies");
	ImGui::SliderFloat("##stars_speed", &stars_speed, 0.f, 500.f, "%.1f");
}

void Menu::display()
{
	static std::string pause_button = "Pause";
	static char config_output_path[256] = "batch_configs/user.batchcfg";
	static std::string config_output_status;

	if (visible)
	{
		ImGui::Begin("Simulation settings (F1 to hide)");
		ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.9f);

		ImGui::NewLine();

		SimulationType temp = simulation_type;

		ImGui::Text("The type of simulation");
		ImGui::Combo("##simulation_type", reinterpret_cast<int*>(&simulation_type), "Galaxy\0Collision\0Universe");

		if (simulation_type != temp)
		{
			set_default_values();
			Simulator::reload = true;
		}
		ImGui::NewLine();

		Simulator::CameraView previous_camera_view = Simulator::camera_view;
		ImGui::Text("Camera view");
		ImGui::Combo("##camera_view", reinterpret_cast<int*>(&Simulator::camera_view), "Isometric\0Top");
		if (Simulator::camera_view != previous_camera_view)
			Simulator::apply_camera_view();
		ImGui::NewLine();

		// Janus force multipliers (real-time).
		ImGui::Text("Negative Attraction Constant");
		ImGui::SliderFloat("##Negative_Attraction_Constant", &negative_attraction_constant, -3.0f, 3.0f);
		ImGui::Text("Repulsion Constant");
		ImGui::SliderFloat("##Repulsion_Constant", &repulsion_constant, -3.0f, 3.0f);
		ImGui::NewLine();

		title("Real time settings");

		ImGui::NewLine();

		ImGui::Text("The time step duration");
		ImGui::SliderFloat("##step", &step, 0.0001f, 0.1f, "%.4f", ImGuiSliderFlags_Logarithmic);

		ImGui::NewLine();

		ImGui::Text("The smoothing length");
		ImGui::SliderFloat("##smoothing_length", &smoothing_length, 0.001f, 1.f, NULL, ImGuiSliderFlags_Logarithmic);

		ImGui::NewLine();

		ImGui::Text("The interaction rate");
		ImGui::SliderFloat("##interaction_rate", &interaction_rate, 0.001f, 1.f, "%.3f", ImGuiSliderFlags_Logarithmic);

		ImGui::NewLine();

		title("Applies after restart");

		ImGui::NewLine();

		ImGui::Text("Matter distribution");
		ImGui::Combo("##matter_distribution", reinterpret_cast<int*>(&matter_distribution), "Core + halo\0Random mix\0Split on X\0");
		ImGui::NewLine();

		if (matter_distribution == MatterDistribution::CoreHalo)
		{
			ImGui::Text("Positive core diameter");
			ImGui::SliderFloat("##Type_Diameter", &type_diameter, 0.0f, galaxy_diameter);
			ImGui::NewLine();

			ImGui::Text("Extra negative density inside core");
			ImGui::SliderFloat("##Core_Extra_Negative_Density", &core_extra_negative_density, 0.0f, 1.0f, "%.2f");
			ImGui::TextDisabled("0 = core fully positive, 1 = core fully negative");
			ImGui::NewLine();
		}
		else if (matter_distribution == MatterDistribution::RandomMix)
		{
			ImGui::Text("Positive matter ratio");
			ImGui::SliderFloat("##Positive_Ratio", &positive_ratio, 0.0f, 1.0f, "%.2f");
			ImGui::NewLine();
		}

		switch (simulation_type)
		{
		case SimulationType::Galaxy: galaxy(); break;
		case SimulationType::Collision: collision(); break;
		case SimulationType::Universe: universe(); break;
		default: break;
		}

		ImGui::NewLine();
		ImGui::Separator();
		ImGui::Text("Batch config export");
		ImGui::InputText("##config_output_path", config_output_path, sizeof(config_output_path));
		if (ImGui::Button("Append current SIMCFG to file"))
		{
			try
			{
				const std::filesystem::path output_path(config_output_path);
				if (output_path.has_parent_path())
					std::filesystem::create_directories(output_path.parent_path());

				std::ofstream out(config_output_path, std::ios::app);
				if (out)
				{
					out << Simulator::configuration_line() << '\n';
					config_output_status = std::string("Appended to ") + config_output_path;
				}
				else
					config_output_status = std::string("Failed to open ") + config_output_path;
			}
			catch (const std::exception& e)
			{
				config_output_status = std::string("Export error: ") + e.what();
			}
		}
		if (!config_output_status.empty())
			ImGui::TextWrapped("%s", config_output_status.c_str());

		ImGui::NewLine();

		std::vector<bool> buttons = centered_buttons({ "Restart", pause_button }, 25.f, 20.f);

		if (buttons[1])
			pause = !pause;

		pause_button = (pause ? "Play" : "Pause");

		if (buttons[0])
			Simulator::reload = true;

		active = ImGui::IsWindowFocused();

		ImGui::End();
	}
}
