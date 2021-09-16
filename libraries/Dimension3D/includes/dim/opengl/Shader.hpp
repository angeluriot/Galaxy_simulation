#ifndef DIM_SHADER_HPP
#define DIM_SHADER_HPP

#include "dim/utils/libraries.hpp"
#include "dim/vectors/Vector2.hpp"
#include "dim/vectors/Vector3.hpp"
#include "dim/vectors/Vector4.hpp"
#include "dim/opengl/Texture.hpp"

namespace dim
{
	class Mesh;
	class VertexBuffer;
	class Light;
	class Material;
	class Color;
	void init();
	void shut_down();

	/**
	 * @brief A class that represents an OpenGL shader, it is a program that runs on the GPU (it needs to be binded before use and unbinded after).
	 */
	class Shader
	{
	private:

		std::shared_ptr<sf::Shader>				shader;				// The SFML object.

		static std::map<std::string, Shader>	shaders;			// The static shaders container.

	public:

		static constexpr unsigned int			max_lights = 10;	// The maximum number of lights that the default shader can handle.
		static Shader							default_shader;		// The default shader.

		/**
		 * @brief Construct a new shader.
		 */
		Shader();

		/**
		 * @brief Construct a reference to the other shader (it is not a copy).
		 *
		 * @param other the reference shader
		 */
		Shader(const Shader& other) = default;

		/**
		 * @brief Construct and compile a new shader.
		 *
		 * @param vert_path the path to the vertex shader
		 * @param frag_path the path to the fragment shader
		 */
		Shader(const std::string& vert_path, const std::string& frag_path);

		/**
		 * @brief Transform the shader to a reference to the other shader (it is not a copy).
		 *
		 * @param other the reference shader
		 * @return a reference to the shader
		 */
		Shader& operator=(const Shader& other) = default;

	private:

		/**
		 * @brief Compile the default shader.
		 */
		static void init();

	public:

		/**
		 * @brief Load and compile the shader
		 *
		 * @param vert_path the path to the vertex shader
		 * @param frag_path the path to the fragment shader
		 */
		void load(const std::string& vert_path, const std::string& frag_path);

		/**
		 * @brief Give the OpenGL id.
		 *
		 * @return the OpenGL id
		 */
		GLuint get_id() const;

		/**
		 * @brief Bind the shader.
		 */
		void bind() const;

		/**
		 * @brief Unbind the shaders.
		 */
		static void unbind();

		/**
		 * @brief Send a texture to the shader.
		 *
		 * @param name the name of the GLSL variable
		 * @param texture the texture to send
		 */
		void send_uniform(const std::string& name, const Texture& texture) const;

		/**
		 * @brief Send a light to the shader.
		 *
		 * @param name the name of the GLSL variable
		 * @param light the light to send
		 */
		void send_uniform(const std::string& name, const Light& light) const;

		/**
		 * @brief Send a light array to the shader.
		 *
		 * @param name the name of the GLSL array
		 * @param lights the light array to send
		 */
		void send_uniform(const std::string& name, const std::vector<Light*>& lights) const;

		/**
		 * @brief Send a material to the shader.
		 *
		 * @param name the name of the GLSL variable
		 * @param material the material to send
		 */
		void send_uniform(const std::string& name, const Material& material) const;

		/**
		 * @brief Send a float number to the shader.
		 *
		 * @param name the name of the GLSL variable
		 * @param number the float number to send
		 */
		void send_uniform(const std::string& name, float number) const;

		/**
		 * @brief Send a integer to the shader.
		 *
		 * @param name the name of the GLSL variable
		 * @param number the integer to send
		 */
		void send_uniform(const std::string& name, int number) const;

		/**
		 * @brief Send a float array to the shader (they can be grouped in vectors).
		 *
		 * @param name the name of the GLSL array
		 * @param numbers the float array to send
		 * @param group the size of the vectors (or 1 for a GLSL float array)
		 */
		void send_uniform(const std::string& name, const std::vector<float>& numbers, unsigned int group = 1) const;

		/**
		 * @brief Send a int array to the shader (they can be grouped in vectors).
		 *
		 * @param name the name of the GLSL array
		 * @param numbers the int array to send
		 * @param group the size of the vectors (or 1 for a GLSL float array)
		 */
		void send_uniform(const std::string& name, const std::vector<int>& numbers, unsigned int group = 1) const;

		/**
		 * @brief Send a 2D vector to the shader.
		 *
		 * @param name the name of the GLSL variable
		 * @param vector the 2D vector to send
		 */
		void send_uniform(const std::string& name, const Vector2& vector) const;

		/**
		 * @brief Send a 3D vector to the shader.
		 *
		 * @param name the name of the GLSL variable
		 * @param vector the 3D vector to send
		 */
		void send_uniform(const std::string& name, const Vector3& vector) const;

		/**
		 * @brief Send a 4D vector to the shader.
		 *
		 * @param name the name of the GLSL variable
		 * @param vector the 4D vector to send
		 */
		void send_uniform(const std::string& name, const Vector4& vector) const;

		/**
		 * @brief Send a color to the shader.
		 *
		 * @param name the name of the GLSL variable
		 * @param vector the color to send
		 */
		void send_uniform(const std::string& name, const Color& color) const;

		/**
		 * @brief Send a 2D vector array to the shader.
		 *
		 * @param name the name of the GLSL array
		 * @param vector the 2D vector array to send
		 */
		void send_uniform(const std::string& name, const std::vector<Vector2>& vectors) const;

		/**
		 * @brief Send a 3D vector array to the shader.
		 *
		 * @param name the name of the GLSL array
		 * @param vector the 3D vector array to send
		 */
		void send_uniform(const std::string& name, const std::vector<Vector3>& vectors) const;

		/**
		 * @brief Send a 4D vector array to the shader.
		 *
		 * @param name the name of the GLSL array
		 * @param vector the 4D vector array to send
		 */
		void send_uniform(const std::string& name, const std::vector<Vector4>& vectors) const;

		/**
		 * @brief Send a color array to the shader.
		 *
		 * @param name the name of the GLSL array
		 * @param vector the color array to send
		 */
		void send_uniform(const std::string& name, const std::vector<Color>& colors) const;

		/**
		 * @brief Send a 2x2 matrix to the shader.
		 *
		 * @param name the name of the GLSL variable
		 * @param vector the 2x2 matrix to send
		 */
		void send_uniform(const std::string& name, const glm::mat2& matrix) const;

		/**
		 * @brief Send a 3x3 matrix to the shader.
		 *
		 * @param name the name of the GLSL variable
		 * @param vector the 3x3 matrix to send
		 */
		void send_uniform(const std::string& name, const glm::mat3& matrix) const;

		/**
		 * @brief Send a 4x4 matrix to the shader.
		 *
		 * @param name the name of the GLSL variable
		 * @param vector the 4x4 matrix to send
		 */
		void send_uniform(const std::string& name, const glm::mat4& matrix) const;

		/**
		 * @brief Add a shader to the static shaders container (throw if the name already exists).
		 *
		 * @param name the name of the shader
		 * @param shader the shader to add
		 */
		static void add(const std::string& name, const Shader& shader);

		/**
		 * @brief Create a shader and add it to the static shaders container (throw if the name already exists).
		 *
		 * @param name the name of the shader
		 * @param vert_path the path to the vertex shader
		 * @param frag_path the path to the fragment shader
		 */
		static void add(const std::string& name, const std::string& vert_path, const std::string& frag_path);

		/**
		 * @brief Remove a shader from the static shaders container (throw if the name does not exist).
		 *
		 * @param name the name of the shader
		 */
		static void remove(const std::string& name);

		/**
		 * @brief Give a shader from the static shaders container (throw if the name does not exist).
		 *
		 * @param name the name of the shader
		 * @return the shader found
		 */
		static Shader get(const std::string& name);

		friend void init();
		friend void shut_down();
	};
}

#endif
