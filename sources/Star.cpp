#include "Star.hpp"
#include "Simulation.hpp"

Star::Star()
{
	//position = dim::Vector3::Spherical(dim::random_float(0.f, 1.f) * (Simulation::galaxy_diameter / 2.f),
		//dim::random_float(0.f, 2.f * dim::pi), dim::random_float(0.f, dim::pi));

	//position.y *= Simulation::galaxy_thickness / Simulation::galaxy_diameter;

	position = dim::Vector3::Spherical(dim::random_float(0.f, 1.f) * (Simulation::galaxy_diameter / 2.f),
		dim::random_float(0.f, 2.f * dim::pi), dim::pi / 2.f);

	position.y = dim::random_float(-0.5f, 0.5f) * Simulation::galaxy_thickness;

	speed = (dim::normalize(dim::Vector3(position.x, 0.f, position.z)) ^ dim::Vector3(0.f, 1.f, 0.f)) * Simulation::stars_speed;
	acceleration.clear();
	std::fill(closest_stars.begin(), closest_stars.end(), 1000000000.f);

	previous_acc.clear();
	previous_pos = position - (speed * Simulation::step);

	alive = true;
}

void Star::force_calculation(const Block& block)
{
	float distance = dim::distance(position, block.mass_center);
	float distance_2 = distance * distance;

	if (block.stars.size() == 1)
	{
		if (distance_2 > 0.f)
		{
			acceleration += dim::normalize(block.mass_center - position) / (distance_2 + Simulation::smoothing_length);

			float farest = 0.f;
			float* farest_ptr;

			for (float& dist : closest_stars)
				if (dist > farest)
				{
					farest = dist;
					farest_ptr = &dist;
				}

			if (distance < farest)
				*farest_ptr = distance;
		}
	}

	else
	{
		if (block.size / distance < Simulation::precision && distance_2 > 0.f)
		{
			acceleration += (static_cast<float>(block.stars.size()) * dim::normalize(block.mass_center - position)) / (distance_2 + Simulation::smoothing_length);

			float farest = 0.f;
			float* farest_ptr;

			for (float& dist : closest_stars)
				if (dist > farest)
				{
					farest = dist;
					farest_ptr = &dist;
				}

			if (distance < farest)
				*farest_ptr = distance;
		}

		else
			for (const Block& child : block.children)
				force_calculation(child);
	}
}

void Star::update_acceleration()
{
	if (alive)
	{
		previous_acc = acceleration;
		acceleration.clear();
		std::fill(closest_stars.begin(), closest_stars.end(), 1000000000.f);

		force_calculation(Simulation::main_block);

		acceleration -= (2000 * dim::normalize(position)) / (position.get_norm_2() + Simulation::smoothing_length);
	}
}

void Star::update_position()
{
	if (alive)
	{
		dim::Vector3 temp = position;

		if (Simulation::intergration_method == IntergrationMethod::Euler)
		{
			speed += acceleration * Simulation::step;
			position += speed * Simulation::step;
		}

		else if (Simulation::intergration_method == IntergrationMethod::Verlet)
		{
			speed = (position - previous_pos) / Simulation::step;
			position = (2.f * position) - previous_pos + (acceleration * (Simulation::step * Simulation::step));
		}

		else
		{
			speed += previous_acc * (Simulation::step / 2.f);
			position += speed * Simulation::step;
			speed += acceleration * (Simulation::step / 2.f);
		}

		previous_pos = temp;
	}
}

float Star::get_brightness() const
{
	if (!alive)
		return 0.f;

	float density = 0.f;

	for (float dist : closest_stars)
		density += dist;

	density = 1.f / density;

	return 5.f * sqrt((Simulation::galaxy_diameter * Simulation::galaxy_diameter * Simulation::galaxy_thickness * density) / Simulation::nb_stars);
}
