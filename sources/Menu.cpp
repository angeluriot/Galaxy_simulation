#include "Menu.hpp"
#include "Simulation.hpp"

bool	Menu::visible				= true;
bool	Menu::active				= false;
bool	Menu::pause					= false;
float	Menu::step					= 0.01f;
int		Menu::intergration_method	= static_cast<int>(IntergrationMethod::Leapfrog);
float	Menu::smoothing_length		= 0.01f;
float	Menu::precision				= 1.f;
int		Menu::nb_stars				= 100000;
float	Menu::galaxy_diameter		= 100.f;
float	Menu::galaxy_thickness		= 5.f;
float	Menu::stars_speed			= 25.f;

void Menu::check_events(const sf::Event& sf_event)
{
	if (sf_event.type == sf::Event::KeyReleased && sf_event.key.code == sf::Keyboard::Key::F1)
		visible = !visible;
}

void Menu::display()
{
	static std::string pause_button = "Pause";

	if (visible)
	{
		ImGui::Begin("simulation settings");
		ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.9f);

		ImGui::Text("Real time settings");
		ImGui::Separator();

		ImGui::NewLine();

		ImGui::Text("The time step duration");
		ImGui::SliderFloat("##step", &step, 0.0001f, 0.1f);

		ImGui::NewLine();

		ImGui::Text("The integration method");
		ImGui::Combo("##integration_method", &intergration_method, "Euler\0Verlet\0Leapfrog");

		ImGui::NewLine();

		ImGui::Text("The smoothing length");
		ImGui::SliderFloat("##smoothing_length", &smoothing_length, 0.f, 0.1f);

		ImGui::NewLine();

		ImGui::Text("The Barnes-Hut precision");
		ImGui::SliderFloat("##precision", &precision, 0.5f, 2.f);

		ImGui::NewLine();
		ImGui::NewLine();

		ImGui::Text("Applies after restart");
		ImGui::Separator();

		ImGui::NewLine();

		ImGui::Text("The number of stars");
		ImGui::SliderInt("##nb_stars", &nb_stars, 100, 500000);

		ImGui::NewLine();

		ImGui::Text("The diameter of the galaxy");
		ImGui::SliderFloat("##galaxy_diameter", &galaxy_diameter, 10.f, 1000.f);

		ImGui::NewLine();

		ImGui::Text("The thickness of the galaxy");
		ImGui::SliderFloat("##galaxy_thickness", &galaxy_thickness, 1.f, 100.f);

		ImGui::NewLine();

		ImGui::Text("The initial speed of the stars");
		ImGui::SliderFloat("##stars_speed", &stars_speed, 0.f, 200.f);

		ImGui::NewLine();
		ImGui::NewLine();

		if (ImGui::Button(pause_button.data(), ImVec2(85, 25)))
			pause = !pause;

		pause_button = (pause ? "Play" : "Pause");

		ImGui::SameLine();
		ImGui::Text("");
		ImGui::SameLine();

		if (ImGui::Button("Restart", ImVec2(85, 25)))
		{
			Simulation::reload.lock();
			Simulation::restart();
			Simulation::reload.unlock();
		}

		active = ImGui::IsWindowFocused();

		ImGui::End();
	}
}
