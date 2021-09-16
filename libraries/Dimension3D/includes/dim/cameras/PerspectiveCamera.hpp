#ifndef DIM_PERSPECTIVECAMERA_HPP
#define DIM_PERSPECTIVECAMERA_HPP

#include "dim/cameras/Camera.hpp"

namespace dim
{
	/**
	 * @brief A derived class from Camera that use a perspective projection
	 * (it looks like the view of an human eye or a real camera).
	 */
	class PerspectiveCamera : public Camera
	{
	private:

		float					fov;				// The field of view of the camera (in degrees).

	public:

		static constexpr float	default_fov = 45.f;	// The default field of view of the camera (in degrees).

		/**
		 * @brief Construct a new perspective camera from another.
		 *
		 * @param other the reference perspective camera
		 */
		PerspectiveCamera(const PerspectiveCamera& other) = default;

		/**
		 * @brief Construct a new perspective camera.
		 *
		 * @param fov the field of view of the camera
		 * @param near the nearest distance that the camera can see
		 * @param far the farest distance that the camera can see
		 */
		PerspectiveCamera(float fov = default_fov, float near = default_near, float far = default_far);

		/**
		 * @brief Copy the data of another perspective camera.
		 *
		 * @param other the perspective camera to copy
		 * @return a reference to the perspective camera
		 */
		PerspectiveCamera& operator=(const PerspectiveCamera& other) = default;

	private:

		/**
		 * @brief Create copy of the perspective camera.
		 *
		 * @return a pointer to the copy
		 */
		Camera* clone() const override;

	public:

		/**
		 * @brief Give the type of the camera.
		 *
		 * @return Type::Perspective
		 */
		Type get_type() const override;

		/**
		 * @brief Give the field of view of the camera.
		 *
		 * @return the field of view of the camera
		 */
		float get_fov() const;

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
