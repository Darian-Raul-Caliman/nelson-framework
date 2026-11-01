#include "nspch.h"
#include <GLFW/glfw3.h>
#include "Nelson/Application.h"
#include "Nelson/Input.h"

namespace Nelson {

	bool Input::IsKeyPressed(Keycode keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(MouseCode button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	float Input::GetMouseX()
	{

		return GetMousePosition().first;

	}

	float Input::GetMouseY()
	{

		return GetMousePosition().second;


	}

	std::pair<float, float> Input::GetMousePosition() {
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return
		{ (float)xpos, (float)ypos
		};
	}




}