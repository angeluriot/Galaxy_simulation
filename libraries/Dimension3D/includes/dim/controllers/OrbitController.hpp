#ifndef DIM_ORBITCONTROLLER_HPP
#define DIM_ORBITCONTROLLER_HPP

#include "dim/controllers/Controller.hpp"

namespace dim
{
	/**
	 * @brief A derived class from Controller that allows you to move the camera around a target and zoom with the mouse.
	 */
	class OrbitController : public Controller
	{
	private:

		Vector3					prev_center;					// The previous target of the camera.
		Vector3					center;							// The current target of the camera.
		Vector2					prev_mouse_pos;					// The previous mouse position.
		bool					prev_mouse_click;				// True if the mouse clicked on the previous frame.
		bool					rotation_forbidden;				// True if the move is forbidden because you started the movement outside the window.
		bool					center_changed;					// True if the target of the camera changed.

	public:

		static constexpr float	default_sensitivity	= 0.005f;	// The default sensitivity of the mouse.
		static constexpr float	default_speed		= 0.2f;		// The default speed of the camera.

		/**
		 * @brief Construct a new orbit controller.
		 *
		 * @param center the target of the camera
		 * @param sensitivity the sensitivity of the mouse
		 * @param speed the speed of the camera
		 */
		OrbitController(const Vector3& center = Vector3(0.f, 0.f, 0.f), float sensitivity = default_sensitivity, float speed = default_speed);

		/**
		 * @brief Construct a new orbit controller from another.
		 *
		 * @param other the reference orbit controller
		 */
		OrbitController(const OrbitController& other) = default;

		/**
		 * @brief Copy the data of another orbit controller.
		 *
		 * @param other the orbit controller to copy
		 * @return a reference to the orbit controller
		 */
		OrbitController& operator=(const OrbitController& other) = default;

	private:

		/**
		 * @brief Create a copy of the orbit controller.
		 *
		 * @return a pointer to the copy
		 */
		Controller* clone() const override;

	public:

		/**
		 * @brief Give the type of the controller.
		 *
		 * @return Type::Orbit
		 */
		Type get_type() const override;

		/**
		 * @brief Check the mouse and the resize events (if the controller is used in a scene).
		 *
		 * @param sf_event the SFML event object
		 * @param scene the scene
		 * @param camera the camera
		 */
		void check_events(const sf::Event& sf_event, Scene& scene, Camera& camera) override;

		/**
		 * @brief Check the mouse and the resize events (if the controller is used in the main window).
		 *
		 * @param sf_event the SFML event object
		 * @param camera the camera
		 */
		void check_events(const sf::Event& sf_event, Camera& camera) override;

		/**
		 * @brief Update the controller based on the mouse moves (if the controller is used in a scene).
		 *
		 * @param scene the scene
		 * @param camera the camera
		 */
		void update(Scene& scene, Camera& camera) override;

		/**
		 * @brief Update the controller based on the mouse moves (if the controller is used in the main window).
		 *
		 * @param camera the camera
		 */
		void update(Camera& camera) override;

		/**
		 * @brief Change the target of the camera.
		 *
		 * @param x the new X target of the camera
		 * @param y the new Y target of the camera
		 * @param z the new Z target of the camera
		 */
		void set_center(float x, float y, float z);

		/**
		 * @brief Change the target of the camera.
		 *
		 * @param center the new target of the camera
		 */
		void set_center(const Vector3& center);

		/**
		 * @brief Give the target of the camera
		 *
		 * @return the target of the camera
		 */
		Vector3 get_center() const;
	};
}

#endif
