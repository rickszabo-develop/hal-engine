#pragma once

#include "engine/renderer/Texture.h"

namespace Haleng {
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D() override;

		virtual void Bind(uint32_t slot = 0) const override;
	};
}