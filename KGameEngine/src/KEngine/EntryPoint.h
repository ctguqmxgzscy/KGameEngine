#pragma once

#ifdef KE_PLATFORM_WINDOWS

extern KEngine::Application* KEngine::CreateApplication();

int main(int argc, char ** argv)
{
	KEngine::Log::Init();
	KE_CORE_WARN("Initialized Log!");

	int a = 5;
	KE_INFO("Hello World! Value = {0}", a);

	auto app = KEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif // KE_PLATFORM_WINDOWS
