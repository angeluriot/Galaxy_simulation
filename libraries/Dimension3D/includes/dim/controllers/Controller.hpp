#ifndef DIM_CONTROLLER_HPP
#define DIM_CONTROLLER_HPP

#include "dim/utils/libraries.hpp"

namespace dim
{
	class Scene;
	class Camera;
	class Window;

	/**
	 * @brief An abstract class allowing you to move a camera with the mouse (see OrbitController, DragController and FlyController).
	 */
	class Controller
	{
	public:

		/**
		 * @brief The type of controller.
		 */
		enum class Type
		{
			Orbit,	// A controller that allows you to move the camera around a target and zoom with the mouse.
			Drag,	// A controller that allows you to move the camera on a plan and zoom with the mouse (is the only one that affects 2D cameras).
			Fly		// A controller that allows you to move the camera with the mouse and the keyboard like a video game (click on the window to control and press escape to stop).
		};

		/**
		 * @brief The type of action a controller can apply to the camera.
		 */
		enum class Action
		{
			Look,	// Change the direction of the camera.
			Move,	// Change the position of the camera.
			All		// Change the direction and the position of the camera.
		};

	protected:

		float	sensitivity;	// The sensitivity of the mouse.
		float	speed;			// The speed of the camera.
		bool	look_active;	// True if the controller can change the direction of the camera.
		bool	move_active;	// True if the controller can change the position of the camera.

	public:

		/**
		 * @brief Construct a new controller.
		 */
		Controller();

		/**
		 * @brief Construct a new controller from another.
		 *
		 * @param other the reference controller
		 */
		Controller(const Controller& other) = default;

		/**
		 * @brief Copy the data of another controller.
		 *
		 * @param other the controller to copy
		 * @return a reference to the controller
		 */
		Controller& operator=(const Controller& other) = default;

	protected:

		/**
		 * @brief Create a copy of the controller.
		 *
		 * @return a pointer to the copy
		 */
		virtual Controller* clone() const = 0;

	public:

		/**
		 * @brief Give the type of the controller.
		 *
		 * @return the type of the controller
		 */
		virtual Type get_type() const = 0;

		/**
		 * @brief Give the sensitivity of the controller.
		 *
		 * @return the sensitivity of the controller
		 */
		float get_sensitivity() const;

		/**
		 * @brief Change the sensitivity of the controller.
		 *
		 * @param sensitivity the new sensitivity of the controller
		 */
		void set_sensitivity(float sensitivity);

		/**
		 * @brief Give the speed of the camera.
		 *
		 * @return the speed of the camera
		 */
		float get_speed() const;

		/**
		 * @brief Change the speed of the camera.
		 *
		 * @param speed the new speed of the camera
		 */
		void set_speed(float speed);

		/**
		 * @brief Check the mouse and the resize events (if the controller is used in a scene).
		 *
		 * @param sf_event the SFML event object
		 * @param scene the scene
		 * @param camera the camera
		 */
		virtual void check_events(const sf::Event& sf_event, Scene& scene, Camera& camera) = 0;

		/**
		 * @brief Check the mouse and the resize events (if the controller is used in the main window).
		 *
		 * @param sf_event the SFML event object
		 * @param camera the camera
		 */
		virtual void check_events(const sf::Event& sf_event, Camera& camera) = 0;

		/**
		 * @brief Update the controller based on the mouse moves (if the controller is used in a scene).
		 *
		 * @param scene the scene
		 * @param camera the camera
		 */
		virtual void update(Scene& scene, Camera& camera) = 0;

		/**
		 * @brief Update the controller based on the mouse moves (if the controller is used in the main window).
		 *
		 * @param camera the camera
		 */
		virtual void update(Camera& camera) = 0;

		/**
		 * @brief Enable or disable the controller.
		 *
		 * @param enable true to enable and false to disable the controller
		 * @param action the action you want to enable / disable
		 */
		void enable(bool enable, Action action = Action::All);

		friend Scene;
		friend Window;
	};
}

#endif
