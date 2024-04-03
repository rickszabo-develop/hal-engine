#include "halpch.h"

#include "engine/renderer/BufferLayout.h"
#include "engine/renderer/VertexArray.h"
#include "platform/opengl/ShaderDataTypeToOpenGLBaseType.h"

#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Haleng
{
    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_RendererID);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
    {
        HALENG_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layouts!");

        glBindVertexArray(m_RendererID);

        vertexBuffer->Bind();

        uint32_t index = 0;
        const auto& layout = vertexBuffer->GetLayout();

        for (const auto& element : layout)
        {
            glVertexAttribPointer(index,
                element.GetComponentCount(),
                ShaderDataTypeToOpenGLBaseType(element.Type),
                element.Normalized,
                layout.GetStride(),
                (const void*)element.Offset
            );
            glEnableVertexAttribArray(index);
            index++;
        }

        m_VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;
    }
}
