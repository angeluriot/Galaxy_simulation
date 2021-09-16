#ifndef DIM_DIRECTIONALLIGHT_HPP
#define DIM_DIRECTIONALLIGHT_HPP

#include "dim/lights/Light.hpp"

namespace dim
{
	/**
	 * @brief A derived class from light that represents a light at an infinite distance shining in a certain direction (like the sun).
	 */
	class DirectionalLight : public Light
	{
	public:

		/**
		 * @brief Construct a new directional light from another.
		 *
		 * @param other the reference directional light
		 */
		DirectionalLight(const DirectionalLight& other) = default;

		/**
		 * @brief Construct a new directional light.
		 *
		 * @param direction the direction of the light
		 * @param color the color of the light
		 * @param intensity the intensity of the light
		 */
		DirectionalLight(const Vector3& direction = Vector3(0.f, -1.f, 0.f), const Color& color = Color::white, float intensity = 1.f);

		/**
		 * @brief Copy the data of another directional light.
		 *
		 * @param other the directional light to copy
		 * @return a reference to the directional light
		 */
		DirectionalLight& operator=(const DirectionalLight& other) = default;

	private:

		/**
		 * @brief Create a copy of the directional light.
		 *
		 * @return a pointer to the copy
		 */
		Light* clone() const override;

	public:

		/**
		 * @brief Change the direction of the light.
		 *
		 * @param x the new X direction of the light
		 * @param y the new Y direction of the light
		 * @param z the new Z direction of the light
		 */
		void set_direction(float x, float y, float z);

		/**
		 * @brief Change the direction of the light.
		 *
		 * @param direction the new direction of the light
		 */
		void set_direction(const Vector3& direction);

		/**
		 * @brief Give the direction of the light.
		 *
		 * @return the direction of the light
		 */
		Vector3 get_direction() const;

		/**
		 * @brief Give the type of the light.
		 *
		 * @return Type::Directional
		 */
		Type get_type() const override;
	};
}

#endif
