#include "dim/dimension3D.hpp"

namespace dim
{
	AmbientLight::AmbientLight(const Color& color, float intensity)
	{
		set_color(color);
		set_intensity(intensity);
	}

	Light* AmbientLight::clone() const
	{
		return new AmbientLight(*this);
	}

	Light::Type AmbientLight::get_type() const
	{
		return Type::Ambient;
	}
}
