#include "mmpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Mimou {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

}