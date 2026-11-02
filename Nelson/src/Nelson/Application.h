#pragma once

#include "Core.h"
#include <chrono>
#include "Events/Event.h"
#include "Window.h"
#include "Nelson/Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Nelson/ImGui/imGuiLayer.h"


namespace Nelson {

	enum class UpdateMode
	{
		OnDemand,    
		Continuous   
	};


	class NS_API Application
	{
	public:
		Application();
		virtual ~Application();
		void onEvent(Event& e);
		void Run();
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
		void SetUpdateMode(UpdateMode mode);
		UpdateMode GetUpdateMode() const;
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
		static Application* s_Instance;
		ImGuiLayer* m_ImGuiLayer;
		std::chrono::steady_clock::time_point m_timestamp;
		UpdateMode m_UpdateMode = UpdateMode::OnDemand;
	};
	Application* CreateApplication();

}







