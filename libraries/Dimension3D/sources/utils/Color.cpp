#include "dim/dimension3D.hpp"

namespace dim
{
	const Color Color::transparent	= Color(0.f, 0.f, 0.f, 0.f);
	const Color Color::black		= Color(0.f, 0.f, 0.f, 1.f);
	const Color Color::white		= Color(1.f, 1.f, 1.f, 1.f);
	const Color Color::red			= Color(1.f, 0.f, 0.f, 1.f);
	const Color Color::green		= Color(0.f, 1.f, 0.f, 1.f);
	const Color Color::blue			= Color(0.f, 0.f, 1.f, 1.f);
	const Color Color::yellow		= Color(1.f, 1.f, 0.f, 1.f);
	const Color Color::pink			= Color(1.f, 0.f, 1.f, 1.f);
	const Color Color::cyan			= Color(0.f, 1.f, 1.f, 1.f);
	const Color Color::orange		= Color(1.f, 0.5f, 0.f, 1.f);
	const Color Color::purple		= Color(0.5f, 0.f, 1.f, 1.f);
	const Color Color::grey			= Color(0.5f, 0.5f, 0.5f, 1.f);

	Color::Color()
	{
		r = 0.f;
		g = 0.f;
		b = 0.f;
		a = 0.f;
	}

	Color::Color(const Vector4& vector)
	{
		*this = vector;
	}

	Color::Color(const sf::Color& color)
	{
		*this = color;
	}

	Color::Color(float red, float green, float blue, float alpha)
	{
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}

	Color& Color::operator=(const Vector4& vector)
	{
		r = vector.x;
		g = vector.y;
		b = vector.z;
		a = vector.w;

		return *this;
	}

	Color& Color::operator=(const sf::Color& color)
	{
		r = color.r / 255.f;
		g = color.g / 255.f;
		b = color.b / 255.f;
		a = color.a / 255.f;

		return *this;
	}

	Color& Color::operator+=(const Color& other)
	{
		*this = *this + other;
		return *this;
	}

	Color& Color::operator-=(const Color& other)
	{
		*this = *this - other;
		return *this;
	}

	Color& Color::operator*=(const Color& other)
	{
		*this = *this * other;
		return *this;
	}

	Color& Color::operator*=(float number)
	{
		*this = *this * number;
		return *this;
	}

	Color& Color::operator*=(int number)
	{
		*this = *this * number;
		return *this;
	}

	Color& Color::operator/=(const Color& other)
	{
		*this = *this / other;
		return *this;
	}

	Color& Color::operator/=(float number)
	{
		*this = *this / number;
		return *this;
	}

	Color& Color::operator/=(int number)
	{
		*this = *this / number;
		return *this;
	}

	sf::Color Color::to_sf() const
	{
		return sf::Color(static_cast<sf::Uint8>(r * 255.f), static_cast<sf::Uint8>(g * 255.f), static_cast<sf::Uint8>(b * 255.f), static_cast<sf::Uint8>(a * 255.f));
	}

	ImVec4 Color::to_im() const
	{
		return ImVec4(r, g, b, a);
	}

	Color operator+(const Color& color_1, const Color& color_2)
	{
		return Color(color_1.r + color_2.r, color_1.g + color_2.g, color_1.b + color_2.b, color_1.a + color_2.a);
	}

	Color operator-(const Color& color_1, const Color& color_2)
	{
		return Color(color_1.r - color_2.r, color_1.g - color_2.g, color_1.b - color_2.b, color_1.a - color_2.a);
	}

	Color operator*(const Color& color_1, const Color& color_2)
	{
		return Color(color_1.r * color_2.r, color_1.g * color_2.g, color_1.b * color_2.b, color_1.a * color_2.a);
	}

	Color operator*(float number, const Color& color)
	{
		return Color(number * color.r, number * color.g, number * color.b, number * color.a);
	}

	Color operator*(const Color& color, float number)
	{
		return Color(color.r * number, color.g * number, color.b * number, color.a * number);
	}

	Color operator*(int number, const Color& color)
	{
		return Color(number * color.r, number * color.g, number * color.b, number * color.a);
	}

	Color operator*(const Color& color, int number)
	{
		return Color(color.r * number, color.g * number, color.b * number, color.a * number);
	}

	Color operator/(const Color& color_1, const Color& color_2)
	{
		return Color(color_1.r / color_2.r, color_1.g / color_2.g, color_1.b / color_2.b, color_1.a / color_2.a);
	}

	Color operator/(float number, const Color& color)
	{
		return Color(number / color.r, number / color.g, number / color.b, number / color.a);
	}

	Color operator/(const Color& color, float number)
	{
		return Color(color.r / number, color.g / number, color.b / number, color.a / number);
	}

	Color operator/(int number, const Color& color)
	{
		return Color(number / color.r, number / color.g, number / color.b, number / color.a);
	}

	Color operator/(const Color& color, int number)
	{
		return Color(color.r / number, color.g / number, color.b / number, color.a / number);
	}
}
