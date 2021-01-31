#include "mmpch.h"
#include "Renderer.h"

namespace Mimou {

	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	// make sure that the shader we are using get the right uniforms
	// : which environment we are using, the camera, the projection matrix
	// the view matrix, where the camera in the world space, any calculation
	// for lighting...
	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}