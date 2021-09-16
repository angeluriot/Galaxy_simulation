#ifndef DIM_VECTOR4_HPP
#define DIM_VECTOR4_HPP

#include "dim/utils/libraries.hpp"

namespace dim
{
	class Vector2;
	class Vector3;
	class Vector2int;
	class Vector3int;
	class Vector4int;
	class Color;

	/**
	 * @brief A class that represents a 4D float vector.
	 */
	class Vector4
	{
	public:

		float					x;		// The X component.
		float					y;		// The Y component.
		float					z;		// The Z component.
		float					w;		// The W component.

		static const Vector4	null;	// A vector full of 0.
		static const Vector4	unit;	// A vector with a norm of 1.

		/**
		 * @brief Construct a new 4D float vector.
		 */
		Vector4();

		/**
		 * @brief Construct a new 4D float vector from another.
		 *
		 * @param other the reference vector
		 */
		Vector4(const Vector4& other) = default;

		/**
		 * @brief Construct a new 3D float vector.
		 *
		 * @param x the X component
		 * @param y the Y component
		 * @param z the Z component
		 * @param w the W component
		 */
		Vector4(float x, float y, float z, float w);

		// Conversions

		Vector4(const Vector2& other, float z, float w);
		Vector4(float x, const Vector2& other, float w);
		Vector4(float x, float y, const Vector2& other);
		Vector4(const Vector3& other, float w);
		Vector4(float x, const Vector3& other);
		Vector4(const Vector2int& other, float z, float w);
		Vector4(float x, const Vector2int& other, float w);
		Vector4(float x, float y, const Vector2int& other);
		Vector4(const Vector3int& other, float w);
		Vector4(float x, const Vector3int& other);
		Vector4(const Vector4int& other);
		Vector4(const std::array<float, 4>& other);
		Vector4(const std::array<int, 4>& other);
		Vector4(const glm::vec4& other);
		Vector4(const ImVec4& other);
		Vector4(const Color& color);

		/**
		 * @brief Copy the data of another vector.
		 *
		 * @param other the vector to copy
		 * @return a reference to the vector
		 */
		Vector4& operator=(const Vector4& other) = default;

		// Conversions

		Vector4& operator=(const Vector4int& other);
		Vector4& operator=(const std::array<float, 4>& other);
		Vector4& operator=(const std::array<int, 4>& other);
		Vector4& operator=(const glm::vec4& other);
		Vector4& operator=(const ImVec4& other);
		Vector4& operator=(const Color& color);

		// Operators

		Vector4& operator+=(const Vector4& other);
		Vector4& operator-=(const Vector4& other);

		/**
		 * @brief Multiply each component with those of the other vector (This is NEITHER a dot product NOR a cross product).
		 *
		 * @param other the other vector
		 * @return a reference to the vector
		 */
		Vector4& operator*=(const Vector4& other);

		// Operators

		Vector4& operator*=(float number);
		Vector4& operator*=(int number);

		/**
		 * @brief Apply a 4x4 matrix to the vector.
		 *
		 * @param matrix the 4x4 matrix
		 * @return a reference to the vector
		 */
		Vector4& operator*=(const glm::mat4& matrix);

		// Operators

		Vector4& operator/=(const Vector4& other);
		Vector4& operator/=(float number);
		Vector4& operator/=(int number);
		Vector4 operator+() const;
		Vector4 operator-() const;

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
		const float* get_ptr() const;

		/**
		 * @brief Change the norm of the vector.
		 *
		 * @param norm the norm of the vector
		 */
		void set_norm(float norm);

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

	Vector4 operator+(const Vector4& vector_1, const Vector4& vector_2);
	Vector4 operator-(const Vector4& vector_1, const Vector4& vector_2);
	Vector4 operator*(float number, const Vector4& vector);
	Vector4 operator*(const Vector4& vector, float number);
	Vector4 operator*(int number, const Vector4& vector);
	Vector4 operator*(const Vector4& vector, int number);

	/**
	 * @brief Multiply each vectors component (This is NEITHER a dot product NOR a cross product).
	 *
	 * @param vector_1 the first vector
	 * @param vector_2 the second vector
	 * @return the result
	 */
	Vector4 operator*(const Vector4& vector_1, const Vector4& vector_2);

	/**
	 * @brief Apply a 4x4 matrix to a vector.
	 *
	 * @param matrix the 4x4 matrix
	 * @param vector the vector
	 * @return the transformed vector
	 */
	Vector4 operator*(const glm::mat4& matrix, const Vector4& vector);

	/**
	 * @brief Apply a 4x4 matrix to a vector.
	 *
	 * @param vector the vector
	 * @param matrix the 4x4 matrix
	 * @return the transformed vector
	 */
	Vector4 operator*(const Vector4& vector, const glm::mat4& matrix);

	// Operators

	Vector4 operator/(float number, const Vector4& vector);
	Vector4 operator/(const Vector4& vector, float number);
	Vector4 operator/(int number, const Vector4& vector);
	Vector4 operator/(const Vector4& vector, int number);
	Vector4 operator/(const Vector4& vector_1, const Vector4& vector_2);

	/**
	 * @brief Performs a dot product with the two vectors.
	 *
	 * @param vector_1 the first vector
	 * @param vector_2 the second vector
	 * @return the result
	 */
	float dot(const Vector4& vector_1, const Vector4& vector_2);

	// Operators

	bool operator==(const Vector4& vector_1, const Vector4& vector_2);
	bool operator!=(const Vector4& vector_1, const Vector4& vector_2);
	std::ostream& operator<<(std::ostream& os, const Vector4& vector);

	/**
	 * @brief Give the distance between two points.
	 *
	 * @param point_1 the first point
	 * @param point_2 the second point
	 * @return the distance between the two points
	 */
	float distance(const Vector4& point_1, const Vector4& point_2);

	/**
	 * @brief Give the squared distance between two points.
	 *
	 * @param point_1 the first point
	 * @param point_2 the second point
	 * @return the squared distance between the two points
	 */
	float distance_2(const Vector4& point_1, const Vector4& point_2);

	/**
	 * @brief Give the normalize version of the vector.
	 *
	 * @param vector the input vector
	 * @return the output normalized vector
	 */
	Vector4 normalize(const Vector4& vector);
}

#endif
