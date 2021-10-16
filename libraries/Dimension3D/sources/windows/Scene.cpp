#include "dim/dimension3D.hpp"

namespace dim
{
	std::map<std::string, Scene*> Scene::scenes = {};

	Scene::Scene()
	{
		name = "";
		controller = nullptr;
		camera = nullptr;
		size = Window::initial_size;
		min  = Vector2int::null;
		max = Window::initial_size;
		active = false;
		moving = false;
		resized = false;
		frame_id = 0;
		unique_shader = false;
		binded = false;
		lights.clear();
		post_processing = false;
		to_delete = false;
	}

	Scene::Scene(const Scene& scene)
	{
		*this = scene;
	}

	Scene::Scene(const std::string& name)
	{
		create(name);
	}

	Scene::~Scene()
	{
		delete controller;
		controller = nullptr;

		delete camera;
		camera = nullptr;
	}

	Scene& Scene::operator=(const Scene& other)
	{
		name = other.name + " (copy)";
		frame_buffer.create(other.frame_buffer.get_size());
		render_texture.create(other.render_texture.getSize().x, other.render_texture.getSize().y);
		controller = other.controller->clone();
		camera = other.camera->clone();
		size = other.size;
		min = other.min;
		max = other.max;
		active = false;
		moving = false;
		resized = false;
		frame_id = 0;
		unique_shader = other.unique_shader;
		shader = other.shader;
		binded = false;
		fixed_camera2D = other.fixed_camera2D;
		lights = other.lights;
		post_processing_shader = other.post_processing_shader;
		post_processing = other.post_processing;

		if (post_processing)
			screen.send_data(post_processing_shader, Mesh::screen, DataType::Positions | DataType::TexCoords);

		clear_texture.create(other.clear_texture.getSize().x, other.clear_texture.getSize().y);
		to_delete = other.to_delete;
		camera2D = other.camera2D;

		return *this;
	}

	void Scene::create(const std::string& name)
	{
		this->name = name;
		frame_buffer.create(Window::initial_size);
		render_texture.create(Window::initial_size.x, Window::initial_size.y);
		controller = nullptr;
		camera = nullptr;
		size = Window::initial_size;
		min  = Vector2int::null;
		max = Window::initial_size;
		active = false;
		moving = false;
		resized = false;
		frame_id = 0;
		unique_shader = false;
		binded = false;
		lights.clear();
		post_processing = false;
		clear_texture.create(Window::initial_size.x, Window::initial_size.y);
		to_delete = false;
	}

	void Scene::check_events(const sf::Event& sf_event)
	{
		if (controller != nullptr && camera != nullptr)
			controller->check_events(sf_event, *this, *camera);
	}

	void Scene::update()
	{
		if (frame_id < 5)
			frame_buffer.set_size(size);

		if (frame_id < 5 || resized)
		{
			render_texture.create(size.x, size.y);
			clear_texture.create(size.x, size.y);

			if (camera != nullptr)
				camera->set_resolution(size);

			camera2D.set_resolution(size);
			render_texture.setView(camera2D.get_view());

			fixed_camera2D.set_resolution(size);
		}

		if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && resized)
		{
			frame_buffer.set_size(size);
			resized = false;
		}

		if (controller != nullptr && camera != nullptr)
			controller->update(*this, *camera);

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

	void Scene::bind() const
	{
		frame_buffer.bind();

		if (unique_shader)
			shader.bind();

		binded = true;
	}

	void Scene::unbind() const
	{
		frame_buffer.unbind();

		if (unique_shader)
			shader.unbind();

		binded = false;
	}

	std::string Scene::get_name() const
	{
		return name;
	}

	void Scene::set_name(const std::string& name)
	{
		this->name = name;
	}

	void Scene::set_camera(const Camera& camera)
	{
		this->camera = camera.clone();
		(this->camera)->set_resolution(get_size());
	}

	Camera& Scene::get_camera()
	{
		if (camera == nullptr)
			throw std::runtime_error("There is no camera");

		return *camera;
	}

	void Scene::set_controller(const Controller& controller)
	{
		this->controller = controller.clone();
	}

	Controller& Scene::get_controller()
	{
		if (controller == nullptr)
			throw std::runtime_error("There is no controller");

		return *controller;
	}

	unsigned int Scene::get_width() const
	{
		return size.x;
	}

	unsigned int Scene::get_height() const
	{
		return size.y;
	}

	Vector2int Scene::get_size() const
	{
		return size;
	}

	Vector2int Scene::get_center() const
	{
		return Vector2int((min.x + max.x) / 2, (min.y + max.y) / 2);
	}

	FrameBuffer Scene::get_frame_buffer() const
	{
		return frame_buffer;
	}

	const sf::RenderTexture& Scene::get_render_texture() const
	{
		return render_texture;
	}

	bool Scene::is_active() const
	{
		return active;
	}

	bool Scene::is_moving() const
	{
		return moving;
	}

	bool Scene::is_resized() const
	{
		return resized;
	}

	void Scene::set_shader(const std::string& shader_name)
	{
		shader = Shader::get(shader_name);
		unique_shader = true;
	}

	void Scene::set_shader(const Shader& shader)
	{
		this->shader = shader;
		unique_shader = true;
	}

	Shader Scene::get_shader() const
	{
		return shader;
	}

	void Scene::set_post_processing_shader(const std::string& shader_name)
	{
		post_processing_shader = Shader::get(shader_name);
		screen.send_data(post_processing_shader, Mesh::screen, DataType::Positions | DataType::TexCoords);
		post_processing = true;
	}

	void Scene::set_post_processing_shader(const Shader& shader)
	{
		post_processing_shader = shader;
		screen.send_data(post_processing_shader, Mesh::screen, DataType::Positions | DataType::TexCoords);
		post_processing = true;
	}

	Shader Scene::get_post_processing_shader() const
	{
		return post_processing_shader;
	}

	bool Scene::is_in(const Vector2& position) const
	{
		return position.x >= min.x && position.x <= max.x && position.y >= min.y && position.y <= max.y;
	}

	Vector2 Scene::get_2d_world_mouse_position()
	{
		Vector2 pos;
		pos.x = (sf::Mouse::getPosition(Window::get_window()).x - get_center().x) * camera2D.get_zoom() + camera2D.get_view().getCenter().x;
		pos.y = (sf::Mouse::getPosition(Window::get_window()).y - get_center().y) * camera2D.get_zoom() + camera2D.get_view().getCenter().y;
		return pos;
	}

	void Scene::add_light(const Light& light)
	{
		lights.push_back(light.clone());
	}

	void Scene::clear_lights()
	{
		for (auto& light : lights)
		{
			delete light;
			light = nullptr;
		}

		lights.clear();
	}

	void Scene::clear(const Color& color)
	{
		if (!binded)
			frame_buffer.bind();

		frame_buffer.clear(color);
		frame_buffer.unbind();

		render_texture.clear(color.to_sf());
		clear_texture.clear();

		if (binded)
			frame_buffer.bind();
	}

	void Scene::draw(const sf::Drawable& drawable, bool fixed)
	{
		Window::set_cull_face(false);

		if (fixed)
			render_texture.setView(fixed_camera2D.get_view());

		render_texture.draw(drawable);

		if (fixed)
			render_texture.setView(camera2D.get_view());
	}

	void Scene::draw(const Object& object, DrawType draw_type)
	{
		Window::set_cull_face(true);

		if (!binded)
			frame_buffer.bind();

		if (draw_type == DrawType::Default)
			object.draw(camera, lights, object.mesh.draw_type, unique_shader);

		else
			object.draw(camera, lights, draw_type, unique_shader);

		if (!binded)
			frame_buffer.unbind();
	}

	void Scene::draw(const VertexBuffer& vertex_buffer, DrawType draw_type)
	{
		Window::set_cull_face(true);

		if (!binded)
		{
			frame_buffer.bind();

			if (unique_shader)
				shader.bind();
		}

		vertex_buffer.draw(draw_type);

		if (!binded)
		{
			frame_buffer.unbind();

			if (unique_shader)
				shader.unbind();
		}
	}

	void Scene::display()
	{
		if (post_processing)
		{
			if (binded && unique_shader)
				shader.unbind();

			if (!binded)
				frame_buffer.bind();

			post_processing_shader.bind();
			frame_buffer.get_texture().bind();
			screen.bind();

			post_processing_shader.send_uniform("u_texture", frame_buffer.get_texture());

			screen.draw();

			screen.unbind();
			frame_buffer.get_texture().unbind();
			post_processing_shader.unbind();

			if (!binded)
				frame_buffer.unbind();
		}

		if (binded)
			frame_buffer.unbind();

		// SFML

		render_texture.display();

		// ImGui

		ImGui::SetNextWindowSizeConstraints(ImVec2(50.f, 50.f), ImVec2(100000.f, 100000.f));
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse;

		ImGui::Begin(name.data(), NULL, window_flags);

		Vector2int viewport_panel_size = ImGui::GetContentRegionAvail();
		Vector2int temp = size;

		if (frame_id == 0 || size.x != viewport_panel_size.x || size.y != viewport_panel_size.y)
		{
			size.x = viewport_panel_size.x;
			size.y = viewport_panel_size.y;

			resized = true;
		}

		Vector2int v_min = ImGui::GetWindowContentRegionMin();
		Vector2int v_max = ImGui::GetWindowContentRegionMax();
		Vector2int v_pos = ImGui::GetWindowPos();

		moving = min != (v_min + v_pos) || max != (v_max + v_pos);

		min = v_min + v_pos;
		max = v_max + v_pos;

		active = ImGui::IsWindowFocused();

		ImGui::SetCursorPos(ImVec2(8.f, 27.f));
		ImGui::Image(frame_buffer.get_texture().get_id(), ImVec2(static_cast<float>(temp.x), static_cast<float>(temp.y)), ImVec2(0.f, 1.f), ImVec2(1.f, 0.f));
		ImGui::SetCursorPos(ImVec2(8.f, 27.f));
		ImGui::Image(render_texture.getTexture().getNativeHandle(),
			ImVec2(static_cast<float>(render_texture.getTexture().getSize().x),
			static_cast<float>(render_texture.getTexture().getSize().y)), ImVec2(0.f, 1.f), ImVec2(1.f, 0.f));

		ImGui::End();

		if (binded)
		{
			frame_buffer.bind();

			if (unique_shader)
				shader.bind();
		}

		frame_id++;
	}

	void Scene::add(Scene& scene)
	{
		if (!scenes.insert(std::make_pair(scene.name, &scene)).second)
			throw std::invalid_argument("This name is already used");
	}

	void Scene::add(const std::string& name)
	{
		if (!scenes.insert(std::make_pair(name, new Scene(name))).second)
			throw std::invalid_argument("This name is already used");

		get(name).to_delete = true;
	}

	void Scene::remove(const std::string& name)
	{
		try
		{
			Scene*& scene = scenes.at(name);

			if (scene->to_delete)
			{
				delete scene;
				scene = nullptr;
			}
		}

		catch (const std::out_of_range&)
		{
			throw std::invalid_argument("This name does not exit");
		}

		if (!scenes.erase(name))
			throw std::invalid_argument("This name does not exit");
	}

	Scene& Scene::get(const std::string& name)
	{
		try
		{
			return *scenes.at(name);
		}

		catch (const std::out_of_range&)
		{
			throw std::invalid_argument("This name does not exit");
		}
	}

	void Scene::check_all_events(const sf::Event& sf_event)
	{
		for (auto& scene : scenes)
			scene.second->check_events(sf_event);
	}

	void Scene::update_all()
	{
		for (auto& scene : scenes)
			scene.second->update();
	}

	void Scene::clear_all()
	{
		for (auto& scene : scenes)
			scene.second->clear();
	}

	void Scene::display_all()
	{
		for (auto& scene : scenes)
			scene.second->display();
	}
}
