#ifndef DIM_VECTOR3_HPP
#define DIM_VECTOR3_HPP

#include "dim/utils/libraries.hpp"

namespace dim
{
	class Vector2;
	class Vector4;
	class Vector2int;
	class Vector3int;
	class Vector4int;
	class Color;

	/**
	 * @brief A class that represents a 3D float vector.
	 */
	class Vector3
	{
	public:

		float					x;		// The X component.
		float					y;		// The Y component.
		float					z;		// The Z component.

		static const Vector3	null;	// A vector full of 0.
		static const Vector3	unit;	// A vector with a norm of 1.

		/**
		 * @brief Construct a new 3D float vector.
		 */
		Vector3();

		/**
		 * @brief Construct a new 3D float vector from another.
		 *
		 * @param other the reference vector
		 */
		Vector3(const Vector3& other) = default;

		/**
		 * @brief Construct a new 3D float vector.
		 *
		 * @param x the X component
		 * @param y the Y component
		 * @param z the Z component
		 */
		Vector3(float x, float y, float z);

		// Conversions

		Vector3(const Vector2& other, float z);
		Vector3(float x, const Vector2& other);
		Vector3(const Vector4& other);
		Vector3(const Vector2int& other, float z);
		Vector3(float x, const Vector2int& other);
		Vector3(const Vector3int& other);
		Vector3(const Vector4int& other);
		Vector3(const std::array<float, 3>& other);
		Vector3(const std::array<float, 4>& other);
		Vector3(const std::array<int, 3>& other);
		Vector3(const std::array<int, 4>& other);
		Vector3(const glm::vec3& other);
		Vector3(const glm::vec4& other);
		Vector3(const sf::Vector3f& other);
		Vector3(const sf::Vector3i& other);
		Vector3(const ImVec4& other);
		Vector3(const sf::Color& color);

		/**
		 * @brief Contruct a new 3D float vector from cartesian coordinates.
		 *
		 * @param x the X coordinate
		 * @param y the Y coordinate
		 * @param y the Z coordinate
		 * @return the new 3D float vector
		 */
		static Vector3 Cartesian(float x, float y, float z);

		/**
		 * @brief Contruct a new 3D float vector from spherical coordinates.
		 *
		 * @param norm the norm of the vector
		 * @param theta the theta angle of the vector
		 * @param phi the phi angle of the vector
		 * @return the new 3D float vector
		 */
		static Vector3 Spherical(float norm, float theta, float phi);

		/**
		 * @brief Copy the data of another vector.
		 *
		 * @param other the vector to copy
		 * @return a reference to the vector
		 */
		Vector3& operator=(const Vector3& other) = default;

		// Conversions

		Vector3& operator=(const Vector4& other);
		Vector3& operator=(const Vector3int& other);
		Vector3& operator=(const Vector4int& other);
		Vector3& operator=(const std::array<float, 3>& other);
		Vector3& operator=(const std::array<float, 4>& other);
		Vector3& operator=(const std::array<int, 3>& other);
		Vector3& operator=(const std::array<int, 4>& other);
		Vector3& operator=(const glm::vec3& other);
		Vector3& operator=(const glm::vec4& other);
		Vector3& operator=(const sf::Vector3f& other);
		Vector3& operator=(const sf::Vector3i& other);
		Vector3& operator=(const ImVec4& other);
		Vector3& operator=(const sf::Color& color);

		// Operators

		Vector3& operator+=(const Vector3& other);
		Vector3& operator-=(const Vector3& other);

		/**
		 * @brief Multiply each component with those of the other vector (This is NEITHER a dot product NOR a cross product).
		 *
		 * @param other the other vector
		 * @return a reference to the vector
		 */
		Vector3& operator*=(const Vector3& other);

		// Operators

		Vector3& operator*=(float number);
		Vector3& operator*=(int number);

		/**
		 * @brief Apply a 3x3 matrix to the vector.
		 *
		 * @param matrix the 3x3 matrix
		 * @return a reference to the vector
		 */
		Vector3& operator*=(const glm::mat3& matrix);

		/**
		 * @brief Apply a 4x4 matrix to the vector.
		 *
		 * @param matrix the 4x4 matrix
		 * @return a reference to the vector
		 */
		Vector3& operator*=(const glm::mat4& matrix);

		// Operators

		Vector3& operator/=(const Vector3& other);
		Vector3& operator/=(float number);
		Vector3& operator/=(int number);

		/**
		 * @brief Performs a cross product with the other vector.
		 *
		 * @param other the other vector
		 * @return a reference to the vector
		 */
		Vector3& operator^=(const Vector3& other);

		// Operators

		Vector3 operator+() const;
		Vector3 operator-() const;

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
		 * @brief Give the spherical theta angle of the vector.
		 *
		 * @return the spherical theta angle of the vector
		 */
		float get_theta() const;

		/**
		 * @brief Give the spherical phi angle of the vector.
		 *
		 * @return the spherical phi angle of the vector
		 */
		float get_phi() const;

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
		 * @brief Change the spherical theta angle of the vector.
		 *
		 * @param angle the spherical theta angle of the vector
		 */
		void set_theta(float theta);

		/**
		 * @brief Change the spherical phi angle of the vector.
		 *
		 * @param angle the spherical phi angle of the vector
		 */
		void set_phi(float phi);

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

	Vector3 operator+(const Vector3& vector_1, const Vector3& vector_2);
	Vector3 operator-(const Vector3& vector_1, const Vector3& vector_2);
	Vector3 operator*(float number, const Vector3& vector);
	Vector3 operator*(const Vector3& vector, float number);
	Vector3 operator*(int number, const Vector3& vector);
	Vector3 operator*(const Vector3& vector, int number);

	/**
	 * @brief Multiply each vectors component (This is NEITHER a dot product NOR a cross product).
	 *
	 * @param vector_1 the first vector
	 * @param vector_2 the second vector
	 * @return the result
	 */
	Vector3 operator*(const Vector3& vector_1, const Vector3& vector_2);

	/**
	 * @brief Apply a 3x3 matrix to a vector.
	 *
	 * @param matrix the 3x3 matrix
	 * @param vector the vector
	 * @return the transformed vector
	 */
	Vector3 operator*(const glm::mat3& matrix, const Vector3& vector);

	/**
	 * @brief Apply a 3x3 matrix to a vector.
	 *
	 * @param vector the vector
	 * @param matrix the 3x3 matrix
	 * @return the transformed vector
	 */
	Vector3 operator*(const Vector3& vector, const glm::mat3& matrix);

	/**
	 * @brief Apply a 4x4 matrix to a vector.
	 *
	 * @param matrix the 4x4 matrix
	 * @param vector the vector
	 * @return the transformed vector
	 */
	Vector3 operator*(const glm::mat4& matrix, const Vector3& vector);

	/**
	 * @brief Apply a 4x4 matrix to a vector.
	 *
	 * @param vector the vector
	 * @param matrix the 4x4 matrix
	 * @return the transformed vector
	 */
	Vector3 operator*(const Vector3& vector, const glm::mat4& matrix);

	// Operators

	Vector3 operator/(float number, const Vector3& vector);
	Vector3 operator/(const Vector3& vector, float number);
	Vector3 operator/(int number, const Vector3& vector);
	Vector3 operator/(const Vector3& vector, int number);
	Vector3 operator/(const Vector3& vector_1, const Vector3& vector_2);

	/**
	 * @brief Performs a cross product with the two vectors.
	 *
	 * @param vector_1 the first vector
	 * @param vector_2 the second vector
	 * @return a reference to the vector
	 */
	Vector3 operator^(const Vector3& vector_1, const Vector3& vector_2);

	/**
	 * @brief Performs a dot product with the two vectors.
	 *
	 * @param vector_1 the first vector
	 * @param vector_2 the second vector
	 * @return the result
	 */
	float dot(const Vector3& vector_1, const Vector3& vector_2);

	// Operators

	bool operator==(const Vector3& vector_1, const Vector3& vector_2);
	bool operator!=(const Vector3& vector_1, const Vector3& vector_2);
	std::ostream& operator<<(std::ostream& os, const Vector3& vector);

	/**
	 * @brief Give the distance between two points.
	 *
	 * @param point_1 the first point
	 * @param point_2 the second point
	 * @return the distance between the two points
	 */
	float distance(const Vector3& point_1, const Vector3& point_2);

	/**
	 * @brief Give the squared distance between two points.
	 *
	 * @param point_1 the first point
	 * @param point_2 the second point
	 * @return the squared distance between the two points
	 */
	float distance_2(const Vector3& point_1, const Vector3& point_2);

	/**
	 * @brief Give the spherical theta angle between two points.
	 *
	 * @param point_1 the first point
	 * @param point_2 the second point
	 * @return the spherical theta angle between the two points
	 */
	float theta(const Vector3& point_1, const Vector3& point_2);

	/**
	 * @brief Give the spherical phi angle between two points.
	 *
	 * @param point_1 the first point
	 * @param point_2 the second point
	 * @return the spherical phi angle between the two points
	 */
	float phi(const Vector3& point_1, const Vector3& point_2);

	/**
	 * @brief Give the normalize version of the vector.
	 *
	 * @param vector the input vector
	 * @return the output normalized vector
	 */
	Vector3 normalize(const Vector3& vector);
}

#endif
