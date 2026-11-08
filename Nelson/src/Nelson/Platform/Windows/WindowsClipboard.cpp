#include "nspch.h"
#include <GLFW/glfw3.h>
#include "Nelson/Application.h"
#include "Nelson/Clipboard.h"

namespace Nelson {

	std::string Clipboard::GetText() {
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		const char* rezultat =  glfwGetClipboardString(window);
		if (rezultat == nullptr) {
			return nullptr;
		}
		return static_cast<std::string>(rezultat);
	}

	void Clipboard::SetText(const std::string& text) {
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		glfwSetClipboardString(window, text.c_str());
	}
}