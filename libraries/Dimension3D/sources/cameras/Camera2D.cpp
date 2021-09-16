#include "dim/dimension3D.hpp"

namespace dim
{
	Camera2D::Camera2D()
	{
		zoom_level = 1.f;
		size = Window::initial_size;
		view = sf::View((size / 2.f).to_sf_float(), size.to_sf_float());
	}

	void Camera2D::set_zoom(float zoom)
	{
		if (zoom > 0.f)
		{
			zoom_level = zoom;
			view.setSize((zoom_level * size).to_sf_float());
		}
	}

	void Camera2D::set_rotation(float angle)
	{
		view.setRotation(angle);
	}

	void Camera2D::set_position(const Vector2& position)
	{
		view.setCenter((zoom_level * position).to_sf_float());
	}

	void Camera2D::set_position(float x, float y)
	{
		set_position(Vector2(x, y));
	}

	void Camera2D::zoom(float zoom)
	{
		if (zoom > 0.f)
		{
			zoom_level *= zoom;
			view.setSize((zoom_level * size).to_sf_float());
		}
	}

	void Camera2D::rotate(float angle)
	{
		view.rotate(angle);
	}

	void Camera2D::move(const Vector2& move)
	{
		view.move(move.to_sf_float());
	}

	void Camera2D::move(float x, float y)
	{
		move(Vector2(x, y));
	}

	void Camera2D::set_resolution(unsigned int width, unsigned int height)
	{
		if (width > 0 && height > 0)
		{
			move((Vector2(static_cast<float>(width), static_cast<float>(height)) - size) * 0.5f * zoom_level);
			size = Vector2(static_cast<float>(width), static_cast<float>(height));
			view.setSize((zoom_level * size).to_sf_float());
		}
	}

	void Camera2D::set_resolution(const Vector2int& resolution)
	{
		if (resolution.x > 0 && resolution.y > 0)
			set_resolution(resolution.x, resolution.y);
	}

	sf::View& Camera2D::get_view()
	{
		return view;
	}

	float Camera2D::get_zoom() const
	{
		return zoom_level;
	}

	Vector2 Camera2D::get_resolution() const
	{
		return size;
	}
}
