#include <KEngine/KEngine.h>

#include "imgui.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public KEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f),
		m_SquarePosition(0.0f), m_SquareColor(0.0f)
	{
		m_VertexArray.reset(KEngine::VertexArray::Create());

		float vertices[3 * 7] =
		{
			-0.5f,	-0.5f,	+0.0f,	0.8f,	0.2f,	0.8f,	1.0f,
			+0.5f,	-0.5f,	+0.0f,	0.2f,	0.3f,	0.8f,	1.0f,
			+0.0f,	+0.5f,	+0.0f,	0.8f,	0.8f,	0.2f,	1.0f,
		};

		std::shared_ptr<KEngine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(KEngine::VertexBuffer::Create(vertices, sizeof(vertices)));
		KEngine::BufferLayout layout = {
			{KEngine::ShaderDataType::Float3, "a_Position"},
			{KEngine::ShaderDataType::Float4, "a_Color"},
		};
		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		std::shared_ptr<KEngine::IndexBuffer> indexBuffer;
		indexBuffer.reset(KEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->AddIndexBuffer(indexBuffer);

		m_SquareVA.reset(KEngine::VertexArray::Create());
		float squareVertices[3 * 4] =
		{
			-0.5f,	-0.5f,	+0.0f,
			+0.5f,	-0.5f,	+0.0f,
			+0.5f,	+0.5f,	+0.0f,
			-0.5f,	+0.5f,	+0.0f,
		};
		std::shared_ptr<KEngine::VertexBuffer> squareVB;
		squareVB.reset(KEngine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout(
			{
				{KEngine::ShaderDataType::Float3, "a_Position"},
			}
		);

		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<KEngine::IndexBuffer> squareIB;
		squareIB.reset(KEngine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->AddIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;			

			uniform mat4 u_ViewProjection;			
			uniform mat4 u_Transform;
 
			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(KEngine::Shader::Create(vertexSrc, fragmentSrc));

		std::string bludeShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;		

			uniform mat4 u_ViewProjection;	
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string bludeShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			uniform vec3 u_Color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_BlueShader.reset(KEngine::Shader::Create(bludeShaderVertexSrc, bludeShaderFragmentSrc));
	}

	void OnUpdate(KEngine::Timestep timestep) override
	{

		if (KEngine::Input::IsKeyPressed(KE_KEY_LEFT))
		{
			m_SquarePosition.x -= m_CameraMoveSpeed * timestep;
		}
		else if (KEngine::Input::IsKeyPressed(KE_KEY_RIGHT))
		{
			m_SquarePosition.x += m_CameraMoveSpeed * timestep;
		}
		if (KEngine::Input::IsKeyPressed(KE_KEY_UP))
		{
			m_SquarePosition.y += m_CameraMoveSpeed * timestep;
		}
		else if (KEngine::Input::IsKeyPressed(KE_KEY_DOWN))
		{
			m_SquarePosition.y -= m_CameraMoveSpeed * timestep;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.f), m_SquarePosition);

		KEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		KEngine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);

		//Renderer::BeginSecen(camera, lights,enviroment);
		KEngine::Renderer::BeginScene(m_Camera);
		m_BlueShader->Bind();
		m_BlueShader->SetGlobalVector3("u_Color", m_SquareColor);
		KEngine::Renderer::Submit(m_BlueShader, m_SquareVA, transform);

		KEngine::Renderer::Submit(m_Shader, m_VertexArray);
		KEngine::Renderer::EndScene();

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(KEngine::Event& event) override
	{
		KEngine::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<KEngine::KeyPressedEvent>(KE_BIND_EVENT_FUNC(ExampleLayer::OnKeyPressedEvent));
	}

	bool OnKeyPressedEvent(KEngine::KeyPressedEvent& event)
	{
		return false;
	}

private:
	std::shared_ptr<KEngine::Shader> m_Shader;
	std::shared_ptr<KEngine::VertexArray> m_VertexArray;

	std::shared_ptr<KEngine::Shader> m_BlueShader;
	std::shared_ptr<KEngine::VertexArray> m_SquareVA;

	KEngine::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition;
	glm::vec3 m_SquarePosition;
	glm::vec3 m_SquareColor;

	float m_CameraMoveSpeed = 1.0f;
	float m_CameraRotationSpeed = 30.0f;
	float m_CameraRotation = 0.0f;
};

class Sandbox : public KEngine::Application
{
public :
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

KEngine::Application* KEngine::CreateApplication()
{
	return new Sandbox();
}