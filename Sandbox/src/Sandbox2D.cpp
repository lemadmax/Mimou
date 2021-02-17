#include "Sandbox2D.h"


Sandbox2D::Sandbox2D() 
	: Layer("2D Layout"), m_CameraController(1280.0f / 720.0f)
{
	
}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = Mimou::Texture2D::Create(std::string("assets/textures/Checkerboard.png"));
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Mimou::Timestep ts)
{
	m_CameraController.OnUpdate(ts);
	Mimou::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Mimou::RenderCommand::Clear();

	

	Mimou::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Mimou::Renderer2D::DrawQuad({ -1.0f, 0.2f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Mimou::Renderer2D::DrawQuad({ 1.0f, 0.2f }, { 1.0f, 0.6f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	Mimou::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
	Mimou::Renderer2D::EndScene();

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
