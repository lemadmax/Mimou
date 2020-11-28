#pragma once

// #include "I:/GameEngine/learning/Mimou0/Mimou/Mimou/src/Mimou/Core.h"
#include "Mimou/Core.h"

namespace Mimou {

	enum class EventType {
		None = 0,
		WindowClose,
		WindowResize,
		WindowFocus,
		WindowLostFocus,
		WindowMoved,
		AppTick,
		AppUpdate,
		AppRender,
		KeyPressed,
		KeyReleased,
		MouseButtonPressed,
		MouseButtonReleased,
		MouseMoved,
		MouseScrolled
	};

	enum EventCategory {
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4),
	};

// Static event because we don't actually need the event to check what event it is
// virtual functions can still be virtual in the derived class
// const means the function cannot change any values
// override is to avoid mistakely override a function
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::type;} \
								virtual EventType GetEventType() const override {return GetStaticType();} \
								virtual const char* GetName() const override {return #type;}

#define EVENT_CLASS_GATEGORY(category) virtual int GetCategoryFlags() const override {return category;}

	class MIMOU_API Event {
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}
	protected:
		// If we don't want to process this event
		// further, set this to true.
		bool m_Handled = false;
	};

	class EventDispatcher {
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) : m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFn<T> func) {
			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			else return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	}

}
