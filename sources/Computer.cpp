#include "Computer.hpp"
#include "Simulator.hpp"

std::vector<dim::Vector4>	Computer::positions;
std::vector<dim::Vector4>	Computer::speeds;
std::vector<dim::Vector4>	Computer::accelerations;
cl::Buffer					Computer::positions_buffer;
cl::Buffer					Computer::speeds_buffer;
cl::Buffer					Computer::accelerations_buffer;
cl::Buffer					Computer::step_buffer;
cl::Buffer					Computer::smoothing_length_buffer;
cl::Buffer					Computer::interaction_rate_buffer;
cl::Buffer					Computer::black_hole_mass_buffer;

dim::Vector3 Computer::random_sphere()
{
	dim::Vector3 result = dim::Vector3::null;

	do
	{
		result.x = dim::random_float(-Simulator::galaxy_diameter / 2.f, Simulator::galaxy_diameter / 2.f);
		result.y = dim::random_float(-Simulator::galaxy_diameter / 2.f, Simulator::galaxy_diameter / 2.f);
		result.z = dim::random_float(-Simulator::galaxy_diameter / 2.f, Simulator::galaxy_diameter / 2.f);
	}
	while (result.get_norm() > Simulator::galaxy_diameter / 2.f);

	return result;
}

void Computer::create_galaxy(int i)
{
	positions[i].set_norm(static_cast<float>(pow(positions[i].get_norm() / (Simulator::galaxy_diameter / 2.f), 5)) * (Simulator::galaxy_diameter / 2.f));
	positions[i].y *= Simulator::galaxy_thickness / Simulator::galaxy_diameter;
	speeds[i] = dim::Vector4(dim::normalize(dim::Vector3(positions[i]) ^ dim::Vector3(0.f, 1.f, 0.f)) * Simulator::stars_speed, 0.f);
}

void Computer::create_collision(int i)
{
	create_galaxy(i);

	if (i % 2)
		positions[i].x -= Simulator::galaxies_distance / 2.f;

	else
	{
		positions[i].x += Simulator::galaxies_distance / 2.f;
		std::swap(positions[i].y, positions[i].z);
		std::swap(speeds[i].y, speeds[i].z);
	}

}

void Computer::create_universe(int i)
{
	speeds[i] = positions[i];
	speeds[i].set_norm((speeds[i].get_norm() / (Simulator::galaxy_diameter / 2.f)) * Simulator::stars_speed);
}

void Computer::init()
{
	positions.clear();
	speeds.clear();
	accelerations.clear();

	positions.resize(Simulator::nb_stars);
	speeds.resize(Simulator::nb_stars);
	accelerations.resize(Simulator::nb_stars, dim::Vector4::null);

	for (int i = 0; i < Simulator::nb_stars; i++)
	{
		positions[i] = dim::Vector4(random_sphere(), 0.f);

		switch (Simulator::simulation_type)
		{
		case SimulationType::Galaxy: create_galaxy(i); break;
		case SimulationType::Collision: create_collision(i); break;
		case SimulationType::Universe: create_universe(i); break;
		default: break;
		}
	}

	positions_buffer = ComputeShader::Buffer(positions, Permissions::All);
	speeds_buffer = ComputeShader::Buffer(speeds, Permissions::All);
	accelerations_buffer = ComputeShader::Buffer(accelerations, Permissions::All);
	step_buffer = ComputeShader::Buffer(Simulator::step, Permissions::Read);
	smoothing_length_buffer = ComputeShader::Buffer(Simulator::smoothing_length, Permissions::Read);
	interaction_rate_buffer = ComputeShader::Buffer(Simulator::interaction_rate, Permissions::Read);
	black_hole_mass_buffer = ComputeShader::Buffer(Simulator::black_hole_mass, Permissions::Read);
}

void Computer::compute()
{
	step_buffer = ComputeShader::Buffer(Simulator::step, Permissions::Read);
	smoothing_length_buffer = ComputeShader::Buffer(Simulator::smoothing_length, Permissions::Read);
	interaction_rate_buffer = ComputeShader::Buffer(Simulator::interaction_rate, Permissions::Read);
	black_hole_mass_buffer = ComputeShader::Buffer(Simulator::black_hole_mass, Permissions::Read);

	// The interactions computations.
	ComputeShader::launch("interactions", { &positions_buffer, &accelerations_buffer, &interaction_rate_buffer,
		&smoothing_length_buffer, &black_hole_mass_buffer }, cl::NDRange(accelerations.size()));
	ComputeShader::get_data(accelerations_buffer, accelerations);

	// The integration computation.
	ComputeShader::launch("integration", { &positions_buffer, &speeds_buffer, &accelerations_buffer, &step_buffer }, cl::NDRange(speeds.size()));
	ComputeShader::get_data(positions_buffer, positions);
	ComputeShader::get_data(speeds_buffer, speeds);
}
