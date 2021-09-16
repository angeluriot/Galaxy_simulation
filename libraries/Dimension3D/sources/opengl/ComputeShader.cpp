#include "dim/dimension3D.hpp"

namespace dim
{
	void printWorkGroupsCapabilities()
	{
		int workgroup_count[3];
		int workgroup_size[3];
		int workgroup_invocations;

		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &workgroup_count[0]);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &workgroup_count[1]);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &workgroup_count[2]);

		std::cout << "Taille maximale des workgroups : " << workgroup_count[0] << " " << workgroup_count[1] << " " << workgroup_count[2] << std::endl;

		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &workgroup_size[0]);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &workgroup_size[1]);
		glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &workgroup_size[2]);

		std::cout << "Nombre maximal d'invocation locale : " << workgroup_size[0] << " " << workgroup_size[1] << " " << workgroup_size[2] << std::endl;

		glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &workgroup_invocations);

		std::cout << "Nombre maximum d'invocation de workgroups : " << workgroup_invocations << std::endl;
	}

	void compileShader(GLuint shaderID, char* sourcePointer)
	{
		glShaderSource(shaderID, 1, &sourcePointer, NULL);
		glCompileShader(shaderID);

		GLint Result = GL_FALSE;
		int InfoLogLength = 1024;
		char shaderErrorMessage[1024] = { 0 };

		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &Result);

		glGetShaderInfoLog(shaderID, InfoLogLength, NULL, shaderErrorMessage);

		if (strlen(shaderErrorMessage) != 0)
			std::cout << shaderErrorMessage << "\n";
	}

	void loadShader(char ** shaderBuffer, const char* fileName)
	{
		FILE * shader = fopen(fileName, "r");
		(*shaderBuffer) = new char[1280];

		for (int i = 0; i<1280; i++)
		{
			(*shaderBuffer)[i] = (unsigned char)fgetc(shader);

			if ((*shaderBuffer)[i] == EOF)
			{
				(*shaderBuffer)[i] = '\0';
				break;
			}
		}

		fclose(shader);
	}

	ComputeShader::ComputeShader()
	{
		id = std::make_shared<GLuint>(0);
		program_id = std::make_shared<GLuint>(0);
	}

	ComputeShader::ComputeShader(const std::string& path)
	{
		id = std::make_shared<GLuint>(0);
		program_id = std::make_shared<GLuint>(0);
		load(path);
	}

	void ComputeShader::load(const std::string& path)
	{
		//printWorkGroupsCapabilities();

		char* computeShader = 0;

		GLint Result = GL_FALSE;
		int InfoLogLength = 1024;
		char ProgramErrorMessage[1024] = {0};

		*id = glCreateShader(GL_COMPUTE_SHADER);

		loadShader(&computeShader, path.data());
		compileShader(*id, computeShader);

		*program_id = glCreateProgram();

		glAttachShader(*program_id, *id);
		glLinkProgram(*program_id);
		glDeleteShader(*id);
	}

	GLuint ComputeShader::get_id() const
	{
		return *id;
	}

	void ComputeShader::bind() const
	{
		glUseProgram(*program_id);
	}

	void ComputeShader::unbind()
	{
		glUseProgram(0);
	}

	void ComputeShader::launch(unsigned int groups_nb_x, unsigned int groups_nb_y, unsigned int groups_nb_z) const
	{
		glDispatchCompute(groups_nb_x, groups_nb_y, groups_nb_z);
		glMemoryBarrier(GL_ALL_BARRIER_BITS);
	}

	void ComputeShader::send_uniform(unsigned int location, float number) const
	{
		glUniform1f(location, number);
	}

	void ComputeShader::send_uniform(unsigned int location, int number) const
	{
		glUniform1i(location, number);
	}

	void ComputeShader::send_uniform(unsigned int location, const std::vector<float>& numbers, unsigned int group) const
	{
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

	void ComputeShader::send_uniform(unsigned int location, const std::vector<int>& numbers, unsigned int group) const
	{
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

	void ComputeShader::send_uniform(unsigned int location, const Vector2& vector) const
	{
		glUniform2f(location, vector.x, vector.y);
	}

	void ComputeShader::send_uniform(unsigned int location, const Vector3& vector) const
	{
		glUniform3f(location, vector.x, vector.y, vector.z);
	}

	void ComputeShader::send_uniform(unsigned int location, const Vector4& vector) const
	{
		glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
	}

	void ComputeShader::send_uniform(unsigned int location, const Color& color) const
	{
		glUniform4f(location, color.r, color.g, color.b, color.a);
	}

	void ComputeShader::send_uniform(unsigned int location, const std::vector<Vector2>& vectors) const
	{
		glUniform2fv(location, static_cast<GLsizei>(vectors.size()), reinterpret_cast<const float*>(vectors.data()));
	}

	void ComputeShader::send_uniform(unsigned int location, const std::vector<Vector3>& vectors) const
	{
		glUniform3fv(location, static_cast<GLsizei>(vectors.size()), reinterpret_cast<const float*>(vectors.data()));
	}

	void ComputeShader::send_uniform(unsigned int location, const std::vector<Vector4>& vectors) const
	{
		glUniform4fv(location, static_cast<GLsizei>(vectors.size()), reinterpret_cast<const float*>(vectors.data()));
	}

	void ComputeShader::send_uniform(unsigned int location, const std::vector<Color>& colors) const
	{
		glUniform4fv(location, static_cast<GLsizei>(colors.size()), reinterpret_cast<const float*>(colors.data()));
	}

	void ComputeShader::send_uniform(unsigned int location, const glm::mat2& matrix) const
	{
		glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void ComputeShader::send_uniform(unsigned int location, const glm::mat3& matrix) const
	{
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void ComputeShader::send_uniform(unsigned int location, const glm::mat4& matrix) const
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}
