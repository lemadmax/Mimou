
#include "mmpch.h"
#include "VertexArray.h"

#include "mmpch.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Mimou {



	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			MM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexArray();
		}
		MM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}