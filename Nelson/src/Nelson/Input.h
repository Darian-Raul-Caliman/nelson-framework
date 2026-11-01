#pragma once
#include "Core.h"
#include "Nelson/KeyCodes.h"
#include "Nelson/MouseCodes.h"
#include <utility>

namespace Nelson {


	class NS_API Input {


	public:
		static bool IsKeyPressed(Keycode key);
		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();




	};
}
