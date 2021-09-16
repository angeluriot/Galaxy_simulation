#include "dim/dimension3D.hpp"

namespace dim
{
	Camera::Camera()
	{
		position = Vector3(0.f, 0.f, 5.f);
		direction = glm::vec3(0.f, 0.f, -1.f);
		view = glm::lookAt(position.to_glm(), (position + direction).to_glm(), glm::vec3(0.f, 1.f, 0.f));
		yaw = -90.f;
		pitch = 0.f;
	}

	glm::mat4 Camera::get_matrix() const
	{
		return projection * view;
	}

	Vector3 Camera::get_position() const
	{
		return position;
	}

	void Camera::set_position(const Vector3& position)
	{
		this->position = position;
		view = glm::lookAt(position.to_glm(), (position + direction).to_glm(), glm::vec3(0.f, 1.f, 0.f));
	}

	void Camera::set_position(float x, float y, float z)
	{
		set_position(Vector3(x, y, z));
	}

	Vector3 Camera::get_direction() const
	{
		return direction;
	}

	void Camera::set_direction(const Vector3& direction)
	{
		if (direction != Vector3::null)
		{
			this->direction = normalize(direction);
			pitch = asin(-this->direction.y);
			yaw = atan2(this->direction.x, this->direction.z);
			view = glm::lookAt(position.to_glm(), (position + direction).to_glm(), glm::vec3(0.f, 1.f, 0.f));
		}
	}

	void Camera::set_direction(float yaw, float pitch)
	{
		this->yaw = yaw;
		this->pitch = pitch;

		if (this->pitch > 89.f)
			this->pitch = 89.f;

		if (this->pitch < -89.f)
			this->pitch = -89.f;

		direction.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		direction.y = sin(glm::radians(this->pitch));
		direction.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
		direction.normalize();
		view = glm::lookAt(position.to_glm(), (position + direction).to_glm(), glm::vec3(0.f, 1.f, 0.f));
	}

	float Camera::get_yaw() const
	{
		return yaw;
	}

	void Camera::set_yaw(float yaw)
	{
		set_direction(yaw, pitch);
	}

	float Camera::get_pitch() const
	{
		return pitch;
	}

	void Camera::set_pitch(float pitch)
	{
		set_direction(yaw, pitch);
	}

	float Camera::get_near() const
	{
		return near;
	}

	float Camera::get_far() const
	{
		return far;
	}
}
