#include "mmpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Mimou {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type) {
		case Mimou::ShaderDataType::Float:		return GL_FLOAT;
		case Mimou::ShaderDataType::Float2:		return GL_FLOAT;
		case Mimou::ShaderDataType::Float3:		return GL_FLOAT;
		case Mimou::ShaderDataType::Float4:		return GL_FLOAT;
		case Mimou::ShaderDataType::Mat3:		return GL_FLOAT;
		case Mimou::ShaderDataType::Mat4:		return GL_FLOAT;
		case Mimou::ShaderDataType::Int:		return GL_INT;
		case Mimou::ShaderDataType::Int2:		return GL_INT;
		case Mimou::ShaderDataType::Int3:		return GL_INT;
		case Mimou::ShaderDataType::Int4:		return GL_INT;
		case Mimou::ShaderDataType::Bool:		return GL_BOOL;
		}
		MM_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

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

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		MM_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout");
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();
		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::AddIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}

}