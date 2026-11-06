#include "nspch.h"
#include "Application.h"
#include "Layer.h"
#include "Input.h"
#include "Nelson/Log.h"
#include "Timestep.h"
#include "imgui.h"
#include <glad/GLAD.h>
#include "Nelson/Platform/PlatformUtils.h"

namespace Nelson {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application(const ApplicationSpecification& spec ) {
		NS_CORE_ASSERT(!s_Instance, "Application already exists ! ");
		m_Specification = spec;
		m_timestamp = std::chrono::steady_clock::now();
		s_Instance = this;
		m_Settings.Load(GetUserDataPath(m_Specification.Name) / "settings.json");
		WindowProps props(m_Specification.Name, m_Specification.Width, m_Specification.Height);
		m_Window = std::unique_ptr<Window>(Window::Create(props));
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::onEvent));
		m_Window->SetVSync(m_Specification.VSync);

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application() {

	}
	
	void Application::SetUpdateMode(UpdateMode mode) {
		m_Specification.Mode = mode;
		m_Window->SetWaitForEvents(mode == UpdateMode::OnDemand);
	}


	void Application::PushLayer(Layer* layer) 
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer) 
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::Close() {
		m_Running = false;
	}

	Settings& Application::GetSettings()
	{
		return m_Settings;
	}


	void Application::onEvent(Event& e) {

		EventDispatcher dispatcher(e);
		//NS_CORE_INFO("{0}", e); Logging events in the console
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		NS_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled())
			{
				break;
			}
		}

	}


	UpdateMode Application::GetUpdateMode() const
	{
		return UpdateMode();
	}

	const ApplicationSpecification& Application::GetSpecification() const
	{
		return m_Specification;
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {

		m_Running = false;
		return true;

	}

	void Application::Run() {
		



		while (m_Running) {

			auto now = std::chrono::steady_clock::now();
			Timestep ts = std::chrono::duration<float>(now - m_timestamp).count();
			m_timestamp = now;
			// daca trece timestampul de 100 ms se seteaza ca fiind acela 
			if (ts > 0.1f)
				ts = 0.1f;

			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate(ts);
			}		

			m_ImGuiLayer->Begin();

			if (m_MenubarCallback)
			{
				if (ImGui::BeginMainMenuBar())
				{
					m_MenubarCallback();
					ImGui::EndMainMenuBar();
				}
			}

			if (m_Specification.EnableDockspace)
				ImGui::DockSpaceOverViewport(nullptr, ImGuiDockNodeFlags_PassthruCentralNode);


			for (Layer* layer : m_LayerStack)
				layer->OnUIRender();

			m_ImGuiLayer->End();




				

			m_Window->OnUpdate();
		}

		m_LayerStack.Clear();
		m_ImGuiLayer = nullptr;
		m_Settings.Save();
	}

}
