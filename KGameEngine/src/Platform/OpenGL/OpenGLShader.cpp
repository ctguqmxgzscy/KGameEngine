#include "kepch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace KEngine {

	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		//---------------------Vertex Shader------------------
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const GLchar* source = (const GLchar*)vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);
		glCompileShader(vertexShader);
		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(vertexShader);

			KE_CORE_ERROR("{0}", infoLog.data());
			KE_CORE_ASSERT(false, "Vertex shader complicayion failure1");
		}

		//-------------------Fragment Shader------------------
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		source = (const GLchar*)fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(fragmentShader);
			KE_CORE_ERROR("{0}", infoLog.data());
			KE_CORE_ASSERT(false, "Fragment shader complicayion failure1");
		}

		//--------------------Link Program--------------------
		m_ShaderID = glCreateProgram();
		glAttachShader(m_ShaderID, vertexShader);
		glAttachShader(m_ShaderID, fragmentShader);
		glLinkProgram(m_ShaderID);
		GLint isLinked = 0;
		glGetProgramiv(m_ShaderID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_ShaderID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_ShaderID, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(m_ShaderID);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			KE_CORE_ERROR("{0}", infoLog.data());
			KE_CORE_ASSERT(false, "Shader program link failure1");
		}

		glDetachShader(m_ShaderID, vertexShader);
		glDetachShader(m_ShaderID, fragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_ShaderID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_ShaderID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetGlobalInt(const std::string& name, int32_t value) const
	{
		GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::SetGlobalUint(const std::string& name, uint32_t value) const
	{
		GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniform1ui(location, value);
	}

	void OpenGLShader::SetGlobalFloat(const std::string& name, float value) const
	{
		GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::SetGlobalVector2(const std::string& name, const glm::vec2& value) const
	{
		GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::SetGlobalVector3(const std::string& name, const glm::vec3& value) const
	{
		GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::SetGlobalVector4(const std::string& name, const glm::vec4& value) const
	{
		GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetGlobalMat2(const std::string& name, const glm::mat2& value) const
	{
		GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::SetGlobalMat3(const std::string& name, const glm::mat3& value) const
	{
		GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::SetGlobalMat4(const std::string& name, const glm::mat4& value) const
	{
		GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

}