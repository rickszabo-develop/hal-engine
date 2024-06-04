#pragma once

namespace Haleng
{
	class Texture
	{
	public:
		
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind() const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		virtual Texture2D* Create(const std::string& path) = 0;
	};
}