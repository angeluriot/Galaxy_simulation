#include "Renderer.hpp"
#include "Simulator.hpp"

GLuint				Renderer::vbo = 0;
GLuint				Renderer::vao = 0;
dim::VertexBuffer	Renderer::blur_vbo;
dim::VertexBuffer	Renderer::post_vbo;
dim::FrameBuffer	Renderer::galaxy_fbo_1;
dim::FrameBuffer	Renderer::galaxy_fbo_2;
dim::FrameBuffer	Renderer::blur_fbo_1;
dim::FrameBuffer	Renderer::blur_fbo_2;

void Renderer::init_vbo()
{
	// delete buffers
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);

	// Create VBO
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

		GLsizeiptr array_size = Computer::positions.size() * sizeof(dim::Vector4);

		glBufferData(GL_ARRAY_BUFFER, 2 * array_size, NULL, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, array_size, Computer::positions.data());
		glBufferSubData(GL_ARRAY_BUFFER, array_size, array_size, Computer::speeds.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Create VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

			GLint positions = glGetAttribLocation(dim::Shader::get("galaxy").get_id(), "a_position");
			glVertexAttribPointer(positions, 4, GL_FLOAT, GL_FALSE, sizeof(dim::Vector4), reinterpret_cast<GLvoid*>(0));
			glEnableVertexAttribArray(positions);

			GLint speeds = glGetAttribLocation(dim::Shader::get("galaxy").get_id(), "a_speed");
			glVertexAttribPointer(speeds, 4, GL_FLOAT, GL_FALSE, sizeof(dim::Vector4), reinterpret_cast<GLvoid*>(array_size));
			glEnableVertexAttribArray(speeds);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Renderer::update_vbo()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

		GLsizeiptr array_size = Computer::positions.size() * sizeof(dim::Vector4);

		glBufferData(GL_ARRAY_BUFFER, 2 * array_size, NULL, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, array_size, Computer::positions.data());
		glBufferSubData(GL_ARRAY_BUFFER, array_size, array_size, Computer::speeds.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderer::draw_vbo()
{
	glDrawArrays(GL_POINTS, 0, static_cast<GLsizei>(Computer::positions.size()));
}

void Renderer::bind_vbo()
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void Renderer::unbind_vbo()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Renderer::init()
{
	init_vbo();

	blur_vbo.send_data("blur", dim::Mesh::screen, dim::DataType::Positions | dim::DataType::TexCoords);
	post_vbo.send_data("post", dim::Mesh::screen, dim::DataType::Positions | dim::DataType::TexCoords);
	galaxy_fbo_1.create(dim::Window::get_size(), dim::Texture::Type::RGB_16f);
	galaxy_fbo_2.create(dim::Window::get_size(), dim::Texture::Type::RGB_16f);
	blur_fbo_1.create(dim::Window::get_size(), dim::Texture::Type::RGB_16f);
	blur_fbo_2.create(dim::Window::get_size(), dim::Texture::Type::RGB_16f);

	update_vbo();
}

void Renderer::check_events(const sf::Event& sf_event)
{
	if (sf_event.type == sf::Event::Resized)
	{
		galaxy_fbo_1.set_size(dim::Window::get_size());
		galaxy_fbo_2.set_size(dim::Window::get_size());
		blur_fbo_1.set_size(dim::Window::get_size());
		blur_fbo_2.set_size(dim::Window::get_size());
	}
}

void Renderer::clear()
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

void Renderer::draw()
{
	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	dim::Window::set_thickness(1.f);

	// Draw the stars.
	galaxy_fbo_1.bind();
		dim::Shader::get("galaxy").bind();
			bind_vbo();

				dim::Shader::get("galaxy").send_uniform("u_mvp", dim::Window::get_camera().get_matrix());
				draw_vbo();

			unbind_vbo();
		dim::Shader::get("galaxy").unbind();
	galaxy_fbo_1.unbind();

	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	dim::Window::set_thickness(2.f);

	// Draw the stars to be blured.
	galaxy_fbo_2.bind();
		dim::Shader::get("galaxy").bind();
			bind_vbo();

				dim::Shader::get("galaxy").send_uniform("u_mvp", dim::Window::get_camera().get_matrix());
				draw_vbo();

			unbind_vbo();
		dim::Shader::get("galaxy").unbind();
	galaxy_fbo_2.unbind();

	// The first step of the blur.
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

	// The second step of the blur.
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

	// Merge all the steps and set the color.
	dim::Shader::get("post").bind();
		galaxy_fbo_1.get_texture().bind();
		blur_fbo_2.get_texture().bind();
			post_vbo.bind();

				dim::Shader::get("post").send_uniform("u_color_type", static_cast<int>(Simulator::simulation_type));
				dim::Shader::get("post").send_uniform("u_galaxy", galaxy_fbo_1.get_texture());
				dim::Shader::get("post").send_uniform("u_blur", blur_fbo_2.get_texture());
				post_vbo.draw();

			post_vbo.unbind();
		blur_fbo_2.get_texture().unbind();
		galaxy_fbo_1.get_texture().unbind();
	dim::Shader::get("post").unbind();

	glDisable(GL_BLEND);
}
