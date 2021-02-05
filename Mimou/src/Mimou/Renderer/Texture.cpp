#include "mmpch.h"
#include "Texture.h"

#include <string>
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Mimou {



	Ref<Texture2D> Texture2D::Create(std::string& path)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			MM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
		}
		MM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}