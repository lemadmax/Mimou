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

#include "Mimou/Core/EntryPoint.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "imgui.h"
#include <Platform/OpenGL/OpenGLShader.h>
#include "Sandbox2D.h"

class ExampleLayer : public Mimou::Layer {

public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f/720.0f), 
		m_SquarePosition(glm::vec3(0.0f)),
		m_SquareColor(glm::vec3(1.0f))
	{

		// Create and bind vertics and indics
		// Vertex Array
		m_VertexArray = Mimou::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f
		};
		// Vertex Buffer
		Mimou::Ref<Mimou::VertexBuffer> vertexBuffer;
		vertexBuffer = Mimou::VertexBuffer::Create(vertices, sizeof(vertices));
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
		Mimou::Ref<Mimou::IndexBuffer> indexBuffer;
		indexBuffer = Mimou::IndexBuffer::Create(indices, 3);
		m_VertexArray->AddIndexBuffer(indexBuffer);
		// Shader (vertex shader, fragment shader)
		// define shaders
		// R"()" make it easier to write multiple lines
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec4 v_Color;

			void main()
			{
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

		m_Shader = Mimou::Shader::Create("TriangleShader", vertexSrc, fragmentSrc);


		float Svertices[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		uint32_t Sindices[6] = {
			0, 1, 2, 2, 3, 0
		};

		square_VertexArray = Mimou::VertexArray::Create();
		Mimou::Ref<Mimou::VertexBuffer> squareBuffer;
		Mimou::Ref<Mimou::IndexBuffer> squareIndexB;
		squareBuffer = Mimou::VertexBuffer::Create(Svertices, sizeof(Svertices));
		squareIndexB = Mimou::IndexBuffer::Create(Sindices, sizeof(Sindices) / sizeof(uint32_t));
		Mimou::BufferLayout Slayout = {
			{"a_Position", Mimou::ShaderDataType::Float3},
			{"a_TextCoord", Mimou::ShaderDataType::Float2}
		};
		squareBuffer->SetLayout(Slayout);
		square_VertexArray->AddVertexBuffer(squareBuffer);
		square_VertexArray->AddIndexBuffer(squareIndexB);

		std::string SvertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			
			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}

		)";

		std::string SfragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			uniform vec3 u_Color;
			
			in vec3 v_Position;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}

		)";
		square_Shader = Mimou::Shader::Create("SquareShader", SvertexSrc, SfragmentSrc);

		auto texture_Shader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Mimou::Texture2D::Create(std::string("assets/textures/Checkerboard.png"));
		m_LogoTexture = Mimou::Texture2D::Create(std::string("assets/textures/ChernoLogo.png"));

		std::dynamic_pointer_cast<Mimou::OpenGLShader>(texture_Shader)->Bind();
		// 0 indicates slot 0.
		std::dynamic_pointer_cast<Mimou::OpenGLShader>(texture_Shader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Mimou::Timestep ts) override {
		////MM_CLIENT_INFO("ExampleLayer::Update");
		//auto [x, y] = Mimou::Input::GetMousePos();
		//bool A = Mimou::Input::IsKeyPressed(MM_KEY_A);
		//bool ML = Mimou::Input::IsMouseButtonPressed(MM_MOUSE_BUTTON_LEFT);
		////MM_CORE_TRACE("{0}, {1}", x, y);
		//if (A) {
		//	MM_CORE_WARN("A is pressed!!!");
		//}
		//if (ML) {
		//	MM_CORE_WARN("Left mouse button is pressed!!!");
		//}

		// this way the movement will be more smooth
		// scince it update per frame, the speed depends
		// on the frame rate;

		m_CameraController.OnUpdate(ts);

		if (Mimou::Input::IsKeyPressed(MM_KEY_LEFT)) {
			m_SquarePosition.x -= m_SquareSpeed * ts;
		}
		if (Mimou::Input::IsKeyPressed(MM_KEY_RIGHT)) {
			m_SquarePosition.x += m_SquareSpeed * ts;
		}
		if (Mimou::Input::IsKeyPressed(MM_KEY_UP)) {
			m_SquarePosition.y += m_SquareSpeed * ts;
		}
		if (Mimou::Input::IsKeyPressed(MM_KEY_DOWN)) {
			m_SquarePosition.y -= m_SquareSpeed * ts;
		}
		//if (Mimou::Input::IsKeyPressed(MM_KEY_N)) {
		//	m_Camera.SetRotation(m_Camera.GetRotation() - m_CameraRotationS * ts);
		//}
		//if (Mimou::Input::IsKeyPressed(MM_KEY_M)) {
		//	m_Camera.SetRotation(m_Camera.GetRotation() + m_CameraRotationS * ts);
		//}

		

		Mimou::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Mimou::RenderCommand::Clear();

		Mimou::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Mimou::OpenGLShader>(square_Shader)->Bind();
		std::dynamic_pointer_cast<Mimou::OpenGLShader>(square_Shader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int i = 0; i <= 20; i++) {
			for (int j = 0; j <= 20; j++) {
				glm::vec3 pos = m_SquarePosition + glm::vec3({ i * 0.11, j * 0.11, 0 });
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Mimou::Renderer::Submit(square_VertexArray, square_Shader, transform);
			}
		}
		auto texture_Shader = m_ShaderLibrary.Get("Texture");
		m_Texture->Bind();
		Mimou::Renderer::Submit(square_VertexArray, texture_Shader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_LogoTexture->Bind(); 
		Mimou::Renderer::Submit(square_VertexArray, texture_Shader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		//Mimou::Renderer::Submit(m_VertexArray, m_Shader);
		Mimou::Renderer::EndScene();

	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("square color");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Mimou::Event& e) override {
		//Mimou::EventDispatcher dispatcher(event);
		//dispatcher.Dispatch<Mimou::KeyPressedEvent>(MM_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
		m_CameraController.OnEvent(e);
	}

	//bool OnKeyPressedEvent(Mimou::KeyPressedEvent& event) {
	//	int key = event.GetKeyCode();
	//	switch(key) {
	//	case MM_KEY_E:
	//		m_Camera.SetRotation(m_Camera.GetRotation() + m_CameraRotationS);
	//		MM_CORE_INFO("Key e is pressed");
	//		break;
	//	case MM_KEY_Q:
	//		m_Camera.SetRotation(m_Camera.GetRotation() - m_CameraRotationS);
	//		break;
	//	case MM_KEY_A:
	//		m_CameraPosition.x += m_CameraSpeed;
	//		break;
	//	case MM_KEY_D:
	//		m_CameraPosition.x -= m_CameraSpeed;
	//		break;
	//	case MM_KEY_W:
	//		m_CameraPosition.y -= m_CameraSpeed;
	//		break;
	//	case MM_KEY_S:
	//		m_CameraPosition.y += m_CameraSpeed;
	//		break;
	//	case MM_KEY_Z:
	//		m_CameraPosition.z -= m_CameraSpeed;
	//		break;
	//	}
	//	m_Camera.SetPosition(m_CameraPosition);
	//	return true;
	//}

private:
	// different with shared_ptr, unique_ptr only allow
		// one pointer points to an object
	Mimou::ShaderLibrary m_ShaderLibrary;
	Mimou::Ref<Mimou::Shader> m_Shader;
	Mimou::Ref<Mimou::VertexArray> m_VertexArray;

	Mimou::Ref<Mimou::Shader> square_Shader;
	Mimou::Ref<Mimou::VertexArray> square_VertexArray;

	Mimou::Ref<Mimou::Texture2D> m_Texture, m_LogoTexture;

	Mimou::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquarePosition;
	float m_SquareSpeed = 2.0f;
	float m_SquareRotationS = 2.0f;

	glm::vec3 m_SquareColor;

};

class Sandbox : public Mimou::Application {
public:
	Sandbox() {
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox() {

	}
};

// global variables initialized before the main function
Mimou::Application* Mimou::CreateApplication() {
	return new Sandbox();
}
