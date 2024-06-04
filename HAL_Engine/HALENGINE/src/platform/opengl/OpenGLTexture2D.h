#pragma once

#include "engine/renderer/Texture.h"

namespace Haleng
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		virtual uint32_t GetWidth() const override { return m_Width; };
		virtual uint32_t GetHeight() const override { return m_Height; };

		virtual void Bind() const override;

		virtual Texture2D* Create(const std::string& path) override;
	private:
		std::string Path;
		uint32_t m_Width;
		uint32_t m_Height;
		uint32_t m_NrChannels;
		uint32_t m_RendererID;
	};
}