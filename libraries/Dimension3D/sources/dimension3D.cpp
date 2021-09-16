#include <dim/dimension3D.hpp>

namespace dim
{
	void init_opengl()
	{
		glewExperimental = GL_TRUE;
		glewInit();

		glViewport(0, 0, Window::get_width(), Window::get_height());
		glClearColor(Window::background.r, Window::background.g, Window::background.b, Window::background.a);
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
		glDepthFunc(GL_LESS);
		glDepthRange(0.f, 1.f);
	}

	void init_imgui()
	{
		ImGui::SFML::Init(Window::get_window());
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		ImGui::StyleColorsDark();
		ImGui::GetStyle().TabRounding = 7.f;
		ImGui::GetStyle().GrabRounding = 7.f;
		ImGui::GetStyle().ChildRounding = 7.f;
		ImGui::GetStyle().FrameRounding = 7.f;
		ImGui::GetStyle().PopupRounding = 7.f;
		ImGui::GetStyle().WindowRounding = 7.f;
		ImGui::GetStyle().ScrollbarRounding = 7.f;

		Color invisible_medium(40.f / 255.f, 44.f / 255.f, 52.f / 255.f, 0.f);

		Color dark(27.f / 255.f, 31.f / 255.f, 39.f / 255.f);
		Color medium(40.f / 255.f, 44.f / 255.f, 52.f / 255.f);
		Color light(67.f / 255.f, 74.f / 255.f, 87.f / 255.f);
		Color blue(0.1f, 0.5f, 1.f, 0.3f);

		ImGuiStyle& style = ImGui::GetStyle();

		style.Colors[ImGuiCol_Border] = light.to_im();
		style.Colors[ImGuiCol_BorderShadow] = Color::transparent.to_im();
		style.Colors[ImGuiCol_Button] = dark.to_im();
		style.Colors[ImGuiCol_ButtonActive] = ((dark + medium) / 2.f).to_im();
		style.Colors[ImGuiCol_ButtonHovered] = light.to_im();
		style.Colors[ImGuiCol_CheckMark] = Color::white.to_im();
		style.Colors[ImGuiCol_ChildBg] = medium.to_im();
		style.Colors[ImGuiCol_COUNT] = Color::transparent.to_im();
		style.Colors[ImGuiCol_DockingEmptyBg] = Color::transparent.to_im();
		style.Colors[ImGuiCol_DockingPreview] = blue.to_im();
		style.Colors[ImGuiCol_DragDropTarget] = light.to_im();
		style.Colors[ImGuiCol_FrameBg] = dark.to_im();
		style.Colors[ImGuiCol_FrameBgActive] = light.to_im();
		style.Colors[ImGuiCol_FrameBgHovered] = light.to_im();
		style.Colors[ImGuiCol_Header] = light.to_im();
		style.Colors[ImGuiCol_HeaderActive] = light.to_im();
		style.Colors[ImGuiCol_HeaderHovered] = light.to_im();
		style.Colors[ImGuiCol_MenuBarBg] = dark.to_im();
		style.Colors[ImGuiCol_ModalWindowDimBg] = dark.to_im();
		style.Colors[ImGuiCol_NavHighlight] = light.to_im();
		style.Colors[ImGuiCol_NavWindowingDimBg] = light.to_im();
		style.Colors[ImGuiCol_NavWindowingHighlight] = blue.to_im();
		style.Colors[ImGuiCol_PlotHistogram] = Color::white.to_im();
		style.Colors[ImGuiCol_PlotHistogramHovered] = light.to_im();
		style.Colors[ImGuiCol_PlotLines] = Color::white.to_im();
		style.Colors[ImGuiCol_PlotLinesHovered] = light.to_im();
		style.Colors[ImGuiCol_PopupBg] = medium.to_im();
		style.Colors[ImGuiCol_ResizeGrip] = Color::transparent.to_im();
		style.Colors[ImGuiCol_ResizeGripActive] = light.to_im();
		style.Colors[ImGuiCol_ResizeGripHovered] = light.to_im();
		style.Colors[ImGuiCol_ScrollbarBg] = Color::transparent.to_im();
		style.Colors[ImGuiCol_ScrollbarGrab] = light.to_im();
		style.Colors[ImGuiCol_ScrollbarGrabActive] = (0.95f * light + 0.05f * Color::white).to_im();
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = (0.95f * light + 0.05f * Color::white).to_im();
		style.Colors[ImGuiCol_Separator] = light.to_im();
		style.Colors[ImGuiCol_SeparatorActive] = (0.95f * light + 0.05f * Color::white).to_im();
		style.Colors[ImGuiCol_SeparatorHovered] = (0.95f * light + 0.05f * Color::white).to_im();
		style.Colors[ImGuiCol_SliderGrab] = Color(1.f, 1.f, 1.f, 0.25f).to_im();
		style.Colors[ImGuiCol_SliderGrabActive] = Color(1.f, 1.f, 1.f, 0.55f).to_im();
		style.Colors[ImGuiCol_Tab] = medium.to_im();
		style.Colors[ImGuiCol_TabActive] = (0.9f * light + 0.1f * Color::white).to_im();
		style.Colors[ImGuiCol_TabHovered] = (0.8f * light + 0.2f * medium).to_im();
		style.Colors[ImGuiCol_TableBorderLight] = Color::transparent.to_im();
		style.Colors[ImGuiCol_TableBorderStrong] = Color::transparent.to_im();
		style.Colors[ImGuiCol_TableHeaderBg] = Color::transparent.to_im();
		style.Colors[ImGuiCol_TableRowBg] = Color::transparent.to_im();
		style.Colors[ImGuiCol_TableRowBgAlt] = Color::transparent.to_im();
		style.Colors[ImGuiCol_TabUnfocused] = light.to_im();
		style.Colors[ImGuiCol_TabUnfocusedActive] = (0.9f * light + 0.1f * Color::white).to_im();
		style.Colors[ImGuiCol_Text] = Color::white.to_im();
		style.Colors[ImGuiCol_TextDisabled] = Color::white.to_im();
		style.Colors[ImGuiCol_TextSelectedBg] = light.to_im();
		style.Colors[ImGuiCol_TitleBg] = ((light + medium) / 2.f).to_im();
		style.Colors[ImGuiCol_TitleBgActive] = dark.to_im();
		style.Colors[ImGuiCol_TitleBgCollapsed] = ((light + medium) / 2.f).to_im();
		style.Colors[ImGuiCol_WindowBg] = medium.to_im();
	}

	void init()
	{
		init_opengl();
		init_imgui();
		Shader::init();
	}

	void shut_down()
	{
		Shader::default_shader.shader.reset();
		Shader::shaders.clear();

		for (auto& scene : Scene::scenes)
			if (scene.second->to_delete)
				delete scene.second;

		Scene::scenes.clear();
		ImGui::SFML::Shutdown();
	}
}
