#pragma once

#include "KEngine/Renderer/Shader.h"

namespace KEngine {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetGlobalInt(const std::string& name, int32_t value) const override;
		virtual void SetGlobalUint(const std::string& name, uint32_t value) const override;
		virtual void SetGlobalFloat(const std::string& name, float value) const override;

		virtual void SetGlobalVector2(const std::string& name, const glm::vec2& value) const override;
		virtual void SetGlobalVector3(const std::string& name, const glm::vec3& value) const override;
		virtual void SetGlobalVector4(const std::string& name, const glm::vec4& value) const override;

		virtual void SetGlobalMat2(const std::string& name, const glm::mat2& value) const override;
		virtual void SetGlobalMat3(const std::string& name, const glm::mat3& value) const override;
		virtual void SetGlobalMat4(const std::string& name, const glm::mat4& value) const override;

	private:
		uint32_t m_ShaderID;
	};
}