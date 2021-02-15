#include "Sandbox2D.h"
#include <Platform/OpenGL/OpenGLShader.h>

Sandbox2D::Sandbox2D() 
	: Layer("2D Layout"), m_CameraController(1280.0f / 720.0f)
{
	
}

void Sandbox2D::OnAttach()
{
	float vertices[4 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
	};

	uint32_t indices[6] = {
		0, 1, 2, 2, 3, 0
	};
	m_VertexArray = Mimou::VertexArray::Create();
	Mimou::Ref<Mimou::VertexBuffer> vertexBuffer = Mimou::VertexBuffer::Create(vertices, sizeof(vertices));
	Mimou::Ref<Mimou::IndexBuffer> indexBuffer = Mimou::IndexBuffer::Create(indices, sizeof(indices));
	Mimou::BufferLayout layout = {
		{"a_Position", Mimou::ShaderDataType::Float3}
	};
	vertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(vertexBuffer);
	m_VertexArray->AddIndexBuffer(indexBuffer);
	m_Shader = Mimou::Shader::Create("assets/shaders/FlatColorSquare.glsl");


}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Mimou::Timestep ts)
{
	m_CameraController.OnUpdate(ts);
	Mimou::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Mimou::RenderCommand::Clear();

	std::dynamic_pointer_cast<Mimou::OpenGLShader>(m_Shader)->Bind();
	std::dynamic_pointer_cast<Mimou::OpenGLShader>(m_Shader)->UploadUniformFloat3("u_Color", m_SquareColor);

	Mimou::Renderer::BeginScene(m_CameraController.GetCamera());
	Mimou::Renderer::Submit(m_VertexArray, m_Shader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
	Mimou::Renderer::EndScene();

}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("square color");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Mimou::Event& e)
{
	m_CameraController.OnEvent(e);
}
