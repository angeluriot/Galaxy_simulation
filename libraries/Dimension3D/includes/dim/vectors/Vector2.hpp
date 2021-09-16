#ifndef DIM_VECTOR2_HPP
#define DIM_VECTOR2_HPP

#include "dim/utils/libraries.hpp"

namespace dim
{
	class Vector3;
	class Vector4;
	class Vector2int;
	class Vector3int;
	class Vector4int;

	/**
	 * @brief A class that represents a 2D float vector.
	 */
	class Vector2
	{
	public:

		float					x;		// The X component.
		float					y;		// The Y component.

		static const Vector2	null;	// A vector full of 0.
		static const Vector2	unit;	// A vector with a norm of 1.

		/**
		 * @brief Construct a new 2D float vector.
		 */
		Vector2();

		/**
		 * @brief Construct a new 2D float vector from another.
		 *
		 * @param other the reference vector
		 */
		Vector2(const Vector2& other) = default;

		/**
		 * @brief Construct a new 2D float vector.
		 *
		 * @param x the X component
		 * @param y the Y component
		 */
		Vector2(float x, float y);

		// Conversions

		Vector2(const Vector3& other);
		Vector2(const Vector4& other);
		Vector2(const Vector2int& other);
		Vector2(const Vector3int& other);
		Vector2(const Vector4int& other);
		Vector2(const std::array<float, 2>& other);
		Vector2(const std::array<float, 3>& other);
		Vector2(const std::array<float, 4>& other);
		Vector2(const std::array<int, 2>& other);
		Vector2(const std::array<int, 3>& other);
		Vector2(const std::array<int, 4>& other);
		Vector2(const glm::vec2& other);
		Vector2(const glm::vec3& other);
		Vector2(const glm::vec4& other);
		Vector2(const sf::Vector2f& other);
		Vector2(const sf::Vector3f& other);
		Vector2(const sf::Vector2i& other);
		Vector2(const sf::Vector3i& other);
		Vector2(const ImVec2& other);
		Vector2(const ImVec4& other);

		/**
		 * @brief Contruct a new 2D float vector from cartesian coordinates.
		 *
		 * @param x the X coordinate
		 * @param y the Y coordinate
		 * @return the new 2D float vector
		 */
		static Vector2 Cartesian(float x, float y);

		/**
		 * @brief Contruct a new 2D float vector from polar coordinates.
		 *
		 * @param norm the norm of the vector
		 * @param angle the angle of the vector
		 * @return the new 2D float vector
		 */
		static Vector2 Polar(float norm, float angle);

		/**
		 * @brief Copy the data of another vector.
		 *
		 * @param other the vector to copy
		 * @return a reference to the vector
		 */
		Vector2& operator=(const Vector2& other) = default;

		// Conversions

		Vector2& operator=(const Vector3& other);
		Vector2& operator=(const Vector4& other);
		Vector2& operator=(const Vector2int& other);
		Vector2& operator=(const Vector3int& other);
		Vector2& operator=(const Vector4int& other);
		Vector2& operator=(const std::array<float, 2>& other);
		Vector2& operator=(const std::array<float, 3>& other);
		Vector2& operator=(const std::array<float, 4>& other);
		Vector2& operator=(const std::array<int, 2>& other);
		Vector2& operator=(const std::array<int, 3>& other);
		Vector2& operator=(const std::array<int, 4>& other);
		Vector2& operator=(const glm::vec2& other);
		Vector2& operator=(const glm::vec3& other);
		Vector2& operator=(const glm::vec4& other);
		Vector2& operator=(const sf::Vector2f& other);
		Vector2& operator=(const sf::Vector3f& other);
		Vector2& operator=(const sf::Vector2i& other);
		Vector2& operator=(const sf::Vector3i& other);
		Vector2& operator=(const ImVec2& other);
		Vector2& operator=(const ImVec4& other);

		// Operators

		Vector2& operator+=(const Vector2& other);
		Vector2& operator-=(const Vector2& other);

		/**
		 * @brief Multiply each component with those of the other vector (this is NOT a dot product, use the dot function for that).
		 *
		 * @param other the other vector
		 * @return a reference to the vector
		 */
		Vector2& operator*=(const Vector2& other);

		// Operators

		Vector2& operator*=(float number);
		Vector2& operator*=(int number);

		/**
		 * @brief Apply a 2x2 matrix to the vector.
		 *
		 * @param matrix the 2x2 matrix
		 * @return a reference to the vector
		 */
		Vector2& operator*=(const glm::mat2& matrix);

		/**
		 * @brief Apply a 3x3 matrix to the vector.
		 *
		 * @param matrix the 3x3 matrix
		 * @return a reference to the vector
		 */
		Vector2& operator*=(const glm::mat3& matrix);

		// Operators

		Vector2& operator/=(const Vector2& other);
		Vector2& operator/=(float number);
		Vector2& operator/=(int number);
		Vector2 operator+() const;
		Vector2 operator-() const;

		/**
		 * @brief Give the norm of the vector.
		 *
		 * @return the norm of the vector
		 */
		float get_norm() const;

		/**
		 * @brief Give the squared norm of the vector.
		 *
		 * @return the squared norm of the vector
		 */
		float get_norm_2() const;

		/**
		 * @brief Give the polar angle of the vector.
		 *
		 * @return the polar angle of the vector
		 */
		float get_angle() const;

		/**
		 * @brief Give a pointer to the vector's data.
		 *
		 * @return a pointer to the vector's data
		 */
		const float* get_ptr() const;

		/**
		 * @brief Change the norm of the vector.
		 *
		 * @param norm the norm of the vector
		 */
		void set_norm(float norm);

		/**
		 * @brief Change the polar angle of the vector.
		 *
		 * @param angle the polar angle of the vector
		 */
		void set_angle(float angle);

		/**
		 * @brief Normalize the vector.
		 */
		void normalize();

		/**
		 * @brief Set all components to 0.
		 */
		void clear();

		/**
		 * @brief Give a float array copy of the vector.
		 *
		 * @return the float array copy of the vector
		 */
		std::array<float, 2> to_array_float() const;

		/**
		 * @brief Give an int array copy of the vector.
		 *
		 * @return the int array copy of the vector
		 */
		std::array<int, 2> to_array_int() const;

		/**
		 * @brief Give a GLM vector copy of the vector.
		 *
		 * @return the GLM vector copy of the vector
		 */
		glm::vec2 to_glm() const;

		/**
		 * @brief Give an SFML float vector copy of the vector.
		 *
		 * @return the SFML float vector copy of the vector
		 */
		sf::Vector2f to_sf_float() const;

		/**
		 * @brief Give an SFML int vector copy of the vector.
		 *
		 * @return the SFML int vector copy of the vector
		 */
		sf::Vector2i to_sf_int() const;

		/**
		 * @brief Give an ImGui vector copy of the vector.
		 *
		 * @return the ImGui vector copy of the vector
		 */
		ImVec2 to_imgui() const;
	};

	// Operators

	Vector2 operator+(const Vector2& vector_1, const Vector2& vector_2);
	Vector2 operator-(const Vector2& vector_1, const Vector2& vector_2);
	Vector2 operator*(float number, const Vector2& vector);
	Vector2 operator*(const Vector2& vector, float number);
	Vector2 operator*(int number, const Vector2& vector);
	Vector2 operator*(const Vector2& vector, int number);

	/**
	 * @brief Multiply each vectors component (this is NOT a dot product, use the dot function for that).
	 *
	 * @param vector_1 the first vector
	 * @param vector_2 the second vector
	 * @return the result
	 */
	Vector2 operator*(const Vector2& vector_1, const Vector2& vector_2);

	/**
	 * @brief Apply a 2x2 matrix to a vector.
	 *
	 * @param matrix the 2x2 matrix
	 * @param vector the vector
	 * @return the transformed vector
	 */
	Vector2 operator*(const glm::mat2& matrix, const Vector2& vector);

	/**
	 * @brief Apply a 2x2 matrix to a vector.
	 *
	 * @param vector the vector
	 * @param matrix the 2x2 matrix
	 * @return the transformed vector
	 */
	Vector2 operator*(const Vector2& vector, const glm::mat2& matrix);

	/**
	 * @brief Apply a 3x3 matrix to a vector.
	 *
	 * @param matrix the 3x3 matrix
	 * @param vector the vector
	 * @return the transformed vector
	 */
	Vector2 operator*(const glm::mat3& matrix, const Vector2& vector);

	/**
	 * @brief Apply a 3x3 matrix to a vector.
	 *
	 * @param vector the vector
	 * @param matrix the 3x3 matrix
	 * @return the transformed vector
	 */
	Vector2 operator*(const Vector2& vector, const glm::mat3& matrix);

	// Operators

	Vector2 operator/(float number, const Vector2& vector);
	Vector2 operator/(const Vector2& vector, float number);
	Vector2 operator/(int number, const Vector2& vector);
	Vector2 operator/(const Vector2& vector, int number);
	Vector2 operator/(const Vector2& vector_1, const Vector2& vector_2);

	/**
	 * @brief Performs a dot product with the two vectors.
	 *
	 * @param vector_1 the first vector
	 * @param vector_2 the second vector
	 * @return the result
	 */
	float dot(const Vector2& vector_1, const Vector2& vector_2);

	// Operators

	bool operator==(const Vector2& vector_1, const Vector2& vector_2);
	bool operator!=(const Vector2& vector_1, const Vector2& vector_2);
	std::ostream& operator<<(std::ostream& os, const Vector2& vector);

	/**
	 * @brief Give the distance between two points.
	 *
	 * @param point_1 the first point
	 * @param point_2 the second point
	 * @return the distance between the two points
	 */
	float distance(const Vector2& point_1, const Vector2& point_2);

	/**
	 * @brief Give the squared distance between two points.
	 *
	 * @param point_1 the first point
	 * @param point_2 the second point
	 * @return the squared distance between the two points
	 */
	float distance_2(const Vector2& point_1, const Vector2& point_2);

	/**
	 * @brief Give the polar angle between two points.
	 *
	 * @param point_1 the first point
	 * @param point_2 the second point
	 * @return the polar angle between the two points
	 */
	float angle(const Vector2& point_1, const Vector2& point_2);

	/**
	 * @brief Give the normalize version of the vector.
	 *
	 * @param vector the input vector
	 * @return the output normalized vector
	 */
	Vector2 normalize(const Vector2& vector);
}

#endif
