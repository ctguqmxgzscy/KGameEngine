#include "kepch.h"
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
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			KE_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			KE_TRACE(e);
		}

		while (true)
		{

		}
	}

}