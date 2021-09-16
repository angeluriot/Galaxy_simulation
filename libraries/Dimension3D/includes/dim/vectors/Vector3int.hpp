#ifndef DIM_VECTOR3INT_HPP
#define DIM_VECTOR3INT_HPP

#include "dim/utils/libraries.hpp"

namespace dim
{
	class Vector2;
	class Vector3;
	class Vector4;
	class Vector2int;
	class Vector4int;

	/**
	 * @brief A class that represents a 3D int vector.
	 */
	class Vector3int
	{
	public:

		int						x;		// The X component.
		int						y;		// The Y component.
		int						z;		// The Z component.

		static const Vector3int	null;	// A vector full of 0.

		/**
		 * @brief Construct a new 3D int vector.
		 */
		Vector3int();

		/**
		 * @brief Construct a new 3D int vector from another.
		 *
		 * @param other the reference vector
		 */
		Vector3int(const Vector3int& other) = default;

		/**
		 * @brief Construct a new 3D int vector.
		 *
		 * @param x the X component
		 * @param y the Y component
		 * @param z the Z component
		 */
		Vector3int(int x, int y, int z);

		// Conversions

		Vector3int(const Vector2& other, int z);
		Vector3int(int x, const Vector2& other);
		Vector3int(const Vector3& other);
		Vector3int(const Vector4& other);
		Vector3int(const Vector2int& other, int z);
		Vector3int(int x, const Vector2int& other);
		Vector3int(const Vector4int& other);
		Vector3int(const std::array<float, 3>& other);
		Vector3int(const std::array<float, 4>& other);
		Vector3int(const std::array<int, 3>& other);
		Vector3int(const std::array<int, 4>& other);
		Vector3int(const glm::vec3& other);
		Vector3int(const glm::vec4& other);
		Vector3int(const sf::Vector3f& other);
		Vector3int(const sf::Vector3i& other);
		Vector3int(const ImVec4& other);

		/**
		 * @brief Copy the data of another vector.
		 *
		 * @param other the vector to copy
		 * @return a reference to the vector
		 */
		Vector3int& operator=(const Vector3int& other) = default;

		// Conversions

		Vector3int& operator=(const Vector3& other);
		Vector3int& operator=(const Vector4& other);
		Vector3int& operator=(const Vector4int& other);
		Vector3int& operator=(const std::array<float, 3>& other);
		Vector3int& operator=(const std::array<float, 4>& other);
		Vector3int& operator=(const std::array<int, 3>& other);
		Vector3int& operator=(const std::array<int, 4>& other);
		Vector3int& operator=(const glm::vec3& other);
		Vector3int& operator=(const glm::vec4& other);
		Vector3int& operator=(const sf::Vector3f& other);
		Vector3int& operator=(const sf::Vector3i& other);
		Vector3int& operator=(const ImVec4& other);

		// Operators

		Vector3int& operator+=(const Vector3int& other);
		Vector3int& operator-=(const Vector3int& other);

		/**
		 * @brief Multiply each component with those of the other vector (This is NEITHER a dot product NOR a cross product).
		 *
		 * @param other the other vector
		 * @return a reference to the vector
		 */
		Vector3int& operator*=(const Vector3int& other);

		// Operators

		Vector3int& operator*=(float number);
		Vector3int& operator*=(int number);
		Vector3int& operator/=(const Vector3int& other);
		Vector3int& operator/=(float number);
		Vector3int& operator/=(int number);
		Vector3int operator+() const;
		Vector3int operator-() const;

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
		std::array<float, 3> to_array_float() const;

		/**
		 * @brief Give an int array copy of the vector.
		 *
		 * @return the int array copy of the vector
		 */
		std::array<int, 3> to_array_int() const;

		/**
		 * @brief Give a GLM vector copy of the vector.
		 *
		 * @return the GLM vector copy of the vector
		 */
		glm::vec3 to_glm() const;

		/**
		 * @brief Give an SFML float vector copy of the vector.
		 *
		 * @return the SFML float vector copy of the vector
		 */
		sf::Vector3f to_sf_float() const;

		/**
		 * @brief Give an SFML int vector copy of the vector.
		 *
		 * @return the SFML int vector copy of the vector
		 */
		sf::Vector3i to_sf_int() const;
	};

	// Operators

	Vector3int operator+(const Vector3int& vector_1, const Vector3int& vector_2);
	Vector3int operator-(const Vector3int& vector_1, const Vector3int& vector_2);
	Vector3int operator*(float number, const Vector3int& vector);
	Vector3int operator*(const Vector3int& vector, float number);
	Vector3int operator*(int number, const Vector3int& vector);
	Vector3int operator*(const Vector3int& vector, int number);

	/**
	 * @brief Multiply each vectors component (This is NEITHER a dot product NOR a cross product).
	 *
	 * @param vector_1 the first vector
	 * @param vector_2 the second vector
	 * @return the result
	 */
	Vector3int operator*(const Vector3int& vector_1, const Vector3int& vector_2);

	// Operators

	Vector3int operator/(float number, const Vector3int& vector);
	Vector3int operator/(const Vector3int& vector, float number);
	Vector3int operator/(int number, const Vector3int& vector);
	Vector3int operator/(const Vector3int& vector, int number);
	Vector3int operator/(const Vector3int& vector_1, const Vector3int& vector_2);
	bool operator==(const Vector3int& vector_1, const Vector3int& vector_2);
	bool operator!=(const Vector3int& vector_1, const Vector3int& vector_2);
	std::ostream& operator<<(std::ostream& os, const Vector3int& vector);

	/**
	 * @brief Give the distance between two points.
	 *
	 * @param point_1 the first point
	 * @param point_2 the second point
	 * @return the distance between the two points
	 */
	float distance(const Vector3int& point_1, const Vector3int& point_2);

	/**
	 * @brief Give the squared distance between two points.
	 *
	 * @param point_1 the first point
	 * @param point_2 the second point
	 * @return the squared distance between the two points
	 */
	float distance_2(const Vector3int& point_1, const Vector3int& point_2);
}

#endif
