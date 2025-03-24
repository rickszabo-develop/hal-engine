#pragma once

#include "engine/Renderer/Shader.h"
#include <string>
#include <glm/ext/matrix_float4x4.hpp>

namespace Haleng {
	class OpenGLShader: public Shader
	{
	public:
		OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath);
		~OpenGLShader();

		virtual void Bind() override;
		virtual void Unbind() override;

		void SetUniform1i(const std::string& name, int value) override;
		void SetUniform1f(const std::string& name, float value) override;
		void SetUniformMat4f(const std::string& name, const glm::mat4& matrix) override;

	private:
		void Compile(const std::string& vertexSrc, const std::string& fragmentSrc);

	private:
		uint32_t m_RendererID;
	};
}