#pragma once
#include "Nelson/Input.h"
#include <GLFW/glfw3.h>

namespace Nelson {
	class WindowInput : public Input {

	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;

	private:

	};
}