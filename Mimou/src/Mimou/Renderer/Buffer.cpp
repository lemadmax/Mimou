#include "mmpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Mimou {



	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None: 
			MM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}
		MM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::API::None:
			MM_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLIndexBuffer>(indices, size);
		}
		MM_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}