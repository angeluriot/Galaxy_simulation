#include "dim/dimension3D.hpp"

namespace dim
{
	const Vector3 Vector3::null = Vector3();
	const Vector3 Vector3::unit = Vector3(1.f, 0.f, 0.f);

	Vector3::Vector3()
	{
		x = 0.f;
		y = 0.f;
		z = 0.f;
	}

	Vector3::Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3::Vector3(const Vector2& other, float z)
	{
		x = other.x;
		y = other.y;
		this->z = z;
	}

	Vector3::Vector3(float x, const Vector2& other)
	{
		this->x = x;
		y = other.x;
		z = other.y;
	}

	Vector3::Vector3(const Vector4& other)
	{
		*this = other;
	}

	Vector3::Vector3(const Vector2int& other, float z)
	{
		x = static_cast<float>(other.x);
		y = static_cast<float>(other.y);
		this->z = z;
	}

	Vector3::Vector3(float x, const Vector2int& other)
	{
		this->x = x;
		y = static_cast<float>(other.x);
		z = static_cast<float>(other.y);
	}

	Vector3::Vector3(const Vector3int& other)
	{
		*this = other;
	}

	Vector3::Vector3(const Vector4int& other)
	{
		*this = other;
	}

	Vector3::Vector3(const std::array<float, 3>& other)
	{
		*this = other;
	}

	Vector3::Vector3(const std::array<float, 4>& other)
	{
		*this = other;
	}

	Vector3::Vector3(const std::array<int, 3>& other)
	{
		*this = other;
	}

	Vector3::Vector3(const std::array<int, 4>& other)
	{
		*this = other;
	}

	Vector3::Vector3(const glm::vec3& other)
	{
		*this = other;
	}

	Vector3::Vector3(const glm::vec4& other)
	{
		*this = other;
	}

	Vector3::Vector3(const sf::Vector3f& other)
	{
		*this = other;
	}

	Vector3::Vector3(const sf::Vector3i& other)
	{
		*this = other;
	}

	Vector3::Vector3(const ImVec4& other)
	{
		*this = other;
	}

	Vector3::Vector3(const sf::Color& color)
	{
		*this = color;
	}

	Vector3 Vector3::Cartesian(float x, float y, float z)
	{
		return Vector3(x, y, z);
	}

	Vector3 Vector3::Spherical(float norm, float theta, float phi)
	{
		return Vector3(norm * sin(theta) * sin(phi), norm * cos(phi), norm * cos(theta) * sin(phi));
	}

	Vector3& Vector3::operator=(const Vector4& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;

		return *this;
	}

	Vector3& Vector3::operator=(const Vector3int& other)
	{
		x = static_cast<float>(other.x);
		y = static_cast<float>(other.y);
		z = static_cast<float>(other.z);

		return *this;
	}

	Vector3& Vector3::operator=(const Vector4int& other)
	{
		x = static_cast<float>(other.x);
		y = static_cast<float>(other.y);
		z = static_cast<float>(other.z);

		return *this;
	}

	Vector3& Vector3::operator=(const std::array<float, 3>& other)
	{
		x = other[0];
		y = other[1];
		z = other[2];

		return *this;
	}

	Vector3& Vector3::operator=(const std::array<float, 4>& other)
	{
		x = other[0];
		y = other[1];
		z = other[2];

		return *this;
	}

	Vector3& Vector3::operator=(const std::array<int, 3>& other)
	{
		x = static_cast<float>(other[0]);
		y = static_cast<float>(other[1]);
		z = static_cast<float>(other[2]);

		return *this;
	}

	Vector3& Vector3::operator=(const std::array<int, 4>& other)
	{
		x = static_cast<float>(other[0]);
		y = static_cast<float>(other[1]);
		z = static_cast<float>(other[2]);

		return *this;
	}

	Vector3& Vector3::operator=(const glm::vec3& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;

		return *this;
	}

	Vector3& Vector3::operator=(const glm::vec4& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;

		return *this;
	}

	Vector3& Vector3::operator=(const sf::Vector3f& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;

		return *this;
	}

	Vector3& Vector3::operator=(const sf::Vector3i& other)
	{
		x = static_cast<float>(other.x);
		y = static_cast<float>(other.y);
		z = static_cast<float>(other.z);

		return *this;
	}

	Vector3& Vector3::operator=(const ImVec4& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;

		return *this;
	}

	Vector3& Vector3::operator=(const sf::Color& color)
	{
		x = color.r;
		y = color.g;
		z = color.b;

		return *this;
	}

	Vector3& Vector3::operator+=(const Vector3& other)
	{
		*this = *this + other;
		return *this;
	}

	Vector3& Vector3::operator-=(const Vector3& other)
	{
		*this = *this - other;
		return *this;
	}

	Vector3& Vector3::operator*=(const Vector3& other)
	{
		*this = *this * other;
		return *this;
	}

	Vector3& Vector3::operator*=(float number)
	{
		*this = *this * number;
		return *this;
	}

	Vector3& Vector3::operator*=(int number)
	{
		*this = *this * number;
		return *this;
	}

	Vector3& Vector3::operator*=(const glm::mat3& matrix)
	{
		*this = *this * matrix;
		return *this;
	}

	Vector3& Vector3::operator*=(const glm::mat4& matrix)
	{
		*this = *this * matrix;
		return *this;
	}

	Vector3& Vector3::operator/=(const Vector3& other)
	{
		*this = *this / other;
		return *this;
	}

	Vector3& Vector3::operator/=(float number)
	{
		*this = *this / number;
		return *this;
	}

	Vector3& Vector3::operator/=(int number)
	{
		*this = *this / number;
		return *this;
	}

	Vector3& Vector3::operator^=(const Vector3& other)
	{
		*this = *this ^ other;
		return *this;
	}

	Vector3 Vector3::operator+() const
	{
		return *this;
	}

	Vector3 Vector3::operator-() const
	{
		return null - *this;
	}

	float Vector3::get_norm() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	float Vector3::get_norm_2() const
	{
		return x * x + y * y + z * z;
	}

	float Vector3::get_theta() const
	{
		return Vector2(z, x).get_angle();
	}

	float Vector3::get_phi() const
	{
		if (get_norm() == 0.f)
			return 0.f;

		return acos(y / get_norm());
	}

	const float* Vector3::get_ptr() const
	{
		return &x;
	}

	void Vector3::set_norm(float norm)
	{
		*this = dim::normalize(*this) * norm;
	}

	void Vector3::set_theta(float theta)
	{
		*this = Spherical(get_norm(), theta, get_phi());
	}

	void Vector3::set_phi(float phi)
	{
		*this = Spherical(get_norm(), get_theta(), phi);
	}

	void Vector3::normalize()
	{
		*this = dim::normalize(*this);
	}

	void Vector3::clear()
	{
		*this = null;
	}

	std::array<float, 3> Vector3::to_array_float() const
	{
		return { x, y, z };
	}

	std::array<int, 3> Vector3::to_array_int() const
	{
		return { static_cast<int>(round(x)), static_cast<int>(round(y)), static_cast<int>(round(z)) };
	}

	glm::vec3 Vector3::to_glm() const
	{
		return glm::vec3(x, y, z);
	}

	sf::Vector3f Vector3::to_sf_float() const
	{
		return sf::Vector3f(x, y, z);
	}

	sf::Vector3i Vector3::to_sf_int() const
	{
		return sf::Vector3i(static_cast<int>(round(x)), static_cast<int>(round(y)), static_cast<int>(round(z)));
	}

	Vector3 operator+(const Vector3& vector_1, const Vector3& vector_2)
	{
		return Vector3(vector_1.x + vector_2.x, vector_1.y + vector_2.y, vector_1.z + vector_2.z);
	}

	Vector3 operator-(const Vector3& vector_1, const Vector3& vector_2)
	{
		return Vector3(vector_1.x - vector_2.x, vector_1.y - vector_2.y, vector_1.z - vector_2.z);
	}

	Vector3 operator*(float number, const Vector3& vector)
	{
		return Vector3(number * vector.x, number * vector.y, number * vector.z);
	}

	Vector3 operator*(const Vector3& vector, float number)
	{
		return number * vector;
	}

	Vector3 operator*(int number, const Vector3& vector)
	{
		return Vector3(static_cast<float>(number) * vector.x, static_cast<float>(number) * vector.y, static_cast<float>(number) * vector.z);
	}

	Vector3 operator*(const Vector3& vector, int number)
	{
		return number * vector;
	}

	Vector3 operator*(const Vector3& vector_1, const Vector3& vector_2)
	{
		return Vector3(vector_1.x * vector_2.x, vector_1.y * vector_2.y, vector_1.z * vector_2.z);
	}

	Vector3 operator*(const glm::mat3& matrix, const Vector3& vector)
	{
		return Vector3(matrix * vector.to_glm());
	}

	Vector3 operator*(const Vector3& vector, const glm::mat3& matrix)
	{
		return matrix * vector;
	}

	Vector3 operator*(const glm::mat4& matrix, const Vector3& vector)
	{
		return Vector3(matrix * Vector4(vector, 1.f));
	}

	Vector3 operator*(const Vector3& vector, const glm::mat4& matrix)
	{
		return matrix * vector;
	}

	Vector3 operator/(float number, const Vector3& vector)
	{
		return Vector3((vector.x != 0.f ? number / vector.x : 0.f), (vector.y != 0.f ? number / vector.y : 0.f), (vector.z != 0.f ? number / vector.z : 0.f));
	}

	Vector3 operator/(const Vector3& vector, float number)
	{
		if (number == 0.f)
			return Vector3::null;

		return Vector3(vector.x / number, vector.y / number, vector.z / number);
	}

	Vector3 operator/(int number, const Vector3& vector)
	{
		return Vector3((vector.x != 0.f ? static_cast<float>(number) / vector.x : 0.f), (vector.y != 0.f ? static_cast<float>(number) / vector.y : 0.f),
			(vector.z != 0.f ? static_cast<float>(number) / vector.z : 0.f));
	}

	Vector3 operator/(const Vector3& vector, int number)
	{
		if (number == 0)
			return Vector3::null;

		return Vector3(vector.x / static_cast<float>(number), vector.y / static_cast<float>(number), vector.z / static_cast<float>(number));
	}

	Vector3 operator/(const Vector3& vector_1, const Vector3& vector_2)
	{
		return Vector3((vector_2.x != 0.f ? vector_1.x / vector_2.x : 0.f), (vector_2.y != 0.f ? vector_1.y / vector_2.y : 0.f), (vector_2.z != 0.f ? vector_1.z / vector_2.z : 0.f));
	}

	Vector3 operator^(const Vector3& vector_1, const Vector3& vector_2)
	{
		return Vector3(vector_1.y * vector_2.z - vector_1.z * vector_2.y, vector_1.z * vector_2.x - vector_1.x * vector_2.z, vector_1.x * vector_2.y - vector_1.y * vector_2.x);
	}

	float dot(const Vector3& vector_1, const Vector3& vector_2)
	{
		return vector_1.x * vector_2.x + vector_1.y * vector_2.y + vector_1.z * vector_2.z;
	}

	bool operator==(const Vector3& vector_1, const Vector3& vector_2)
	{
		return (vector_1.x == vector_2.x && vector_1.y == vector_2.y && vector_1.z == vector_2.z);
	}

	bool operator!=(const Vector3& vector_1, const Vector3& vector_2)
	{
		return (!(vector_1 == vector_2));
	}

	std::ostream& operator<<(std::ostream& os, const Vector3& vector)
	{
		os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
		return os;
	}

	float distance(const Vector3& point_1, const Vector3& point_2)
	{
		return (point_2 - point_1).get_norm();
	}

	float distance_2(const Vector3& point_1, const Vector3& point_2)
	{
		return (point_2 - point_1).get_norm_2();
	}

	float theta(const Vector3& point_1, const Vector3& point_2)
	{
		return (point_2 - point_1).get_theta();
	}

	float phi(const Vector3& point_1, const Vector3& point_2)
	{
		return (point_2 - point_1).get_phi();
	}

	Vector3 normalize(const Vector3& vector)
	{
		float norm = vector.get_norm();

		if (norm != 0.f)
			return vector / norm;

		return Vector3::unit;
	}
}
