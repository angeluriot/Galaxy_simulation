#include "dim/dimension3D.hpp"

namespace dim
{
	PerspectiveCamera::PerspectiveCamera(float fov, float near, float far) : Camera()
	{
		this->fov = (fov > 0.f ? fov : default_fov);
		this->near = (near > 0.f ? near : default_near);
		this->far = (far > near ? far : near);
		projection = glm::perspective(glm::radians(this->fov), 1.f, this->near, this->far);
	}

	Camera* PerspectiveCamera::clone() const
	{
		return new PerspectiveCamera(*this);
	}

	Camera::Type PerspectiveCamera::get_type() const
	{
		return Type::Perspective;
	}

	float PerspectiveCamera::get_fov() const
	{
		return fov;
	}

	void PerspectiveCamera::set_resolution(unsigned int width, unsigned int height)
	{
		if (width > 0 && height > 0)
			projection = glm::perspective(glm::radians(fov), static_cast<float>(width) / static_cast<float>(height), near, far);
	}

	void PerspectiveCamera::set_resolution(const Vector2int& resolution)
	{
		if (resolution.x > 0 && resolution.y > 0)
			set_resolution(resolution.x, resolution.y);
	}
}
