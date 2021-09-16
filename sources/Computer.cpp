#include "Computer.hpp"
#include "Simulation.hpp"

dim::Vector2int		Computer::textures_size;
dim::ComputeShader	Computer::init_positions;
dim::ComputeShader	Computer::init_speeds;
dim::ComputeShader	Computer::interactions;
dim::ComputeShader	Computer::integration;
dim::FrameBuffer	Computer::positions;
dim::FrameBuffer	Computer::speeds;
dim::FrameBuffer	Computer::accelerations;

void Computer::init()
{
	textures_size = dim::Vector2int(100, 100);
	positions.create(textures_size, dim::Texture::Type::RGBA_32f);
	speeds.create(textures_size, dim::Texture::Type::RGBA_32f);
	accelerations.create(textures_size, dim::Texture::Type::RGBA_32f);
	init_positions.load("shaders/compute/init_positions.comp");
	init_speeds.load("shaders/compute/init_speeds.comp");
	interactions.load("shaders/compute/interactions.comp");
	integration.load("shaders/compute/integration.comp");

	positions.bind();
		positions.clear();
	positions.unbind();

	speeds.bind();
		speeds.clear();
	speeds.unbind();

	accelerations.bind();
		accelerations.clear();
	accelerations.unbind();

	positions.get_texture().bind_image(0, dim::Texture::Permissions::Write);
		init_positions.bind();
			init_positions.send_uniform(1, Simulation::galaxy_diameter);
			init_positions.send_uniform(2, Simulation::galaxy_thickness);
			init_positions.launch(10, 10, 1);
		init_positions.unbind();
	positions.get_texture().unbind_image(dim::Texture::Permissions::Write);

	positions.get_texture().bind_image(0, dim::Texture::Permissions::Read);
	speeds.get_texture().bind_image(1, dim::Texture::Permissions::Write);
		init_speeds.bind();
			init_speeds.send_uniform(2, Simulation::stars_speed);
			init_speeds.launch(10, 10, 1);
		init_speeds.unbind();
	speeds.get_texture().unbind_image(dim::Texture::Permissions::Write);
	positions.get_texture().unbind_image(dim::Texture::Permissions::Read);
}

void Computer::update_accelerations()
{
	positions.get_texture().bind_image(0, dim::Texture::Permissions::Read);
	accelerations.get_texture().bind_image(1, dim::Texture::Permissions::Write);
		interactions.bind();
			interactions.send_uniform(2, Simulation::smoothing_length);
			interactions.send_uniform(3, textures_size);
			interactions.launch(10, 10, 1);
		interactions.unbind();
	accelerations.get_texture().unbind_image(dim::Texture::Permissions::Write);
	positions.get_texture().unbind_image(dim::Texture::Permissions::Read);
}

void Computer::update_speeds()
{
	speeds.get_texture().bind_image(0, dim::Texture::Permissions::All);
	accelerations.get_texture().bind_image(1, dim::Texture::Permissions::Read);
		integration.bind();
			integration.send_uniform(2, Simulation::step);
			integration.launch(10, 10, 1);
		integration.unbind();
	accelerations.get_texture().unbind_image(dim::Texture::Permissions::Read);
	speeds.get_texture().unbind_image(dim::Texture::Permissions::All);
}

void Computer::update_positions()
{
	positions.get_texture().bind_image(0, dim::Texture::Permissions::All);
	speeds.get_texture().bind_image(1, dim::Texture::Permissions::Read);
		integration.bind();
			integration.send_uniform(2, Simulation::step);
			integration.launch(10, 10, 1);
		integration.unbind();
	speeds.get_texture().unbind_image(dim::Texture::Permissions::Read);
	positions.get_texture().unbind_image(dim::Texture::Permissions::All);
}

void Computer::compute()
{
	update_accelerations();
	update_speeds();
	update_positions();
}
