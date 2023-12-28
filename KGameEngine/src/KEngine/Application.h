#pragma once

#include "Core.h"

#include "Window.h"
#include "KEngine/LayerStack.h"
#include "KEngine/Events/Event.h"
#include "KEngine/Events/ApplicationEvent.h"

#include "KEngine/ImGui/ImGuiLayer.h"
#include "KEngine/Core/Timestep.h"

namespace KEngine {

	class KENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		
	private:

		bool m_Running = true;
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
		Timestep m_Timestep;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();
}

