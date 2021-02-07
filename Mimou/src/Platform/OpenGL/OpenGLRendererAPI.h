#pragma once

#include "Mimou/Renderer/RendererAPI.h"

namespace Mimou {

	class OpenGLRendererAPI : public RendererAPI {
	public:
		virtual void Init() override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Mimou::Ref<VertexArray>& vertexArray) override;
	};

}