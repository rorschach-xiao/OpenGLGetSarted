#pragma once

#include <string>
#include "glad/glad.h"
#include "glm/glm.hpp"
namespace common {

	class MyShaderProgram
	{
	private:
		unsigned int shaderProgramId;
		GLint getUniformLocation(const std::string& name) const;
		std::string ReadFile(std::string path);

	public:
		MyShaderProgram();
		~MyShaderProgram();
		bool LoadShader(std::string vertexShaderPath, std::string fragmentShaderPath);
		unsigned int GetShaderId()const;

		virtual void UseProgram() const;
		void SetBool(const std::string& name, bool value) const;
		void SetInt(const std::string& name, int value) const;
		void SetFloat(const std::string& name, float value) const;
		void SetVec3(const std::string& name, float x, float y, float z) const;
        void SetVec4(const std::string& name, float x, float y, float z, float w) const;
        void SetVec3(const std::string& name, glm::vec3 v3) const;
        void SetVec4(const std::string& name, glm::vec4 v4) const;
		void SetMat4(const std::string& name, glm::mat4 matrix);

	};
}
