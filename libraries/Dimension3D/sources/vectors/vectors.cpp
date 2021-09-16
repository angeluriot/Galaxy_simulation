#include "dim/dimension3D.hpp"

namespace dim
{
	Vector2 operator+(const Vector2& vector_1, const Vector2int& vector_2)
	{
		return vector_1 + Vector2(vector_2);
	}

	Vector2 operator+(const Vector2int& vector_1, const Vector2& vector_2)
	{
		return Vector2(vector_1) + vector_2;
	}

	Vector2 operator-(const Vector2& vector_1, const Vector2int& vector_2)
	{
		return vector_1 - Vector2(vector_2);
	}

	Vector2 operator-(const Vector2int& vector_1, const Vector2& vector_2)
	{
		return Vector2(vector_1) - vector_2;
	}

	Vector2 operator*(const Vector2& vector_1, const Vector2int& vector_2)
	{
		return vector_1 * Vector2(vector_2);
	}

	Vector2 operator*(const Vector2int& vector_1, const Vector2& vector_2)
	{
		return Vector2(vector_1) * vector_2;
	}

	Vector2 operator/(const Vector2& vector_1, const Vector2int& vector_2)
	{
		return vector_1 / Vector2(vector_2);
	}

	Vector2 operator/(const Vector2int& vector_1, const Vector2& vector_2)
	{
		return Vector2(vector_1) / vector_2;
	}

	Vector3 operator+(const Vector3& vector_1, const Vector3int& vector_2)
	{
		return vector_1 + Vector3(vector_2);
	}

	Vector3 operator+(const Vector3int& vector_1, const Vector3& vector_2)
	{
		return Vector3(vector_1) + vector_2;
	}

	Vector3 operator-(const Vector3& vector_1, const Vector3int& vector_2)
	{
		return vector_1 - Vector3(vector_2);
	}

	Vector3 operator-(const Vector3int& vector_1, const Vector3& vector_2)
	{
		return Vector3(vector_1) - vector_2;
	}

	Vector3 operator*(const Vector3& vector_1, const Vector3int& vector_2)
	{
		return vector_1 * Vector3(vector_2);
	}

	Vector3 operator*(const Vector3int& vector_1, const Vector3& vector_2)
	{
		return Vector3(vector_1) * vector_2;
	}

	Vector3 operator/(const Vector3& vector_1, const Vector3int& vector_2)
	{
		return vector_1 / Vector3(vector_2);
	}

	Vector3 operator/(const Vector3int& vector_1, const Vector3& vector_2)
	{
		return Vector3(vector_1) / vector_2;
	}

	Vector4 operator+(const Vector4& vector_1, const Vector4int& vector_2)
	{
		return vector_1 + Vector4(vector_2);
	}

	Vector4 operator+(const Vector4int& vector_1, const Vector4& vector_2)
	{
		return Vector4(vector_1) + vector_2;
	}

	Vector4 operator-(const Vector4& vector_1, const Vector4int& vector_2)
	{
		return vector_1 - Vector4(vector_2);
	}

	Vector4 operator-(const Vector4int& vector_1, const Vector4& vector_2)
	{
		return Vector4(vector_1) - vector_2;
	}

	Vector4 operator*(const Vector4& vector_1, const Vector4int& vector_2)
	{
		return vector_1 * Vector4(vector_2);
	}

	Vector4 operator*(const Vector4int& vector_1, const Vector4& vector_2)
	{
		return Vector4(vector_1) * vector_2;
	}

	Vector4 operator/(const Vector4& vector_1, const Vector4int& vector_2)
	{
		return vector_1 / Vector4(vector_2);
	}

	Vector4 operator/(const Vector4int& vector_1, const Vector4& vector_2)
	{
		return Vector4(vector_1) / vector_2;
	}
}
