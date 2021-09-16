#include "dim/dimension3D.hpp"

namespace dim
{
	std::map<std::string, FrameBuffer> FrameBuffer::frame_buffers = {};

	FrameBuffer::FrameBuffer()
	{
		fbo = std::make_shared<GLuint>();
		rbo = std::make_shared<GLuint>();
		width = std::make_shared<unsigned int>(Window::initial_size.x);
		height = std::make_shared<unsigned int>(Window::initial_size.y);
		texture.pixel_type = std::make_shared<Texture::Type>(Texture::Type::RGB);
	}

	FrameBuffer::FrameBuffer(unsigned int width, unsigned int height, Texture::Type texture_type)
	{
		fbo = std::make_shared<GLuint>(0);
		rbo = std::make_shared<GLuint>(0);
		this->width = std::make_shared<unsigned int>(std::max(width, static_cast<unsigned int>(1)));
		this->height = std::make_shared<unsigned int>(std::max(height, static_cast<unsigned int>(1)));
		texture.pixel_type = std::make_shared<Texture::Type>(Texture::Type::RGB);

		create(width, height, texture_type);
	}

	FrameBuffer::FrameBuffer(const Vector2int& size, Texture::Type texture_type)
	{
		fbo = std::make_shared<GLuint>(0);
		rbo = std::make_shared<GLuint>(0);
		width = std::make_shared<unsigned int>(std::max(size.x, 1));
		height = std::make_shared<unsigned int>(std::max(size.y, 1));
		texture.pixel_type = std::make_shared<Texture::Type>(Texture::Type::RGB);

		create(size, texture_type);
	}

	FrameBuffer::~FrameBuffer()
	{
		if (fbo.unique())
		{
			glDeleteFramebuffers(1, &(*fbo));
			glDeleteRenderbuffers(1, &(*rbo));
		}
	}

	void FrameBuffer::create(unsigned int width, unsigned int height, Texture::Type texture_type)
	{
		*(this->width) = std::max(width, static_cast<unsigned int>(1));
		*(this->height) = std::max(height, static_cast<unsigned int>(1));
		*texture.pixel_type = texture_type;

		glDeleteFramebuffers(1, &(*fbo));
		glDeleteTextures(1, &(*texture.id));
		glDeleteRenderbuffers(1, &(*rbo));

		glGenFramebuffers(1, &(*fbo));
		glBindFramebuffer(GL_FRAMEBUFFER, *fbo);
		{
			glGenTextures(1, &(*texture.id));
			glBindTexture(GL_TEXTURE_2D, *texture.id);
			{
				if (*texture.pixel_type == Texture::Type::RGB || *texture.pixel_type == Texture::Type::RGBA)
					glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(*texture.pixel_type), *(this->width), *(this->height), 0, static_cast<GLint>(*texture.pixel_type), GL_UNSIGNED_BYTE, NULL);

				else if (*texture.pixel_type == Texture::Type::RGB_16f || *texture.pixel_type == Texture::Type::RGB_32f)
					glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(*texture.pixel_type), *(this->width), *(this->height), 0, GL_RGB, GL_FLOAT, NULL);

				else
					glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(*texture.pixel_type), *(this->width), *(this->height), 0, GL_RGBA, GL_FLOAT, NULL);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *texture.id, 0);
			}
			glBindTexture(GL_TEXTURE_2D, 0);

			glGenRenderbuffers(1, &(*rbo));
			glBindRenderbuffer(GL_RENDERBUFFER, *rbo);
			{
				glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, *(this->width), *(this->height));
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, *rbo);
			}
			glBindRenderbuffer(GL_RENDERBUFFER, 0);

			if (!(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE))
				throw std::runtime_error("Frame buffer error");
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::create(const Vector2int& size, Texture::Type texture_type)
	{
		create(size.x, size.y, texture_type);
	}

	void FrameBuffer::bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, *fbo);
		glViewport(0, 0, *width, *height);
	}

	void FrameBuffer::unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, Window::get_width(), Window::get_height());
	}

	GLuint FrameBuffer::get_id() const
	{
		return *fbo;
	}

	Texture FrameBuffer::get_texture() const
	{
		return texture;
	}

	void FrameBuffer::set_size(unsigned int width, unsigned int height)
	{
		create(width, height, *texture.pixel_type);
	}

	void FrameBuffer::set_size(const Vector2int& size)
	{
		create(size.x, size.y, *texture.pixel_type);
	}

	void FrameBuffer::set_width(unsigned int width)
	{
		set_size(width, *height);
	}

	void FrameBuffer::set_height(unsigned int height)
	{
		set_size(*width, height);
	}

	Vector2int FrameBuffer::get_size() const
	{
		return Vector2int(*width, *height);
	}

	unsigned int FrameBuffer::get_width() const
	{
		return *width;
	}

	unsigned int FrameBuffer::get_height() const
	{
		return *height;
	}

	void FrameBuffer::clear(const Color& color) const
	{
		glViewport(0, 0, *width, *height);
		glEnable(GL_DEPTH_TEST);
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void FrameBuffer::add(const std::string& name, const FrameBuffer& frame_buffer)
	{
		if (!frame_buffers.insert(std::make_pair(name, frame_buffer)).second)
			throw std::invalid_argument("This name is already used");
	}

	void FrameBuffer::add(const std::string& name, unsigned int width, unsigned int height, Texture::Type texture_type)
	{
		if (!frame_buffers.insert(std::make_pair(name, FrameBuffer(width, height, texture_type))).second)
			throw std::invalid_argument("This name is already used");
	}

	void FrameBuffer::remove(const std::string& name)
	{
		if (!frame_buffers.erase(name))
			throw std::invalid_argument("This name does not exit");
	}

	FrameBuffer FrameBuffer::get(const std::string& name)
	{
		try
		{
			return frame_buffers.at(name);
		}

		catch (const std::out_of_range&)
		{
			throw std::invalid_argument("This name does not exit");
		}
	}
}
