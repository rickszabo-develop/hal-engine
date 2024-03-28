#pragma once

namespace Haleng {
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const BufferLayout& GetLayout() const override { return m_BufferLayout; }
		virtual void SetLayout(const BufferLayout& layout) override { m_BufferLayout = layout; }

	private:
		uint32_t m_RendererID;
		BufferLayout m_BufferLayout;
	};
}