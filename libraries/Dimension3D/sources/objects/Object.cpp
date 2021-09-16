#include "dim/dimension3D.hpp"

namespace dim
{
	Object::Object()
	{
		scaling_matrix = glm::mat4(1.f);
		rotation_matrix = glm::mat4(1.f);
		translation_matrix = glm::mat4(1.f);
		origin_matrix = glm::mat4(1.f);
		model = translation_matrix * rotation_matrix * scaling_matrix * origin_matrix;
		thickness = 1.f;
		textured = false;
		binded = false;
	}

	Object::Object(const Object& other)
	{
		*this = other;
	}

	Object::Object(const Mesh& mesh, const Material& material)
	{
		create(mesh, material);
	}

	Object& Object::operator=(const Object& other)
	{
		shader = other.shader;
		mesh = other.mesh;
		vertex_buffer.set_shader(shader);
		vertex_buffer.send_data(mesh);
		texture = other.texture;
		scaling_matrix = other.scaling_matrix;
		rotation_matrix = other.rotation_matrix;
		translation_matrix = other.translation_matrix;
		origin_matrix = other.origin_matrix;
		model = other.model;
		thickness = other.thickness;
		textured = other.textured;

		return *this;
	}

	void Object::create(const Mesh& mesh, const Material& material)
	{
		shader = Shader::default_shader;
		this->mesh = mesh;
		this->material = material;
		vertex_buffer.set_shader(shader);
		vertex_buffer.send_data(this->mesh);
		scaling_matrix = glm::mat4(1.f);
		rotation_matrix = glm::mat4(1.f);
		translation_matrix = glm::mat4(1.f);
		origin_matrix = glm::mat4(1.f);
		model = translation_matrix * rotation_matrix * scaling_matrix * origin_matrix;
		thickness = 1.f;
		textured = false;
		binded = false;
	}

	void Object::set_shader(const std::string& shader_name)
	{
		shader = Shader::get(shader_name);
		vertex_buffer.set_shader(shader_name);
		vertex_buffer.send_data(mesh);
	}

	void Object::set_shader(const Shader& shader)
	{
		this->shader = shader;
		vertex_buffer.set_shader(this->shader);
		vertex_buffer.send_data(mesh);
	}

	Shader Object::get_shader() const
	{
		return shader;
	}

	void Object::set_texture(const std::string& texture_name)
	{
		texture = Texture::get(texture_name);
		textured = true;
	}

	void Object::set_texture(const Texture& texture)
	{
		this->texture = texture;
		textured = true;
	}

	void Object::remove_texture()
	{
		textured = false;
	}

	Texture Object::get_texture() const
	{
		return texture;
	}

	void Object::set_mesh(const Mesh& mesh, dim::DataType data_sent)
	{
		this->mesh = mesh;
		vertex_buffer.send_data(mesh, data_sent);
	}

	void Object::update_mesh(dim::DataType data_sent)
	{
		vertex_buffer.send_data(mesh, data_sent);
	}

	void Object::set_size(float x, float y, float z)
	{
		set_size(Vector3(x, y, z));
	}

	void Object::set_size(const Vector3& size)
	{
		scaling_matrix = glm::scale(glm::mat4(1.f), size.to_glm());
		model = translation_matrix * rotation_matrix * scaling_matrix * origin_matrix;
	}

	void Object::set_rotation(float angle, const Vector3& axis)
	{
		rotation_matrix = glm::rotate(glm::mat4(1.f), glm::radians(angle), axis.to_glm());
		model = translation_matrix * rotation_matrix * scaling_matrix * origin_matrix;
	}

	void Object::set_position(float x, float y, float z)
	{
		set_position(Vector3(x, y, z));
	}

	void Object::set_position(const Vector3& position)
	{
		translation_matrix = glm::translate(glm::mat4(1.f), position.to_glm());
		model = translation_matrix * rotation_matrix * scaling_matrix * origin_matrix;
	}

	void Object::set_origin(float x, float y, float z)
	{
		set_origin(Vector3(x, y, z));
	}

	void Object::set_origin(const Vector3& origin)
	{
		origin_matrix = glm::translate(glm::mat4(1.f), origin.to_glm());
		model = translation_matrix * rotation_matrix * scaling_matrix * origin_matrix;
	}

	void Object::set_thickness(float thickness)
	{
		this->thickness = std::max(thickness, 0.f);
	}

	void Object::scale(float x, float y, float z)
	{
		scale(Vector3(x, y, z));
	}

	void Object::scale(const Vector3& scale)
	{
		scaling_matrix = glm::scale(scaling_matrix, scale.to_glm());
		model = translation_matrix * rotation_matrix * scaling_matrix * origin_matrix;
	}

	void Object::rotate(float angle, const Vector3& axis)
	{
		rotation_matrix = glm::rotate(rotation_matrix, glm::radians(angle), axis.to_glm());
		model = translation_matrix * rotation_matrix * scaling_matrix * origin_matrix;
	}

	void Object::move(float x, float y, float z)
	{
		move(Vector3(x, y, z));
	}

	void Object::move(const Vector3& move)
	{
		translation_matrix = glm::translate(translation_matrix, move.to_glm());
		model = translation_matrix * rotation_matrix * scaling_matrix * origin_matrix;
	}

	Vector3 Object::get_size() const
	{
		return Vector4(scaling_matrix * glm::vec4(1.f, 1.f, 1.f, 1.f));
	}

	glm::mat4 Object::get_rotation() const
	{
		return rotation_matrix;
	}

	Vector3 Object::get_position() const
	{
		return Vector4(translation_matrix * glm::vec4(0.f, 0.f, 0.f, 1.f));
	}

	Vector3 Object::get_origin() const
	{
		return Vector4(origin_matrix * glm::vec4(0.f, 0.f, 0.f, 1.f));
	}

	float Object::get_thickness() const
	{
		return thickness;
	}

	void Object::bind() const
	{
		shader.bind();
		texture.bind();
		vertex_buffer.bind();
		binded = true;
	}

	void Object::unbind() const
	{
		vertex_buffer.unbind();
		texture.unbind();
		shader.unbind();
		binded = false;
	}

	void Object::draw(Camera* camera, const std::vector<Light*>& lights, DrawType draw_type, bool scene_shader) const
	{
		if (vertex_buffer.get_nb_vertices())
		{
			Window::set_thickness(thickness);

			// Bind

			if (!binded)
			{
				if (!scene_shader)
					shader.bind();

				texture.bind();
				vertex_buffer.bind();
			}

			// Matrices

			shader.send_uniform("u_model", model);
			shader.send_uniform("u_normals_model", glm::transpose(glm::inverse(glm::mat3(model))));

			if (camera != nullptr)
				shader.send_uniform("u_mvp", camera->get_matrix() * model);

			else
				shader.send_uniform("u_mvp", model);

			// Camera

			if (!scene_shader)
			{
				if (camera != nullptr)
					shader.send_uniform("u_camera", camera->get_position());

				else
					shader.send_uniform("u_camera", Vector3(0.f, 0.f, -1.f));
			}

			// Material

			shader.send_uniform("u_material", material);

			// Lights

			if (!scene_shader)
				shader.send_uniform("u_lights", lights);

			// Texture

			if (textured)
			{
				shader.send_uniform("u_texture", texture);
				shader.send_uniform("u_textured", 1);
			}

			else
				shader.send_uniform("u_textured", 0);

			// Draw

			vertex_buffer.draw(draw_type);

			// Unbind

			if (!binded)
			{
				vertex_buffer.unbind();
				texture.unbind();

				if (!scene_shader)
					shader.unbind();
			}
		}
	}
}
