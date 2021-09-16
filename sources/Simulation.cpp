#include "Simulation.hpp"

std::atomic<bool>	Simulation::mesh_done = false;
std::mutex			Simulation::reload;
float				Simulation::step;
IntergrationMethod	Simulation::intergration_method;
float				Simulation::smoothing_length;
float				Simulation::precision;
int					Simulation::nb_stars;
float				Simulation::galaxy_diameter;
float				Simulation::galaxy_thickness;
float				Simulation::stars_speed;
std::list<Star>		Simulation::galaxy = {};
dim::FrameBuffer	Simulation::input_texture;
dim::FrameBuffer	Simulation::output_texture;
dim::ComputeShader	Simulation::compute_shader;
dim::VertexBuffer	Simulation::star_vbo;
dim::VertexBuffer	Simulation::galaxy_vbo;
dim::VertexBuffer	Simulation::blur_vbo;
dim::VertexBuffer	Simulation::post_vbo;
dim::Mesh			Simulation::mesh;
dim::FrameBuffer	Simulation::galaxy_fbo_1;
dim::FrameBuffer	Simulation::galaxy_fbo_2;
dim::FrameBuffer	Simulation::blur_fbo_1;
dim::FrameBuffer	Simulation::blur_fbo_2;
Block				Simulation::main_block;

void Simulation::restart()
{
	galaxy.clear();
	mesh.clear();

	step = Menu::step;
	intergration_method = static_cast<IntergrationMethod>(Menu::intergration_method);
	smoothing_length = Menu::smoothing_length;
	precision = Menu::precision;
	nb_stars = Menu::nb_stars;
	galaxy_diameter = Menu::galaxy_diameter;
	galaxy_thickness = Menu::galaxy_thickness;
	stars_speed = Menu::stars_speed;

	input_texture.create(640, 480, dim::Texture::Type::RGBA_32f);
	output_texture.create(640, 480, dim::Texture::Type::RGBA_32f);
	compute_shader.load("shaders/compute.comp");

	galaxy_vbo.set_shader("galaxy");
	star_vbo.send_data("star", dim::Mesh::square, dim::DataType::Positions);
	blur_vbo.send_data("blur", dim::Mesh::screen, dim::DataType::Positions | dim::DataType::TexCoords);
	post_vbo.send_data("post", dim::Mesh::screen, dim::DataType::Positions | dim::DataType::TexCoords);
	galaxy_fbo_1.create(dim::Window::get_size(), dim::Texture::Type::RGB_16f);
	galaxy_fbo_2.create(dim::Window::get_size(), dim::Texture::Type::RGB_16f);
	blur_fbo_1.create(dim::Window::get_size(), dim::Texture::Type::RGB_16f);
	blur_fbo_2.create(dim::Window::get_size(), dim::Texture::Type::RGB_16f);

	Computer::init();
	Renderer::init();

	galaxy.resize(nb_stars);
	mesh.positions.resize(nb_stars);
	mesh.texcoords.resize(nb_stars);

	center_camera();
	update_mesh();
}

void Simulation::center_camera()
{
	
}

void Simulation::menu_update()
{
	step = Menu::step;
	intergration_method = static_cast<IntergrationMethod>(Menu::intergration_method);
	smoothing_length = Menu::smoothing_length;
	precision = Menu::precision;
}

void Simulation::update()
{
	Simulation::reload.lock();

	//if (!Menu::pause && !mesh_done)
	//{
		menu_update();
		//main_block.reload();

		//for (Star& star : galaxy)
			//star.update_acceleration();

		//for (Star& star : galaxy)
			//star.update_position();

		//center_camera();
		//update_mesh();
	//}

	Simulation::reload.unlock();
}

void Simulation::update_mesh()
{
	int i = 0;

	for (Star& star : galaxy)
	{
		mesh.positions[i] = star.position;
		mesh.texcoords[i].x = star.get_brightness();
		i++;
	}

	mesh_done = true;
}

void Simulation::send_mesh()
{
	//if (mesh_done)
	//{
		//galaxy_vbo.send_data(mesh, dim::DataType::Positions | dim::DataType::TexCoords);
		//mesh_done = false;
	//}
}

void Simulation::check_events(const sf::Event& sf_event)
{
	if (sf_event.type == sf::Event::Resized)
	{
		galaxy_fbo_1.set_size(dim::Window::get_size());
		galaxy_fbo_2.set_size(dim::Window::get_size());
		blur_fbo_1.set_size(dim::Window::get_size());
		blur_fbo_2.set_size(dim::Window::get_size());
	}
}

void Simulation::clear()
{
	galaxy_fbo_1.bind();
	galaxy_fbo_1.clear();
	galaxy_fbo_1.unbind();

	galaxy_fbo_2.bind();
	galaxy_fbo_2.clear();
	galaxy_fbo_2.unbind();

	blur_fbo_1.bind();
	blur_fbo_1.clear();
	blur_fbo_1.unbind();

	blur_fbo_2.bind();
	blur_fbo_2.clear();
	blur_fbo_2.unbind();
}

void Simulation::draw()
{
	Computer::compute();
	Renderer::draw();

	/*
	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	dim::Window::set_thickness(1.f);

	galaxy_fbo_1.bind();
		dim::Shader::get("galaxy").bind();
			galaxy_vbo.bind();

				dim::Shader::get("galaxy").send_uniform("u_mvp", dim::Window::get_camera().get_matrix());
				galaxy_vbo.draw(dim::DrawType::Points);

			galaxy_vbo.unbind();
		dim::Shader::get("galaxy").unbind();
	galaxy_fbo_1.unbind();

	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	dim::Window::set_thickness(2.f);

	galaxy_fbo_2.bind();
		dim::Shader::get("galaxy").bind();
			galaxy_vbo.bind();

				dim::Shader::get("galaxy").send_uniform("u_mvp", dim::Window::get_camera().get_matrix());
				galaxy_vbo.draw(dim::DrawType::Points);

			galaxy_vbo.unbind();
		dim::Shader::get("galaxy").unbind();
	galaxy_fbo_2.unbind();

	blur_fbo_1.bind();
		dim::Shader::get("blur").bind();
			galaxy_fbo_2.get_texture().bind();
				blur_vbo.bind();

					dim::Shader::get("blur").send_uniform("u_texture", galaxy_fbo_2.get_texture());
					dim::Shader::get("blur").send_uniform("u_horizontal", 1);
					blur_vbo.draw();

				blur_vbo.unbind();
			galaxy_fbo_2.get_texture().unbind();
		dim::Shader::get("blur").unbind();
	blur_fbo_1.unbind();

	blur_fbo_2.bind();
		dim::Shader::get("blur").bind();
			blur_fbo_1.get_texture().bind();
				blur_vbo.bind();

					dim::Shader::get("blur").send_uniform("u_texture", blur_fbo_1.get_texture());
					dim::Shader::get("blur").send_uniform("u_horizontal", 0);
					blur_vbo.draw();

				blur_vbo.unbind();
			blur_fbo_1.get_texture().unbind();
		dim::Shader::get("blur").unbind();
	blur_fbo_2.unbind();

	dim::Shader::get("post").bind();
		galaxy_fbo_1.get_texture().bind();
		blur_fbo_2.get_texture().bind();
			post_vbo.bind();

				dim::Shader::get("post").send_uniform("u_galaxy", galaxy_fbo_1.get_texture());
				dim::Shader::get("post").send_uniform("u_blur", blur_fbo_2.get_texture());
				post_vbo.draw();

			post_vbo.unbind();
		blur_fbo_2.get_texture().unbind();
		galaxy_fbo_1.get_texture().unbind();
	dim::Shader::get("post").unbind();

	glDisable(GL_BLEND);*/
}
