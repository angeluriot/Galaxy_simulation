#ifndef DIM_VECTOR4INT_HPP
#define DIM_VECTOR4INT_HPP

#include "dim/utils/libraries.hpp"

namespace dim
{
	class Vector2;
	class Vector3;
	class Vector4;
	class Vector2int;
	class Vector3int;

	/**
	 * @brief A class that represents a 4D int vector.
	 */
	class Vector4int
	{
	public:

		int						x;		// The X component.
		int						y;		// The Y component.
		int						z;		// The Z component.
		int						w;		// The W component.

		static const Vector4int	null;	// A vector full of 0.

		/**
		 * @brief Construct a new 4D int vector.
		 */
		Vector4int();

		/**
		 * @brief Construct a new 4D int vector from another.
		 *
		 * @param other the reference vector
		 */
		Vector4int(const Vector4int& other) = default;

		/**
		 * @brief Construct a new 4D int vector.
		 *
		 * @param x the X component
		 * @param y the Y component
		 * @param z the Z component
		 */
		Vector4int(int x, int y, int z, int w);

		// Conversions

		Vector4int(const Vector2& other, int z, int w);
		Vector4int(int x, const Vector2& other, int w);
		Vector4int(int x, int y, const Vector2& other);
		Vector4int(const Vector3& other, int w);
		Vector4int(int x, const Vector3& other);
		Vector4int(const Vector4& other);
		Vector4int(const Vector2int& other, int z, int w);
		Vector4int(int x, const Vector2int& other, int w);
		Vector4int(int x, int y, const Vector2int& other);
		Vector4int(const Vector3int& other, int w);
		Vector4int(int x, const Vector3int& other);
		Vector4int(const std::array<float, 4>& other);
		Vector4int(const std::array<int, 4>& other);
		Vector4int(const glm::vec4& other);
		Vector4int(const ImVec4& other);

		/**
		 * @brief Copy the data of another vector.
		 *
		 * @param other the vector to copy
		 * @return a reference to the vector
		 */
		Vector4int& operator=(const Vector4int& other) = default;

		// Conversions

		Vector4int& operator=(const Vector4& other);
		Vector4int& operator=(const std::array<float, 4>& other);
		Vector4int& operator=(const std::array<int, 4>& other);
		Vector4int& operator=(const glm::vec4& other);
		Vector4int& operator=(const ImVec4& other);

		// Operators

		Vector4int& operator+=(const Vector4int& other);
		Vector4int& operator-=(const Vector4int& other);

		/**
		 * @brief Multiply each component with those of the other vector (This is NEITHER a dot product NOR a cross product).
		 *
		 * @param other the other vector
		 * @return a reference to the vector
		 */
		Vector4int& operator*=(const Vector4int& other);

		// Operators

		Vector4int& operator*=(float number);
		Vector4int& operator*=(int number);
		Vector4int& operator/=(const Vector4int& other);
		Vector4int& operator/=(float number);
		Vector4int& operator/=(int number);
		Vector4int operator+() const;
		Vector4int operator-() const;

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
		std::array<float, 4> to_array_float() const;

		/**
		 * @brief Give an int array copy of the vector.
		 *
		 * @return the int array copy of the vector
		 */
		std::array<int, 4> to_array_int() const;

		/**
		 * @brief Give a GLM vector copy of the vector.
		 *
		 * @return the GLM vector copy of the vector
		 */
		glm::vec4 to_glm() const;

		/**
		 * @brief Give an ImGui vector copy of the vector.
		 *
		 * @return the ImGui vector copy of the vector
		 */
		ImVec4 to_imgui() const;
	};

	// Operators

	Vector4int operator+(const Vector4int& vector_1, const Vector4int& vector_2);
	Vector4int operator-(const Vector4int& vector_1, const Vector4int& vector_2);
	Vector4int operator*(float number, const Vector4int& vector);
	Vector4int operator*(const Vector4int& vector, float number);
	Vector4int operator*(int number, const Vector4int& vector);
	Vector4int operator*(const Vector4int& vector, int number);

	/**
	 * @brief Multiply each vectors component (This is NEITHER a dot product NOR a cross product).
	 *
	 * @param vector_1 the first vector
	 * @param vector_2 the second vector
	 * @return the result
	 */
	Vector4int operator*(const Vector4int& vector_1, const Vector4int& vector_2);

	// Operators

	Vector4int operator/(float number, const Vector4int& vector);
	Vector4int operator/(const Vector4int& vector, float number);
	Vector4int operator/(int number, const Vector4int& vector);
	Vector4int operator/(const Vector4int& vector, int number);
	Vector4int operator/(const Vector4int& vector_1, const Vector4int& vector_2);
	bool operator==(const Vector4int& vector_1, const Vector4int& vector_2);
	bool operator!=(const Vector4int& vector_1, const Vector4int& vector_2);
	std::ostream& operator<<(std::ostream& os, const Vector4int& vector);

	/**
	 * @brief Give the distance between two points.
	 *
	 * @param point_1 the first point
	 * @param point_2 the second point
	 * @return the distance between the two points
	 */
	float distance(const Vector4int& point_1, const Vector4int& point_2);

	/**
	 * @brief Give the squared distance between two points.
	 *
	 * @param point_1 the first point
	 * @param point_2 the second point
	 * @return the squared distance between the two points
	 */
	float distance_2(const Vector4int& point_1, const Vector4int& point_2);
}

#endif
