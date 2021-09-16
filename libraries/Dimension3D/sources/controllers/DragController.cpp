#include "dim/dimension3D.hpp"

namespace dim
{
	DragController::DragController(float sensitivity, float speed)
	{
		this->sensitivity = std::max(sensitivity, 0.f);
		this->speed = std::max(speed, 0.f);
		look_active = true;
		move_active = true;
		prev_mouse_pos = sf::Mouse::getPosition(Window::get_window());
		prev_mouse_click = false;
		move_forbidden = false;
	}

	Controller* DragController::clone() const
	{
		return new DragController(*this);
	}

	Controller::Type DragController::get_type() const
	{
		return Type::Drag;
	}

	void DragController::check_events(const sf::Event& sf_event, Scene& scene, Camera& camera)
	{
		if (move_active && sf_event.type == sf::Event::MouseWheelMoved && scene.is_in(sf::Mouse::getPosition(Window::get_window())))
		{
			camera.position += normalize(camera.direction) * speed * static_cast<float>(sf_event.mouseWheel.delta);

			if (camera.get_type() == Camera::Type::Orthographic)
				static_cast<OrthographicCamera&>(camera).zoom(1.f + static_cast<float>(sf_event.mouseWheel.delta) * speed * 0.5f);

			camera.view = glm::lookAt(camera.position.to_glm(), (camera.position + camera.direction).to_glm(), glm::vec3(0.f, 1.f, 0.f));

			Vector2 pos = scene.get_2d_world_mouse_position();
			scene.camera2D.zoom(1.f - (speed * static_cast<float>(sf_event.mouseWheel.delta) * 0.5f));
			scene.camera2D.set_position((Vector2(scene.camera2D.get_view().getCenter()) - (scene.get_2d_world_mouse_position() - pos)) / scene.camera2D.get_zoom());
			scene.render_texture.setView(scene.camera2D.get_view());
		}
	}

	void DragController::check_events(const sf::Event& sf_event, Camera& camera)
	{
		if (move_active && sf_event.type == sf::Event::MouseWheelMoved && Window::is_in(sf::Mouse::getPosition(Window::get_window())))
		{
			camera.position += normalize(camera.direction) * speed * static_cast<float>(sf_event.mouseWheel.delta);

			if (camera.get_type() == Camera::Type::Orthographic)
				static_cast<OrthographicCamera&>(camera).zoom(1.f + static_cast<float>(sf_event.mouseWheel.delta) * speed * 0.5f);

			camera.view = glm::lookAt(camera.position.to_glm(), (camera.position + camera.direction).to_glm(), glm::vec3(0.f, 1.f, 0.f));

			Vector2 pos = Window::get_2d_world_mouse_position();
			Window::camera2D.zoom(1.f - (speed * static_cast<float>(sf_event.mouseWheel.delta) * 0.5f));
			Window::camera2D.set_position((Vector2(Window::camera2D.get_view().getCenter()) - (Window::get_2d_world_mouse_position() - pos)) / Window::camera2D.get_zoom());
			Window::get_window().setView(Window::camera2D.get_view());
		}
	}

	void DragController::update(Scene& scene, Camera& camera)
	{
		if ((!prev_mouse_click && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && (!scene.is_in(sf::Mouse::getPosition(Window::get_window())) ||
			!scene.is_active())) || scene.is_moving())
			move_forbidden = true;

		else if (!scene.is_moving() && prev_mouse_click && !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			move_forbidden = false;

		if (!scene.is_moving() && scene.is_active() && scene.is_in(sf::Mouse::getPosition(Window::get_window())))
			move_forbidden = false;

		if (!scene.is_active())
			move_forbidden = true;

		if (look_active && !move_forbidden && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			Vector2 move = Vector2(sf::Mouse::getPosition()) - prev_mouse_pos;

			glm::vec3 right = glm::normalize(glm::cross(camera.direction.to_glm(), glm::vec3(0.f, 1.f, 0.f)));

			camera.position -= right * sensitivity * move.x * (4.f / scene.size.y);
			camera.position -= glm::normalize(glm::cross(camera.direction.to_glm(), right)) * sensitivity * move.y * (4.f / scene.size.y);
			camera.view = glm::lookAt(camera.position.to_glm(), (camera.position + camera.direction).to_glm(), glm::vec3(0.f, 1.f, 0.f));

			scene.camera2D.move(-move * sensitivity * scene.camera2D.get_zoom());
			scene.render_texture.setView(scene.camera2D.get_view());
		}

		prev_mouse_pos = sf::Mouse::getPosition();
		prev_mouse_click = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	}

	void DragController::update(Camera& camera)
	{
		if (!prev_mouse_click && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !Window::is_in(sf::Mouse::getPosition(Window::get_window())))
			move_forbidden = true;

		else if (prev_mouse_click && !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			move_forbidden = false;

		if (look_active && !move_forbidden && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			Vector2 move = Vector2(sf::Mouse::getPosition()) - prev_mouse_pos;

			glm::vec3 right = glm::normalize(glm::cross(camera.direction.to_glm(), glm::vec3(0.f, 1.f, 0.f)));

			camera.position -= right * sensitivity * move.x * (4.f / Window::get_size().y);
			camera.position -= glm::normalize(glm::cross(camera.direction.to_glm(), right)) * sensitivity * move.y * (4.f / Window::get_size().y);
			camera.view = glm::lookAt(camera.position.to_glm(), (camera.position + camera.direction).to_glm(), glm::vec3(0.f, 1.f, 0.f));

			Window::camera2D.move(-move * sensitivity * Window::camera2D.get_zoom());
			Window::get_window().setView(Window::camera2D.get_view());
		}

		prev_mouse_pos = sf::Mouse::getPosition();
		prev_mouse_click = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	}
}
