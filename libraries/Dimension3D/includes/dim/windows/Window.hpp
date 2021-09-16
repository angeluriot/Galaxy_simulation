#ifndef DIM_WINDOW_HPP
#define DIM_WINDOW_HPP

#include "dim/utils/libraries.hpp"

namespace dim
{
	class Camera;
	class Camera2D;
	class Object;
	class Controller;
	class OrbitController;
	class FlyController;
	class DragController;

	/**
	 * @brief A static class that represents the main window, it can be binded for optimization but it is not essential.
	 */
	class Window
	{
	private:

		static sf::RenderWindow*	window;					// A pointer to a SFML window.
		static float				screen_coef;			// The coefficient between HD and the size of the window.
		static sf::Clock			clock;					// Update elapsed_time.
		static float				elapsed_time;			// The elapsed time since the last frame.
		static float				thickness;				// The current OpenGL line thickness.
		static bool					cull_face;				// The current OpenGL cull face mode (true for enabled).
		static Controller*			controller;				// The controller of the window.
		static Camera*				camera;					// The 3D camera of the window.
		static bool					unique_shader;			// True if all objects are drawn with the same shader.
		static Shader				shader;					// The shader used if unique_shader is true.
		static bool					binded;					// True if the window is currently binded.
		static Camera2D				fixed_camera2D;			// The 2D camera of fixed SFML shapes.
		static std::vector<Light*>	lights;					// The lights of the window.
		static FrameBuffer			frame_buffer;			// The frame buffer where Dimension3D objects are drawn.
		static Shader				post_processing_shader;	// The post processing shader used id post_processing is true.
		static bool					post_processing;		// True if you want to add a post processing shader to the window.
		static VertexBuffer			screen;					// Screen object used to apply the post processing shader.

	public:

		static const Color			background;				// The default background color of the window.
		static const Vector2int		initial_size;			// The minimal size of the window (and the initial size of others like scenes of frame buffers).
		static bool					running;				// True if the program is running.
		static Camera2D				camera2D;				// The 2D camera of the window.

		/**
		 * @brief Open the window and initialize all the libraries.
		 *
		 * @param name the name of the window
		 * @param screen_ratio the ratio to the size of the screen
		 * @param icon_path the path to an image for the icon of the window
		 */
		static void open(const std::string& name, float screen_ratio, const std::string& icon_path = "");

		/**
		 * @brief Open the window and initialize all the libraries.
		 *
		 * @param name the name of the window
		 * @param width the width of the window
		 * @param height the height of the window
		 * @param icon_path the path to an image for the icon of the window
		 */
		static void open(const std::string& name, unsigned int width, unsigned int height, const std::string& icon_path = "");

		/**
		 * @brief Open the window and initialize all the libraries.
		 *
		 * @param name the name of the window
		 * @param size the size of the window
		 * @param icon_path the path to an image for the icon of the window
		 */
		static void open(const std::string& name, const Vector2int& size, const std::string& icon_path = "");

		/**
		 * @brief Give a reference to the SFML window.
		 *
		 * @return the reference to the SFML window
		 */
		static sf::RenderWindow& get_window();

		/**
		 * @brief Give the position of the window.
		 *
		 * @return the position of the window
		 */
		static Vector2int get_position();

		/**
		 * @brief Give the width of the window.
		 *
		 * @return the width of the window
		 */
		static unsigned int get_width();

		/**
		 * @brief Give the height of the window.
		 *
		 * @return the height of the window
		 */
		static unsigned int get_height();

		/**
		 * @brief Give the size of the window.
		 *
		 * @return the size of the window
		 */
		static Vector2int get_size();

		/**
		 * @brief Bind the window.
		 */
		static void bind();

		/**
		 * @brief Unbind the window.
		 */
		static void unbind();

		/**
		 * @brief Change the 3D camera of the window.
		 *
		 * @param camera the new 3D camera of the window
		 */
		static void set_camera(const Camera& camera);

		/**
		 * @brief Give a reference to the 3D camera of the window.
		 *
		 * @return the reference to the 3D camera
		 */
		static Camera& get_camera();

		/**
		 * @brief Change the controller of the window.
		 *
		 * @param controller the new controller of the window
		 */
		static void set_controller(const Controller& controller);

		/**
		 * @brief Give a reference to the controller of the window.
		 *
		 * @return the reference to the controller
		 */
		static Controller& get_controller();

		/**
		 * @brief Change the shader of the window.
		 *
		 * @param shader the name of the new shader of the window
		 */
		static void set_shader(const std::string& shader_name);

		/**
		 * @brief Change the shader of the window.
		 *
		 * @param shader the new shader of the window
		 */
		static void set_shader(const Shader& shader);

		/**
		 * @brief Give the shader of the window.
		 *
		 * @return the shader of the window
		 */
		static Shader get_shader();

		/**
		 * @brief Give the frame buffer of the window.
		 *
		 * @return the frame buffer of the window
		 */
		static FrameBuffer get_frame_buffer();

		/**
		 * @brief Change the post processing shader of the window.
		 *
		 * @param shader the name of the new post processing shader of the window
		 */
		static void set_post_processing_shader(const std::string& shader_name);

		/**
		 * @brief Change the post processing shader of the window.
		 *
		 * @param shader the new post processing shader of the window
		 */
		static void set_post_processing_shader(const Shader& shader);

		/**
		 * @brief Give the post processing shader of the window.
		 *
		 * @return the post processing shader of the window
		 */
		static Shader get_post_processing_shader();

		/**
		 * @brief Give the mouse position in the 2D scene world.
		 *
		 * @return the mouse position in the 2D scene world
		 */
		static Vector2 get_2d_world_mouse_position();

		/**
		 * @brief Add a light to the window.
		 *
		 * @param light the light to add
		 */
		static void add_light(const Light& light);

		/**
		 * @brief Remove all lights.
		 */
		static void clear_lights();

		/**
		 * @brief Clear the rendered image.
		 *
		 * @param color the new background color
		 */
		static void clear(const Color& color = background);

		/**
		 * @brief But the current SFML events in the sf_event parameter.
		 *
		 * @param sf_event collect the SFML events
		 * @return false when all the events are collected, true otherwise
		 */
		static bool poll_event(sf::Event& sf_event);

		/**
		 * @brief Check and handle mouse and resize events.
		 *
		 * @param sf_event the SFML event
		 */
		static void check_events(const sf::Event& sf_event);

		/**
		 * @brief Update the window based of the user actions.
		 */
		static void update();

		/**
		 * @brief Draw an SFML shape on the window.
		 *
		 * @param drawable the SFML shape to draw
		 * @param fixed true if the shape should not be affected by the 2D camera
		 */
		static void draw(const sf::Drawable& drawable, bool fixed = false);

		/**
		 * @brief Draw a Dimension3D object on the window.
		 *
		 * @param object the Dimension3D object to draw
		 * @param draw_type the way to draw it
		 */
		static void draw(const Object& object, DrawType draw_type = DrawType::Default);

		/**
		 * @brief Draw a vertex buffer on the window.
		 *
		 * @param vertex_buffer the vertex buffer to draw
		 * @param draw_type the way to draw it
		 */
		static void draw(const VertexBuffer& vertex_buffer, DrawType draw_type = DrawType::Triangles);

		/**
		 * @brief Draw the scene on the main window.
		 */
		static void display();

		/**
		 * @brief Close the window and shut down all the libraries.
		 */
		static void close();

		/**
		 * @brief Convert an HD position into the window position.
		 *
		 * @param position the input HD position
		 * @return the output window position
		 */
		static int hd_to_window(int position);

		/**
		 * @brief Convert an HD position into the window position.
		 *
		 * @param x the input HD X position
		 * @param y the input HD Y position
		 * @return the output window position
		 */
		static Vector2int hd_to_window(int x, int y);

		/**
		 * @brief Convert an HD position into the window position.
		 *
		 * @param position the input HD position
		 * @return the output window position
		 */
		static Vector2int hd_to_window(const Vector2int& position);

		/**
		 * @brief Change the OpenGL thickness.
		 *
		 * @param thickness the new OpenGL thickness
		 */
		static void set_thickness(float thickness);

		/**
		 * @brief Change the OpenGL cull face mode.
		 *
		 * @param enable true to enable OpenGL cull face, false otherwise
		 */
		static void set_cull_face(bool enable);

		/**
		 * @brief Give the elapsed time since the last frame.
		 *
		 * @return the elapsed time since the last frame
		 */
		static float get_elapsed_time();

		/**
		 * @brief Tell if the position is in the window.
		 *
		 * @param position the position to test
		 * @return true if the position is in the window, false otherwise
		 */
		static bool is_in(const Vector2& position);

		/**
		 * @brief Tell if the position is on the border of the window.
		 *
		 * @param position the position to test
		 * @return true if the position is on the border of the window, false otherwise
		 */
		static bool is_on_border(const Vector2& position);
	};

	/**
	 * @brief Give a reference to the SFML window.
	 *
	 * @return the reference to the SFML window
	 */
	sf::RenderWindow& get_window();

	/**
	 * @brief Convert an HD position into the window position.
	 *
	 * @param position the input HD position
	 * @return the output window position
	 */
	int hd_to_window(int position);

	/**
	 * @brief Convert an HD position into the window position.
	 *
	 * @param x the input HD X position
	 * @param y the input HD Y position
	 * @return the output window position
	 */
	Vector2int hd_to_window(int x, int y);

	/**
	 * @brief Convert an HD position into the window position.
	 *
	 * @param position the input HD position
	 * @return the output window position
	 */
	Vector2int hd_to_window(const Vector2int& position);
}

#endif
