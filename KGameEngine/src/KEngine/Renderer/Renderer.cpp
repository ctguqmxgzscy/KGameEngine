#include "kepch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace KEngine {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, 
		const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		shader->SetGlobalMat4("u_Transform", transform);
		shader->SetGlobalMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}