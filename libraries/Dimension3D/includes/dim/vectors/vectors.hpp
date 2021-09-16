#ifndef VECTORS_HPP
#define VECTORS_HPP

#include "dim/utils/libraries.hpp"

namespace dim
{
	// Operators

	Vector2	operator+(const Vector2& vector_1, const Vector2int& vector_2);
	Vector2	operator+(const Vector2int& vector_1, const Vector2& vector_2);
	Vector2	operator-(const Vector2& vector_1, const Vector2int& vector_2);
	Vector2	operator-(const Vector2int& vector_1, const Vector2& vector_2);

	/**
	 * @brief Multiply each vectors component (this is NOT a dot product).
	 *
	 * @param vector_1 the first vector
	 * @param vector_2 the second vector
	 * @return the result
	 */
	Vector2	operator*(const Vector2& vector_1, const Vector2int& vector_2);

	/**
	 * @brief Multiply each vectors component (this is NOT a dot product).
	 *
	 * @param vector_1 the first vector
	 * @param vector_2 the second vector
	 * @return the result
	 */
	Vector2	operator*(const Vector2int& vector_1, const Vector2& vector_2);

	// Operators

	Vector2	operator/(const Vector2& vector_1, const Vector2int& vector_2);
	Vector2	operator/(const Vector2int& vector_1, const Vector2& vector_2);

	Vector3	operator+(const Vector3& vector_1, const Vector3int& vector_2);
	Vector3	operator+(const Vector3int& vector_1, const Vector3& vector_2);
	Vector3	operator-(const Vector3& vector_1, const Vector3int& vector_2);
	Vector3	operator-(const Vector3int& vector_1, const Vector3& vector_2);

	/**
	 * @brief Multiply each vectors component (This is NEITHER a dot product NOR a cross product).
	 *
	 * @param vector_1 the first vector
	 * @param vector_2 the second vector
	 * @return the result
	 */
	Vector3	operator*(const Vector3& vector_1, const Vector3int& vector_2);

	/**
	 * @brief Multiply each vectors component (This is NEITHER a dot product NOR a cross product).
	 *
	 * @param vector_1 the first vector
	 * @param vector_2 the second vector
	 * @return the result
	 */
	Vector3	operator*(const Vector3int& vector_1, const Vector3& vector_2);

	// Operators

	Vector3	operator/(const Vector3& vector_1, const Vector3int& vector_2);
	Vector3	operator/(const Vector3int& vector_1, const Vector3& vector_2);

	Vector4	operator+(const Vector4& vector_1, const Vector4int& vector_2);
	Vector4	operator+(const Vector4int& vector_1, const Vector4& vector_2);
	Vector4	operator-(const Vector4& vector_1, const Vector4int& vector_2);
	Vector4	operator-(const Vector4int& vector_1, const Vector4& vector_2);

	/**
	 * @brief Multiply each vectors component (This is NEITHER a dot product NOR a cross product).
	 *
	 * @param vector_1 the first vector
	 * @param vector_2 the second vector
	 * @return the result
	 */
	Vector4	operator*(const Vector4& vector_1, const Vector4int& vector_2);

	/**
	 * @brief Multiply each vectors component (This is NEITHER a dot product NOR a cross product).
	 *
	 * @param vector_1 the first vector
	 * @param vector_2 the second vector
	 * @return the result
	 */
	Vector4	operator*(const Vector4int& vector_1, const Vector4& vector_2);

	// Operators

	Vector4	operator/(const Vector4& vector_1, const Vector4int& vector_2);
	Vector4	operator/(const Vector4int& vector_1, const Vector4& vector_2);
}

#endif
