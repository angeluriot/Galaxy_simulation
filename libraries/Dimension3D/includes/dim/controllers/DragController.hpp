#ifndef DIM_DRAGCONTROLLER_HPP
#define DIM_DRAGCONTROLLER_HPP

#include "dim/controllers/Controller.hpp"

namespace dim
{
	/**
	 * @brief A derived class from Controller that allows you to move the camera on a plan and zoom with the mouse (is the only one that affects 2D cameras).
	 */
	class DragController : public Controller
	{
	private:

		Vector2					prev_mouse_pos;				// The previous mouse position.
		bool					prev_mouse_click;			// True if the mouse clicked on the previous frame.
		bool					move_forbidden;				// True if the move is forbidden because you started the movement outside the window.

	public:

		static constexpr float	default_sensitivity	= 1.f;	// The default sensitivity of the mouse.
		static constexpr float	default_speed		= 0.2f;	// The default speed of the camera.

		/**
		 * @brief Construct a new drag controller.
		 *
		 * @param sensitivity the sensitivity of the mouse
		 * @param speed the speed of the camera
		 */
		DragController(float sensitivity = default_sensitivity, float speed = default_speed);

		/**
		 * @brief Construct a new drag controller from another.
		 *
		 * @param other the reference drag controller
		 */
		DragController(const DragController& other) = default;

		/**
		 * @brief Copy the data of another drag controller.
		 *
		 * @param other the drag controller to copy
		 * @return a reference to the drag controller
		 */
		DragController& operator=(const DragController& other) = default;

	private:

		/**
		 * @brief Create a copy of the drag controller.
		 *
		 * @return a pointer to the copy
		 */
		Controller* clone() const override;

	public:

		/**
		 * @brief Give the type of the controller.
		 *
		 * @return Type::Drag
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
	};
}

#endif
