#ifndef DIM_CAMERA2D_HPP
#define DIM_CAMERA2D_HPP

#include "dim/utils/libraries.hpp"

namespace dim
{
	/**
	 * @brief This class represents a 2D camera, it is based on the View class of SFML but with better control of its properties.
	 */
	class Camera2D
	{
	private:

		sf::View	view;		// The SFML View object.
		float		zoom_level;	// The zoom level of the view.
		Vector2		size;		// The resolution of the rendered image.

	public:

		/**
		 * @brief Construct a new 2D camera.
		 */
		Camera2D();

		/**
		 * @brief Construct a new 2D camera from another.
		 *
		 * @param other the reference 2D camera
		 */
		Camera2D(const Camera2D& other) = default;

		/**
		 * @brief Copy the data of another 2D camera.
		 *
		 * @param other the 2D camera to copy
		 * @return a reference to the 2D camera
		 */
		Camera2D& operator=(const Camera2D& other) = default;

		/**
		 * @brief Change the zoom level of the view.
		 *
		 * @param zoom the new zoom level of the view
		 */
		void set_zoom(float zoom);

		/**
		 * @brief Change the rotation of the view.
		 *
		 * @param angle the new rotation of the view
		 */
		void set_rotation(float angle);

		/**
		 * @brief Change the position of the view.
		 *
		 * @param position the new position of the view
		 */
		void set_position(const Vector2& position);

		/**
		 * @brief Change the position of the view.
		 *
		 * @param x the new X position of the view
		 * @param y the new Y position of the view
		 */
		void set_position(float x, float y);

		/**
		 * @brief Zoom on the view.
		 *
		 * @param zoom the zoom to apply
		 */
		void zoom(float zoom);

		/**
		 * @brief Rotate the view.
		 *
		 * @param angle the rotation
		 */
		void rotate(float angle);

		/**
		 * @brief Move the view.
		 *
		 * @param move the move
		 */
		void move(const Vector2& move);

		/**
		 * @brief Move the view.
		 *
		 * @param x the X move
		 * @param y the Y move
		 */
		void move(float x, float y);

		/**
		 * @brief Change the resolution of the rendered image.
		 *
		 * @param width the new width of the rendered image
		 * @param height the new height of the rendered image
		 */
		void set_resolution(unsigned int width, unsigned int height);

		/**
		 * @brief Change the resolution of the rendered image.
		 *
		 * @param resolution the new resolution of the rendered image
		 */
		void set_resolution(const Vector2int& resolution);

		/**
		 * @brief Give the SFML View object.
		 *
		 * @return the SFML View object
		 */
		sf::View& get_view();

		/**
		 * @brief Give the zoom level of the view.
		 *
		 * @return the zoom level of the view
		 */
		float get_zoom() const;

		/**
		 * @brief Give the resolution of the rendered image.
		 *
		 * @return the resolution of the rendered image
		 */
		Vector2 get_resolution() const;
	};
}

#endif
