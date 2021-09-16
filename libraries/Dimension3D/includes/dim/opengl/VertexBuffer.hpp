#ifndef DIM_VERTEXBUFFER_HPP
#define DIM_VERTEXBUFFER_HPP

#include "dim/utils/libraries.hpp"
#include "dim/opengl/Shader.hpp"
#include "dim/vectors/Vector2.hpp"
#include "dim/vectors/Vector3.hpp"
#include "dim/vectors/Vector4.hpp"
#include "dim/opengl/Texture.hpp"

namespace dim
{
	class Texture;
	class Mesh;

	/**
	 * @brief The type of data to send (you can use the | operator).
	 */
	enum class DataType : uint8_t
	{
		Positions	= 0b001,	// The position data.
		Normals		= 0b010,	// The normals data.
		TexCoords	= 0b100,	// The texture coordinates data.
		All			= 0b111		// All the data.
	};

	/**
	 * @brief The way to draw a 3D object.
	 */
	enum class DrawType
	{
		Default		= 0x0015,		// The default way.
		Points		= GL_POINTS,	// With points.
		Lines		= GL_LINES,		// With lines.
		Triangles	= GL_TRIANGLES	// With triangles.
	};

	/**
	 * @brief A class that represents an OpenGL vertex buffer object and an OpenGL vertex array object,
	 * it is made to send mesh data to the shader (it needs to be binded before use and unbinded after).
	 */
	class VertexBuffer
	{
	private:

		Shader							shader;			// The shader used by the vertex buffer.
		std::shared_ptr<GLuint>			vbo;			// The OpenGL vertex buffer object.
		std::shared_ptr<GLuint>			vao;			// The OpenGL vertex array object.
		std::shared_ptr<unsigned int>	nb_vertices;	// The number of vertices of the mesh.

	public:

		/**
		 * @brief Construct a new vertex buffer.
		 */
		VertexBuffer();

		/**
		 * @brief Construct a reference to the other vertex buffer (it is not a copy).
		 *
		 * @param other the reference vertex buffer
		 */
		VertexBuffer(const VertexBuffer& other) = default;

		/**
		 * @brief Construct a new vertex buffer and set its shader.
		 *
		 * @param shader_name the name of the shader
		 */
		VertexBuffer(const std::string& shader_name);

		/**
		 * @brief Construct a new vertex buffer and set its shader.
		 *
		 * @param shader the shader
		 */
		VertexBuffer(const Shader& shader);

		/**
		 * @brief Construct a new vertex buffer, set its shader and send the data of a mesh.
		 *
		 * @param shader_name the name of the shader
		 * @param mesh the mesh to send
		 * @param data_sent the data type to send (you can use the | operator)
		 */
		VertexBuffer(const std::string& shader_name, const Mesh& mesh, DataType data_sent = DataType::All);

		/**
		 * @brief Construct a new vertex buffer, set its shader and send the data of a mesh.
		 *
		 * @param shader the shader
		 * @param mesh the mesh to send
		 * @param data_sent the data type to send (you can use the | operator)
		 */
		VertexBuffer(const Shader& shader, const Mesh& mesh, DataType data_sent = DataType::All);

		/**
		 * @brief Delete the vertex buffer.
		 */
		~VertexBuffer();

		/**
		 * @brief Transform the vertex buffer to a reference to the other vertex buffer (it is not a copy).
		 *
		 * @param other the reference vertex buffer
		 * @return a reference to the vertex buffer
		 */
		VertexBuffer& operator=(const VertexBuffer& other) = default;

		/**
		 * @brief Change the shader of the vertex buffer.
		 *
		 * @param shader_name the name of the new shader
		 */
		void set_shader(const std::string& shader_name);

		/**
		 * @brief Change the shader of the vertex buffer.
		 *
		 * @param shader the new shader
		 */
		void set_shader(const Shader& shader);

		/**
		 * @brief Change its shader and send the data of a mesh.
		 *
		 * @param shader_name the name of the new shader
		 * @param mesh the mesh to send
		 * @param data_sent the data type to send (you can use the | operator)
		 */
		void send_data(const std::string& shader_name, const Mesh& mesh, DataType data_sent = DataType::All);

		/**
		 * @brief Change its shader and send the data of a mesh.
		 *
		 * @param shader the new shader
		 * @param mesh the mesh to send
		 * @param data_sent the data type to send (you can use the | operator)
		 */
		void send_data(const Shader& shader, const Mesh& mesh, DataType data_sent = DataType::All);

		/**
		 * @brief Send the data of a mesh.
		 *
		 * @param mesh the mesh to send
		 * @param data_sent the data type to send (you can use the | operator)
		 */
		void send_data(const Mesh& mesh, DataType data_sent = DataType::All);

		/**
		 * @brief Give the shader of the vertex buffer.
		 *
		 * @return the shader of the vertex buffer
		 */
		Shader get_shader() const;

		/**
		 * @brief Give the number of vertices of the mesh.
		 *
		 * @return the number of vertices of the mesh
		 */
		unsigned int get_nb_vertices() const;

		/**
		 * @brief Bind the vertex buffer.
		 */
		void bind() const;

		/**
		 * @brief Unbind the vertex buffer.
		 */
		static void unbind();

		/**
		 * @brief Draw the vertex buffer to the screen.
		 *
		 * @param draw_type the way to draw the 3D object
		 */
		void draw(DrawType draw_type = DrawType::Triangles) const;
	};

	/**
	 * @brief Apply the binary AND operator.
	 *
	 * @param type_1 the first data type
	 * @param type_2 the second data type
	 * @return the result
	 */
	DataType operator&(DataType type_1, DataType type_2);

	/**
	 * @brief Apply the binary OR operator.
	 *
	 * @param type_1 the first data type
	 * @param type_2 the second data type
	 * @return the result
	 */
	DataType operator|(DataType type_1, DataType type_2);

	/**
	 * @brief Apply the binary XOR operator.
	 *
	 * @param type_1 the first data type
	 * @param type_2 the second data type
	 * @return the result
	 */
	DataType operator^(DataType type_1, DataType type_2);

	/**
	 * @brief Apply the binary NOT operator.
	 *
	 * @param type the input data type
	 * @return the result
	 */
	DataType operator~(DataType type);
}

#endif
