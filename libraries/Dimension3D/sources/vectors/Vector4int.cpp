#include "dim/dimension3D.hpp"

namespace dim
{
	const Vector4int Vector4int::null = Vector4int();

	Vector4int::Vector4int()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}

	Vector4int::Vector4int(int x, int y, int z, int w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Vector4int::Vector4int(const Vector2& other, int z, int w)
	{
		x = static_cast<int>(round(other.x));
		y = static_cast<int>(round(other.y));
		this->z = z;
		this->w = w;
	}

	Vector4int::Vector4int(int x, const Vector2& other, int w)
	{
		this->x = x;
		y = static_cast<int>(round(other.x));
		z = static_cast<int>(round(other.y));
		this->w = w;
	}

	Vector4int::Vector4int(int x, int y, const Vector2& other)
	{
		this->x = x;
		this->y = y;
		z = static_cast<int>(round(other.x));
		w = static_cast<int>(round(other.y));
	}

	Vector4int::Vector4int(const Vector3& other, int w)
	{
		x = static_cast<int>(round(other.x));
		y = static_cast<int>(round(other.y));
		z = static_cast<int>(round(other.z));
		this->w = w;
	}

	Vector4int::Vector4int(int x, const Vector3& other)
	{
		this->x = x;
		y = static_cast<int>(round(other.x));
		z = static_cast<int>(round(other.y));
		w = static_cast<int>(round(other.z));
	}

	Vector4int::Vector4int(const Vector4& other)
	{
		*this = other;
	}

	Vector4int::Vector4int(const Vector2int& other, int z, int w)
	{
		x = other.x;
		y = other.y;
		this->z = z;
		this->w = w;
	}

	Vector4int::Vector4int(int x, const Vector2int& other, int w)
	{
		this->x = x;
		y = other.x;
		z = other.y;
		this->w = w;
	}

	Vector4int::Vector4int(int x, int y, const Vector2int& other)
	{
		this->x = x;
		this->y = y;
		z = other.x;
		w = other.y;
	}

	Vector4int::Vector4int(const Vector3int& other, int w)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		this->w = w;
	}

	Vector4int::Vector4int(int x, const Vector3int& other)
	{
		this->x = x;
		y = other.x;
		z = other.y;
		w = other.z;
	}

	Vector4int::Vector4int(const std::array<float, 4>& other)
	{
		*this = other;
	}

	Vector4int::Vector4int(const std::array<int, 4>& other)
	{
		*this = other;
	}

	Vector4int::Vector4int(const glm::vec4& other)
	{
		*this = other;
	}

	Vector4int::Vector4int(const ImVec4& other)
	{
		*this = other;
	}

	Vector4int& Vector4int::operator=(const Vector4& other)
	{
		x = static_cast<int>(round(other.x));
		y = static_cast<int>(round(other.y));
		z = static_cast<int>(round(other.z));
		w = static_cast<int>(round(other.w));

		return *this;
	}

	Vector4int& Vector4int::operator=(const std::array<float, 4>& other)
	{
		x = static_cast<int>(round(other[0]));
		y = static_cast<int>(round(other[1]));
		z = static_cast<int>(round(other[2]));
		w = static_cast<int>(round(other[3]));

		return *this;
	}

	Vector4int& Vector4int::operator=(const std::array<int, 4>& other)
	{
		x = other[0];
		y = other[1];
		z = other[2];
		z = other[3];

		return *this;
	}

	Vector4int& Vector4int::operator=(const glm::vec4& other)
	{
		x = static_cast<int>(round(other.x));
		y = static_cast<int>(round(other.y));
		z = static_cast<int>(round(other.z));
		w = static_cast<int>(round(other.w));

		return *this;
	}

	Vector4int& Vector4int::operator=(const ImVec4& other)
	{
		x = static_cast<int>(round(other.x));
		y = static_cast<int>(round(other.y));
		z = static_cast<int>(round(other.z));
		w = static_cast<int>(round(other.w));

		return *this;
	}

	Vector4int& Vector4int::operator+=(const Vector4int& other)
	{
		*this = *this + other;
		return *this;
	}

	Vector4int& Vector4int::operator-=(const Vector4int& other)
	{
		*this = *this - other;
		return *this;
	}

	Vector4int& Vector4int::operator*=(const Vector4int& other)
	{
		*this = *this * other;
		return *this;
	}

	Vector4int& Vector4int::operator*=(float number)
	{
		*this = *this * number;
		return *this;
	}

	Vector4int& Vector4int::operator*=(int number)
	{
		*this = *this * number;
		return *this;
	}

	Vector4int& Vector4int::operator/=(const Vector4int& other)
	{
		*this = *this / other;
		return *this;
	}

	Vector4int& Vector4int::operator/=(float number)
	{
		*this = *this / number;
		return *this;
	}

	Vector4int& Vector4int::operator/=(int number)
	{
		*this = *this / number;
		return *this;
	}

	Vector4int Vector4int::operator+() const
	{
		return *this;
	}

	Vector4int Vector4int::operator-() const
	{
		return null - *this;
	}

	float Vector4int::get_norm() const
	{
		return static_cast<float>(sqrt(x * x + y * y + z * z + w * w));
	}

	float Vector4int::get_norm_2() const
	{
		return static_cast<float>(x * x + y * y + z * z + w * w);
	}

	const int* Vector4int::get_ptr() const
	{
		return &x;
	}

	void Vector4int::clear()
	{
		*this = null;
	}

	std::array<float, 4> Vector4int::to_array_float() const
	{
		return { static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) , static_cast<float>(w) };
	}

	std::array<int, 4> Vector4int::to_array_int() const
	{
		return { x, y, z, w };
	}

	glm::vec4 Vector4int::to_glm() const
	{
		return glm::vec4(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z), static_cast<float>(w));
	}

	ImVec4 Vector4int::to_imgui() const
	{
		return ImVec4(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z), static_cast<float>(w));
	}

	Vector4int operator+(const Vector4int& vector_1, const Vector4int& vector_2)
	{
		return Vector4int(vector_1.x + vector_2.x, vector_1.y + vector_2.y, vector_1.z + vector_2.z, vector_1.w + vector_2.w);
	}

	Vector4int operator-(const Vector4int& vector_1, const Vector4int& vector_2)
	{
		return Vector4int(vector_1.x - vector_2.x, vector_1.y - vector_2.y, vector_1.z - vector_2.z, vector_1.w - vector_2.w);
	}

	Vector4int operator*(float number, const Vector4int& vector)
	{
		return Vector4int(static_cast<int>(round(number * static_cast<float>(vector.x))), static_cast<int>(round(number * static_cast<float>(vector.y))),
			static_cast<int>(round(number * static_cast<float>(vector.z))), static_cast<int>(round(number * static_cast<float>(vector.w))));
	}

	Vector4int operator*(const Vector4int& vector, float number)
	{
		return number * vector;
	}

	Vector4int operator*(int number, const Vector4int& vector)
	{
		return Vector4int(number * vector.x, number * vector.y, number * vector.z, number * vector.w);
	}

	Vector4int operator*(const Vector4int& vector, int number)
	{
		return number * vector;
	}

	Vector4int operator*(const Vector4int& vector_1, const Vector4int& vector_2)
	{
		return Vector4int(vector_1.x * vector_2.x, vector_1.y * vector_2.y, vector_1.z * vector_2.z, vector_1.w * vector_2.w);
	}

	Vector4int operator/(float number, const Vector4int& vector)
	{
		return Vector4int((vector.x != 0 ? static_cast<int>(round(number / static_cast<float>(vector.x))) : 0),
			(vector.y != 0 ? static_cast<int>(round(number / static_cast<float>(vector.y))) : 0),
			(vector.z != 0 ? static_cast<int>(round(number / static_cast<float>(vector.z))) : 0),
			(vector.w != 0 ? static_cast<int>(round(number / static_cast<float>(vector.w))) : 0));
	}

	Vector4int operator/(const Vector4int& vector, float number)
	{
		if (number == 0.f)
			return Vector4int::null;

		return Vector4int(static_cast<int>(round(static_cast<float>(vector.x) / number)), static_cast<int>(round(static_cast<float>(vector.y) / number)),
			static_cast<int>(round(static_cast<float>(vector.z) / number)), static_cast<int>(round(static_cast<float>(vector.w) / number)));
	}

	Vector4int operator/(int number, const Vector4int& vector)
	{
		return Vector4int((vector.x != 0 ? number / vector.x : 0), (vector.y != 0 ? number / vector.y : 0), (vector.z != 0 ? number / vector.z : 0),
			(vector.w != 0 ? number / vector.w : 0));
	}

	Vector4int operator/(const Vector4int& vector, int number)
	{
		if (number == 0)
			return Vector4int::null;

		return Vector4int(vector.x / number, vector.y / number, vector.z / number, vector.w / number);
	}

	Vector4int operator/(const Vector4int& vector_1, const Vector4int& vector_2)
	{
		return Vector4int((vector_2.x != 0 ? vector_1.x / vector_2.x : 0), (vector_2.y != 0 ? vector_1.y / vector_2.y : 0),
			(vector_2.z != 0 ? vector_1.z / vector_2.z : 0), (vector_2.w != 0 ? vector_1.w / vector_2.w : 0));
	}

	bool operator==(const Vector4int& vector_1, const Vector4int& vector_2)
	{
		return (vector_1.x == vector_2.x && vector_1.y == vector_2.y && vector_1.z == vector_2.z && vector_1.w == vector_2.w);
	}

	bool operator!=(const Vector4int& vector_1, const Vector4int& vector_2)
	{
		return (!(vector_1 == vector_2));
	}

	std::ostream& operator<<(std::ostream& os, const Vector4int& vector)
	{
		os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
		return os;
	}

	float distance(const Vector4int& point_1, const Vector4int& point_2)
	{
		return (point_2 - point_1).get_norm();
	}

	float distance_2(const Vector4int& point_1, const Vector4int& point_2)
	{
		return (point_2 - point_1).get_norm_2();
	}
}
