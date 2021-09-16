#ifndef DIM_SCENE_HPP
#define DIM_SCENE_HPP

#include "dim/utils/libraries.hpp"
#include "dim/utils/utils.hpp"
#include "dim/opengl/FrameBuffer.hpp"
#include "dim/cameras/Camera2D.hpp"

namespace dim
{
	void shut_down();
	class Camera;
	class Object;
	class Controller;
	class OrbitController;
	class FlyController;
	class DragController;

	/**
	 * @brief A class that represents an ImGui window made for display graphics content, it can be binded for optimization but it is not essential.
	 */
	class Scene
	{
	private:

		std::string								name;					// The name of the scene.
		FrameBuffer								frame_buffer;			// The frame buffer where Dimension3D objects are drawn.
		sf::RenderTexture						render_texture;			// The render texture where SFML shapes are drawn.
		Controller*								controller;				// The controller of the scene.
		Camera*									camera;					// The 3D camera of the scene.
		Vector2int								size;					// The size of the window.
		Vector2int								min;					// The top left corner coordinates of the window.
		Vector2int								max;					// The right down corner coordinates of the window.
		bool									active;					// True if the window is on the on the foreground.
		bool									moving;					// True if the window is moving.
		bool									resized;				// True if the window is being resized.
		unsigned int							frame_id;				// A frame counter.
		bool									unique_shader;			// True if all objects are drawn with the same shader.
		Shader									shader;					// The shader used if unique_shader is true.
		mutable bool							binded;					// True if the scene is currently binded.
		Camera2D								fixed_camera2D;			// The 2D camera of fixed SFML shapes.
		std::vector<Light*>						lights;					// The lights of the scene.
		Shader									post_processing_shader;	// The post processing shader used id post_processing is true.
		bool									post_processing;		// True if you want to add a post processing shader to the scene.
		VertexBuffer							screen;					// Screen object used to apply the post processing shader.
		sf::RenderTexture						clear_texture;			// A render texture to clear OpenGL status.
		bool									to_delete;				// True if the scene has to be delete automatically.

		static std::map<std::string, Scene*>	scenes;					// The static scenes container.

	public:

		Camera2D								camera2D;				// The 2D camera of the scene.

		/**
		 * @brief Construct a new scene.
		 */
		Scene();

		/**
		 * @brief Construct a new scene from another.
		 *
		 * @param other the reference scene
		 */
		Scene(const Scene& other);

		/**
		 * @brief Construct a new scene.
		 *
		 * @param name the name of the scene
		 */
		Scene(const std::string& name);

		/**
		 * @brief Delete the scene.
		 */
		~Scene();

		/**
		 * @brief Copy the data of another scene.
		 *
		 * @param other the scene to copy
		 * @return a reference to the scene
		 */
		Scene& operator=(const Scene& other);

		/**
		 * @brief Initialize an already created scene.
		 *
		 * @param name the name of the scene.
		 */
		void create(const std::string& name);

		/**
		 * @brief Check and handle mouse and resize events
		 *
		 * @param sf_event the SFML event
		 */
		void check_events(const sf::Event& sf_event);

		/**
		 * @brief Update the scene based of the user actions.
		 */
		void update();

		/**
		 * @brief Bin the scene.
		 */
		void bind() const;

		/**
		 * @brief Unbind the scene.
		 */
		void unbind() const;

		/**
		 * @brief Give the name of the scene.
		 *
		 * @return the name of the scene
		 */
		std::string get_name() const;

		/**
		 * @brief Change the name of the scene.
		 *
		 * @param name the new name of the scene
		 */
		void set_name(const std::string& name);

		/**
		 * @brief Change the 3D camera of the scene.
		 *
		 * @param camera the new 3D camera of the scene
		 */
		void set_camera(const Camera& camera);

		/**
		 * @brief Give a reference to the 3D camera of the scene.
		 *
		 * @return the reference to the 3D camera
		 */
		Camera& get_camera();

		/**
		 * @brief Change the controller of the scene.
		 *
		 * @param controller the new controller of the scene
		 */
		void set_controller(const Controller& controller);

		/**
		 * @brief Give a reference to the controller of the scene.
		 *
		 * @return the reference to the controller
		 */
		Controller& get_controller();

		/**
		 * @brief Give the width of the window.
		 *
		 * @return the width of the window
		 */
		unsigned int get_width() const;

		/**
		 * @brief Give the height of the window.
		 *
		 * @return the height of the window
		 */
		unsigned int get_height() const;

		/**
		 * @brief Give the size of the window.
		 *
		 * @return the size of the window
		 */
		Vector2int get_size() const;

		/**
		 * @brief Give the center of the window.
		 *
		 * @return the center of the window
		 */
		Vector2int get_center() const;

		/**
		 * @brief Give the frame buffer of the scene.
		 *
		 * @return the frame buffer of the scene
		 */
		FrameBuffer get_frame_buffer() const;

		/**
		 * @brief Give the render texture of the scene.
		 *
		 * @return the render texture of the scene
		 */
		const sf::RenderTexture& get_render_texture() const;

		/**
		 * @brief Tell if the scene is on the foreground.
		 *
		 * @return true if the scene is on the foreground, false otherwise
		 */
		bool is_active() const;

		/**
		 * @brief Tell if the scene is moving.
		 *
		 * @return true if the scene is moving, false otherwise
		 */
		bool is_moving() const;

		/**
		 * @brief Tell if the scene is being resized.
		 *
		 * @return true if the scene is being resized, false otherwise
		 */
		bool is_resized() const;

		/**
		 * @brief Change the shader of the scene.
		 *
		 * @param shader the name of the new shader of the scene
		 */
		void set_shader(const std::string& shader_name);

		/**
		 * @brief Change the shader of the scene.
		 *
		 * @param shader the new shader of the scene
		 */
		void set_shader(const Shader& shader);

		/**
		 * @brief Give the shader of the scene.
		 *
		 * @return the shader of the scene
		 */
		Shader get_shader() const;

		/**
		 * @brief Change the post processing shader of the scene.
		 *
		 * @param shader the name of the new post processing shader of the scene
		 */
		void set_post_processing_shader(const std::string& shader_name);

		/**
		 * @brief Change the post processing shader of the scene.
		 *
		 * @param shader the new post processing shader of the scene
		 */
		void set_post_processing_shader(const Shader& shader);

		/**
		 * @brief Give the post processing shader of the scene.
		 *
		 * @return the post processing shader of the scene
		 */
		Shader get_post_processing_shader() const;

		/**
		 * @brief Tell if a position is in the window.
		 *
		 * @param position the position to test
		 * @return true if the position if in the window, false otherwise
		 */
		bool is_in(const Vector2& position) const;

		/**
		 * @brief Give the mouse position in the 2D scene world.
		 *
		 * @return the mouse position in the 2D scene world
		 */
		Vector2 get_2d_world_mouse_position();

		/**
		 * @brief Add a light to the scene.
		 *
		 * @param light the light to add
		 */
		void add_light(const Light& light);

		/**
		 * @brief Remove all lights.
		 */
		void clear_lights();

		/**
		 * @brief Clear the rendered image.
		 *
		 * @param color the new background color
		 */
		void clear(const Color& color = Color::transparent);

		/**
		 * @brief Draw an SFML shape on the scene.
		 *
		 * @param drawable the SFML shape to draw
		 * @param fixed true if the shape should not be affected by the 2D camera
		 */
		void draw(const sf::Drawable& drawable, bool fixed = false);

		/**
		 * @brief Draw a Dimension3D object on the scene.
		 *
		 * @param object the Dimension3D object to draw
		 * @param draw_type the way to draw it
		 */
		void draw(const Object& object, DrawType draw_type = DrawType::Default);

		/**
		 * @brief Draw a vertex buffer on the scene.
		 *
		 * @param vertex_buffer the vertex buffer to draw
		 * @param draw_type the way to draw it
		 */
		void draw(const VertexBuffer& vertex_buffer, DrawType draw_type = DrawType::Triangles);

		/**
		 * @brief Draw the scene on the main window.
		 */
		void display();

		/**
		 * @brief Add a scene to the static scenes container (throw if the name already exists).
		 *
		 * @param name the name of the scene
		 * @param scene the scene to add
		 */
		static void add(Scene& scene);

		/**
		 * @brief Create a scene and add it to the static scenes container (throw if the name already exists).
		 *
		 * @param name the name of the scene
		 */
		static void add(const std::string& name);

		/**
		 * @brief Remove a scene from the static scenes container (throw if the name does not exist).
		 *
		 * @param name the name of the scene
		 */
		static void remove(const std::string& name);

		/**
		 * @brief Give a scene from the static scenes container (throw if the name does not exist).
		 *
		 * @param name the name of the scene
		 * @return the scene found
		 */
		static Scene& get(const std::string& name);

		/**
		 * @brief Check the events of all scenes.
		 *
		 * @param sf_event the SFML event
		 */
		static void check_all_events(const sf::Event& sf_event);

		/**
		 * @brief Update all scenes.
		 */
		static void update_all();

		/**
		 * @brief Clear all scenes.
		 */
		static void clear_all();

		/**
		 * @brief Display all scenes.
		 */
		static void display_all();

		friend Controller;
		friend OrbitController;
		friend FlyController;
		friend DragController;
		friend void shut_down();
	};
}

#endif
