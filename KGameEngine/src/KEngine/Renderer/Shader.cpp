#include "kepch.h"
#include "Shader.h"

#include <glad/glad.h>

namespace KEngine {

	Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
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
		m_RendererID = glCreateProgram();
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);
		glLinkProgram(m_RendererID);	
		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(m_RendererID);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			
			KE_CORE_ERROR("{0}", infoLog.data());
			KE_CORE_ASSERT(false, "Shader program link failure1");
		}

		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}
}