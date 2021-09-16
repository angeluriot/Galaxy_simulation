#ifndef DIM_FLYCONTROLLER_HPP
#define DIM_FLYCONTROLLER_HPP

#include "dim/controllers/Controller.hpp"

namespace dim
{
	/**
	 * @brief A derived class from Controller that allows you to move the camera with the mouse and the
	 * keyboard like a video game (click on the window to control and press escape to stop).
	 */
	class FlyController : public Controller
	{
	private:

		bool								moving;												// True if you currently control.
		sf::Keyboard::Key					forward;											// The key to go forward.
		sf::Keyboard::Key					left;												// The key to go left.
		sf::Keyboard::Key					right;												// The key to go right.
		sf::Keyboard::Key					backward;											// The key to go backward.
		sf::Keyboard::Key					up;													// The key to go up.
		sf::Keyboard::Key					down;												// The key to go down.

	public:

		static constexpr float				default_sensitivity	= 0.2f;							// The default sensitivity of the mouse.
		static constexpr float				default_speed		= 2.f;							// The default speed of the camera.
		static constexpr sf::Keyboard::Key	default_forward		= sf::Keyboard::Key::Z;			// The default forward key.
		static constexpr sf::Keyboard::Key	default_left		= sf::Keyboard::Key::Q;			// The default left key.
		static constexpr sf::Keyboard::Key	default_right		= sf::Keyboard::Key::D;			// The default right key.
		static constexpr sf::Keyboard::Key	default_backward	= sf::Keyboard::Key::S;			// The default backward key.
		static constexpr sf::Keyboard::Key	default_up			= sf::Keyboard::Key::Space;		// The default up key.
		static constexpr sf::Keyboard::Key	default_down		= sf::Keyboard::Key::LControl;	// The default down key.

		/**
		 * @brief Construct a new fly controller.
		 *
		 * @param sensitivity the sensitivity of the mouse
		 * @param speed the speed of the camera
		 */
		FlyController(float sensitivity = default_sensitivity, float speed = default_speed);

		/**
		 * @brief Construct a new fly controller from another.
		 *
		 * @param other the reference fly controller
		 */
		FlyController(const FlyController& other) = default;

		/**
		 * @brief Copy the data of another fly controller.
		 *
		 * @param other the fly controller to copy
		 * @return a reference to the fly controller
		 */
		FlyController& operator=(const FlyController& other) = default;

	private:

		/**
		 * @brief Create a copy of the fly controller.
		 *
		 * @return a pointer to the copy
		 */
		Controller* clone() const override;

		/**
		 * @brief Update the camera's position depending on the keyboard.
		 *
		 * @param camera the camera to update
		 */
		void move(Camera& camera) const;

		/**
		 * @brief Update the camera's direction depending on the mouse (if the controller is used in a scene).
		 *
		 * @param scene the scene
		 * @param camera the camera to update
		 */
		void look(Scene& scene, Camera& camera) const;

		/**
		 * @brief Update the camera's direction depending on the mouse (if the controller is used in the main window).
		 *
		 * @param camera the camera to update
		 */
		void look(Camera& camera) const;

	public:

		/**
		 * @brief Give the type of the controller.
		 *
		 * @return Type::Fly
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
		 * @brief Change the control keys of the controller.
		 *
		 * @param forward the new forward key
		 * @param left the new left key
		 * @param right the new right key
		 * @param backward the new backward key
		 * @param up the new up key
		 * @param down the new down key
		 */
		void set_controls(sf::Keyboard::Key forward, sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key backward, sf::Keyboard::Key up, sf::Keyboard::Key down);
	};
}

#endif
