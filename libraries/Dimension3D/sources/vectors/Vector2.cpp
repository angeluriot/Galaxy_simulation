#include "dim/dimension3D.hpp"

namespace dim
{
	const Vector2 Vector2::null = Vector2();
	const Vector2 Vector2::unit = Vector2(1.f, 0.f);

	Vector2::Vector2()
	{
		x = 0.f;
		y = 0.f;
	}

	Vector2::Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2::Vector2(const Vector3& other)
	{
		*this = other;
	}

	Vector2::Vector2(const Vector4& other)
	{
		*this = other;
	}

	Vector2::Vector2(const Vector2int& other)
	{
		*this = other;
	}

	Vector2::Vector2(const Vector3int& other)
	{
		*this = other;
	}

	Vector2::Vector2(const Vector4int& other)
	{
		*this = other;
	}

	Vector2::Vector2(const std::array<float, 2>& other)
	{
		*this = other;
	}

	Vector2::Vector2(const std::array<float, 3>& other)
	{
		*this = other;
	}

	Vector2::Vector2(const std::array<float, 4>& other)
	{
		*this = other;
	}

	Vector2::Vector2(const std::array<int, 2>& other)
	{
		*this = other;
	}

	Vector2::Vector2(const std::array<int, 3>& other)
	{
		*this = other;
	}

	Vector2::Vector2(const std::array<int, 4>& other)
	{
		*this = other;
	}

	Vector2::Vector2(const glm::vec2& other)
	{
		*this = other;
	}

	Vector2::Vector2(const glm::vec3& other)
	{
		*this = other;
	}

	Vector2::Vector2(const glm::vec4& other)
	{
		*this = other;
	}

	Vector2::Vector2(const sf::Vector2f& other)
	{
		*this = other;
	}

	Vector2::Vector2(const sf::Vector3f& other)
	{
		*this = other;
	}

	Vector2::Vector2(const sf::Vector2i& other)
	{
		*this = other;
	}

	Vector2::Vector2(const sf::Vector3i& other)
	{
		*this = other;
	}

	Vector2::Vector2(const ImVec2& other)
	{
		*this = other;
	}

	Vector2::Vector2(const ImVec4& other)
	{
		*this = other;
	}

	Vector2 Vector2::Cartesian(float x, float y)
	{
		return Vector2(x, y);
	}

	Vector2 Vector2::Polar(float norm, float angle)
	{
		return Vector2(cos(angle) * norm, sin(angle) * norm);
	}

	Vector2& Vector2::operator=(const Vector3& other)
	{
		x = other.x;
		y = other.y;

		return *this;
	}

	Vector2& Vector2::operator=(const Vector4& other)
	{
		x = other.x;
		y = other.y;

		return *this;
	}

	Vector2& Vector2::operator=(const Vector2int& other)
	{
		x = static_cast<float>(other.x);
		y = static_cast<float>(other.y);

		return *this;
	}

	Vector2& Vector2::operator=(const Vector3int& other)
	{
		x = static_cast<float>(other.x);
		y = static_cast<float>(other.y);

		return *this;
	}

	Vector2& Vector2::operator=(const Vector4int& other)
	{
		x = static_cast<float>(other.x);
		y = static_cast<float>(other.y);

		return *this;
	}

	Vector2& Vector2::operator=(const std::array<float, 2>& other)
	{
		x = other[0];
		y = other[1];

		return *this;
	}

	Vector2& Vector2::operator=(const std::array<float, 3>& other)
	{
		x = other[0];
		y = other[1];

		return *this;
	}

	Vector2& Vector2::operator=(const std::array<float, 4>& other)
	{
		x = other[0];
		y = other[1];

		return *this;
	}

	Vector2& Vector2::operator=(const std::array<int, 2>& other)
	{
		x = static_cast<float>(other[0]);
		y = static_cast<float>(other[1]);

		return *this;
	}

	Vector2& Vector2::operator=(const std::array<int, 3>& other)
	{
		x = static_cast<float>(other[0]);
		y = static_cast<float>(other[1]);

		return *this;
	}

	Vector2& Vector2::operator=(const std::array<int, 4>& other)
	{
		x = static_cast<float>(other[0]);
		y = static_cast<float>(other[1]);

		return *this;
	}

	Vector2& Vector2::operator=(const glm::vec2& other)
	{
		x = other.x;
		y = other.y;

		return *this;
	}

	Vector2& Vector2::operator=(const glm::vec3& other)
	{
		x = other.x;
		y = other.y;

		return *this;
	}

	Vector2& Vector2::operator=(const glm::vec4& other)
	{
		x = other.x;
		y = other.y;

		return *this;
	}

	Vector2& Vector2::operator=(const sf::Vector2f& other)
	{
		x = other.x;
		y = other.y;

		return *this;
	}

	Vector2& Vector2::operator=(const sf::Vector3f& other)
	{
		x = other.x;
		y = other.y;

		return *this;
	}

	Vector2& Vector2::operator=(const sf::Vector2i& other)
	{
		x = static_cast<float>(other.x);
		y = static_cast<float>(other.y);

		return *this;
	}

	Vector2& Vector2::operator=(const sf::Vector3i& other)
	{
		x = static_cast<float>(other.x);
		y = static_cast<float>(other.y);

		return *this;
	}

	Vector2& Vector2::operator=(const ImVec2& other)
	{
		x = other.x;
		y = other.y;

		return *this;
	}

	Vector2& Vector2::operator=(const ImVec4& other)
	{
		x = other.x;
		y = other.y;

		return *this;
	}

	Vector2& Vector2::operator+=(const Vector2& other)
	{
		*this = *this + other;
		return *this;
	}

	Vector2& Vector2::operator-=(const Vector2& other)
	{
		*this = *this - other;
		return *this;
	}

	Vector2& Vector2::operator*=(const Vector2& other)
	{
		*this = *this * other;
		return *this;
	}

	Vector2& Vector2::operator*=(float number)
	{
		*this = *this * number;
		return *this;
	}

	Vector2& Vector2::operator*=(int number)
	{
		*this = *this * number;
		return *this;
	}

	Vector2& Vector2::operator*=(const glm::mat2& matrix)
	{
		*this = *this * matrix;
		return *this;
	}

	Vector2& Vector2::operator*=(const glm::mat3& matrix)
	{
		*this = *this * matrix;
		return *this;
	}

	Vector2& Vector2::operator/=(const Vector2& other)
	{
		*this = *this / other;
		return *this;
	}

	Vector2& Vector2::operator/=(float number)
	{
		*this = *this / number;
		return *this;
	}

	Vector2& Vector2::operator/=(int number)
	{
		*this = *this / number;
		return *this;
	}

	Vector2 Vector2::operator+() const
	{
		return *this;
	}

	Vector2 Vector2::operator-() const
	{
		return null - *this;
	}

	float Vector2::get_norm() const
	{
		return sqrt(x * x + y * y);
	}

	float Vector2::get_norm_2() const
	{
		return x * x + y * y;
	}

	float Vector2::get_angle() const
	{
		if (get_norm() == 0.f)
			return 0.f;

		if (y >= 0.f)
			return acos(x / get_norm());

		else
			return 2.f * pi - acos(x / get_norm());
	}

	const float* Vector2::get_ptr() const
	{
		return &x;
	}

	void Vector2::set_norm(float norm)
	{
		*this = dim::normalize(*this) * norm;
	}

	void Vector2::set_angle(float angle)
	{
		*this = Polar(get_norm(), angle);
	}

	void Vector2::normalize()
	{
		*this = dim::normalize(*this);
	}

	void Vector2::clear()
	{
		*this = null;
	}

	std::array<float, 2> Vector2::to_array_float() const
	{
		return { x, y };
	}

	std::array<int, 2> Vector2::to_array_int() const
	{
		return { static_cast<int>(round(x)), static_cast<int>(round(y)) };
	}

	glm::vec2 Vector2::to_glm() const
	{
		return glm::vec2(x, y);
	}

	sf::Vector2f Vector2::to_sf_float() const
	{
		return sf::Vector2f(x, y);
	}

	sf::Vector2i Vector2::to_sf_int() const
	{
		return sf::Vector2i(static_cast<int>(round(x)), static_cast<int>(round(y)));
	}

	ImVec2 Vector2::to_imgui() const
	{
		return ImVec2(x, y);
	}

	Vector2 operator+(const Vector2& vector_1, const Vector2& vector_2)
	{
		return Vector2(vector_1.x + vector_2.x, vector_1.y + vector_2.y);
	}

	Vector2 operator-(const Vector2& vector_1, const Vector2& vector_2)
	{
		return Vector2(vector_1.x - vector_2.x, vector_1.y - vector_2.y);
	}

	Vector2 operator*(float number, const Vector2& vector)
	{
		return Vector2(number * vector.x, number * vector.y);
	}

	Vector2 operator*(const Vector2& vector, float number)
	{
		return number * vector;
	}

	Vector2 operator*(int number, const Vector2& vector)
	{
		return Vector2(static_cast<float>(number) * vector.x, static_cast<float>(number) * vector.y);
	}

	Vector2 operator*(const Vector2& vector, int number)
	{
		return number * vector;
	}

	Vector2 operator*(const Vector2& vector_1, const Vector2& vector_2)
	{
		return Vector2(vector_1.x * vector_2.x, vector_1.y * vector_2.y);
	}

	Vector2 operator*(const glm::mat2& matrix, const Vector2& vector)
	{
		return Vector2(matrix * vector.to_glm());
	}

	Vector2 operator*(const Vector2& vector, const glm::mat2& matrix)
	{
		return matrix * vector;
	}

	Vector2 operator*(const glm::mat3& matrix, const Vector2& vector)
	{
		return Vector2(matrix * Vector3(vector, 1.f));
	}

	Vector2 operator*(const Vector2& vector, const glm::mat3& matrix)
	{
		return matrix * vector;
	}

	Vector2 operator/(float number, const Vector2& vector)
	{
		return Vector2((vector.x != 0.f ? number / vector.x : 0.f), (vector.y != 0.f ? number / vector.y : 0.f));
	}

	Vector2 operator/(const Vector2& vector, float number)
	{
		if (number == 0.f)
			return Vector2::null;

		return Vector2(vector.x / number, vector.y / number);
	}

	Vector2 operator/(int number, const Vector2& vector)
	{
		return Vector2((vector.x != 0.f ? static_cast<float>(number) / vector.x : 0.f), (vector.y != 0.f ? static_cast<float>(number) / vector.y : 0.f));
	}

	Vector2 operator/(const Vector2& vector, int number)
	{
		if (number == 0)
			return Vector2::null;

		return Vector2(vector.x / static_cast<float>(number), vector.y / static_cast<float>(number));
	}

	Vector2 operator/(const Vector2& vector_1, const Vector2& vector_2)
	{
		return Vector2((vector_2.x != 0.f ? vector_1.x / vector_2.x : 0.f), (vector_2.y != 0.f ? vector_1.y / vector_2.y : 0.f));
	}

	float dot(const Vector2& vector_1, const Vector2& vector_2)
	{
		return vector_1.x * vector_2.x + vector_1.y * vector_2.y;
	}

	bool operator==(const Vector2& vector_1, const Vector2& vector_2)
	{
		return (vector_1.x == vector_2.x && vector_1.y == vector_2.y);
	}

	bool operator!=(const Vector2& vector_1, const Vector2& vector_2)
	{
		return (!(vector_1 == vector_2));
	}

	std::ostream& operator<<(std::ostream& os, const Vector2& vector)
	{
		os << "(" << vector.x << ", " << vector.y << ")";
		return os;
	}

	float distance(const Vector2& point_1, const Vector2& point_2)
	{
		return (point_2 - point_1).get_norm();
	}

	float distance_2(const Vector2& point_1, const Vector2& point_2)
	{
		return (point_2 - point_1).get_norm_2();
	}

	float angle(const Vector2& point_1, const Vector2& point_2)
	{
		return (point_2 - point_1).get_angle();
	}

	Vector2 normalize(const Vector2& vector)
	{
		float norm = vector.get_norm();

		if (norm != 0.f)
			return vector / norm;

		return Vector2::unit;
	}
}
