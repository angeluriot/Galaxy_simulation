#include "dim/dimension3D.hpp"

namespace dim
{
	std::map<std::string, Shader> Shader::shaders = {};
	Shader Shader::default_shader;

	Shader::Shader() {}

	Shader::Shader(const std::string& vert_path, const std::string& frag_path)
	{
		shader = std::make_shared<sf::Shader>();
		load(vert_path, frag_path);
	}

	void Shader::init()
	{
		default_shader.shader = std::make_shared<sf::Shader>();

		default_shader.shader->loadFromMemory(
			"#version 430\n"
			"precision mediump float;\n"
			"\n"
			"in vec3 a_position;\n"
			"in vec3 a_normal;\n"
			"in vec2 a_texcoord;\n"
			"\n"
			"out vec3 v_position;\n"
			"out vec3 v_normal;\n"
			"out vec2 v_texcoord;\n"
			"\n"
			"uniform mat4 u_model;\n"
			"uniform mat3 u_normals_model;\n"
			"uniform mat4 u_mvp;\n"
			"\n"
			"void main()\n"
			"{\n"
			"	v_position = vec3(u_model * vec4(a_position, 1.));\n"
			"	v_normal = normalize(u_normals_model * a_normal);\n"
			"	v_texcoord = a_texcoord;\n"
			"\n"
			"	gl_Position = u_mvp * vec4(a_position, 1.);\n"
			"}\n",

			"#version 430\n"
			"precision mediump float;\n"
			"\n"
			"#define MAX_LIGHTS 10\n"
			"\n"
			"struct Material\n"
			"{\n"
			"	vec4 color;\n"
			"	float ambient;\n"
			"	float diffuse;\n"
			"	float specular;\n"
			"	float shininess;\n"
			"	int illuminated;\n"
			"};\n"
			"\n"
			"struct Light\n"
			"{\n"
			"	int type;\n"
			"	vec3 vector;\n"
			"	vec4 color;\n"
			"	float intensity;\n"
			"};\n"
			"\n"
			"in vec3 v_position;\n"
			"in vec3 v_normal;\n"
			"in vec2 v_texcoord;\n"
			"\n"
			"out vec4 frag_color;\n"
			"\n"
			"uniform vec3 u_camera;\n"
			"uniform Material u_material;\n"
			"uniform Light[MAX_LIGHTS] u_lights;\n"
			"uniform int u_nb_lights;\n"
			"uniform sampler2D u_texture;\n"
			"uniform int u_textured;\n"
			"\n"
			"void main()\n"
			"{\n"
			"	vec4 initial_color = (1 - u_textured) * u_material.color + u_textured * texture2D(u_texture, v_texcoord);\n"
			"\n"
			"	if (u_material.illuminated == 1)\n"
			"	{\n"
			"		vec3 ambient_color = vec3(0., 0., 0.);\n"
			"		vec3 diffuse_color = vec3(0., 0., 0.);\n"
			"		vec3 specular_color = vec3(0., 0., 0.);\n"
			"		vec3 reflection = vec3(0., 0., 0.);\n"
			"		vec3 camera_direction = vec3(0., 0., 0.);\n"
			"		vec3 light_direction = vec3(0., 0., 0.);\n"
			"		float intensity = 0 ;\n"
			"\n"
			"		for (int i = 0; i < u_nb_lights; i++)\n"
			"		{\n"
			"			light_direction = u_lights[i].vector;\n"
			"			intensity = u_lights[i].intensity;\n"
			"\n"
			"			if (u_lights[i].type == 2)\n"
			"			{\n"
			"				light_direction = normalize(v_position - u_lights[i].vector);\n"
			"				intensity = u_lights[i].intensity / pow(distance(v_position, u_lights[i].vector), 2);\n"
			"			}\n"
			"\n"
			"			// Ambiant\n"
			"			ambient_color += initial_color.rgb * u_material.ambient * intensity;\n"
			"\n"
			"			if (u_lights[i].type != 0)\n"
			"			{\n"
			"				// Diffuse\n"
			"				diffuse_color += initial_color.rgb * u_material.diffuse * max(0., dot(v_normal, -light_direction)) * u_lights[i].color.rgb * intensity;\n"
			"\n"
			"				// Specular\n"
			"				reflection = reflect(light_direction, v_normal);\n"
			"				camera_direction = normalize(u_camera - v_position);\n"
			"				specular_color += u_material.specular * pow(max(0., dot(reflection, camera_direction)), u_material.shininess) * u_lights[i].color.rgb * intensity;\n"
			"			}\n"
			"		}\n"
			"\n"
			"		frag_color = vec4(ambient_color + diffuse_color + specular_color, initial_color.a);\n"
			"	}\n"
			"\n"
			"	else\n"
			"		frag_color = initial_color;\n"
			"}\n");
	}

	void Shader::load(const std::string& vert_path, const std::string& frag_path)
	{
		shader = std::make_shared<sf::Shader>();

		if (!shader->loadFromFile(vert_path, frag_path))
			throw std::runtime_error("The shader " + vert_path + " or " + frag_path + " could not be loaded");
	}

	GLuint Shader::get_id() const
	{
		return shader->getNativeHandle();
	}

	void Shader::bind() const
	{
		glUseProgram(get_id());
	}

	void Shader::unbind()
	{
		glUseProgram(0);
	}

	void Shader::send_uniform(const std::string& name, const Texture& texture) const
	{
		GLint location = glGetUniformLocation(get_id(), name.data());
		glUniform1i(location, texture.get_unit());
	}

	void Shader::send_uniform(const std::string& name, const Light& light) const
	{
		send_uniform(name + ".type", (int)light.get_type());
		send_uniform(name + ".vector", light.vector);
		send_uniform(name + ".color", light.color);
		send_uniform(name + ".intensity", light.intensity);
	}

	void Shader::send_uniform(const std::string& name, const std::vector<Light*>& lights) const
	{
		for (unsigned int i = 0; i < lights.size() && i < max_lights; i++)
		{
			send_uniform(name + "[" + std::to_string(i) + "].type", static_cast<int>(lights[i]->get_type()));
			send_uniform(name + "[" + std::to_string(i) + "].vector", lights[i]->vector);
			send_uniform(name + "[" + std::to_string(i) + "].color", lights[i]->color);
			send_uniform(name + "[" + std::to_string(i) + "].intensity", lights[i]->intensity);
		}

		send_uniform("u_nb_lights", std::min(static_cast<int>(lights.size()), static_cast<int>(max_lights)));
	}

	void Shader::send_uniform(const std::string& name, const Material& material) const
	{
		send_uniform(name + ".color", material.get_color());
		send_uniform(name + ".ambient", material.get_ambient());
		send_uniform(name + ".diffuse", material.get_diffuse());
		send_uniform(name + ".specular", material.get_specular());
		send_uniform(name + ".shininess", material.get_shininess());
		send_uniform(name + ".illuminated", material.is_illuminated());
	}

	void Shader::send_uniform(const std::string& name, float number) const
	{
		GLint location = glGetUniformLocation(get_id(), name.data());
		glUniform1f(location, number);
	}

	void Shader::send_uniform(const std::string& name, int number) const
	{
		GLint location = glGetUniformLocation(get_id(), name.data());
		glUniform1i(location, number);
	}

	void Shader::send_uniform(const std::string& name, const std::vector<float>& numbers, unsigned int group) const
	{
		GLint location = glGetUniformLocation(get_id(), name.data());

		if (group == 1)
			glUniform1fv(location, static_cast<GLsizei>(numbers.size()), numbers.data());

		else if (group == 2)
			glUniform2fv(location, static_cast<GLsizei>(numbers.size() / 2), numbers.data());

		else if (group == 3)
			glUniform3fv(location, static_cast<GLsizei>(numbers.size() / 3), numbers.data());

		else if (group == 4)
			glUniform4fv(location, static_cast<GLsizei>(numbers.size() / 4), numbers.data());

		else
			throw std::invalid_argument("Invalid group (<1 or >4)");
	}

	void Shader::send_uniform(const std::string& name, const std::vector<int>& numbers, unsigned int group) const
	{
		GLint location = glGetUniformLocation(get_id(), name.data());

		if (group == 1)
			glUniform1iv(location, static_cast<GLsizei>(numbers.size()), numbers.data());

		else if (group == 2)
			glUniform2iv(location, static_cast<GLsizei>(numbers.size() / 2), numbers.data());

		else if (group == 3)
			glUniform3iv(location, static_cast<GLsizei>(numbers.size() / 3), numbers.data());

		else if (group == 4)
			glUniform4iv(location, static_cast<GLsizei>(numbers.size() / 4), numbers.data());

		else
			throw std::invalid_argument("Invalid group (<1 or >4)");
	}

	void Shader::send_uniform(const std::string& name, const Vector2& vector) const
	{
		GLint location = glGetUniformLocation(get_id(), name.data());
		glUniform2f(location, vector.x, vector.y);
	}

	void Shader::send_uniform(const std::string& name, const Vector3& vector) const
	{
		GLint location = glGetUniformLocation(get_id(), name.data());
		glUniform3f(location, vector.x, vector.y, vector.z);
	}

	void Shader::send_uniform(const std::string& name, const Vector4& vector) const
	{
		GLint location = glGetUniformLocation(get_id(), name.data());
		glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::send_uniform(const std::string& name, const Color& color) const
	{
		GLint location = glGetUniformLocation(get_id(), name.data());
		glUniform4f(location, color.r, color.g, color.b, color.a);
	}

	void Shader::send_uniform(const std::string& name, const std::vector<Vector2>& vectors) const
	{
		GLint location = glGetUniformLocation(get_id(), name.data());
		glUniform2fv(location, static_cast<GLsizei>(vectors.size()), reinterpret_cast<const float*>(vectors.data()));
	}

	void Shader::send_uniform(const std::string& name, const std::vector<Vector3>& vectors) const
	{
		GLint location = glGetUniformLocation(get_id(), name.data());
		glUniform3fv(location, static_cast<GLsizei>(vectors.size()), reinterpret_cast<const float*>(vectors.data()));
	}

	void Shader::send_uniform(const std::string& name, const std::vector<Vector4>& vectors) const
	{
		GLint location = glGetUniformLocation(get_id(), name.data());
		glUniform4fv(location, static_cast<GLsizei>(vectors.size()), reinterpret_cast<const float*>(vectors.data()));
	}

	void Shader::send_uniform(const std::string& name, const std::vector<Color>& colors) const
	{
		GLint location = glGetUniformLocation(get_id(), name.data());
		glUniform4fv(location, static_cast<GLsizei>(colors.size()), reinterpret_cast<const float*>(colors.data()));
	}

	void Shader::send_uniform(const std::string& name, const glm::mat2& matrix) const
	{
		GLint location = glGetUniformLocation(get_id(), name.data());
		glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::send_uniform(const std::string& name, const glm::mat3& matrix) const
	{
		GLint location = glGetUniformLocation(get_id(), name.data());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::send_uniform(const std::string& name, const glm::mat4& matrix) const
	{
		GLint location = glGetUniformLocation(get_id(), name.data());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::add(const std::string& name, const Shader& shader)
	{
		if (!shaders.insert(std::make_pair(name, shader)).second)
			throw std::invalid_argument("This name is already used");
	}

	void Shader::add(const std::string& name, const std::string& vert_path, const std::string& frag_path)
	{
		if (!shaders.insert(std::make_pair(name, Shader(vert_path, frag_path))).second)
			throw std::invalid_argument("This name is already used");
	}

	void Shader::remove(const std::string& name)
	{
		if (!shaders.erase(name))
			throw std::invalid_argument("This name does not exit");
	}

	Shader Shader::get(const std::string& name)
	{
		try
		{
			return shaders.at(name);
		}

		catch (const std::out_of_range&)
		{
			throw std::invalid_argument("This name does not exit");
		}
	}
}
