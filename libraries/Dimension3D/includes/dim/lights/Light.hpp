#ifndef DIM_LIGHT_HPP
#define DIM_LIGHT_HPP

#include "dim/utils/libraries.hpp"
#include "dim/vectors/Vector3.hpp"
#include "dim/lights/Light.hpp"
#include "dim/utils/Color.hpp"

namespace dim
{
	class Shader;
	class Scene;
	class Window;

	/**
	 * @brief An abstract class that represents a light (see AmbientLight, DirectionalLight and PointLight).
	 */
	class Light
	{
	public:

		/**
		 * @brief The type of light.
		 */
		enum class Type
		{
			Ambient		= 0,	// An ambient light.
			Directional	= 1,	// A light at an infinite distance shining in a certain direction (like the sun).
			Point		= 2		// A light shining in all directions at a certain position.
		};

	protected:

		Vector3	vector;		// The position for PointLight and the direction for DirectionalLight.
		Color	color;		// The color of the light.
		float	intensity;	// The intensity of the light.

	public:

		/**
		 * @brief Construct a new light.
		 */
		Light();

		/**
		 * @brief Construct a new light from another.
		 *
		 * @param other the reference light
		 */
		Light(const Light& other) = default;

		/**
		 * @brief Copy the data of another light.
		 *
		 * @param other the light to copy
		 * @return a reference to the light
		 */
		Light& operator=(const Light& other) = default;

	protected:

		/**
		 * @brief Create a copy of the light.
		 *
		 * @return a pointer to the copy
		 */
		virtual Light* clone() const = 0;

	public:

		/**
		 * @brief Give the type of the light.
		 *
		 * @return the type of the light
		 */
		virtual Type get_type() const = 0;

		/**
		 * @brief Give the color of the light.
		 *
		 * @return the color of the light
		 */
		Color get_color() const;

		/**
		 * @brief Change the color of the light.
		 *
		 * @param color the new color of the light
		 */
		void set_color(const Color& color);

		/**
		 * @brief Give the intensity of the light.
		 *
		 * @return the intensity of the light
		 */
		float get_intensity() const;

		/**
		 * @brief Change the intensity of the light.
		 *
		 * @param intensity the new intensity of the light
		 */
		void set_intensity(float intensity);

		friend Shader;
		friend Scene;
		friend Window;
	};
}

#endif
