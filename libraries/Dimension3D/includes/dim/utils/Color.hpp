#ifndef DIM_COLOR_HPP
#define DIM_COLOR_HPP

#include "dim/utils/libraries.hpp"

namespace dim
{
	class Vector4;

	/**
	 * @brief A class that represents a color with the red, green, blue and alpha part from 0 to 1.
	 */
	class Color
	{
	public:

		float				r;				// The red component.
		float				g;				// The green component.
		float				b;				// The blue component.
		float				a;				// The opacity of the color.

		static const Color	transparent;	// A transparent color.
		static const Color	black;			// A black color.
		static const Color	white;			// A white color.
		static const Color	red;			// A red color.
		static const Color	green;			// A green color.
		static const Color	blue;			// A blue color.
		static const Color	yellow;			// A yellow color.
		static const Color	pink;			// A pink color.
		static const Color	cyan;			// A cyan color.
		static const Color	orange;			// An orange color.
		static const Color	purple;			// A purple color.
		static const Color	grey;			// A grey color.

		/**
		 * @brief Construct a new color.
		 */
		Color();

		/**
		 * @brief Construct a new color from another.
		 *
		 * @param other the reference color
		 */
		Color(const Color& other) = default;

		/**
		 * @brief Construct a new color from a 4D vector.
		 *
		 * @param vector the 4D vector
		 */
		Color(const Vector4& vector);

		/**
		 * @brief Construct a new color from an SFML color.
		 *
		 * @param color the SFML color
		 */
		Color(const sf::Color& color);

		/**
		 * @brief Construct a new color.
		 *
		 * @param red the red component
		 * @param green the green component
		 * @param blue the blue component
		 * @param alpha the opacity of the color
		 */
		Color(float red, float green, float blue, float alpha = 1.f);

		/**
		 * @brief Copy the data of another color.
		 *
		 * @param other the color to copy
		 * @return a reference to the color
		 */
		Color& operator=(const Color& other) = default;

		/**
		 * @brief Change the color from the values of a 4D vector.
		 *
		 * @param vector the 4D vector
		 * @return a reference to the color
		 */
		Color& operator=(const Vector4& vector);

		/**
		 * @brief Change the color from the values of an SFML color.
		 *
		 * @param color the SFML color
		 * @return a reference to the color
		 */
		Color& operator=(const sf::Color& color);

		/**
		 * @brief Add the color with another.
		 *
		 * @param other the other color
		 * @return a reference to the color
		 */
		Color& operator+=(const Color& other);

		/**
		 * @brief Subtract the color with another.
		 *
		 * @param other the other color
		 * @return a reference to the color
		 */
		Color& operator-=(const Color& other);

		/**
		 * @brief Multiply the color with another.
		 *
		 * @param other the other color
		 * @return a reference to the color
		 */
		Color& operator*=(const Color& other);

		/**
		 * @brief Multiply the color with a float number.
		 *
		 * @param number the float number
		 * @return a reference to the color
		 */
		Color& operator*=(float number);

		/**
		 * @brief Multiply the color with an integer.
		 *
		 * @param number the integer
		 * @return a reference to the color
		 */
		Color& operator*=(int number);

		/**
		 * @brief Divide the color with another.
		 *
		 * @param other the other color
		 * @return a reference to the color
		 */
		Color& operator/=(const Color& other);

		/**
		 * @brief Divide the color with a float number.
		 *
		 * @param number the float number
		 * @return a reference to the color
		 */
		Color& operator/=(float number);

		/**
		 * @brief Divide the color with an integer.
		 *
		 * @param number the integer
		 * @return a reference to the color
		 */
		Color& operator/=(int number);

		/**
		 * @brief Give an SFML color with the same color.
		 *
		 * @return the SFML color
		 */
		sf::Color to_sf() const;

		/**
		 * @brief Give an ImGui 4D vector with the same color.
		 *
		 * @return the ImGui 4D vector
		 */
		ImVec4 to_im() const;
	};

	/**
	 * @brief Add the component values of two colors.
	 *
	 * @param color_1 the first color
	 * @param color_2 the second color
	 * @return the result
	 */
	Color operator+(const Color& color_1, const Color& color_2);

	/**
	 * @brief Subtract the component values of two colors.
	 *
	 * @param color_1 the first color
	 * @param color_2 the second color
	 * @return the result
	 */
	Color operator-(const Color& color_1, const Color& color_2);

	/**
	 * @brief Multiply the component values of two colors.
	 *
	 * @param color_1 the first color
	 * @param color_2 the second color
	 * @return the result
	 */
	Color operator*(const Color& color_1, const Color& color_2);

	/**
	 * @brief Multiply a float number with the component values of a color.
	 *
	 * @param number the float number
	 * @param color the color
	 * @return the result
	 */
	Color operator*(float number, const Color& color);

	/**
	 * @brief Multiply the component values of a color with a float number.
	 *
	 * @param color the color
	 * @param number the float number
	 * @return the result
	 */
	Color operator*(const Color& color, float number);

	/**
	 * @brief Multiply an integer number with the component values of a color.
	 *
	 * @param number the integer
	 * @param color the color
	 * @return the result
	 */
	Color operator*(int number, const Color& color);

	/**
	 * @brief Multiply the component values of a color with an integer.
	 *
	 * @param color the color
	 * @param number the integer
	 * @return the result
	 */
	Color operator*(const Color& color, int number);

	/**
	 * @brief Divide the component values of two colors.
	 *
	 * @param color_1 the first color
	 * @param color_2 the second color
	 * @return the result
	 */
	Color operator/(const Color& color_1, const Color& color_2);

	/**
	 * @brief Divide a float number with the component values of a color.
	 *
	 * @param number the float number
	 * @param color the color
	 * @return the result
	 */
	Color operator/(float number, const Color& color);

	/**
	 * @brief Divide the component values of a color with a float number.
	 *
	 * @param color the color
	 * @param number the float number
	 * @return the result
	 */
	Color operator/(const Color& color, float number);

	/**
	 * @brief Divide an integer number with the component values of a color.
	 *
	 * @param number the integer
	 * @param color the color
	 * @return the result
	 */
	Color operator/(int number, const Color& color);

	/**
	 * @brief Divide the component values of a color with an integer.
	 *
	 * @param color the color
	 * @param number the integer
	 * @return the result
	 */
	Color operator/(const Color& color, int number);
}

#endif
