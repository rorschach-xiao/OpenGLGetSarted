#include <iostream>
#include <fstream>
#include <sstream>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "common/MyShaderProgram.h"

namespace common {

	MyShaderProgram::MyShaderProgram() { shaderProgramId = -1; }

	MyShaderProgram::~MyShaderProgram() { }

	unsigned int MyShaderProgram::GetShaderId() const { return shaderProgramId; }

	bool MyShaderProgram::LoadShader(std::string vertexShaderPath, std::string fragmentShaderPath) {

		// vertex shader
		GLint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
		std::string vertexCodeStr = ReadFile(vertexShaderPath).c_str();
		const char* vertexShaderCode = vertexCodeStr.c_str();

		glShaderSource(vertexShaderId, 1, &vertexShaderCode, NULL);
		glCompileShader(vertexShaderId);

		int success;
		char log[512];
		glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShaderId, 512, NULL, log);
			std::cout << "Error compiling shader " << vertexShaderPath << ":\n\t" << log << std::endl;
			glDeleteShader(vertexShaderId);
			return false;
		}

		// fragment shader
		GLint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
		std::string fragmentCodeStr = ReadFile(fragmentShaderPath).c_str();
		const char* fragmentShaderCode = fragmentCodeStr.c_str();

		glShaderSource(fragmentShaderId, 1, &fragmentShaderCode, NULL);
		glCompileShader(fragmentShaderId);

		glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShaderId, 512, NULL, log);
			std::cout << "Error compiling shader " << fragmentShaderPath << ":\n\t" << log << std::endl;
			glDeleteShader(vertexShaderId);
			glDeleteShader(fragmentShaderId);
			return false;
		}

		// link shaders
		shaderProgramId = glCreateProgram();
		glAttachShader(shaderProgramId, vertexShaderId);
		glAttachShader(shaderProgramId, fragmentShaderId);
		glLinkProgram(shaderProgramId);
		glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderProgramId, 512, NULL, log);
			std::cout << "Error linking shaders\n ";
			glDeleteShader(vertexShaderId);
			glDeleteShader(fragmentShaderId);
			return false;
		}

		glDeleteShader(vertexShaderId);
		glDeleteShader(fragmentShaderId);
		return true;
	}
	void MyShaderProgram::UseProgram() const
	{
		glUseProgram(shaderProgramId);
	}
	void MyShaderProgram::SetBool(const std::string& name, bool value) const
	{
		int location{ getUniformLocation(name) };
		glUniform1i(location, (int)value);
	}
	void MyShaderProgram::SetInt(const std::string& name, int value) const
	{
		int location{ getUniformLocation(name) };
		glUniform1i(location, value);
	}
	void MyShaderProgram::SetFloat(const std::string& name, float value) const
	{
		int location{ getUniformLocation(name) };
		glUniform1f(location, value);
	}
	void MyShaderProgram::SetVec3(const std::string& name, float x, float y, float z) const
	{
		int location{ getUniformLocation(name) };
		glUniform3f(location, x, y, z);
	}
    void MyShaderProgram::SetVec3(const std::string& name, glm::vec3 v3) const
    {
        int location{ getUniformLocation(name) };
        glUniform3f(location, v3[0], v3[1], v3[2]);

    }
    void MyShaderProgram::SetVec4(const std::string& name, float x, float y, float z, float w) const
    {
        int location{ getUniformLocation(name) };
        glUniform4f(location, x, y, z, w);
    }
    void MyShaderProgram::SetVec4(const std::string& name, glm::vec4 v4) const
    {
        int location{ getUniformLocation(name) };
        glUniform4f(location, v4[0], v4[1], v4[2], v4[3]);
    }
	void MyShaderProgram::SetMat4(const std::string& name, glm::mat4 matrix)
	{
		int location{ getUniformLocation(name) };
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	GLint MyShaderProgram::getUniformLocation(const std::string& name) const
	{
		int location{ glGetUniformLocation(shaderProgramId, name.c_str()) };
		if (location == -1)
		{
			printf("ShaderProgram: Cannot locate location for uniform variable: [%s]\nIf the variable does exist in the shader, this could also happen if the variable is not used and stripped out by the compiler.\n", name.c_str());
		}
		return location;
	}
	std::string MyShaderProgram::ReadFile(std::string path)
	{
		std::ifstream fin;
		fin.open(path);
		if (!fin.is_open())
		{
			printf("Invalid file path: %s\n", path.c_str());
			abort();
		}
		std::stringstream strstream;
		strstream << fin.rdbuf();
		fin.close();
		return strstream.str();
	}
}
