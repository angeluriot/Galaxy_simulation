#ifndef DIM_ORTHOGRAPHICCAMERA_HPP
#define DIM_ORTHOGRAPHICCAMERA_HPP

#include "dim/cameras/Camera.hpp"

namespace dim
{
	/**
	 * @brief A derived class from Camera that use an orthographic projection (an object's
	 * size in the rendered image stays constant regardless of its distance from the camera).
	 */
	class OrthographicCamera : public Camera
	{
	private:

		float					ratio;				// The ratio of the rendered image.
		float					zoom_level;			// The zoom level of the rendered objects.

	public:

		static constexpr float	default_zoom = 1.f;	// The default zoom level of the rendered objects.

		/**
		 * @brief Construct a new orthographic camera from another.
		 *
		 * @param other the reference orthographic camera
		 */
		OrthographicCamera(const OrthographicCamera& other) = default;

		/**
		 * @brief Construct a new orthographic camera.
		 *
		 * @param zoom the zoom level of the rendered objects
		 * @param near the nearest distance that the camera can see
		 * @param far the farest distance that the camera can see
		 */
		OrthographicCamera(float zoom = default_zoom, float near = default_near, float far = default_far);

		/**
		 * @brief Copy the data of another orthographic camera.
		 *
		 * @param other the orthographic camera to copy
		 * @return a reference to the orthographic camera
		 */
		OrthographicCamera& operator=(const OrthographicCamera& other) = default;

	private:

		/**
		 * @brief Create a copy of the orthographic camera.
		 *
		 * @return a pointer to the copy
		 */
		Camera* clone() const override;

	public:

		/**
		 * @brief Give the type of the camera.
		 *
		 * @return Type::Orthographic
		 */
		Type get_type() const override;

		/**
		 * @brief Zoom the rendered objects.
		 *
		 * @param zoom the zoom to apply
		 */
		void zoom(float zoom);

		/**
		 * @brief Change the zoom level of the rendered objects.
		 *
		 * @param zoom the new zoom level
		 */
		void set_zoom(float zoom);

		/**
		 * @brief Give the zoom level of the rendered objects.
		 *
		 * @return the zoom level
		 */
		float get_zoom() const;

		/**
		 * @brief Change the resolution of the rendered image.
		 *
		 * @param width the new width of the rendered image
		 * @param height the new height of the rendered image
		 */
		void set_resolution(unsigned int width, unsigned int height) override;

		/**
		 * @brief Change the resolution of the rendered image.
		 *
		 * @param resolution the new resolution of the rendered image
		 */
		void set_resolution(const Vector2int& resolution) override;
	};
}

#endif
