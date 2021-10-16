#ifndef DIM_TEXTURE_HPP
#define DIM_TEXTURE_HPP

#include "dim/utils/libraries.hpp"

namespace dim
{
	class FrameBuffer;

	/**
	 * @brief A class that represents a image used to give texture to 3D models (it needs to be binded before use and unbinded after).
	 */
	class Texture
	{
	public:

		/**
		 * @brief Tell how to handle texture coordinates outside of the image.
		 */
		enum class Warpping
		{
			Repeat			= GL_REPEAT,			// Repeat the image with the same orientation.
			MirroredRepeat	= GL_MIRRORED_REPEAT,	// Repeat the image with a mirror effect.
			ClampToEdge		= GL_CLAMP_TO_EDGE,		// Stretche pixels at the ends of the image.
			ClampToBorder	= GL_CLAMP_TO_BORDER	// Just draw nothing.
		};

		/**
		 * @brief Tell how to handle texture zoom.
		 */
		enum class Filtering
		{
			Nearest	= GL_NEAREST,	// Pixelate on zoom.
			Linear	= GL_LINEAR		// Blur on zoom.
		};

		/**
		 * @brief The type of the texture pixels.
		 */
		enum class Type
		{
			RGB			= GL_RGB,		// RGB int colors.
			RGBA		= GL_RGBA,		// RGBA int colors.
			RGB_16f		= GL_RGB16F,	// Vector3 float16 values.
			RGBA_16f	= GL_RGBA16F,	// Vector4 float16 values.
			RGB_32f		= GL_RGB32F,	// Vector3 float32 values.
			RGBA_32f	= GL_RGBA32F	// Vector4 float32 values.
		};

		/**
		 * @brief The permissions of the compute shader using the texture image.
		 */
		enum class Permissions
		{
			Read	= GL_READ_ONLY,		// Allow access to read the texture.
			Write	= GL_WRITE_ONLY,	// Allow access to write on the texture.
			All		= GL_READ_WRITE		// Allow both access.
		};

	private:

		std::shared_ptr<GLuint>					id;			// The OpenGL id of the texture.
		mutable std::shared_ptr<unsigned int>	unit;		// The bind order of the texture.
		std::shared_ptr<Type>					pixel_type;	// The type of the texture pixels.

		static std::map<std::string, Texture>	textures;	// The static textures container.
		static int								max_unit;	// The current maximum texture bind order - 1

	public:

		/**
		 * @brief Construct a new texture.
		 */
		Texture();

		/**
		 * @brief Construct a reference to the other texture (it is not a copy).
		 *
		 * @param other the reference texture
		 */
		Texture(const Texture& other) = default;

		/**
		 * @brief Construct a new texture.
		 *
		 * @param path the path to the image file
		 * @param filtering the way to handle texture zoom
		 * @param warpping the way to handle texture coordinates outside of the image
		 */
		Texture(const std::string& path, Filtering filtering = Filtering::Linear, Warpping warpping = Warpping::MirroredRepeat);

		/**
		 * @brief Delete the texture.
		 */
		~Texture();

		/**
		 * @brief Transform the texture to a reference to the other texture (it is not a copy).
		 *
		 * @param other the reference texture
		 * @return a reference to the texture
		 */
		Texture&operator=(const Texture& other) = default;

		/**
		 * @brief Initialize an already created texture.
		 *
		 * @param width the width of the texture
		 * @param height the height of the texture
		 * @param filtering the way to handle texture zoom
		 * @param warpping the way to handle texture coordinates outside of the image
		 * @param pixel_type the type of the texture pixels
		 */
		void create(unsigned int width, unsigned int height, Filtering filtering = Filtering::Linear, Warpping warpping = Warpping::MirroredRepeat, Type pixel_type = Type::RGBA);

		/**
		 * @brief Initialize an already created texture.
		 *
		 * @param size the size of the texture
		 * @param filtering the way to handle texture zoom
		 * @param warpping the way to handle texture coordinates outside of the image
		 * @param pixel_type the type of the texture pixels
		 */
		void create(Vector2int size, Filtering filtering = Filtering::Linear, Warpping warpping = Warpping::MirroredRepeat, Type pixel_type = Type::RGBA);

		/**
		 * @brief Load an image file on an already created texture.
		 *
		 * @param path the path to the image file
		 * @param filtering the way to handle texture zoom
		 * @param warpping the way to handle texture coordinates outside of the image
		 */
		void load(const std::string& path, Filtering filtering = Filtering::Linear, Warpping warpping = Warpping::MirroredRepeat);

		/**
		 * @brief Give the OpenGL id.
		 *
		 * @return the OpenGL id
		 */
		GLuint get_id() const;

		/**
		 * @brief Give the bind order of the texture.
		 *
		 * @return the bind order of the texture
		 */
		unsigned int get_unit() const;

		/**
		 * @brief Bind the texture.
		 */
		void bind() const;

		/**
		 * @brief Unbind the textures.
		 */
		void unbind() const;

		/**
		 * @brief Add a texture to the static textures container (throw if the name already exists).
		 *
		 * @param name the name of the texture
		 * @param texture the texture to add
		 */
		static void add(const std::string& name, const Texture& texture);

		/**
		 * @brief Create a texture and add it to the static textures container (throw if the name already exists).
		 *
		 * @param path the path to the image file
		 * @param filtering the way to handle texture zoom
		 * @param warpping the way to handle texture coordinates outside of the image
		 * @param pixel_type the type of the texture pixels
		 */
		static void add(const std::string& name, const std::string& path, Filtering filtering = Filtering::Linear, Warpping warpping = Warpping::MirroredRepeat, Type pixel_type = Type::RGBA);

		/**
		 * @brief Remove a texture from the static textures container (throw if the name does not exist).
		 *
		 * @param name the name of the texture
		 */
		static void remove(const std::string& name);

		/**
		 * @brief Give a texture from the static textures container (throw if the name does not exist).
		 *
		 * @param name the name of the texture
		 * @return the texture found
		 */
		static Texture get(const std::string& name);

		friend FrameBuffer;
	};
}

#endif
