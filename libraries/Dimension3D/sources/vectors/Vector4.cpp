#include "dim/dimension3D.hpp"

namespace dim
{
	const Vector4 Vector4::null = Vector4();
	const Vector4 Vector4::unit = Vector4(1.f, 0.f, 0.f, 0.f);

	Vector4::Vector4()
	{
		x = 0.f;
		y = 0.f;
		z = 0.f;
		w = 0.f;
	}

	Vector4::Vector4(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Vector4::Vector4(const Vector2& other, float z, float w)
	{
		x = other.x;
		y = other.y;
		this->z = z;
		this->w = w;
	}

	Vector4::Vector4(float x, const Vector2& other, float w)
	{
		this->x = x;
		y = other.x;
		z = other.y;
		this->w = w;
	}

	Vector4::Vector4(float x, float y, const Vector2& other)
	{
		this->x = x;
		this->y = y;
		z = other.x;
		w = other.y;
	}

	Vector4::Vector4(const Vector3& other, float w)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		this->w = w;
	}

	Vector4::Vector4(float x, const Vector3& other)
	{
		this->x = x;
		y = other.x;
		z = other.y;
		w = other.z;
	}

	Vector4::Vector4(const Vector2int& other, float z, float w)
	{
		x = static_cast<float>(other.x);
		y = static_cast<float>(other.y);
		this->z = z;
		this->w = w;
	}

	Vector4::Vector4(float x, const Vector2int& other, float w)
	{
		this->x = x;
		y = static_cast<float>(other.x);
		z = static_cast<float>(other.y);
		this->w = w;
	}

	Vector4::Vector4(float x, float y, const Vector2int& other)
	{
		this->x = x;
		this->y = y;
		z = static_cast<float>(other.x);
		w = static_cast<float>(other.y);
	}

	Vector4::Vector4(const Vector3int& other, float w)
	{
		x = static_cast<float>(other.x);
		y = static_cast<float>(other.y);
		z = static_cast<float>(other.z);
		this->w = w;
	}

	Vector4::Vector4(float x, const Vector3int& other)
	{
		this->x = x;
		y = static_cast<float>(other.x);
		z = static_cast<float>(other.y);
		w = static_cast<float>(other.z);
	}

	Vector4::Vector4(const Vector4int& other)
	{
		*this = other;
	}

	Vector4::Vector4(const std::array<float, 4>& other)
	{
		*this = other;
	}

	Vector4::Vector4(const std::array<int, 4>& other)
	{
		*this = other;
	}

	Vector4::Vector4(const glm::vec4& other)
	{
		*this = other;
	}

	Vector4::Vector4(const ImVec4& other)
	{
		*this = other;
	}

	Vector4::Vector4(const Color& color)
	{
		*this = color;
	}

	Vector4& Vector4::operator=(const Vector4int& other)
	{
		x = static_cast<float>(other.x);
		y = static_cast<float>(other.y);
		z = static_cast<float>(other.z);
		w = static_cast<float>(other.w);

		return *this;
	}

	Vector4& Vector4::operator=(const std::array<float, 4>& other)
	{
		x = other[0];
		y = other[1];
		z = other[2];
		w = other[3];

		return *this;
	}

	Vector4& Vector4::operator=(const std::array<int, 4>& other)
	{
		x = static_cast<float>(other[0]);
		y = static_cast<float>(other[1]);
		z = static_cast<float>(other[2]);
		w = static_cast<float>(other[3]);

		return *this;
	}

	Vector4& Vector4::operator=(const glm::vec4& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;

		return *this;
	}

	Vector4& Vector4::operator=(const ImVec4& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;

		return *this;
	}

	Vector4& Vector4::operator=(const Color& color)
	{
		x = color.r;
		y = color.g;
		z = color.b;
		w = color.a;

		return *this;
	}

	Vector4& Vector4::operator+=(const Vector4& other)
	{
		*this = *this + other;
		return *this;
	}

	Vector4& Vector4::operator-=(const Vector4& other)
	{
		*this = *this - other;
		return *this;
	}

	Vector4& Vector4::operator*=(const Vector4& other)
	{
		*this = *this * other;
		return *this;
	}

	Vector4& Vector4::operator*=(float number)
	{
		*this = *this * number;
		return *this;
	}

	Vector4& Vector4::operator*=(int number)
	{
		*this = *this * number;
		return *this;
	}

	Vector4& Vector4::operator*=(const glm::mat4& matrix)
	{
		*this = *this * matrix;
		return *this;
	}

	Vector4& Vector4::operator/=(const Vector4& other)
	{
		*this = *this / other;
		return *this;
	}

	Vector4& Vector4::operator/=(float number)
	{
		*this = *this / number;
		return *this;
	}

	Vector4& Vector4::operator/=(int number)
	{
		*this = *this / number;
		return *this;
	}

	Vector4 Vector4::operator+() const
	{
		return *this;
	}

	Vector4 Vector4::operator-() const
	{
		return null - *this;
	}

	float Vector4::get_norm() const
	{
		return sqrt(x * x + y * y + z * z + w * w);
	}

	float Vector4::get_norm_2() const
	{
		return x * x + y * y + z * z + w * w;
	}

	const float* Vector4::get_ptr() const
	{
		return &x;
	}

	void Vector4::set_norm(float norm)
	{
		*this = dim::normalize(*this) * norm;
	}

	void Vector4::normalize()
	{
		*this = dim::normalize(*this);
	}

	void Vector4::clear()
	{
		*this = null;
	}

	std::array<float, 4> Vector4::to_array_float() const
	{
		return { x, y, z, w };
	}

	std::array<int, 4> Vector4::to_array_int() const
	{
		return { static_cast<int>(round(x)), static_cast<int>(round(y)), static_cast<int>(round(z)), static_cast<int>(round(w)) };
	}

	glm::vec4 Vector4::to_glm() const
	{
		return glm::vec4(x, y, z, w);
	}

	ImVec4 Vector4::to_imgui() const
	{
		return ImVec4(x, y, z, w);
	}

	Vector4 operator+(const Vector4& vector_1, const Vector4& vector_2)
	{
		return Vector4(vector_1.x + vector_2.x, vector_1.y + vector_2.y, vector_1.z + vector_2.z, vector_1.w + vector_2.w);
	}

	Vector4 operator-(const Vector4& vector_1, const Vector4& vector_2)
	{
		return Vector4(vector_1.x - vector_2.x, vector_1.y - vector_2.y, vector_1.z - vector_2.z, vector_1.w - vector_2.w);
	}

	Vector4 operator*(float number, const Vector4& vector)
	{
		return Vector4(number * vector.x, number * vector.y, number * vector.z, number * vector.w);
	}

	Vector4 operator*(const Vector4& vector, float number)
	{
		return number * vector;
	}

	Vector4 operator*(int number, const Vector4& vector)
	{
		return Vector4(static_cast<float>(number) * vector.x, static_cast<float>(number) * vector.y,
			static_cast<float>(number) * vector.z, static_cast<float>(number) * vector.w);
	}

	Vector4 operator*(const Vector4& vector, int number)
	{
		return number * vector;
	}

	Vector4 operator*(const Vector4& vector_1, const Vector4& vector_2)
	{
		return Vector4(vector_1.x * vector_2.x, vector_1.y * vector_2.y, vector_1.z * vector_2.z, vector_1.w * vector_2.w);
	}

	Vector4 operator*(const glm::mat4& matrix, const Vector4& vector)
	{
		return Vector4(matrix * vector.to_glm());
	}

	Vector4 operator*(const Vector4& vector, const glm::mat4& matrix)
	{
		return matrix * vector;
	}

	Vector4 operator/(float number, const Vector4& vector)
	{
		return Vector4((vector.x != 0.f ? number / vector.x : 0.f), (vector.y != 0.f ? number / vector.y : 0.f),
			(vector.z != 0.f ? number / vector.z : 0.f), (vector.w != 0.f ? number / vector.w : 0.f));
	}

	Vector4 operator/(const Vector4& vector, float number)
	{
		if (number == 0.f)
			return Vector4::null;

		return Vector4(vector.x / number, vector.y / number, vector.z / number, vector.w / number);
	}

	Vector4 operator/(int number, const Vector4& vector)
	{
		return Vector4((vector.x != 0.f ? static_cast<float>(number) / vector.x : 0.f), (vector.y != 0.f ? static_cast<float>(number) / vector.y : 0.f),
			(vector.z != 0.f ? static_cast<float>(number) / vector.z : 0.f), (vector.w != 0.f ? static_cast<float>(number) / vector.w : 0.f));
	}

	Vector4 operator/(const Vector4& vector, int number)
	{
		if (number == 0)
			return Vector4::null;

		return Vector4(vector.x / static_cast<float>(number), vector.y / static_cast<float>(number),
			vector.z / static_cast<float>(number), vector.w / static_cast<float>(number));
	}

	Vector4 operator/(const Vector4& vector_1, const Vector4& vector_2)
	{
		return Vector4((vector_2.x != 0.f ? vector_1.x / vector_2.x : 0.f), (vector_2.y != 0.f ? vector_1.y / vector_2.y : 0.f),
			(vector_2.z != 0.f ? vector_1.z / vector_2.z : 0.f), (vector_2.w != 0.f ? vector_1.w / vector_2.w : 0.f));
	}

	float dot(const Vector4& vector_1, const Vector4& vector_2)
	{
		return vector_1.x * vector_2.x + vector_1.y * vector_2.y + vector_1.z * vector_2.z + vector_1.w * vector_2.w;
	}

	bool operator==(const Vector4& vector_1, const Vector4& vector_2)
	{
		return (vector_1.x == vector_2.x && vector_1.y == vector_2.y && vector_1.z == vector_2.z && vector_1.w == vector_2.w);
	}

	bool operator!=(const Vector4& vector_1, const Vector4& vector_2)
	{
		return (!(vector_1 == vector_2));
	}

	std::ostream& operator<<(std::ostream& os, const Vector4& vector)
	{
		os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
		return os;
	}

	float distance(const Vector4& point_1, const Vector4& point_2)
	{
		return (point_2 - point_1).get_norm();
	}

	float distance_2(const Vector4& point_1, const Vector4& point_2)
	{
		return (point_2 - point_1).get_norm_2();
	}

	Vector4 normalize(const Vector4& vector)
	{
		float norm = vector.get_norm();

		if (norm != 0.f)
			return vector / norm;

		return Vector4::unit;
	}
}
