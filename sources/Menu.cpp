#include "Menu.hpp"
#include "Simulator.hpp"

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

		switch (simulation_type)
		{
		case SimulationType::Galaxy: galaxy(); break;
		case SimulationType::Collision: collision(); break;
		case SimulationType::Universe: universe(); break;
		default: break;
		}

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
