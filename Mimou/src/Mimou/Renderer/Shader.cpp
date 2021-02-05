#include "mmpch.h"
#include "Shader.h"
#include "Mimou/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Mimou {

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			MM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexSrc, fragmentSrc);
		}
		MM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}