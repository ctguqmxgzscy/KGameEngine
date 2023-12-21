#include <KEngine/KEngine.h>

#include "imgui.h"

class ExampleLayer : public KEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{

		if (KEngine::Input::IsKeyPressed(KE_KEY_TAB))
			KE_TRACE("Tab key is pressed (poll)!");
	}

	void OnEvent(KEngine::Event& event) override
	{
		if (event.GetEventType() == KEngine::EventType::KeyPressed)
		{
			KEngine::KeyPressedEvent& e = (KEngine::KeyPressedEvent&)event;
			if (e.GetKeyCode() == KE_KEY_TAB)
				KE_TRACE("Tab key is pressed (event)!");
			KE_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World!");
		ImGui::ColorEdit4("", new float[4]);
		ImGui::End();
	}
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