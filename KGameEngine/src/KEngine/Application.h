#pragma once

#include "Core.h"

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

