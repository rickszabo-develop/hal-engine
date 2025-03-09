#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Haleng {
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
	public:
		virtual void SetUniform1i(const std::string& name, int value) = 0;
		virtual void SetUniform1f(const std::string& name, float value) = 0;
		virtual void SetUniformMat4f(const std::string& name, const glm::mat4& matrix) = 0;
		public:
			static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};
}