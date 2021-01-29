#include "mmpch.h"

#include "Application.h"
#include "Log.h"
#include "Mimou/Events/MouseEvent.h"
#include "Mimou/Events/ApplicationEvent.h"
#include <GLFW/glfw3.h>

#include <glad/glad.h>

#include "Input.h"

#include "glm/glm.hpp"

namespace Mimou {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	

	Application::Application() {
		MM_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		// set eventcallbackfn of m_window to be OnEvent(event)
		// then when a event happen, data.eventcallbackfn is OnEvent(event)
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		
		m_ImGuiLayer = std::make_unique<ImGuiLayer>();

		// Create and bind vertics and indics
		// Vertex Array
		m_VertexArray.reset(VertexArray::Create());
		
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f
		};
		// Vertex Buffer
		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ "a_Posistion", ShaderDataType::Float3 },
			{ "a_Color", ShaderDataType::Float4 }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);
		
		// Index Buffer
		uint32_t indices[3] = {
			0, 1, 2
		};
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, 3));
		m_VertexArray->AddIndexBuffer(indexBuffer);
		// Shader (vertex shader, fragment shader)
		// define shaders
		// R"()" make it easier to write multiple lines
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec4 v_Color;

			void main()
			{
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
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

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

		float Svertices[4 * 3] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		uint32_t Sindices[6] = {
			0, 1, 2, 2, 3, 0
		};

		square_VertexArray.reset(VertexArray::Create());
		std::shared_ptr<VertexBuffer> squareBuffer;
		std::shared_ptr<IndexBuffer> squareIndexB;
		squareBuffer.reset(VertexBuffer::Create(Svertices, sizeof(Svertices)));
		squareIndexB.reset(IndexBuffer::Create(Sindices, sizeof(Sindices) / sizeof(uint32_t)));
		BufferLayout Slayout = {
			{"a_Position", ShaderDataType::Float3}
		};
		squareBuffer->SetLayout(Slayout);
		square_VertexArray->AddVertexBuffer(squareBuffer);
		square_VertexArray->AddIndexBuffer(squareIndexB);

		std::string SvertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			
			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
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
		square_Shader.reset(new Shader(SvertexSrc, SfragmentSrc));
	}
	Application::~Application() {}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed));
		//MM_CORE_TRACE("{0}", e);
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.Handled) break;
		}
	}

	void Application::Run() {
		//MouseMovedEvent e(3.23, 1.33);
		//WindowResizeEvent e1(1232, 332);
		//if (!e.IsInCategory(EventCategoryApplication)) {
		//	MM_CLIENT_ERROR("not an application event");
		//}
		//if (e.IsInCategory(EventCategoryMouse)) {
		//	MM_CLIENT_TRACE(e);
		//}
		//MM_CLIENT_TRACE(e1);
		while (m_Running) {
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			
			// Bind shader
			square_Shader->Bind();
			square_VertexArray->Bind();
			//glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, square_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
			
			// Bind shader
			m_Shader->Bind();
			m_VertexArray->Bind();
			//glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			

			for (Layer* layer : m_LayerStack) 
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

}