#include "Application.h"

#include "KEngine/Events/ApplicationEvent.h"
#include "KEngine/Log.h"

namespace KEngine {

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent event(1280, 720);
		KE_TRACE(event);

		while (true)
		{

		}
	}

}