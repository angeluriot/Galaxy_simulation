#include "Renderer.hpp"
#include "Simulation.hpp"

dim::Shader			Renderer::galaxy_shader;
dim::VertexBuffer	Renderer::galaxy_vbo;
dim::Shader			Renderer::test_shader;
dim::VertexBuffer	Renderer::test_vbo;

void Renderer::init()
{
	galaxy_shader.load("shaders/galaxy2.vert", "shaders/galaxy2.frag");

	dim::Mesh mesh;

	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			mesh.positions.push_back(dim::Vector3(i / 100.f, j / 100.f, 0.f));

	galaxy_vbo.send_data(galaxy_shader, mesh, dim::DataType::Positions);

	test_shader.load("shaders/test.vert", "shaders/test.frag");
	test_vbo.send_data("test", dim::Mesh::screen, dim::DataType::Positions | dim::DataType::TexCoords);
}

void Renderer::draw()
{
	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	dim::Window::set_thickness(1.f);

	galaxy_shader.bind();
		Computer::positions.get_texture().bind();
			galaxy_vbo.bind();

				galaxy_shader.send_uniform("u_mvp", dim::Window::get_camera().get_matrix());
				galaxy_shader.send_uniform("u_texture", Computer::positions.get_texture());
				galaxy_vbo.draw(dim::DrawType::Points);

			galaxy_vbo.unbind();
		Computer::positions.get_texture().unbind();
	galaxy_shader.unbind();
/*
	test_shader.bind();
		Computer::positions.get_texture().bind();
			test_vbo.bind();

				test_shader.send_uniform("u_texture", Computer::positions.get_texture());
				test_vbo.draw();

			test_vbo.unbind();
		Computer::positions.get_texture().unbind();
	test_shader.unbind();*/

	glDisable(GL_BLEND);
}
