#include "dim/dimension3D.hpp"

namespace dim
{
	FlyController::FlyController(float sensitivity, float speed)
	{
		this->sensitivity = std::max(sensitivity, 0.f);
		this->speed = std::max(speed, 0.f);
		look_active = true;
		move_active = true;
		moving = false;
		forward = default_forward;
		left = default_left;
		right = default_right;
		backward = default_backward;
		up = default_up;
		down = default_down;
	}

	Controller* FlyController::clone() const
	{
		return new FlyController(*this);
	}

	void FlyController::move(Camera& camera) const
	{
		if (sf::Keyboard::isKeyPressed(left))
			camera.position -= glm::normalize(glm::cross(camera.direction.to_glm(), glm::vec3(0.f, 1.f, 0.f))) * speed * Window::get_elapsed_time();

		if (sf::Keyboard::isKeyPressed(right))
			camera.position += glm::normalize(glm::cross(camera.direction.to_glm(), glm::vec3(0.f, 1.f, 0.f))) * speed * Window::get_elapsed_time();

		if (sf::Keyboard::isKeyPressed(forward))
			camera.position += glm::normalize(glm::vec3(camera.direction.to_glm().x, 0.f, camera.direction.to_glm().z)) * speed * Window::get_elapsed_time();

		if (sf::Keyboard::isKeyPressed(backward))
			camera.position -= glm::normalize(glm::vec3(camera.direction.to_glm().x, 0.f, camera.direction.to_glm().z)) * speed * Window::get_elapsed_time();

		if (sf::Keyboard::isKeyPressed(up))
			camera.position += Vector3(0.f, 1.f, 0.f) * speed * Window::get_elapsed_time();

		if (sf::Keyboard::isKeyPressed(down))
			camera.position -= Vector3(0.f, 1.f, 0.f) * speed * Window::get_elapsed_time();

		camera.view = glm::lookAt(camera.position.to_glm(), (camera.position + camera.direction).to_glm(), glm::vec3(0.f, 1.f, 0.f));
	}

	void FlyController::look(Scene& scene, Camera& camera) const
	{
		float new_yaw = camera.yaw + (sf::Mouse::getPosition(Window::get_window()).x - scene.get_center().x) * sensitivity;
		float new_pitch = camera.pitch - (sf::Mouse::getPosition(Window::get_window()).y - scene.get_center().y) * sensitivity;

		camera.set_direction(new_yaw, new_pitch);
	}

	void FlyController::look(Camera& camera) const
	{
		float new_yaw = camera.yaw + (sf::Mouse::getPosition(Window::get_window()).x - (Window::get_size() / 2).x) * sensitivity;
		float new_pitch = camera.pitch - (sf::Mouse::getPosition(Window::get_window()).y - (Window::get_size() / 2).y) * sensitivity;

		camera.set_direction(new_yaw, new_pitch);
	}

	Controller::Type FlyController::get_type() const
	{
		return Type::Fly;
	}

	void FlyController::check_events(const sf::Event& sf_event, Scene& scene, Camera& camera)
	{
		if (move_active || look_active)
		{
			if (!moving && sf_event.type == sf::Event::MouseButtonReleased && scene.is_in(sf::Mouse::getPosition(Window::get_window())))
			{
				moving = true;
				sf::Mouse::setPosition(scene.get_center().to_sf_int(), dim::Window::get_window());
				Window::get_window().setMouseCursorVisible(false);
				ImGui::SetMouseCursor(ImGuiMouseCursor_None);
			}

			if (moving && sf_event.type == sf::Event::KeyReleased && sf_event.key.code == sf::Keyboard::Escape)
			{
				moving = false;
				sf::Mouse::setPosition(scene.get_center().to_sf_int(), dim::Window::get_window());
				Window::get_window().setMouseCursorVisible(true);
			}
		}
	}

	void FlyController::check_events(const sf::Event& sf_event, Camera& camera)
	{
		if (move_active || look_active)
		{
			if (!moving && sf_event.type == sf::Event::MouseButtonReleased && Window::is_in(sf::Mouse::getPosition(Window::get_window())))
			{
				moving = true;
				sf::Mouse::setPosition((Window::get_size() / 2).to_sf_int(), Window::get_window());
				Window::get_window().setMouseCursorVisible(false);
				ImGui::SetMouseCursor(ImGuiMouseCursor_None);
			}

			if (moving && sf_event.type == sf::Event::KeyReleased && sf_event.key.code == sf::Keyboard::Escape)
			{
				moving = false;
				sf::Mouse::setPosition((Window::get_size() / 2).to_sf_int(), Window::get_window());
				Window::get_window().setMouseCursorVisible(true);
			}
		}
	}

	void FlyController::update(Scene& scene, Camera& camera)
	{
		if ((move_active || look_active) && moving)
		{
			if (move_active)
				move(camera);

			if (look_active)
				look(scene, camera);

			sf::Mouse::setPosition(scene.get_center().to_sf_int(), Window::get_window());
			ImGui::SetMouseCursor(ImGuiMouseCursor_None);
		}
	}

	void FlyController::update(Camera& camera)
	{
		if ((move_active || look_active) && moving)
		{
			if (move_active)
				move(camera);

			if (look_active)
				look(camera);

			sf::Mouse::setPosition((Window::get_size() / 2).to_sf_int(), Window::get_window());
			ImGui::SetMouseCursor(ImGuiMouseCursor_None);
		}
	}

	void FlyController::set_controls(sf::Keyboard::Key forward, sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key backward, sf::Keyboard::Key up, sf::Keyboard::Key down)
	{
		this->forward = forward;
		this->left = left;
		this->right = right;
		this->backward = backward;
		this->up = up;
		this->down = down;
	}
}
