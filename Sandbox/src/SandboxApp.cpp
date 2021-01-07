#include<Mimou.h>

class ExampleLayer : public Mimou::Layer {
public:
	ExampleLayer() : Layer("Example") {

	}

	void OnUpdate() override {
		//MM_CLIENT_INFO("ExampleLayer::Update");
		auto [x, y] = Mimou::Input::GetMousePos();
		bool A = Mimou::Input::IsKeyPressed(MM_KEY_A);
		bool ML = Mimou::Input::IsMouseButtonPressed(MM_MOUSE_BUTTON_LEFT);
		//MM_CORE_TRACE("{0}, {1}", x, y);
		if (A) {
			MM_CORE_WARN("A is pressed!!!");
		}
		if (ML) {
			MM_CORE_WARN("Left mouse button is pressed!!!");
		}
	}

	virtual void OnImGuiRender() override {
		//ImGui::Begin("Test");
		//ImGui::Text("Hello World!");
		//ImGui::End();
	}

	void OnEvent(Mimou::Event& event) override {
		//MM_CLIENT_TRACE("{0}", event);
	}
};

class Sandbox : public Mimou::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new Mimou::ImGuiLayer());
	}

	~Sandbox() {

	}
};

Mimou::Application* Mimou::CreateApplication() {
	return new Sandbox();
}