#pragma once

#include "Mimou/Renderer/OrthographicCamera.h"
#include "Mimou/Core/TimeStep.h"

#include "Mimou/Events/Event.h"
#include "Mimou/Events/ApplicationEvent.h"
#include "Mimou/Events/MouseEvent.h"

namespace Mimou {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = true);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }
		
		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		// put m_AspectRatio above m_Camera so that it will initialized
		// before m_Camera.
		OrthographicCamera m_Camera;

		bool m_Rotation;
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 2.0f;
		float m_CameraRotationSpeed = 2.0f;
	};

}

