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

	//user configuration needed, this is default

	struct ApplicationSpecification
	{
		std::string Name = "Nelson App";
		uint32_t Width = 1280;
		uint32_t Height = 720;
		bool VSync = true;
		UpdateMode Mode = UpdateMode::OnDemand;
		bool EnableDockspace = true;
	};


	class NS_API Application
	{
	public:
		Application(const ApplicationSpecification& spec = ApplicationSpecification());
		virtual ~Application();
		void onEvent(Event& e);
		void Run();
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
		void SetUpdateMode(UpdateMode mode);
		UpdateMode GetUpdateMode() const;
		const ApplicationSpecification& GetSpecification() const;
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
		static Application* s_Instance;
		ImGuiLayer* m_ImGuiLayer;
		std::chrono::steady_clock::time_point m_timestamp;
		UpdateMode m_UpdateMode = UpdateMode::OnDemand;
		ApplicationSpecification m_Specification;


	};
	Application* CreateApplication();

}







