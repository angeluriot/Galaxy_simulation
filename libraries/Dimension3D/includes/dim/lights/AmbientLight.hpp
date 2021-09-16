#ifndef DIM_AMBIENTLIGHT_HPP
#define DIM_AMBIENTLIGHT_HPP

#include "dim/lights/Light.hpp"

namespace dim
{
	/**
	 * @brief A derived class from light that represents an ambient light.
	 */
	class AmbientLight : public Light
	{
	public:

		/**
		 * @brief Construct a new ambient light from another.
		 *
		 * @param other the reference ambient light
		 */
		AmbientLight(const AmbientLight& other) = default;

		/**
		 * @brief Construct a new ambient light.
		 *
		 * @param color the color of the ambient light
		 * @param intensity the intensity of the ambient light
		 */
		AmbientLight(const Color& color = Color::white, float intensity = 1.f);

		/**
		 * @brief Copy the data of another ambient light.
		 *
		 * @param other the ambient light to copy
		 * @return a reference to the ambient light
		 */
		AmbientLight& operator=(const AmbientLight& other) = default;

	private:

		/**
		 * @brief Create a copy of the ambient light.
		 *
		 * @return a pointer to the copy
		 */
		Light* clone() const override;

	public:

		/**
		 * @brief Give the type of the light.
		 *
		 * @return Type::Ambient
		 */
		Type get_type() const override;
	};
}

#endif
