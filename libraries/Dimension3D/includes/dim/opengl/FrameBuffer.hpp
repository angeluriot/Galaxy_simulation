#ifndef DIM_FRAMEBUFFER_HPP
#define DIM_FRAMEBUFFER_HPP

#include "dim/utils/libraries.hpp"
#include "dim/opengl/Texture.hpp"
#include "dim/utils/Color.hpp"
#include "dim/vectors/Vector2int.hpp"

namespace dim
{

	/**
	 * @brief A class that represents a texture you can draw on. If binded, all the draw calls will affect
	 * the frame buffer instead of the screen (it needs to be binded before use and unbinded after).
	 */
	class FrameBuffer
	{
	private:

		std::shared_ptr<GLuint>						fbo;			// The OpenGL id of the frame buffer.
		std::shared_ptr<GLuint>						rbo;			// The OpenGL id of the deth buffer.
		Texture										texture;		// The color texture.
		std::shared_ptr<unsigned int>				width;			// The width of the textures.
		std::shared_ptr<unsigned int>				height;			// The height of the textures.

		static std::map<std::string, FrameBuffer>	frame_buffers;	// The static frame buffers container.

	public:

		/**
		 * @brief Construct a new frame buffer.
		 */
		FrameBuffer();

		/**
		 * @brief Construct a reference to the other frame buffer (it is not a copy).
		 *
		 * @param other the reference frame buffer
		 */
		FrameBuffer(const FrameBuffer& other) = default;

		/**
		 * @brief Construct a new frame buffer.
		 *
		 * @param width the width of the frame buffer textures
		 * @param height the height of the frame buffer textures
		 * @param texture_type the type of the frame buffer texture
		 */
		FrameBuffer(unsigned int width, unsigned int height, Texture::Type texture_type = Texture::Type::RGB);

		/**
		 * @brief Construct a new frame buffer.
		 *
		 * @param size the size of the frame buffer textures
		 * @param texture_type the type of the frame buffer texture
		 */
		FrameBuffer(const Vector2int& size, Texture::Type texture_type = Texture::Type::RGB);

		/**
		 * @brief Delete the frame buffer.
		 */
		~FrameBuffer();

		/**
		 * @brief Transform the frame buffer to a reference to the other frame buffer (it is not a copy).
		 *
		 * @param other the reference frame buffer
		 * @return a reference to the frame buffer
		 */
		FrameBuffer& operator=(const FrameBuffer& other) = default;

		/**
		 * @brief Initialize an already created frame buffer.
		 *
		 * @param width the width of the frame buffer textures
		 * @param height the height of the frame buffer textures
		 * @param texture_type the type of the frame buffer texture
		 */
		void create(unsigned int width, unsigned int height, Texture::Type texture_type = Texture::Type::RGB);

		/**
		 * @brief Initialize an already created frame buffer.
		 *
		 * @param size the size of the frame buffer textures
		 * @param texture_type the type of the frame buffer texture
		 */
		void create(const Vector2int& size, Texture::Type texture_type = Texture::Type::RGB);

		/**
		 * @brief Bind the frame buffer.
		 */
		void bind() const;

		/**
		 * @brief Unbind the frame buffers.
		 */
		static void unbind();

		/**
		 * @brief Give the OpenGL object id.
		 *
		 * @return the OpenGL object id
		 */
		GLuint get_id() const;

		/**
		 * @brief Give the color texture.
		 *
		 * @return the color texture
		 */
		Texture get_texture() const;

		/**
		 * @brief Change the size of the frame buffer textures.
		 *
		 * @param width the new width of the frame buffer textures
		 * @param height the new height of the frame buffer textures
		 */
		void set_size(unsigned int width, unsigned int height);

		/**
		 * @brief Change the size of the frame buffer textures.
		 *
		 * @param size the new size of the frame buffer textures
		 */
		void set_size(const Vector2int& size);

		/**
		 * @brief Change the width of the frame buffer textures.
		 *
		 * @param width the new width of the frame buffer textures
		 */
		void set_width(unsigned int width);

		/**
		 * @brief Change the height of the frame buffer textures.
		 *
		 * @param width the new height of the frame buffer textures
		 */
		void set_height(unsigned int height);

		/**
		 * @brief Give the size of the frame buffer textures.
		 *
		 * @return the size of the frame buffer textures
		 */
		Vector2int get_size() const;

		/**
		 * @brief Give the width of the frame buffer textures.
		 *
		 * @return the width of the frame buffer textures
		 */
		unsigned int get_width() const;

		/**
		 * @brief Give the height of the frame buffer textures.
		 *
		 * @return the height of the frame buffer textures
		 */
		unsigned int get_height() const;

		/**
		 * @brief Clear the frame buffer textures.
		 *
		 * @param color the new background color
		 */
		void clear(const Color& color = Color::transparent) const;

		/**
		 * @brief Add a frame buffer to the static frame buffers container (throw if the name already exists).
		 *
		 * @param name the name of the frame buffer
		 * @param frame_buffer the frame buffer to add
		 */
		static void add(const std::string& name, const FrameBuffer& frame_buffer);

		/**
		 * @brief Create a frame buffer and add it to the static frame buffers container (throw if the name already exists).
		 *
		 * @param name the name of the frame buffer
		 * @param width the width of the frame buffer textures
		 * @param height the height of the frame buffer textures
		 * @param texture_type the type of the frame buffer texture
		 */
		static void add(const std::string& name, unsigned int width, unsigned int height, Texture::Type texture_type = Texture::Type::RGB);

		/**
		 * @brief Remove a frame buffer from the static frame buffers container (throw if the name does not exist).
		 *
		 * @param name the name of the frame buffer
		 */
		static void remove(const std::string& name);

		/**
		 * @brief Give a frame buffer from the static frame buffers container (throw if the name does not exist).
		 *
		 * @param name the name of the frame buffer
		 * @return the frame buffer found
		 */
		static FrameBuffer get(const std::string& name);
	};
}

#endif
