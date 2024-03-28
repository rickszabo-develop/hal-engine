#pragma once

#include "engine/renderer/BufferLayout.h"

namespace Haleng 
{
	class VertexBuffer 
	{
	public:
		virtual ~VertexBuffer();

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

	public:
		static VertexBuffer* Create(float* vertices, uint32_t size);
	private:
	};
}