#pragma once
#include "Mimou.h"

class Sandbox2D : public Mimou::Layer {
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Mimou::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Mimou::Event& e) override;
private:

	Mimou::Ref<Mimou::VertexArray> m_VertexArray;
	Mimou::Ref<Mimou::Shader> m_Shader;
	Mimou::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};