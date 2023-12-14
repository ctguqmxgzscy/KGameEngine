#pragma once

#ifdef KE_PLATFORM_WINDOWS

extern KEngine::Application* KEngine::CreateApplication();

int main(int argc, char ** argv)
{
	auto app = KEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif // KE_PLATFORM_WINDOWS
