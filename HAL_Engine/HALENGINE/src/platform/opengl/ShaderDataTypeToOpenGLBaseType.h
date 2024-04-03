#pragma once
#include <engine/renderer/BufferLayout.h>
#include <glad/glad.h>
#include <engine/Core.h>

namespace Haleng 
{
	static GLenum ShaderDataTypeToOpenGLBaseType(Haleng::ShaderDataType type)
	{
		switch (type)
		{
			case Haleng::ShaderDataType::None:
			case Haleng::ShaderDataType::Float:		return GL_FLOAT;
			case Haleng::ShaderDataType::Float2:	return GL_FLOAT;
			case Haleng::ShaderDataType::Float3:	return GL_FLOAT;
			case Haleng::ShaderDataType::Float4:	return GL_FLOAT;
			case Haleng::ShaderDataType::Mat3:		return GL_FLOAT;
			case Haleng::ShaderDataType::Mat4:		return GL_FLOAT;
			case Haleng::ShaderDataType::Int:		return GL_INT;
			case Haleng::ShaderDataType::Int2:		return GL_INT;
			case Haleng::ShaderDataType::Int3:		return GL_INT;
			case Haleng::ShaderDataType::Int4:		return GL_INT;
			case Haleng::ShaderDataType::Bool:		return GL_BOOL;
		}

		HALENG_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
}