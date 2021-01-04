#pragma once

#include "Mimou/Input.h"

namespace Mimou {

	class WindowsInput : public Input {
	protected:
		// still write virtual here is just for a reminder
		// whether write or not, this is always still a virtual function
		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
		virtual std::pair<float, float> GetMousePosImpl() override;
	};

}