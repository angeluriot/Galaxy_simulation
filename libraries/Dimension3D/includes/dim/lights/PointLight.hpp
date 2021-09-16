#ifndef DIM_POINTLIGHT_HPP
#define DIM_POINTLIGHT_HPP

#include "dim/lights/Light.hpp"

namespace dim
{
	/**
	 * @brief A derived class from light that represents a light shining in all directions at a certain position.
	 */
	class PointLight : public Light
	{
	public:

		/**
		 * @brief Construct a new point light from another.
		 *
		 * @param other the reference point light
		 */
		PointLight(const PointLight& other) = default;

		/**
		 * @brief Construct a new point light.
		 *
		 * @param position the position of the light
		 * @param color the color of the light
		 * @param intensity the intensity of the light
		 */
		PointLight(const Vector3& position = Vector3(0.f, 0.f, 0.f), const Color& color = Color::white, float intensity = 1.f);

		/**
		 * @brief Copy the data of another point light.
		 *
		 * @param other the point light to copy
		 * @return a reference to the point light
		 */
		PointLight& operator=(const PointLight& other) = default;

	private:

		/**
		 * @brief Create a copy of the point light.
		 *
		 * @return a pointer to the copy
		 */
		Light* clone() const override;

	public:

		/**
		 * @brief Change the position of the light.
		 *
		 * @param x the new X position of the light
		 * @param y the new Y position of the light
		 * @param z the new Z position of the light
		 */
		void set_position(float x, float y, float z);

		/**
		 * @brief Change the position of the light.
		 *
		 * @param position the new position of the light
		 */
		void set_position(const Vector3& position);

		/**
		 * @brief Give the position of the light.
		 *
		 * @return the position of the light
		 */
		Vector3 get_position() const;

		/**
		 * @brief Give the type of the light.
		 *
		 * @return Type::Point
		 */
		Type get_type() const override;
	};
}

#endif
