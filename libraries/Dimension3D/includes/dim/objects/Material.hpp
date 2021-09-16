#ifndef DIM_MATERIAL_HPP
#define DIM_MATERIAL_HPP

#include "dim/utils/libraries.hpp"
#include "dim/utils/Color.hpp"

namespace dim
{
	/**
	 * @brief This class represents how the light behaves on the object in the Phong illumination,
	 * it contains the color of the object and 4 other variables : The first 3 (ambient, diffuse and
	 * specular) define the opacity of the 3 parts of the Phong illumination, and the last variable
	 * is the shininess that defines the size and the smoothness of the reflection.
	 */
	class Material
	{
	private:

		Color	color;			// The color of the object.
		float	ambient;		// The Phong ambient opacity.
		float	diffuse;		// The Phong diffuse opacity.
		float	specular;		// The Phong specular opacity.
		float	shininess;		// The shininess of the object.
		bool	illuminated;	// True if the object interact with light.

	public:

		/**
		 * @brief Construct a new material from another.
		 *
		 * @param other the reference material
		 */
		Material(const Material& other) = default;

		/**
		 * @brief Construct a new material that does not interact with light.
		 *
		 * @param color the color of the object
		 */
		Material(const Color& color = Color(0.f, 0.f, 0.f, 0.f));

		/**
		 * @brief Construct a new material that interacts with light.
		 *
		 * @param color the color of the object
		 * @param ambient the Phong ambient opacity
		 * @param diffuse the Phong diffuse opacity
		 * @param specular the Phong specular opacity
		 * @param shininess the shininess of the object
		 */
		Material(const Color& color, float ambient, float diffuse, float specular, float shininess);

		/**
		 * @brief Copy the data of another material.
		 *
		 * @param other the material to copy
		 * @return a reference to the material
		 */
		Material& operator=(const Material& other) = default;

		/**
		 * @brief Give the color of the material.
		 *
		 * @return the color of the material
		 */
		Color get_color() const;

		/**
		 * @brief Change the color of the material.
		 *
		 * @param color the new color of the material
		 */
		void set_color(const Color& color);

		/**
		 * @brief Give the Phong ambient opacity of the material.
		 *
		 * @return the Phong ambient opacity of the material
		 */
		float get_ambient() const;

		/**
		 * @brief Change the Phong ambient opacity of the material.
		 *
		 * @param ambient the new Phong ambient opacity of the material
		 */
		void set_ambient(float ambient);

		/**
		 * @brief Give the Phong diffuse opacity of the material.
		 *
		 * @return the Phong diffuse opacity of the material
		 */
		float get_diffuse() const;

		/**
		 * @brief Change the Phong diffuse opacity of the material.
		 *
		 * @param diffuse the new Phong diffuse opacity of the material
		 */
		void set_diffuse(float diffuse);

		/**
		 * @brief Give the Phong specular opacity of the material.
		 *
		 * @return the Phong specular opacity of the material
		 */
		float get_specular() const;

		/**
		 * @brief Change the Phong specular opacity of the material.
		 *
		 * @param specular the new Phong specular opacity of the material
		 */
		void set_specular(float specular);

		/**
		 * @brief Give the shininess of the material.
		 *
		 * @return the shininess of the material
		 */
		float get_shininess() const;

		/**
		 * @brief Change the shininess of the material.
		 *
		 * @param shininess the new shininess of the material
		 */
		void set_shininess(float shininess);

		/**
		 * @brief Indicates if the material interacts with light.
		 *
		 * @return true if the material interacts with light, false otherwise
		 */
		bool is_illuminated() const;

		/**
		 * @brief Set if the material should interact with light.
		 *
		 * @param illuminated true if the material should interact with light, false otherwise
		 */
		void set_illuminated(bool illuminated);
	};
}

#endif
