#pragma once

#include "KEngine/Renderer/VertexArray.h"

namespace KEngine {

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;


		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() 
			const { return m_VertexBuffers; }
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffers;  }
	private:
		uint32_t m_VertexArrayID;

		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffers;
	};
}


