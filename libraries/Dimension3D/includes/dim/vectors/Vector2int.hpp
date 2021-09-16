#ifndef DIM_VECTOR2INT_HPP
#define DIM_VECTOR2INT_HPP

#include "dim/utils/libraries.hpp"

namespace dim
{
	class Vector2;
	class Vector3;
	class Vector4;
	class Vector3int;
	class Vector4int;

	/**
	 * @brief A class that represents a 2D int vector.
	 */
	class Vector2int
	{
	public:

		int						x;		// The X component.
		int						y;		// The Y component.

		static const Vector2int	null;	// A vector full of 0.

		/**
		 * @brief Construct a new 2D int vector.
		 */
		Vector2int();

		/**
		 * @brief Construct a new 2D int vector from another.
		 *
		 * @param other the reference vector
		 */
		Vector2int(const Vector2int& other) = default;

		/**
		 * @brief Construct a new 2D int vector.
		 *
		 * @param x the X component
		 * @param y the Y component
		 */
		Vector2int(int x, int y);

		// Conversions

		Vector2int(const Vector2& other);
		Vector2int(const Vector3& other);
		Vector2int(const Vector4& other);
		Vector2int(const Vector3int& other);
		Vector2int(const Vector4int& other);
		Vector2int(const std::array<float, 2>& other);
		Vector2int(const std::array<float, 3>& other);
		Vector2int(const std::array<float, 4>& other);
		Vector2int(const std::array<int, 2>& other);
		Vector2int(const std::array<int, 3>& other);
		Vector2int(const std::array<int, 4>& other);
		Vector2int(const glm::vec2& other);
		Vector2int(const glm::vec3& other);
		Vector2int(const glm::vec4& other);
		Vector2int(const sf::Vector2f& other);
		Vector2int(const sf::Vector3f& other);
		Vector2int(const sf::Vector2i& other);
		Vector2int(const sf::Vector3i& other);
		Vector2int(const ImVec2& other);
		Vector2int(const ImVec4& other);

		/**
		 * @brief Copy the data of another vector.
		 *
		 * @param other the vector to copy
		 * @return a reference to the vector
		 */
		Vector2int& operator=(const Vector2int& other) = default;

		// Conversions

		Vector2int& operator=(const Vector2& other);
		Vector2int& operator=(const Vector3& other);
		Vector2int& operator=(const Vector4& other);
		Vector2int& operator=(const Vector3int& other);
		Vector2int& operator=(const Vector4int& other);
		Vector2int& operator=(const std::array<float, 2>& other);
		Vector2int& operator=(const std::array<float, 3>& other);
		Vector2int& operator=(const std::array<float, 4>& other);
		Vector2int& operator=(const std::array<int, 2>& other);
		Vector2int& operator=(const std::array<int, 3>& other);
		Vector2int& operator=(const std::array<int, 4>& other);
		Vector2int& operator=(const glm::vec2& other);
		Vector2int& operator=(const glm::vec3& other);
		Vector2int& operator=(const glm::vec4& other);
		Vector2int& operator=(const sf::Vector2f& other);
		Vector2int& operator=(const sf::Vector3f& other);
		Vector2int& operator=(const sf::Vector2i& other);
		Vector2int& operator=(const sf::Vector3i& other);
		Vector2int& operator=(const ImVec2& other);
		Vector2int& operator=(const ImVec4& other);

		// Operators

		Vector2int& operator+=(const Vector2int& other);
		Vector2int& operator-=(const Vector2int& other);

		/**
		 * @brief Multiply each component with those of the other vector (this is NOT a dot product).
		 *
		 * @param other the other vector
		 * @return a reference to the vector
		 */
		Vector2int& operator*=(const Vector2int& other);

		// Operators

		Vector2int& operator*=(float number);
		Vector2int& operator*=(int number);
		Vector2int& operator/=(const Vector2int& other);
		Vector2int& operator/=(float number);
		Vector2int& operator/=(int number);
		Vector2int operator+() const;
		Vector2int operator-() const;

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
		 * @brief Give a pointer to the vector's data.
		 *
		 * @return a pointer to the vector's data
		 */
		const int* get_ptr() const;

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

	Vector2int operator+(const Vector2int& vector_1, const Vector2int& vector_2);
	Vector2int operator-(const Vector2int& vector_1, const Vector2int& vector_2);
	Vector2int operator*(float number, const Vector2int& vector);
	Vector2int operator*(const Vector2int& vector, float number);
	Vector2int operator*(int number, const Vector2int& vector);
	Vector2int operator*(const Vector2int& vector, int number);

	/**
	 * @brief Multiply each vectors component (this is NOT a dot product).
	 *
	 * @param vector_1 the first vector
	 * @param vector_2 the second vector
	 * @return the result
	 */
	Vector2int operator*(const Vector2int& vector_1, const Vector2int& vector_2);

	// Operators

	Vector2int operator/(float number, const Vector2int& vector);
	Vector2int operator/(const Vector2int& vector, float number);
	Vector2int operator/(int number, const Vector2int& vector);
	Vector2int operator/(const Vector2int& vector, int number);
	Vector2int operator/(const Vector2int& vector_1, const Vector2int& vector_2);
	bool operator==(const Vector2int& vector_1, const Vector2int& vector_2);
	bool operator!=(const Vector2int& vector_1, const Vector2int& vector_2);
	std::ostream& operator<<(std::ostream& os, const Vector2int& vector);

	/**
	 * @brief Give the distance between two points.
	 *
	 * @param point_1 the first point
	 * @param point_2 the second point
	 * @return the distance between the two points
	 */
	float distance(const Vector2int& point_1, const Vector2int& point_2);

	/**
	 * @brief Give the squared distance between two points.
	 *
	 * @param point_1 the first point
	 * @param point_2 the second point
	 * @return the squared distance between the two points
	 */
	float distance_2(const Vector2int& point_1, const Vector2int& point_2);
}

#endif
