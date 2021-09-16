#ifndef DIM_COMPUTE_SHADER_HPP
#define DIM_COMPUTE_SHADER_HPP

#include "dim/utils/libraries.hpp"

namespace dim
{
	class ComputeShader
	{
	private:

		std::shared_ptr<GLuint>	id;
		std::shared_ptr<GLuint>	program_id;

	public:

		ComputeShader();
		ComputeShader(const ComputeShader& other) = default;
		ComputeShader(const std::string& path);

		ComputeShader& operator=(const ComputeShader& other) = default;

		void load(const std::string& path);
		GLuint get_id() const;
		void bind() const;
		static void unbind();
		void launch(unsigned int groups_nb_x, unsigned int groups_nb_y, unsigned int groups_nb_z) const;

		/**
		 * @brief Send a float number to the compute shader.
		 *
		 * @param location the object location id in the compute shader
		 * @param number the float number to send
		 */
		void send_uniform(unsigned int location, float number) const;

		/**
		 * @brief Send a integer to the compute shader.
		 *
		 * @param location the object location id in the compute shader
		 * @param number the integer to send
		 */
		void send_uniform(unsigned int location, int number) const;

		/**
		 * @brief Send a float array to the compute shader (they can be grouped in vectors).
		 *
		 * @param location the object location id in the compute shader
		 * @param numbers the float array to send
		 * @param group the size of the vectors (or 1 for a GLSL float array)
		 */
		void send_uniform(unsigned int location, const std::vector<float>& numbers, unsigned int group = 1) const;

		/**
		 * @brief Send a int array to the compute shader (they can be grouped in vectors).
		 *
		 * @param location the object location id in the compute shader
		 * @param numbers the int array to send
		 * @param group the size of the vectors (or 1 for a GLSL float array)
		 */
		void send_uniform(unsigned int location, const std::vector<int>& numbers, unsigned int group = 1) const;

		/**
		 * @brief Send a 2D vector to the compute shader.
		 *
		 * @param location the object location id in the compute shader
		 * @param vector the 2D vector to send
		 */
		void send_uniform(unsigned int location, const Vector2& vector) const;

		/**
		 * @brief Send a 3D vector to the compute shader.
		 *
		 * @param location the object location id in the compute shader
		 * @param vector the 3D vector to send
		 */
		void send_uniform(unsigned int location, const Vector3& vector) const;

		/**
		 * @brief Send a 4D vector to the compute shader.
		 *
		 * @param location the object location id in the compute shader
		 * @param vector the 4D vector to send
		 */
		void send_uniform(unsigned int location, const Vector4& vector) const;

		/**
		 * @brief Send a color to the compute shader.
		 *
		 * @param location the object location id in the compute shader
		 * @param vector the color to send
		 */
		void send_uniform(unsigned int location, const Color& color) const;

		/**
		 * @brief Send a 2D vector array to the compute shader.
		 *
		 * @param location the object location id in the compute shader
		 * @param vector the 2D vector array to send
		 */
		void send_uniform(unsigned int location, const std::vector<Vector2>& vectors) const;

		/**
		 * @brief Send a 3D vector array to the compute shader.
		 *
		 * @param location the object location id in the compute shader
		 * @param vector the 3D vector array to send
		 */
		void send_uniform(unsigned int location, const std::vector<Vector3>& vectors) const;

		/**
		 * @brief Send a 4D vector array to the compute shader.
		 *
		 * @param location the object location id in the compute shader
		 * @param vector the 4D vector array to send
		 */
		void send_uniform(unsigned int location, const std::vector<Vector4>& vectors) const;

		/**
		 * @brief Send a color array to the compute shader.
		 *
		 * @param location the object location id in the compute shader
		 * @param vector the color array to send
		 */
		void send_uniform(unsigned int location, const std::vector<Color>& colors) const;

		/**
		 * @brief Send a 2x2 matrix to the compute shader.
		 *
		 * @param location the object location id in the compute shader
		 * @param vector the 2x2 matrix to send
		 */
		void send_uniform(unsigned int location, const glm::mat2& matrix) const;

		/**
		 * @brief Send a 3x3 matrix to the compute shader.
		 *
		 * @param location the object location id in the compute shader
		 * @param vector the 3x3 matrix to send
		 */
		void send_uniform(unsigned int location, const glm::mat3& matrix) const;

		/**
		 * @brief Send a 4x4 matrix to the compute shader.
		 *
		 * @param location the object location id in the compute shader
		 * @param vector the 4x4 matrix to send
		 */
		void send_uniform(unsigned int location, const glm::mat4& matrix) const;
	};
}

#endif
