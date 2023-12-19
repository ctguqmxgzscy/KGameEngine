#pragma once

#include "Core.h"

#include "Window.h"
#include "KEngine/LayerStack.h"
#include "KEngine/Events/Event.h"
#include "KEngine/Events/ApplicationEvent.h"

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
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		
		bool m_Running = true;
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
	};

	Application* CreateApplication();
}

