#include "kepch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"


namespace KEngine {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}