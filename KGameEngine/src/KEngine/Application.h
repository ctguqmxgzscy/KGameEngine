#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace KEngine {

	class KENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();
}

