#include "dim/dimension3D.hpp"

namespace dim
{
	sf::RenderWindow*	Window::window					= nullptr;
	float				Window::screen_coef				= 1.f;
	sf::Clock			Window::clock;
	float				Window::elapsed_time			= 1.f / 60.f;
	float				Window::thickness				= 1.f;
	const Color			Window::background				= Color(13.f / 255.f, 17.f / 255.f, 23.f / 255.f);
	const Vector2int	Window::initial_size			= Vector2int(100, 100);
	bool				Window::running					= false;
	bool				Window::cull_face				= true;
	Controller*			Window::controller				= nullptr;
	Camera*				Window::camera					= nullptr;
	bool				Window::unique_shader			= false;
	Shader				Window::shader;
	bool				Window::binded					= false;
	Camera2D			Window::fixed_camera2D;
	std::vector<Light*>	Window::lights					= {};
	FrameBuffer			Window::frame_buffer;
	Shader				Window::post_processing_shader;
	bool				Window::post_processing			= false;
	VertexBuffer		Window::screen;
	Camera2D			Window::camera2D;

	void Window::open(const std::string& name, float screen_ratio, const std::string& icon_path)
	{
		unsigned int width = static_cast<unsigned int>(clamp(screen_ratio, 0.f, 1.f) * static_cast<float>(sf::VideoMode::getDesktopMode().width));
		unsigned int height = static_cast<unsigned int>(clamp(screen_ratio, 0.f, 1.f) * static_cast<float>(sf::VideoMode::getDesktopMode().height));

		open(name, width, height, icon_path);
	}

	void Window::open(const std::string& name, unsigned int width, unsigned int height, const std::string& icon_path)
	{
		width = std::max(width, static_cast<unsigned int>(initial_size.x));
		height = std::max(height, static_cast<unsigned int>(initial_size.y));

		screen_coef = width / 1920.f;

		sf::ContextSettings settings;
		settings.depthBits = 24;
		settings.stencilBits = 8;
		settings.antialiasingLevel = 8;
		settings.majorVersion = 4;
		settings.minorVersion = 3;

		window = new sf::RenderWindow(sf::VideoMode(width, height), name, sf::Style::Default, settings);

		if (icon_path != "")
		{
			sf::Image icon;

			if (icon.loadFromFile(icon_path))
				window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
		}

		init();
		frame_buffer.create(width, height);
		running = true;
	}

	void Window::open(const std::string& name, const Vector2int& size, const std::string& icon_path)
	{
		open(name, size.x, size.y, icon_path);
	}

	sf::RenderWindow& Window::get_window()
	{
		return *window;
	}

	Vector2int Window::get_position()
	{
		return window->getPosition();
	}

	unsigned int Window::get_width()
	{
		return window->getSize().x;
	}

	unsigned int Window::get_height()
	{
		return window->getSize().y;
	}

	Vector2int Window::get_size()
	{
		return sf::Vector2i(window->getSize());
	}

	void Window::bind()
	{
		if (post_processing)
			frame_buffer.bind();

		if (unique_shader)
			shader.bind();

		binded = true;
	}

	void Window::unbind()
	{
		if (post_processing)
			frame_buffer.unbind();

		if (unique_shader)
			shader.unbind();

		binded = false;
	}

	void Window::set_camera(const Camera& camera)
	{
		Window::camera = camera.clone();
		Window::camera->set_resolution(get_size());
	}

	Camera& Window::get_camera()
	{
		if (camera == nullptr)
			throw std::runtime_error("There is no camera");

		return *camera;
	}

	void Window::set_controller(const Controller& controller)
	{
		Window::controller = controller.clone();
	}

	Controller& Window::get_controller()
	{
		if (controller == nullptr)
			throw std::runtime_error("There is no controller");

		return *controller;
	}

	void Window::set_shader(const std::string& shader_name)
	{
		shader = Shader::get(shader_name);
		unique_shader = true;
	}

	void Window::set_shader(const Shader& shader)
	{
		Window::shader = shader;
		unique_shader = true;
	}

	Shader Window::get_shader()
	{
		return shader;
	}

	FrameBuffer Window::get_frame_buffer()
	{
		return frame_buffer;
	}

	void Window::set_post_processing_shader(const std::string& shader_name)
	{
		post_processing_shader = Shader::get(shader_name);
		screen.send_data(post_processing_shader, Mesh::screen, DataType::Positions | DataType::TexCoords);
		post_processing = true;
	}

	void Window::set_post_processing_shader(const Shader& shader)
	{
		post_processing_shader = shader;
		screen.send_data(post_processing_shader, Mesh::screen, DataType::Positions | DataType::TexCoords);
		post_processing = true;
	}

	Shader Window::get_post_processing_shader()
	{
		return post_processing_shader;
	}

	Vector2 Window::get_2d_world_mouse_position()
	{
		Vector2 pos;
		pos.x = (sf::Mouse::getPosition(Window::get_window()).x - (get_size() / 2).x) * camera2D.get_zoom() + camera2D.get_view().getCenter().x;
		pos.y = (sf::Mouse::getPosition(Window::get_window()).y - (get_size() / 2).y) * camera2D.get_zoom() + camera2D.get_view().getCenter().y;
		return pos;
	}

	void Window::add_light(const Light& light)
	{
		lights.push_back(light.clone());
	}

	void Window::clear_lights()
	{
		for (auto& light : lights)
		{
			delete light;
			light = nullptr;
		}

		lights.clear();
	}

	void Window::clear(const Color& color)
	{
		if (binded)
			frame_buffer.unbind();

		window->clear(color.to_sf());

		glViewport(0, 0, Window::get_width(), Window::get_height());
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);
		glCullFace(GL_FRONT);
		glFrontFace(GL_CW);

		if (cull_face)
			glEnable(GL_CULL_FACE);

		else
			glDisable(GL_CULL_FACE);

		glPointSize(thickness);
		glLineWidth(thickness);
		glEnable(GL_POINT_SMOOTH);
		glEnable(GL_LINE_SMOOTH);

		ImGui::SFML::Update(dim::Window::get_window(), sf::seconds(Window::elapsed_time));

		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;

		if (is_on_border(sf::Mouse::getPosition(Window::get_window())))
			ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
		else
			ImGui::GetIO().ConfigFlags &= ~ImGuiConfigFlags_NoMouseCursorChange;

		ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly = true;

		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);

		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
		ImGui::Begin("InvisibleWindow", NULL, windowFlags);
		ImGui::PopStyleVar(3);

		ImGuiID dockSpaceId = ImGui::GetID("InvisibleWindowDockSpace");

		ImGui::DockSpace(dockSpaceId, ImVec2(0.f, 0.f), ImGuiDockNodeFlags_PassthruCentralNode);
		ImGui::End();

		if (binded)
			frame_buffer.bind();

		if (post_processing)
		{
			if (!binded)
				frame_buffer.bind();

			frame_buffer.clear(color);

			if (!binded)
				frame_buffer.unbind();
		}
	}

	bool Window::poll_event(sf::Event& sf_event)
	{
		return window->pollEvent(sf_event);
	}

	void Window::check_events(const sf::Event& sf_event)
	{
		static int frame_id = 0;
		ImGui::SFML::ProcessEvent(sf_event);

		if (sf_event.type == sf::Event::Resized || frame_id < 5)
		{
			if (window->getSize().x < static_cast<unsigned int>(initial_size.x))
				window->setSize(sf::Vector2u(initial_size.x, window->getSize().y));

			if (window->getSize().y < static_cast<unsigned int>(initial_size.y))
				window->setSize(sf::Vector2u(window->getSize().x, initial_size.y));

			screen_coef = window->getSize().x / 1920.f;

			if (post_processing)
				frame_buffer.set_size(get_size());

			if (camera != nullptr)
				camera->set_resolution(get_size());

			camera2D.set_resolution(get_size());
			window->setView(camera2D.get_view());
			fixed_camera2D.set_resolution(get_size());
		}

		if (controller != nullptr && camera != nullptr)
			controller->check_events(sf_event, *camera);

		if (sf_event.type == sf::Event::Closed)
			running = false;

		frame_id++;
	}

	void Window::update()
	{
		if (controller != nullptr && camera != nullptr)
			controller->update(*camera);

		if (unique_shader)
		{
			if (!binded)
				shader.bind();

			if (camera != nullptr)
				shader.send_uniform("u_camera", camera->get_position());

			else
				shader.send_uniform("u_camera", Vector3(0.f, 0.f, -1.f));

			shader.send_uniform("u_light", lights);

			if (!binded)
				shader.unbind();
		}
	}

	void Window::draw(const sf::Drawable& drawable, bool fixed)
	{
		Window::set_cull_face(false);

		if (fixed)
			window->setView(fixed_camera2D.get_view());

		window->draw(drawable);

		if (fixed)
			window->setView(camera2D.get_view());
	}

	void Window::draw(const Object& object, DrawType draw_type)
	{
		Window::set_cull_face(true);

		if (!binded && post_processing)
			frame_buffer.bind();

		if (draw_type == DrawType::Default)
			object.draw(camera, lights, object.mesh.draw_type, unique_shader);

		else
			object.draw(camera, lights, draw_type, unique_shader);

		if (!binded && post_processing)
			frame_buffer.unbind();
	}

	void Window::draw(const VertexBuffer& vertex_buffer, DrawType draw_type)
	{
		Window::set_cull_face(true);

		if (!binded)
		{
			if (post_processing)
				frame_buffer.bind();

			if (unique_shader)
				shader.bind();
		}

		vertex_buffer.draw(draw_type);

		if (!binded)
		{
			if (post_processing)
				frame_buffer.unbind();

			if (unique_shader)
				shader.unbind();
		}
	}

	void Window::display()
	{
		if (binded)
		{
			if (post_processing)
				frame_buffer.unbind();

			if (unique_shader)
				shader.unbind();
		}

		if (post_processing)
		{
			post_processing_shader.bind();
			frame_buffer.get_texture().bind();
			screen.bind();

			post_processing_shader.send_uniform("u_texture", frame_buffer.get_texture());

			screen.draw();

			screen.unbind();
			frame_buffer.get_texture().unbind();
			post_processing_shader.unbind();
		}

		ImGui::SFML::Render(*window);
		window->display();
		elapsed_time = clock.restart().asSeconds();

		if (binded)
		{
			if (post_processing)
				frame_buffer.bind();

			if (unique_shader)
				shader.bind();
		}
	}

	void Window::close()
	{
		if (window != NULL)
		{
			window->close();
			delete window;
			window = nullptr;
		}

		delete controller;
		controller = nullptr;
		delete camera;
		camera = nullptr;

		shut_down();
		running = false;
	}

	int Window::hd_to_window(int position)
	{
		return static_cast<int>(round(position * screen_coef));
	}

	Vector2int Window::hd_to_window(int x, int y)
	{
		return Vector2int(x, y) * screen_coef;
	}

	Vector2int Window::hd_to_window(const Vector2int& position)
	{
		return position * screen_coef;
	}

	void Window::set_thickness(float thickness)
	{
		if (thickness >= 0.f && thickness != Window::thickness)
		{
			glPointSize(thickness);
			glLineWidth(thickness);
			Window::thickness = thickness;
		}
	}

	void Window::set_cull_face(bool enable)
	{
		if (!cull_face && enable)
		{
			glEnable(GL_CULL_FACE);
			cull_face = true;
		}

		else if (cull_face && !enable)
		{
			glDisable(GL_CULL_FACE);
			cull_face = false;
		}
	}

	float Window::get_elapsed_time()
	{
		return elapsed_time;
	}

	bool Window::is_in(const Vector2& position)
	{
		return position.x >= 0 && position.x <= Window::get_width() && position.y >= 0 && position.y <= Window::get_height();
	}

	bool Window::is_on_border(const Vector2& position)
	{
		return (position.x >= -2 && position.x <= 2) || (position.x >= Window::get_width() - 2 && position.x <= Window::get_width() + 2) ||
			(position.y >= -2 && position.y <= 2) || (position.y >= Window::get_height() - 2 && position.y <= Window::get_height() + 2);
	}

	sf::RenderWindow& get_window()
	{
		return Window::get_window();
	}

	int hd_to_window(int position)
	{
		return Window::hd_to_window(position);
	}

	Vector2int hd_to_window(int x, int y)
	{
		return Window::hd_to_window(x, y);
	}

	Vector2int hd_to_window(const Vector2int& position)
	{
		return Window::hd_to_window(position);
	}
}
