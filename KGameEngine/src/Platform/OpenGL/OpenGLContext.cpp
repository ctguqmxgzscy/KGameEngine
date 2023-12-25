#include "kepch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace KEngine
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		KE_CORE_ASSERT(m_WindowHandle, "windowHandle is nullptr!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		KE_CORE_ASSERT(status, "Failed to intialize Glad!");

		KE_CORE_INFO("OpenGL Info:");
		KE_CORE_INFO("	Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		KE_CORE_INFO("	Renderer : {0}", (const char*)glGetString(GL_RENDERER));
		KE_CORE_INFO("	Viersion : {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}