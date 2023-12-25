#include "kepch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace KEngine {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case KEngine::ShaderDataType::Float:	return GL_FLOAT;
			case KEngine::ShaderDataType::Float2:	return GL_FLOAT;
			case KEngine::ShaderDataType::Float3:	return GL_FLOAT;
			case KEngine::ShaderDataType::Float4:	return GL_FLOAT;
			case KEngine::ShaderDataType::Mat3:		return GL_FLOAT;
			case KEngine::ShaderDataType::Mat4:		return GL_FLOAT;
			case KEngine::ShaderDataType::Int:		return GL_INT;
			case KEngine::ShaderDataType::Int2:		return GL_INT;
			case KEngine::ShaderDataType::Int3:		return GL_INT;
			case KEngine::ShaderDataType::Int4:		return GL_INT;
			case KEngine::ShaderDataType::Bool:		return GL_BOOL;
		}
		KE_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}


	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_VertexArrayID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_VertexArrayID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_VertexArrayID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		KE_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_VertexArrayID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index, element.GetElementCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset
			);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_VertexArrayID);
		indexBuffer->Bind();

		m_IndexBuffers = indexBuffer;
	}
}