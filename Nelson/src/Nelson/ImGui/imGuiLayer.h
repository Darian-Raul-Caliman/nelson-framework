#pragma once
#include "Nelson/Layer.h"
#include "Nelson/Events/KeyEvent.h"
#include "Nelson/Events/MouseEvents.h"
#include "Nelson/Events/ApplicationEvent.h"

namespace Nelson {

	class NS_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnEvent(Event& event);
		void OnAttach();
		void OnDetach();

		void Begin();
		void End();
	};
}