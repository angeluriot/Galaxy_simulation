#include "dim/dimension3D.hpp"

namespace dim
{
	Material::Material(const Color& color)
	{
		set_color(color);
		ambient = 0.f;
		diffuse = 0.f;
		specular = 0.f;
		shininess = 0.f;
		illuminated = false;
	}

	Material::Material(const Color& color, float ambient, float diffuse, float specular, float shininess)
	{
		set_color(color);
		set_ambient(ambient);
		set_diffuse(diffuse);
		set_specular(specular);
		set_shininess(shininess);
		illuminated = true;
	}

	Color Material::get_color() const
	{
		return color;
	}

	void Material::set_color(const Color& color)
	{
		this->color = color;
	}

	float Material::get_ambient() const
	{
		return ambient;
	}

	void Material::set_ambient(float ambient)
	{
		this->ambient = std::max(ambient, 0.f);
	}

	float Material::get_diffuse() const
	{
		return diffuse;
	}

	void Material::set_diffuse(float diffuse)
	{
		this->diffuse = std::max(diffuse, 0.f);
	}

	float Material::get_specular() const
	{
		return specular;
	}

	void Material::set_specular(float specular)
	{
		this->specular = std::max(specular, 0.f);
	}

	float Material::get_shininess() const
	{
		return shininess;
	}

	void Material::set_shininess(float shininess)
	{
		this->shininess = std::max(shininess, 1.f);
	}

	bool Material::is_illuminated() const
	{
		return illuminated;
	}

	void Material::set_illuminated(bool illuminated)
	{
		this->illuminated = illuminated;
	}
}
