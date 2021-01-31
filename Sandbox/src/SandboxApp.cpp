#include<Mimou.h>

#include <iostream>
#include<memory>
#include<utility>
#include<algorithm>
#include<functional>

#include<string>
#include<sstream>
#include<vector>
#include<unordered_map>
#include<unordered_set>

#include "imgui.h"

class ExampleLayer : public Mimou::Layer {

private:
	// different with shared_ptr, unique_ptr only allow
		// one pointer points to an object
	std::shared_ptr<Mimou::Shader> m_Shader;
	std::shared_ptr<Mimou::VertexArray> m_VertexArray;

	std::shared_ptr<Mimou::Shader> square_Shader;
	std::shared_ptr<Mimou::VertexArray> square_VertexArray;

	Mimou::OrthographicCamera m_Camera;

public:
	ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) {

		// Create and bind vertics and indics
		// Vertex Array
		m_VertexArray.reset(Mimou::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f
		};
		// Vertex Buffer
		std::shared_ptr<Mimou::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Mimou::VertexBuffer::Create(vertices, sizeof(vertices)));
		Mimou::BufferLayout layout = {
			{ "a_Posistion", Mimou::ShaderDataType::Float3 },
			{ "a_Color", Mimou::ShaderDataType::Float4 }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		// Index Buffer
		uint32_t indices[3] = {
			0, 1, 2
		};
		std::shared_ptr<Mimou::IndexBuffer> indexBuffer;
		indexBuffer.reset(Mimou::IndexBuffer::Create(indices, 3));
		m_VertexArray->AddIndexBuffer(indexBuffer);
		// Shader (vertex shader, fragment shader)
		// define shaders
		// R"()" make it easier to write multiple lines
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec4 v_Color;

			void main()
			{
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}

		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Color);
			}

		)";

		m_Shader.reset(new Mimou::Shader(vertexSrc, fragmentSrc));

		float Svertices[4 * 3] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		uint32_t Sindices[6] = {
			0, 1, 2, 2, 3, 0
		};

		square_VertexArray.reset(Mimou::VertexArray::Create());
		std::shared_ptr<Mimou::VertexBuffer> squareBuffer;
		std::shared_ptr<Mimou::IndexBuffer> squareIndexB;
		squareBuffer.reset(Mimou::VertexBuffer::Create(Svertices, sizeof(Svertices)));
		squareIndexB.reset(Mimou::IndexBuffer::Create(Sindices, sizeof(Sindices) / sizeof(uint32_t)));
		Mimou::BufferLayout Slayout = {
			{"a_Position", Mimou::ShaderDataType::Float3}
		};
		squareBuffer->SetLayout(Slayout);
		square_VertexArray->AddVertexBuffer(squareBuffer);
		square_VertexArray->AddIndexBuffer(squareIndexB);

		std::string SvertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			
			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}

		)";

		std::string SfragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			
			in vec3 v_Position;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}

		)";
		square_Shader.reset(new Mimou::Shader(SvertexSrc, SfragmentSrc));

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

		Mimou::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Mimou::RenderCommand::Clear();

		Mimou::Renderer::BeginScene(m_Camera);

		Mimou::Renderer::Submit(square_VertexArray, square_Shader);
		Mimou::Renderer::Submit(m_VertexArray, m_Shader);

		Mimou::Renderer::EndScene();

	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Test");
		ImGui::Text("Hello World!");
		ImGui::End();
	}

	void OnEvent(Mimou::Event& event) override {
		Mimou::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Mimou::KeyPressedEvent>(MM_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	}

	bool OnKeyPressedEvent(Mimou::KeyPressedEvent& event) {
		int key = event.GetKeyCode();
		switch(key) {
		case MM_KEY_E:
			m_Camera.SetRotation(m_Camera.GetRotation() + 0.1f);
			MM_CORE_INFO("Key e is pressed");
			break;
		case MM_KEY_Q:
			m_Camera.SetRotation(m_Camera.GetRotation() - 0.1f);
			break;
		case MM_KEY_A:
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3({0.1, 0, 0}));
			break;
		case MM_KEY_D:
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3({-0.1, 0, 0}));
			break;
		case MM_KEY_W:
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3({0, 0.1, 0}));
			break;
		case MM_KEY_S:
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3({0, -0.1, 0}));
			break;
		case MM_KEY_Z:
			m_Camera.SetPosition(m_Camera.GetPosition() + glm::vec3({ 0, 0, -0.1}));
			break;
		}

		return true;
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

// global variables initialized before the main function
Mimou::Application* Mimou::CreateApplication() {
	return new Sandbox();
}
