#pragma once

#include "mmpch.h"
#include "Core.h"

#include "Mimou/Events/Event.h"

namespace Mimou {

	struct WindowProps {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Mimou Engine",
			unsigned int width = 1280,
			unsigned int height = 720) : Title(title), Width(width), Height(height) {}
	};

	class MIMOU_API Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		
		virtual ~Window() {}
		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		// a const function doesn't change no members;
		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};

}