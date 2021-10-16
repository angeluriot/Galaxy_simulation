#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "libraries.hpp"

/**
 * @brief Takes care of the simulation display.
 */
class Renderer
{
public:

	static GLuint				vbo;			// The OpenGL vertex buffer object id.
	static GLuint				vao;			// The OpenGL vertex array object id.
	static dim::VertexBuffer	blur_vbo;		// The VBO of the blur shader.
	static dim::VertexBuffer	post_vbo;		// The VBO of the post processing shader.
	static dim::FrameBuffer		galaxy_fbo_1;	// The FBO of the stars.
	static dim::FrameBuffer		galaxy_fbo_2;	// The FBO of the stars to be blured.
	static dim::FrameBuffer		blur_fbo_1;		// The FBO of the first step of the blur.
	static dim::FrameBuffer		blur_fbo_2;		// The FBO of the second step of the blur.

	/**
	 * @brief Create the OpenGL vertex buffer object.
	 */
	static void init_vbo();

	/**
	 * @brief Update the vertices.
	 */
	static void update_vbo();

	/**
	 * @brief Draw the VBO.
	 */
	static void draw_vbo();

	/**
	 * @brief Bind the VBO.
	 */
	static void bind_vbo();

	/**
	 * @brief Unbind the VBO.
	 */
	static void unbind_vbo();

	/**
	 * @brief Initialize the renderer.
	 */
	static void init();

	/**
	 * @brief Check the events of the renderer.
	 *
	 * @param sf_event the SFML event object
	 */
	static void check_events(const sf::Event& sf_event);

	/**
	 * @brief Clear the FBOs.
	 */
	static void clear();

	/**
	 * @brief Draw the simulation.
	 */
	static void draw();
};

#endif
