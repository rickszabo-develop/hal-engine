#pragma once

#include <string>

namespace Haleng {
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual void Bind(uint32_t slot = 0) const = 0;
	protected:
		uint32_t m_RendererID;
	};

	class Texture2D : public Texture
	{
	public:
		virtual ~Texture2D() = default;

		virtual void Bind(uint32_t slot = 0) const = 0;

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }
	public:
		static Texture2D* Create(const std::string& path);
	protected:
		uint32_t m_Width, m_Height;
	};
}
