#pragma once

#include <string>
#include <glm/glm.hpp>

namespace KEngine {

	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetGlobalInt(const std::string& name, int32_t value) const = 0;
		virtual void SetGlobalUint(const std::string& name, uint32_t value) const = 0;
		virtual void SetGlobalFloat(const std::string& name, float value) const = 0;

		virtual void SetGlobalVector2(const std::string& name, const glm::vec2& value) const = 0;
		virtual void SetGlobalVector3(const std::string& name, const glm::vec3& value) const = 0;
		virtual void SetGlobalVector4(const std::string& name, const glm::vec4& value) const = 0;

		virtual void SetGlobalMat2(const std::string& name, const glm::mat2& value) const = 0;
		virtual void SetGlobalMat3(const std::string& name, const glm::mat3& value) const = 0;
		virtual void SetGlobalMat4(const std::string& name, const glm::mat4& value) const = 0;

		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};
}