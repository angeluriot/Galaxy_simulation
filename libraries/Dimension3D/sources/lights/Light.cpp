#include "dim/dimension3D.hpp"

namespace dim
{
	Light::Light() {}

	Color Light::get_color() const
	{
		return color;
	}

	void Light::set_color(const Color& color)
	{
		this->color.r = color.r * color.a;
		this->color.g = color.g * color.a;
		this->color.b = color.b * color.a;
		this->color.a = 1.f;
	}

	float Light::get_intensity() const
	{
		return intensity;
	}

	void Light::set_intensity(float intensity)
	{
		this->intensity = std::max(intensity, 0.f);
	}
}
