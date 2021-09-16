#include "dim/dimension3D.hpp"

namespace dim
{
	const Vector2int Vector2int::null = Vector2int();

	Vector2int::Vector2int()
	{
		x = 0;
		y = 0;
	}

	Vector2int::Vector2int(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2int::Vector2int(const Vector2& other)
	{
		*this = other;
	}

	Vector2int::Vector2int(const Vector3& other)
	{
		*this = other;
	}

	Vector2int::Vector2int(const Vector4& other)
	{
		*this = other;
	}

	Vector2int::Vector2int(const Vector3int& other)
	{
		*this = other;
	}

	Vector2int::Vector2int(const Vector4int& other)
	{
		*this = other;
	}

	Vector2int::Vector2int(const std::array<float, 2>& other)
	{
		*this = other;
	}

	Vector2int::Vector2int(const std::array<float, 3>& other)
	{
		*this = other;
	}

	Vector2int::Vector2int(const std::array<float, 4>& other)
	{
		*this = other;
	}

	Vector2int::Vector2int(const std::array<int, 2>& other)
	{
		*this = other;
	}

	Vector2int::Vector2int(const std::array<int, 3>& other)
	{
		*this = other;
	}

	Vector2int::Vector2int(const std::array<int, 4>& other)
	{
		*this = other;
	}

	Vector2int::Vector2int(const glm::vec2& other)
	{
		*this = other;
	}

	Vector2int::Vector2int(const glm::vec3& other)
	{
		*this = other;
	}

	Vector2int::Vector2int(const glm::vec4& other)
	{
		*this = other;
	}

	Vector2int::Vector2int(const sf::Vector2f& other)
	{
		*this = other;
	}

	Vector2int::Vector2int(const sf::Vector3f& other)
	{
		*this = other;
	}

	Vector2int::Vector2int(const sf::Vector2i& other)
	{
		*this = other;
	}

	Vector2int::Vector2int(const sf::Vector3i& other)
	{
		*this = other;
	}

	Vector2int::Vector2int(const ImVec2& other)
	{
		*this = other;
	}

	Vector2int::Vector2int(const ImVec4& other)
	{
		*this = other;
	}

	Vector2int& Vector2int::operator=(const Vector2& other)
	{
		x = static_cast<int>(round(other.x));
		y = static_cast<int>(round(other.y));

		return *this;
	}

	Vector2int& Vector2int::operator=(const Vector3& other)
	{
		x = static_cast<int>(round(other.x));
		y = static_cast<int>(round(other.y));

		return *this;
	}

	Vector2int& Vector2int::operator=(const Vector4& other)
	{
		x = static_cast<int>(round(other.x));
		y = static_cast<int>(round(other.y));

		return *this;
	}

	Vector2int& Vector2int::operator=(const Vector3int& other)
	{
		x = other.x;
		y = other.y;

		return *this;
	}

	Vector2int& Vector2int::operator=(const Vector4int& other)
	{
		x = other.x;
		y = other.y;

		return *this;
	}

	Vector2int& Vector2int::operator=(const std::array<float, 2>& other)
	{
		x = static_cast<int>(round(other[0]));
		y = static_cast<int>(round(other[1]));

		return *this;
	}

	Vector2int& Vector2int::operator=(const std::array<float, 3>& other)
	{
		x = static_cast<int>(round(other[0]));
		y = static_cast<int>(round(other[1]));

		return *this;
	}

	Vector2int& Vector2int::operator=(const std::array<float, 4>& other)
	{
		x = static_cast<int>(round(other[0]));
		y = static_cast<int>(round(other[1]));

		return *this;
	}

	Vector2int& Vector2int::operator=(const std::array<int, 2>& other)
	{
		x = other[0];
		y = other[1];

		return *this;
	}

	Vector2int& Vector2int::operator=(const std::array<int, 3>& other)
	{
		x = other[0];
		y = other[1];

		return *this;
	}

	Vector2int& Vector2int::operator=(const std::array<int, 4>& other)
	{
		x = other[0];
		y = other[1];

		return *this;
	}

	Vector2int& Vector2int::operator=(const glm::vec2& other)
	{
		x = static_cast<int>(round(other.x));
		y = static_cast<int>(round(other.y));

		return *this;
	}

	Vector2int& Vector2int::operator=(const glm::vec3& other)
	{
		x = static_cast<int>(round(other.x));
		y = static_cast<int>(round(other.y));

		return *this;
	}

	Vector2int& Vector2int::operator=(const glm::vec4& other)
	{
		x = static_cast<int>(round(other.x));
		y = static_cast<int>(round(other.y));

		return *this;
	}

	Vector2int& Vector2int::operator=(const sf::Vector2f& other)
	{
		x = static_cast<int>(round(other.x));
		y = static_cast<int>(round(other.y));

		return *this;
	}

	Vector2int& Vector2int::operator=(const sf::Vector3f& other)
	{
		x = static_cast<int>(round(other.x));
		y = static_cast<int>(round(other.y));

		return *this;
	}

	Vector2int& Vector2int::operator=(const sf::Vector2i& other)
	{
		x = other.x;
		y = other.y;

		return *this;
	}

	Vector2int& Vector2int::operator=(const sf::Vector3i& other)
	{
		x = other.x;
		y = other.y;

		return *this;
	}

	Vector2int& Vector2int::operator=(const ImVec2& other)
	{
		x = static_cast<int>(round(other.x));
		y = static_cast<int>(round(other.y));

		return *this;
	}

	Vector2int& Vector2int::operator=(const ImVec4& other)
	{
		x = static_cast<int>(round(other.x));
		y = static_cast<int>(round(other.y));

		return *this;
	}

	Vector2int& Vector2int::operator+=(const Vector2int& other)
	{
		*this = *this + other;
		return *this;
	}

	Vector2int& Vector2int::operator-=(const Vector2int& other)
	{
		*this = *this - other;
		return *this;
	}

	Vector2int& Vector2int::operator*=(const Vector2int& other)
	{
		*this = *this * other;
		return *this;
	}

	Vector2int& Vector2int::operator*=(float number)
	{
		*this = *this * number;
		return *this;
	}

	Vector2int& Vector2int::operator*=(int number)
	{
		*this = *this * number;
		return *this;
	}

	Vector2int& Vector2int::operator/=(const Vector2int& other)
	{
		*this = *this / other;
		return *this;
	}

	Vector2int& Vector2int::operator/=(float number)
	{
		*this = *this / number;
		return *this;
	}

	Vector2int& Vector2int::operator/=(int number)
	{
		*this = *this / number;
		return *this;
	}

	Vector2int Vector2int::operator+() const
	{
		return *this;
	}

	Vector2int Vector2int::operator-() const
	{
		return null - *this;
	}

	float Vector2int::get_norm() const
	{
		return static_cast<float>(sqrt(x * x + y * y));
	}

	float Vector2int::get_norm_2() const
	{
		return static_cast<float>(x * x + y * y);
	}

	const int* Vector2int::get_ptr() const
	{
		return &x;
	}

	void Vector2int::clear()
	{
		*this = null;
	}

	std::array<float, 2> Vector2int::to_array_float() const
	{
		return { static_cast<float>(x), static_cast<float>(y) };
	}

	std::array<int, 2> Vector2int::to_array_int() const
	{
		return { x, y };
	}

	glm::vec2 Vector2int::to_glm() const
	{
		return glm::vec2(static_cast<float>(x), static_cast<float>(y));
	}

	sf::Vector2f Vector2int::to_sf_float() const
	{
		return sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
	}

	sf::Vector2i Vector2int::to_sf_int() const
	{
		return sf::Vector2i(x, y);
	}

	ImVec2 Vector2int::to_imgui() const
	{
		return ImVec2(static_cast<float>(x), static_cast<float>(y));
	}

	Vector2int operator+(const Vector2int& vector_1, const Vector2int& vector_2)
	{
		return Vector2int(vector_1.x + vector_2.x, vector_1.y + vector_2.y);
	}

	Vector2int operator-(const Vector2int& vector_1, const Vector2int& vector_2)
	{
		return Vector2int(vector_1.x - vector_2.x, vector_1.y - vector_2.y);
	}

	Vector2int operator*(float number, const Vector2int& vector)
	{
		return Vector2int(static_cast<int>(round(number * static_cast<float>(vector.x))), static_cast<int>(round(number * static_cast<float>(vector.y))));
	}

	Vector2int operator*(const Vector2int& vector, float number)
	{
		return number * vector;
	}

	Vector2int operator*(int number, const Vector2int& vector)
	{
		return Vector2int(number * vector.x, number * vector.y);
	}

	Vector2int operator*(const Vector2int& vector, int number)
	{
		return number * vector;
	}

	Vector2int operator*(const Vector2int& vector_1, const Vector2int& vector_2)
	{
		return Vector2int(vector_1.x * vector_2.x, vector_1.y * vector_2.y);
	}

	Vector2int operator/(float number, const Vector2int& vector)
	{
		return Vector2int((vector.x != 0 ? static_cast<int>(round(number / static_cast<float>(vector.x))) : 0),
			(vector.y != 0 ? static_cast<int>(round(number / static_cast<float>(vector.y))) : 0));
	}

	Vector2int operator/(const Vector2int& vector, float number)
	{
		if (number == 0.f)
			return Vector2int::null;

		return Vector2int(static_cast<int>(round(static_cast<float>(vector.x) / number)), static_cast<int>(round(static_cast<float>(vector.y) / number)));
	}

	Vector2int operator/(int number, const Vector2int& vector)
	{
		return Vector2int((vector.x != 0 ? number / vector.x : 0), (vector.y != 0 ? number / vector.y : 0));
	}

	Vector2int operator/(const Vector2int& vector, int number)
	{
		if (number == 0)
			return Vector2int::null;

		return Vector2int(vector.x / number, vector.y / number);
	}

	Vector2int operator/(const Vector2int& vector_1, const Vector2int& vector_2)
	{
		return Vector2int((vector_2.x != 0 ? vector_1.x / vector_2.x : 0), (vector_2.y != 0 ? vector_1.y / vector_2.y : 0));
	}

	bool operator==(const Vector2int& vector_1, const Vector2int& vector_2)
	{
		return (vector_1.x == vector_2.x && vector_1.y == vector_2.y);
	}

	bool operator!=(const Vector2int& vector_1, const Vector2int& vector_2)
	{
		return (!(vector_1 == vector_2));
	}

	std::ostream& operator<<(std::ostream& os, const Vector2int& vector)
	{
		os << "(" << vector.x << ", " << vector.y << ")";
		return os;
	}

	float distance(const Vector2int& point_1, const Vector2int& point_2)
	{
		return (point_2 - point_1).get_norm();
	}

	float distance_2(const Vector2int& point_1, const Vector2int& point_2)
	{
		return (point_2 - point_1).get_norm_2();
	}
}
