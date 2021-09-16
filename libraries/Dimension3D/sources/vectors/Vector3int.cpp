#include "dim/dimension3D.hpp"

namespace dim
{
	const Vector3int Vector3int::null = Vector3int();

	Vector3int::Vector3int()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Vector3int::Vector3int(int x, int y, int z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3int::Vector3int(const Vector2& other, int z)
	{
		x = static_cast<int>(round(other.x));
		y = static_cast<int>(round(other.y));
		this->z = z;
	}

	Vector3int::Vector3int(int x, const Vector2& other)
	{
		this->x = x;
		y = static_cast<int>(round(other.x));
		z = static_cast<int>(round(other.y));
	}

	Vector3int::Vector3int(const Vector3& other)
	{
		*this = other;
	}

	Vector3int::Vector3int(const Vector4& other)
	{
		*this = other;
	}

	Vector3int::Vector3int(const Vector2int& other, int z)
	{
		x = other.x;
		y = other.y;
		this->z = z;
	}

	Vector3int::Vector3int(int x, const Vector2int& other)
	{
		this->x = x;
		y = other.x;
		z = other.y;
	}

	Vector3int::Vector3int(const Vector4int& other)
	{
		*this = other;
	}

	Vector3int::Vector3int(const std::array<float, 3>& other)
	{
		*this = other;
	}

	Vector3int::Vector3int(const std::array<float, 4>& other)
	{
		*this = other;
	}

	Vector3int::Vector3int(const std::array<int, 3>& other)
	{
		*this = other;
	}

	Vector3int::Vector3int(const std::array<int, 4>& other)
	{
		*this = other;
	}

	Vector3int::Vector3int(const glm::vec3& other)
	{
		*this = other;
	}

	Vector3int::Vector3int(const glm::vec4& other)
	{
		*this = other;
	}

	Vector3int::Vector3int(const sf::Vector3f& other)
	{
		*this = other;
	}

	Vector3int::Vector3int(const sf::Vector3i& other)
	{
		*this = other;
	}

	Vector3int::Vector3int(const ImVec4& other)
	{
		*this = other;
	}

	Vector3int& Vector3int::operator=(const Vector3& other)
	{
		x = static_cast<int>(round(other.x));
		y = static_cast<int>(round(other.y));
		z = static_cast<int>(round(other.z));

		return *this;
	}

	Vector3int& Vector3int::operator=(const Vector4& other)
	{
		x = static_cast<int>(round(other.x));
		y = static_cast<int>(round(other.y));
		z = static_cast<int>(round(other.z));

		return *this;
	}

	Vector3int& Vector3int::operator=(const Vector4int& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;

		return *this;
	}

	Vector3int& Vector3int::operator=(const std::array<float, 3>& other)
	{
		x = static_cast<int>(round(other[0]));
		y = static_cast<int>(round(other[1]));
		z = static_cast<int>(round(other[2]));

		return *this;
	}

	Vector3int& Vector3int::operator=(const std::array<float, 4>& other)
	{
		x = static_cast<int>(round(other[0]));
		y = static_cast<int>(round(other[1]));
		z = static_cast<int>(round(other[2]));

		return *this;
	}

	Vector3int& Vector3int::operator=(const std::array<int, 3>& other)
	{
		x = other[0];
		y = other[1];
		z = other[2];

		return *this;
	}

	Vector3int& Vector3int::operator=(const std::array<int, 4>& other)
	{
		x = other[0];
		y = other[1];
		z = other[2];

		return *this;
	}

	Vector3int& Vector3int::operator=(const glm::vec3& other)
	{
		x = static_cast<int>(round(other.x));
		y = static_cast<int>(round(other.y));
		z = static_cast<int>(round(other.z));

		return *this;
	}

	Vector3int& Vector3int::operator=(const glm::vec4& other)
	{
		x = static_cast<int>(round(other.x));
		y = static_cast<int>(round(other.y));
		z = static_cast<int>(round(other.z));

		return *this;
	}

	Vector3int& Vector3int::operator=(const sf::Vector3f& other)
	{
		x = static_cast<int>(round(other.x));
		y = static_cast<int>(round(other.y));
		z = static_cast<int>(round(other.z));

		return *this;
	}

	Vector3int& Vector3int::operator=(const sf::Vector3i& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;

		return *this;
	}

	Vector3int& Vector3int::operator=(const ImVec4& other)
	{
		x = static_cast<int>(round(other.x));
		y = static_cast<int>(round(other.y));
		z = static_cast<int>(round(other.z));

		return *this;
	}

	Vector3int& Vector3int::operator+=(const Vector3int& other)
	{
		*this = *this + other;
		return *this;
	}

	Vector3int& Vector3int::operator-=(const Vector3int& other)
	{
		*this = *this - other;
		return *this;
	}

	Vector3int& Vector3int::operator*=(const Vector3int& other)
	{
		*this = *this * other;
		return *this;
	}

	Vector3int& Vector3int::operator*=(float number)
	{
		*this = *this * number;
		return *this;
	}

	Vector3int& Vector3int::operator*=(int number)
	{
		*this = *this * number;
		return *this;
	}

	Vector3int& Vector3int::operator/=(const Vector3int& other)
	{
		*this = *this / other;
		return *this;
	}

	Vector3int& Vector3int::operator/=(float number)
	{
		*this = *this / number;
		return *this;
	}

	Vector3int& Vector3int::operator/=(int number)
	{
		*this = *this / number;
		return *this;
	}

	Vector3int Vector3int::operator+() const
	{
		return *this;
	}

	Vector3int Vector3int::operator-() const
	{
		return null - *this;
	}

	float Vector3int::get_norm() const
	{
		return static_cast<float>(sqrt(x * x + y * y + z * z));
	}

	float Vector3int::get_norm_2() const
	{
		return static_cast<float>(x * x + y * y + z * z);
	}

	const int* Vector3int::get_ptr() const
	{
		return &x;
	}

	void Vector3int::clear()
	{
		*this = null;
	}

	std::array<float, 3> Vector3int::to_array_float() const
	{
		return { static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) };
	}

	std::array<int, 3> Vector3int::to_array_int() const
	{
		return { x, y, z };
	}

	glm::vec3 Vector3int::to_glm() const
	{
		return glm::vec3(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
	}

	sf::Vector3f Vector3int::to_sf_float() const
	{
		return sf::Vector3f(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
	}

	sf::Vector3i Vector3int::to_sf_int() const
	{
		return sf::Vector3i(x, y, z);
	}

	Vector3int operator+(const Vector3int& vector_1, const Vector3int& vector_2)
	{
		return Vector3int(vector_1.x + vector_2.x, vector_1.y + vector_2.y, vector_1.z + vector_2.z);
	}

	Vector3int operator-(const Vector3int& vector_1, const Vector3int& vector_2)
	{
		return Vector3int(vector_1.x - vector_2.x, vector_1.y - vector_2.y, vector_1.z - vector_2.z);
	}

	Vector3int operator*(float number, const Vector3int& vector)
	{
		return Vector3int(static_cast<int>(round(number * static_cast<float>(vector.x))), static_cast<int>(round(number * static_cast<float>(vector.y))),
			static_cast<int>(round(number * static_cast<float>(vector.z))));
	}

	Vector3int operator*(const Vector3int& vector, float number)
	{
		return number * vector;
	}

	Vector3int operator*(int number, const Vector3int& vector)
	{
		return Vector3int(number * vector.x, number * vector.y, number * vector.z);
	}

	Vector3int operator*(const Vector3int& vector, int number)
	{
		return number * vector;
	}

	Vector3int operator*(const Vector3int& vector_1, const Vector3int& vector_2)
	{
		return Vector3int(vector_1.x * vector_2.x, vector_1.y * vector_2.y, vector_1.z * vector_2.z);
	}

	Vector3int operator/(float number, const Vector3int& vector)
	{
		return Vector3int((vector.x != 0 ? static_cast<int>(round(number / static_cast<float>(vector.x))) : 0),
			(vector.y != 0 ? static_cast<int>(round(number / static_cast<float>(vector.y))) : 0),
			(vector.z != 0 ? static_cast<int>(round(number / static_cast<float>(vector.z))) : 0));
	}

	Vector3int operator/(const Vector3int& vector, float number)
	{
		if (number == 0.f)
			return Vector3int::null;

		return Vector3int(static_cast<int>(round(static_cast<float>(vector.x) / number)), static_cast<int>(round(static_cast<float>(vector.y) / number)),
			static_cast<int>(round(static_cast<float>(vector.z) / number)));
	}

	Vector3int operator/(int number, const Vector3int& vector)
	{
		return Vector3int((vector.x != 0 ? number / vector.x : 0), (vector.y != 0 ? number / vector.y : 0), (vector.z != 0 ? number / vector.z : 0));
	}

	Vector3int operator/(const Vector3int& vector, int number)
	{
		if (number == 0)
			return Vector3int::null;

		return Vector3int(vector.x / number, vector.y / number, vector.z / number);
	}

	Vector3int operator/(const Vector3int& vector_1, const Vector3int& vector_2)
	{
		return Vector3int((vector_2.x != 0 ? vector_1.x / vector_2.x : 0), (vector_2.y != 0 ? vector_1.y / vector_2.y : 0),
			(vector_2.z != 0 ? vector_1.z / vector_2.z : 0));
	}

	bool operator==(const Vector3int& vector_1, const Vector3int& vector_2)
	{
		return (vector_1.x == vector_2.x && vector_1.y == vector_2.y && vector_1.z == vector_2.z);
	}

	bool operator!=(const Vector3int& vector_1, const Vector3int& vector_2)
	{
		return (!(vector_1 == vector_2));
	}

	std::ostream& operator<<(std::ostream& os, const Vector3int& vector)
	{
		os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
		return os;
	}

	float distance(const Vector3int& point_1, const Vector3int& point_2)
	{
		return (point_2 - point_1).get_norm();
	}

	float distance_2(const Vector3int& point_1, const Vector3int& point_2)
	{
		return (point_2 - point_1).get_norm_2();
	}
}
