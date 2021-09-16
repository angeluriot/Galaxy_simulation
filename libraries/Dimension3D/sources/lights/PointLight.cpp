#include "dim/dimension3D.hpp"

namespace dim
{
	PointLight::PointLight(const Vector3& position, const Color& color, float intensity)
	{
		set_position(position);
		set_color(color);
		set_intensity(intensity);
	}

	Light* PointLight::clone() const
	{
		return new PointLight(*this);
	}

	void PointLight::set_position(float x, float y, float z)
	{
		set_position(Vector3(x, y, z));
	}

	void PointLight::set_position(const Vector3& position)
	{
		vector = position;
	}

	Vector3 PointLight::get_position() const
	{
		return vector;
	}

	Light::Type PointLight::get_type() const
	{
		return Type::Point;
	}
}
