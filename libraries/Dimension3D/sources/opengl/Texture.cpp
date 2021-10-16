#include "dim/dimension3D.hpp"

namespace dim
{
	std::map<std::string, Texture>	Texture::textures = {};
	int								Texture::max_unit = -1;

	Texture::Texture()
	{
		id = std::make_shared<GLuint>(0);
		unit = std::make_shared<unsigned int>(-1);
		pixel_type = std::make_shared<Type>(Type::RGBA);
	}

	Texture::Texture(const std::string& path, Filtering filtering, Warpping warpping)
	{
		id = std::make_shared<GLuint>(0);
		unit = std::make_shared<unsigned int>(-1);
		pixel_type = std::make_shared<Type>(Type::RGBA);
		load(path, filtering, warpping);
	}

	Texture::~Texture()
	{
		if (id.unique())
			glDeleteTextures(1, &(*id));
	}

	void Texture::create(unsigned int width, unsigned int height, Filtering filtering, Warpping warpping, Type pixel_type)
	{
		*(this->pixel_type) = pixel_type;

		glDeleteTextures(1, &(*id));
		*unit = -1;

		glGenTextures(1, &(*id));
		glBindTexture(GL_TEXTURE_2D, *id);
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLenum>(filtering));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLenum>(filtering));

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLenum>(warpping));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLenum>(warpping));

			glGenerateMipmap(GL_TEXTURE_2D);

			if (pixel_type == Texture::Type::RGB || pixel_type == Texture::Type::RGBA)
					glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(pixel_type), width, height, 0, static_cast<GLint>(pixel_type), GL_UNSIGNED_BYTE, NULL);

			else if (pixel_type == Texture::Type::RGB_16f || pixel_type == Texture::Type::RGB_32f)
				glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(pixel_type), width, height, 0, GL_RGB, GL_FLOAT, NULL);

			else
				glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(pixel_type), width, height, 0, GL_RGBA, GL_FLOAT, NULL);
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::create(Vector2int size, Filtering filtering, Warpping warpping, Type pixel_type)
	{
		create(size.x, size.y, filtering, warpping, pixel_type);
	}

	void Texture::load(const std::string& path, Filtering filtering, Warpping warpping)
	{
		glDeleteTextures(1, &(*id));
		*unit = -1;
		*pixel_type = Type::RGBA;

		sf::Image image;

		if (!image.loadFromFile(path))
			throw std::runtime_error("The texture could not be loaded");

		glGenTextures(1, &(*id));
		glBindTexture(GL_TEXTURE_2D, *id);
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLenum>(filtering));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLenum>(filtering));

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLenum>(warpping));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLenum>(warpping));

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)image.getPixelsPtr());
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	GLuint Texture::get_id() const
	{
		return *id;
	}

	unsigned int Texture::get_unit() const
	{
		return *unit;
	}

	void Texture::bind() const
	{
		*unit = max_unit + 1;
		glActiveTexture(GL_TEXTURE0 + *unit);
		glBindTexture(GL_TEXTURE_2D, *id);
		max_unit++;
	}

	void Texture::unbind() const
	{
		*unit = -1;
		glBindTexture(GL_TEXTURE_2D, 0);
		max_unit = std::max(-1, max_unit - 1);
	}

	void Texture::add(const std::string& name, const Texture& texture)
	{
		if (!textures.insert(std::make_pair(name, texture)).second)
			throw std::invalid_argument("This name is already used");
	}

	void Texture::add(const std::string& name, const std::string& path, Filtering filtering, Warpping warpping, Type pixel_type)
	{
		if (!textures.insert(std::make_pair(name, Texture(path, filtering, warpping))).second)
			throw std::invalid_argument("This name is already used");
	}

	void Texture::remove(const std::string& name)
	{
		if (!textures.erase(name))
			throw std::invalid_argument("This name does not exit");
	}

	Texture Texture::get(const std::string& name)
	{
		try
		{
			return textures.at(name);
		}

		catch (const std::out_of_range&)
		{
			throw std::invalid_argument("This name does not exit");
		}
	}
}
