#include "dim/dimension3D.hpp"

namespace dim
{
	OrbitController::OrbitController(const Vector3& center, float sensitivity, float speed)
	{
		prev_center = Vector3::null;
		this->center = center;
		center_changed = true;
		this->sensitivity = std::max(sensitivity, 0.f);
		this->speed = std::max(speed, 0.f);
		look_active = true;
		move_active = true;
		prev_mouse_pos = sf::Mouse::getPosition();
		prev_mouse_click = false;
		rotation_forbidden = false;
	}

	Controller* OrbitController::clone() const
	{
		return new OrbitController(*this);
	}

	Controller::Type OrbitController::get_type() const
	{
		return Type::Orbit;
	}

	void OrbitController::check_events(const sf::Event& sf_event, Scene& scene, Camera& camera)
	{
		if (center_changed)
		{
			camera.position += center - prev_center;
			camera.view = glm::lookAt(camera.position.to_glm(), (camera.position + normalize(center - camera.position)).to_glm(), glm::vec3(0.f, 1.f, 0.f));
			center_changed = false;
		}

		if (move_active && sf_event.type == sf::Event::MouseWheelMoved && scene.is_in(sf::Mouse::getPosition(Window::get_window())))
		{
			camera.position -= center;
			camera.position.set_norm(std::max(camera.position.get_norm() - static_cast<float>(sf_event.mouseWheel.delta) * speed, 0.01f));
			camera.position += center;

			if (camera.get_type() == Camera::Type::Orthographic)
				static_cast<OrthographicCamera&>(camera).zoom(1.f + static_cast<float>(sf_event.mouseWheel.delta) * speed * 0.5f);

			camera.view = glm::lookAt(camera.position.to_glm(), (camera.position + normalize(center - camera.position)).to_glm(), glm::vec3(0.f, 1.f, 0.f));
		}
	}

	void OrbitController::check_events(const sf::Event& sf_event, Camera& camera)
	{
		if (center_changed)
		{
			camera.position += center - prev_center;
			camera.view = glm::lookAt(camera.position.to_glm(), (camera.position + normalize(center - camera.position)).to_glm(), glm::vec3(0.f, 1.f, 0.f));
			center_changed = false;
		}

		if (move_active && sf_event.type == sf::Event::MouseWheelMoved && Window::is_in(sf::Mouse::getPosition(Window::get_window())))
		{
			camera.position -= center;
			camera.position.set_norm(std::max(camera.position.get_norm() - static_cast<float>(sf_event.mouseWheel.delta) * speed, 0.01f));
			camera.position += center;

			if (camera.get_type() == Camera::Type::Orthographic)
				static_cast<OrthographicCamera&>(camera).zoom(1.f + static_cast<float>(sf_event.mouseWheel.delta) * speed * 0.5f);

			camera.view = glm::lookAt(camera.position.to_glm(), (camera.position + normalize(center - camera.position)).to_glm(), glm::vec3(0.f, 1.f, 0.f));
		}
	}

	void OrbitController::update(Scene& scene, Camera& camera)
	{
		if (center_changed)
		{
			camera.position += center - prev_center;
			camera.view = glm::lookAt(camera.position.to_glm(), (camera.position + normalize(center - camera.position)).to_glm(), glm::vec3(0.f, 1.f, 0.f));
			center_changed = false;
		}

		if ((!prev_mouse_click && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && (!scene.is_in(sf::Mouse::getPosition(Window::get_window())) ||
			!scene.is_active())) || scene.is_moving())
			rotation_forbidden = true;

		else if (!scene.is_moving() && prev_mouse_click && !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			rotation_forbidden = false;

		if (!scene.is_moving() && scene.is_active() && scene.is_in(sf::Mouse::getPosition(Window::get_window())))
			rotation_forbidden = false;

		if (!scene.is_active())
			rotation_forbidden = true;

		if (look_active && !rotation_forbidden && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			Vector2 move = Vector2(sf::Mouse::getPosition()) - prev_mouse_pos;

			camera.position -= center;
			camera.position.set_theta(camera.position.get_theta() - move.x * sensitivity);
			camera.position.set_phi(std::min(std::max(camera.position.get_phi() - move.y * sensitivity, 0.01f), pi - 0.01f));
			camera.position += center;

			camera.view = glm::lookAt(camera.position.to_glm(), (camera.position + normalize(center - camera.position)).to_glm(), glm::vec3(0.f, 1.f, 0.f));
		}

		prev_mouse_pos = sf::Mouse::getPosition();
		prev_mouse_click = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	}

	void OrbitController::update(Camera& camera)
	{
		if (center_changed)
		{
			camera.position += center - prev_center;
			camera.view = glm::lookAt(camera.position.to_glm(), (camera.position + normalize(center - camera.position)).to_glm(), glm::vec3(0.f, 1.f, 0.f));
			center_changed = false;
		}

		if (!prev_mouse_click && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !Window::is_in(sf::Mouse::getPosition(Window::get_window())))
			rotation_forbidden = true;

		else if (prev_mouse_click && !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			rotation_forbidden = false;

		if (look_active && !rotation_forbidden && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			Vector2 move = Vector2(sf::Mouse::getPosition()) - prev_mouse_pos;

			camera.position -= center;
			camera.position.set_theta(camera.position.get_theta() - move.x * sensitivity);
			camera.position.set_phi(std::min(std::max(camera.position.get_phi() - move.y * sensitivity, 0.01f), pi - 0.01f));
			camera.position += center;

			camera.view = glm::lookAt(camera.position.to_glm(), (camera.position + normalize(center - camera.position)).to_glm(), glm::vec3(0.f, 1.f, 0.f));
		}

		prev_mouse_pos = sf::Mouse::getPosition();
		prev_mouse_click = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
	}

	void OrbitController::set_center(float x, float y, float z)
	{
		set_center(Vector3(x, y, z));
	}

	void OrbitController::set_center(const Vector3& center)
	{
		prev_center = this->center;
		this->center  = center;
		center_changed = true;
	}

	Vector3 OrbitController::get_center() const
	{
		return center;
	}
}
