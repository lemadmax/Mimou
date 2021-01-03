#include<Mimou.h>

class ExampleLayer : public Mimou::Layer {
public:
	ExampleLayer() : Layer("Example") {

	}

	void OnUpdate() override {
		MM_CLIENT_INFO("ExampleLayer::Update");
	}

	void OnEvent(Mimou::Event& event) override {
		MM_CLIENT_TRACE("{0}", event);
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