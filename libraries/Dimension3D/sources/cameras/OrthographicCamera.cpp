#include "dim/dimension3D.hpp"

namespace dim
{
	OrthographicCamera::OrthographicCamera(float zoom, float near, float far) : Camera()
	{
		zoom_level = (zoom > 0.f ? zoom : default_zoom);
		this->near = (near > 0.f ? near : default_near);
		this->far = (far > near ? far : near);
		ratio = 1.f;
		projection = glm::ortho(-ratio * zoom_level, ratio * zoom_level, -zoom_level, zoom_level, near, far);
	}

	Camera* OrthographicCamera::clone() const
	{
		return new OrthographicCamera(*this);
	}

	Camera::Type OrthographicCamera::get_type() const
	{
		return Type::Orthographic;
	}

	void OrthographicCamera::zoom(float zoom)
	{
		if (zoom > 0.f)
		{
			zoom_level *= 1.f - (zoom - 1.f);
			projection = glm::ortho(-ratio * zoom_level, ratio * zoom_level, -zoom_level, zoom_level, near, far);
		}
	}

	void OrthographicCamera::set_zoom(float zoom)
	{
		if (zoom > 0.f)
		{
			zoom_level = 1.f - (zoom - 1.f);
			projection = glm::ortho(-ratio * zoom_level, ratio * zoom_level, -zoom_level, zoom_level, near, far);
		}
	}

	float OrthographicCamera::get_zoom() const
	{
		return zoom_level;
	}

	void OrthographicCamera::set_resolution(unsigned int width, unsigned int height)
	{
		if (width > 0 && height > 0)
		{
			ratio = static_cast<float>(width) / static_cast<float>(height);
			projection = glm::ortho(-ratio * zoom_level, ratio * zoom_level, -zoom_level, zoom_level, near, far);
		}
	}

	void OrthographicCamera::set_resolution(const Vector2int& resolution)
	{
		if (resolution.x > 0 && resolution.y > 0)
			set_resolution(resolution.x, resolution.y);
	}
}
