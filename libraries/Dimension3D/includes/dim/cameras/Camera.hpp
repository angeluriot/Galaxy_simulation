#ifndef DIM_CAMERA_HPP
#define DIM_CAMERA_HPP

#include "dim/utils/libraries.hpp"
#include "dim/utils/utils.hpp"
#include "dim/windows/Window.hpp"

namespace dim
{
	class Scene;
	class Controller;
	class OrbitController;
	class FlyController;
	class DragController;
	class Window;

	/**
	 * @brief An abstract class representing a 3D camera (see OrthographicCamera and PerspectiveCamera).
	 */
	class Camera
	{
	public:

		/**
		 * @brief The type of camera.
		 */
		enum class Type
		{
			Orthographic,	// A camera that use an orthographic projection (an object's size in the rendered image stays constant regardless of its distance from the camera).
			Perspective		// A camera that use a perspective projection (it looks like the view of an human eye or a real camera).
		};

	protected:

		Vector3					position;					// The position of the camera.
		glm::mat4				view;						// The view matrix.
		glm::mat4				projection;					// The projection matrix.
		Vector3					direction;					// The direction in which the camera is looking.
		float					yaw;						// The yaw angle of the direction (in degrees).
		float					pitch;						// The pitch angle of the direction (in degrees).
		float					near;						// The nearest distance that the camera can see.
		float					far;						// The farest distance that the camera can see.

	public:

		static constexpr float	default_near	= 0.1f;		// The default nearest distance that the camera can see.
		static constexpr float	default_far		= 100.f;	// The default farest distance that the camera can see.

		/**
		 * @brief construct a new camera.
		 */
		Camera();

		/**
		 * @brief Construct a new camera from another.
		 *
		 * @param other the reference camera
		 */
		Camera(const Camera& other) = default;

		/**
		 * @brief Copy the data of another camera.
		 *
		 * @param other the camera to copy
		 * @return a reference to the camera
		 */
		Camera& operator=(const Camera& other) = default;

	protected:

		/**
		 * @brief Create a copy of the camera.
		 *
		 * @return a pointer to the copy
		 */
		virtual Camera* clone() const = 0;

	public:

		/**
		 * @brief Give the type of the camera.
		 *
		 * @return the type of the camera
		 */
		virtual Type get_type() const = 0;

		/**
		 * @brief Give the view-projection matrix of the camera.
		 *
		 * @return the view-projection matrix
		 */
		glm::mat4 get_matrix() const;

		/**
		 * @brief Give the position of the camera.
		 *
		 * @return the position of the camera
		 */
		Vector3 get_position() const;

		/**
		 * @brief Change the position of the camera.
		 *
		 * @param position the new position of the camera
		 */
		void set_position(const Vector3& position);

		/**
		 * @brief Change the position of the camera.
		 *
		 * @param x the new X position of the camera
		 * @param y the new Y position of the camera
		 * @param z the new Z position of the camera
		 */
		void set_position(float x, float y, float z);

		/**
		 * @brief Give the direction in which the camera is looking.
		 *
		 * @return the direction
		 */
		Vector3 get_direction() const;

		/**
		 * @brief Change the direction in which the camera is looking.
		 *
		 * @param direction the new direction
		 */
		void set_direction(const Vector3& direction);

		/**
		 * @brief Change the direction in which the camera is looking.
		 *
		 * @param yaw the yaw angle of the direction (in degrees)
		 * @param pitch the pitch angle of the direction (in degrees)
		 */
		void set_direction(float yaw, float pitch);

		/**
		 * @brief Give the yaw angle of the direction.
		 *
		 * @return the yaw angle of the direction (in degrees)
		 */
		float get_yaw() const;

		/**
		 * @brief Change the yaw angle of the direction.
		 *
		 * @param yaw the new yaw angle of the direction (in degrees)
		 */
		void set_yaw(float yaw);

		/**
		 * @brief Give the pitch angle of the direction.
		 *
		 * @return the pitch angle of the direction (in degrees)
		 */
		float get_pitch() const;

		/**
		 * @brief Change the pitch angle of the direction.
		 *
		 * @param pitch the new pitch angle of the direction (in degrees)
		 */
		void set_pitch(float pitch);

		/**
		 * @brief Give the nearest distance that the camera can see.
		 *
		 * @return the nearest distance that the camera can see
		 */
		float get_near() const;

		/**
		 * @brief Give the farest distance that the camera can see.
		 *
		 * @return the farest distance that the camera can see
		 */
		float get_far() const;

		/**
		 * @brief Change the resolution of the rendered image.
		 *
		 * @param width the new width of the rendered image
		 * @param height the new height of the rendered image
		 */
		virtual void set_resolution(unsigned int width, unsigned int height) = 0;

		/**
		 * @brief Change the resolution of the rendered image.
		 *
		 * @param resolution the new resolution of the rendered image
		 */
		virtual void set_resolution(const Vector2int& resolution) = 0;

		friend Controller;
		friend OrbitController;
		friend FlyController;
		friend DragController;
		friend Scene;
		friend Window;
	};
}

#endif
