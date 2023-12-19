#include <KEngine/KEngine.h>

class ExampleLayer : public KEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		KE_INFO("ExampleLayer::Update");
	}

	void OnEvent(KEngine::Event& event) override
	{
		KE_TRACE("{0}", event);
	}
};

class Sandbox : public KEngine::Application
{
public :
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushLayer(new KEngine::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

KEngine::Application* KEngine::CreateApplication()
{
	return new Sandbox();
}