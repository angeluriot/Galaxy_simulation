#include "dim/dimension3D.hpp"

namespace dim
{
	VertexBuffer::VertexBuffer()
	{
		shader = Shader::default_shader;
		vbo = std::make_shared<GLuint>();
		vao = std::make_shared<GLuint>();
		nb_vertices = std::make_shared<unsigned int>(0);
	}

	VertexBuffer::VertexBuffer(const std::string& shader_name)
	{
		set_shader(shader_name);
		vbo = std::make_shared<GLuint>();
		vao = std::make_shared<GLuint>();
		nb_vertices = std::make_shared<unsigned int>(0);
	}

	VertexBuffer::VertexBuffer(const Shader& shader)
	{
		set_shader(shader);
		vbo = std::make_shared<GLuint>();
		vao = std::make_shared<GLuint>();
		nb_vertices = std::make_shared<unsigned int>(0);
	}

	VertexBuffer::VertexBuffer(const std::string& shader_name, const Mesh& mesh, DataType data_sent)
	{
		set_shader(shader_name);
		vbo = std::make_shared<GLuint>();
		vao = std::make_shared<GLuint>();
		nb_vertices = std::make_shared<unsigned int>(0);
		send_data(mesh, data_sent);
	}

	VertexBuffer::VertexBuffer(const Shader& shader, const Mesh& mesh, DataType data_sent)
	{
		set_shader(shader);
		vbo = std::make_shared<GLuint>();
		vao = std::make_shared<GLuint>();
		nb_vertices = std::make_shared<unsigned int>(0);
		send_data(mesh, data_sent);
	}

	VertexBuffer::~VertexBuffer()
	{
		if (vbo.unique())
		{
			glDeleteBuffers(1, &(*vbo));
			glDeleteVertexArrays(1, &(*vao));
		}
	}

	void VertexBuffer::set_shader(const std::string& shader_name)
	{
		shader = Shader::get(shader_name);
	}

	void VertexBuffer::set_shader(const Shader& shader)
	{
		this->shader = shader;
	}

	void VertexBuffer::send_data(const std::string& shader_name, const Mesh& mesh, DataType data_sent)
	{
		set_shader(shader_name);
		send_data(mesh, data_sent);
	}

	void VertexBuffer::send_data(const Shader& shader, const Mesh& mesh, DataType data_sent)
	{
		set_shader(shader);
		send_data(mesh, data_sent);
	}

	void VertexBuffer::send_data(const Mesh& mesh, DataType data_sent)
	{
		#pragma warning(push, 0)

		glDeleteBuffers(1, &(*vbo));
		glDeleteVertexArrays(1, &(*vao));

		bool send_positions = (data_sent & DataType::Positions) == DataType::Positions;
		bool send_normals = (data_sent & DataType::Normals) == DataType::Normals;
		bool send_texcoords = (data_sent & DataType::TexCoords) == DataType::TexCoords;

		*nb_vertices = (data_sent == static_cast<DataType>(0) ? 0 : mesh.get_nb_vertices());

		if (*nb_vertices)
		{
			glGenBuffers(1, &(*vbo));
			glBindBuffer(GL_ARRAY_BUFFER, *vbo);
			{
				glBufferData(GL_ARRAY_BUFFER, send_positions * mesh.get_positions_size() +
					send_normals * mesh.get_normals_size() + send_texcoords * mesh.get_texcoords_size(), NULL, GL_DYNAMIC_DRAW);

				if (send_positions)
					glBufferSubData(GL_ARRAY_BUFFER, 0, mesh.get_positions_size(), reinterpret_cast<const float*>(mesh.positions.data()));

				if (send_normals)
					glBufferSubData(GL_ARRAY_BUFFER, send_positions * mesh.get_positions_size(), mesh.get_normals_size(), reinterpret_cast<const float*>(mesh.normals.data()));

				if (send_texcoords)
					glBufferSubData(GL_ARRAY_BUFFER, send_positions * mesh.get_positions_size() +
						send_normals * mesh.get_normals_size(), mesh.get_texcoords_size(), reinterpret_cast<const float*>(mesh.texcoords.data()));
			}
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glGenVertexArrays(1, &(*vao));
			glBindVertexArray(*vao);
			{
				glBindBuffer(GL_ARRAY_BUFFER, *vbo);
				{
					if (send_positions)
					{
						GLint positions = glGetAttribLocation(shader.get_id(), "a_position");
						glVertexAttribPointer(positions, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<GLvoid*>(0));
						glEnableVertexAttribArray(positions);
					}

					if (send_normals)
					{
						GLint normals = glGetAttribLocation(shader.get_id(), "a_normal");
						glVertexAttribPointer(normals, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<GLvoid*>(send_positions * mesh.get_positions_size()));
						glEnableVertexAttribArray(normals);
					}

					if (send_texcoords)
					{
						GLint texcoords = glGetAttribLocation(shader.get_id(), "a_texcoord");
						glVertexAttribPointer(texcoords, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), reinterpret_cast<GLvoid*>(send_positions * mesh.get_positions_size() +
							send_normals * mesh.get_normals_size()));
						glEnableVertexAttribArray(texcoords);
					}
				}
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}
			glBindVertexArray(0);
		}

		#pragma warning(pop)
	}

	Shader VertexBuffer::get_shader() const
	{
		return shader;
	}

	unsigned int VertexBuffer::get_nb_vertices() const
	{
		return *nb_vertices;
	}

	void VertexBuffer::bind() const
	{
		glBindVertexArray(*vao);
		glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	}

	void VertexBuffer::unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void VertexBuffer::draw(DrawType draw_type) const
	{
		if (*nb_vertices)
			glDrawArrays(static_cast<GLenum>(draw_type == DrawType::Default ? DrawType::Triangles : draw_type), 0, *nb_vertices);
	}

	DataType operator&(DataType type_1, DataType type_2)
	{
		return static_cast<DataType>(static_cast<uint8_t>(type_1) & static_cast<uint8_t>(type_2));
	}

	DataType operator|(DataType type_1, DataType type_2)
	{
		return static_cast<DataType>(static_cast<uint8_t>(type_1) | static_cast<uint8_t>(type_2));
	}

	DataType operator^(DataType type_1, DataType type_2)
	{
		return static_cast<DataType>(static_cast<uint8_t>(type_1) ^ static_cast<uint8_t>(type_2));
	}

	DataType operator~(DataType type)
	{
		return static_cast<DataType>(~static_cast<uint8_t>(type));
	}
}
